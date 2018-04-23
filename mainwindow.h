#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <console.h>
#include <udp_connection.h>



QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}


QT_END_NAMESPACE
class console;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QHBoxLayout *mainLayout;
    QHBoxLayout *port_o_Layout;
    QHBoxLayout *port_i_Layout;
    QHBoxLayout *ip_Layout;
    QVBoxLayout *statLayout;
    console *my_console = nullptr;
    QLineEdit *port_output;
    QLineEdit *port_input;
    QPushButton *port_output_label;
    QPushButton *port_input_label;
    QPushButton *ip_address_label;
    QLineEdit *ip_address;

    udp_connection *connection;
private slots:
    void input_port_changed();
    void output_port_changed();
    void address_changed();
    void resend_msg(QString);

signals:
    void send_msg_to_udp(QString);
};

#endif // MAINWINDOW_H
