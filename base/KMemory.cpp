/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	共享内存
 *
 */
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "KMemory.h"

KMemory::KMemory(size_t _size) :m_Size(_size)
{
	assert(m_Size > 0);
	m_Buffer = (char*)mmap(NULL, m_Size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (m_Buffer == NULL)
	{
		throw("mmap error");
	}
}

KMemory::~KMemory()
{	
	if (m_Buffer != NULL)
	{
		munmap(m_Buffer, m_Size);
	}	
}
