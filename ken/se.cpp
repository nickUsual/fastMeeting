#include "se.h"
void Kernel::init()
{
	//网络
	connect(&net, &netmanage::signal_recvmsg, this, &Kernel::getData);
	connect(&net, &netmanage::result_link, this, &Kernel::loginResult);
	connect(&net, &netmanage::signal_dislink, this, &Kernel::ondislink);
	connect(&net, &netmanage::client_change, this, &Kernel::userChange);
	connect(&net, &netmanage::failed_send, this, &Kernel::sendFailed);
    connect(&net, &netmanage::get_userlist, this, &Kernel::get_userlist);
	//视频
	connect(&video, &VideoC::screenOut, this, &Kernel::getCamera);
	connect(&video, &VideoC::audioOut, this, &Kernel::getAudio);
	//远控
	connect(&remote, &RemoteC::commandOut, this, &Kernel::getCommandOut);
	connect(&remote, &RemoteC::boardOut, this, &Kernel::getBoard);
	connect(&remote, &RemoteC::screenOut, this, &Kernel::getScreen);
}



void Kernel::getData(UserId id, MsgType type, QByteArray data)
{
    QImage img;//图
	double x, y;//坐标
	int keyValue;//键值
	bool down;//是否按下
	bool enable;//是否开启
	switch (type)
	{
	case MsgType::MSG:
		emit recv_msg(id, QString::fromLocal8Bit(data));
		break;
	case MsgType::GROUNP_MSG:
		emit recv_msg_all(id, QString::fromLocal8Bit(data));
		break;
	case MsgType::CAMERA:
		img.loadFromData(data, "JPEG");
		emit recv_video(id, img);
		break;
	case MsgType::CAMERA_ENABLE:
		memcpy(&enable, data.data(), sizeof(enable));
		emit video_change(id, enable);
		break;
	case MsgType::AUDIO:
		if (audio_play_enable)video.audioPlay(data);
		break;
	case MsgType::MIC_ENABLE:
		memcpy(&enable, data.data(), sizeof(enable));
		emit mic_change(id, enable);
        break;
	case MsgType::SCREEN:
		img.loadFromData(data, "PNG");
		emit recv_desktop(id, img);
		break;
	case MsgType::SCREEN_PRI:
		img.loadFromData(data, "PNG");
		emit recv_desktop_pri(id, img);
		break;
	case MsgType::SCREEN_ENABLE:
		memcpy(&enable, data.data(), sizeof(enable));
		emit screen_change(id, enable);
		break;
	case MsgType::BOARD:
		if (remoteId == id)remote.boardChange(data);
		break;
	case MsgType::COMMANDOUT:
		if (remoteId == id)remote.executeCommand(data);
		break;
	case MsgType::ASK_CONTRAL:
		if (remoteId == -1)emit recv_control(id);
		break;
	case MsgType::ASK_CONTRALLED:
		if (remoteId == -1)emit recv_controlled(id);
		break;
	case MsgType::ACK_CONTRAL:
		if (remoteId == -1 && remoteId_pre == id)
		{
			memcpy(&enable, data.data(), sizeof(enable));
			remoteId_pre = -1;
			emit ok_control(id, enable);
			if (enable)
			{
				remote.boardCapture();
				remoteId = id;
			}
		}
		break;
	case MsgType::ACK_CONTRALLED:
		if (remoteId == -1 && remoteId_pre == id)
		{
			memcpy(&enable, data.data(), sizeof(enable));
			remoteId_pre = -1;
			emit ok_controlled(id, enable);
			if (enable)
			{
				remote.boardCapture();
				remoteId = id;
				is_remoted = true;
			}
		}
		break;
	case MsgType::MOUSE_MOVE:
		if (id == remoteId && is_remoted)
		{
			memcpy(&x, data.data(), sizeof(x));
			memcpy(&y, data.data() + sizeof(x), sizeof(y));
			remote.mouseMove(x, y);
		}
		break;
	case MsgType::MOUSE_CLICK:
		if (id == remoteId && is_remoted)
		{
			memcpy(&keyValue, data.data(), sizeof(keyValue));
			memcpy(&down, data.data() + sizeof(keyValue), sizeof(down));
			remote.mouseClicked(keyValue, down);
		}
		break;
	case MsgType::KEY_CLICK:
		if (id == remoteId && is_remoted)
		{
			memcpy(&keyValue, data.data(), sizeof(keyValue));
			memcpy(&down, data.data() + sizeof(keyValue), sizeof(down));
			remote.keyEvent(keyValue, down);
		}
		break;
	case MsgType::STARTCOMMAND:
		if (id == remoteId && is_remoted)
		{
			memcpy(&enable, data.data(), sizeof(enable));
			remote.commandCapture(enable);
		}
		break;
	case MsgType::COMMAND:
		if (id == remoteId && is_remoted)
		{
			remote.executeCommand(data);
		}
		break;
	case MsgType::DISCONTRAL:
		if (id == remoteId)
		{
			remoteId = 0;
			is_remoted = false;
			emit remote_disconnect();
			remote.boardCapture(false);
		}
		break;
	default:
		break;
	}
}

