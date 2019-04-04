#include "Dictionary.h"

Dictionary::Dictionary()
{
	//10CM土壤水分
	map.insert("watery010", "SoilVolume10");
	//20CM土壤水分
	map.insert("watery020", "SoilVolume20");
	//30CM土壤水分
	map.insert("watery030", "SoilVolume30");
	//40CM土壤水分
	map.insert("watery040", "SoilVolume40");
	//50CM土壤水分
	map.insert("watery050", "SoilVolume50");
	//60CM土壤水分
	map.insert("watery060", "SoilVolume60");
	//80CM土壤水分
	map.insert("watery080", "SoilVolume80");
	//100CM土壤水分
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
