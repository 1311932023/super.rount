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