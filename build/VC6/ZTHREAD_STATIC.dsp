# Microsoft Developer Studio Project File - Name="ZTHREAD_STATIC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ZTHREAD_STATIC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZTHREAD_STATIC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZTHREAD_STATIC.mak" CFG="ZTHREAD_STATIC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZTHREAD_STATIC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ZTHREAD_STATIC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZTHREAD_STATIC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ZTHREAD_STATIC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\ZThread.lib"

!ENDIF 

# Begin Target

# Name "ZTHREAD_STATIC - Win32 Release"
# Name "ZTHREAD_STATIC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\AtomicCount.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ConcurrentExecutor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\Condition.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ConditionImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\CountingSemaphore.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\Debug.h
# End Source File
# Begin Source File

SOURCE=..\..\src\DeferredInterruptionScope.h
# End Source File
# Begin Source File

SOURCE=..\..\src\FastLock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\FastMutex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\FastRecursiveLock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\FastRecursiveMutex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\IntrusivePtr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Monitor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\Monitor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mutex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\MutexImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\PoolExecutor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\PriorityCondition.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\PriorityInheritanceMutex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\PriorityMutex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\PrioritySemaphore.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\RecursiveMutex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\RecursiveMutexImpl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\RecursiveMutexImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Scheduling.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Semaphore.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\SemaphoreImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\State.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Status.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SynchronousExecutor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\Thread.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadedExecutor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadImpl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadLocalImpl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadOps.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadOps.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadQueue.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\ThreadQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Time.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\TimeStrategy.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TSS.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\zthread\AtomicCount.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Barrier.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\BiasedReadWriteLock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\BlockingQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\BoundedQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Cancelable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ClassLockable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ConcurrentExecutor.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Condition.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Config.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\CountedPtr.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\CountingSemaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Exceptions.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Executor.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\FairReadWriteLock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\FastMutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\FastRecursiveMutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Guard.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\GuardedClass.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Lockable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\LockedQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\MonitoredQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\NonCopyable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\PoolExecutor.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Priority.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\PriorityCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\PriorityInheritanceMutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\PriorityMutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\PrioritySemaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Queue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ReadWriteLock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\RecursiveMutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Runnable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Semaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Singleton.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\SynchronousExecutor.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Task.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Thread.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ThreadedExecutor.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ThreadLocal.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ThreadLocalImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Time.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\Waitable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\zthread\ZThread.h
# End Source File
# End Group
# End Target
# End Project
