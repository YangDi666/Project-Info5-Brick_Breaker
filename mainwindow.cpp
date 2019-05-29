#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    timer_=new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateGame()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer_;
}

void MainWindow::on_startButton_clicked()
{
     bool ok;
     QString text=QInputDialog::getText(this,"SetWidth",
                              "Input the width of platform(1.0-50.0)",
                              QLineEdit::Normal, ui->platformLabel->text(),&ok);
     if (ok && !text.isEmpty())
     {
         ui->Game->getGame()->loadRank();
         ui->Game->setWidth(text.toFloat());
         ui->ballsLabel->setText(QString("Balls Left : %1").arg(ui->Game->getNumberOfball()));
         ui->levelLabel->setText(QString("Level : %1").arg(ui->Game->getLevel()));
         ui->scoreLabel->setText(QString("Score : %1").arg(ui->Game->getScore()));
         ui->platformLabel->setText(QString("Width of Platform : %1").arg(text.toFloat()));
         timer_->start(15);
     }
}

void MainWindow::updateGame()
{
    if(ui->Game->getGame()->isLose())
    {
        bool ok;
        QString text=QInputDialog::getText(this,"Save Score",
                                 "Input your name, please.",
                                 QLineEdit::Normal, "" ,&ok);
        if (ok && !text.isEmpty())
        {
            ui->Game->getGame()->setName(text.toStdString());
        }
    }
    ui->Game->getGame()->getPlatform_()->movePlatform(ui->Web->getMove());
    ui->Game->updateGame();
    ui->ballsLabel->setText(QString("Balls Left : %1").arg(ui->Game->getNumberOfball()));
    ui->levelLabel->setText(QString("Level : %1").arg(ui->Game->getLevel()));
    ui->scoreLabel->setText(QString("Score : %1").arg(ui->Game->getScore()));
    ui->platformLabel->setText(QString("Width of Platform : %1").arg(ui->Game->getWidthOfPlatform()));
}

void MainWindow::on_platformButton_clicked()
{
    bool ok;
    QString text=QInputDialog::getText(this,"ChangeWidth",
                              "Input the width of platform(1.0-50.0)",
                              QLineEdit::Normal, ui->platformLabel->text(),&ok);
    if (ok && !text.isEmpty())
    {
        ui->Game->setWidth(text.toFloat());
        ui->platformLabel->setText(QString("Width of Platform : %1").arg(text.toFloat()));
    }
}

void MainWindow::on_exitButton_clicked()
{
    ui->Game->getGame()->clearRank();
    close();
}

void MainWindow::on_classmentButton_clicked()
{
    RankDialog r(this);
    r.exec();
}
