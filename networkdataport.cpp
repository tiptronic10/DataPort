#include "networkdataport.h"

NetworkDataPort::NetworkDataPort(QObject *parent) : QObject(parent)
{
}

void NetworkDataPort::slt_init()
{
    m_socket = new QTcpSocket;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slt_read()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slt_onError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(connected()), this, SIGNAL(sig_connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SIGNAL(sig_disconnected()));
}

void NetworkDataPort::slt_onError(QAbstractSocket::SocketError value)
{
    QString ErrInfo;
    ErrInfo = "SocketError  ErrorCode:" + QString::number(value);
    emit sig_error(ErrInfo);
}

void NetworkDataPort::slt_open(const QString& address, const int& port)
{
    m_socket->abort();
    m_socket->connectToHost(address, port);
}

void NetworkDataPort::slt_write(const QByteArray& data)
{
    m_socket->write(data);
}

void NetworkDataPort::slt_read(void)
{
    if(m_socket)
    {
        emit sig_received(m_socket->readAll());
    }
}

void NetworkDataPort::slt_close()
{
    m_socket->disconnectFromHost();
}
