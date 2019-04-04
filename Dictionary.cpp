#include "Dictionary.h"

Dictionary::Dictionary()
{
	//10CM����ˮ��
	map.insert("watery010", "SoilVolume10");
	//20CM����ˮ��
	map.insert("watery020", "SoilVolume20");
	//30CM����ˮ��
	map.insert("watery030", "SoilVolume30");
	//40CM����ˮ��
	map.insert("watery040", "SoilVolume40");
	//50CM����ˮ��
	map.insert("watery050", "SoilVolume50");
	//60CM����ˮ��
	map.insert("watery060", "SoilVolume60");
	//80CM����ˮ��
	map.insert("watery080", "SoilVolume80");
	//100CM����ˮ��
	map.insert("watery100", "SoilVolume100");

	map.insert("waterf","");
}

Dictionary::~Dictionary()
{
}

QString Dictionary::Find(QString key)
{

	QMap<QString, QString>::const_iterator mi = map.find(key);
	if (mi != map.end())
		return map[key];
	return NULL;
}
