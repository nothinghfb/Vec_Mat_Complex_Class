#pragma once
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

template<typename TR,typename TI>
class HFB_Complex
{
private:
	TR real;
	TI imag;
public:
	// 设值 取值
	void setReal(TR real);
	TR getReal();
	void setImag(TI imag);
	TI getImag();
	void setValue(TR real, TI imag);
	HFB_Complex<TR, TI> clone();

	// 复数 加减乘除
	void add(HFB_Complex<TR, TI > obj);
	void sub(HFB_Complex<TR, TI> obj);
	void multi(HFB_Complex<TR, TI> obj);
	void divide(HFB_Complex<TR, TI> obj);

	// 取模
	auto mod();
public:
	HFB_Complex(TR real = 0,TI imag = 0);
	~HFB_Complex();
};

template<typename TR, typename TI>
auto HFB_Complex<TR, TI>::mod()
{
	double rt = 0.;
	rt =  sqrtl((double)real*real + (double)imag*imag);
	return rt;
}

template<typename TR, typename TI>
void HFB_Complex<TR, TI>::multi(HFB_Complex<TR, TI> obj)
{
	TR r = this->real;
	TI i = this->imag;

	this->real = r*obj.getReal() - i*obj.getImag();
	this->imag = r*obj.getImag() - i*obj.getReal();
}

template<typename TR, typename TI>
inline void HFB_Complex<TR, TI>::divide(HFB_Complex<TR, TI> obj)
{

}

template<typename TR, typename TI>
void HFB_Complex<TR, TI>::sub(HFB_Complex<TR, TI> obj)
{
	this->real -= obj.getReal();
	this->imag -= obj.getImag();
}

template<typename TR, typename TI>
void HFB_Complex<TR, TI>::add(HFB_Complex<TR, TI > obj)
{
	this->real += obj.getReal();
	this->imag += obj.getImag();
}

template<typename TR, typename TI>
HFB_Complex<TR, TI> HFB_Complex<TR, TI>::clone()
{
	HFB_Complex<TR, TI> rt(this->getReal(),this->getImag());
	return rt;
}

template<typename TR, typename TI>
void HFB_Complex<TR, TI>::setValue(TR real, TI imag)
{
	this->setImag(imag);
	this->setReal(real);
}

template<typename TR, typename TI>
HFB_Complex<TR, TI>::HFB_Complex(TR real /*= 0*/, TI imag /*= 0*/)
{
	setReal(real);
	setImag(imag);
}


template<typename TR, typename TI>
HFB_Complex<TR, TI>::~HFB_Complex()
{

}


template<typename TR, typename TI>
TI HFB_Complex<TR, TI>::getImag()
{
	return this->imag;
}

template<typename TR, typename TI>
void HFB_Complex<TR, TI>::setImag(TI imag)
{
	this->imag = imag;
/*	return true;*/
}

template<typename TR, typename TI>
TR HFB_Complex<TR, TI>::getReal()
{
	return this->real;
}

template<typename TR, typename TI>
void HFB_Complex<TR, TI>::setReal(TR real)
{
	this->real = real;
/*	return true;*/
}

