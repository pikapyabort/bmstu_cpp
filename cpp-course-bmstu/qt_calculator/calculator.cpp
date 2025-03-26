#include "calculator.h"

void Calc::error() {
    slot1 = "error!";
    x = 0.0;
    hasNumber = false;
    hasComma = false;
    operation = 0;
    stage = STAGE1;
    updateDisplay();
}

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

double pow_y(double a, double b) {
    return pow(a, b);
}

double y_root(double a, double b) {
    return pow(a, 1/b);
}

double log_y(double a, double b) {
    return log(a)/log(b);
}

double (*operations[])(double, double) = {
        nullptr,
        add,
        subtract,
        multiply,
        divide,
        pow_y,
        y_root,
        log_y
};

unsigned long factorial(unsigned long long i) {
    if (i == 0) {
        return 1;
    }
    return i * factorial(i - 1);
}

Calc::Calc(QWidget *parent)
    : QMainWindow(parent), mainWidget(nullptr), mainLayout(nullptr) {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    createCommonWidget();
    createSimpleWidget();
    createEngineeringWidget();
    clear();
    showSimple();
}

Calc::~Calc() {
    delete common;
    delete simple;
    delete engineering;
}

void Calc::createCommonWidget() {
    common = new QWidget(this);
    QGridLayout *commonLayout = new QGridLayout(common);
    display = new QLineEdit(common);
    display->setReadOnly(true);
    display->setStyleSheet("QLineEdit{ qproperty-alignment: 'AlignVCenter | AlignRight'; "
                           "border: 1px solid black; background-color: black; "
                           "color: white; font: 45pt 'Helvetica';}");
    display->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    display->setPlaceholderText("0");

    simpleRadioButton = new QRadioButton(tr("regular"));
    engineeringRadioButton = new QRadioButton(tr("engineer"));

    simpleRadioButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    engineeringRadioButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QString st = "QRadioButton{ color: #2643ff; font: 15pt 'Helvetica'; border-radius: 30px;} "
                 "QRadioButton:hover{ background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                 " stop: 0 #0F0F0F, stop: 1 #171717);}";

    simpleRadioButton->setStyleSheet(st);
    engineeringRadioButton->setStyleSheet(st);

    simpleRadioButton->setChecked(true);
    connect(simpleRadioButton, SIGNAL(toggled(bool)), SLOT(switchMode()));

    commonLayout->setSpacing(5);
    commonLayout->addWidget(display, 0, 0, 1, 4);
    commonLayout->addWidget(simpleRadioButton, 1, 0, 1, 1);
    commonLayout->addWidget(engineeringRadioButton, 1, 1, 1, 1);
    common->layout()->setContentsMargins(1, 1, 1, 10);

}

