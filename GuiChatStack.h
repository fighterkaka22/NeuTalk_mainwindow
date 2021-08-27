#ifndef GUICHATSTACK_H
#define GUICHATSTACK_H

#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GuiChatBubble.h"
#include "GlobalData.h"
#include "UsrData.h"
#include "ThreadData.h"
#include "GuiScrollStack.h"

#include <QScrollBar>
#include <QScrollArea>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QJsonArray>

class GuiTextEdit;
class GuiChatStack_chat_widget;
class GuiChatStack_message_editor;
class GuiChatStack;
//class GuiChatStack_top_bar;
//class GuiChatStack_old;


class GuiTextEdit : public QTextEdit
{
  Q_OBJECT

public:
  explicit GuiTextEdit(QWidget *parent = 0);
  ~GuiTextEdit();

protected:
///Do not delete!
//  void keyPressEvent(QKeyEvent *e);
//  void keyReleaseEvent(QKeyEvent *e);
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

private:
  bool control_pressed = false;

signals:
  void keyEnterTriggered(bool pressed);
};


class GuiChatStack_chat_widget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_chat_widget(QWidget *parent = 0);
  ~GuiChatStack_chat_widget();

  void clearChatBubbles();

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *chat_bubble_layout;
  GuiChatBubble *gui_chat_bubble;

  QList<GuiChatBubble*> chat_bubble_list;

public slots:
  void addChatBubble(const QString &message, const bool &fromMe);

};

//////////////////////////bottom//////////////////////////////////////

class GuiChatStack_message_editor : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatStack_message_editor(QWidget *parent = 0);
  ~GuiChatStack_message_editor();

  GuiLabelButton *send_btn;
  GuiTextEdit *text_editor;

protected:
/// An old way to capture QEvent outside the class!
  bool eventFilter(QObject *obj, QEvent *e);

private:
  QVBoxLayout *edit_layout;
  QHBoxLayout *tool_layout;


  QHBoxLayout *main_layout;

  bool control_pressed = false;


signals:
  void sendTriggered();

};



class GuiChatStack : public GuiScrollStack
{
  Q_OBJECT

public:
  explicit GuiChatStack(QWidget *parent = 0);
  ~GuiChatStack();

  void setUsrData(UsrData *usrData);
  void display(const QString &usrKey);
  bool refreshProfile(const QString &usrKey);
  bool refreshMessage(const QString &usrKey);

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

  LayoutStyle layout_style = LayoutStyle::Profile;

private:
  //UI
  GuiChatStack_chat_widget *chat_widget;
  GuiChatStack_message_editor *message_editor;

  //Data
  UsrData *usr_data;

  //Function
  void flipUnreadMessage();
  void flipLatestMessage(const bool &clear);
  void flipUpMessage(const bool &clear);
  void flipDownMessage(const bool &clear);
  bool isDisplaying(const QString &usrKey);

public slots:
  void onSendButtonClicked();
  void onKeyEnterTriggered(bool &pressed);
  void on_Title_UserName_clicked();

signals:
  void sendMessage(QString usrKey, QString message);

};






#endif // GUICHATSTACK_H
