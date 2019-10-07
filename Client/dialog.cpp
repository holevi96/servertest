#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    m_pClientSocket = new QTcpSocket(this);
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButtonConnect_clicked()
{
    m_pClientSocket->connectToHost(ui->textEditIP->toPlainText(),quint16(ui->textEditPort->toPlainText().toInt()));
    //connect the socket error to our error
    connect(m_pClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_pClientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}
void Dialog::readyRead(){
    QTcpSocket *server = (QTcpSocket*)sender();
    QString line = QString::fromUtf8(server->readLine()).trimmed();
    qDebug() <<  "Returned message: " << line;
}
void Dialog::on_pushButtonSend_clicked()
{
    QString message = ui->textEditMessage->toPlainText().trimmed();

    // Only send the text to the chat server if it's not empty:
    if(!message.isEmpty())
    {
        qDebug() <<  message;
        m_pClientSocket->flush();
        m_pClientSocket->write(QString(message + " ").toUtf8());
    }

    // Clear out the input box so they can type something else:
    ui->textEditMessage->clear();

    // Put the focus back into the input box so they can type again:
     ui->textEditMessage->setFocus();
}
void Dialog::displayError ( QAbstractSocket::SocketError socketError )
{
    switch (socketError) {
         case QAbstractSocket::RemoteHostClosedError:
             break;
         case QAbstractSocket::HostNotFoundError:
             QMessageBox::information(this, tr("Fortune Client"),
                                      tr("The host was not found. Please check the "
                                         "host name and port settings."));
             break;
         case QAbstractSocket::ConnectionRefusedError:
             QMessageBox::information(this, tr("Fortune Client"),
                                      tr("The connection was refused by the peer. "
                                         "Make sure the fortune server is running, "
                                         "and check that the host name and port "
                                         "settings are correct."));
             break;
         default:
             QMessageBox::information(this, tr("Fortune Client"),
                                      tr("The following error occurred: %1.")
                                      .arg(m_pClientSocket->errorString()));
         }


}
