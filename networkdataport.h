#ifndef NETWORKDATAPORT_H
#define NETWORKDATAPORT_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>

class NetworkDataPort : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDataPort(QObject *parent = 0);
    void init();
signals:

public slots:
    void open();
    void write(const QByteArray& data);
    void close();
private:
    QTcpSocket* m_socket;
    QThread* m_thread;
};

#endif // NETWORKDATAPORT_H
