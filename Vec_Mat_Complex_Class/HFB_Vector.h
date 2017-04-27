#pragma once
#include "stdafx.h"

template<class T> class HFB_Vector
{
private:
	T *data;
	unsigned int length;
	unsigned int currentNum;
	int(*compareFun)( const T left, const T right );
public:
//	���ȴ�С
	void setLength(unsigned int length);
	unsigned int getLength();
	unsigned int size();
	unsigned int getCurrentNum();//ȡ��ǰ��������

//	��ֵ
	void setValue(T obj,unsigned int local);//��ָ��λ����һ��ֵ
	void setValue(const T* const obj, unsigned int *index, unsigned int num);//��ָ���Ķ��λ������ֵ����num��
	void setValue(const T* const obj, unsigned int num, unsigned int beginIndex = 0);//��beginIndex��ʼ����������num��ֵ
/*	T& operator= (const T& obj);*/


//	ȡֵ
	T at(unsigned int local);//ȡһ��ֵ
	T getValue(unsigned int local);//ȡһ��ֵ
	T *getValue(const unsigned int *index, unsigned int num);//ȡ���±�Ϊindex��Ԫ�ص�Num��ֵ
	T *getValue(unsigned int beginIndex, unsigned int num);//ȡ����beginIndex��ʼ��num��Ԫ��ֵ

//	�ж��Ƿ����Ԫ�ش��������������±�
	bool contains(T a,int (*compareFun)(const T left,const T right) = nullptr);
	unsigned contains(const HFB_Vector & obj, int *num = nullptr, unsigned int *index = nullptr, const int(*const compareFun)( const T left, const T right ) = nullptr);

//	��ȡ����ָ��
	T *getDataPtr();
	const T * getDataPtr() const;

//	����Ԫ��
	void push_front(const T obj);//��ǰ������Ԫ�ء�
	void push_back(const T obj);//��ĩβ����Ԫ�ء�
	void insert(const T obj, unsigned int index);//��ָ��λ�ú������Ԫ��

//	ɾ��Ԫ��
	void pop_front();//��ǰ��ɾ��Ԫ��
	void pop_back();//��ĩβɾ��Ԫ��
	void drop(unsigned int index);//ɾ����indexλ�õ�Ԫ��
	void drop(unsigned int beginIndex, unsigned int num);//��beginIndex��ʼɾ��num��Ԫ��
	void drop(unsigned int *index, unsigned int num);//ɾ��index���±��num��Ԫ��
	void dropAll();//ɾ��ȫ��Ԫ��.

//	��������Ĵ洢��Ϣ
	void clear();

//	����ת��
//	template<typename GT> operator GT();

//	���ñȽϺ��� 
	void setCompareFun(int (*compareFun)(const T left,const T right) = nullptr);
	void* getCompareFun();//////////////////////////////////

//	����
	void sort(int mode = 0,const int (* const compareFun)( const T left, const T right ) = nullptr);

//	�����ϲ�
	HFB_Vector join(HFB_Vector obj, int mode = 0);//������obj�ϲ�������mode = 0,����ͬԪ�أ�=1 ������ͬԪ��
//	HFB_Vector& operator+(const HFB_Vector& left, const HFB_Vector& right);//������right׷�ӵ�left��ĩβ��
//	HFB_Vector& operator-(const HFB_Vector& left, const HFB_Vector& right);//������left�г�ȥright�еİ�����Ԫ�ء�

//	�±�����
	T& operator[] (unsigned int index);

public:
	HFB_Vector(unsigned int len = 0,T * dataPtr = nullptr);
	HFB_Vector(const HFB_Vector& obj);//�������ƹ��캯��
	~HFB_Vector();

};

template<class T>
void HFB_Vector<T>::clear()
{
	this->currentNum = 0;
	this->length = 0;
	if (!this->data) delete [] this->data;
}

