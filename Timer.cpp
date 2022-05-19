#include "Timer.h"

int Timer::curWeek = 0;
int Timer::curDay = 0;
int Timer::curTime = 9;
int Timer::isWorking = 0;
int Timer::interval = 10000;    //�Լ������10s��Ϊģ��ϵͳ��1h

void Timer::task() {

    while (isWorking) {

        this_thread::sleep_for(chrono::milliseconds(interval));
        curTime++;

        if (curTime == 24) {

            curTime = 0;
            curDay++;

            if (curDay == 7) {

                curDay = 0;
                curWeek++;

                if (curWeek == 20) {

                    stop();
                }
            }
        } 
    }
}

void Timer::start() {

    if (isWorking) return;

    isWorking = 1;

    thread th(task);
    th.detach();
}

void Timer::stop() {

    if (!isWorking) return;

    isWorking = 0;
}
