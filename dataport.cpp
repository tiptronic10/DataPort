#include "dataport.h"

DataPort::DataPort() : m_portType(DataPort_Type::NULL_PORT),m_thread(nullptr), m_networkDataPort(nullptr), m_serialDataPort(nullptr)
{

}

DataPort::DataPort(DataPort_Type type) : m_thread(nullptr), m_networkDataPort(nullptr), m_serialDataPort(nullptr)
{
	switch(type)
	{
	case DataPort_Type::NULL_PORT:
		break;
	case DataPort_Type::NETWORK_PORT:
		m_thread = new QThread;
		m_networkDataPort = new NetworkDataPort();
		m_networkDataPort->moveToThread(m_thread);
		m_thread->start();
		break;
	case DataPort_Type::SERIAL_PORT:
		m_thread = new QThread;
		m_serialDataPort = new SerialDataPort();
		m_serialDataPort->moveToThread(m_thread);
		m_thread->start();
		break;
	}
	m_portType = type;
}

DataPort::~DataPort()
{
	switch(m_portType)
	{
	case DataPort_Type::NULL_PORT:
		break;
	case DataPort_Type::NETWORK_PORT:
		delete m_networkDataPort;
		m_networkDataPort = nullptr;
		break;
	case DataPort_Type::SERIAL_PORT:
		delete m_serialDataPort;
		m_serialDataPort = nullptr;
		break;
	}
	m_portType = DataPort_Type::NULL_PORT;
}

void DataPort::createDataPort(DataPort_Type type)
{
	if(m_portType == DataPort_Type::NULL_PORT)
	{
		switch(type)
		{
		case DataPort_Type::NULL_PORT:
			break;
		case DataPort_Type::NETWORK_PORT:
			m_thread = new QThread;
			m_networkDataPort = new NetworkDataPort();
			m_networkDataPort->moveToThread(m_thread);
			m_thread->start();
			break;
		case DataPort_Type::SERIAL_PORT:
			m_thread = new QThread;
			m_serialDataPort = new SerialDataPort();
			connect(this, SIGNAL(sig_wirte(QByteArray)), m_serialDataPort, SLOT(SerialDataPort::slt_write(QByteArray)));
			connect(m_thread, SIGNAL(started()), m_serialDataPort, SLOT(SerialDataPort::slt_init()));
			connect(m_serialDataPort->m_serialPort, SIGNAL(readyRead()), m_serialDataPort, SLOT(SerialDataPort::slt_read()));
			connect(m_serialDataPort->m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT());
			connect(m_serialDataPort, SIGNAL(sig_received(QByteArray)), this, SIGNAL(sig_received(QByteArray)));//发送接收数据
			m_serialDataPort->moveToThread(m_thread);
			m_thread->start();
			break;
		}
		m_portType = type;
	}
}

int DataPort::getPortType()
{
	return m_portType;
}

bool DataPort::open()
{
	switch(m_portType)
	{
	case DataPort_Type::NULL_PORT:
		break;
	case DataPort_Type::NETWORK_PORT:
		m_networkDataPort->slt_open();
		break;
	case DataPort_Type::SERIAL_PORT:
		m_serialDataPort->slt_open();
		break;
	}

	return false;
}

void DataPort::write(const QByteArray &data)
{
	Q_UNUSED(data);
	switch(m_portType)
	{
	case DataPort_Type::NULL_PORT:
		break;
	case DataPort_Type::NETWORK_PORT:
		emit sig_wirte(data);
		break;
	case DataPort_Type::SERIAL_PORT:
		emit sig_wirte(data);
		break;
	}
}

void DataPort::close()
{
	switch(m_portType)
	{
	case DataPort_Type::NULL_PORT:
		break;
	case DataPort_Type::NETWORK_PORT:
		m_networkDataPort->slt_close();
		break;
	case DataPort_Type::SERIAL_PORT:
		m_serialDataPort->slt_close();
		break;
	}
}