#ifndef SFYTH_H
#define SFYTH_H

#define SFYTHSHARED_EXPORT __declspec(dllexport)
#ifdef SFYTHSHARED_EXPORT
#else
#define SFYTHSHARED_EXPORT __declspec(dllimport)
#endif
#include<windows.h>
#include<QJsonObject>
#include"ControlUI.h"
#define SFYTH "7"
//返回值为22，表示是水肥一体化数据
EXTERN_C SFYTHSHARED_EXPORT LRESULT Char2Json(QString &buff, QJsonObject &json);
QString Convert2Time(QString strTime);
//获取业务号
EXTERN_C SFYTHSHARED_EXPORT int GetServiceTypeID();
//获取业务名称
EXTERN_C SFYTHSHARED_EXPORT QString GetServiceTypeName();
//获取版本号
EXTERN_C SFYTHSHARED_EXPORT QString GetVersionNo();
//获取端口号
EXTERN_C SFYTHSHARED_EXPORT int GetPort();

//调试窗体
EXTERN_C SFYTHSHARED_EXPORT void GetControlWidget(QString StationID, uint Socket, QWidget *parent);
//矫正时钟
EXTERN_C SFYTHSHARED_EXPORT void SetTime(QString StationID, uint Socket);
//显示返回值
EXTERN_C SFYTHSHARED_EXPORT void  SetValueToControlWidget(QStringList list);
//发送命令
EXTERN_C SFYTHSHARED_EXPORT void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID);
ControlUI *control_ui;//终端窗体
bool isActive = false;//判断终端窗体是否开启
#endif // SFYTH_H
