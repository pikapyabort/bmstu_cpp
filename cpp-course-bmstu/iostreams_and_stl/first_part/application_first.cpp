#include "application_first.h"

void Application::printMenu() {
    std::cout << "   1) generate new file using fstreams" << std::endl
         << "   2) generate new file using stream iterators" << std::endl
         << "   3) load data from file using fstream" << std::endl
         << "   4) load data from file using stream iterators" << std::endl
         << "   5) modify data" << std::endl
         << "   6) modify data with iterators as parameters" << std::endl
         << "   7) modify data using for_each" << std::endl
         << "   8) modify data using transform" << std::endl
         << "   9) output result to file" << std::endl
         << "  10) output result using stream iterators" << std::endl
         << "  11) exit." << std::endl;
}

//void Application::chooseContainer() {
//    std::cout << "   1) vector" << std::endl
//         << "   2) list" << std::endl
//         << "   3) deque" << std::endl;
//    std::cout << "choose container: \n";
//    chooseContainer() ;
//    std::cin >> container;
//
//    switch (container) {
//        case 1:
//            std::vector<int> vec{};
//            break;
//        case 2:
//            std::list<int> lst{};
//            break;
//        case 3:
//            std::deque<int> dqe{};
//            break;
//        default:
//            std::cout << "choose another option." << std::endl;
//            break;
//    }
//}


void Application::run() {
    int option;
    std::string in, out;
    std::srand(std::time(nullptr));



    while(true) {
        std::cout << "choose option: \n";
        printMenu();
        std::cin >> option;

        switch(option) {
            case 1:
                std::cout << "filename: ";
                std::cin >> in;
                createDataByStreams(in, 100);
                break;
            case 2:
                std::cout << "filename: ";
                std::cin >> in;
                createDataByAlgorithms(in, 100);
                break;
            case 3:
                std::cout << "filename: ";
                std::cin >> in;
                data = loadDataByStreams<std::vector<int>>(in);
                std::cout << "loaded data: " << std::endl;
                outputResultByCout(data);
                break;
            case 4:
                std::cout << "Filename: ";
                std::cin >> in;
                data = loadDataAlgorithms<std::vector<int>>(in);
                std::cout << "loaded data: " << std::endl;
                outputResultByCout(data);
                break;
            case 5:
                //foo
                if(data.size() == 0) {
                    std::cout << "load data first!" << std::endl;
                    break;
                }
                modifyTemplate(data);
                std::cout << "modified data:" << std::endl;
                outputResultByCout(data);
                break;
            case 6:
                if(data.size() == 0) {
                   std:: cout << "load data first!" << std::endl;
                    break;
                }
                modifyIter(data.begin(), data.end());
                std::cout << "modified data:" << std::endl;
                outputResultByCout(data);
                break;
            case 7:
                if(data.size() == 0) {
                    std::cout << "load data first!" << std::endl;
                    break;
                }
                modifyForEach(data.begin(), data.end());
                std::cout << "modified data:" << std::endl;
                outputResultByCout(data);
                break;
            case 8:
                if(data.size() == 0) {
                    std::cout << "load data first!" << std::endl;
                    break;
                }
                modifyTransform<int>(in, "out_transform.txt");
                std::cout << "modified data:" << std::endl;
                outputResultByCout(loadDataByStreams<std::vector<int>>("out_transform.txt"));
                break;
            case 9:
                if(data.size() == 0) {
                    std::cout << "load and modify data first!" << std::endl;
                    break;
                }
                std::cout << "destination file: ";
                std::cin >> out;
                outputResultByStreams(out, data);
                std::cout << "done!" << std::endl;
                break;
            case 10:
                if(data.size() == 0) {
                    std::cout << "load and modify data first!" << std::endl;
                    break;
                }
                std::cout << "destination file: ";
                std::cin >> in;
                outputResultAlgorithms(in, data);
                std::cout << "done!" << std::endl;
                break;
            case 11:
                std::cout << "goodbye!" << std::endl;
                return;
            default:
                std::cout << "choose another option." << std::endl;
                break;
        }
        std::cout << std::endl;
    }
}
