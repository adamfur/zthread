#include "Monitor.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

using namespace ZThread;

Monitor::Monitor() : _owner(0), _waiting(false), _pending(false) {
  
  if(MPCreateSemaphore(1, 0, &_sema) != noErr) {
    assert(0);
    throw Initialization_Exception();
  }

}
 
Monitor::~Monitor() throw() {

  assert(!_waiting);

  OSStatus status = MPDeleteSemaphore(_sema);
  if(status != noErr) 
    assert(false);

}

Monitor::STATE Monitor::wait(unsigned long timeout) {

  // Calcuate the time, taking into account Intertask Signaling Time
  // http://developer.apple.com/techpubs/macosx/Carbon/oss/MultiPServices/Multiprocessing_Services/index.html?http://developer.apple.com/techpubs/macosx/Carbon/oss/MultiPServices/Multiprocessing_Services/Functions/Creating_and_ssage_Queues.html

  AbsoluteTime tTarget;
  Duration waitDuration = 
    (timeout == 0) ? kDurationForever : (kDurationMillisecond * timeout); 
  
  if(waitDuration != kDurationForever)
    tTarget = AddDurationToAbsolute(waitDuration, UpTime());

  // Update the owner on first use. The owner will not change, each
  // thread waits only on a single Monitor and a Monitor is never
  // shared
  if(_owner == 0)
    _owner = MPCurrentTaskID();

  STATE state(INVALID);
  
  // Serialize access to the state of the Monitor
  // and test the state to determine if a wait is needed.
  _waitLock.acquire();

  if(pending(ANYTHING)) {
    
    // Return without waiting when possible
    state = next();

    _waitLock.release();
    return state;

  }
  // Unlock the external lock if a wait() is probably needed. 
  // Access to the state is still serial.
  _lock.release();

  // Wait for a transition in the state that is of interest, this
  // allows waits to exclude certain flags (e.g. INTERRUPTED) 
  // for a single wait() w/o actually discarding those flags -
  // they will remain set until a wait interested in those flags
  // occurs.

  // Wait, ignoring signals
  _waiting = true;
 
  _waitLock.release();

  // Update the wait time
  if(waitDuration != kDurationForever) 
    waitDuration = AbsoluteDeltaToDuration(tTarget, UpTime());

  // Sleep until a signal arrives or a timeout occurs 
  OSStatus status = MPWaitOnSemaphore(_sema, waitDuration);

  // Reacquire serialized access to the state
  _waitLock.acquire();
 
  // Awaken only when the event is set or the timeout expired
  assert(status == kMPTimeoutErr || status == noErr);
  
  if(status ==  kMPTimeoutErr)
    push(TIMEDOUT);

  // Get the next available STATE
  state = next();  

  _waiting = false;  

  // Its possible that a timeout will wake the thread before a signal is 
  // delivered. Absorb that leftover so the next wait isn't aborted right away
  if(status ==  kMPTimeoutErr && _pending) {
    
    status = MPWaitOnSemaphore(_sema, kDurationForever);
    assert(status == noErr);

  }

  _pending = false;
  
  // Reaquire the external lock
  _lock.acquire();

  // Acquire the internal lock & release the external lock
  _waitLock.release();
  
  return state;

}


bool Monitor::interrupt() {

  // Serialize access to the state
  _waitLock.acquire();
  
  bool wasInterruptable = !pending(INTERRUPTED);
  bool hasWaiter = false;

  // Update the state & wake the waiter if there is one
  if(wasInterruptable) {

    push(INTERRUPTED);
    
    if(_waiting && !_pending) {

      _pending = true;
      hasWaiter = true;

    }

  }

  _waitLock.release();

  if(hasWaiter)
    MPSignalSemaphore(_sema);

  return wasInterruptable;

}

bool Monitor::isInterrupted() {

  // Serialize access to the state
  _waitLock.acquire();

  bool wasInterrupted = pending(INTERRUPTED);
  clear(INTERRUPTED);
    
  _waitLock.release();

  return wasInterrupted;

}


bool Monitor::notify() {

  // Serialize access to the state
  _waitLock.acquire();

  bool wasNotifyable = !pending(INTERRUPTED);
  bool hasWaiter = false;

  // Set the flag if theres a waiter
  if(wasNotifyable) {

    push(SIGNALED);

    if(_waiting && !_pending) {

      _pending = true;
      hasWaiter = true;

    }

  }

  _waitLock.release();

  if(hasWaiter)
    MPSignalSemaphore(_sema);

  return wasNotifyable;

}


bool Monitor::cancel() {

  // Serialize access to the state
  _waitLock.acquire();

  bool wasInterrupted = !pending(INTERRUPTED);
  bool hasWaiter = false;
  
  push(CANCELED);

  // Update the state if theres a waiter
  if(wasInterrupted) {
        
    push(INTERRUPTED);

    if(_waiting && !_pending) {

      _pending = true;
      hasWaiter = true;

    }

  }
  
  _waitLock.release();
  
  if(hasWaiter)
    MPSignalSemaphore(_sema);

  return wasInterrupted;

}

bool Monitor::isCanceled() {
  
  // Serialize access to the state
  _waitLock.acquire();
  
  bool wasCanceled = Status::check2(CANCELED);
    
  if(_owner == MPCurrentTaskID())
    clear(INTERRUPTED);

  _waitLock.release();

  return wasCanceled;

}










