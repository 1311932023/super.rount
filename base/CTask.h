/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	message list 线程间消息列表，可依次执行push_back的Vtask消息
 *
 */
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