#include "GuiCentralWidget.h"
//主窗口
GuiCentralWidget::GuiCentralWidget(QWidget *parent) : QWidget(parent)
{
  initAction();
  initTrayIcon();
//! do not delete yet, see if it causes problems.
//  QPalette palette;
//  palette.setColor(QPalette::Window, QColor(250,250,250));
//  this->setPalette(palette);

  this->setMinimumHeight(500);
  this->setMinimumWidth(800);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowTitle(QString("NeuTalk"));

  ////Gui
  gui_tab_block = new GuiTabBlock(this);
  gui_main_block = new GuiMainBlock(this);

  //左边栏的横竖两条分割线
  QFrame *line = new QFrame(this);
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Plain);
  line->setFixedWidth(1);
  line->setStyleSheet ("QFrame{  background: #646464; border: transparent;  }");

  //main_layout
  main_layout = new QHBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(gui_tab_block);
  main_layout->addWidget(line);
  main_layout->addWidget(gui_main_block);

  //connect

  connect(gui_tab_block->gui_chat_tab->comb_scroll_widget, SIGNAL(combWidgetClicked(const QString&)), this, SLOT(onCombWidgetClicked(QString)));

  ///buttons~~
  connect(gui_tab_block->gui_home_tab->welcome_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_home_tab->list_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_home_tab->storage_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));


  connect(gui_tab_block->gui_settings_tab->messaging_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_settings_tab->profile_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));
  connect(gui_tab_block->gui_settings_tab->questions_btn, SIGNAL(clicked(StaticStackType)), gui_main_block, SLOT(displayStaticStack(StaticStackType)));



}

GuiCentralWidget::~GuiCentralWidget()
{
  qDebug()<<"\n@NeuTalk UI is destructed";
}

void GuiCentralWidget::initAction()
{
  hide_action = new QAction(tr("&Hide"), this);
  connect(hide_action, &QAction::triggered, this, &QWidget::hide);

  show_action = new QAction(tr("&Show"), this);
  connect(show_action, &QAction::triggered, this, &QWidget::showNormal);

  quit_action = new QAction(tr("&Quit"), this);
  connect(quit_action, &QAction::triggered, qApp, &QCoreApplication::quit);
}

//小心！这里有一张用不上的蜜蜂图案
void GuiCentralWidget::initTrayIcon()
{
  tray_icon_menu = new QMenu(this);
  tray_icon_menu->addAction(hide_action);
  tray_icon_menu->addAction(show_action);
  tray_icon_menu->addSeparator();
  tray_icon_menu->addAction(quit_action);

//  QPixmap pixmap(":/img/img/icon.png");
  QIcon icon(":/img/img/tray_0.png");

  tray_icon = new QSystemTrayIcon(this);
  tray_icon->setIcon(icon);
  tray_icon->setToolTip("NeuTalk!");
  tray_icon->setContextMenu(tray_icon_menu);
  tray_icon->setVisible(true);
  tray_icon->show();
}

void GuiCentralWidget::onCombWidgetClicked(const QString &usrKey)
{
  gui_main_block->displayChatStack(usrKey);
  gui_tab_block->gui_chat_tab->comb_scroll_widget->setBadgeNumber(usrKey, 0);

}

void GuiCentralWidget::onMessageReceived(const MessageStruct &messageStruct, const bool &fromMe)
{
  if(fromMe)
    {
      gui_main_block->gui_chat_stack->refreshMessage(messageStruct.reciever_key);
    }
  else
    {
      //if not displaying the usr
      if(!gui_main_block->gui_chat_stack->refreshMessage(messageStruct.sender_key))
        {
          UsrData *temp_usr_data = GlobalData::online_usr_data_map.value(messageStruct.sender_key);
          gui_tab_block->gui_chat_tab->comb_scroll_widget->setBadgeNumber(messageStruct.sender_key, temp_usr_data->unreadMessageNumber());
          tray_icon->showMessage(temp_usr_data->name(), messageStruct.message_str);
        }
    }
}


void GuiCentralWidget::addUsr(UsrData *userData)
{
  gui_tab_block->gui_chat_tab->comb_scroll_widget->addComb(userData->usrProfileStruct());
  gui_main_block->gui_home_stack_list->addUsr(userData->usrProfileStruct());
}

void GuiCentralWidget::delUsr(UsrData *userData)
{

}

void GuiCentralWidget::changeUsr(UsrData *userData)
{
  gui_tab_block->gui_chat_tab->comb_scroll_widget->refreshComb(userData->usrProfileStruct());
  gui_main_block->gui_chat_stack->refreshProfile(userData->key());
  gui_main_block->gui_home_stack_list->refreshUsrProfile(userData->usrProfileStruct());
  //these will be eliminated
  //  gui_main_block->gui_chat_stack_map.value(usrProfileStruct->key_str)->refreshUsrProfile(usrProfileStruct);<<
}

void GuiCentralWidget::refreshUI()
{
  gui_main_block->gui_home_stack_welcome->refreshUI();
}

