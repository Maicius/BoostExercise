#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition_any.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/interprocess/containers/pair.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <glm.hpp>
#include "drawWindow.h"

#include <iostream>

using namespace boost::interprocess;
glm::vec2 scaleMouse(glm::vec2 coords, glm::vec2 viewport);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
glm::vec2 mousePos = glm::vec2(0.0f);
glm::vec2 mouseOffset;
GLfloat MVP[16] = {1.0f, 0.0f, 0.0f, mousePos.x,
					0.0f, 1.0f, 0.0f, mousePos.y,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f};
bool firstMouse = true;

int main(int argc, char*argv[])
{
	//shared_memory_object::remove("shm");
	std::cout<<"Please input process Number"<<std::endl;
	std::pair<unsigned int, unsigned int> ChildAndID;
	std::cin >> ChildAndID.first >> ChildAndID.second;

	drawWindow *drawWindows = new drawWindow();
	GLFWwindow *window = drawWindows->createGlfw();	
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);
	std::cout<<"initFinished"<<std::endl;
	typedef boost::interprocess::pair<int, float> Pair;
	managed_shared_memory managed_shm(open_or_create, "shm", 102400);
	Pair *i = managed_shm.find_or_construct<Pair>("Pair")();

	typedef allocator<std::pair<const unsigned int, bool>, managed_shared_memory::segment_manager> MapAllocator;
	typedef map<unsigned int, bool, std::less<unsigned int>, MapAllocator> MyMap;
	MyMap *pProcess2IsReadedMap = managed_shm.find_or_construct<MyMap>("p2read")(std::less<unsigned int>(), managed_shm.get_segment_manager());
	(*pProcess2IsReadedMap).insert(std::make_pair(ChildAndID.second, false));

	interprocess_sharable_mutex *pSharableMutex = managed_shm.find_or_construct<interprocess_sharable_mutex>("mtx")();
	interprocess_condition_any *pCondition = managed_shm.find_or_construct<interprocess_condition_any>("cnd")();

	bool FirstTime   = true;
	bool IsAllReaded = false;
	unsigned int ChildProcessNum = 0;
	while(!glfwWindowShouldClose(window))
	{
		
		std::cout<<"EnterLoop"<<std::endl;
		if (ChildAndID.first > 1)
		{			
			scoped_lock<interprocess_sharable_mutex> lock(*pSharableMutex);
		/*	while (!IsAllReaded && !FirstTime)
			{
				pCondition->notify_all();
				pCondition->wait(lock);
				for (auto& P2R : *pProcess2IsReadedMap)
				{
					if (P2R.second == true) ChildProcessNum++;
				}

				if (ChildProcessNum == ChildAndID.first) IsAllReaded = true;
			}*/
			std::cout<<"Parent"<<std::endl;

			drawWindows->Render(window, mouseOffset);
			std::cout<<"RenderFinished"<<std::endl;
			i->first = mouseOffset.x;
			i->second = mouseOffset.y;

			FirstTime       = false;
			IsAllReaded     = false;
			ChildProcessNum = 0;
			for (auto& P2R : *pProcess2IsReadedMap)
			{
				P2R.second = false;
			}

			pCondition->notify_all();
			//pCondition->wait(lock);

		}
		else
		{
			std::cout<<"Children"<<std::endl;
			sharable_lock<interprocess_sharable_mutex> lock(*pSharableMutex);
			while (pProcess2IsReadedMap->find(ChildAndID.second)->second)
			{
				pCondition->notify_one();
				pCondition->wait(lock);
			}
			mouseOffset.x = i->first;
			mouseOffset.y = i->second;
			drawWindows->Render(window, mouseOffset);
			std::cout<<"RenderFinished"<<std::endl;
			std::cout << i->first << " " << i->second << std::endl;
			pProcess2IsReadedMap->find(ChildAndID.second)->second = true;
			pCondition->notify_one();
			//pCondition->wait(lock);
		}
	}
	pCondition->notify_all();
	shared_memory_object::remove("shm");
	glfwTerminate();
	system("pause");
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		mousePos.x = xpos;
		mousePos.y = ypos;
		firstMouse = false;
	}
	
	mouseOffset.x = xpos - mousePos.x;
	mouseOffset.y = mousePos.y - ypos; 

	mousePos.x = xpos;
	mousePos.y = ypos;
}	

