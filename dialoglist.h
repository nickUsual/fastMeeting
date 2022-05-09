#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QWidget>
#include "Widget.h"
#include "ExtendWight.h"
namespace Ui {
class DialogList;
}

class DialogList : public QWidget
{
    Q_OBJECT

public:
    explicit DialogList(QWidget *parent = nullptr);
    ~DialogList();
    void refrash();

private:
    Ui::DialogList *ui;
    QVector<bool> isShowList;

};

#endif // DIALOGLIST_H