template<class T>
void HFB_Vector<T>::dropAll()
{
	this->currentNum = 0;
	insert(!this->data) delete []this->data;
}

template<class T>
void HFB_Vector<T>::drop(unsigned int *index, unsigned int num)
{
	if (index && num > 0)
	{
		for (unsigned int i = 0;i < num)
		{
			this->drop(index [ i ]);
		}
	}
}

template<class T>
void HFB_Vector<T>::drop(unsigned int beginIndex, unsigned int num)
{
	if (beginIndex >= 0 && beginIndex < this->length)
	{
		for (unsigned int i = 0;i < num;++i)
		{
			if (i + beginIndex < this->length)
			{
				this->drop(beginIndex + i);
			}
		}
	}
}

template<class T>
void HFB_Vector<T>::drop(unsigned int index)
{
	this->length--;
	this->currentNum--;
	if (this->length > 0)
	{
		T * newData = new T [ this->length ];
		for (unsigned int i = 0,j = 0;i < this->length + 1;++i)
		{
			newData [ j++ ] = this->data[i];
		}
		this->dropAll();
		this->data = newData;
	}
	else
	{
		this->length = 0;
		this->currentNum = 0;
		this->data = nullptr;
	}
}

template<class T>
void HFB_Vector<T>::pop_back()
{
	if (length-1 > 0)
	{
		T* tem = new T [ this->length ];
		memcpy(tem, this->data, sizeof(T)*this->length);
		this->dropAll();
		this->data = new T [ --this->length ];
		this->currentNum--;
		for (unsigned int i = 0;i < this->length;++i)
		{
			this->data [ i ] = tem [ i ];
		}
		delete [] tem;
	}
	else
	{
		this->data = nullptr;
		this->length = 0;
		this->currentNum = 0;
	}
}

template<class T>
void HFB_Vector<T>::pop_front()
{
	if (this->length - 1 > 0)
	{
		T *tem = new T [ this->length - 1 ];
		this->currentNum--;
		for (unsigned int i = 1;i < this->length;++i)
		{
			tem [ i - 1 ] = this->data [ i ];
		}
		this->dropAll();
		this->data = tem;
	}
	else
	{
		this->length = 0;
		this->currentNum = 0;
		this->data = nullptr;
	}
}

template<class T>
void HFB_Vector<T>::insert(const T obj, unsigned int index)
{
	if (this->length >= 0 && this->length > index)
	{
		if (index == 0)
		{
			this->push_front(obj);
		}
		else if (index == this->length-1)
		{
			this->push_back(obj);
		}
		else
		{
			T *tem = new T [ this->length + 1 ];
			this->length++;
			this->currentNum++;
			for (unsigned int = 0; i < index;++i)
			{
				tem [ i ] = this->data [ i ];
			}
			tem [ index ] = obj;
			for (unsigned int i = index + 1;i < this->length;++i)
			{
				tem [ i ] = this->data [ i - 1 ];
			}
			this->dropAll();
			this->data = tem;
		}
	}
}

template<class T>
void HFB_Vector<T>::push_back(const T obj)
{
	if (this->length > 0)
	{
		T *tem = new T [ this->length + 1 ];
		memcpy(tem, this->data, size(T)*this->length);
		tem [ this->length++ ] = obj;
		this->currentNum++;
		this->dropAll();
		this->data = tem;
	}
	else
	{
		this->length++;
		this->currentNum++;
		this->data = new T [ this->length ];
		this->data [ this->length - 1 ] = obj;
	}
}

template<class T>
void HFB_Vector<T>::push_front(const T obj)
{
	if (this->length > 0)
	{
		T *tem = new T [ this->length + 1 ];
		memcpy(tem + 1, this->data, sizeof(T)*this->length);
		this->length++;
		tem [ 0 ] = obj;
		this->dropAll();
		this->data = tem;
	}
	else
	{
		this->length++;
		this->currentNum++;
		this->data = new T [ this->length ];
		this->data [ this->length - 1 ] = obj;
	}
}

