/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	memory pool
 *
 */
#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__
#include <array>
#include "Klist.h"

namespace ashan
{
	namespace __inner
	{		
		template<class _Type>
		void* create(_Type& _obj);	
		template<class _Type>
		void destroy(_Type& _obj, char* _ptr);		
		template<class _Type>
		void clear(_Type& _obj);		
	}
	template<size_t... _Size>
	class Mempool;

	template<size_t _Size>
	class Mempool<_Size>
	{
		Klist<std::array<char, _Size>> m_data;
	public:
		virtual ~Mempool<_Size>() { __inner::clear(m_data); }
		void* create(size_t s)
		{
			if (s <= _Size)
				return __inner::create(m_data);
			return malloc(s);
		}
		void destroy(size_t s, void* ptr)
		{
			if (s <= _Size)
				return __inner::destroy(m_data, (char*)ptr);
			free(ptr);
		}
	};
	template<size_t _Size, size_t... _Res>
	class Mempool<_Size, _Res...> : public Mempool<_Res...>
	{
		Klist<std::array<char, _Size>> m_data;
	public:
		~Mempool<_Size, _Res...>() { __inner::clear(m_data); }
		void* create(size_t s)
		{
			if (s <= _Size)
				return __inner::create(m_data);
			return Mempool<_Res...>::create(s);
		}
		void destroy(size_t s, void* ptr)
		{
			if (s <= _Size)
				return __inner::destroy(m_data, (char*)ptr);
			return Mempool<_Res...>::destroy(s, ptr);
		}
	};	
	namespace __inner
	{
		template<class _Type>
		void* create(_Type& _obj)
		{
			if (_obj.empty())
				return (_obj.emplace())->m_data.data();
			auto p = _obj.front();
			_obj.erase(p);
			return p->m_data.data();
		}
		template<class _Type>
		void destroy(_Type& _obj, char* _ptr)
		{
			const auto _shift = ((size_t)&(((decltype(_obj.front()))0)->m_data));
			_obj.push_back(decltype(_obj.front())(_ptr - _shift));
		}
		template<class _Type>
		void clear(_Type& _obj)
		{
			while (!_obj.empty())
			{
				auto p = _obj.front();
				_obj.erase(p);
				delete p;
			}
		}
	}
}
#endif