void Calc::createSimpleWidget() {
    simple = new QWidget();
    QGridLayout *simpleLayout = new QGridLayout(simple);

    QPushButton* Button0 = new QPushButton("0");
    QPushButton* Button1 = new QPushButton("1");
    QPushButton* Button2 = new QPushButton("2");
    QPushButton* Button3 = new QPushButton("3");
    QPushButton* Button4 = new QPushButton("4");
    QPushButton* Button5 = new QPushButton("5");
    QPushButton* Button6 = new QPushButton("6");
    QPushButton* Button7 = new QPushButton("7");
    QPushButton* Button8 = new QPushButton("8");
    QPushButton* Button9 = new QPushButton("9");
    QPushButton* ButtonComma = new QPushButton(",");
    QPushButton* ButtonClear = new QPushButton("AC");
    QPushButton* ButtonChange = new QPushButton("+/-");
    QPushButton* ButtonPercent = new QPushButton("%");
    QPushButton* ButtonDivide = new QPushButton("÷");
    QPushButton* ButtonIncrease = new QPushButton("×");
    QPushButton* ButtonMinus = new QPushButton("-");
    QPushButton* ButtonPlus = new QPushButton("+");
    QPushButton* ButtonEqual = new QPushButton("=");
    QPushButton* ButtonInvert = new QPushButton("¹⁄ₓ");

    Button0->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button3->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button4->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button5->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button6->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button7->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button8->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Button9->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonComma->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonClear->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonChange->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonPercent->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonDivide->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonIncrease->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonMinus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonPlus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonEqual->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonInvert->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QString style1 = "QPushButton {background-color: #404040; color: white; border: 4px solid black; "
                  "font: 30pt 'Helvetica'; border-radius: 10px;} QPushButton:pressed {"
                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                  "stop: 0 #8c8c8c, stop: 1 #a6a6a6);}";

    QString style2 = "QPushButton {color: black; background-color: #b3b3b3; border: 4px solid black; "
                  "font: bold black 40pt 'Helvetica'; border-radius: 10px;} QPushButton:pressed {"
                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                  "stop: 0 #d9d9d9, stop: 1 #e6e6e6);}";

    Button0->setStyleSheet(style1);
    Button1->setStyleSheet(style1);
    Button2->setStyleSheet(style1);
    Button3->setStyleSheet(style1);
    Button4->setStyleSheet(style1);
    Button5->setStyleSheet(style1);
    Button6->setStyleSheet(style1);
    Button7->setStyleSheet(style1);
    Button8->setStyleSheet(style1);
    Button9->setStyleSheet(style1);
    ButtonComma->setStyleSheet(style1);
    ButtonChange->setStyleSheet(style1);
    ButtonClear->setStyleSheet(style2);
    ButtonPercent->setStyleSheet(style2);
    ButtonDivide->setStyleSheet(style2);
    ButtonIncrease->setStyleSheet(style2);
    ButtonMinus->setStyleSheet(style2);
    ButtonPlus->setStyleSheet(style2);
    ButtonEqual->setStyleSheet(style2);
    ButtonInvert->setStyleSheet(style2);

    simpleLayout->setSpacing(3);
    simpleLayout->setContentsMargins(10, 1, 10, 10);

    simpleLayout->addWidget(ButtonClear, 0, 0, 1, 1);
    simpleLayout->addWidget(ButtonInvert, 0, 1, 1, 1);
    simpleLayout->addWidget(ButtonPercent, 0, 2, 1, 1);
    simpleLayout->addWidget(ButtonDivide, 0, 3, 1, 1);
    simpleLayout->addWidget(Button1, 1, 0, 1, 1);
    simpleLayout->addWidget(Button2, 1, 1, 1, 1);
    simpleLayout->addWidget(Button3, 1, 2, 1, 1);
    simpleLayout->addWidget(ButtonIncrease, 1, 3, 1, 1);
    simpleLayout->addWidget(Button4, 2, 0, 1, 1);
    simpleLayout->addWidget(Button5, 2, 1, 1, 1);
    simpleLayout->addWidget(Button6, 2, 2, 1, 1);
    simpleLayout->addWidget(ButtonMinus, 2, 3, 1, 1);
    simpleLayout->addWidget(Button7, 3, 0, 1, 1);
    simpleLayout->addWidget(Button8, 3, 1, 1, 1);
    simpleLayout->addWidget(Button9, 3, 2, 1, 1);
    simpleLayout->addWidget(ButtonPlus, 3, 3, 1, 1);
    simpleLayout->addWidget(ButtonChange, 4, 0, 1, 1);
    simpleLayout->addWidget(Button0, 4, 1, 1, 1);
    simpleLayout->addWidget(ButtonComma, 4, 2, 1, 1);
    simpleLayout->addWidget(ButtonEqual, 4, 3, 1, 1);

    simple->setLayout(simpleLayout);

    connect(ButtonClear, SIGNAL(clicked()), this, SLOT(clear()));
    connect(Button0, SIGNAL(clicked()), this, SLOT(zeroClicked()));
    connect(Button1, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button2, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button3, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button4, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button5, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button6, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button7, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button8, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(Button9, SIGNAL(clicked()), this, SLOT(numberClicked()));
    connect(ButtonComma, SIGNAL(clicked()), this, SLOT(commaClicked()));
    connect(ButtonEqual, SIGNAL(clicked()), this, SLOT(equalClicked()));
    connect(ButtonPlus, SIGNAL(clicked()), this, SLOT(plusClicked()));
    connect(ButtonMinus, SIGNAL(clicked()), this, SLOT(minusClicked()));
    connect(ButtonIncrease, SIGNAL(clicked()), this, SLOT(increaseClicked()));
    connect(ButtonDivide, SIGNAL(clicked()), this, SLOT(divideClicked()));
    connect(ButtonChange, SIGNAL(clicked()), this, SLOT(changeClicked()));
    connect(ButtonPercent, SIGNAL(clicked()), this, SLOT(percentClicked()));
    connect(ButtonInvert, SIGNAL(clicked()), this, SLOT(inverseClicked()));
}

void Calc::createEngineeringWidget() {
    engineering = new QWidget();
    QGridLayout *engineeringLayout = new QGridLayout(engineering);

    QPushButton* ButtonStep2 = new QPushButton("x²");
    QPushButton* ButtonStep3 = new QPushButton("x³");
    QPushButton* ButtonStepY = new QPushButton("xʸ");
    QPushButton* ButtonStepE = new QPushButton("eˣ");
    QPushButton* ButtonStep10 = new QPushButton("10ˣ");
    QPushButton* ButtonAbs = new QPushButton("|x|");
    QPushButton* ButtonSqrt = new QPushButton("√x");
    QPushButton* ButtonCbrt = new QPushButton("³√x");
    QPushButton* ButtonYrt = new QPushButton("ʸ√x");
    QPushButton* ButtonFactorial = new QPushButton("x!");
    QPushButton* ButtonLn = new QPushButton("ln");
    QPushButton* ButtonLog = new QPushButton("log");
    QPushButton* ButtonLogY = new QPushButton("logᵧx");
    QPushButton* ButtonExpon = new QPushButton("e");
    QPushButton* ButtonPi = new QPushButton("π");
    QPushButton* ButtonSin = new QPushButton("sin");
    QPushButton* ButtonCos = new QPushButton("cos");
    QPushButton* ButtonTg = new QPushButton("tg");
    QPushButton* ButtonCtg = new QPushButton("ctg");
    QPushButton* ButtonSec = new QPushButton("sec");
    QPushButton* ButtonSh = new QPushButton("sh");
    QPushButton* ButtonCh = new QPushButton("ch");
    QPushButton* ButtonTh = new QPushButton("th");
    QPushButton* ButtonCth = new QPushButton("cth");
    QPushButton* ButtonCsc = new QPushButton("csc");

    ButtonStep2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonStep3->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonStepY->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonStepE->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonStep10->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonAbs->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonSqrt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonCbrt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonYrt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonFactorial->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonLn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonLog->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonLogY->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonExpon->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonPi->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonSin->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonCos->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonTg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonCtg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonSec->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonSh->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonCh->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonTh->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonCth->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ButtonCsc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QString style = "QPushButton{ background: #262626; color: white; font: 15pt 'Helvetica'; "
                    "border-radius: 30px; border: 1px solid black;} QPushButton:pressed{ "
                    "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                    "stop: 0 #5E5E5E, stop: 1 #696969);}";

    ButtonStep2->setStyleSheet(style);
    ButtonStep3->setStyleSheet(style);
    ButtonStepY->setStyleSheet(style);
    ButtonStepE->setStyleSheet(style);
    ButtonStep10->setStyleSheet(style);
    ButtonAbs->setStyleSheet(style);
    ButtonSqrt->setStyleSheet(style);
    ButtonCbrt->setStyleSheet(style);
    ButtonYrt->setStyleSheet(style);
    ButtonFactorial->setStyleSheet(style);
    ButtonLn->setStyleSheet(style);
    ButtonLog->setStyleSheet(style);
    ButtonLogY->setStyleSheet(style);
    ButtonExpon->setStyleSheet(style);
    ButtonPi->setStyleSheet(style);
    ButtonSin->setStyleSheet(style);
    ButtonCos->setStyleSheet(style);
    ButtonTg->setStyleSheet(style);
    ButtonCtg->setStyleSheet(style);
    ButtonSec->setStyleSheet(style);
    ButtonSh->setStyleSheet(style);
    ButtonCh->setStyleSheet(style);
    ButtonTh->setStyleSheet(style);
    ButtonCth->setStyleSheet(style);
    ButtonCsc->setStyleSheet(style);

    engineeringLayout->setSpacing(5);

    engineeringLayout->setContentsMargins(10, 0, 10, 10);

    engineeringLayout->addWidget(ButtonStep2, 0, 0, 1, 1);
    engineeringLayout->addWidget(ButtonStep3, 0, 1, 1, 1);
    engineeringLayout->addWidget(ButtonStepY, 0, 2, 1, 1);
    engineeringLayout->addWidget(ButtonStepE, 0, 3, 1, 1);
    engineeringLayout->addWidget(ButtonStep10, 0, 4, 1, 1);
    engineeringLayout->addWidget(ButtonAbs, 1, 0, 1, 1);
    engineeringLayout->addWidget(ButtonSqrt, 1, 1, 1, 1);
    engineeringLayout->addWidget(ButtonCbrt, 1, 2, 1, 1);
    engineeringLayout->addWidget(ButtonYrt, 1, 3, 1, 1);
    engineeringLayout->addWidget(ButtonFactorial, 1, 4, 1, 1);
    engineeringLayout->addWidget(ButtonLn, 2, 0, 1, 1);
    engineeringLayout->addWidget(ButtonLog, 2, 1, 1, 1);
    engineeringLayout->addWidget(ButtonLogY, 2, 2, 1, 1);
    engineeringLayout->addWidget(ButtonExpon, 2, 3, 1, 1);
    engineeringLayout->addWidget(ButtonPi, 2, 4, 1, 1);
    engineeringLayout->addWidget(ButtonSin, 3, 0, 1, 1);
    engineeringLayout->addWidget(ButtonCos, 3, 1, 1, 1);
    engineeringLayout->addWidget(ButtonTg, 3, 2, 1, 1);
    engineeringLayout->addWidget(ButtonCtg, 3, 3, 1, 1);
    engineeringLayout->addWidget(ButtonSec, 3, 4, 1, 1);
    engineeringLayout->addWidget(ButtonSh, 4, 0, 1, 1);
    engineeringLayout->addWidget(ButtonCh, 4, 1, 1, 1);
    engineeringLayout->addWidget(ButtonTh, 4, 2, 1, 1);
    engineeringLayout->addWidget(ButtonCth, 4, 3, 1, 1);
    engineeringLayout->addWidget(ButtonCsc, 4, 4, 1, 1);


    engineering->setLayout(engineeringLayout);

    connect(ButtonStepY, SIGNAL(clicked()), this, SLOT(stepYClicked()));
    connect(ButtonYrt, SIGNAL(clicked()), this, SLOT(yRootClicked()));
    connect(ButtonLogY, SIGNAL(clicked()), this, SLOT(logYClicked()));
    connect(ButtonStep2, SIGNAL(clicked()), this, SLOT(squareClicked()));
    connect(ButtonStep3, SIGNAL(clicked()), this, SLOT(cubeClicked()));
    connect(ButtonStepE, SIGNAL(clicked()), this, SLOT(expToYClicked()));
    connect(ButtonStep10, SIGNAL(clicked()), this, SLOT(tenToYClicked()));
    connect(ButtonAbs, SIGNAL(clicked()), this, SLOT(absClicked()));
    connect(ButtonSqrt, SIGNAL(clicked()), this, SLOT(sqrtClicked()));
    connect(ButtonCbrt, SIGNAL(clicked()), this, SLOT(cbrtClicked()));
    connect(ButtonFactorial, SIGNAL(clicked()), this, SLOT(factorialClicked()));
    connect(ButtonLn, SIGNAL(clicked()), this, SLOT(lnClicked()));
    connect(ButtonLog, SIGNAL(clicked()), this, SLOT(logClicked()));
    connect(ButtonExpon, SIGNAL(clicked()), this, SLOT(expClicked()));
    connect(ButtonPi, SIGNAL(clicked()), this, SLOT(piClicked()));
    connect(ButtonSin, SIGNAL(clicked()), this, SLOT(sinClicked()));
    connect(ButtonCos, SIGNAL(clicked()), this, SLOT(cosClicked()));
    connect(ButtonTg, SIGNAL(clicked()), this, SLOT(tgClicked()));
    connect(ButtonCtg, SIGNAL(clicked()), this, SLOT(ctgClicked()));
    connect(ButtonSec, SIGNAL(clicked()), this, SLOT(secClicked()));
    connect(ButtonSh, SIGNAL(clicked()), this, SLOT(shClicked()));
    connect(ButtonCh, SIGNAL(clicked()), this, SLOT(chClicked()));
    connect(ButtonTh, SIGNAL(clicked()), this, SLOT(thClicked()));
    connect(ButtonCth, SIGNAL(clicked()), this, SLOT(cthClicked()));
    connect(ButtonCsc, SIGNAL(clicked()), this, SLOT(cscClicked()));
}


void Calc::showSimple () {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);

    setWindowTitle(tr("regular calculator"));
    setMinimumSize(380, 525);
    setMaximumSize(380, 525);

    mainLayout->addWidget(common, 0, 0, 3, 1);
    mainLayout->addWidget(simple, 4, 0, 7, 1);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("background-color: black;");

    mainWidget->layout()->setContentsMargins(0, 0, 0, 0);
}

