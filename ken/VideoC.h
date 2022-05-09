#ifndef VIDEOC_H
#define VIDEOC_H
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <qtimer.h> //计时器用于视频截图
#include <QCamera> //用于获取摄像头
#include <QCameraImageCapture>//用于获取摄像头截图

#include <QAudio>     //这五个是QT处理音频的库
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>

class VideoC :public QObject
{
	Q_OBJECT
private:
	//是否开启视频捕获
	bool enable_camera = false;
	// 视频捕获频率
	unsigned int freq_camera = 0;
	// 视频捕获高度、宽度
	unsigned int weight_camera = 160, height_camera = 120;
	//是否开启音频捕获
	bool enable_audio_mic = false;
	bool enable_audio_sys = false;
private:
	QTimer* camera_timer = NULL;//用于存放截图计时器
	QCamera camera;//摄像头
	QCameraImageCapture imageCapture;//摄像头截图

	QAudioInput* audio_in_mic;//麦克风音频输入
	QAudioInput* audio_in_sys;//系统音频输入
	QAudioOutput* audio_out;//音频输出
	int input_number;//输入设备编码
	int output_number;//输出设备编号
	QIODevice* audio_streamIn_mic;//麦克风音频输入流
	QIODevice* audio_streamIn_sys;//系统音频输入流
	QIODevice* audio_out_streamIn;//音频输出流
	QAudioFormat audio_settings;//音频设置
	QMetaObject::Connection connect_mic;//临时存放麦克链接
public:
	VideoC(QObject* parent = nullptr)
		:imageCapture(&camera)
	{
		//初始化摄像头参数
		camera.setCaptureMode(QCamera::CaptureStillImage);
		if (imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer)) {}
		imageCapture.setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
		imageCapture.setBufferFormat(QVideoFrame::PixelFormat::Format_Jpeg);
		//cameraSizeSetting(weight_camera, height_camera);
		connect(&imageCapture, &QCameraImageCapture::imageCaptured, this, &VideoC::processCapturedImage);
		//初始化音频参数
		//设置音频格式	
		QAudioDeviceInfo input_Device_mic; //麦克风音频输入设备
		QAudioDeviceInfo input_Device_sys; //系统音频输入设备
		QAudioDeviceInfo output_Device; //音频输出设备

		auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
		bool get_sys = false;
		foreach(auto &i, info)
		{
			if (i.deviceName().left(5) == QStringLiteral("立体声混音") && !get_sys)
			{
				input_Device_sys = i;
				get_sys = true;
			}
			
		}
		input_Device_mic = QAudioDeviceInfo::defaultInputDevice();
		input_number = 0;
		output_Device = QAudioDeviceInfo::defaultOutputDevice();
		output_number = 0;
		audio_settings.setCodec("audio/pcm");
		audio_settings.setSampleRate(44100);
		audio_settings.setSampleType(QAudioFormat::SampleType(1));
		audio_settings.setSampleSize(16);
		audio_settings.setChannelCount(1);
		audio_settings.setByteOrder(QAudioFormat::LittleEndian);
		//格式支持判断,若不支持则选择相近格式
		if (!output_Device.isFormatSupported(audio_settings))
			output_Device.nearestFormat(audio_settings);
		//开始录音和监听
		audio_in_mic = new QAudioInput(input_Device_mic, audio_settings, this);
		audio_in_sys = new QAudioInput(input_Device_sys, audio_settings, this);
		audio_out = new QAudioOutput(output_Device, audio_settings, this);
		audio_in_mic->setBufferSize(100000);
		audio_in_sys->setBufferSize(100000);
		audio_out->setBufferSize(100000);
		audio_out_streamIn = audio_out->start();
	}
public://输入接口
	//摄像头捕获（捕获频率，是否开启）
	void cameraCapture(unsigned int freq, bool enable = true);
	//设计摄像头截图大小（宽度，高度）
	void cameraSizeSetting(unsigned int weight, unsigned int height);
	//音频捕获（是否开启麦克风，是否开启系统声音）
	void audioCapture(bool enable_mic = true, bool enable_sys = true);
	//播放音频（音频）
	void audioPlay(QByteArray data);

	//获取当前输入音频 —— 返回为当前可用设备列表中的编号
	int getInput();
	//获取当前输出音频 —— 返回为当前可用设备列表中的编号
	int getOutput();
	//获取可用输入设备 —— 返回当前可用设备列表名
	QList<QString> getInputList();
	//获取可以输出设备 —— 返回当前可用设备列表名
	QList<QString> getOutputList();
	//设置当前输入设备（可用设备列表中的编号）
	void setInput(int num);
	//设置当前输出设备（可用设备列表中的编号）
	void setOutput(int num);
	//获取当前输入设备音量 —— 返回值在 0-1
	double getInputVolume();
	//获取当前输入设备音量 —— 返回值在 0-1
	double getOutputVolume();
	//设置当前输入设备音量（音量（0-1））
	void setInputVolume(double volume);
	//设置当前输出设备音量（音量（0-1））
	void setOutputVolume(double volume);

private://用于接收信号
	//输出图片
	void processCapturedImage(int request_id, const QImage& img);
public://内部处理
	//视频截图
	void getCamera();
	//输出接口（消息槽）
signals:
	//输出摄像头截图（截图）
	void screenOut(const QImage& img);
signals:
	//输出音频（截图）
	void audioOut(QByteArray data);
};
#endif
