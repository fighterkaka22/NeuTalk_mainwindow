#ifndef THREADNET_H
#define THREADNET_H

#include "GlobalData.h"
#include "GlobalType.h"

#include <QThread>
#include <QHostInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QFile>
#include <QDate>
#include <QMutex>


class ThreadNet : public QThread
{
  Q_OBJECT
public:
  explicit ThreadNet(QObject *parent = 0);
  ~ThreadNet();

protected:
  void run();


private:
  enum BroadcastType{
    Message,
    UsrEnter,
    UsrLeave,
    FileTran,
    FileReject
  };

  ///Thread Tasks
  bool running = true;
  int loop_count = 1;
  void refreshLocalHostIP();
  void sendOnlineStatus();

  ///UDP Socket
  quint16 udp_port = 23232;
  QUdpSocket *udp_socket;
  void udpProcessMessage(MessageStruct *messageStruct);
  void udpProcessUsrEnter(UsrProfileStruct *usrProfileStruct);
  void udpProcessUsrLeft(QString *usrKey);
  // void udpProcessFileTran(const FileInfoStruct &fileInfoStruct);
  void udpProcessFileReject();

  void udpSendUsrEnter();
  void udpSendUsrLeave();
  void udpSendFileTran();
  void udpSendFileAccept();
  void TEST_udpsSendMessage(QString to, QString from, QString message);


  ///TCP Server
  qint16 tcp_port = 23232;
  QString file_name;
  QFile *local_file;

  QTcpServer *tcp_server;
  QTcpSocket *tcp_socket;

  void tcpInitServer();
  void tcpCloseConnection();


public slots:
  void udpSendMessage(QString usrKeyStr, QString message);
private slots:
  void udpProcessPendingDatagrams();

  void tcpSendData();



signals:
  void messageRecieved(MessageStruct *messageStruct, bool fromMe);
  void usrEnter(UsrProfileStruct *usrProfileStruct);
  void usrLeft(QString *usrKey);

};

#endif // THREADNET_H







