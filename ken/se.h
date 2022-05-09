﻿#ifndef SE_H
#define SE_H
#include <qobject.h>
#include <qbuffer.h>
#include "RemoteC.h"
#include "VideoC.h"
#include "netmanage.h"
#include "form.h"

//用于界面的核 ———— 音视频、桌面演示会持续收到，并不会关闭
class Kernel :public QObject
{
	Q_OBJECT
public:
	Kernel() { init(); }
private:
	//初始化，用于连接后配置接口
	void init();
private:/*网络*/
	netmanage net;
private:
	//收到消息
	void getData(UserId id, MsgType type, QByteArray data);
private:
	//连接结果
	void loginResult(LOGIN_RESULT result);
	//连接断开
	void ondislink();
	//用户改变
	void userChange(UserId id, ClientChange state);
	//发送失败
	void sendFailed();
public:/*连接*/
	//用户登录(昵称，密码)
	void login(QString name, QString password);
	//下线 —— 应用关闭的时候执行
	void dislink();
	//获取用户昵称（用户ID）
	QString get_name(UserId id);
	//获取当前在线用户
	QList<UserId> get_user();
	//获取用户昵称（用户ID）
	bool get_camera(UserId id);
	//获取用户昵称（用户ID）
	bool get_mic(UserId id);
	//获取用户昵称（用户ID）
	bool get_screen(UserId id);
signals:
	//登录结果(结果)
	void login_result(LOGIN_RESULT);
signals:
	//用户变动（变动用户编码，上下线（上线为true, 下线为false））
	void user_change(UserId, bool);
signals:
    void get_userlist();
signals:
	//服务器连接断开
	void server_dislink();


public:/*消息发送*/
	//发送聊天消息（接收方编码，消息内容）
	void send_msg(UserId, QString);
signals:
	//接收到消息(发送方编码，消息内容)
	void recv_msg(UserId, QString);
signals:
	//接收到群发消息(发送方编码，消息内容)
	void recv_msg_all(UserId, QString);
signals:
	//发送消息失败（接收方编号，消息内容）——未完成
	void fail_send_msg(UserId, QString);

private:/*视频*/
	VideoC video;
	bool audio_play_enable = false;//是否播放音频
	bool sys_enable = false;//输出系统声音
	bool mic_enable = false;//输出麦克声音
	unsigned display_freq = 30;//桌面演示截图频率
private:
	//捕获到摄像头截图
	void getCamera(const QImage& img);
	//捕获到音频
	void getAudio(QByteArray data);
public:
	//开启摄像头（开启摄像头）—— 默认为关闭（假为关闭）
	void enable_camera(bool enable);
	//开启麦克风（开启麦克风）—— 默认为关闭（假为关闭）
	void enable_mic(bool enable);
	//开启系统声音（开启系统声音）—— 默认为关闭（假为关闭）
	void enable_sys(bool enable);

	//自动播放接收到的音频（开启播放器）—— 默认为关闭（假为关闭）
	void enable_audio(bool enable);

	//获取当前输入音频 —— 返回为当前可用设备列表中的编号
	int get_input();

	//获取当前输出音频 —— 返回为当前可用设备列表中的编号
	int get_outout();
	//获取可用输入设备 —— 返回当前可用设备列表名
	QList<QString> get_input_list();
	//获取可以输出设备 —— 返回当前可用设备列表名
	QList<QString> get_output_list();
	//设置当前输入设备（可用设备列表中的编号）
	void set_input(int num);
	//设置当前输出设备（可用设备列表中的编号）
	void set_output(int num);
	//获取当前输入设备音量 —— 返回值在 0-1
	double get_input_volume();
    //获取当前输出设备音量 —— 返回值在 0-1
	double get_output_volume();
	//设置当前输入设备音量（音量（0-1））
	void set_input_volume(double volume);
	//设置当前输出设备音量（音量（0-1））
	void set_output_volume(double volume);
signals:
	//接收到视频（发送方编码，视频截图）
	void recv_video(UserId, QImage);
signals:
	//视频改变（发送方编码，开启）
	void video_change(UserId, bool);
signals:
	//麦克风改变（发送方编码，开启）
	void mic_change(UserId, bool);
signals:
	//捕获到本地视频（视频截图）
	void get_video(QImage);

private:/*远控*/
	UserId remoteId = -1; //远控另一端编码
	UserId remoteId_pre = -1;//准备接收远控的一端
	bool is_remoted = false;//被控制
	RemoteC remote;
	bool screen = false, screen_pri = false;
private:
	//捕获到屏幕截图
	void getScreen(const QImage& img);
	//获取剪切板变化
	void getBoard(QString data);
	//获取命令行输出
	void getCommandOut(QString info);
public:
	//开启远程演示（开启（假为关闭））
	void start_show(bool enable);
	//开启远程演示私发（开启（假为关闭））—— 用于远控
	void start_show_pri(bool enable);
	//请求远控（远控方编码）
	void ask_control(UserId id);
	//邀请远控（邀请远控方编码）
	void ask_controlled(UserId id);
	//接受远控（请求远控方编码，是否接受） —— 接受一方的远控请求
	void accept_control(UserId id, bool accept);
	//接受远控邀请（接收）
	void accept_controlled(UserId id, bool accept);
	//远控鼠标移动（鼠标x坐标/桌面宽度，鼠标y坐标/桌面高度）—— 这里的坐标是比例
	void remote_mouse_move(double x, double y);
	//远控鼠标按键（键值（qt的左中右键），按下（假为松开））
	void remote_mouse_cliked(int keyValue, bool down);
	//远控键盘按键（键值（qt的键值），按下（假为松开））
	void remote_key(int keyValue, bool down);
	//远控开启命令行（开启）
	void remote_start_command(bool enable);
	//远控执行命令（命令）
	void remote_run_command(QString command);
	//断开远控 —— 任意一方都可
	void disconnect_control();

signals:
	//接收到桌面演示（发送方编码，桌面截图）
	void recv_desktop(UserId, QImage);
signals:
	//接收到桌面演示私发（发送方编码，桌面截图）
	void recv_desktop_pri(UserId, QImage);
signals:
	//桌面演示改变（发送方编码，开启）
	void screen_change(UserId, bool);
signals:
	//收到远控请求（请求方编码）
	void recv_control(UserId);
signals:
	//收到远控邀请（邀请方编码）
	void recv_controlled(UserId);
signals:
	//远控请求同意（同意方编码, 是否同意）
	void ok_control(UserId, bool);
signals:
	//远控邀请同意（同意方编码, 是否同意）
	void ok_controlled(UserId, bool);
signals:
	//远控命令行收到输出（输出内容）
	void recv_command_out(QString);
signals:
	//远控另一方断开
	void remote_disconnect();
};
#endif // !SE_H
