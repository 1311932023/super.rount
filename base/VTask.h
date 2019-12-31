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
	enum E_TASK_STATUE	{ e_running, e_terminating, e_terminated,};		
	std::list<VTask*> m_list;
	std::mutex m_mutex;
	std::atomic_int m_statue = e_running;
public:
	virtual ~VTaskEx() 
	{
		stop();
		while (m_statue != e_terminated)
			usleep(1000);
	}
	virtual void notify_task() = 0;
	virtual void wait_task() = 0;	
public:
	void push_task(VTask* _task) 
	{
		{
			std::lock_guard<decltype(m_mutex)> _lock(m_mutex);
			m_list.push_back(_task);
		}
		notify_task();
	}
	void run_task()
	{		
		do
		{
			decltype(m_list) _list;
			{
				std::lock_guard<decltype(m_mutex)> _lock(m_mutex);
				if (m_list.empty())
					wait_task();
				_list.swap(m_list);
			}
			for (auto it : _list)			
				(*it)();			
		}while(m_state == e_running);
		m_state = e_terminated;
	}
	void stop_task()
	{
		m_statue = e_terminating;
		notify_task();
	}
};
#endif
