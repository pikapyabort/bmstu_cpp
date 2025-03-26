#include "second_part_application.h"

void ApplicationSecond::printMenu() {
    std::cout << std::endl;
    std::cout << "choose an option:" << std::endl;
    std::cout << "1. add new subject to the file" << std::endl;
    std::cout << "2. print all the subjects" << std::endl;
    std::cout << "3. search subjects by lecturer's last name" << std::endl;
    std::cout << "4. search subjects by group" << std::endl;
    std::cout << "5. search subjects by type of finals" << std::endl;
    std::cout << "6. search subjects by course work" << std::endl;
    std::cout << "7. output subjects into \"out.txt\"" << std::endl;
    std::cout << "8. delete a record" << std::endl;
    std::cout << "9. update a record" << std::endl;
    std::cout << "10. replace a record" << std::endl;
    std::cout << "11. exit" << std::endl << std::endl;
}

void ApplicationSecond::run() {
    int input = 0, ind;
    std::string tmp;

    SubjectManager manager{"../subjects.bin", "../second_part_out/out.txt"};

    while (input != 10) {
        printMenu();

        std::cin >> input;
        std::cout << std::endl;

        switch (input) {
            case 1:
                try {
                    manager.addSubject();
                }
                catch (std::runtime_error err) {
                    std::cout << err.what() << std::endl;
                }
                break;

            case 2:
                manager.printData();
                break;

            case 3:
                std::cout << "input lecturer's name: ";
                std::cin >> tmp;
                manager.findByLecturer(tmp);
                break;

            case 4:
                char code[10];
                std::cout << std::endl << "input group's code: \n";
                std::cin >> code;
                manager.findByGroup(code);
                break;

            case 5:
                bool exam_flag;
                std::cout << "input 1 to search all the course with exam and 0 – with credit: \n";
                std::cin >> exam_flag;
                manager.findByExam(exam_flag);
                break;

            case 6:
                bool cw_flag;
                std::cout << "input 1 to search all the course with course work and 0 – without course work: \n";
                std::cin >> cw_flag;
                manager.findByCourseWork(cw_flag);
                break;

            case 7:
                try {
                    manager.loadDataIntoTxt();
                }
                catch (std::runtime_error err) {
                    std::cout << err.what() << std::endl;
                }
                break;

            case 8:
                std::cout << std::endl << "input an index of the record to delete: ";
                std::cin >> ind;
                try {
                    manager.deleteRecord(ind);
                }
                catch (std::runtime_error err) {
                    std::cout << err.what() << std::endl;
                }
                break;

            case 9:
                std::cout << std::endl << "input an index of the record to update: ";
                std::cin >> ind;
                try {
                    manager.updateRecord(ind);
                }
                catch (std::runtime_error err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            case 10:
                std::cout << std::endl << "input an index of the record to replace: ";
                std::cin >> ind;
                try {
                    manager.replaceRecord(ind);
                }
                catch (std::runtime_error err) {
                    std::cout << err.what() << std::endl;
                }
                break;

            case 11:
                std::cout << std::endl << std::endl << "goodbye!" << std::endl << std::endl;
                break;

            default:
                std::cout << std::endl << std::endl << "there is no such command!" << std::endl << std::endl;
        }
    }
}