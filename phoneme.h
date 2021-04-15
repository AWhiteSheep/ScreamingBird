#ifndef PHONEME_H
#define PHONEME_H
class Phoneme {
public:
	enum { nombre_channel = 4 };
	Phoneme();
	void ajoutValeur(int enregistrement, int channel);
	void clear(int channel);
	void setPhoneme();
	void clear();
	bool empty();
	bool hasEmpty();
	bool isReady();
	int nombreEnregistrement(int channel);
	int sommeValeursEnregistrement(int channel);
	int* moyenEnregistrement();
private:
	int _nombreEnregistrement[nombre_channel] = { 0,0,0,0 };
	int _sommeValeurEnregistrement[nombre_channel] = { 0,0,0,0 };
	int _moyenEnregistrement[nombre_channel] = { 0,0,0,0 };
};
#endif