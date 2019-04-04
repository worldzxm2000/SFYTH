#include "sfyth.h"
#include"qdatetime.h"
#include"qfile.h"
#include"qtextstream.h"
#include"qjsondocument.h"
#include "qdebug.h"
#include "qcoreapplication.h"
#include"qdir.h"
#include"Dictionary.h"
#include<QDateTime>
//��ȡҵ���
int GetServiceTypeID()
{
	return 7;
}

//��ȡҵ������
QString GetServiceTypeName()
{
	QString name = QString::fromLocal8Bit("����ʩ�ʻ�");
	return name;
}
//��ȡ�˿ں�
int GetPort()
{
	return 27020;
}

//��ȡ�汾��
QString GetVersionNo()
{
	QString Version = QString::fromLocal8Bit("1.0");
	return Version;
}

//��������
LRESULT Char2Json(QString &buff, QJsonObject &json)
{ 

	int Count = 0;//���ݸ���
	int Current_P = buff.length();//��ǰ����ָ

    //������������
	for (int i = 0; i < buff.length() - 2; i++)
	{
		if (buff[i].toUpper() == 'I' && buff[i + 1].toUpper() == 'D'&&buff[i + 2] == ':')
		{
			Current_P = i;//ָ��ָ��֡ͷ
			for (int j = i + 3; j < buff.length(); j++)
			{
				if (buff[j] == ';')
				{
					Current_P = j ;//ָ���ƶ���֡β��һ���ַ�
					Count += 1;//���ݸ���
					QJsonObject SubJson;
					QString strBuff = buff.mid(i, j - i);
					//���ݡ��������ַ�����ֳɸ���Ҫ��
					QStringList strList = strBuff.split(",");
					QString StationID;
					//json���ݸ���
					int ListLen = strList.count();
					SubJson.insert("DataLength", 1);
					//�������� �۲�����
					SubJson.insert("DataType", 1);
					//ҵ��� 06ˮ��һ�廯
					SubJson.insert("ServiceTypeID", SFYTH);
					SubJson.insert("DataSourceID", 0);
					//ʱ��
					QDateTime current_date_time = QDateTime::currentDateTime();
					QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
					SubJson.insert("ObserveTime", current_date);
					//��ŷ�����
					int Num = 0;
					for (int i = 0; i < ListLen; i++)
					{
						QStringList KeyValue = strList.at(i).split(":");
						int len = KeyValue.count();
						if (len != 2)
							continue;
						QString Key = KeyValue.at(0);
						QString Value = KeyValue.at(1);
						//̨վ��
						if (Key.toLower().compare("id")==0)
						{
							SubJson.insert("StationID",Value);
							continue;
						}
						//��ŷ�ˮ����
						if (Key.contains("waterf"))
						{
							SubJson.insert("WaterVolum", Value.toFloat() / 100.0);
							continue;
						}
						//��ŷ�����
						if (Key.contains("dcf"))
						{
							QString DevModID;
							DevModID = Key.mid(3, Key.count()-3);
							SubJson.insert("DevModID"+QString::number(Num), DevModID);
							SubJson.insert("Status"+QString::number(Num), Value);
							Num++;
							continue;
						}
						//�絼��
						if (Key.contains("condu"))
						{
							SubJson.insert("EC", Value.toFloat());
							continue;
						}
						//����PH
						if (Key.contains("soilph"))
						{
							SubJson.insert("PH", Value.toFloat());
							continue;
						}
					}
					json.insert(QString::number(Count), SubJson);
					QDateTime current_date_time1 = QDateTime::currentDateTime();
					QString current_date1 = current_date_time1.toString("yyyy.MM.dd hh:mm:ss");
					QString current_day = current_date_time1.toString("yyyy-MM-dd");
					QString fileName = QCoreApplication::applicationDirPath() + "\\"+ QString::fromLocal8Bit("����ʩ�ʻ�") +"\\" + StationID + "\\" + current_day;
					QDir dir(fileName);
					if (!dir.exists())
						dir.mkpath(fileName);//�����༶Ŀ¼
					fileName += "\\data.txt";
					QFile file(fileName);
					QTextStream in(&file);
					in << current_date1 << "\r\n" << strBuff << "\r\n";
					file.close();
					i = j ;//��ǰѭ��
					break;
				}
			}
		}
		else if(buff[i].toUpper() == 'S' && buff[i + 1].toUpper() == 'N'&&buff[i + 2] == ':')
		{
			Current_P = i;//ָ��ָ��֡ͷ
			for (int j = i + 3; j < buff.length(); j++)
			{
				if (buff[j] == ';')
				{
					Current_P = j;//ָ���ƶ���֡β��һ���ַ�
					Count += 1;//���ݸ���
					QJsonObject Json;
					QJsonObject SubJson;
					QString strBuff = buff.mid(i, j - i + 1);
					//���ݡ��������ַ�����ֳɸ���Ҫ��
					QStringList strList = strBuff.split(",");
					QString StationID;
					//json���ݸ���
					int ListLen = strList.count();
					for (int i = 0; i < ListLen; i++)
					{
						QStringList KeyValue = strList.at(i).split(":");
						int len = KeyValue.count();
						if (len != 2)
							continue;
						QString Key = KeyValue.at(0);
						QString Value = KeyValue.at(1);
						//̨վ��
						if (Key.toLower().compare("sn") == 0)
						{
							Json.insert("StationID", Value);
							break;
						}
					}
					SubJson.insert("Count", 1);
					SubJson.insert("Params1", strBuff);
					Json.insert("DataType", 2);//�������� �۲�����
					Json.insert("ValueCount", 8);//����ֵ����
					Json.insert("Command", 80201);
					Json.insert("Parameter", SubJson);
					json.insert(QString::number(Count), Json);
					i = j ;//��ǰѭ��
					break;
				}
			}
		}
		else if (buff[i].toUpper() == 'Y'&& buff[i+1].toUpper()=='E'&&buff[i+2].toUpper()=='S')
		{
			Current_P = i;//ָ��ָ��֡ͷ
			for (int j = i + 3; j < buff.length(); j++)
			{
				if (buff[j] == ';')
				{
					Current_P = j;//ָ���ƶ���֡β��һ���ַ�
					Count += 1;//���ݸ���
					QJsonObject Json;
					QJsonObject SubJson;
					QString strBuff = buff.mid(i, j - i);
					//���ݡ��������ַ�����ֳɸ���Ҫ��
					QStringList strList = strBuff.split(",");
					QString StationID;
					//json���ݸ���
					int ListLen = strList.count();
					for (int i = 0; i < ListLen; i++)
					{
						QStringList KeyValue = strList.at(i).split(":");
						int len = KeyValue.count();
						if (len != 2)
							continue;
						QString Key = KeyValue.at(0);
						QString Value = KeyValue.at(1);
						//̨վ��
						if (Key.toLower().compare("id") == 0)
						{
							Json.insert("StationID", Value);
							break;
						}
					}
					SubJson.insert("Count", 1);
					SubJson.insert("Params1", "yes");
					Json.insert("DataType", 2);//�������� �۲�����
					Json.insert("ValueCount", 8);//����ֵ����
					Json.insert("Command", 80202);
					Json.insert("Parameter", SubJson);
					json.insert(QString::number(Count), Json);
					i = j;//��ǰѭ��
					break;
				}
			}
		}
	}
	json.insert("DataLength", Count);//JSON���ݸ���
	if (Current_P >= buff.length())//�жϵ�ǰָ��λ��
	{
		buff.clear();
	}//����ڴ�
	else
	{
		buff.remove(0, Current_P);
	}//��ʣ���ֽڴ��뻺��
	return 1;
}

//�ַ���ת�����ݿ�ʱ���ʽ
QString Convert2Time(QString strTime)
{
	QString tmp;
	tmp = "to_date('" + strTime.mid(0, 4) + "-" + strTime.mid(4, 2) + "-" + strTime.mid(6, 2) + " " + strTime.mid(8, 2) + ":" + strTime.mid(10, 2) + ":" + strTime.mid(12, 2) + "', 'yyyy-mm-dd hh24:mi:ss')";
	return tmp;
}

//���Դ���
void  GetControlWidget(QString StationID, uint Socket, QWidget* parent)
{

}
//����ʱ��
void SetTime(QString StationID, uint Socket)
{
}
//����ֵ����
void SetValueToControlWidget(QStringList list)
{
	
}

//��������
void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID)
{
	//�豸�ն�����
	QString Comm;
	switch (CommandType)
	{
	case 80201:case 80202:
		Comm = Params1;
		break;
	default:
		break;
	}
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}