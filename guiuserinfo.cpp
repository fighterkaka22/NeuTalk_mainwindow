#include "guiuserinfo.h"
#include "ui_guiuserinfo.h"

GuiUserInfo::GuiUserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiUserInfo)
{
    ui->setupUi(this);
}

GuiUserInfo::~GuiUserInfo()
{
    delete ui;
}
