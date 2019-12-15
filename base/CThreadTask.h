/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	线程间消息列表，可依次执行push_back的Vtask消息
 *
 */
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
