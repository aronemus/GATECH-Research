TeensyCounter.cpp

#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "TeensyCounter.h"

TeensyCounter::TeensyCounter(int port)
{
    cout << "for the computer to receive data make sure the teensy is plugged into the computer after the computer has started!!!" << endl;
    usbname = "/dev/ttyACM" + std::to_string(port);
    cout << "using usb port to teensy " << usbname << endl;

    fd = open(usbname.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    cout << "port number " << fd << endl;
    if (fd < 0)
    {
        cout << "Teensy not connected" << endl;
        exit(1);
    }

    tcflush(fd, TCIOFLUSH);

    struct termios port_settings;
    tcgetattr(fd, &port_settings);

    cfsetispeed(&port_settings, B115200);
    cfsetospeed(&port_settings, B115200);

    port_settings.c_cflag |= (CLOCAL | CREAD);
    port_settings.c_cflag &= ~PARENB;
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;

    tcsetattr(fd, TCSANOW, &port_settings);
    cout << "Have configured the port" << endl;
    tcflush(fd, TCIOFLUSH);

    cout << "done opening port for reading counter values" << endl;
}

TeensyCounter::~TeensyCounter() {}

bool TeensyCounter::NewRateMeasurementAvailable()
{
    bool bNewRate = false;
    int numbytes = 0;
    ioctl(fd, FIONREAD, &numbytes);

    if (numbytes > 0)
    {
        char reply[numbytes + 1];
        ssize_t size = read(fd, reply, numbytes);
        reply[size] = '\0'; // null terminate

      	std::string data(reply);
      	std::istringstream iss(data);

        long int r1, r2;
        if (iss >> r1 >> r2)
        {
          rate1 = r1;
          rate2 = r2;
          bNewRate = true;
        }
    }
return bNewRate;
}
