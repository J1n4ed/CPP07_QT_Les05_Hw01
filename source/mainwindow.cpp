#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    about = new About(this);
    stopwatch = new Stopwatch(this);

    ui->frame_display->frameStyle();
    ui->frame_display->setStyleSheet("border-image: url(:/images/soyjak)");

    ui->pb_startstop->setText("СТАРТ");
    ui->pb_startstop->setStyleSheet("QPushButton { background-color : green; color : red; font-size: 18pt; font-weight: bold;}");

    ui->pb_clear->setText("ОЧИСТИТЬ");
    ui->pb_clear->setStyleSheet("QPushButton {font-size: 18pt; font-weight: bold}");
    ui->pb_clear->setEnabled(false);

    ui->pb_exit->setText("ВЫЙТИ");
    ui->pb_exit->setStyleSheet("QPushButton {font-size: 18pt; font-weight: bold}");

    ui->lb_timer->setText("00:00:00");
    ui->lb_timer->setStyleSheet("QLabel {font-size: 40pt; font-weight: bold");

    ui->te_results->setEnabled(false);
    ui->te_results->setStyleSheet("QTextEdit {font-size: 8pt}");

    ui->pb_save_time->setText("Сохранить время круга");
    ui->pb_save_time->setStyleSheet("QPushButton {font-size: 18pt; font-weight: bold}");

    QObject::connect(this, &MainWindow::signal_SendStartStop, stopwatch, &Stopwatch::recieve_startStop);
    QObject::connect(stopwatch, &Stopwatch::signal_SendDisplayUpdate, this, &MainWindow::recive_displayUpdate);
    QObject::connect(this, &MainWindow::signal_getCircleTime, stopwatch, &Stopwatch::recieve_getCircleTime);
    QObject::connect(stopwatch, &Stopwatch::signal_SendCircleTime, this, &MainWindow::recive_circleTime);
    QObject::connect(this, &MainWindow::signal_sendClear, stopwatch, &Stopwatch::recieve_sendClear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendStartStop(bool status)
{
    emit signal_SendStartStop(timerStatus);
}

void MainWindow::getCircleTime()
{
    emit signal_getCircleTime();
}

void MainWindow::sendClear()
{
    emit signal_sendClear();
}

void MainWindow::on_action_about_triggered()
{
    about->show();
}


void MainWindow::on_action_close_triggered()
{
    this->close();
}


void MainWindow::on_pb_startstop_clicked()
{
    timerStatus = !timerStatus;

    if (!ui->pb_clear->isEnabled())
    {
        ui->pb_clear->setEnabled(true);
    }

    sendStartStop(timerStatus);

    if (timerStatus)
    {
        ui->pb_startstop->setText("СТОП");
        ui->pb_startstop->setStyleSheet("QPushButton { background-color : red; color : green; font-size: 18pt; font-weight: bold;}");
    }
    else
    {
        ui->pb_startstop->setText("СТАРТ");
        ui->pb_startstop->setStyleSheet("QPushButton { background-color : green; color : red; font-size: 18pt; font-weight: bold;}");
    }
}


void MainWindow::on_pb_clear_clicked()
{
    sendClear();
    ui->te_results->clear();
    ui->lb_timer->setText("00:00:00");
    currentCircle = 1;
}

void MainWindow::on_pb_exit_clicked()
{
    this->close();
}

void MainWindow::recive_displayUpdate(QString timer)
{
    ui->lb_timer->setText(timer);
}

void MainWindow::recive_circleTime(QString timer)
{
    QString circle_time = "Круг №" + QString::number(currentCircle++) + " , время: " + timer;
    ui->te_results->append(circle_time);
}

void MainWindow::on_pb_save_time_clicked()
{
    getCircleTime();
}

