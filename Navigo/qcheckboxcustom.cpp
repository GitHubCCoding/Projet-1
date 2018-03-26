#include <iostream>
#include "qcheckboxcustom.h"

QCheckBoxCustom::QCheckBoxCustom(QWidget *parent):QCheckBox(parent)
{

}

void QCheckBoxCustom::setCheckedCustom()
{
    //setChecked(isChecked());
   // std::cout<<"état du CheckBox"<<checkState()<<std::endl;
    if(isChecked())
    {
        //setChecked(true);
        emit isCheckedSignal();
    }
    //return QCheckBox::isChecked();
}
