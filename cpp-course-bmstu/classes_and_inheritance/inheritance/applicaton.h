#ifndef INHERITANCE_APPLICATON_H
#define INHERITANCE_APPLICATON_H
#include "dollar.h"
#include "euro.h"

class Application {
private:
    unsigned int m_option;
    Currency* m_curPtr;
    bool m_runFlag;
    void notCreated();
public:
    Application();
    ~Application();

    void run();
};
#endif //INHERITANCE_APPLICATON_H