template<class T>
const T * HFB_Vector<T>::getDataPtr() const
{
	return this->data;
}

template<class T>
T * HFB_Vector<T>::getDataPtr()
{
	return this->data;
}

template<class T>
unsigned HFB_Vector<T>::contains(const HFB_Vector & obj, int *num /*= nullptr*/, unsigned int *index /*= nullptr*/, const int(*const compareFun)( const T left, const T right ) /*= nullptr*/)
{
	if (!num) {
		num = new int;
	}
	*num = 0;
	if (this->length <= 0 || obj.getLength() <= 0)
	{
		return -1;
	}
	if (this->length > 0 && obj.getLength() > 0)
	{
		for (unsigned int i = 0; i < obj.getLength();++i)
		{
			if (this->contains(obj.getValue(i)))
			{
				*num++;
			}
		}
		if (!index)
		{
			index = new unsigned int [ *num ];
		}
		else
		{
			delete []index;
		}
		for (unsigned int i = 0,j = 0; i < obj.getLength();++i)
		{
			if (this->contains(obj.getValue(i)))
			{
				index [ j++ ] = i;
			}
		}
	}
	return *num;
}

template<class T>
bool HFB_Vector<T>::contains(T a, int(*compareFun)( const T left, const T right ) /*= nullptr*/)
{
	if (!compareFun)
	{
		for (unsigned int i = 0;i < this->length;++i)
		{
			if (this->data [ i ] == a)
				return true;
		}
	}
	else
	{
		for (unsigned int i = 0;i < this->length;++i)
		{
			if (compareFun(a, this->data [ i ]) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

template<class T>
T * HFB_Vector<T>::getValue(unsigned int beginIndex, unsigned int num)
{
	if (this->length <= 0 || num <= 0)
	{
		return nullptr;
	}
	T *rt = new T [ num ];
	for (unsigned int i = beginIndex;i < num; ++i)
	{
		rt [ i - beginIndex ] = this->data [ i ];
	}
	return rt;
}

template<class T>
T * HFB_Vector<T>::getValue(const unsigned int *index, unsigned int num)
{
	if (this->length <= 0 || num <= 0 || !index)
	{
		return nullptr;
	}

	T *rt = new T [ num ];
	for (unsigned int i = 0; i < num;++i)
	{
		rt [ i ] = this->getValue(index [ i ]);
	}
	return rt;
}

template<class T>
T HFB_Vector<T>::getValue(unsigned int local)
{
	if (local < 0 || local >= length)
	{
		return (T)0;
	}
	return *(this->data + local);
}

template<class T>
T HFB_Vector<T>::at(unsigned int local)
{
	return this->getValue(local);
}

template<class T>
void HFB_Vector<T>::setValue(const T* const obj, unsigned int num, unsigned int beginIndex /*= 0*/)
{
	if (beginIndex >= this->length|| !obj || num <= 0 ) return;
	for (unsigned int i = 0;i+beginIndex < this->length && i < num;++i)
	{
		this->data [ beginIndex + i ] = obj [ i ];
	}
}

template<class T>
void HFB_Vector<T>::setValue(const T* const obj, unsigned int *index, unsigned int num)
{
	if (!index || !obj || num <= 0) return;
	for (unsigned int i = 0;i < num;++i)
	{
		if (index [ i ] < this->length)
		{
			this->setValue(obj [ i ], index [ i ]);
		}
	}
}

template<class T>
void HFB_Vector<T>::setValue(T obj, unsigned int local)
{
	if ( !this->data || local < 0 && local >= this->length) return;
	*( this->data + local ) = obj;
}

template<class T>
unsigned int HFB_Vector<T>::getCurrentNum()
{
	return this->currentNum;
}

template<class T>
unsigned int HFB_Vector<T>::size()
{
	return this->length;
}

template<class T>
unsigned int HFB_Vector<T>::getLength()
{
	this->length;
}

template<class T>
void HFB_Vector<T>::setLength(unsigned int length)
{
	this->length = length;
}

// template<typename GT>
// HFB_Vector::operator GT()
// {
// /*	return (GT)(data);*/
// }

template<class T>
void* HFB_Vector<T>::getCompareFun()
{
	return this->compareFun;
}

template<class T>
void HFB_Vector<T>::setCompareFun(int(*compareFun)( const T left, const T right ) /*= nullptr*/)
{
	this->compareFun = compareFun;
}

template<class T>
void HFB_Vector<T>::sort(int mode /*= 0*/, const int(*const compareFun)( const T left, const T right ) /*= nullptr*/)
{
	if (!compareFun) compareFun = this->compareFun;
	if (!compareFun)
	{
		if (!mode)
		{
			// �������� 
		}
		else
		{
			//��������
		}
	}
	else
	{
		if (!mode)
		{
			// �������� ��compareFun
		}
		else
		{
			//�������� ��compareFun
		}
	}
}

template<class T>
HFB_Vector<T> HFB_Vector<T>::join(HFB_Vector obj, int mode /*= 0*/)
{
	if (!mode)
	{
		if (this->data && obj.getDataPtr())
		{
			T *cur = new T [ this->length ];
			memcpy(cur, this->data, sizeof(T)*this->length);
			unsigned int oldLen = this->length;
			this->length += obj.getLength();
			this->currentNum += obj.getCurrentNum();
			this->dropAll();
			this->data = new T [ this->length ];
			memcpy(this->data, cur, sizeof(T)*( oldLen ));
			for (unsigned int i = 0;i < obj.getLength();++i)
			{
				this->data [ oldLen + i ] = obj.getValue(i);
			}
		}
	}
	else
	{
		if (this->data && obj.getDataPtr())
		{
			HFB_Vector<T> objT(obj);
			unsigned int num;
			unsigned int *index;
			if (objT->contains(*this,num, index, this->compareFun))
			{
				objT.drop(index, num);
			}
			this->join(objT);
		}
	}
	return *this;
}

// template<class T>
// HFB_Vector& HFB_Vector<T>::operator+(const HFB_Vector& left, const HFB_Vector& right)
// {
// 	HFB_Vector<T> rt(left);
// 	return rt.join(right);
// }

// template<class T>
// HFB_Vector& HFB_Vector<T>::operator-(const HFB_Vector& left, const HFB_Vector& right)
// {
// 	HFB_Vector<T> rt(left);
// 	unsigned len = right.getLength();
// 	unsigned int *index;
// 	unsigned int num;
// 	if (rt.contains(right,num, index, this->compareFun))
// 	{
// 		rt.drop(index, num);
// 	}
// 	return rt;
// }


template<class T>
T& HFB_Vector<T>::operator[](unsigned int index)
{
	return getValue(index);
}

template<class T>
HFB_Vector<T>::HFB_Vector(unsigned int len /*= 0*/, T * dataPtr /*= nullptr*/)
{
	if (len > 0 && dataPtr)
	{
		this->length = len;
		this->data = new T [ len ];
		memcpy(this->data, dataPtr, sizeof(T)*len);
	}
	else
	{
		this->length = 0;
		this->data = nullptr;
	}
}

template<class T>
HFB_Vector<T>::HFB_Vector(const HFB_Vector& obj)
{
	this->length = obj.getLength();
	this->currentNum = obj.getCurrentNum();
	this->compareFun;
	if (this->length > 0)
	{
		this->data = new T [ length ];
		memcpy(this->data, obj.getDataPtr(), sizeof(T)*length);
	}
	else
	{
		this->data = nullptr;
	}
}

template<class T>
HFB_Vector<T>::~HFB_Vector()
{
	this->clear();
}
