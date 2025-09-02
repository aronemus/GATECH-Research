TeensyCounter.h

#include <iostream>
#include <string>
using namespace std;

class TeensyCounter
{
private:
    std::string usbname;
    long int rate1;
    long int rate2;
    int fd;
public:
    TeensyCounter(int port);
    ~TeensyCounter();
    bool NewRateMeasurementAvailable();
    long int GetCountRate1() { return rate1; }
    long int GetCountRate2() { return rate2; }
};
