#ifndef __THREAD_H__
#define __THREAD_H__
#include <list>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "VTask.h"


class CThreadTask
{
	enum state
	{
		e_running,
		e_stop,
		e_terminal,		
	};	
public:
	CThreadTask();
	virtual ~CThreadTask();	
	void push_task(VTask* cmd);
	void stop();		
private:	
	void run();	
	std::list<VTask*> m_list;		
	std::atomic_int m_state;
	std::thread m_thd;
	std::mutex m_mutex;
	std::condition_variable m_cond;
	
};
#endif
