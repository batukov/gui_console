#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>
#include <QList>

class console : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit console(QWidget *parent = nullptr);

    void putData(const QByteArray &data);
    void putData(const QString &data);
    QStringList history;
    int historyPos = 0;
    void historyAdd(QString cmd);
    void historyBack();
    void historyForward();
public slots:
    void get_data_from_udp(QByteArray);
signals:
    void send_to_udp(QString msg);
protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

};

#endif // CONSOLE_H




