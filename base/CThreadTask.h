#ifndef __CTHREADTASK_H__
#define __CTHREADTASK_H__
#include <thread>
#include "CTask.h"

class CThreadTask : public CTask
{
	typedef CTask _Upper;
	std::thread m_thd;
public:
	CThreadTask() :m_thd(&_Upper::run, this)
	{
		m_thd.detach();
	}	
};
#endif
