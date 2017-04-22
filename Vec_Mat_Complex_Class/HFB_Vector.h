#pragma once
#include "stdafx.h"

enum IDETIFIER
{
	BisicType = 0,
	ComplexType = 1
};

//	Vector 数据存储结构体
template<typename BisicType> struct  HFB_Vector_BisicType
{
	BisicType *data = nullptr;
	unsigned int length = 0;
};

template<typename ComplexType> struct  HFB_Vector_ComplexType
{
	ComplexType *data = nullptr;
	unsigned int length = 0;
};


template<class T>
class HFB_Vector
{
private:
	HFB_Vector_BisicType<T> *BisicData;
	HFB_Vector_ComplexType<T> *ComplexTypeData;
	IDETIFIER Id;
	char *classType;
public:
	unsigned initData(unsigned int len = 0);
	unsigned getLength();
	T at(unsigned index);
	bool setValueAt(T t,unsigned index);
	bool setValueAts(const T* values,unsigned* index, const unsigned int indexLen);
	T getValueAt(unsigned index);
	T* getValueAts(unsigned* index, const unsigned int indexLen);

	bool clearAt(unsigned index);
	bool clearAts(unsigned *index, const unsigned int indexLen);
	bool clearAll();


public:
	HFB_Vector(int mode = 0);
	HFB_Vector(const unsigned int len,int mode  = 0);

	~HFB_Vector();
};

template<class T>
bool HFB_Vector<T>::clearAll()
{

}

template<class T>
bool HFB_Vector<T>::clearAts(unsigned *index, const unsigned int indexLen)
{

}

template<class T>
bool HFB_Vector<T>::clearAt(unsigned index)
{

}

template<class T>
T* HFB_Vector<T>::getValueAts(unsigned* index, const unsigned int indexLen)
{
	T *rt;
	if (!Id && this->BisicData && ( indexLen < this->BisicData->length && indexLen >= 0 ))
	{
		rt = new T [ indexLen ];
		for (unsigned i = 0;i < indexLen;++i)
		{
			rt [ i ] = this->BisicData [ index [ i ] ];
		}
		return rt;
	}
	else if (Id && this->ComplexTypeData && ( indexLen < this->ComplexTypeData->length && indexLen >= 0 ))
	{
		rt = new T [ indexLen ];
		for (unsigned i = 0;i < indexLen;++i)
		{
			rt [ i ] = this->ComplexTypeData [ index [ i ] ];
		}
		return rt;
	}
	return nullptr;
}

template<class T>
T HFB_Vector<T>::getValueAt(unsigned index)
{
	if (!Id && this->BisicData && ( index < this->BisicData->length && index >= 0 ))
	{
		return this->BisicData [ index ];
	}
	else if (Id && this->ComplexTypeData && ( index < this->ComplexTypeData->length && index >= 0 ))
	{
		return this->ComplexTypeData [ index ];
	}
	return false;
}

template<class T>
bool HFB_Vector<T>::setValueAts(const T* values, unsigned* index, const unsigned int indexLen)
{
	if (!T)
		return false;
	if (!Id && this->BisicData && ( index < this->BisicData->length && index >= 0 ))
	{
		for (unsigned i = 0;i < indexLen;++i)
		{
			this->BisicData [ index[i] ] = values[i];
		}
		return true;
	}
	else if (Id && this->ComplexTypeData && ( index < this->ComplexTypeData->length && index >= 0 ))
	{
		for (unsigned i = 0;i < indexLen;++i)
		{
			this->ComplexTypeData [ index [ i ] ] = values [ i ];
		}
		return true;
	}
	return false;
}

template<class T>
bool HFB_Vector<T>::setValueAt(T t, unsigned index)
{
	if (!Id && this->BisicData && (index < this->BisicData->length && index >= 0))
	{
		this->BisicData [ index ] = t;
		return true;
	}
	else if (Id && this->ComplexTypeData && ( index < this->ComplexTypeData->length && index >= 0 ))
	{
		this->ComplexTypeData [ i ] = t;
		return true;
	}
	return false;
}

template<class T>
T HFB_Vector<T>::at(unsigned index)
{
	switch (this->Id)
	{
		case BisicData：
		{
			if (!this->BisicData) 
			return this->BisicData [ index ];
			break;
		}
		case ComplexTypeData：
		{
			if (!this->ComplexTypeData) 
			return this->ComplexTypeData [ index ];
	    	break;
		}
		default; 
		break;
	}
	return 0;
}

template<class T>
unsigned HFB_Vector<T>::getLength()
{
	switch (this->Id)
	{
		case BisicType:
		{
			if (!this->BisicData) return this->BisicData->length;
			break;
		}
		case ComplexType:
		{
			if (!this->ComplexTypeData) return this->ComplexTypeData->length;
			break;
		}
	}
	return 0;
}

template<class T>
unsigned HFB_Vector<T>::initData(unsigned int len /*= 0*/)
{
	if (len == 0)
	{
		this->BisicData = nullptr;
		this->ComplexTypeData = nullptr;
		return 0;
	}
	else
	{
		switch (this->Id)
		{
			case IDETIFIER.BisicType:
			{
				this->ComplexTypeData = nullptr;
				this->BisicData = new HFB_Vector_BisicType<T>;
				this->BisicData->length = len;
				this->BisicData->data = new T [ len ];
				this->classType = new char;
				this->classType = 'B';

				break;
			}
			case IDETIFIER.ComplexType:
			{
				this->BisicData = nullptr;
				this->ComplexTypeData = new HFB_Vector_ComplexType<T>;
				this->ComplexTypeData->length = len;
				this->ComplexTypeData->data = new T [ len ];
				this->classType = new char;
				this->classType = 'C';
				break;
			}
			default:
			{
				this->Id = BisicType;
				this->BisicData = nullptr;
				this->ComplexTypeData = nullptr;
				this->classType = nullptr;
				break;
			}
		}
	}
	return len;
}

template<class T>
HFB_Vector<T>::HFB_Vector(const unsigned int len, int mode /*= 0*/)
{
	this->Id = mode;
	this->initData(len);
}

template<class T>
HFB_Vector<T>::HFB_Vector(int mode /*= 0*/)
{
	this->Id = mode;
	this->initData();
}


