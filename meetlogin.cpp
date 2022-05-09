#include "meetlogin.h"
#include "ui_meetlogin.h"
#include "videochat.h"
#include "ExternVariable.h"
meetlogin::meetlogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::meetlogin)
{
    passwd_Visiable = false;
    ui->setupUi(this);
    setWindowTitle("登录");
    ui->passwdEdit->setEchoMode(QLineEdit::Password);
    ui->visiableButton->setStyleSheet("QToolButton{border:Opx}");

    connect(kern,&Kernel::login_result,[=](LOGIN_RESULT result){qDebug()<<int(result);
        if(result == LOGIN_RESULT::SUCCESS)
         {mywidget = new VideoChat(0,ui->userEdit->text());mywidget->show();}
    });
}

meetlogin::~meetlogin()
{
    delete ui;
}



void meetlogin::on_visiableButton_clicked()
{   if(passwd_Visiable == false){
        ui->passwdEdit->setEchoMode(QLineEdit::Normal);
        QPixmap pixmap(":/imge/visible.png");
        ui->visiableButton->setIcon(QIcon(pixmap));
        passwd_Visiable = true;
    }else{
        ui->passwdEdit->setEchoMode(QLineEdit::Password);
        QPixmap pixmap(":/imge/invisible.png");
        ui->visiableButton->setIcon(QIcon(pixmap));
        passwd_Visiable = false;
    }

}

void meetlogin::on_enterAdmin_clicked()
{
    this->hide();
    kern->login(ui->userEdit->text(),ui->passwdEdit->text());


}