void Calc::showEngineering () {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);

    setWindowTitle(tr("engineering calculator"));
    setMinimumSize(855, 525);
    setMaximumSize(855, 525);

    mainLayout->addWidget(common, 0, 0, 3, 9);
    mainLayout->addWidget(engineering, 4, 0, 7, 5);
    mainLayout->addWidget(simple, 4, 5, 7, 4);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("background-color: black;");

    mainWidget->layout()->setContentsMargins(0, 0, 0, 0);

}

void Calc::switchMode() {
    common->setParent(this);
    simple->setParent(this);
    engineering->setParent(this);
    delete mainLayout;
    if (!simpleRadioButton->isChecked()) {
        showEngineering();
    }
    else {
        showSimple();
    }
}

void Calc::clear() {
    slot1 = "0";
    x = 0.0;
    hasNumber = false;
    hasComma = false;
    operation = 0;
    stage = STAGE1;
    updateDisplay();
}

void Calc::updateDisplay() {
    display->setText(slot1);
}

void Calc::zeroClicked() {
    if (!hasNumber) {
        slot1 = "0";
        return updateDisplay();
    }
    if (slot1.size() > 10) {
        return;
    }
    slot1 += "0";
    updateDisplay();
}

void Calc::numberClicked() {
    if (!hasNumber) {
        slot1 = "";
        hasNumber = true;
    }
    if (slot1.size() > 10) {
        return;
    }

    QPushButton* temp_button = qobject_cast<QPushButton*>(sender());
    if(!temp_button) {
        return;
    }
    slot1 += ((QPushButton*)sender())->text();


    updateDisplay();
}

