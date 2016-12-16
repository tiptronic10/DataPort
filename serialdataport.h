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
signals:
	void sig_received(const QByteArray data);
	void sig_error(int);
	public slots:
		void slt_init();
		void slt_open(const QString& portName, const int& baudRate);
		void slt_read();
		void slt_write(const QByteArray& data);
		void slt_close();
private:
    QSerialPort* m_serialPort;
};

#endif // SERIALDATAPORT_H
