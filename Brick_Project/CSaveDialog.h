#ifndef CSAVEDIALOG_H
#define CSAVEDIALOG_H

#include <QObject>
#include <QLineEdit>
#include <QPushButton>

class CSaveDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CSaveDialog(QWidget *parent = 0);

signals:

public slots:
    void vSave();
};

#endif // CSAVEDIALOG_H
