#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include "shared_mutex_data.h"

#include <iostream>
/********************************************
*void interProcessOutputTest(int vProcessID)
*change the vProcessID to create new Process;
*********************************************/
void interProcessOutputTest(int vProcessID);
int main ()
{
   interProcessOutputTest(1);
   return 0;
}
void interProcessOutputTest(int vProcessID)
{
	using namespace boost::interprocess;
	int processID = vProcessID;
	   struct shm_remove
   {
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   } remover;
 
   shared_memory_object shm
      (open_only                   
      ,"MySharedMemory"           
      ,read_write 
      );
   mapped_region region
      (shm                      
      ,read_write 
      );
   void * addr = region.get_address();
   std::cout<<region.get_size()<<std::endl;
   SSharedMutexLock * data = static_cast<SSharedMutexLock*>(addr);

   for(data->m_Current_line; data->m_Current_line < SSharedMutexLock::ENumItems;){
	   data->m_ProcessArray[processID] = false;
	   sharable_lock<interprocess_sharable_mutex> lock(data->m_Mutex);
	   std::cout << data->m_Items[data->m_Current_line] <<std::endl;	   
	   lock.unlock();
	   data->m_ProcessArray[processID] = true;	   
	   while(1){
		   if(data->m_WriteProcessEnd)
			   break;
	   }
   }
}