#include "CSaveDialog.h"

CSaveDialog::CSaveDialog(QWidget *parent) :
    QDialog(parent)
{
    QLabel* poNameLabel = new QLabel(tr("Entrer un nom :"));
    oLineEdit = new QLineEdit;
    QPushButton* poSaveBtn = new QPushButton(tr("&Save"));
    connect(poSaveBtn, SIGNAL(clicked()), this, SLOT(vSave()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(poNameLabel);
    layout->addWidget(oLineEdit);
    layout->addWidget(poSaveBtn);

    setLayout(layout);
    setWindowTitle(tr("Save a Score"));
    show();
}


void CSaveDialog::vSave(void){
     {
         QString text = lineEdit->text();

         if (text.isEmpty()) {
             QMessageBox::information(this, tr("Empty Field"),
                 tr("Please enter a name."));
             return;
         } else {
             m_poCtrl->vSave(text);
             lineEdit->clear();
             m_poSave->hide();
         }
     }
}
