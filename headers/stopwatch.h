#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:

    explicit Stopwatch(QObject *parent = nullptr);

    ~Stopwatch();

    void SendDisplayUpdate(QString);
    void SendCircleTime(QString);

signals:

    void signal_SendDisplayUpdate(QString);
    void signal_SendCircleTime(QString);

public slots:

    void recieve_startStop(bool);
    void recieve_getCircleTime();
    void recieve_sendClear();

private slots:

    void recieve_timer_update();

private:

     QTimer *timer;
     int minutes = 0;
     int seconds = 0;
     int mseconds = 0;
     bool timerStatus = false;
     bool timerActivated = false;
     int prev_minutes = 0;
     int prev_seconds = 0;
     int prev_mseconds = 0;

     void pause();
     void resume();
     void update_time();
     QString build_string();
};

#endif // STOPWATCH_H
