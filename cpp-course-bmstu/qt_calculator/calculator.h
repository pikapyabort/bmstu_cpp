#pragma once

#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QVector>
#include <QWidget>

#include <cmath>

#define SIMPLE_MODE 1
#define ENGINEERING_MODE 2

#define STAGE1 1
#define STAGE2 2

#define OPERATION_PLUS 1
#define OPERATION_MINUS 2
#define OPERATION_INCREASE 3
#define OPERATION_DIVIDE 4
#define OPERATION_STEP_Y 5
#define OPERATION_Y_ROOT 6
#define OPERATION_LOG_Y 7

class Calc : public QMainWindow {
    Q_OBJECT
private:
    QWidget *mainWidget;
    QGridLayout *mainLayout;
    QGridLayout *commonLayout;
    QWidget *common;
    QWidget *simple;
    QWidget *engineering;
    QLineEdit *display;
    QRadioButton *simpleRadioButton;
    QRadioButton *engineeringRadioButton;

    QString slot1;
    double x;
    int operation;
    int stage;
    bool hasNumber;
    bool hasComma;

    void createCommonWidget();

    void createSimpleWidget();
    void createEngineeringWidget();

    void showSimple();
    void showEngineering();

public:

    Calc(QWidget *parent = nullptr);
    ~Calc();

public slots:

    void error();

    void switchMode();
    void updateDisplay();
    void clear();

    void zeroClicked();
    void numberClicked();
    void commaClicked();
    void equalClicked();
    void binaryClicked();
    void unaryClicked();
    void plusClicked();
    void minusClicked();
    void increaseClicked();
    void divideClicked();
    void stepYClicked();
    void yRootClicked();
    void logYClicked();
    void changeClicked();
    void percentClicked();
    void squareClicked();
    void cubeClicked();
    void expToYClicked();
    void tenToYClicked();
    void absClicked();
    void inverseClicked();
    void sqrtClicked();
    void cbrtClicked();
    void factorialClicked();
    void lnClicked();
    void logClicked();
    void expClicked();
    void piClicked();
    void sinClicked();
    void cosClicked();
    void tgClicked();
    void ctgClicked();
    void secClicked();
    void shClicked();
    void cthClicked();
    void cscClicked();
    void chClicked();
    void thClicked();
};
