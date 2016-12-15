#ifndef DATAPORT_H
#define DATAPORT_H

#include "dataport_global.h"
#include "networkdataport.h"
#include "serialdataport.h"
#include <QSerialPort>
#include <QTcpSocket>
#include <QObject>

class DATAPORT_EXPORT DataPort : public QObject
{
	Q_OBJECT
public:
	enum DataPort_Type{
		NULL_PORT,
		NETWORK_PORT,
		SERIAL_PORT
	};

	DataPort();
	DataPort(DataPort_Type);
	~DataPort();

	void createDataPort(DataPort_Type);
	int getPortType();

	bool open();
	void write(const QByteArray& data);
	void close();

signals:
	void sig_received(QByteArray data);
	void sig_error(int);
	void sig_wirte(QByteArray data);

private:
	QThread* m_thread;
	DataPort_Type m_portType;
	NetworkDataPort* m_networkDataPort;
	SerialDataPort* m_serialDataPort;
};

#endif // DATAPORT_H
