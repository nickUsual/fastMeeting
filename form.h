#ifndef FORM_H
#define FORM_H
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
typedef int UserId;

typedef int ClientChange;
enum class MsgType :int
{
    MSG,//消息
    CAMERA,//摄像头
    AUDIO,//音频
    SCREEN,//屏幕截图
    BOARD,//剪切板
    COMMAND,//命令行
};


enum  SettingState
{
    SYSTEM_SET,//系统设置
    REDIO_SET,//音频信息
    MEETING_INFOR,//会议信息
    ABOUT_US//关于我们
};

#define GROUP 0 //用于群发
#endif
