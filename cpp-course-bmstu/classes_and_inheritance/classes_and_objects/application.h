#ifndef CLASSES_AND_INHERITANCE_APPLICATION_H
#define CLASSES_AND_INHERITANCE_APPLICATION_H
#include "calculator.h"

class Application {
    Calculator m_calculator;
    bool m_flagMenu;
    unsigned int m_option;
public:
    Application();
    void run();
private:
    void math();
};

#endif //CLASSES_AND_INHERITANCE_APPLICATION_H
