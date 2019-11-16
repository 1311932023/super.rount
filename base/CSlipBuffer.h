#ifndef __CSLIPBUFFER_H__
#define __CSLIPBUFFER_H__
#include "CSafeBuffer.h"

template<class _Type, size_t _Size>
class CSlipBuffer : CSafeBuffer<_Type, _Size>
{
	size_t m_Pos;
	typedef CSafeBuffer<_Type, _Size> base;
public:
	CSlipBuffer() : m_Pos(0) {}
	_Type* data()const { return base::data() + m_Pos; }
	int size() { return base::size() - m_Pos; }
	void push_back(const _Type* other, size_t iSize)
	{
		if (base::size() + iSize >= base::max())
		{
			if (m_Pos > 0)
			{
				base::pop_front(m_Pos);
				m_Pos = 0;
			}
		}
		return base::push_back(other, iSize);
	}
	void pop_front(size_t iSize)
	{
		m_Pos += iSize;
		if (m_Pos >= base::size())
		{
			base::pop_front(base::size());
			m_Pos = 0;			
		}
	}
	bool empty() { return base::empty(); }
	_Type* at(size_t pos)const
	{		
		if (m_Pos + pos < base::size())
			return base::data() + m_Pos + pos;
		throw("at error pos");
	}
	int max()const 
	{
		assert(m_Pos <= base::max());
		return base::max() - m_Pos;
	}
	void reserve(size_t c) {
		if (c < max())
			return ;
		base::reserve(m_Pos + c); 
	}
	_Type* end() { return base::data() + base::size(); }		
	void clear() { pop_front(size()); }
};

#endif
