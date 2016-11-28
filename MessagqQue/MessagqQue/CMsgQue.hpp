#include <boost/interprocess/ipc/message_queue.hpp>
using namespace boost::interprocess;

template <typename T>
class CMsgQue{
private:
	T m_ReceivedMsg;
	T m_SendMsg;
	const char* m_DefaultMsgQueName;
	int m_DefaultMaxQueLen;
	int m_DefaultMaxMsgLen;
	void raiseNotice();
public:
	CMsgQue(const char* vMsgQueName,int vMaxQueLen,int vMaxMsgLen);
	CMsgQue();
	void sendMsg(T vSendMsg);
	void sendMsg(T vSendMsg, const char* vMsgQueName); 
	T dumpReceiveMsg();
	T dumpReceiveMsg(const char* vMsgQueName);
	void removeMsgQue(const char* vMsgQueName);
	void removeMsgQue();
};

//******************************************************************
//FUNCTION:
template<typename T>
void CMsgQue<T>::raiseNotice()
{
	std::cout<<"Notice: The Message Queue is Full!\n New Message Will be Deserted"<<std::endl;
}

//******************************************************************
//FUNCTION:
template <typename T>
CMsgQue<T>::CMsgQue(const char* vMsgQueName,int vMaxQueLen,int vMaxMsgLen)
{
	try{
		m_DefaultMsgQueName = vMsgQueName;
		m_DefaultMaxQueLen = vMaxQueLen;
		m_DefaultMaxMsgLen = vMaxMsgLen;
		message_queue mq(open_or_create, vMsgQueName, vMaxQueLen, vMaxMsgLen);
	}catch(interprocess_exception &ex){  
		std::cout << ex.what() << std::endl;  
		exit(0);
	} 
}

//******************************************************************
//FUNCTION:
template <typename T>
CMsgQue<T>::CMsgQue()
{
	try{
		m_DefaultMsgQueName = "message_queue";
		m_DefaultMaxQueLen = 1024;
		m_DefaultMaxMsgLen = sizeof(T);
		message_queue mq(open_or_create, m_DefaultMsgQueName, m_DefaultMaxQueLen, m_DefaultMaxMsgLen);
	}catch(interprocess_exception &ex){  
		std::cout << ex.what() << std::endl;  
		exit(0);
	} 
}

//******************************************************************
//FUNCTION:
template <typename T>
void CMsgQue<T>::sendMsg(T vSendMsg)
{
	try{
		message_queue mq(open_only, m_DefaultMsgQueName);
		m_SendMsg = vSendMsg;
		if(!mq.try_send(&m_SendMsg, m_DefaultMaxMsgLen, 0))
		{
			raiseNotice();
		}
	}catch(interprocess_exception &ex){  
		std::cout << ex.what() << std::endl;  
		exit(1);
	}
}

//******************************************************************
//FUNCTION:
template <typename T>
void CMsgQue<T>::sendMsg(T vSendMsg, const char* vMsgQueName)
{  
	try{
		message_queue mq(open_only, vMsgQueName);
		m_SendMsg = vSendMsg;
		if(!mq.try_send(&m_SendMsg,m_DefaultMaxMsgLen, 0))
		{
			raiseNotice();
		}
	}  
	catch(interprocess_exception &ex){  
		std::cout << ex.what() << std::endl;  
		exit(1);
	}
}

//******************************************************************
//FUNCTION:
template <typename T>
T CMsgQue<T>::dumpReceiveMsg()
{
	try{
		message_queue mq(open_only, m_DefaultMsgQueName);  
		unsigned int Priority;  
		message_queue::size_type RecSize;
		mq.receive(&m_ReceivedMsg, m_DefaultMaxMsgLen, RecSize, Priority);
		return m_ReceivedMsg;
	}  
	catch(interprocess_exception &ex){  
		message_queue::remove(m_DefaultMsgQueName);  
		std::cout << ex.what() << std::endl;  
		return 0;
	}
}

//******************************************************************
//FUNCTION:
template <typename T>
T CMsgQue<T>::dumpReceiveMsg(const char* vMsgQueName)
{  
	try{
		message_queue mq(open_only, vMsgQueName);  
		unsigned int Priority;  
		message_queue::size_type RecSize;
		mq.receive(&m_ReceivedMsg, m_DefaultMaxQueLen, RecSize, Priority);
		return m_ReceivedMsg;
	}  
	catch(interprocess_exception &ex){  
		message_queue::remove(vMsgQueName);  
		std::cout << ex.what() << std::endl;  
		return 0;
	}  
}

//******************************************************************
//FUNCTION:
template<typename T>
void CMsgQue<T>::removeMsgQue(const char* vMsgQueName)
{
	message_queue::remove(vMsgQueName);
}

//******************************************************************
//FUNCTION:
template<typename T>
void CMsgQue<T>::removeMsgQue()
{
	message_queue::remove(m_DefaultMsgQueName);
}