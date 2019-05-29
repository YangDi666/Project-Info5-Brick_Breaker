#include "rankdialog.h"
#include "ui_rankdialog.h"
#include <iostream>

RankDialog::RankDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankDialog)
{
    ifstream is("C://Users//asus//Desktop//bureau//ST//smestre 8//info//ANG Di DU Pingjie//code//code//Scores.txt");
            if (!is.good())
            {
                cout<<"cant load!"<<endl;
            }
            r1_.load(is);
            is.close();

    ui->setupUi(this);
}

RankDialog::~RankDialog()
{
    delete ui;
}

void RankDialog::on_pushButton_2_clicked()
{
    close();
    r1_.clear();
}

void RankDialog::on_pushButton_3_clicked()
{
    if(r1_.size()>=1)
        ui->label_1->setText(QString("1. %1 / ").arg(r1_[0].getScore())+QString::fromStdString(r1_[0].getName()));
    if(r1_.size()>=2)
        ui->label_2->setText(QString("2. %1 / ").arg(r1_[1].getScore())+QString::fromStdString(r1_[1].getName()));
    if(r1_.size()>=3)
        ui->label_3->setText(QString("3. %1 / ").arg(r1_[2].getScore())+QString::fromStdString(r1_[2].getName()));
    if(r1_.size()>=4)
        ui->label_4->setText(QString("4. %1 / ").arg(r1_[3].getScore())+QString::fromStdString(r1_[3].getName()));
    if(r1_.size()>=5)
        ui->label_5->setText(QString("5. %1 / ").arg(r1_[4].getScore())+QString::fromStdString(r1_[4].getName()));
    if(r1_.size()>=6)
        ui->label_6->setText(QString("6. %1 / ").arg(r1_[5].getScore())+QString::fromStdString(r1_[5].getName()));
    if(r1_.size()>=7)
        ui->label_7->setText(QString("7. %1 / ").arg(r1_[6].getScore())+QString::fromStdString(r1_[6].getName()));
    if(r1_.size()>=8)
        ui->label_8->setText(QString("8. %1 / ").arg(r1_[7].getScore())+QString::fromStdString(r1_[7].getName()));
    if(r1_.size()>=9)
        ui->label_9->setText(QString("9. %1 / ").arg(r1_[8].getScore())+QString::fromStdString(r1_[8].getName()));
    if(r1_.size()>=10)
        ui->label_10->setText(QString("10. %1 / ").arg(r1_[9].getScore())+QString::fromStdString(r1_[9].getName()));
}
