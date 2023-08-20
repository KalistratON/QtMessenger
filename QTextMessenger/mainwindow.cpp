#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    textEditRead(new QTextEdit(this)),
    textEditWrite(new QTextEdit(this)),
    listView(new QListView(this)),
    layout(new QGridLayout(this)),
    push(new QPushButton(this))
{
    socket = new QTcpSocket(this);

    socket->connectToHost(QHostAddress::LocalHost, quint16(1234), QIODeviceBase::ReadWrite);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::recvFrom);
    connect(socket, &QTcpSocket::disconnected, &QTcpSocket::deleteLater);
    connect(push, &QPushButton::clicked, this, &MainWindow::sendTo);

    setUi();

    textEditRead->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    socket->disconnectFromHost();
}

void MainWindow::recvFrom()
{
    socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream input(socket);
    input.setVersion(QDataStream::Qt_6_5);

    if (input.status() == QDataStream::Ok)
    {
        qDebug() << "reading ...\n";

        QString str;
        input >> str;
        textEditRead->append(str);
    }
    else
        qDebug() << "Broken data. Can't be read\n";
}

void MainWindow::sendTo()
{
    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);
    output << textEditWrite->toPlainText();

    socket->write(data);
    textEditWrite->clear();
}

void MainWindow::setUi()
{
    // repair layout

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(textEditRead,     0, 1, 1, 2);
    layout->addWidget(textEditWrite,    2, 1, 2, 1);
    layout->addWidget(push,             4, 1, 2, 1);
    layout->addWidget(listView,         0, 0, 6, 1);

    setLayout(layout);
}

