#DataPort库
[toc]
###简介
```C++
int i = 0; i = 1;
for(int i = 0; i < 100; i++)
{
printf("hello markdown!\n");
}
```
###使用方法
实例化DataPort对象，构造函数选择串口或网口枚举参数，之后写入数据调用write();读取数据接收sig_received();监控错误信息sig_error();
```C++
DataPort* obj = new DataPort(DataPort::SERIAL_PORT);//实例化DataPort对象
//连接信号槽，负责处理接收数据以及错误信息
connect(obj, SIGNAL(sig_received(QByteArray)), this, SLOT(/*数据接收槽函数*/));
connect(obj, SIGNAL(sig_error(int)), this, SLOT(/*错误处理槽函数*/));
//需要写数据时
obj->write();
```
1. 插入图片
![](https://ws4.sinaimg.cn/mw600/6bade3a2gw1faq8hbjc3wj20m80godga.jpg)
1. 插入链接
[为知笔记](http://www.wizcn)