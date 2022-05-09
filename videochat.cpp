#include "videochat.h"
#include "ui_videochat.h"
#include "settingwidget.h"
#include "dialoglist.h"
#include "sharecontrol.h"
#include "ExternVariable.h"
#include "videowidget.h"
#include <QSettings>
#include <QPushButton>
#include <QDebug>
#include "normal.h"
VideoChat::VideoChat(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::VideoChat)
{
    ui->setupUi(this);
    setWindowTitle(name);
    QString fileName = QCoreApplication::applicationDirPath();

    QSettings *set= new QSettings(fileName+"/startSetting.ini", QSettings::IniFormat);
    qDebug() << fileName+"/startSetting.ini";

    //麦克风默认状态是关闭的
    camera = !set->value("camera/enable").toBool();
    //摄像头默认处于关闭状态
    mic = !set->value("microphone/enable").toBool();
    //系统声音信号默认处于关闭状态；
    sys_voice = !set->value("redio/enable").toBool();
    myIsSharing = false;



    //刷新获取当前的长和宽
    currentH = this->size().height();
    currentW = this->size().width();

    chatwi = new Widget(0,0);
    kern->get_user();
    shareWidget = new ShareWidget();
    //设置当前有人共享屏幕的状态为false;
    issharing = false;
    myname = name;






//    videoWidget1 = new VideoWidget();
//    videoWidget1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    for(int i=0 ;i<geshu ; i++)
    {
        QLabel *lable = new QLabel();
        int label_r = i / conlum;
        int label_c = i - label_r * conlum;
        double label_w = this->size().width()/conlum;
        double label_h = (this->size().height() -35) / row;

         //设置label的大小,位置
        lable->setGeometry(label_c *label_w,label_r * label_h ,label_w,label_h);
        lable->setFrameShape (QFrame::Box);
        lable->setParent(this);
        //设置label的样式表
        lable->setStyleSheet("QLabel{background-color:rgb(60, 54, 54);color:rgb(0, 0, 0)}");
//        lable->setText(kern->get_name(i));
        //获取当前的成员的列表，将现有成员的所有的名字显示在显示屏上
//        if(i < kern->get_user().count()){
//            lable->setText(kern->get_name(i));
//        }
        labelList.push_back(lable);
    }
    ui->previouPageBtn->setGeometry(0,(this->size().height() / 2) -20,30,30);
    ui->nextPageBtn->setGeometry(this->size().width()-30,(this->size().height() / 2) -20,30,30);
    ui->previouPageBtn->raise();
    ui->nextPageBtn->raise();

    frashVideo();
    qDebug()<<"初始化视频界面";
//    //初始化视频区域
//    QList<UserId> list = kern->get_user();

//    for (int i = 0; i < geshu && i + page * geshu < list.count() + 1; i++){
//       if(i ==0 && page == 0){
//            labelList[(0) % geshu]->setPixmap(namePicture(myname).scaled(labelList[i+1]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//            continue;
//       }
//       //先把所有人的信息全部用文字刷新一遍
//            labelList[(i + 1) % geshu]->setPixmap(namePicture(kern->get_name(i+page * geshu)).scaled(labelList[i+1]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

//   }


//    //获取其他id下传送来的图像
//   connect(kern, &Kernel::recv_video, this, [=](UserId id, QImage img) {
//         QList<UserId> list = kern->get_user();
//         for (int i = 0; i < geshu && i + page * geshu < list.count(); i++)
//            {
//                if (list[i + page * geshu] == id)
//                {

//                    labelList[i]->setPixmap(QPixmap::fromImage(img).scaled(labelList[i]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

//                }
//        }
//   });
   //获取自己图像
      connect(kern, &Kernel::get_video, this, [=](QImage img) {
           if(page == 0)
           {
               labelList[0]->setPixmap(QPixmap::fromImage(img).scaled(labelList[0]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
           }
      });
       //获取其他id下传送来的图像
      connect(kern, &Kernel::recv_video, this, [=](UserId id, QImage img) {
            QList<UserId> list = kern->get_user();
            for (int i = 0; i < geshu && i + page * geshu < list.count() + 1; i++)
               {
                   if(i ==0 && page == 0)
                   {
                       continue;
                   }
                   if(kern->get_camera(id))
                   {
                       if (list[i - 1 + page * geshu] == id)
                       {

                           labelList[i]->setPixmap(QPixmap::fromImage(img).scaled(labelList[i]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

                       }else{
                           qDebug() << "未开摄像头用户";
                            labelList[i]->setPixmap(namePicture(kern->get_name(list[i-1 + page * geshu])).scaled(labelList[i]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                       }
                   }

           }
      });
      //接收到用户数量发生改变的信号的时候，会重新刷新当前的界面
//      connect(kern,&Kernel::user_change,[=](UserId id, bool access){
//          //用户的数量发生改变的时候会判断当前窗口是否为用户Id所在的窗口、
//          //用户数量增加的时候检验当前的屏
//          if(access == true){

//          }
//      });

//   for(auto label:labelList ){
//       ui->verticalLayout_2->addWidget(label);
//   }


//    connect(&kern, &Kernel::recv_video, this, [=](UserId id, QImage img) {

//        QList<UserId> list = kern->get_user();
//        for(auto i :list)
//        {
//            qDebug()<<i;
//        }
//        qDebug()<<"--------";
//        for (int i = 0; i < geshu && i + page * geshu < list.count(); i++)
//        {
//            if (list[i + page * geshu] == id)
//            {

//                labelList[i]->setPixmap(QPixmap::fromImage(img));

//            }
//        }
//    });

//    for(int i =0;i < row;i++){

//        for(int j =0;j < conlum;j++){
//            ui->gridLayout_2->addWidget(labelList[i*conlum + j],i,j);

//        }
//    }

//   for(int i=0;i < row;i++){
//       ui->gridLayout_2->setRowStretch(i, 1);
//   }
//   for(int i=0;i < conlum;i++){
//       ui->gridLayout_2->setColumnStretch(i, 1);
//   }

      //接受到其他用户的共享屏幕的信号并进行显示
  connect(kern,&Kernel::recv_desktop,[=](UserId id,QImage image){
      shareWidget->setWindowTitle(kern->get_name(id)+"当前正在共享屏幕");
      shareWidget->getLabel()->setPixmap(QPixmap::fromImage(image).scaled(shareWidget->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
      //如果当前没有用户在展示，则证明窗口不存在需要将窗口显示出来
      if(issharing == false){
           shareWidget->show();
      }
      issharing = true;
  });
   //接受对方请求控制我的电脑（是/否）窗口（对方请求控制我的电脑）
   connect(kern,&Kernel::recv_control, [=](UserId id){
       recvControlWidget = new RecvControlWidget(0,id);
       recvControlWidget->show();
   });

   //获取对方成功接收远控信号
   connect(kern,&Kernel::ok_control, this, [=](UserId id, bool access){
       if(access == true){
            conWidget = new ControlWidget(0,id);
       }else{
            QMessageBox::warning(this,tr("警告"),"对方拒绝了你的远控请求",QMessageBox::Yes);
       }
   });

   connect(kern,&Kernel::ok_controlled, this, [=](UserId id, bool access){
       if(access == true){
            kern->start_show_pri(true);
       }else{
            QMessageBox::warning(this,tr("警告"),"对方拒绝了你的受远控请求",QMessageBox::Yes);
       }
   });
   //接受对方发出的请求被远控的信号（对方请求我控制他）
   connect(kern,&Kernel::recv_controlled,[=](UserId id){
       int rec = QMessageBox::question(this,tr("请求受控"),kern->get_name((id))+"请求您控制他的设备",QMessageBox::Yes | QMessageBox::No);
       if(rec == QMessageBox::Yes){
           conWidget = new ControlWidget(0,id);
           kern->accept_controlled(id, true);
       }else{
           QMessageBox::information(this,tr("拒绝"),"已拒绝对方的受控请求",QMessageBox::Yes);
           kern->accept_controlled(id, false);
       }
   });


   //接收对方远控结束的信号
   connect(kern,&Kernel::screen_change,[=](UserId id, bool access){
      if(access == false){
          conWidget->close();
      }
   });


   //接收对方下线和上线的信号
   connect(kern,&Kernel::user_change,[=](UserId id,bool access){
        frashVideo();
   });

   connect(kern,&Kernel::video_change,[=](UserId id,bool access){
        frashVideo();
   });
   connect(kern,&Kernel::get_userlist,[=](){
        frashVideo();
   });
   frashCameraBtn();
   frashRedioBtn();
   frashMicroBtn();

}

VideoChat::~VideoChat()
{
    delete ui;
}

//刷新当前的视频窗口
void VideoChat::frashVideo(){

    QList<UserId> list = kern->get_user();
    qDebug()<<"fresh :"<<list.count();
    if(page == 0){
         labelList[0]->setPixmap(namePicture(myname).scaled(labelList[0]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
         for (int i = 1; i < geshu && i + page * geshu <= list.count(); i++){
            qDebug() << "label运行了  "  << i;
            //先把所有人的信息全部用文字刷新一遍
            labelList[i]->setPixmap(namePicture(kern->get_name(list[i-1+page * geshu])).scaled(labelList[0]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }else{
        for (int i = 0; i <  geshu && i + page * geshu < list.count(); i++){

           //先把所有人的信息全部用文字刷新一遍
           labelList[i]->setPixmap(namePicture(kern->get_name(list[i+page * geshu])).scaled(labelList[0]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
       }

    }

}

void VideoChat::frashMicroBtn()
{
    //如果麦克风的状态是开启的，则将麦克风关闭
    //麦克风的状态是开启，则当前显示图片应该是麦克风关闭的图片
   if(mic == true){
       mic = false;
       kern->enable_mic(false);
       //更换图片
       QPixmap micPix(":/imge/icon/png/microphoneOn.png");
       ui->microButton->setIcon(QIcon(micPix));
   }else{
       QPixmap micPix(":/imge/icon/png/microphoneOff.png");
       ui->microButton->setIcon(QIcon(micPix));
       kern->enable_mic(true);
       mic = true;
   }
}

void VideoChat::frashCameraBtn()
{
 //如果相机是开启的状态，显示的图片应当是关闭的
   if(camera == true){
       //将相片的设置调整为否定
       camera = false;
       kern->enable_camera(false);
       QPixmap camPix(":/imge/icon/png/videoOn.png");
       ui->videoButton->setIcon(QIcon(camPix));
       if(page == 0)
       {
           labelList[0]->setPixmap(namePicture(myname).scaled(labelList[0]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
       }
   }else{
       camera = true;
       kern->enable_camera(true);
       QPixmap camPix(":/imge/icon/png/videoOff.png");
       ui->videoButton->setIcon(QIcon(camPix));

   }
}
void VideoChat::frashRedioBtn()
{
    //如果声音是开启的状态，显示的图片应当是关闭的
      if(sys_voice == true){
          //将相片的设置调整为否定
          sys_voice = false;
          kern->enable_audio(false);
          QPixmap redioPix(":/imge/icon/png/redioOn.png");
          ui->redioButton->setIcon(QIcon(redioPix));
      }else{
          sys_voice = true;
           kern->enable_audio(true);
          QPixmap redioPix(":/imge/icon/png/redioOff.png");
          ui->redioButton->setIcon(QIcon(redioPix));
      }
}

void VideoChat::on_microButton_clicked()
{
    frashMicroBtn();
}
void VideoChat::on_videoButton_clicked()
{
    frashCameraBtn();
}

void VideoChat::on_redioButton_clicked()
{
    frashRedioBtn();
}

//共享屏幕的api
void VideoChat::on_screenShareButton_clicked()
{
    if(myIsSharing == false){
        kern->start_show(true);
        myIsSharing = true;
        QPixmap redioPix(":/imge/myIcon/isSharing.png");
        ui->screenShareButton->setIcon(QIcon(redioPix));
    }else{
        kern->start_show(false);
        myIsSharing = false;
        QPixmap redioPix(":/imge/icon/png/screenSharing.png");
        ui->screenShareButton->setIcon(QIcon(redioPix));
    }

}

//群组的功能
void VideoChat::on_manListButton_clicked()
{

}

//聊天窗口
void VideoChat::on_chatButton_clicked()
{
     QWidget *chatListWidget = new DialogList();
     chatListWidget->show();
}

//设置窗口
void VideoChat::on_settingButton_clicked()
{
    QWidget *setWidget = new SettingWidget(this);
    setWidget->show();
}

//关闭窗口
void VideoChat::on_overButton_clicked()
{
    this->close();
}

//请求远控
void VideoChat::on_remoteButton_clicked()
{
    QWidget *conWidget = new ShareControl();
    conWidget->show();
}
//窗口大小调整
void VideoChat::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
//    double label_w = this->size().width()/conlum;
//    double label_h = (this->size().height() -35) / row;
//    qDebug() << "label数值" <<label_w << "  " << label_h;
//    QList<UserId> list = kern->get_user();
//    for (int i = 0; i < geshu && i + page * geshu < list.count(); i++){
//        int label_r = i / conlum;
//        int label_c = i - label_r * conlum;
//        labelList[i]->setGeometry(label_c *label_w,label_r * label_h ,label_w,label_h);
//   }
//    ui->ButtonFrame->setGeometry(0,this->size().height()- 35,label_w,35);
}

void VideoChat::on_previouPageBtn_clicked()
{
    if(page >0) {
        page--;
        frashVideo();
    }
}

void VideoChat::on_nextPageBtn_clicked()
{
    if(page < kern->get_user().count() + 1 / geshu){
        page ++;
        frashVideo();
    }
}
