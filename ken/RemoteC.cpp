#include "RemoteC.h"

void RemoteC::timerEvent(QTimerEvent* event)
{

}



void RemoteC::screenshotsCapture(unsigned int freq, bool enable)
{
	if (enable)
	{
		if (enable_screenshots)
		{
			screen_timer->stop();
			delete screen_timer;
		}
		screen_timer = new QTimer(this);
		connect(screen_timer, &QTimer::timeout, this, &RemoteC::slotGrabFullScreen);
		screen_timer->start(1000 / freq);
	}
	else
	{
		if (enable_screenshots)
		{
			screen_timer->stop();
			delete screen_timer;
			screen_timer = NULL;
		}
	}
	freq_screenshots = freq;
	enable_screenshots = enable;


}

void RemoteC::boardCapture(bool enable)
{
	static QMetaObject::Connection dis;//剪切链接

	if (enable)
	{
		if (!enable_board)
		{
			dis = connect(board, &QClipboard::dataChanged, this, &RemoteC::boardDataChanged, Qt::DirectConnection);
		}
	}
	else
	{
		if (enable_board)
		{
			disconnect(dis);
		}
	}
	enable_board = enable;

}

void RemoteC::boardChange(QString content)
{
	if (board->text() != content)
	{
		board->setText(content);
	}
}

void RemoteC::boardDataChanged()
{
	emit boardOut(board->text());
}

void RemoteC::commandCapture(bool enable)
{
	enable_command = enable;
	if (enable)
	{
		if (!cmd)
		{
			cmd = new QProcess(this);
			connect(cmd, &QProcess::readyReadStandardOutput, this, &RemoteC::onReadoutput);
			connect(cmd, &QProcess::readyReadStandardError, this, &RemoteC::onReaderror);
			cmd->start("cmd");             //启动终端(内容为终端名字)
			cmd->waitForStarted();        //等待启动完成
		}
	}
	else
	{
		if (cmd)
		{
			cmd->close();
			cmd->waitForFinished();
			delete cmd;
			cmd = NULL;
		}
	}
}
void RemoteC::executeCommand(QString command)
{
	command += '\n';
	cmd->write(command.toLocal8Bit());
}
void RemoteC::onReadoutput()
{
	emit commandOut(QString::fromLocal8Bit(cmd->readAllStandardOutput()));
}
void RemoteC::onReaderror()
{
	emit commandOut(QString::fromLocal8Bit(cmd->readAllStandardError()));
}

void RemoteC::mouseMove(double x, double y)
{
	//获取设备屏幕大小
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	QPoint pt;
	pt.setX(int(x * screenRect.width()));
	pt.setY(int(y * screenRect.height()));

	QCursor::setPos(pt);
}
void RemoteC::mouseClicked(int keyValue, bool down)
{
	mouse_event(getMouseValue(keyValue, down), 0, 0, 0, 0);
}
void RemoteC::keyEvent(int keyValue, bool down)
{
    if(down)keybd_event(getKeyValue(keyValue), 0, 0, 0);
    else keybd_event(getKeyValue(keyValue), 0, KEYEVENTF_KEYUP, 0);
}
void RemoteC::wheelEvent(int delta)
{
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, delta, 0);
}
int RemoteC::getKeyValue(int keyValue)
{
	//对于特殊意义的键值[event->key()的值无法用ASCII码表示]
	switch (keyValue)
	{
	case Qt::Key_Escape:
		keyValue = VK_ESCAPE;
		break;
	case Qt::Key_Tab:
		keyValue = VK_TAB;
		break;
	case Qt::Key_CapsLock:
		keyValue = VK_CAPITAL;
		break;
	case Qt::Key_Shift:
		keyValue = VK_SHIFT;
		break;
	case Qt::Key_Control:
		keyValue = VK_CONTROL;
		break;
	case Qt::Key_Alt:
		keyValue = VK_MENU;
		break;
	case Qt::Key_Backspace:
        keyValue = VK_BACK;
		break;
	case Qt::Key_Meta:
		//特别按键
		keyValue = VK_LWIN;
		break;
	case Qt::Key_Return:
		//特别按键
		keyValue = VK_RETURN;
		break;
	case Qt::Key_Enter:
		keyValue = VK_RETURN;
		break;
	case Qt::Key_Home:
		keyValue = VK_HOME;
		break;
	case Qt::Key_End:
		keyValue = VK_END;
		break;
	case Qt::Key_PageUp:
		keyValue = VK_PRIOR;
		break;
	case Qt::Key_PageDown:
		keyValue = VK_NEXT;
		break;
	case Qt::Key_Insert:
		keyValue = VK_INSERT;
		break;
	case Qt::Key_Up:
		keyValue = VK_UP;
		break;
	case Qt::Key_Right:
		keyValue = VK_RIGHT;
		break;
	case Qt::Key_Left:
		keyValue = VK_LEFT;
		break;
	case Qt::Key_Down:
		keyValue = VK_DOWN;
		break;
	case Qt::Key_Delete:
		keyValue = VK_DELETE;
		break;
	case Qt::Key_Space:
		keyValue = VK_SPACE;
		break;
	case Qt::Key_F1:
		keyValue = VK_F1;
		break;
	case Qt::Key_F2:
		keyValue = VK_F2;
		break;
	case Qt::Key_F3:
		keyValue = VK_F3;
		break;
	case Qt::Key_F4:
		keyValue = VK_F4;
		break;
	case Qt::Key_F5:
		keyValue = VK_F5;
		break;
	case Qt::Key_F6:
		keyValue = VK_F6;
		break;
	case Qt::Key_F7:
		keyValue = VK_F7;
		break;
	case Qt::Key_F8:
		keyValue = VK_F8;
		break;
	case Qt::Key_F9:
		keyValue = VK_F9;
		break;
	case Qt::Key_F10:
		keyValue = VK_F10;
		break;
	case Qt::Key_F11:
		keyValue = VK_F11;
		break;
	case Qt::Key_F12:
		keyValue = VK_F12;
		break;
	case Qt::Key_NumLock:
		keyValue = VK_NUMLOCK;
		break;
	case Qt::Key_ScrollLock:
		keyValue = VK_SCROLL;
		break;
	case Qt::Key_Pause:
		keyValue = VK_PAUSE;
		break;
	}




	return keyValue;

}
int RemoteC::getMouseValue(int keyValue, bool down)
{
	switch (keyValue)
	{
	case Qt::LeftButton:
		if (down)keyValue = MOUSEEVENTF_LEFTDOWN; else keyValue = MOUSEEVENTF_LEFTUP;
		break;
	case Qt::MiddleButton:
		if (down)keyValue = MOUSEEVENTF_MIDDLEDOWN; else keyValue = MOUSEEVENTF_MIDDLEUP;
		break;
	case Qt::RightButton:
		if (down)keyValue = MOUSEEVENTF_RIGHTDOWN; else keyValue = MOUSEEVENTF_RIGHTUP;
		break;
	default:
		break;
	}
	return keyValue;
}

void RemoteC::setScreenSize(int Weight, int Height)
{
	screen_weight = Weight;
	screen_height = Height;
}

void RemoteC::slotGrabFullScreen()
{
	QScreen* screen = QGuiApplication::primaryScreen();
	emit screenOut(screen->grabWindow(0).toImage().scaled(screen_weight, screen_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
