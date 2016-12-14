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
    void init();
signals:

public slots:
    void open();
    void write(const QByteArray& data);
    void close();
private:
    QSerialPort* m_serialPort;
    QThread* m_thread;
};

#endif // SERIALDATAPORT_H
