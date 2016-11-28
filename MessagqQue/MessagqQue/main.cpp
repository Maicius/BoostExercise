#include "CMsgQue.hpp"
using namespace boost::interprocess;
int main()
{
	int process, testCase;
	std::cout<<"Input process ID>>\n(1 means writing process; others means read process)"<<std::endl;
	std::cin>>process;
	std::cout<<"Input testCaseID>>\n(1 means test defalut case, others means non_defalut case)"<<std::endl;
	std::cin>>testCase;
	CMsgQue<int> *pMsgQue;
	if( testCase == 1){
		pMsgQue = new CMsgQue<int>();
	}
	else
		pMsgQue = new CMsgQue<int>("message_queue", 100, sizeof(int));
	if(process==1){
		for(int i = 0; i < 100; ++i){
			std::cout<<"Ready:"<<std::endl;
			int number;
			std::cin>>number;
			if(testCase == 1)
				pMsgQue->sendMsg(number);
			else
				pMsgQue->sendMsg(number, "message_queue");
			if(number == 100)
				break;
		}
	} else {
		for(int i = 0; i < 100; ++i){
			int number;
			if(testCase == 1){
				number = pMsgQue->dumpReceiveMsg();
				std::cout<<number<<std::endl;
			} else {
				number = pMsgQue->dumpReceiveMsg("message_queue");
				std::cout<<number<<std::endl;
			}
		}
	}
	system("PAUSE");
	pMsgQue->removeMsgQue("message_queue");
	return 0;
}