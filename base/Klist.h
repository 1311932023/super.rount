/*
 *	Copyright (c) 2019-2020 Zhao YunShan(93850592@qq.com)
 *	All rights reserved.
 *	仿linux内核的双向链表
 *
 */
#ifndef __KLIST_H__
#define __KLIST_H__
#include <stddef.h>

namespace ashan
{
	template<class _Type>
	class Klist
	{
		struct node_
		{
			node_* m_prev = NULL;
			node_* m_next = NULL;		
			operator node_*() { return this; }
		};
		template<class _T>
		struct node : public node_
		{
			_T m_data;
			template<class... _Args>
			node(_Args&&... _args) : m_data(std::forward<_Args>(_args)...){}
			void* operator new(size_t s)
			{
				auto p = malloc(s);
				if (p != NULL)
					return p;
				throw("malloc error");
			}
			void operator delete(void* ptr) { free(ptr); }
		};
		node<int> m_node;
		typedef node<_Type> node_t;
	public:
		Klist()
		{
			m_node.m_next = m_node.m_prev = m_node;
			m_node.m_data = 0;
		}
		void push_front(node_t *new_) { __list_add(new_, m_node, m_node.m_next); }
		void push_back(node_t *new_) { __list_add(new_, m_node.m_prev, m_node); }
		void erase(node_t *old) { __list_del(old->m_prev, old->m_next); }
		void replace(node_t *old, node_t *new_) { __replace(old, new_); }
		bool empty()const { return m_node.m_data == 0; }
		int size()const { return m_node.m_data; }
		node_* begin() { return m_node.m_next; }
		node_* end() { return m_node; }
		node_t* front() { return (node_t*)m_node.m_next; }
		node_t* back() { return (node_t*)m_node.m_prev; }
		bool is_member(node_t* old)const
		{
			for (auto n = begin(); n != end(); n = n->m_next)
				if (n == old)
					return true;
			return false;
		}
		template<class... _Args>
		void emplace_back(_Args&&... _args)
		{
			push_back(new node_t(std::forward<_Args>(_args)...));
		}
		template<class... _Args>
		void emplace_front(_Args&&... _args)
		{
			push_front(new node_t(std::forward<_Args>(_args)...));
		}
		template<class... _Args>
		node_t* emplace(_Args&&... _args)
		{
			return new node_t(std::forward<_Args>(_args)...);
		}
	private:
		void __list_add(node_ *cur, node_ *prev, node_ *next)
		{
			prev->m_next = next->m_prev = cur;
			cur->m_next = next;
			cur->m_prev = prev;
			m_node.m_data++;
		}
		void __list_del(node_ * prev, node_ * next)
		{
			next->m_prev = prev;
			prev->m_next = next;
			m_node.m_data--;
		}
		void __replace(node_ *old, node_ *new_)
		{
			new_->m_next = old->m_next;
			new_->m_prev = old->m_prev;
			new_->m_next->m_prev = new_->m_prev->m_next = new_;
		}
	};
}
#endif