void Kernel::loginResult(LOGIN_RESULT result)
{

	emit login_result(result);
}

void Kernel::ondislink()
{
	emit server_dislink();
}

void Kernel::userChange(UserId id, ClientChange state)
{
	if (id == remoteId)
	{
		remoteId = -1;
		is_remoted = false;
		emit remote_disconnect();
	}
	else if (id == remoteId_pre)
	{
		remoteId_pre = -1;
	}
	emit user_change(id, state);//(可能需要修改)
}

void Kernel::sendFailed()
{
	//暂不处理
}

void Kernel::login(QString name, QString password)
{
	net.login(name.toLocal8Bit(), password.toLocal8Bit());
}

void Kernel::dislink()
{
	net.dislink();
}

QString Kernel::get_name(UserId id)
{
	return QString::fromLocal8Bit(net.get_name(id));
}

bool Kernel::get_camera(UserId id)
{
	return net.get_camera(id);
}

bool Kernel::get_mic(UserId id)
{
	return net.get_mic(id);
}

bool Kernel::get_screen(UserId id)
{
	return net.get_screen(id);
}

QList<UserId> Kernel::get_user()
{
	return net.get_user();
}

void Kernel::send_msg(UserId id, QString msg)
{
	if (id == GROUP)
	{
		net.send_msg(id, MsgType::GROUNP_MSG, msg.toLocal8Bit());
	}
	else
	{
		net.send_msg(id, MsgType::MSG, msg.toLocal8Bit());
	}

}

void Kernel::getCamera(const QImage& img)
{
	QByteArray arr;
	QBuffer buffer(&arr);
	buffer.open(QIODevice::WriteOnly);
	img.save(&buffer, "JPEG");
	net.send_msg(GROUP, MsgType::CAMERA, arr);
	emit get_video(img);
}

void Kernel::getAudio(QByteArray data)
{
	net.send_msg(GROUP, MsgType::AUDIO, data);
}

void Kernel::enable_camera(bool enable)
{
	QByteArray data;
	data.append(enable);
	net.send_server(mationType::enable_camera, data);
	net.send_msg(GROUP, MsgType::CAMERA_ENABLE, data);
	video.cameraCapture(30, enable);
}

void Kernel::enable_mic(bool enable)
{
	QByteArray data;
	data.append(enable);
	net.send_server(mationType::enable_mic, data);
	net.send_msg(GROUP, MsgType::MIC_ENABLE, data);
	mic_enable = enable;
	video.audioCapture(enable, sys_enable);
}

void Kernel::enable_sys(bool enable)
{
	sys_enable = enable;
	video.audioCapture(mic_enable, enable);
}


void Kernel::enable_audio(bool enable)
{
	audio_play_enable = enable;
}

int Kernel::get_input()
{
	return video.getInput();
}

int Kernel::get_outout()
{
	return video.getOutput();
}

QList<QString> Kernel::get_input_list()
{
	return video.getInputList();
}

QList<QString> Kernel::get_output_list()
{
	return video.getOutputList();
}

void Kernel::set_input(int num)
{
	video.setInput(num);
}

void Kernel::set_output(int num)
{
	video.setOutput(num);
}

double Kernel::get_input_volume()
{
	return video.getInputVolume();
}

double Kernel::get_output_volume()
{
	return video.getOutputVolume();
}

