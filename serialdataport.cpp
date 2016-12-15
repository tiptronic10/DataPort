#include "serialdataport.h"

SerialDataPort::SerialDataPort(QObject *parent) : QObject(parent)
{

}

void SerialDataPort::slt_init()
{
	m_serialPort = new QSerialPort;
	m_serialPort->open(QIODevice::ReadWrite);
}

void SerialDataPort::slt_open()
{

}

void SerialDataPort::slt_write(const QByteArray& data)
{
	m_serialPort->write(data);
}

void SerialDataPort::slt_read(void)
{
	if (m_serialPort)
	{
		m_receivedData = m_serialPort->readAll();
		emit sig_received(m_receivedData);
	}
}

void SerialDataPort::slt_close()
{
	m_serialPort->close();
}
