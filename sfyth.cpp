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
//获取业务号
int GetServiceTypeID()
{
	return 7;
}

//获取业务名称
QString GetServiceTypeName()
{
	QString name = QString::fromLocal8Bit("智能施肥机");
	return name;
}
//获取端口号
int GetPort()
{
	return 27020;
}

//获取版本号
QString GetVersionNo()
{
	QString Version = QString::fromLocal8Bit("1.0");
	return Version;
}

//解析数据
LRESULT Char2Json(QString &buff, QJsonObject &json)
{ 

	int Count = 0;//数据个数
	int Current_P = buff.length();//当前数据指

    //遍历查找数据
	for (int i = 0; i < buff.length() - 2; i++)
	{
		if (buff[i].toUpper() == 'I' && buff[i + 1].toUpper() == 'D'&&buff[i + 2] == ':')
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 3; j < buff.length(); j++)
			{
				if (buff[j] == ';')
				{
					Current_P = j ;//指针移动到帧尾下一个字符
					Count += 1;//数据个数
					QJsonObject SubJson;
					QString strBuff = buff.mid(i, j - i);
					//根据“，”将字符串拆分成各个要素
					QStringList strList = strBuff.split(",");
					QString StationID;
					//json数据个数
					int ListLen = strList.count();
					SubJson.insert("DataLength", 1);
					//数据类型 观测数据
					SubJson.insert("DataType", 1);
					//业务号 06水肥一体化
					SubJson.insert("ServiceTypeID", SFYTH);
					SubJson.insert("DataSourceID", 0);
					//时间
					QDateTime current_date_time = QDateTime::currentDateTime();
					QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
					SubJson.insert("ObserveTime", current_date);
					//电磁阀个数
					int Num = 0;
					for (int i = 0; i < ListLen; i++)
					{
						QStringList KeyValue = strList.at(i).split(":");
						int len = KeyValue.count();
						if (len != 2)
							continue;
						QString Key = KeyValue.at(0);
						QString Value = KeyValue.at(1);
						//台站号
						if (Key.toLower().compare("id")==0)
						{
							SubJson.insert("StationID",Value);
							continue;
						}
						//电磁阀水流量
						if (Key.contains("waterf"))
						{
							SubJson.insert("WaterVolum", Value.toFloat() / 100.0);
							continue;
						}
						//电磁阀开关
						if (Key.contains("dcf"))
						{
							QString DevModID;
							DevModID = Key.mid(3, Key.count()-3);
							SubJson.insert("DevModID"+QString::number(Num), DevModID);
							SubJson.insert("Status"+QString::number(Num), Value);
							Num++;
							continue;
						}
						//电导率
						if (Key.contains("condu"))
						{
							SubJson.insert("EC", Value.toFloat());
							continue;
						}
						//土壤PH
						if (Key.contains("soilph"))
						{
							SubJson.insert("PH", Value.toFloat());
							continue;
						}
						//液位
						if (Key.contains("watdeep"))
						{
							SubJson.insert("waterlevel", Value.toFloat());
							continue;
						}
						//压力
						if (Key.contains("press"))
						{
							SubJson.insert("waterpres", Value.toFloat());
							continue;
						}
					}
					json.insert(QString::number(Count), SubJson);
					QDateTime current_date_time1 = QDateTime::currentDateTime();
					QString current_date1 = current_date_time1.toString("yyyy.MM.dd hh:mm:ss");
					QString current_day = current_date_time1.toString("yyyy-MM-dd");
					QString fileName = QCoreApplication::applicationDirPath() + "\\"+ QString::fromLocal8Bit("智能施肥机") +"\\" + StationID + "\\" + current_day;
					QDir dir(fileName);
					if (!dir.exists())
						dir.mkpath(fileName);//创建多级目录
					fileName += "\\data.txt";
					QFile file(fileName);
					file.open(QIODevice::ReadWrite | QIODevice::Append);
					QTextStream in(&file);
					in << current_date1 << "\r\n" << strBuff << "\r\n";
					file.close();
					i = j ;//当前循环
					break;
				}
			}
		}
		else if(buff[i].toUpper() == 'S' && buff[i + 1].toUpper() == 'N'&&buff[i + 2] == ':')
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 3; j < buff.length(); j++)
			{
				if (buff[j] == ';')
				{
					Current_P = j;//指针移动到帧尾下一个字符
					Count += 1;//数据个数
					QJsonObject Json;
					QJsonObject SubJson;
					QString strBuff = buff.mid(i, j - i + 1);
					//根据“，”将字符串拆分成各个要素
					QStringList strList = strBuff.split(",");
					QString StationID;
					//json数据个数
					int ListLen = strList.count();
					for (int i = 0; i < ListLen; i++)
					{
						QStringList KeyValue = strList.at(i).split(":");
						int len = KeyValue.count();
						if (len != 2)
							continue;
						QString Key = KeyValue.at(0);
						QString Value = KeyValue.at(1);
						//台站号
						if (Key.toLower().compare("sn") == 0)
						{
							Json.insert("StationID", Value);
							break;
						}
					}
					SubJson.insert("Count", 1);
					SubJson.insert("Params1", strBuff);
					Json.insert("DataType", 2);//数据类型 观测数据
					Json.insert("ValueCount", 8);//返回值个数
					Json.insert("Command", 80201);
					Json.insert("Parameter", SubJson);
					json.insert(QString::number(Count), Json);
					i = j ;//当前循环
					break;
				}
			}
		}
		else if (buff[i].toUpper() == 'Y'&& buff[i+1].toUpper()=='E'&&buff[i+2].toUpper()=='S')
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 3; j < buff.length(); j++)
			{
				if (buff[j] == ';')
				{
					Current_P = j;//指针移动到帧尾下一个字符
					Count += 1;//数据个数
					QJsonObject Json;
					QJsonObject SubJson;
					QString strBuff = buff.mid(i, j - i);
					//根据“，”将字符串拆分成各个要素
					QStringList strList = strBuff.split(",");
					QString StationID;
					//json数据个数
					int ListLen = strList.count();
					for (int i = 0; i < ListLen; i++)
					{
						QStringList KeyValue = strList.at(i).split(":");
						int len = KeyValue.count();
						if (len != 2)
							continue;
						QString Key = KeyValue.at(0);
						QString Value = KeyValue.at(1);
						//台站号
						if (Key.toLower().compare("id") == 0)
						{
							Json.insert("StationID", Value);
							break;
						}
					}
					SubJson.insert("Count", 1);
					SubJson.insert("Params1", "yes");
					Json.insert("DataType", 2);//数据类型 观测数据
					Json.insert("ValueCount", 8);//返回值个数
					Json.insert("Command", 80202);
					Json.insert("Parameter", SubJson);
					json.insert(QString::number(Count), Json);
					i = j;//当前循环
					break;
				}
			}
		}
	}
	json.insert("DataLength", Count);//JSON数据个数
	if (Current_P >= buff.length())//判断当前指针位置
	{
		buff.clear();
	}//清除内存
	else
	{
		buff.remove(0, Current_P);
	}//将剩余字节存入缓存
	return 1;
}

//字符串转成数据库时间格式
QString Convert2Time(QString strTime)
{
	QString tmp;
	tmp = "to_date('" + strTime.mid(0, 4) + "-" + strTime.mid(4, 2) + "-" + strTime.mid(6, 2) + " " + strTime.mid(8, 2) + ":" + strTime.mid(10, 2) + ":" + strTime.mid(12, 2) + "', 'yyyy-mm-dd hh24:mi:ss')";
	return tmp;
}

//调试窗体
void  GetControlWidget(QString StationID, uint Socket, QWidget* parent)
{

}
//矫正时钟
void SetTime(QString StationID, uint Socket)
{
}
//返回值反馈
void SetValueToControlWidget(QStringList list)
{
	
}

//发送命令
void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID)
{
	//设备终端命令
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
	int nn=::send(Socket, ch, len, 0);
	qDebug() << send << nn;
}