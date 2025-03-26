#include "application.h"

using std::cout;
using std::cin;
using std::endl;

void Application::run() {

    while (m_run_flag) {
        cout << endl << "Menu:"
                 // << endl << "1. array (base class) test"
                  << endl << "1. bit (derived class) string test "
                  << endl << "2. money (derived class) test" << endl
                  << "---------press 0 to exit---------" << endl << endl;

        cin >> m_option;

        switch (m_option) {
            case 0:
                m_run_flag = false;
                break;
           // case 1:
                // menuArray();
                // break;
            case 1:
                menuBitSrting();
                break;
            case 2:
                menuMoney();
                break;

            default:
                cout << "No such option!";
                break;
        }
    }
}
void Application::menuMoney() {
    double mon;
    int arrSize, ind;
    bool money_flag = true;
    m_result = new Money;
    m_first = new Money;
    m_second = new Money;

    Money *money_result = dynamic_cast<Money *>(m_result);
    Money *money_first = dynamic_cast<Money *>(m_first);
    Money *money_second = dynamic_cast<Money *>(m_second);

    //cout << "Dynamic cast test: ";
    //cout << typeid(money_first).name() << typeid(money_second).name() << typeid(money_result).name() << endl;


    if (money_result && money_first && money_second) {
        while (money_flag){

        std::cout << std::endl << "Money menu:"
				<< std::endl << "1. input first money string" 
                << std::endl << "2. input second money string"
				<< std::endl << "3. output money strings "
				<< std::endl << "4. sum money operands" << endl
                << "---------press 0 to exit---------" << endl << endl;

            
            std::cin >> m_option;
            switch (m_option) {
            case 0:
				money_flag = false;
				break;
			case 1:
				std::cin >> *money_first;
				break;
			case 2:
				std::cin >> *money_second;
				break;
			case 3:
				std::cout << "1) " << *money_first << std::endl
					<< "2) " << *money_second<< std::endl;
				break;
			case 4:
				m_first->arrSum(*m_second, *m_result);
				std::cout << "= " << *m_result << std::endl;
				break;
			default:
				money_flag = false;
				break;
			}
        }
        
        
        
        
        
        
        //!!! Вы для этих указателей new использовали?
        //исправила
        delete m_result;
        delete m_first;
        delete m_second;
    }
    else {
        std::cout << "Couldn't cast!" << std::endl;
    }
    //     cout << "Input size of the array and the array to make first money class object:" << std::endl;
    //     cin >> arrSize;
    //     unsigned char mArr[100];
    //     for (int i = 0; i < arrSize; ++i) {
    //         cin >> mArr[i];
    //     }
    //     money_first = {arrSize, mArr};
    //     cout << "Input a double to make second money class object:" << std::endl;
    //     cin >> mon;
    //     money_second = {mon};

    //     while (flag) {
    //         cout << endl << "Class Money Menu:" << endl
    //              << "1. change first operand" << endl
    //              << "2. change second operand" << endl
    //              << "3. output objects" << endl
    //              << "4. sum two onjects" << endl
    //              << "---------press 0 to exit---------" << endl << endl;
    //         cout << "______________________________________________________________" << endl << endl;

    //         cout << "Created objects:" << endl
    //              << *dynamic_cast<Money *>(m)
    //              << endl //!!! НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ dynamic_cast БЕЗ ПРОВЕРКИ ПРАВИЛЬНОСТИ ПРИВЕДЕНИЯ!
    //              << *dynamic_cast<Money *>(dM) << endl;
    //         m->arrSum(dM, m_result);
    //         cout << "Sum of the objects:" << endl
    //              << *dynamic_cast<Money *>(m_result) << endl;
    //         delete m;
    //         delete dM;
    //         delete m_result;
    //     }
    // }
}

