#include "dataport.h"

DataPort::DataPort(DataPort_Type type) : m_thread(nullptr), m_networkDataPort(nullptr), m_serialDataPort(nullptr)
{
	switch(type)
	{
	case DataPort_Type::NULL_PORT:
		break;
	case DataPort_Type::NETWORK_PORT:
		m_thread = new QThread;
		m_networkDataPort = new NetworkDataPort();
		//向网口操作
		connect(this, SIGNAL(sig_open(QString, int)), m_networkDataPort, SLOT(slt_open(QString, int)));
		connect(this, SIGNAL(sig_wirte(QByteArray)), m_networkDataPort, SLOT(slt_write(QByteArray)));
		connect(this, SIGNAL(sig_close()), m_networkDataPort, SLOT(slt_close()));
		//接收网口信号
		connect(m_networkDataPort, SIGNAL(sig_received(QByteArray)), this, SIGNAL(sig_received(QByteArray)));//发送接收数据
		connect(m_networkDataPort, SIGNAL(sig_error(QString)), this, SIGNAL(sig_error(QString)));
		connect(m_networkDataPort, SIGNAL(sig_connected()), this, SIGNAL(sig_opened()));
		connect(m_networkDataPort, SIGNAL(sig_disconnected()), this, SIGNAL(sig_closed()));
		//响应退出信号
		connect(this, SIGNAL(sig_quiting()), m_networkDataPort, SLOT(deleteLater()));
		connect(m_networkDataPort, SIGNAL(destroyed(QObject*)), m_thread, SLOT(quit()));
		connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));
		//响应子线程启动信号
		connect(m_thread, SIGNAL(started()), m_networkDataPort, SLOT(slt_init()));
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
		connect(m_serialDataPort, SIGNAL(sig_error(QString)), this, SIGNAL(sig_error(QString)));
		connect(m_serialDataPort, SIGNAL(sig_connected()), this, SIGNAL(sig_opened()));
		connect(m_serialDataPort, SIGNAL(sig_disconnected()), this, SIGNAL(sig_closed()));
		//响应退出信号
		connect(this, SIGNAL(sig_quiting()), m_serialDataPort, SLOT(deleteLater()));
		connect(m_serialDataPort, SIGNAL(destroyed(QObject*)), m_thread, SLOT(quit()));
		connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));
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
	emit sig_quiting();
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
