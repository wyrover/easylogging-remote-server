#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include "server.h"
#include "easylogging++.h"
#include "credentials.h"
#include "json_packet.h"
#include "requests/request.h"
#include "requests/request_type.h"
#include "requests/request_factory.h"

const char* Server::kPortParam = "--port";

Server::Server(Credentials *credentials, QObject *parent) :
    QTcpServer(parent), m_credentials(credentials)
{
    m_port = el::Helpers::commandLineArgs()->hasParamWithValue(kPortParam)
            ? atoi(el::Helpers::commandLineArgs()->getParamValue(kPortParam))
            : kDefaultPort;

    if (m_port == 0) {
        m_port = kDefaultPort;
    }
}

Server::~Server(void)
{
    LOG(INFO) << "Stopping server on port [" << m_port << "]";
}

std::string Server::address(void) const {
    std::string ipAddresses;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            ipAddresses = address.toString().toStdString() + " ";
    }
    return ipAddresses;
}

void Server::start(void)
{
    if (!listen(QHostAddress::Any, m_port)) {
        LOG(FATAL) << "Unable to start server on port [" << m_port << "]." << std::endl
                   << "    Please make sure this port is free." << std::endl
                   << "    You can specify server port by using [" << kPortParam << "] argument";
        exit(1);
    }
    QObject::connect(this, SIGNAL(newConnection()), this, SLOT(onReceived()));

    LOG(INFO) << "Starting server {" << std::endl
              << "    Parameters: " << *el::Helpers::commandLineArgs() << std::endl
              << "    Address: " << address() << std::endl
              << "    Port: " << m_port << std::endl
              << "    Easylogging++ v" << el::VersionInfo::version() << std::endl
              << "}";
}

void Server::readCompletePacket(QTcpSocket *connection, QString& target) const
{
    QString packet(connection->readAll());
    // FIXME: This does not work for big data e.g, conf_data etc
    bool readFailed = false;
    while (!readFailed && !packet.contains("}\0")) {
        readFailed = !connection->waitForReadyRead(100);
        packet += connection->readAll();
    }

    target = packet;
}

void Server::onReceived(void)
{
    QTcpSocket* connection = nextPendingConnection();
    QObject::connect(connection, SIGNAL(disconnected()), connection, SLOT(deleteLater()));
    QObject::connect(connection, SIGNAL(readyRead()), this, SLOT(packetReady()));
}

void Server::packetReady(void)
{
    QTcpSocket* connection = static_cast<QTcpSocket*>(sender());
    VLOG(3) << "Reading packet from connection [" << connection << "]";
    QString packet;
    readCompletePacket(connection, packet);
    JsonPacket jsonPacket(packet.toStdString());
    if (!jsonPacket.valid()) {
        LOG(ERROR) << jsonPacket.lastError();
        connection->write("ERR: Invalid JSON");
        connection->disconnectFromHost();
        return;
    }
    Request* request = RequestFactory::buildRequest(&jsonPacket, m_credentials);
    if (request == nullptr) {
        connection->write("ERR: Invalid request type");
        connection->disconnectFromHost();
        return;
    }
    VLOG(4) << "Received JSON: " << *request->jsonPacket();
    if (!request->valid()) {
        std::stringstream ss;
        ss << "ERR: " << request->lastError();
        connection->write(ss.str().c_str());
        LOG(ERROR) << request->lastError();
        connection->disconnectFromHost();
        delete request;
    }
    if (!request->userHasPermissions(m_credentials)) {
        LOG(ERROR) << "Unsuccessful attempt to [" << RequestTypeHelper::convertToString(request->type()) << "] by user ["
                      << request->user() << " (" << m_credentials->getPermissions(request->user()) << ")]";
        connection->write("ERR: Permission denied");
    } else {
        if (request->process()) {
            connection->write("OK");
        } else {
            LOG(ERROR) << request->lastError();
            std::stringstream ss;
            ss << "ERR: " << request->lastError();
            connection->write(ss.str().c_str());
        }
    }

    connection->disconnectFromHost();
    delete request;
}
