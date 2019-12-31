/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	共享内存
 *
 */
#ifndef __KMEMORY_H__
#define __KMEMORY_H__

class KMemory
{
	char* m_Buffer = NULL;
	size_t m_Size = 0;
public:
	KMemory(size_t _size);
	virtual ~KMemory();
	char* data() { return m_Buffer; }
	size_t size() { return m_Size; }

};

#endif