void Calc::commaClicked() {
    if (hasComma) {
        return;
    }
    if (slot1.size() > 10) {
        return;
    }
    if (!hasNumber) {
        hasNumber = true;
    }
    slot1 += ".";
    hasComma = true;
    updateDisplay();
}

void Calc::equalClicked() {
    if (stage != STAGE2) {
        return;
    }
    double y = slot1.toDouble();
    try {
        double res = operations[operation](x, y);
        if (res != res || res >= std::numeric_limits<double>::max() || res <= -std::numeric_limits<double>::max()) {
            return error();
        }
        slot1 = QString("%1").arg(res, 0, 'g', 6);
        hasComma = false;
        hasNumber = false;
        updateDisplay();
    } catch (...) {
        error();
    }
}

void Calc::binaryClicked() {
    if (stage == STAGE2) {
        equalClicked();
    } else {
        hasComma = false;
        hasNumber = false;
        stage = STAGE2;
    }
    x = slot1.toDouble();
    updateDisplay();
}

void Calc::unaryClicked() {
    hasNumber = false;
    hasComma = false;
    updateDisplay();
}

void Calc::plusClicked() {
    binaryClicked();
    operation = OPERATION_PLUS;
}

void Calc::minusClicked() {
    binaryClicked();
    operation = OPERATION_MINUS;
}

