//: c11:SimpleThread.cxx
// Very simple Threading example.
#include "zthread/Thread.h"
#include <iostream>

using namespace ZThread;
using namespace std;

class Launch : public Runnable {

  int countDown;

public:

  Launch(int n) : countDown(n) {}

  virtual ~Launch() throw() {}

  virtual void run() {
    try {
    
  Thread::sleep(2000);
    while(countDown--) 
      cout << countDown << endl;

    cout << "Liftoff!" << endl;
} catch(Synchronization_Exception& e) {
  cout << e.what() << endl;
}
    cout << "DONE!" << endl;
  }

};

int main() {
  
  try {
  
    Thread(new Launch(10));

  } catch(Synchronization_Exception& e) {
    cerr << e.what() << endl;
  }
  
  cout << " !exit! " << endl;
  
} ///:~
