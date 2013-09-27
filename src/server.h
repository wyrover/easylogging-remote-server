#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Request;
class Credentials;
class JsonPacket;

class Server : public QTcpServer {
    Q_OBJECT
public:

    /// @brief Connection process timeout (in sec)
    /// Time to wait until we are ready to process request from client
    static const int kReadTimeout = 60;

    explicit Server(Credentials* credentials, QObject *parent = nullptr);
    virtual ~Server(void);
    void start(int port);
private:
    int m_port;
    Credentials* m_credentials;
    Request* buildRequestFromPacket(JsonPacket* json) const;
    void processRequest(Request* request);
private slots:
    void onReceived(void);
    void packetReady(void);
};

#endif // SERVER_H
