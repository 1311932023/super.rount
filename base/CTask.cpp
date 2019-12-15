#include "CTask.h"

CTask::~CTask()
{
	while (m_state != e_terminal)
	{
		stop();
		usleep(100);
	}
}
void CTask::run()
{
	m_state = e_running;
	do
	{
		std::list<VTask*> _list;
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			if (m_list.empty())
			{
				m_cond.wait(lock);
			}
			_list.swap(m_list);
		}
		for (auto it = _list.begin(); it != _list.end(); ++it)
		{
			VTask* notify = *it;
			(*notify)(this);
			delete notify;
		}
	} while (m_state == e_running);
	m_state = e_terminal;
}
void CTask::stop()
{
	if (m_state == e_running)
	{
		m_state = e_stop;
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.notify_one();
	}
}
void CTask::push_task(VTask* task)
{
	if (task != NULL)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_list.push_back(task);
		m_cond.notify_one();
	}
}
