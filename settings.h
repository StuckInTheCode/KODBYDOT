#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets/QDialog>
#include "ui_settings.h"

class Settings: public QDialog, public Ui_Settings
{
    Q_OBJECT

public:
    Settings(QWidget *parent = 0);
    void accept();

private slots:
    void loadDefaults();
    void loadFromSettings();
    void saveToSettings();
};

#endif // SETTINGS_H
