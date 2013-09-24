#include "server.h"

#include <QTcpSocket>

#include "easylogging++.h"
#include "request_type.h"
#include "request.h"
#include "write_logs_request.h"

Server::Server(QObject *parent) :
    QTcpServer(parent), m_port(-1)
{
}

Server::~Server()
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
    Request* request = buildRequestFromPacket(packet.toStdString());
    if (request == nullptr || !request->valid()) {
        connection->disconnectFromHost();
        LOG_IF(request != nullptr && !request->valid(), ERROR) << request->lastError();
        return;
    }
    processRequest(request);
    delete request;
    connection->disconnectFromHost();
}

Request* Server::buildRequestFromPacket(const std::string& packet) const
{
    Request* request = nullptr;
    switch (RequestTypeHelper::findRequestTypeFromJson(packet)) {
        case RequestType::WriteLogs:
            request = new WriteLogsRequest(packet);
            break;
        case RequestType::NewLogger:
            break;
        case RequestType::ConfigurationUpdate:
            break;
        default:
            // Ignore, error is logged from findRequestTypeFromJson(..)
            break;
    }
    return request;
}

void Server::processRequest(Request* request)
{

}
