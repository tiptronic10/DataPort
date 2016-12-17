#include "serialdataport.h"

SerialDataPort::SerialDataPort(QObject *parent) : QObject(parent)
{
}

void SerialDataPort::slt_onError(QSerialPort::SerialPortError value)
{
    QString ErrInfo;
    ErrInfo = "SerialPortError  ErrorCode:" + QString::number(value);
    emit sig_error(ErrInfo);
}

void SerialDataPort::slt_init()
{
	m_serialPort = new QSerialPort;
	connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(slt_read()));
    connect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SIGNAL(slt_onError(QSerialPort::SerialPortError)));
}

void SerialDataPort::slt_open(const QString& portName, const int& baudRate)
{
	m_serialPort->setPortName(portName);
	if(m_serialPort->open(QIODevice::ReadWrite))
	{
		m_serialPort->setBaudRate(baudRate);
		m_serialPort->setDataBits(QSerialPort::Data8);
		m_serialPort->setParity(QSerialPort::NoParity);
		m_serialPort->setStopBits(QSerialPort::OneStop);
	}
}

void SerialDataPort::slt_write(const QByteArray& data)
{
	m_serialPort->write(data);
}

void SerialDataPort::slt_read(void)
{
	if (m_serialPort)
	{
//		m_receivedData = m_serialPort->readAll();
//		emit sig_received(m_receivedData);
        emit sig_received(m_serialPort->readAll());
	}
}

void SerialDataPort::slt_close()
{
	m_serialPort->close();
}
