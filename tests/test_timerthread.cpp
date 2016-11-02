#include <iostream>
#include <string>
#include <vector>

#include "../include/TimerThread.h"

using namespace std;

void func()
{
    cout << "hello world!" << endl;
}

int main(int argc, const char *argv[])
{
    TimerThread t;
    t.setTimer(3,1);
    t.setTimerCallback(&func);

    t.startTimerThread();

    sleep(10);
    t.cancelTimerThread();
    return 0;
}
