#include "applicaton.h"
using std::cout;
using std::cin;
using std::endl;


//!!! Нет демонстрации работы с полиморфизмом. Где подменю?
//!!! Указатель на базовый класс должен быть полем класса.
//исправила

Application::Application() : m_option(0), m_curPtr(nullptr), m_runFlag(true) {}

Application::~Application() {
    delete m_curPtr;
}

void Application::notCreated() {
    std::cout << "No Currency objects yet assigned!" << std::endl;
}

void Application::run() {

    while (m_runFlag) {
        std::cout << std::endl << "Menu:" << std::endl
        << "1. make an USD object" << std::endl
        << "2. make an EUR object"<< std::endl
        << "3. output value" << std::endl
        << "4. convert to rubles" << std::endl
        << "---------press 0 to exit---------" << std::endl << std::endl;

        std::cin >> m_option;

        switch (m_option) {
            case 0:
                m_runFlag = false;
                break;
            case 1:
                m_curPtr = new Dollar;
                cout << "Input the number of dollars:" << endl;
                cin >> *m_curPtr;
                cout << "Created object: " << *m_curPtr << endl;
                delete m_curPtr;
                break;
            case 2:
                m_curPtr = new Euro;
                std::cout << "Input the number of euros:" << std::endl;
                std::cin >> *m_curPtr;
                std::cout << "Created object: " << *m_curPtr << std::endl;
                delete m_curPtr;
                break;
            case 3:
                m_curPtr ? m_curPtr->print(std::cout) : this->notCreated();
                break;
            case 4:
                std::cout << (m_curPtr ?
                          (std::to_string((static_cast<int>(m_curPtr->toRuble())*100) / 100.)  + "₽") :
                          ("No Currency objects yet assigned!"))
                          << std::endl;
                break;
            default:
                cout << "No such option!" << std::endl;
                break;
        }
    }
}
