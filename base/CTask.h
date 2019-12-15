#ifndef __CTASK_H_2019_12_08__
#define __CTASK_H_2019_12_08__
#include <unistd.h>
#include <atomic>
#include <list>
#include <mutex>
#include <condition_variable>
#include "VTask.h"

class CTask
{
	enum state
	{
		e_running,
		e_stop,
		e_terminal,
	};
	std::list<VTask*> m_list;
	std::atomic_int m_state;
	std::mutex m_mutex;
	std::condition_variable m_cond;
public:
	virtual ~CTask();
	void push_task(VTask* cmd);
	void stop();
	void run();
};
#endif