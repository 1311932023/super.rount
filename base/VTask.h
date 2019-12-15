/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	用于message list 执行的对象 纯虚父类
 *
 */
#ifndef __VTASK_H__
#define __VTASK_H__

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

#endif
