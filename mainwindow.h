#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include"readLetter.h"
#include<QTreeWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseMoveEvent(QMouseEvent *event);      //拖拽窗口用的
    void mousePressEvent(QMouseEvent *event);      //拖拽窗口用的
    void mouseReleaseEvent(QMouseEvent *event);      //拖拽窗口用的
    QWidget *createItem(QString title, QString content, QString num);      //向邮件列表里添加邮件条目
    QPoint mouse_relative_pos;      //拖拽窗口用的
    void UpdateLetter();      //更新，收取全部邮件

          //下面几个字符串是重要的变量，所有收发邮件都要用到这些字符串
string smtpServer;      //smtp服务器
string smtpPort;      //smtp端口
string pop3Server;      //pop3服务器
string pop3Port;      //pop3端口
string mailAddress;      //邮件地址
string userName;      //用户名
string password;      //密码
vector<readLetterSimple> allLetter;      //所有邮件的全部信息，一个readLetterSimple类包含一封邮件

void displayLetter(QString id);      //在邮件列表里显示一封信
void removeLetter(QString id);      //在邮件列表里删除一封信
private slots:
    void on_nextHello_clicked();

    void on_MailWhu_clicked();

    void on_toMainPage_clicked();

    void on_mailList_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_back_clicked();

    void on_send_clicked();

    void on_back_2_clicked();

    void on_toWrite_clicked();

    void on_del_clicked();

    void on_refresh_clicked();

    void on_reply_clicked();

    void on_refresh_2_clicked();

    void on_Mail163_clicked();

    void on_MailOther_clicked();

    void on_Mailqq_clicked();

    void on_nextSMTP_clicked();

    void on_nextPOP3_clicked();

    void on_toDelete_clicked();

    void on_deleteList_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_back_3_clicked();

private:
    Ui::MainWindow *ui;

public slots:
    void on_UpdateDone();
    void on_UpdateStart();
    void on_UpdateWrong();
};
#endif // MAINWINDOW_H
