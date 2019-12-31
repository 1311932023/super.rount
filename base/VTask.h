/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	用于message list 执行的对象 纯虚父类
 *
 */
#ifndef __VTASK_H__
#define __VTASK_H__
#include <list>
#include <mutex>
#include <atomic_int>

class VTask 
{
	int m_tag = 0;
public:
    VTask(){}
	VTask(int _tag) { m_tag = _tag; }
	int tag()const { return m_tag; }
    virtual ~VTask(){}
	virtual void operator()(void*) = 0;
};

class VTaskEx
{
protected:
	enum E_TASK_STATUS	{ e_running, e_terminating, e_terminated,};		
	std::list<VTask*> m_list;
	std::mutex m_mutex;
	std::atomic_int m_status = e_running;
public:
	virtual ~VTaskEx() 
	{
		stop();
		while (m_status != e_terminated)
			usleep(1000);
	}
	virtual void notify_task() = 0;
	virtual void wait_task(std::unique_lock<std::m_mutex>&) = 0;	
public:
	void push_task(VTask* _task) 
	{
		{
			std::unique_lock<decltype(m_mutex)> _lock(m_mutex);
			m_list.push_back(_task);
		}
		notify_task();
	}
	void run_task()
	{
		do {
			decltype(m_list) _list; 
			{
				std::unique_lock<decltype(m_mutex)> _lock(m_mutex);
				if (m_list.empty())
					wait_task(_lock);
				_list.swap(m_list);
			}
			for (auto it : _list)
				(*it)();
		} while (m_status == e_running);
		m_status = e_terminated;
	}
	void stop_task()
	{
		m_status = e_terminating;
		notify_task();
	}
};
#endif
