/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*
*/
#include "widget.h"
#include <QApplication>
#include <QMainWindow>
#include <QTextCodec>
#include <QMenuBar>
#include <QMessageBox>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QMainWindow mainWindow;
	QMessageBox message;
	message.setText("Comment jouer avec les phonemes: Il faut prononcer ces voyelles la\n"
					"\nA : Monter\n"
					"E = Descendre\n"
					"I = Lancer du feu\n"
					"O = Utiliser le bonus\n"
					"\nComment jouer avec le clavier:\n"
					"\nW = Monter\n"
					"S = Descendre\n"
					"D = Lancer du feu\n"
					"A = Utiliser le bonus\n"
					"\nCliquez sur Show Details pour plus d'informations.");
	message.setDetailedText("Le but de l'application est d'effectuer "
		                    "le plus grand haut score possible en evitant les obstacles et en "
							"combattant certains ennemis. Les actions disponibles lorsque le "
							"jeu est actif sont de monter, descendre, cracher une boule de feu "
							"et d'utiliser un bonus. Le jeu fini lorsque l'utilisateur touche "
							"un tuyau, un ennemi ou l'un des projectiles du boss. " 
							"Lorsque le joueur commence le jeu, plusieurs obstacle ou bonus "
							"vont etre envoyes vers l'utilisateur.Il y a des tuyaux, des tortues "
							"volantes qui font fit d'ennemis et des petites boites de bonus.");

	Widget* w = new Widget;
	mainWindow.menuBar()->addAction("Help");
	mainWindow.connect(mainWindow.menuBar(), &QMenuBar::triggered, [&message]()
		{
			message.exec();
		});
	mainWindow.setCentralWidget(w);
	mainWindow.show();
	return a.exec();
}
