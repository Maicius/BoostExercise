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
glm::vec2 mouse_callback(GLFWwindow* window, double xpos, double ypos);
glm::vec2 mousePos = glm::vec2(0.0f);
GLfloat MVP[16] = {1.0f, 0.0f, 0.0f, mousePos.x,
					0.0f, 1.0f, 0.0f, mousePos.y,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f};
bool firstMouse = true;

int main(int argc, char*argv[])
{
	std::pair<unsigned int, unsigned int> ChildAndID;
	std::cin >> ChildAndID.first >> ChildAndID.second;

	drawWindow *drawWindows = new drawWindow();
	GLFWwindow *window = drawWindows->createGlfw();	
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)mouse_callback);
	GLuint VBO = drawWindows->createVertexBuffer();
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
	Shader shader("vertex.vert", "fragment.frag");
	while(!glfwWindowShouldClose(window))
	{
		std::cout<<"EnterLoop"<<std::endl;
		if (ChildAndID.first > 1)
		{			
			scoped_lock<interprocess_sharable_mutex> lock(*pSharableMutex);
			while (!IsAllReaded && !FirstTime)
			{
				pCondition->notify_all();
				pCondition->wait(lock);
				for (auto& P2R : *pProcess2IsReadedMap)
				{
					if (P2R.second == true) ChildProcessNum++;
				}

				if (ChildProcessNum == ChildAndID.first) IsAllReaded = true;
			}
			std::cout<<"Parent"<<std::endl;

			drawWindows->Render(shader, MVP, VBO);
			glfwSwapBuffers(window);
			glfwPollEvents();
			i->first = mousePos.x;
			i->second = mousePos.y;

			FirstTime       = false;
			IsAllReaded     = false;
			ChildProcessNum = 0;
			for (auto& P2R : *pProcess2IsReadedMap)
			{
				P2R.second = false;
			}

			pCondition->notify_all();
			pCondition->wait(lock);

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
			mousePos.x = i->first;
			mousePos.y = i->second;
			drawWindows->Render(shader, MVP, VBO);
			glfwSwapBuffers(window);
			glfwPollEvents();
			//std::cout << i->first << " " << i->second << std::endl;
			pProcess2IsReadedMap->find(ChildAndID.second)->second = true;
			pCondition->notify_one();
			pCondition->wait(lock);
		}
	}
	pCondition->notify_all();
	shared_memory_object::remove("shm");
	glfwTerminate();
	system("pause");
}
glm::vec2 scaleMouse(glm::vec2 coords, glm::vec2 viewport){
	return glm::vec2( static_cast<float>(coords.x*2.f) / static_cast<float>(viewport.x) - 1.f,
		1.f - static_cast<float>(coords.y*2.f) / static_cast<float>(viewport.y) );
}
glm::vec2 mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	if(firstMouse)
	{
		mousePos.x = xpos;
		mousePos.y = ypos;
		firstMouse = false;
	}
	glm::vec2 mouseOffset;
	mouseOffset.x = xpos - mousePos.x;
	mouseOffset.y = mousePos.y - ypos; 

	mousePos.x = xpos;
	mousePos.y = ypos;

	//mousePos = scaleMouse( mouseOffset, glm::vec2(viewport[2],viewport[3]));
return mouseOffset;
}	

