#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "../headers/about.h"
#include "../headers/stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void sendStartStop(bool);
    void getCircleTime();
    void sendClear();

private slots:

    void on_action_about_triggered();
    void on_action_close_triggered();
    void on_pb_startstop_clicked();
    void on_pb_clear_clicked();
    void on_pb_exit_clicked();
    void on_pb_save_time_clicked();

signals:

    void signal_SendStartStop(bool);
    void signal_getCircleTime();
    void signal_sendClear();

public slots:

     void recive_displayUpdate(QString);
     void recive_circleTime(QString);

private:

    Ui::MainWindow *ui;
    About *about;
    Stopwatch *stopwatch;
    bool timerStatus = false;
    int currentCircle = 1;
};
#endif // MAINWINDOW_H
