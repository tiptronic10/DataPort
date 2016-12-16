#include "dataport.h"

DataPort::DataPort(DataPort_Type type, const QString& str, const int& num) : m_thread(nullptr), m_networkDataPort(nullptr), m_serialDataPort(nullptr)
{
	m_strData = str;
	m_numData = num;
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
		//向串口操作
		connect(this, SIGNAL(sig_open(QString, int)), m_serialDataPort, SLOT(slt_open(QString, int)));
		connect(this, SIGNAL(sig_wirte(QByteArray)), m_serialDataPort, SLOT(slt_write(QByteArray)));
		connect(this, SIGNAL(sig_close()), m_serialDataPort, SLOT(slt_close()));
		//接收串口信号
		connect(m_serialDataPort, SIGNAL(sig_received(QByteArray)), this, SIGNAL(sig_received(QByteArray)));//发送接收数据
		connect(m_serialDataPort, SIGNAL(sig_received(QByteArray)), this, SIGNAL(sig_received()));
		connect(m_serialDataPort, SIGNAL(sig_error(QSerialPort::SerialPortError)), this, SIGNAL(sig_error(int)));
		//响应子线程启动信号
		connect(m_thread, SIGNAL(started()), m_serialDataPort, SLOT(slt_init()));
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

int DataPort::getPortType()
{
	return m_portType;
}

void DataPort::open(const QString& strAddress, const int& number)
{
	emit sig_open(strAddress, number);
}

void DataPort::write(const QByteArray &data)
{
	emit sig_wirte(data);
}

void DataPort::close()
{
	emit sig_close();
}