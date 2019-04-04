#pragma once

#include <QObject>
#include<QMap>
class Dictionary : public QObject
{
	Q_OBJECT

public:
	Dictionary();
	QString Find(QString key);
protected:
	QMap<QString, QString> map;
};
