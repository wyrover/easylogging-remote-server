#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Request;
class Credentials;
class JsonPacket;

class Server : public QTcpServer {
    Q_OBJECT
public:

    static const char* kPortParam;
    static const int kDefaultPort = 1592;

    /// @brief Connection process timeout (in sec)
    /// Time to wait until we are ready to process request from client
    static const int kReadTimeout = 60;

    explicit Server(Credentials* credentials, QObject *parent = nullptr);
    virtual ~Server(void);
    void start();
private:
    Credentials* m_credentials;
    int m_port;
    void readCompletePacket(QTcpSocket* connection, QString& target) const;
private slots:
    void onReceived(void);
    void packetReady(void);
};

#endif // SERVER_H
