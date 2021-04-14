#ifndef USER_H
#define USER_H
#include "phoneme.h"
class User {
	enum { nombre_phoneme = 4 };
public:
	enum class Phonemes { A, E, I, O};
	User();
	bool setPhonemes();
	bool phonemesReady();
	bool userPhonemeEmpty();
	void clearPhoneme(Phonemes phoneme);
	void ajoutEnregistrement(int enregistrement, int channel, Phonemes phoneme);
	void ajoutEnregistrement(int* echconv, Phonemes phoneme);
	int** getPhonemes();
private:
	Phoneme phonemes[nombre_phoneme];
};
#endif