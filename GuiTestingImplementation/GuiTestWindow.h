#pragma once

#include <QtWidgets/QWidget>
#include "ui_GuiTestWindow.h"

class GuiTestWindow : public QWidget {
	Q_OBJECT

public:
	GuiTestWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::GuiTestWindowClass ui;
};