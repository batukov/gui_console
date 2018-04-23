#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    my_console(new console)
{
    ui->setupUi(this);
    this->mainLayout = new QHBoxLayout();
    this->port_o_Layout = new QHBoxLayout();
    this->port_i_Layout = new QHBoxLayout();
    this->ip_Layout = new QHBoxLayout();
    this->statLayout = new QVBoxLayout();

    this->ip_address_label = new QPushButton(tr("ip adress"));
    this->ip_address = new QLineEdit(tr("127.0.0.1"));
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    this->ip_address->setValidator(ipValidator);
    this->ip_address_label->setStyleSheet("Text-align:center");

    this->port_input = new QLineEdit(tr("20061"));
    this->port_input_label = new QPushButton(tr("input port"));
    QString poRange = "(?:[0-5]?[0-9]?[0-9]?[0-9]?[0-9]|6[0-4][0-9]?[0-9]?[0-9]|65[0-4]?[0-9]?[0-9]|655[0-2]?[0-9]|6553[0-5])"; //0-65535
    QRegExp poRegex ("^" + poRange + "$");
    QRegExpValidator *poValidator = new QRegExpValidator(poRegex, this);
    this->port_input->setValidator(poValidator);
    this->port_input_label->setStyleSheet("Text-align:center");

    this->port_output = new QLineEdit(tr("20061"));
    this->port_output_label = new QPushButton(tr("output port"));
    QString piRange =  "(?:[0-5]?[0-9]?[0-9]?[0-9]?[0-9]|6[0-4][0-9]?[0-9]?[0-9]|65[0-4]?[0-9]?[0-9]|655[0-2]?[0-9]|6553[0-5])"; //0-65535
    QRegExp piRegex ("^" + piRange + "\\." + piRange + "\\." + piRange + "\\." + piRange + "$");
    QRegExpValidator *piValidator = new QRegExpValidator(piRegex, this);
    this->port_output->setValidator(piValidator);
    this->port_output_label->setStyleSheet("Text-align:center");

    // LAYOUT STUFF
    this->mainLayout->addWidget(this->my_console);
    ui->verticalLayout->addLayout(this->mainLayout);

    this->port_o_Layout->addWidget(this->port_output_label);
    this->port_o_Layout->addWidget(this->port_output);
    this->port_i_Layout->addWidget(this->port_input_label);
    this->port_i_Layout->addWidget(this->port_input);
    this->ip_Layout->addWidget(this->ip_address_label);
    this->ip_Layout->addWidget(this->ip_address);
    this->statLayout->addLayout(this->port_o_Layout);
    this->statLayout->addLayout(this->port_i_Layout);
    this->statLayout->addLayout(this->ip_Layout);
    this->statLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->statLayout);
    // UDP STUFF
    this->connection = new udp_connection();
    QHostAddress address;
    QString address_string = this->ip_address->text();
    address.setAddress(address_string);
    this->connection->set_address(address);
    this->connection->set_input_port(this->port_input->text().toShort());
    this->connection->set_output_port(this->port_output->text().toShort());
    QObject::connect(this->port_input_label, SIGNAL(clicked()), this, SLOT(input_port_changed()));
    QObject::connect(this->port_output_label, SIGNAL(clicked()), this, SLOT(output_port_changed()));
    QObject::connect(this->ip_address_label, SIGNAL(clicked()), this, SLOT(address_changed()));
    QObject::connect(this->my_console, SIGNAL(send_to_udp(QString)), this->connection, SLOT(send_msg_to_ch(QString)));
    QObject::connect(this->connection, SIGNAL(got_msg(QByteArray)), this->my_console, SLOT(get_data_from_udp(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_port_changed()
{
    this->connection->set_input_port(this->port_input->text().toShort());
}
void MainWindow::output_port_changed()
{
    this->connection->set_output_port(this->port_output->text().toShort());
}
void MainWindow::address_changed()
{
    QHostAddress address;
    QString address_string = this->ip_address->text();
    address.setAddress(address_string);
    this->connection->set_address(address);
}
void MainWindow::resend_msg(QString msg)
{
    emit send_msg_to_udp(msg);
}
