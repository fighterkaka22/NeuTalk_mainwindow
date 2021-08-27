#include "GuiChatStack.h"
#include "guiuserinfo.h"
GuiUserInfo *user_info;


GuiChatStack_chat_widget::GuiChatStack_chat_widget(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, QColor(237,242,246));
  this->setPalette(palette);

  chat_bubble_layout = new QVBoxLayout();
  chat_bubble_layout->setAlignment(Qt::AlignTop);
  chat_bubble_layout->addStretch();
  chat_bubble_layout->setContentsMargins(5,30,5,30);

  ///lines
  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(2);
  top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(4);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setSpacing(5);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->addWidget(top_line);
  main_layout->addLayout(chat_bubble_layout);
  main_layout->addWidget(bottom_line);


}

GuiChatStack_chat_widget::~GuiChatStack_chat_widget()
{

}

void GuiChatStack_chat_widget::clearChatBubbles()
{
  foreach (GuiChatBubble *temp_chat_bubble_pointer, chat_bubble_list)
    {
      if(temp_chat_bubble_pointer != nullptr)
        {
          temp_chat_bubble_pointer->deleteLater();
        }
      chat_bubble_list.removeOne(temp_chat_bubble_pointer);
    }
}

void GuiChatStack_chat_widget::addChatBubble(const QString &message, const bool &fromMe)
{
  gui_chat_bubble = new GuiChatBubble(message, !fromMe, this);
  chat_bubble_list.append(gui_chat_bubble);

  chat_bubble_layout->addWidget(gui_chat_bubble);
}

//////////////////////////bottom//////////////////////////////////////

GuiChatStack_message_editor::GuiChatStack_message_editor(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  text_editor = new GuiTextEdit(this);
  text_editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  text_editor->setFrameStyle(QFrame::NoFrame);
  text_editor->setFont(GlobalData::font_chatTextEditor);
  text_editor->installEventFilter(this);


  tool_layout = new QHBoxLayout();
  tool_layout->setAlignment(Qt::AlignLeft);
  tool_layout->setContentsMargins(0,5,5,5);
  tool_layout->setSpacing(15);

  edit_layout = new QVBoxLayout();
  edit_layout->setAlignment(Qt::AlignLeft);
  edit_layout->setContentsMargins(10,5,15,10);
  edit_layout->setSpacing(5);
  edit_layout->addLayout(tool_layout);
  edit_layout->addWidget(text_editor);

  ///send button
  send_btn = new GuiLabelButton(this);
  send_btn->setDefaultPixmap(":/img/img/send_button_0.png");
  send_btn->setHoveredPixmap(":/img/img/send_button_1.png");
  send_btn->setAlignment(Qt::AlignRight);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,20,0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);
  main_layout->addWidget(send_btn);


  this->setMaximumHeight(130);
}

GuiChatStack_message_editor::~GuiChatStack_message_editor()
{

}

// Event filter: capture QEvent outside the class
//   text_editor->installEventFilter(this);
bool GuiChatStack_message_editor::eventFilter(QObject *obj, QEvent *e)
{
  Q_ASSERT(obj == text_editor);
  if(e->type() == QEvent::KeyPress)
    {
      QKeyEvent *event = static_cast<QKeyEvent*>(e);
      if(event->key() == Qt::Key_Return)
        {
          if(event->modifiers() & Qt::ControlModifier)
            {
              control_pressed = true;
              text_editor->insertPlainText("\n");
            }
          else
            {
              control_pressed = false;
              send_btn->setHovered();
            }
          return true;
        }
    }
  if(e->type() == QEvent::KeyRelease)
    {
      QKeyEvent *event = static_cast<QKeyEvent*>(e);
      if (event->key() == Qt::Key_Return)
        {
          if(event->modifiers() & Qt::ControlModifier)
            {
              return true;
            }
          else
            {
              qDebug()<<"old key";
              emit sendTriggered();
              send_btn->setDefault();
              return true;
            }
        }
    }

    return false;
}





GuiTextEdit::GuiTextEdit(QWidget *parent)
{
  this->setParent(parent);
}

GuiTextEdit::~GuiTextEdit()
{

}


void GuiTextEdit::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();
}

void GuiTextEdit::dropEvent(QDropEvent *event)
{
  QList<QUrl> url_list = event->mimeData()->urls();
  if(url_list.isEmpty())
    {
      return;
    }

  if(url_list.count() > 15)
    {
      qDebug()<<"@GuiTextEdit::dropEvent: Too many files dropped";
      return;
    }

  foreach(QUrl url, url_list)
    {
      QString fileName = url.toLocalFile();
      if (fileName.isEmpty())
        {
          break;
        }
      qDebug()<<"@file dropped"<<fileName;
    }

}


