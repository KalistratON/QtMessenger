#include "server.h"

Server::Server()
{
    if (listen(QHostAddress::Any, quint16(1234)))
        qDebug() << QString("Server has been started on 1234 port\n");
    else
    {
        qDebug() << QString("Server can't be start\n");
        exit (EXIT_FAILURE);
    }
}

Server::~Server()
{
    close();
}

void Server::recvFrom()
{
    socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream input(socket);
    input.setVersion(QDataStream::Qt_6_5);

    if (input.status() == QDataStream::Ok)
    {
        qDebug() << "reading ...\n";
        editor(input, QString("Anonymus"));
    }
    else
        qDebug() << "Broken data. Can't be read\n";
}

void Server::sendTo(const QString& msg)
{
    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);
    output << msg;

    for (const auto& sock : sockets)
        sock->write(data);
}

void Server::editor(QDataStream& input, const QString& _name)
{
    QString str;
    input >> str;

    sendTo(QString(_name + QString(":\n\t") + str + QString("\n")));
}

void Server::incomingConnection(qintptr socketDescription)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescription);
    connect(socket, &QTcpSocket::readyRead, this, &Server::recvFrom);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    sockets.push_back(socket);
    qDebug() << "New client was added\n";

    //QTcpServer::incomingConnection(socketDescription);
}


