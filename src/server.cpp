#include "server.h"

#include <QTcpSocket>

#include "easylogging++.h"
#include "credentials.h"
#include "request_type.h"
#include "request.h"
#include "write_logs_request.h"

Server::Server(Credentials *credentials, QObject *parent) :
    QTcpServer(parent), m_port(-1), m_credentials(credentials)
{
}

Server::~Server(void)
{
    LOG(INFO) << "Stopping server on port [" << m_port << "]";
    close();
}

void Server::start(int port)
{
    CHECK(listen(QHostAddress::Any, port)) << "Unable to start server on port [" << port << "]." << std::endl <<
                                              " Please make sure this port is free."
                                              " You can specify server port by using [--port] argument";
    QObject::connect(this, SIGNAL(newConnection()), this, SLOT(onReceived()));

    m_port = port;
    LOG(INFO) << "Server started on port [" << m_port << "]";
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
    LOG(INFO) << "Reading packet from connection [" << connection << "]";
    QString packet = QString(connection->readAll());
    if (packet.startsWith("e")) exit(0);
    Request* request = buildRequestFromPacket(packet.toStdString());
    if (request == nullptr) {
        connection->disconnectFromHost();
        return;
    }
    if (!request->valid()) {
        connection->disconnectFromHost();
        LOG(ERROR) << request->lastError();
        delete request;
        return;
    }
    if (!request->userHasPermissions(m_credentials)) {
        LOG(ERROR) << "Unsuccessful attempt to [" << RequestTypeHelper::convertToString(request->type()) << "] by user [" <<
                      request->user() << " (" << m_credentials->getPermissions(request->user()) << ")]";
    } else {
        request->process();
    }
    delete request;
    connection->disconnectFromHost();
}

Request* Server::buildRequestFromPacket(const std::string& packet) const
{
    Request* request = nullptr;

    // Intel C++ does not yet support switch over strongly-typed enums so we use if-statements
    RequestType type = RequestTypeHelper::findRequestTypeFromJson(packet);
    if (type == RequestType::WriteLogs) {
        request = new WriteLogsRequest(packet);
    } else if (type == RequestType::NewLogger) {

    } else if (type == RequestType::ConfigurationUpdate) {

    } else if (type == RequestType::RunCommand) {

    } else {
        // Ignore, error is logged from findRequestTypeFromJson(..)
    }
    return request;
}