GuiChatStack::GuiChatStack(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Profile);

  usr_data = new UsrData(this);//empty object


  chat_widget = new GuiChatStack_chat_widget(this);
  QPalette palette = scroll_area->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255,255));
  scroll_area->setPalette(palette);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(chat_widget);
  scroll_area->setFrameStyle(0);

  message_editor = new GuiChatStack_message_editor(this);


  ////main layout
  QVBoxLayout *central_layout = new QVBoxLayout(chat_widget);
  central_layout->setContentsMargins(0,0,0,0);
  central_layout->setAlignment(Qt::AlignBottom);
  central_layout->setMargin(0);
  central_layout->setSpacing(0);

  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(message_editor);

  connect(message_editor, SIGNAL(sendTriggered()), this, SLOT(onSendButtonClicked()));
  connect(message_editor->send_btn, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));
  connect(this->title_label, SIGNAL(clicked()), this, SLOT(on_Title_UserName_clicked()));

  this->setParent(parent);
}

GuiChatStack::~GuiChatStack()
{
  //  this->set
}

bool GuiChatStack::refreshProfile(const QString &usrKey)
{
  if(!this->isDisplaying(usrKey))
    {
      return false;
    }
  else
    {
      this->setIcon(usr_data->avatar());
      this->setTitle(usr_data->name());
      this->setSubTitle(usr_data->signature());
      return true;
    }
}

bool GuiChatStack::refreshMessage(const QString &usrKey)
{
  if(!this->isDisplaying(usrKey))
    {
      qDebug()<<"@GuiChatStack::refreshMessage: Message load request denied (different usr)...";
      return false;
    }
  else
    {
      this->flipUnreadMessage();
      return true;
    }
}

void GuiChatStack::setUsrData(UsrData *usrData)
{
  usr_data = usrData;
}

void GuiChatStack::display(const QString &usrKey)
{
  UsrData *temp_usr_data = GlobalData::online_usr_data_map.value(usrKey);

  if(*usr_data->usrProfileStruct() != *temp_usr_data->usrProfileStruct())
    {
      if(usr_data->key() != temp_usr_data->key())
        {
          this->setUsrData(temp_usr_data);
          this->flipLatestMessage(true);
          this->flipUnreadMessage();
        }

      this->setIcon(temp_usr_data->avatar());
      this->setTitle(temp_usr_data->name());
      this->setSubTitle(temp_usr_data->signature());


    }
}

bool GuiChatStack::isDisplaying(const QString &usrKey)
{
  return (usrKey == usr_data->key());
}

void GuiChatStack::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();

}

void GuiChatStack::dropEvent(QDropEvent *event)
{
  qDebug()<<"#GuiChatStack::dropEvent(): file entered.";
  QList<QUrl> urls = event->mimeData()->urls();
  if (urls.isEmpty())
    {
      return;
    }
  QString fileName = urls.first().toLocalFile();
  if (fileName.isEmpty())
    {
      return;
    }
}

void GuiChatStack::flipUnreadMessage()
{
  qDebug()<<"@GuiChatStack::flipUnreadMessage(): Chat stack is loading unread message...";
  if(usr_data->unreadMessageNumber() != 0)
    {
      QList<QJsonObject> *message_list = usr_data->retrieveUnreadMessage();
      foreach (QJsonObject history_json_obj, *message_list)
        {
          chat_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
          qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
        }
    }
  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);
}

void GuiChatStack::flipLatestMessage(const bool &clear)
{
  if(clear)
    {
      chat_widget->clearChatBubbles();
    }

  qDebug()<<"@GuiChatStack::flipLatestMessage(): Chat stack is loading history message...";
  QJsonArray message_json_array = *usr_data->flipLatest();
  int message_count = message_json_array.count();
  for(int i = 0; i < message_count; i++)
    {
      QJsonObject history_json_obj = message_json_array[i].toObject();

      chat_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
      qDebug()<<" | @GuiChatStack::refreshUI(): Message loaded...";
    }

  scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum());
}

void GuiChatStack::flipUpMessage(const bool &clear)
{
  if(clear)
    {
      chat_widget->clearChatBubbles();
    }
}

void GuiChatStack::flipDownMessage(const bool &clear)
{
  if(clear)
    {
      chat_widget->clearChatBubbles();
    }
}

void GuiChatStack::onSendButtonClicked()
{
 QString message_str = message_editor->text_editor->toPlainText();
 emit sendMessage(usr_data->key(), message_str);
 message_editor->text_editor->clear();
 scroll_area->verticalScrollBar()->setValue(scroll_area->verticalScrollBar()->maximum()+100);

}

void GuiChatStack::onKeyEnterTriggered(bool &pressed)
{
  qDebug()<<"enter key pressed";
  if(pressed)
    {
      message_editor->send_btn->setHovered();
    }
  else
    {
      message_editor->send_btn->setDefault();
      onSendButtonClicked();
    }
}

//添加的函数
void GuiChatStack::on_Title_UserName_clicked(){
    qDebug() << "user info";
    if(!user_info){
        user_info= new GuiUserInfo;
    }
    user_info -> show();
}