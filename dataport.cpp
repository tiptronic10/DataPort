#include "dataport.h"

DataPort::DataPort() : m_portType(DataPort_Type::NULL_PORT), m_networkDataPort(nullptr), m_serialDataPort(nullptr)
{

}

DataPort::DataPort(DataPort_Type type) : m_networkDataPort(nullptr), m_serialDataPort(nullptr)
{
    switch(type)
    {
    case DataPort_Type::NULL_PORT:
        break;
    case DataPort_Type::NETWORK_PORT:
        m_networkDataPort = new NetworkDataPort();
        break;
    case DataPort_Type::SERIAL_PORT:
        m_serialDataPort = new SerialDataPort();
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
            m_networkDataPort = new NetworkDataPort();
            break;
        case DataPort_Type::SERIAL_PORT:
            m_serialDataPort = new SerialDataPort();
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
        m_networkDataPort->open();
        break;
    case DataPort_Type::SERIAL_PORT:
        m_serialDataPort->open();
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
        m_networkDataPort->write(data);
        break;
    case DataPort_Type::SERIAL_PORT:
        m_serialDataPort->write(data);
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
        m_networkDataPort->close();
        break;
    case DataPort_Type::SERIAL_PORT:
        m_serialDataPort->close();
        break;
    }
}


