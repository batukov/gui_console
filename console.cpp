#include "console.h"
#include <QScrollBar>
#include "QDebug"
#include <QTextBlock>
console::console(QWidget *parent) :
    QPlainTextEdit(parent)
{
    document()->setMaximumBlockCount(1000);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
}

void console::putData(const QByteArray &data)
{
    insertPlainText(data);

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void console::putData(const QString &data)
{
    insertPlainText(data);

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void console::keyPressEvent(QKeyEvent *e)
{
    QTextCursor cursor;
    if(e->key() == Qt::Key_Backspace)
    {
        if(e->modifiers() == Qt::NoModifier && textCursor().positionInBlock() > 0)
            {QPlainTextEdit::keyPressEvent(e);}
        else {return;}
    }
    switch (e->key()) {
    case Qt::Key_Up:
        this->historyBack();
        break;
    case Qt::Key_Down:
        this->historyForward();
        break;
    case Qt::Key_Return:
        cursor = textCursor();
        cursor.movePosition(QTextCursor::EndOfBlock);
        setTextCursor(cursor);
        emit send_to_udp(this->document()->lastBlock().text());
        this->historyAdd(this->document()->lastBlock().text());
    case Qt::Key_Backspace:
    default:
        QPlainTextEdit::keyPressEvent(e);
        break;
    }
}

void console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
void console::historyAdd(QString cmd)
{
    this->history.append(cmd);
    this->historyPos = this->history.length();
}

void console::historyBack()
{
    if(!historyPos)
        return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(this->history.at(this->historyPos-1));
    setTextCursor(cursor);
    this->historyPos--;
}

void console::historyForward()
{
    if(this->historyPos == this->history.length())
        return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    if(this->historyPos != this->history.length() - 1)
        cursor.insertText(this->history.at(historyPos + 1));
    setTextCursor(cursor);
    this->historyPos++;
}
void console::get_data_from_udp(QByteArray msg)
{
    QString new_data;
    new_data.append(msg);
    this->insertPlainText(new_data + "\r\n");

    QTextCursor cursor = this->textCursor();

    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock);
    setTextCursor(cursor);

}
