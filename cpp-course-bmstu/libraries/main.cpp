//Вахрамеева Констанция, вариант 2 — сортировка вставкой
#include "staticlibsort.h"
#include "dynamiclibsort.h"
#include <iostream>
#include <ctime>
#include <dlfcn.h>

//http://195.19.32.74:2038/kvakhrameeva/libraries.git

void inputArrRand(int a[], int n){
    srand(time(nullptr));

    for(int i = 0; i < n; i++)
        a[i] = rand()%100 - 50;
}

void outputArr(int a[], int n){
    for(int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "input array size:" << std::endl;
    n = 10;//std::cin >> n;

    int *arr= new int[n];
    inputArrRand(arr, n);
    std::cout << "original array:" << std::endl;
    outputArr(arr, n);
    isertionSortS(arr, n);
    std::cout << "sorted array (static library):" << std::endl;
    outputArr(arr, n);
    std::cout << "sorted array (dynamic library, implicit)::" << std::endl;
    insertionSortD(arr, n);
    outputArr(arr, n);

    typedef void (*sort)(int*, int);
    void *library;
    sort func;
    library = dlopen("/Users/fenbcn/CLionProjects/libraries/dynamiclib.dylib", RTLD_LAZY);

    //library = dlopen(".//dynamiclib.dylib", RTLD_LAZY);
    if (!library){
        std::cout << "Could not open the library!" << std::endl;
    }
    else {
        func = (sort)dlsym(library, "insertionSortD");
        if (!func){
            std::cout << "Could not find the function!" << std::endl;
        }
        else {
            (*func)(arr, n);
            std::cout << "sorted array (dynamic library, explicit):" << std::endl;
            outputArr(arr, n);
            dlclose(library);
        }
    }

    delete[] arr;

    return 0;
}

