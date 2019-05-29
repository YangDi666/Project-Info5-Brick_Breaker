#ifndef LOSEDIALOG_H
#define LOSEDIALOG_H
#include <QDialog>
#include "scores.h"

namespace Ui {
class LoseDialog;
}

class LoseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoseDialog(QWidget *parent = 0);
    ~LoseDialog();

private slots:

    void on_pushButton_clicked();

private:
    Ui::LoseDialog *ui;
    Scores scores_;
};

#endif // LOSEDIALOG_H