void Application::menuBitSrting() {
    m_first = new BitString;
	m_second = new BitString;
	m_result = new BitString;

	BitString* bs_first = dynamic_cast<BitString*>(m_first);
	BitString* bs_second = dynamic_cast<BitString*>(m_second);
	BitString* bs_result = dynamic_cast<BitString*>(m_result);
    bool bs_flag = true;

    if (bs_first && bs_second && bs_result) {
        while (bs_flag) {
        std::cout << std::endl << "Bti string menu:"
				<< std::endl << "1. input first bit string" 
                << std::endl << "2. input second bit string"
				<< std::endl << "3. output bit strings "
				<< std::endl << "4. XOR bit operands"
				<< std::endl << "5. AND bit operands"
				<< std::endl << "6. OR bit operands"
				<< std::endl << "7. NOT first"
				<< std::endl << "8. NOT second"
				<< std::endl << "---------press 0 to exit---------" 
                << endl << endl;
			std::cin >> m_option;

			switch (m_option) {
            case 0:
				bs_flag = false;
				break;
			case 1:
				std::cin >> *bs_first;
				break;
			case 2:
				std::cin >> *bs_second;
				break;
			case 3:
				std::cout << "1. " << *bs_first << std::endl
					<< "2. " << *bs_second << std::endl;
				break;
			case 4:
				m_first->arrSum(*m_second, *m_result);
				std::cout << "= " << *bs_result << std::endl;
				break;
			case 5:
				std::cout << "= " << bs_first->andFunc(*bs_second) << std::endl;
				break;
			case 6:
				std::cout << "= " << bs_first->orFunc(*bs_second) << std::endl;
				break;
			case 7:
				std::cout << "= " << bs_first->notFunc() << std::endl;
				break;
            case 8:
				std::cout << "= " << bs_second->notFunc() << std::endl;
				break;
			default:
				std::cout << "No such option!" << std::endl;
				break;
			}
	    }	
        delete m_first; 
		delete m_second;
		delete m_result;
    }
    else {
        std::cout << "Couldn't cast!" << std::endl;
    }

    // m_result = new BitString;
    // cout << std::endl << "3. BitString class (derived)" << endl << endl;
    // cout << "______________________________________________________________" << endl << endl;
    // cout << "Input size of the arrays and 2 arrays to make bitstring class objects:" << endl;
    // cin >> arrSize;
    // unsigned char bArr[100];
    // unsigned char bArr1[100];
    // for (int i = 0; i < arrSize; ++i) {
    //     cin >> bArr[i];
    // }
    // for (int i = 0; i < arrSize; ++i) {
    //     cin >> bArr1[i];
    // }
    // Array* s = new BitString{arrSize, bArr};
    // Array* r = new BitString{arrSize, bArr1};
    // cout << "Created objects:" << endl
    //      << *s << endl
    //      << *r << endl
    //      << "Logic operators:" << endl
    //      << "a and b: " << dynamic_cast<BitString*>(s)->andFunc(*dynamic_cast<BitString*>(r)) << endl
    //      << "a or b: " << dynamic_cast<BitString*>(s)->orFunc(*dynamic_cast<BitString*>(r)) << endl
    //      << "a xor b: " << dynamic_cast<BitString*>(s)->xorFunc(*dynamic_cast<BitString*>(r)) << endl
    //      << "not a: " << dynamic_cast<BitString*>(s)->notFunc() << std::endl
    //      << "Array sum:" << endl;
    // s->arrSum(r, m_result);
    // cout << *dynamic_cast<BitString*>(m_result) << endl;
    // delete s;
    // delete r;
    // delete m_result;
}


void Application::menuArray() {
//     int arrSize, ind;
//     auto* result = new Array;
//     cout << "1. Array (base class)" << endl << endl;
//     cout << "______________________________________________________________" << endl << endl;
//     cout << "Input size of the array and the array itself:" << endl;
//     cin >> arrSize;
//     unsigned char arr[100];
//     unsigned char arr1[100];
//     for (int i = 0; i < arrSize; ++i) {
//         cin >> arr[i];
//     }

//     auto* a = new Array(arrSize, arr);
//     cout << "Input array:" << endl << *a << endl
//          << "Input an index of the array element:" << endl;
//     cin >> ind;
//     cout << "arr[index]: " << (*a)[ind] << endl
//          << "Input another array the same size:" << endl;
//     for (int i = 0; i < arrSize; ++i) {
//         cin >> arr1[i];
//     }

//     auto* b = new Array(arrSize, arr1);
//     a->arrSum(b, result);
//     cout << "'Sum' of the array's elements:" << endl << *result << endl;
//     delete a;
//     delete b;
//     delete result;
// }
}

