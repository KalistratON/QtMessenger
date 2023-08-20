#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    QVector<QTcpSocket*> sockets;
private slots:
    void recvFrom();
protected:
    void incomingConnection(qintptr socketDescription) override;
    void editor(QDataStream&, const QString&);
    virtual void sendTo(const QString&);

public:
    Server();
    ~Server();
};

#endif // SERVER_H
