#include "../headers/stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    timer->setInterval(100);
    timer->setTimerType(Qt::PreciseTimer);
    QObject::connect(timer, &QTimer::timeout, this, &Stopwatch::recieve_timer_update);
}

Stopwatch::~Stopwatch()
{
    delete timer;
}

void Stopwatch::SendDisplayUpdate(QString time)
{
    emit signal_SendDisplayUpdate(time);
}

void Stopwatch::SendCircleTime(QString time)
{
    emit signal_SendCircleTime(time);
}

void Stopwatch::recieve_startStop(bool status)
{
    // get update on start stop commands
    timerStatus = status;

    if (status)
    {
        if (!timerActivated)
        {
            timer->start(100);
            timerActivated = true;
        }
        else
        {
            timer->setInterval(100);
            resume();
        }
    }
    else
    {
        pause();
    }
}

void Stopwatch::recieve_getCircleTime()
{
    // build return

    QString circle_time;

    int circle_min = minutes - prev_minutes;
    int circle_sec = seconds - prev_seconds;

    if (circle_sec < 0)
    {
        --circle_min;
        circle_sec = 60 - circle_sec;
    }

    int circle_msec = mseconds - prev_mseconds;

    if (circle_msec < 0)
    {
        --circle_sec;
        circle_msec = 100 - circle_msec;

        if (circle_sec < 0)
        {
            --circle_min;
            circle_sec = 60 - circle_sec;
        }
    }

    // build string

    if (circle_min < 10)
    {
        circle_time = circle_time + "0" + QString::number(circle_min);
    }
    else
    {
        circle_time = circle_time + QString::number(circle_min);
    }

    circle_time += ":";

    if (circle_sec < 10)
    {
        circle_time = circle_time + "0" + QString::number(circle_sec);
    }
    else
    {
        circle_time = circle_time + QString::number(circle_sec);
    }

    circle_time += ":";

    if (circle_msec < 10)
    {
        circle_time = circle_time + "00" + QString::number(circle_msec);
    }
    else if (circle_msec < 100)
    {
        circle_time = circle_time + "0" + QString::number(circle_msec);
    }
    else
    {
        circle_time = circle_time + QString::number(circle_msec);
    }

    // update last circle ints

    prev_minutes = minutes;
    prev_seconds = seconds;
    prev_mseconds = mseconds;

    SendCircleTime(circle_time);
}

void Stopwatch::recieve_sendClear()
{
    minutes = 0;
    seconds = 0;
    mseconds = 0;

    prev_minutes = 0;
    prev_seconds = 0;
    prev_mseconds = 0;

    if (!timerStatus)
    {
        timerActivated = false;
    }
}

void Stopwatch::recieve_timer_update()
{
    if (timerStatus)
    {
        QString current_timer;
        update_time();
        current_timer = build_string();
        SendDisplayUpdate(current_timer);
    }
}

void Stopwatch::pause()
{
    int remaining = timer->remainingTime();
    timer->stop();
    timer->setInterval(remaining);
}

void Stopwatch::resume()
{
    timer->start();
}

void Stopwatch::update_time()
{
    mseconds+=10;

    if (mseconds == 100)
    {
        mseconds = 0;
        ++seconds;
    }

    if (seconds == 60)
    {
        seconds = 0;
        ++minutes;
    }
}

QString Stopwatch::build_string()
{
    QString current_timer;

    if (minutes < 10)
    {
        current_timer = current_timer + "0" + QString::number(minutes);
    }
    else
    {
        current_timer = current_timer + QString::number(minutes);
    }

    current_timer += ":";

    if (seconds < 10)
    {
        current_timer = current_timer + "0" + QString::number(seconds);
    }
    else
    {
        current_timer = current_timer + QString::number(seconds);
    }

    current_timer += ":";

    if (mseconds < 10)
    {
        current_timer = current_timer + "00" + QString::number(mseconds);
    }
    else if (mseconds < 100)
    {
        current_timer = current_timer + "0" + QString::number(mseconds);
    }
    else
    {
        current_timer = current_timer + QString::number(mseconds);
    }

    return current_timer;
}