void Kernel::set_input_volume(double volume)
{
	return video.setInputVolume(volume);
}

void Kernel::set_output_volume(double volume)
{
	return video.setOutputVolume(volume);
}



void Kernel::getScreen(const QImage& img)
{
	QByteArray arr;
	QBuffer buffer(&arr);
	buffer.open(QIODevice::WriteOnly);
	img.save(&buffer, "PNG");
	if (screen)net.send_msg(GROUP, MsgType::SCREEN, arr);
	if (screen_pri && remoteId != -1)net.send_msg(remoteId, MsgType::SCREEN_PRI, arr);
}

void Kernel::getBoard(QString data)
{
	net.send_msg(remoteId, MsgType::BOARD, data.toLocal8Bit());
}

void Kernel::getCommandOut(QString info)
{
	net.send_msg(remoteId, MsgType::COMMANDOUT, info.toLocal8Bit());
}

void Kernel::start_show(bool enable)
{
	screen = enable;
	QByteArray data;
	data.append(enable);
	net.send_server(mationType::enable_camera, data);
	net.send_msg(GROUP, MsgType::SCREEN_ENABLE, data);
	remote.screenshotsCapture(display_freq, screen || screen_pri);
}
void  Kernel::start_show_pri(bool enable)
{
	screen_pri = enable;
	remote.screenshotsCapture(display_freq, screen || screen_pri);
}
void Kernel::ask_control(UserId id)
{
	if (remoteId == -1 && remoteId_pre == -1)
	{
		net.send_msg(id, MsgType::ASK_CONTRAL, NULLBYTE);
		remoteId_pre = id;
	}
}

void Kernel::ask_controlled(UserId id)
{
	if (remoteId == -1 && remoteId_pre == -1)
	{
		net.send_msg(id, MsgType::ASK_CONTRALLED, NULLBYTE);
		remoteId_pre = id;
	}
}

void Kernel::accept_control(UserId id, bool accept)
{
	if (remoteId != -1)accept = false;
	QByteArray data;
	data.append(accept);
	net.send_msg(id, MsgType::ACK_CONTRAL, data);
	remoteId = id;
	is_remoted = true;
	remote.boardCapture();
}

void Kernel::accept_controlled(UserId id, bool accept)
{
	if (remoteId != -1)accept = false;
	QByteArray data;
	data.append(accept);
	net.send_msg(id, MsgType::ACK_CONTRALLED, data);
	remoteId = id;
	remote.boardCapture();
}

void Kernel::remote_mouse_move(double x, double y)
{
	if (remoteId == -1)return;
	QByteArray data;
	double current[2] = { x, y };
	data.resize(sizeof(current));
	memcpy(data.data(), current, sizeof(current));
	net.send_msg(remoteId, MsgType::MOUSE_MOVE, data);
}

void Kernel::remote_mouse_cliked(int keyValue, bool down)
{
	if (remoteId == -1)return;
	QByteArray data;
	data.resize(sizeof(keyValue) + sizeof(down));
	memcpy(data.data(), &keyValue, sizeof(keyValue));
	memcpy(data.data() + sizeof(keyValue), &down, sizeof(down));
	net.send_msg(remoteId, MsgType::MOUSE_CLICK, data);
}

void Kernel::remote_key(int keyValue, bool down)
{
	if (remoteId == -1)return;
	QByteArray data;
	data.resize(sizeof(keyValue) + sizeof(down));
	memcpy(data.data(), &keyValue, sizeof(keyValue));
	memcpy(data.data() + sizeof(keyValue), &down, sizeof(down));
	net.send_msg(remoteId, MsgType::KEY_CLICK, data);
}

void Kernel::remote_start_command(bool enable)
{
	if (remoteId == -1)return;
	QByteArray data;
	data.append(enable);
	net.send_msg(remoteId, MsgType::STARTCOMMAND, data);
}

void Kernel::remote_run_command(QString command)
{
	if (remoteId == -1)return;
	net.send_msg(remoteId, MsgType::COMMAND, command.toLocal8Bit());
}

void Kernel::disconnect_control()
{
	if (remoteId == -1)return;
	net.send_msg(remoteId, MsgType::DISCONTRAL, NULLBYTE);
	remoteId = 0;
	is_remoted = false;
	remote.boardCapture(false);
}

