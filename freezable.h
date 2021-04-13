/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe abstraite contenant qu'une seul fonction qui a pour but de se faire appel� dans la scene pour figer les entit�s devant �tre utilis�s.
*
*/
#ifndef FREEZABLE_H
#define FREEZABLE_H
class Freezable 
{
public:
	virtual void freezeInPlace() = 0;
};
#endif