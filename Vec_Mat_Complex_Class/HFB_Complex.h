#pragma once

template<typename TR,typename TI>
class HFB_Complex
{
private:
	TR real;
	TI imag;
public:
	bool setReal(TR real);
	TR getTreal();
	bool setImag(TI imag);
	TI getImag();

public:
	HFB_Complex();
	~HFB_Complex();
};

template<typename TR, typename TI>
HFB_Complex<TR, TI>::~HFB_Complex()
{

}

template<typename TR, typename TI>
HFB_Complex<TR, TI>::HFB_Complex()
{

}

template<typename TR, typename TI>
TI HFB_Complex<TR, TI>::getImag()
{
	return this->imag;
}

template<typename TR, typename TI>
bool HFB_Complex<TR, TI>::setImag(TI imag)
{
	this->imag = imag;
	return true;
}

template<typename TR, typename TI>
TR HFB_Complex<TR, TI>::getTreal()
{
	return this->real;
}

template<typename TR, typename TI>
bool HFB_Complex<TR, TI>::setReal(TR real)
{
	this->real = real;
	return true;
}

