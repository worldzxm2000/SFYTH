#pragma once

#include <QWidget>
#include "ui_ControlUI.h"

class ControlUI : public QWidget
{
	Q_OBJECT

public:
	ControlUI(QWidget *parent = Q_NULLPTR);
	~ControlUI();

private:
	Ui::ControlUI ui;
};
