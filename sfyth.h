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
//����ֵΪ22����ʾ��ˮ��һ�廯����
EXTERN_C SFYTHSHARED_EXPORT LRESULT Char2Json(QString &buff, QJsonObject &json);
QString Convert2Time(QString strTime);
//��ȡҵ���
EXTERN_C SFYTHSHARED_EXPORT int GetServiceTypeID();
//��ȡҵ������
EXTERN_C SFYTHSHARED_EXPORT QString GetServiceTypeName();
//��ȡ�汾��
EXTERN_C SFYTHSHARED_EXPORT QString GetVersionNo();
//��ȡ�˿ں�
EXTERN_C SFYTHSHARED_EXPORT int GetPort();

//���Դ���
EXTERN_C SFYTHSHARED_EXPORT void GetControlWidget(QString StationID, uint Socket, QWidget *parent);
//����ʱ��
EXTERN_C SFYTHSHARED_EXPORT void SetTime(QString StationID, uint Socket);
//��ʾ����ֵ
EXTERN_C SFYTHSHARED_EXPORT void  SetValueToControlWidget(QStringList list);
//��������
EXTERN_C SFYTHSHARED_EXPORT void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID);
ControlUI *control_ui;//�ն˴���
bool isActive = false;//�ж��ն˴����Ƿ���
#endif // SFYTH_H
