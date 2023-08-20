#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtCore>
#include <QTextEdit>
#include <QMenuBar>
#include <QListView>
#include <QGridLayout>
#include <QPushButton>

#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QVector>

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QTextEdit* textEditRead = nullptr;
    QTextEdit* textEditWrite = nullptr;
    QMenuBar* menuBar = nullptr;
    QListView* listView = nullptr;
    QGridLayout* layout = nullptr;
    QPushButton* push = nullptr;

    QTcpSocket* socket = nullptr;

private slots:
    void recvFrom();
    void sendTo();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void setUi();
};
#endif // MAINWINDOW_H
