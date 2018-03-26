#ifndef QCHECKBOXCUSTOM_H
#define QCHECKBOXCUSTOM_H
#include <QtWidgets>
//#include <QCheckBox>

class QCheckBoxCustom : public QCheckBox
{
    Q_OBJECT

public:
    QCheckBoxCustom(QWidget *parent=0);

//protected:
    void setCheckedCustom();

signals:
    void isCheckedSignal();

//public slots:

};

#endif // QCHECKBOXCUSTOM_H
