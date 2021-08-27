#ifndef GUIUSERINFO_H
#define GUIUSERINFO_H

#include <QApplication>
#include <QWidget>

namespace Ui {
class GuiUserInfo;
}

class GuiUserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GuiUserInfo(QWidget *parent = nullptr);
    ~GuiUserInfo();

private:
    Ui::GuiUserInfo *ui;
};

#endif // GUIUSERINFO_H
