#include "VideoC.h"



void VideoC::cameraCapture(unsigned int freq, bool enable)
{
	if (enable)
	{
		if (enable_camera)
		{
			camera_timer->stop();
			delete camera_timer;
		}
		else
		{
			camera.start();
		}
		camera_timer = new QTimer(this);
		connect(camera_timer, &QTimer::timeout, this, &VideoC::getCamera);
		camera_timer->start(1000 / freq);
	}
	else
	{
		if (enable_camera)
		{
			camera_timer->stop();
			delete camera_timer;
			camera_timer = NULL;
			camera.stop();
		}
	}
	freq_camera = freq;
	enable_camera = enable;
}


void VideoC::getCamera()
{
	imageCapture.capture();
}

void VideoC::processCapturedImage(int request_id, const QImage& img)
{
	emit screenOut(img.scaled(weight_camera, height_camera, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void VideoC::cameraSizeSetting(unsigned int weight, unsigned int height)
{
	weight_camera = weight;
	height_camera = height;
	//QImageEncoderSettings iamge_setting;
	//iamge_setting.setResolution(weight_camera, height_camera);
	//imageCapture.setEncodingSettings(iamge_setting);
}


void VideoC::audioCapture(bool enable_mic, bool enable_sys)
{
	if (enable_mic)
	{
		if (!enable_audio_mic)
		{
			audio_streamIn_mic = audio_in_mic->start(); //开始音频采集
			//关联音频读数据信号
			connect_mic = connect(audio_streamIn_mic, &QIODevice::readyRead, [=]() { emit audioOut(audio_streamIn_mic->readAll()); });
		}
	}
	else
	{
		if (enable_audio_mic)
		{
			disconnect(connect_mic);
			audio_in_mic->stop();
		}
	}
	enable_audio_mic = enable_mic;

	static QMetaObject::Connection temp_sys;//临时存放系统链接
	if (enable_sys)
	{
		if (!enable_audio_sys)
		{
			audio_streamIn_sys = audio_in_sys->start(); //开始音频采集
			//关联音频读数据信号
			temp_sys = connect(audio_streamIn_sys, &QIODevice::readyRead, [=]() {emit audioOut(audio_streamIn_sys->readAll()); });
		}
	}
	else
	{
		if (enable_audio_sys)
		{
			disconnect(temp_sys);
			audio_in_sys->stop();
		}
	}
	enable_audio_sys = enable_sys;
}

void VideoC::audioPlay(QByteArray data)
{
	audio_out_streamIn->write(data);
}

int VideoC::getInput()
{
	return input_number;
}

int VideoC::getOutput()
{
	return output_number;
}

QList<QString> VideoC::getInputList()
{
	QList<QString> temp;
	auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
	temp.append(QStringLiteral("系统默认"));
	foreach(auto & i, info)
	{
		temp.append(i.deviceName());
	}
	return temp;
}

QList<QString> VideoC::getOutputList()
{
	QList<QString> temp;
	auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
	temp.append(QStringLiteral("系统默认"));
	foreach(auto & i, info)
	{
		temp.append(i.deviceName());
	}
	return temp;
}

void VideoC::setInput(int num)
{
    input_number = num;
	QAudioDeviceInfo input_Device_mic; //麦克风音频输入设备
	if (num == 0)input_Device_mic = QAudioDeviceInfo::defaultInputDevice();
	else
	{
		auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
        input_Device_mic = info[num-1];
	}
	if (enable_audio_mic)
	{
		disconnect(connect_mic);
		audio_in_mic->stop();
		delete audio_in_mic;
		audio_in_mic = new QAudioInput(input_Device_mic, audio_settings, this);
        audio_in_mic->setBufferSize(100000);
		audio_streamIn_mic = audio_in_mic->start();
		connect_mic = connect(audio_streamIn_mic, &QIODevice::readyRead, [=]() {emit audioOut(audio_streamIn_mic->readAll()); });
	}
	else
	{
		delete audio_in_mic;
		audio_in_mic = new QAudioInput(input_Device_mic, audio_settings, this);
        audio_in_mic->setBufferSize(100000);
	}
}

void VideoC::setOutput(int num)
{
    output_number = num;
	QAudioDeviceInfo output_Device; //音频输出设备
	if (num == 0)output_Device = QAudioDeviceInfo::defaultOutputDevice();
	else
	{
		auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        qDebug()<<num <<' '<<info.count();
        output_Device = info[num -1];
	}
	audio_out->stop();
	delete audio_out;
	audio_out = new QAudioOutput(output_Device, audio_settings, this);
    audio_out->setBufferSize(100000);
	audio_out_streamIn = audio_out->start();
}

double VideoC::getInputVolume()
{
	return audio_in_mic->volume();
}

double VideoC::getOutputVolume()
{
	return audio_out->volume();
}

void VideoC::setInputVolume(double volume)
{
	audio_in_mic->setVolume(volume);
}

void VideoC::setOutputVolume(double volume)
{
	audio_out->setVolume(volume);
}
