/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	
 *	初始化时在栈上分配内存，超过初始化的内存后动态生成的内存
 *
 */

#ifndef __CSAFEBUFFER_H__
#define __CSAFEBUFFER_H__
#include <string.h>
#include <stdlib.h>
#include <assert.h>

template<class _Type, size_t _Size>
class CSafeBuffer
{
public:		
	CSafeBuffer() : m_max(_Size), m_size(0), m_buffer(m_fix_buffer) {}
	CSafeBuffer(const CSafeBuffer<_Type, _Size>& other) : m_buffer(m_fix_buffer)
	{
		*this = other;
	}
	~CSafeBuffer()
	{		
		if (m_buffer != m_fix_buffer)
			free(m_buffer);
	}
	void push_back(const _Type& other)
	{		
		if (m_size < m_max)
		{			
			m_buffer[m_size++] = other;
			return;
		}
		reserve(m_max * 2);
		m_buffer[m_size++] = other;		
	}
	void push_back(const _Type* other, size_t size)
	{
		if (m_size + size <= m_max)
		{
			memcpy(m_buffer + m_size, other, sizeof(_Type) * size);
			m_size += size;
			return;
		}
		size_t dmax = m_max > size ? m_max : size;
		reserve(dmax * 2);
		memcpy(m_buffer + m_size, other, sizeof(_Type) * size);
		m_size += size;
	}
	void pop_front(size_t size)
	{		
		if (size == m_size)
		{				
			m_size = 0;
		}
		else if (size < m_size)
		{
			m_size -= size;			
			memmove(m_buffer, m_buffer + size, m_size * sizeof(_Type));
		}
		else
		{
			throw("pop_front size is error");
		}
	}
	_Type& operator[](size_t pos)
	{
		if (pos < m_size)
			return m_buffer[pos];
		throw("beyond max size!");
	}
	_Type& operator[](size_t pos)const
	{
		if (pos < m_size)
			return m_buffer[pos];
		throw("beyond max size!");
	}		
	CSafeBuffer<_Type, _Size>& operator=(const CSafeBuffer<_Type, _Size>& other)
	{
		if (max() < other.size())
			reserve(other.max());
		m_size = 0;
		for (_Type* it = other.begin(); it != other.end(); ++it)
		{
			m_buffer[m_size++] = *it;
		}
		return *this;
	}	
	void reserve(size_t _max)
	{
		_Type* tmp_buffer = m_buffer;
		m_max = _max;
		m_buffer = (_Type*)malloc(sizeof(_Type) * m_max);
		if (m_buffer == NULL)
		{
			throw("malloc error");
		}
		if (m_size != 0)
		{
			memcpy(m_buffer, tmp_buffer, sizeof(_Type) * m_size);
		}
		if (tmp_buffer != m_fix_buffer)
		{
			free(tmp_buffer);
		}
	}
	void resize(size_t _size)
	{
		if (_size >= max())
		{
			reserve(_size);			
		}		
		m_size = _size;
	}
	void clear()
	{
		m_size = 0;
		if (m_buffer != m_fix_buffer)
		{
			free(m_buffer);
			m_buffer = m_fix_buffer;
			m_max = _Size;
		}
	}
	bool empty()const { return m_size == 0; }
	size_t max()const { return m_max; }
	size_t size()const { return m_size; }
	_Type* begin() { return m_buffer; }
	_Type* begin() const { return m_buffer; }
	_Type* end() { return m_buffer + m_size; }
	_Type* end() const { return m_buffer + m_size; }
	_Type* front() { return m_buffer; }
	_Type* front() const{ return m_buffer; }
	_Type* back() { 
		if (m_size == 0) return end();
		return end() - 1; 
	}
	_Type* back() const{
		if (m_size == 0) return end();
		return end() - 1;
	}	
	_Type* data()const { return m_buffer; }
private:
	size_t m_max;
	size_t m_size;	
	_Type* m_buffer;
	_Type m_fix_buffer[_Size];	
};

#endif