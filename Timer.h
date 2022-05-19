#pragma once
#include<iostream>
#include<thread>
using namespace std;

class Timer {

public:

    //模拟系统时间 + 闹钟提醒 + 活动过期后更新排序结果
    static void task();

    //开始计时
    static void start();

    //停止计时
    static void stop();

public:

    static int curWeek, curDay, curTime;
    static int isWorking;   //1：开始计时 0：停止计时
    static int interval;
};
