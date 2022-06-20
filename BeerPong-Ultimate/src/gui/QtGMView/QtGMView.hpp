#pragma once

#include <QWidget>
#include "ui_QtGMView.h"

class QtGMView : public QWidget
{
    Q_OBJECT

public:
    QtGMView(QWidget *parent = Q_NULLPTR);
    ~QtGMView();

private:
    Ui::QtGMView ui;
};
