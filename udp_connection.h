#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include <QString>
#include <QUdpSocket>
#include "console.h"

class udp_connection : public QObject
{
    Q_OBJECT
private:

    QHostAddress address;
    quint16 port_output;
    quint16 port_input;
    console *terminal;
    QUdpSocket *socket;

public:
    explicit udp_connection(QObject *parent = 0);
    virtual ~udp_connection();

    void set_address(QHostAddress inc_address);
    void set_output_port(quint16 output_port);
    void set_input_port(quint16 input_port);
public slots:
    void send_msg_to_ch(QString msg);
    void get_data();
signals:
    void got_msg(QByteArray);

};

#endif // UDP_CONNECTION_H
