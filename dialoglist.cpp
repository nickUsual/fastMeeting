#include "dialoglist.h"
#include "ui_dialoglist.h"
#include "QToolButton"
#include "Widget.h"
#include "QMessageBox"
#include "ExternVariable.h"
DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("fastMeeting");
    //设置图标
    setWindowIcon(QPixmap(":/imge/QQ.png"));
    refrash();

    connect(kern, &Kernel::user_change, this, [=](){

        QLayoutItem *child;
        while ((child = ui->verticalLayout->takeAt(0)) != 0) {
            if(child->widget())
                delete child->widget();
            delete child;
        }
        refrash();
    });

}
void DialogList::refrash(){
    QStringList nameList;
    for(auto i:kern->get_user())
    {
        nameList<<kern->get_name(i);
    }

    QStringList iconList;
    iconList << "photo01.jpg" << "photo02.jpg"<< "photo01.jpg"<< "photo02.jpg"<< "photo03.jpg"<< "photo01.jpg"<< "photo02.jpg"<< "photo03.jpg"<< "photo01.jpg"<< "photo02.jpg";
    //加一个容器
    QVector<QToolButton *> buttonList;

    for(int i = 0;i < nameList.length();i++){
        //设置头像
        QToolButton *btn = new QToolButton;
        //设置名字
        btn->setText(nameList[i]);
        //设置头像图片
        btn->setIcon(QPixmap(":/imge/"+iconList[i % 9]));
        //设置头像大小
        btn->setIconSize(QSize(56,56));
        //设置按钮风格,透明
        btn->setAutoRaise(true);
        //设置文字和图片一起显示
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //加到垂直布局中去
        ui->verticalLayout->addWidget(btn);
        //容器保存九个按钮，用于后续的操作
        buttonList.push_back(btn);
        isShowList.push_back(false);
    }
    //对九个按钮，进行添加信号槽
    for(int i = 0;i < buttonList.size();i++){
        connect(buttonList[i],&QToolButton::clicked,[=](){
            //如果窗口被打开了，就不能被打开了
            if(isShowList[i]){
                QString str = QString("%1窗口已经被打开了").arg(buttonList[i]->text());
                QMessageBox::warning(this,"警告",str);
                return;
            }
            isShowList[i] = true;
            chatwi->fresh();
            chatwi->show();
            //弹出聊天对话框
            //构造聊天窗口的时候，告诉这个窗口他的名字，参数1，顶层方式弹出参数为0，参数2，窗口名字
//            Widget *widget = new Widget(0,kern->get_user()[i]);
//            widget->changeId();
//            //设置窗口的标题
//            widget->setWindowTitle(buttonList[i]->text());
//            widget->setWindowIcon(buttonList[i]->icon());
//            widget->show();
//            connect(widget,&Widget::closeWidget,[=](){
//               isShowList[i] = false;
//            });
        });
    }
}
DialogList::~DialogList()
{
    delete ui;
}
