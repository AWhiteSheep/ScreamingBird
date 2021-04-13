#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QWidget>
#include <QMainWindow>
#include <QGroupBox>
#include <QMenuBar>
#include <QMenu>
#include <QKeySequence>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QBoxLayout>
#include <QString>

class Instructions : public QWidget
{
	Q_OBJECT

public:
	Instructions(QWidget* parent);

private slots:
	//void createInstructions();
	void instructionText();

private:
	QMessageBox* boiteDeMessage;
	QMenuBar* menu;
	QMenu* nstrctn;
	QAction* iuio;
	QHBoxLayout* layout;

};

#endif