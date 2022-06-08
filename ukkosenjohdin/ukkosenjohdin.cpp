#include <iostream>
using namespace std;

#include <libserialport.h>
bool run = true;

int main()
{
while (run){
  int selection;
  cout << "Ukkosenjohdin v0.0.1\nMenu:\n0: Exit\n1: Select serial device\n2:Start test\n";
  
  cin >> selection;
  

  switch (selection)
  {
  case 0:
    run = false;
    break;

  case 1:
    cout <<"test 1";
    break;
  
  case 2:
    cout <<"test2";
  
  default:
    cout <<"Selection not recocnised\n";
    break;
  }
}

return 0;
}
