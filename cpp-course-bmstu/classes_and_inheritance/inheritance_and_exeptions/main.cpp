#include "application.h"

int main(){

    try {
        Application a;
        a.run();
    }
    catch (OutOfRangeException excp) {
        std::cout << excp.what() << std::endl;
    }
    catch (WrongSizeException excp) {
        std::cout << excp.what() << std::endl;
    }
    catch (DifferentSizesException excp) {
        std::cout << excp.what() << std::endl;
    }
    catch (std::bad_cast excp) {
        std::cout << excp.what() << std::endl;
    }

    return 0;
}
