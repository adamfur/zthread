//: c11:Executors.cxx
// Demonstrate Executor use.
#include "zthread/ConcurrentExecutor.h"
#include "zthread/Mutex.h"
#include <iostream>

using namespace ZThread;
using namespace std;

class Task0 : public Runnable {

  int countDown;

public:

  Task0(int n) : countDown(n) {}

  virtual ~Task0() { }

  virtual void run() {

    while(countDown--) 
      cout << countDown << endl;

    cout << "Liftoff!" << endl;

  }

};

int main() {

  ConcurrentExecutor<Mutex> executor;
  
  try {

    for(int i = 0; i < 5; i++)
      executor.execute( new Task0(10) );

    executor.cancel();

  } catch(Synchronization_Exception& e) {
    cerr << e.what() << endl;
  }

} ///:~
