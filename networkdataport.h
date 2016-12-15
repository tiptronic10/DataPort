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

	public slots:
		void slt_init();
		void slt_open();
		void slt_write(const QByteArray& data);
		void slt_close();
private:
	QTcpSocket* m_socket;
};

#endif // NETWORKDATAPORT_H
