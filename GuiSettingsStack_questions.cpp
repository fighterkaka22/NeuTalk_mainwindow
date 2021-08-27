#include "GuiSettingsStack_questions.h"


GuiSettingsStack_questions::GuiSettingsStack_questions(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/question.png");
  setTitle("Settings");
  setSubTitle("questions");

  addTag("关于 NeuTalk ");
  addItem("版权：", "<font face = 'Microsoft YaHei' color = #323232>©2021 NeuTalk开发小组. 版权所有</font>", false);
  addItem("介绍：", "<font face = 'Microsoft YaHei' color = #323232>NeuTalk是一款<b>局域网</b>即时聊天软件，<br>用户<b>无需连接Internet</b>即可聊天。</font>",false);

  addTag("常见问题");
  addItem("无法聊天？", "<font face = 'Microsoft YaHei' color = #323232><p><b>1.</b> <font face = 'Microsoft YaHei' >检查您与好友的NeuTalk版本是否一致。</p>  <p><b>2.</b> 请与好友处于同一局域网。</p></font>");
//  central_layout->addSpacing(20);
  addItem("IP指示灯:", "<font face = 'Microsoft YaHei' color = #323232><p><b><font color=#39c828 >●</font> 在线</b></p></font>"
                           "<font face = 'Microsoft YaHei' color = #323232><p><b><font color=#ed403f>●</font> 离线</b> 暂时无法连接哦😂</p></font>"
                           "<font face = 'Microsoft YaHei' color = #323232><p><b><font color=#ffb500>●</font> 好友与您不在同一网段</b> 您和好友只能在同一局域网下聊天。</p></font>");
  this->setParent(parent);
}

GuiSettingsStack_questions::~GuiSettingsStack_questions()
{

}

