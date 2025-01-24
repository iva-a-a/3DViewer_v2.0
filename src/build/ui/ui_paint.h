/********************************************************************************
** Form generated from reading UI file 'paint.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINT_H
#define UI_PAINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *field;
    QFrame *menu;
    QPushButton *chooseFile;
    QTextBrowser *fileName;
    QLabel *label_file;
    QLabel *label_char_model;
    QLabel *label_vertex;
    QLabel *label_edge;
    QLabel *label_settings;
    QLabel *label_shift;
    QLabel *label_shift_x;
    QLabel *label_shift_y;
    QLabel *label_shift_z;
    QLabel *label_rotation;
    QLabel *label_rotation_x;
    QLabel *label_rotation_y;
    QLabel *label_rotation_z;
    QLabel *label_scale;
    QPushButton *resetSettings;
    QTabWidget *tabWidget;
    QWidget *widget;
    QLabel *label_type;
    QLabel *label_color;
    QLabel *label_thickness;
    QComboBox *typeSelectFacets;
    QPushButton *colorSelectFacets;
    QScrollBar *thicknessSelectFacets;
    QWidget *tab_4;
    QLabel *label_type_2;
    QComboBox *typeSelectVertices;
    QLabel *label_color_2;
    QPushButton *colorSelectVertices;
    QLabel *label_size;
    QScrollBar *sizeSelectVerties;
    QWidget *tab;
    QLabel *label_color_3;
    QPushButton *colorSelectBackground;
    QWidget *tab_2;
    QLabel *saveGif;
    QPushButton *saveAsBmpOrJpeg;
    QPushButton *saveAsGif;
    QLabel *label_type_project;
    QComboBox *typeProjection;
    QTextBrowser *number_of_vertices;
    QTextBrowser *number_of_edges;
    QScrollBar *scrollRotateX;
    QScrollBar *scrollShiftX;
    QScrollBar *scrollShiftY;
    QScrollBar *scrollShiftZ;
    QScrollBar *scrollRotateY;
    QScrollBar *scrollRotateZ;
    QScrollBar *scrollScale;
    QLineEdit *boxShiftX;
    QLineEdit *boxShiftY;
    QLineEdit *boxShiftZ;
    QLineEdit *boxRotateX;
    QLineEdit *boxRotateY;
    QLineEdit *boxRotateZ;
    QLineEdit *boxScale;
    QLabel *label_settings_12;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1739, 906);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        field = new QFrame(centralwidget);
        field->setObjectName(QString::fromUtf8("field"));
        field->setGeometry(QRect(10, 10, 1201, 841));
        field->setFocusPolicy(Qt::StrongFocus);
        field->setStyleSheet(QString::fromUtf8("background:white;\n"
"border-radius:5px;\n"
"\n"
""));
        field->setFrameShape(QFrame::StyledPanel);
        field->setFrameShadow(QFrame::Raised);
        menu = new QFrame(centralwidget);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setGeometry(QRect(1210, 10, 361, 841));
        menu->setStyleSheet(QString::fromUtf8("background-color: rgb(66, 66, 66);\n"
"border-radius:5px;"));
        menu->setFrameShape(QFrame::StyledPanel);
        menu->setFrameShadow(QFrame::Raised);
        chooseFile = new QPushButton(menu);
        chooseFile->setObjectName(QString::fromUtf8("chooseFile"));
        chooseFile->setGeometry(QRect(10, 30, 151, 41));
        chooseFile->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: 16pt \"Times New Roman\";"));
        fileName = new QTextBrowser(menu);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setGeometry(QRect(170, 30, 181, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        fileName->setFont(font);
        fileName->setFocusPolicy(Qt::NoFocus);
        fileName->setLayoutDirection(Qt::RightToLeft);
        fileName->setStyleSheet(QString::fromUtf8("background:gray;\n"
"font: italic 18pt \"Times New Roman\";\n"
"color: white;"));
        fileName->setFrameShape(QFrame::StyledPanel);
        fileName->setFrameShadow(QFrame::Sunken);
        fileName->setLineWidth(1);
        fileName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fileName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fileName->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        fileName->setLineWrapMode(QTextEdit::NoWrap);
        label_file = new QLabel(menu);
        label_file->setObjectName(QString::fromUtf8("label_file"));
        label_file->setGeometry(QRect(150, 0, 48, 24));
        label_file->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_char_model = new QLabel(menu);
        label_char_model->setObjectName(QString::fromUtf8("label_char_model"));
        label_char_model->setGeometry(QRect(80, 80, 216, 24));
        label_char_model->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_vertex = new QLabel(menu);
        label_vertex->setObjectName(QString::fromUtf8("label_vertex"));
        label_vertex->setGeometry(QRect(10, 110, 145, 31));
        label_vertex->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_edge = new QLabel(menu);
        label_edge->setObjectName(QString::fromUtf8("label_edge"));
        label_edge->setGeometry(QRect(10, 150, 145, 31));
        label_edge->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_settings = new QLabel(menu);
        label_settings->setObjectName(QString::fromUtf8("label_settings"));
        label_settings->setGeometry(QRect(120, 190, 103, 24));
        label_settings->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_shift = new QLabel(menu);
        label_shift->setObjectName(QString::fromUtf8("label_shift"));
        label_shift->setGeometry(QRect(20, 220, 65, 24));
        label_shift->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_shift_x = new QLabel(menu);
        label_shift_x->setObjectName(QString::fromUtf8("label_shift_x"));
        label_shift_x->setGeometry(QRect(20, 250, 16, 24));
        label_shift_x->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_shift_y = new QLabel(menu);
        label_shift_y->setObjectName(QString::fromUtf8("label_shift_y"));
        label_shift_y->setGeometry(QRect(20, 280, 16, 24));
        label_shift_y->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_shift_z = new QLabel(menu);
        label_shift_z->setObjectName(QString::fromUtf8("label_shift_z"));
        label_shift_z->setGeometry(QRect(20, 310, 13, 24));
        label_shift_z->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_rotation = new QLabel(menu);
        label_rotation->setObjectName(QString::fromUtf8("label_rotation"));
        label_rotation->setGeometry(QRect(20, 340, 87, 24));
        label_rotation->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_rotation_x = new QLabel(menu);
        label_rotation_x->setObjectName(QString::fromUtf8("label_rotation_x"));
        label_rotation_x->setGeometry(QRect(20, 370, 16, 24));
        label_rotation_x->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_rotation_y = new QLabel(menu);
        label_rotation_y->setObjectName(QString::fromUtf8("label_rotation_y"));
        label_rotation_y->setGeometry(QRect(20, 400, 16, 24));
        label_rotation_y->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_rotation_z = new QLabel(menu);
        label_rotation_z->setObjectName(QString::fromUtf8("label_rotation_z"));
        label_rotation_z->setGeometry(QRect(20, 430, 13, 24));
        label_rotation_z->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_scale = new QLabel(menu);
        label_scale->setObjectName(QString::fromUtf8("label_scale"));
        label_scale->setGeometry(QRect(20, 460, 94, 24));
        label_scale->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        resetSettings = new QPushButton(menu);
        resetSettings->setObjectName(QString::fromUtf8("resetSettings"));
        resetSettings->setGeometry(QRect(10, 790, 341, 41));
        resetSettings->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"font: bold 14pt \"Times New Roman\";"));
        tabWidget = new QTabWidget(menu);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(16, 599, 341, 181));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8("font: 75 13pt \"Times New Roman\";\n"
"color: rgb(0, 0, 0);\n"
"background:gray;\n"
""));
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        label_type = new QLabel(widget);
        label_type->setObjectName(QString::fromUtf8("label_type"));
        label_type->setGeometry(QRect(10, 10, 92, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label_type->setFont(font1);
        label_type->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_color = new QLabel(widget);
        label_color->setObjectName(QString::fromUtf8("label_color"));
        label_color->setGeometry(QRect(10, 60, 45, 22));
        label_color->setFont(font1);
        label_color->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        label_thickness = new QLabel(widget);
        label_thickness->setObjectName(QString::fromUtf8("label_thickness"));
        label_thickness->setGeometry(QRect(10, 110, 78, 22));
        label_thickness->setFont(font1);
        label_thickness->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        typeSelectFacets = new QComboBox(widget);
        typeSelectFacets->addItem(QString());
        typeSelectFacets->addItem(QString());
        typeSelectFacets->setObjectName(QString::fromUtf8("typeSelectFacets"));
        typeSelectFacets->setGeometry(QRect(171, 10, 131, 24));
        typeSelectFacets->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        colorSelectFacets = new QPushButton(widget);
        colorSelectFacets->setObjectName(QString::fromUtf8("colorSelectFacets"));
        colorSelectFacets->setGeometry(QRect(169, 60, 131, 22));
        colorSelectFacets->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        thicknessSelectFacets = new QScrollBar(widget);
        thicknessSelectFacets->setObjectName(QString::fromUtf8("thicknessSelectFacets"));
        thicknessSelectFacets->setGeometry(QRect(120, 120, 211, 20));
        thicknessSelectFacets->setStyleSheet(QString::fromUtf8("background: rgb(200, 200, 200);"));
        thicknessSelectFacets->setMinimum(0);
        thicknessSelectFacets->setMaximum(15);
        thicknessSelectFacets->setOrientation(Qt::Horizontal);
        tabWidget->addTab(widget, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label_type_2 = new QLabel(tab_4);
        label_type_2->setObjectName(QString::fromUtf8("label_type_2"));
        label_type_2->setGeometry(QRect(10, 10, 176, 22));
        label_type_2->setFont(font1);
        label_type_2->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        typeSelectVertices = new QComboBox(tab_4);
        typeSelectVertices->addItem(QString());
        typeSelectVertices->addItem(QString());
        typeSelectVertices->addItem(QString());
        typeSelectVertices->setObjectName(QString::fromUtf8("typeSelectVertices"));
        typeSelectVertices->setGeometry(QRect(192, 10, 131, 24));
        typeSelectVertices->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        label_color_2 = new QLabel(tab_4);
        label_color_2->setObjectName(QString::fromUtf8("label_color_2"));
        label_color_2->setGeometry(QRect(10, 60, 45, 22));
        label_color_2->setFont(font1);
        label_color_2->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        colorSelectVertices = new QPushButton(tab_4);
        colorSelectVertices->setObjectName(QString::fromUtf8("colorSelectVertices"));
        colorSelectVertices->setGeometry(QRect(189, 60, 131, 22));
        colorSelectVertices->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        label_size = new QLabel(tab_4);
        label_size->setObjectName(QString::fromUtf8("label_size"));
        label_size->setGeometry(QRect(10, 110, 62, 22));
        label_size->setFont(font1);
        label_size->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        sizeSelectVerties = new QScrollBar(tab_4);
        sizeSelectVerties->setObjectName(QString::fromUtf8("sizeSelectVerties"));
        sizeSelectVerties->setGeometry(QRect(110, 120, 221, 20));
        sizeSelectVerties->setStyleSheet(QString::fromUtf8("background: rgb(200, 200, 200);"));
        sizeSelectVerties->setMinimum(0);
        sizeSelectVerties->setMaximum(15);
        sizeSelectVerties->setOrientation(Qt::Horizontal);
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_color_3 = new QLabel(tab);
        label_color_3->setObjectName(QString::fromUtf8("label_color_3"));
        label_color_3->setGeometry(QRect(10, 60, 45, 22));
        label_color_3->setFont(font1);
        label_color_3->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        colorSelectBackground = new QPushButton(tab);
        colorSelectBackground->setObjectName(QString::fromUtf8("colorSelectBackground"));
        colorSelectBackground->setGeometry(QRect(189, 60, 131, 22));
        colorSelectBackground->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        saveGif = new QLabel(tab_2);
        saveGif->setObjectName(QString::fromUtf8("saveGif"));
        saveGif->setGeometry(QRect(10, 10, 176, 22));
        saveGif->setFont(font1);
        saveGif->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        saveAsBmpOrJpeg = new QPushButton(tab_2);
        saveAsBmpOrJpeg->setObjectName(QString::fromUtf8("saveAsBmpOrJpeg"));
        saveAsBmpOrJpeg->setGeometry(QRect(20, 60, 110, 22));
        saveAsBmpOrJpeg->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        saveAsGif = new QPushButton(tab_2);
        saveAsGif->setObjectName(QString::fromUtf8("saveAsGif"));
        saveAsGif->setGeometry(QRect(190, 60, 110, 22));
        saveAsGif->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background: rgb(200, 200, 200);"));
        tabWidget->addTab(tab_2, QString());
        label_type_project = new QLabel(menu);
        label_type_project->setObjectName(QString::fromUtf8("label_type_project"));
        label_type_project->setGeometry(QRect(20, 560, 137, 24));
        label_type_project->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        typeProjection = new QComboBox(menu);
        typeProjection->addItem(QString());
        typeProjection->addItem(QString());
        typeProjection->setObjectName(QString::fromUtf8("typeProjection"));
        typeProjection->setGeometry(QRect(170, 560, 161, 26));
        typeProjection->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);\n"
"background:gray;"));
        number_of_vertices = new QTextBrowser(menu);
        number_of_vertices->setObjectName(QString::fromUtf8("number_of_vertices"));
        number_of_vertices->setGeometry(QRect(170, 110, 171, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        number_of_vertices->setFont(font2);
        number_of_vertices->setFocusPolicy(Qt::NoFocus);
        number_of_vertices->setLayoutDirection(Qt::RightToLeft);
        number_of_vertices->setStyleSheet(QString::fromUtf8("background:gray;\n"
"color: white;"));
        number_of_vertices->setFrameShape(QFrame::StyledPanel);
        number_of_vertices->setFrameShadow(QFrame::Sunken);
        number_of_vertices->setLineWidth(1);
        number_of_vertices->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        number_of_vertices->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        number_of_vertices->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        number_of_vertices->setLineWrapMode(QTextEdit::NoWrap);
        number_of_edges = new QTextBrowser(menu);
        number_of_edges->setObjectName(QString::fromUtf8("number_of_edges"));
        number_of_edges->setGeometry(QRect(170, 150, 171, 31));
        number_of_edges->setFont(font2);
        number_of_edges->setFocusPolicy(Qt::NoFocus);
        number_of_edges->setLayoutDirection(Qt::RightToLeft);
        number_of_edges->setStyleSheet(QString::fromUtf8("background:gray;\n"
"color: white;"));
        number_of_edges->setFrameShape(QFrame::StyledPanel);
        number_of_edges->setFrameShadow(QFrame::Sunken);
        number_of_edges->setLineWidth(1);
        number_of_edges->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        number_of_edges->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        number_of_edges->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        number_of_edges->setLineWrapMode(QTextEdit::NoWrap);
        scrollRotateX = new QScrollBar(menu);
        scrollRotateX->setObjectName(QString::fromUtf8("scrollRotateX"));
        scrollRotateX->setGeometry(QRect(110, 370, 241, 20));
        scrollRotateX->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollRotateX->setMinimum(0);
        scrollRotateX->setMaximum(360);
        scrollRotateX->setOrientation(Qt::Horizontal);
        scrollShiftX = new QScrollBar(menu);
        scrollShiftX->setObjectName(QString::fromUtf8("scrollShiftX"));
        scrollShiftX->setGeometry(QRect(110, 250, 241, 21));
        scrollShiftX->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollShiftX->setMinimum(-50);
        scrollShiftX->setMaximum(50);
        scrollShiftX->setOrientation(Qt::Horizontal);
        scrollShiftY = new QScrollBar(menu);
        scrollShiftY->setObjectName(QString::fromUtf8("scrollShiftY"));
        scrollShiftY->setGeometry(QRect(110, 280, 241, 20));
        scrollShiftY->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollShiftY->setMinimum(-50);
        scrollShiftY->setMaximum(50);
        scrollShiftY->setOrientation(Qt::Horizontal);
        scrollShiftZ = new QScrollBar(menu);
        scrollShiftZ->setObjectName(QString::fromUtf8("scrollShiftZ"));
        scrollShiftZ->setGeometry(QRect(110, 310, 241, 20));
        scrollShiftZ->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollShiftZ->setMinimum(-50);
        scrollShiftZ->setMaximum(50);
        scrollShiftZ->setOrientation(Qt::Horizontal);
        scrollRotateY = new QScrollBar(menu);
        scrollRotateY->setObjectName(QString::fromUtf8("scrollRotateY"));
        scrollRotateY->setGeometry(QRect(110, 400, 241, 20));
        scrollRotateY->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollRotateY->setMinimum(0);
        scrollRotateY->setMaximum(360);
        scrollRotateY->setOrientation(Qt::Horizontal);
        scrollRotateZ = new QScrollBar(menu);
        scrollRotateZ->setObjectName(QString::fromUtf8("scrollRotateZ"));
        scrollRotateZ->setGeometry(QRect(110, 430, 241, 20));
        scrollRotateZ->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollRotateZ->setMinimum(0);
        scrollRotateZ->setMaximum(360);
        scrollRotateZ->setOrientation(Qt::Horizontal);
        scrollScale = new QScrollBar(menu);
        scrollScale->setObjectName(QString::fromUtf8("scrollScale"));
        scrollScale->setGeometry(QRect(90, 490, 261, 20));
        scrollScale->setStyleSheet(QString::fromUtf8("background:gray;"));
        scrollScale->setMinimum(1);
        scrollScale->setMaximum(50);
        scrollScale->setOrientation(Qt::Horizontal);
        boxShiftX = new QLineEdit(menu);
        boxShiftX->setObjectName(QString::fromUtf8("boxShiftX"));
        boxShiftX->setGeometry(QRect(50, 250, 51, 21));
        boxShiftX->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxShiftX->setAlignment(Qt::AlignCenter);
        boxShiftY = new QLineEdit(menu);
        boxShiftY->setObjectName(QString::fromUtf8("boxShiftY"));
        boxShiftY->setGeometry(QRect(50, 280, 51, 21));
        boxShiftY->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxShiftY->setAlignment(Qt::AlignCenter);
        boxShiftZ = new QLineEdit(menu);
        boxShiftZ->setObjectName(QString::fromUtf8("boxShiftZ"));
        boxShiftZ->setGeometry(QRect(50, 310, 51, 21));
        boxShiftZ->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxShiftZ->setAlignment(Qt::AlignCenter);
        boxRotateX = new QLineEdit(menu);
        boxRotateX->setObjectName(QString::fromUtf8("boxRotateX"));
        boxRotateX->setGeometry(QRect(50, 370, 51, 21));
        boxRotateX->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxRotateX->setAlignment(Qt::AlignCenter);
        boxRotateY = new QLineEdit(menu);
        boxRotateY->setObjectName(QString::fromUtf8("boxRotateY"));
        boxRotateY->setGeometry(QRect(50, 400, 51, 21));
        boxRotateY->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxRotateY->setAlignment(Qt::AlignCenter);
        boxRotateZ = new QLineEdit(menu);
        boxRotateZ->setObjectName(QString::fromUtf8("boxRotateZ"));
        boxRotateZ->setGeometry(QRect(50, 430, 51, 21));
        boxRotateZ->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxRotateZ->setAlignment(Qt::AlignCenter);
        boxScale = new QLineEdit(menu);
        boxScale->setObjectName(QString::fromUtf8("boxScale"));
        boxScale->setGeometry(QRect(20, 490, 51, 21));
        boxScale->setStyleSheet(QString::fromUtf8("background:gray;"));
        boxScale->setAlignment(Qt::AlignCenter);
        label_settings_12 = new QLabel(menu);
        label_settings_12->setObjectName(QString::fromUtf8("label_settings_12"));
        label_settings_12->setGeometry(QRect(50, 520, 256, 24));
        label_settings_12->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";\n"
"color: rgb(255, 255, 255);"));
        chooseFile->raise();
        fileName->raise();
        label_file->raise();
        label_char_model->raise();
        label_vertex->raise();
        label_edge->raise();
        label_settings->raise();
        label_shift->raise();
        label_shift_x->raise();
        label_shift_y->raise();
        label_shift_z->raise();
        label_rotation->raise();
        label_rotation_x->raise();
        label_rotation_y->raise();
        label_rotation_z->raise();
        label_scale->raise();
        tabWidget->raise();
        label_type_project->raise();
        typeProjection->raise();
        resetSettings->raise();
        number_of_vertices->raise();
        number_of_edges->raise();
        scrollRotateX->raise();
        scrollShiftX->raise();
        scrollShiftY->raise();
        scrollShiftZ->raise();
        scrollRotateY->raise();
        scrollRotateZ->raise();
        scrollScale->raise();
        boxShiftX->raise();
        boxShiftY->raise();
        boxShiftZ->raise();
        boxRotateX->raise();
        boxRotateY->raise();
        boxRotateZ->raise();
        boxScale->raise();
        label_settings_12->raise();
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1739, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        chooseFile->setText(QCoreApplication::translate("MainWindow", " \320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273 ", nullptr));
        fileName->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Times New Roman'; font-size:14pt; font-weight:400; font-style:italic;\">\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans'; font-size:12pt; font-weight:600;\"><br /></p></body></html>", nullptr));
        fileName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\265\321\202 \321\204\320\260\320\271\320\273\320\260", nullptr));
        label_file->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        label_char_model->setText(QCoreApplication::translate("MainWindow", "\320\245\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\270\321\201\321\202\320\270\320\272\320\270 \320\274\320\276\320\264\320\265\320\273\320\270", nullptr));
        label_vertex->setText(QCoreApplication::translate("MainWindow", " \320\232\320\276\320\273-\320\262\320\276 \320\262\320\265\321\200\321\210\320\270\320\275 ", nullptr));
        label_edge->setText(QCoreApplication::translate("MainWindow", " \320\232\320\276\320\273-\320\262\320\276 \321\200\320\265\320\261\320\265\321\200 ", nullptr));
        label_settings->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 ", nullptr));
        label_shift->setText(QCoreApplication::translate("MainWindow", " \320\241\320\264\320\262\320\270\320\263 ", nullptr));
        label_shift_x->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_shift_y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_shift_z->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_rotation->setText(QCoreApplication::translate("MainWindow", " \320\237\320\276\320\262\320\276\321\200\320\276\321\202 ", nullptr));
        label_rotation_x->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_rotation_y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_rotation_z->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_scale->setText(QCoreApplication::translate("MainWindow", " \320\234\320\260\321\201\321\210\321\202\320\260\320\261 ", nullptr));
        resetSettings->setText(QCoreApplication::translate("MainWindow", " \320\241\320\261\321\200\320\276\321\201 \320\275\320\260\321\201\321\202\321\200\320\276\320\265\320\272 ", nullptr));
        label_type->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\273\320\270\320\275\320\270\320\271:", nullptr));
        label_color->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202:", nullptr));
        label_thickness->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260:", nullptr));
        typeSelectFacets->setItemText(0, QCoreApplication::translate("MainWindow", "\321\201\320\277\320\273\320\276\321\210\320\275\320\260\321\217", nullptr));
        typeSelectFacets->setItemText(1, QCoreApplication::translate("MainWindow", "\320\277\321\203\320\275\320\272\321\202\320\270\321\200\320\275\320\260\321\217", nullptr));

        colorSelectFacets->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget), QCoreApplication::translate("MainWindow", "\320\240\320\265\320\261\321\200\320\260", nullptr));
        label_type_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\276\321\201\320\276\320\261 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217:", nullptr));
        typeSelectVertices->setItemText(0, QCoreApplication::translate("MainWindow", "\320\272\321\200\321\203\320\263", nullptr));
        typeSelectVertices->setItemText(1, QCoreApplication::translate("MainWindow", "\320\272\320\262\320\260\320\264\321\200\320\260\321\202", nullptr));
        typeSelectVertices->setItemText(2, QCoreApplication::translate("MainWindow", "\320\276\321\202\321\201\321\203\321\202\321\201\321\202\320\262\321\203\320\265\321\202", nullptr));

        label_color_2->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202:", nullptr));
        colorSelectVertices->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202", nullptr));
        label_size->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\210\320\270\320\275\321\213", nullptr));
        label_color_3->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202:", nullptr));
        colorSelectBackground->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\206\320\262\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", " \320\244\320\276\320\275 ", nullptr));
        saveGif->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217:", nullptr));
        saveAsBmpOrJpeg->setText(QCoreApplication::translate("MainWindow", "bmp/jpeg", nullptr));
        saveAsGif->setText(QCoreApplication::translate("MainWindow", "gif", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265 ", nullptr));
        label_type_project->setText(QCoreApplication::translate("MainWindow", " \320\242\320\270\320\277 \320\277\321\200\320\276\320\265\320\272\321\206\320\270\320\270 ", nullptr));
        typeProjection->setItemText(0, QCoreApplication::translate("MainWindow", "\320\277\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\320\260\321\217", nullptr));
        typeProjection->setItemText(1, QCoreApplication::translate("MainWindow", "\321\206\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217", nullptr));

        number_of_vertices->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:600; font-style:italic;\">\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans';\"><br /></p></body></html>", nullptr));
        number_of_vertices->setPlaceholderText(QString());
        number_of_edges->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:600; font-style:italic;\">\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans';\"><br /></p></body></html>", nullptr));
        number_of_edges->setPlaceholderText(QString());
        label_settings_12->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINT_H
