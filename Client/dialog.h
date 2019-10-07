#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QTcpSocket *m_pClientSocket;
private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void on_pushButtonConnect_clicked();
    void on_pushButtonSend_clicked();
    void readyRead();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
