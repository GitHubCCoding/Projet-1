#ifndef QLINEEDITPERSO_H
#define QLINEEDITPERSO_H
#include <QtWidgets>

class QLineEditPerso : public QLineEdit
{

    Q_OBJECT

public:
    QLineEditPerso(QWidget *parent=0);

protected:
    //virtual void mousePressEvent(QMouseEvent *e);
    virtual void focusOutEvent(QFocusEvent *event);

//signals:
    //void clickedOut();
};

#endif // QLINEEDITPERSO_H
