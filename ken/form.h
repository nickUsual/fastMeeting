#ifndef FORM_H
#define FORM_H
#include<qbytearray.h>
enum class RESULT :int
{
    SUCCESS,
    FAIL
};
enum class LOGIN_RESULT :int
{
    DISCONNECTION,//网络链接失败
    PASS_ERROR,//密码错误
    SUCCESS//登录成功
};

enum class mationType//不要写成enum class MsgType,这样的话，无法输出里面的值。
{
    send,//转发
    link,    //连接时的消息，密码昵称什么的
    client_change,//客户端变动的消息类型。
    userlist,
    enable_camera,
    enable_screen,
    enable_mic,
};


typedef int UserId;

//enum class MsgType :int
//{
//    MSG,//消息
//    GROUNP_MSG,//群发消息
//    CAMERA,//摄像头
//    CAMERA_ENABLE,//摄像头开关
//    AUDIO,//音频
//    SCREEN,//屏幕截图
//    BOARD,//剪切板
//    COMMANDOUT,//命令行
//    ASK_CONTRAL,//请求控制
//    ASK_CONTRALLED,//请求被远控
//    ACK_CONTRAL,//接收远控
//    ACK_CONTRALLED,//接收被远控
//    MOUSE_MOVE,//鼠标移动
//    MOUSE_CLICK,//鼠标按下
//    KEY_CLICK,//键盘按下
//    STARTCOMMAND,//开启命令行
//    COMMAND,//命令
//    DISCONTRAL,//断开远控
//};
enum class MsgType :int
{
    MSG,//消息
    GROUNP_MSG,//群发消息
    CAMERA,//摄像头
    CAMERA_ENABLE,//摄像头开关
    AUDIO,//音频
    MIC_ENABLE,//麦克风开关
    SCREEN,//屏幕截图
    SCREEN_PRI,//屏幕截图私法
    SCREEN_ENABLE,//屏幕开关
    BOARD,//剪切板
    COMMANDOUT,//命令行
    ASK_CONTRAL,//请求控制
    ASK_CONTRALLED,//请求被远控
    ACK_CONTRAL,//接收远控
    ACK_CONTRALLED,//接收被远控
    MOUSE_MOVE,//鼠标移动
    MOUSE_CLICK,//鼠标按下
    KEY_CLICK,//键盘按下
    STARTCOMMAND,//开启命令行
    COMMAND,//命令
    DISCONTRAL,//断开远控

};
const QByteArray NULLBYTE = 0;

enum  SettingState
{
    SYSTEM_SET,//系统设置
    REDIO_SET,//音频信息
    MEETING_INFOR,//会议信息
    ABOUT_US//关于我们
};

typedef bool ClientChange;//真为上线，假为下线

#define GROUP 0 //用于群发
#endif
