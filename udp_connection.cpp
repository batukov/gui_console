#include "udp_connection.h"



udp_connection::udp_connection(QObject *parent) : QObject(parent)
{
    this->socket =  new QUdpSocket();
    QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(get_data()));
}
udp_connection::~udp_connection()
{}
void udp_connection::send_msg_to_ch(QString msg)
{
    //qint64 request_size = sizeof(msg);
    QByteArray request_buffer;
    request_buffer.insert(0, msg);
    this->socket->bind(this->address, this->port_output);
    qint64 result = this->socket->writeDatagram(request_buffer, this->address, this->port_output);
}
void udp_connection::set_address(QHostAddress address)
{
    QObject::disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(get_data()));
    this->address = address;
    this->socket->bind(this->address, this->port_input);
    QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(get_data()));
}
void udp_connection::set_input_port(quint16 input_port)
{
    QObject::disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(get_data()));
    this->port_input = input_port;
    this->socket->bind(this->address, this->port_input);
    QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(get_data()));
}
void udp_connection::set_output_port(quint16 output_port)
{
    this->port_output = output_port;
}
void udp_connection::get_data()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    int is_data = socket->readDatagram(datagram.data(), datagram.size(), address);
    if(is_data != -1)
    {
        emit got_msg(datagram.data());
    }
}
