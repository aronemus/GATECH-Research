#include "TeensyCounter.h"
#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    TeensyCounter counter(0); // 0 = /dev/ttyACM0
    while (1)
    {
        if (counter.NewRateMeasurementAvailable())
            cout << “Channel 1: “ <<  counter.GetCountRate1() << “ Hz | Channel 2: “ << counter.GetCountRate2() << “ Hz” << endl;
        usleep(250000); // 250ms
    }
    return 0;
}
