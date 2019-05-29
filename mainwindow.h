#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "rankdialog.h"
/* 
*This​ ​class​ ​is​ ​used​ ​to​ display the main windows  // YANG et DU
*
*/ 
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void updateGame();

    void on_platformButton_clicked();

    void on_exitButton_clicked();

    void on_classmentButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer_;// realise the display dynamic
};

#endif // MAINWINDOW_H
