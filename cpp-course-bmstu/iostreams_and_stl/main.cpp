#include "first_part/application_first.h"
#include "second_part/second_part_application.h"

int main() {
    Application first{};
    ApplicationSecond second {};

    int input = 0;

    while (input != 3) {

        std::cout << "1. test first task\n" <<
        "2. test second task\n" <<
        "3. exit\n";
        std::cin >> input;

        switch (input) {
            case 1:
                first.run();
                break;

            case 2:
                second.run();
                break;

            case 3:
                std::cout << std::endl << std::endl << "goodbye!" << std::endl << std::endl;
                break;

            default:
                std::cout << std::endl << std::endl << "there is no such command!" << std::endl << std::endl;
        }
    }

    return 1;
}


