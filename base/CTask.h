/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	message list 线程间消息列表，可依次执行push_back的Vtask消息
 *
 */
#ifndef __CTASK_H_2019_12_08__
#define __CTASK_H_2019_12_08__
#include <unistd.h>
#include <condition_variable>
#include "VTask.h"

class CTask : public VTaskEx
{
	std::condition_variable m_cond;
public:
	void wait_task(std::unique_lock<std:mutex>& _lock)
	{
		m_cond.wait(_lock);
	}
	void notify_task()
	{
		m_cond.notify_one();
	}
	
};
#endif