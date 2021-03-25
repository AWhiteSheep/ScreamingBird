/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QPushButton *startGameButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1177, 637);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setLayoutDirection(Qt::LeftToRight);
        Widget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSceneRect(QRectF(0, 0, 0, 0));
        graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        verticalLayout->addWidget(graphicsView);

        startGameButton = new QPushButton(Widget);
        startGameButton->setObjectName(QString::fromUtf8("startGameButton"));

        verticalLayout->addWidget(startGameButton);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        startGameButton->setText(QCoreApplication::translate("Widget", "Start Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
