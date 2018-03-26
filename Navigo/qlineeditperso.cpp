#include <iostream>
#include "qlineeditperso.h"

QLineEditPerso::QLineEditPerso(QWidget *parent):QLineEdit(parent)
{

}

/*
void QLineEditPerso::mousePressEvent(QMouseEvent *e){
    mousePressEvent(e);

    emit clickedOut();
}
*/

void QLineEditPerso::focusOutEvent(QFocusEvent *e){
    QLineEdit::focusOutEvent(e);

    setVisible(false);
}


/*
void QLineEditPerso::focusOutEvent(QFocusEvent *e){
    focusOutEvent(e);
    emit clickedOut();
}
*/
