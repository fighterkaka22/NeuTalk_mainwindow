#include "GlobalData.h"



///UI
QFont GlobalData::font_main;
QFont GlobalData::font_chatTextEditor;
QFont GlobalData::font_chatBubble;
QFont GlobalData::font_combWidgetUsrName;
QFont GlobalData::font_combWidgetIpAddr;
QFont GlobalData::font_menuButton;
QFont GlobalData::font_scrollStackTitle;
QFont GlobalData::font_scrollStackSubtitle;

QColor GlobalData::bc_darkGrey = QColor(100,100,100);
QColor GlobalData::bc_lightGrey = QColor(225,225,225);
QColor GlobalData::bc_brown = QColor(103,72,0);
QColor GlobalData::bc_hiveYellow = QColor(255,181,0);
QColor GlobalData::bc_lightYellow = QColor(255,215,126);
    //New colors
QColor GlobalData::bc_white = QColor(237,242,246);
QColor GlobalData::bc_veryLightGrey = QColor(237,242,246);
QColor GlobalData::bc_veryDarkBlue = QColor(29,35,42);
QColor GlobalData::bc_darkBlue = QColor(40,46,54);
QColor GlobalData::bc_lightBlue = QColor(0,132,255);

QColor GlobalData::color_window = QColor(29,35,42);
QColor GlobalData::color_alphaTab = QColor(29,35,42);
QColor GlobalData::color_tab = QColor(40,46,54);

QColor GlobalData::color_defaultChatBubbleI = GlobalData::bc_white;
QColor GlobalData::color_defaultChatBubbleO = GlobalData::bc_lightBlue;

QPalette GlobalData::palette_bkg_normalWhite;
QPalette GlobalData::palette_bkg_transparent;
QPalette GlobalData::palette_txt_brown;


///data
char GlobalData::g_version[3] = {'0','0','6'};
Settings::SettingStruct GlobalData::g_settings_struct;
QMap<QString, UsrProfileStruct> GlobalData::saved_usr_profile_map;
QMap<QString, UsrProfileStruct> GlobalData::online_usr_profile_map;

QMap<QString, UsrData*> GlobalData::online_usr_data_map;//used

///netr
QString GlobalData::g_localHostIP;

QString GlobalData::g_currentTime()
{
  return QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
}

void GlobalData::TEST_printUsrProfileStruct(const UsrProfileStruct &usrProfileStruct, const QString &str)
{
  qDebug()<<endl<<"Test by "<<str;
  qDebug()<<usrProfileStruct.key_str;
  qDebug()<<usrProfileStruct.name_str;
  qDebug()<<usrProfileStruct.ip_str;
  qDebug()<<usrProfileStruct.avatar_str<<endl;

}


