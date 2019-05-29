#ifndef RANKDIALOG_H
#define RANKDIALOG_H

#include <QDialog>
#include "rank.h"
/* 
*This​ ​class​ ​is​ ​used​ ​to​ exctute the rank dialog.  // YANG
*
*/ 
namespace Ui {
class RankDialog;
}

class RankDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RankDialog(QWidget *parent = 0);
    ~RankDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::RankDialog *ui;
    Rank r1_;
};

#endif // RANKDIALOG_H
