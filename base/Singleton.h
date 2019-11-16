#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<class _Type>
class Singleton {
public:
	static _Type& ins(){		
		static _Type obj;
		return obj;
	}	
};
#endif
