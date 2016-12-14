#ifndef DATAPORT_H
#define DATAPORT_H

#include "dataport_global.h"
#include "networkdataport.h"
#include "serialdataport.h"

class DATAPORTSHARED_EXPORT DataPort
{

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

private:
    DataPort_Type m_portType;
    NetworkDataPort* m_networkDataPort;
    SerialDataPort* m_serialDataPort;
};

#endif // DATAPORT_H
