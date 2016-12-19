#DataPort库
[toc]
###简介
DataPort是一个封装后的Qt通信类，数据的读写在子线程中进行，不会阻塞主线程，其通信类包括串口类和网口类
里面使用的是Qt的框架，线程间通信使用信号槽机制，子线程采用movetoThread方法
###使用方法
实例化DataPort对象，构造函数选择串口或网口枚举参数，之后写入数据调用write();读取数据接收sig_received();监控错误信息sig_error();
```C++
//串口使用示例
DataPort* obj = new DataPort(DataPort::SERIAL_PORT);//实例化DataPort对象
//连接信号槽，负责处理接收数据以及错误信息
connect(obj, SIGNAL(sig_received(QByteArray)), this, SLOT(/*数据接收槽函数*/));
connect(obj, SIGNAL(sig_error(int)), this, SLOT(/*错误处理槽函数*/));
connect(obj, SIGNAL(sig_opened()), this, SLOT(slt_onConnected(/*串口打开成功处理槽函数*/)));
connect(obj, SIGNAL(sig_closed()), this, SLOT(slt_onDisconnect(/*串口关闭成功处理槽函数*/)));
//打开串口
obj->open("COM1", 115200);//Windows操作系统
//obj->open("ttyUSB0", 115200);//Linux操作系统
//需要写数据时
obj->write();
//关闭串口
obj->close();
/////////////////////////////////////////////////////////////
//网口使用示例
DataPort* obj = new DataPort(DataPort::NETWORK_PORT);//实例化DataPort对象
//连接信号槽，负责处理接收数据以及错误信息
connect(obj, SIGNAL(sig_received(QByteArray)), this, SLOT(/*数据接收槽函数*/));
connect(obj, SIGNAL(sig_error(int)), this, SLOT(/*错误处理槽函数*/));
connect(obj, SIGNAL(sig_opened()), this, SLOT(/*网口连接成功相关处理*/));
connect(obj, SIGNAL(sig_closed()), this, SLOT(/*网口连接失败相关处理*/));
//连接主机
obj->open("192.168.1.22", 66);
//需要写数据时
obj->write();
//关闭串口
obj->close();
```
1. 插入图片
![](https://ws4.sinaimg.cn/mw600/6bade3a2gw1faq8hbjc3wj20m80godga.jpg)
1. 参考来源  
[如何实现在一个线程内新建QTcpSocket且实现定时判定socket是否连接成功](http://bbs.csdn.net/topics/390161203)  
[Qt 多线程串口通信问题](https://www.zhihu.com/question/31518679)