void Calc::increaseClicked() {
    binaryClicked();
    operation = OPERATION_INCREASE;
}

void Calc::divideClicked() {
    binaryClicked();
    operation = OPERATION_DIVIDE;
}

void Calc::stepYClicked() {
    binaryClicked();
    operation = OPERATION_STEP_Y;
}

void Calc::yRootClicked() {
    binaryClicked();
    operation = OPERATION_Y_ROOT;
}

void Calc::logYClicked() {
    binaryClicked();
    operation = OPERATION_LOG_Y;
}

void Calc::changeClicked() {
    if (slot1[0] == '-') {
        slot1.remove(0,1);
    } else {
        slot1 = "-" + slot1;
    }
    unaryClicked();
}

void Calc::percentClicked() {
    double y = slot1.toDouble();
    y /= 100;
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::squareClicked() {
    double y = slot1.toDouble();
    y *= y;
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::cubeClicked() {
    double y = slot1.toDouble();
    y *= y*y;
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::expToYClicked() {
    double y = slot1.toDouble();
    y = exp(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::tenToYClicked() {
    double y = slot1.toDouble();
    y = pow(10, y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::absClicked() {
    double y = slot1.toDouble();
    y = fabs(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::inverseClicked() {
    double y = slot1.toDouble();
    if (y == 0) {
        error();
        return;
    }
    y = 1/y;
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::sqrtClicked() {
    double y = slot1.toDouble();
    if (y < 0) {
        error();
        return;
    }
    y = sqrt(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::cbrtClicked() {
    double y = slot1.toDouble();
    y = cbrt(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::factorialClicked() {
    double y1 = slot1.toDouble();
    if (y1 < 0 || y1 > 103) {
        error();
        return;
    }
    unsigned long y = slot1.toULong();
    y = factorial(y);
    slot1 = QString("%1").arg((double) y, 0, 'g', 10);
    unaryClicked();
}

void Calc::lnClicked() {
    double y = slot1.toDouble();
    y = log(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::logClicked() {
    double y = slot1.toDouble();
    y = log10(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::expClicked() {
    slot1 = "2.718281828";
    unaryClicked();
}

void Calc::piClicked() {
    slot1 = "3.141592654";
    unaryClicked();
}

void Calc::sinClicked() {
    double y = slot1.toDouble();
    y = sin(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::cosClicked() {
    double y = slot1.toDouble();
    y = cos(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::tgClicked() {
    double y = slot1.toDouble();
    if (cos(y) == 0) {
        error();
        return;
    }
    y = sin(y)/cos(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::ctgClicked() {
    double y = slot1.toDouble();
    if (sin(y) == 0) {
        error();
        return;
    }
    y = cos(y)/sin(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::secClicked() {
    double y = slot1.toDouble();
    if (cos(y) == 0) {
        error();
        return;
    }
    y = 1/cos(y);
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::shClicked() {
    double y = slot1.toDouble();
    y = (exp(y) - exp(-y)) / 2;
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::chClicked() {
    double y = slot1.toDouble();
    y = (exp(y) + exp(-y)) / 2;
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::thClicked() {
    double y = slot1.toDouble();
    y = (exp(y) - exp(-y))/(exp(y) + exp(-y));
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::cthClicked() {
    double y = slot1.toDouble();
    if (y == 0.0) {
        error();
        return;
    }
    y = (exp(y) + exp(-y))/(exp(y) - exp(-y));
    slot1 = QString::number(y);
    unaryClicked();
}

void Calc::cscClicked() {
    double y = slot1.toDouble();
    if (y == 0.0) {
        error();
        return;
    }
    y = 1/sin(y);
    slot1 = QString::number(y);
    unaryClicked();
}
