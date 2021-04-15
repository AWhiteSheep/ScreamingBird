#include "phoneme.h"

Phoneme::Phoneme() 
{
}

void Phoneme::ajoutValeur(int enregistrement, int channel)
{
	_nombreEnregistrement[channel] += 1;
	_sommeValeurEnregistrement[channel] += enregistrement;
}

void Phoneme::clear()
{
	for (int i = 0; i < nombre_channel; i++)
	{
		clear(i);
	}
}

void Phoneme::clear(int channel)
{
	_nombreEnregistrement[channel] = 0;
	_sommeValeurEnregistrement[channel] = 0;
	_moyenEnregistrement[channel] = 0;
}

bool Phoneme::empty() 
{
	for (int i = 0; i < nombre_channel; i++)
	{
		if (_nombreEnregistrement[i] != 0)
			return false;
	}
	return true;
}

bool Phoneme::hasEmpty() 
{
	for (int i = 0; i < nombre_channel; i++)
	{
		if (_nombreEnregistrement[i] == 0)
			return true;
	}
	return false;
}

int Phoneme::nombreEnregistrement(int channel)
{
	return _nombreEnregistrement[channel];
}

int Phoneme::sommeValeursEnregistrement(int channel)
{
	return _sommeValeurEnregistrement[channel];
}

void Phoneme::setPhoneme()
{
	for (int i = 0; i < nombre_channel; i++)
		_moyenEnregistrement[i] = _sommeValeurEnregistrement[i] / _nombreEnregistrement[i];
}

int * Phoneme::moyenEnregistrement() 
{
	return _moyenEnregistrement;
}

bool Phoneme::isReady()
{
	for (int i = 0; i < nombre_channel; i++)
	{
		if (_nombreEnregistrement[i] < 100)
			return false;
	}
	return true;
}