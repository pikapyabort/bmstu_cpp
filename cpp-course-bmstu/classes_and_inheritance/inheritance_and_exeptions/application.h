#ifndef CLASSES_AND_INHERITANCE_APPLICATION_H
#define CLASSES_AND_INHERITANCE_APPLICATION_H
#include "array.h"
#include "bitstring.h"
#include "money.h"
#include "exception.h"

class Application {
private:
    unsigned int m_option;
    Array* m_first;
    Array* m_second;
    Array* m_result;
    bool m_run_flag;
public:

    ///!! Это и без default предоставляется
    //исправила
    //Application() = default;
    //~Application() = default;

    void run();

private:
    void menuArray();
    void menuBitSrting();
    void menuMoney();
};

#endif //CLASSES_AND_INHERITANCE_APPLICATION_H
