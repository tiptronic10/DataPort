#ifndef SERIALDATAPORT_H
#define SERIALDATAPORT_H

#include <QObject>
#include <QSerialPort>
#include <QThread>

class SerialDataPort : public QObject
{
	Q_OBJECT

public:
	explicit SerialDataPort(QObject *parent = 0);
	QSerialPort* m_serialPort;
signals:
	void sig_received(const QByteArray data);
	public slots:
		void slt_init();
		void slt_open();
		void slt_read();
		void slt_write(const QByteArray& data);
		void slt_close();
private:
	QByteArray m_receivedData;
};

#endif // SERIALDATAPORT_H
