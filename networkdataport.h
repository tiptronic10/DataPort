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
signals:
    void sig_received(const QByteArray data);
    void sig_error(int);
    void sig_connected();
    void sig_disconnected();
	public slots:
		void slt_init();
        void slt_open(const QString& address, const int& port);
        void slt_read();
        void slt_write(const QByteArray& data);
		void slt_close();
private:
	QTcpSocket* m_socket;
};

#endif // NETWORKDATAPORT_H
