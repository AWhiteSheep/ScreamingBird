/*
*   CommunicationFPGA est une classe d'interface à la pour la communication
*   avec la carte FPGA de la session S2. Pour les details de l'utilisation
*   de cette classe, consultez le guide d'utilisation.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: CommunicationFPGA.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/

#ifndef COMMUNICATIONFPGA_H
#define COMMUNICATIONFPGA_H

#include <windows.h>

using namespace std;

const int nitermax  = 10000;         // Nbre d'itération max de la boucle de lecture d'acquisition (limite pour tests)
                                     // changer la condition de boucle sans cette limite selon le besoin de l'application
const int delai_boucle = 10;         // delai d'attente ajouté dans la boucle de lecture en ms

// numeros de registres correspondants pour les echanges FPGA <-> PC  ...
unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
unsigned const int nreg_lect_cmpt_t = 2;    // fpga -> PC  compteur temps FPGA -> PC
unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
unsigned const int nreg_ecri_led = 10;      // PC -> fpga (donnees leds)

class CommunicationFPGA {
public:
    BOOL statutport = false;            // statut du port de communication qui sera cree
    int compteur_temps = 0;
    int swt = 0;                         // donnee recue du FPGA
    int aff7sg_octet0 = 0;               // octet 0 (droite) pour afficheur 7 segments
    int aff7sg_octet1 = 0;               // octet 0 (droite) pour afficheur 7 segments
    int stat_btn      = 0;               // donnee recue du FPGA: statut et BTN
    int echconv[4];                      // donnee converties recues du FPGA
    int canal_a_afficher        = 0;     // donnee recue du FPGA
    int indice_canal_a_afficher = 0;

    CommunicationFPGA();
	~CommunicationFPGA();

	bool lireRegistre(int registre, int &valeur);
	bool ecrireRegistre(int registre, int valeur);
	void sleep(unsigned int millisecondes = 10);

	bool estOk();
	const char * messageErreur();
private:
	bool erreur;
    char msgErreur[1024];
	unsigned long hif;
};

#endif
