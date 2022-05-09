#ifndef REMOTEC_H
#define REMOTEC_H
#include <QMouseEvent>//用于鼠标
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <qprocess.h> //用于cmd
#include <qclipboard.h> //用于剪切板
#include <qdesktopwidget.h>//用于获取屏幕大小
#include <qscreen.h> //用于截图
#include <Windows.h> //键鼠的操控需要win的api
#include <qtimer.h> //计时器用于截图
#include <string.h>
#include <QTextCodec>//用于转码

//远程协助模块
class RemoteC : public QObject
{
	Q_OBJECT
private:
	//是否开启桌面截图捕获
	bool enable_screenshots = false;
	// 桌面截图捕获频率
	unsigned int freq_screenshots = 0;
	// 截图大小
    int screen_weight = 1920, screen_height = 1080;
	//是否开启剪切捕获
	bool enable_board = false;
	//是否开启命令行捕获
	bool enable_command = false;

private:
	QProcess* cmd = NULL;//存放命令行进程
	QClipboard* board = NULL;//用于存放剪切板
	QTimer* screen_timer = NULL;//用于存放截图计时器
public:
	RemoteC(QObject* parent = nullptr)
	{
		board = QGuiApplication::clipboard();
	}

private://工具类
	//键盘键值转换 qt->win
	int getKeyValue(int keyValue);
	//鼠标键值转换 qt->win
	int getMouseValue(int keyValue, bool down);


public://输入接口
	//移动鼠标
	void mouseMove(double x, double y);
	//模拟鼠标按键（键值，是否按下） —— 用win的api完成
	void mouseClicked(int keyValue, bool down);
	//模拟滑轮（滑动量） —— 用win的api完成
	void wheelEvent(int delta);
	//屏蔽按键

	//模拟键盘按键（键值，是否按下）—— 用win的api完成
	void keyEvent(int keyValue, bool down);
	//桌面截图捕获（捕获频率，是否开启）
	void screenshotsCapture(unsigned int freq, bool enable = true);
	//设置截图大小
	void setScreenSize(int Weight, int Height);
	//剪切捕获（是否开启）
	void boardCapture(bool enable = true);
	//修改剪切内容（内容）
	void boardChange(QString content);
	//命令行捕获（是否开启）
	void commandCapture(bool enable = true);
	//执行命令行（命令）
	void executeCommand(QString command);

private://用于接收信号
	//命令行输出
	void onReadoutput();
	//命令行报错
	void onReaderror();
	//剪切板改变
	void boardDataChanged();
public://内部处理
	//计时器事件
	void timerEvent(QTimerEvent* event);
	//截图
	void slotGrabFullScreen();
	//输出接口（消息槽）
signals:
	//输出命令行消息（消息内容）
	void commandOut(QString info);
signals:
	//输出剪切板变化内容（变化内容）
	void boardOut(QString data);
signals:
	//输出截图
	void screenOut(const QImage& img);
	
};
#endif

