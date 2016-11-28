#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "shared_mutex_data.h"
#include <iostream>
#include <cstdio>


/********************************************************************
*void interProcessInputTest(int vProcessNumber, int vSharedMemorySize);
*the ProcessNumber should larger or equal to the number of reader Process
*SharedMemorySize should larger of equal to the size of struct SSharedMutexLock;
********************************************************************/
void interProcessInputTest(int vProcessNumber, int vSharedMemorySize);
int main ()
{
	interProcessInputTest(3, 10240);
	return 0;
}
void interProcessInputTest(int vProcessNumber, int vSharedMemorySize)
{
	using namespace boost::interprocess;
	int processNumber = vProcessNumber;
	if(vSharedMemorySize <=sizeof(SSharedMutexLock)){
		std::cout<<"the minimal size of Memory is 10240"<<std::endl;
		vSharedMemorySize = 10240;
	}
	struct shm_remove
	{
		shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
	} remover;
	shared_memory_object shm
		(create_only               
		,"MySharedMemory"          
		,read_write  
		);
	shm.truncate(vSharedMemorySize);
	mapped_region region
		(shm                      
		,read_write 
		);	
	std::cout<<"WriteProcess£º"<<region.get_size()<<std::endl;
	void *addr = region.get_address();

	SSharedMutexLock *data = new (addr)SSharedMutexLock();

	for(data->m_Current_line; data->m_Current_line < SSharedMutexLock::ENumItems; data->m_Current_line++){		  
		scoped_lock<interprocess_sharable_mutex> lock(data->m_Mutex);
		data->m_WriteProcessEnd = true;
		std::cin>>data->m_Items[data->m_Current_line];
		std::cout<<"currentLine:"<<data->m_Current_line<<std::endl;
		data->m_WriteProcessEnd = false;
		lock.unlock();		  
		for(int i=0; i<processNumber; i++)
			if(!data->m_ProcessArray[i]){
				i = i-1;
			}
	}
	std::cout<<"finished";
}