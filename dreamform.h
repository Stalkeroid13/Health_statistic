#ifndef DREAMFORM_H
#define DREAMFORM_H

#include <QDialog>
#include "dream_user.h"

namespace Ui {
class dreamform;
}

class dreamform : public QDialog
{
    Q_OBJECT

public:
    explicit dreamform(QWidget *parent = nullptr);
    ~dreamform();

private slots:
       void on_AddDream_clicked();

private:
    Ui::dreamform *ui;
};

#endif // DREAMFORM_H
