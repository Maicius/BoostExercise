#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
struct SSharedMutexLock
{
   enum { ENumItems = 100 };
   enum { ELineSize = 100 };
 
   SSharedMutexLock(){
	   m_Current_line = 0;
	   m_WriteProcessEnd = false;
	   memset(m_ProcessArray, true, sizeof(int)* ENumItems);
   }
 
   boost::interprocess::interprocess_sharable_mutex m_Mutex;

   char m_Items[ENumItems][ELineSize];
   int  m_Current_line;
   bool m_WriteProcessEnd;
   static const int m_ProcessMaxNumber = 100;
   bool  m_ProcessArray[m_ProcessMaxNumber];
};