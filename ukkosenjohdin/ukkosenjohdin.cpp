#include <iostream>
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
using namespace std;


bool run = true;
int dynoSerial;
struct termios dynoTTY;


void selectPort(){
  char spSelection[50];
  cout << "Give the path of the serial port, for example /dev/ttyUSB0\n";
  cin >> spSelection;

  dynoSerial = open(spSelection,O_RDWR);

  if(tcgetattr(dynoSerial, &dynoTTY) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      
  }
  dynoTTY.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  dynoTTY.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  dynoTTY.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
  dynoTTY.c_cflag |= CS8; // 8 bits per byte (most common)
  dynoTTY.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  dynoTTY.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  dynoTTY.c_lflag &= ~ICANON;
  dynoTTY.c_lflag &= ~ECHO; // Disable echo
  dynoTTY.c_lflag &= ~ECHOE; // Disable erasure
  dynoTTY.c_lflag &= ~ECHONL; // Disable new-line echo
  dynoTTY.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  dynoTTY.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  dynoTTY.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  dynoTTY.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  dynoTTY.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  dynoTTY.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  dynoTTY.c_cc[VMIN] = 0;

  cfsetispeed(&dynoTTY, B19200);
  cfsetospeed(&dynoTTY, B19200);

   if (tcsetattr(dynoSerial, TCSANOW, &dynoTTY) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      
  }




  
}

int main()
{
while (run){
  int selection;
  cout << "Ukkosenjohdin v0.0.1\nMenu:\n0: Exit\n1: Select dyno serial device\n2:Start test\n";
  
  cin >> selection;
  

  switch (selection)
  {
  case 0:
    run = false;
    break;

  case 1:
    selectPort();
    break;
  
  case 2:
    cout <<"test2";
  
  default:
    cout <<"Selection not recocnised\n";
    break;
  }
}
close(dynoSerial);
return 0;
}
