#pragma once

#include <QGroupBox>
#include <QtWidgets>

class QCheckBox;
class QRadioButton;


class Mods : public QGroupBox{
    Q_OBJECT

private:
    QRadioButton* Training;
    QRadioButton* Arcade;
public:
    Mods (QWidget* pwgt = 0);
public slots:
    void slotButtonClicked();
};

