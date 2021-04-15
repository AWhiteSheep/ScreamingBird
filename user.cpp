#include "user.h"

User::User()
{
}

bool User::userPhonemeEmpty() 
{
	for each (Phoneme pho in phonemes)
	{
		if (!pho.empty())
			return false;
	}
	return true;
}

bool User::setPhonemes() 
{
	for (int i = 0; i < nombre_phoneme; i++) 
	{
		if (phonemes[i].hasEmpty())
			return false;
		phonemes[i].setPhoneme();
	}
	return true;
}

void User::ajoutEnregistrement(int enregistrement, int channel, Phonemes phoneme) 
{
	phonemes[int(phoneme)].ajoutValeur(enregistrement, channel);
}

void User::ajoutEnregistrement(int* echconv, Phonemes phoneme)
{
	for (int i = 0; i < Phoneme::nombre_channel ; i++)
	{
		this->ajoutEnregistrement(echconv[i], i, phoneme);
	}
}

int** User::getPhonemes() 
{
	int** _phonemes = new int*[nombre_phoneme];
	for (int i = 0; i < nombre_phoneme; i++)
	{
		_phonemes[i] = phonemes[i].moyenEnregistrement();
	}
	return _phonemes;
}

bool User::phonemesReady() 
{
	bool ready;
	for each (Phoneme var in phonemes)
	{
		if(!(var.isReady()))
			return false;
	}
	for each (Phoneme var in phonemes)
	{
		var.setPhoneme();
	}
	return true;
}

void User::clearPhoneme(Phonemes phoneme) 
{
	phonemes[int(phoneme)].clear();
}