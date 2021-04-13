/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*   Description: Classe abstraite contenant qu'une seul fonction qui a pour but de se faire appelé dans la scene pour figer les entités devant être utilisés.
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