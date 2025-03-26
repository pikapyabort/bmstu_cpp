#include <iostream>
#include "Vector.h"
#include "Matrix.h"

int main() {
    int dim, jsize;
    double defaultVal, scalar;
    std::cout << "Input vector1 and matrix1 sizes:" << std::endl;
    std::cin >> dim;
    std::cout << "Input vector1 default value:" << std::endl;
    std::cin >> defaultVal;
    Vector vector1 {dim, defaultVal}, vector2 {vector1};
    std::cout << "Initialized vector1 (operator '<<'): " << vector1 << std::endl;
    std::cout << "Copied vector1 (vector2): " << vector2 << std::endl;
    std::cout << "Input vector1 values (operator '>>'). ";
    std::cin >> vector1;
    std::cout << "New vector1: " << vector1 << std::endl;
    vector2 = vector1;
    std::cout << "Copied vector1 (operator '='): " << vector2 << std::endl;
    std::cout << "+vector1 (unary operator '+'): " << +vector1 << std::endl;
    std::cout << "-vector1 (unary operator '-'): " << -vector1 << std::endl;
    std::cout << "Input another vector2 values. ";
    std::cin.get();
    std::cin >> vector2;
    Vector expVector1{vector2};
    std::cout << "vector1 + vector2 (operator '+'): " << vector1 << " + " << vector2 << " = " << vector1 + vector2 << std::endl;
    std::cout << "vector1 - vector2 (operator '-'): " << vector1 << " - " << vector2 << " = " << vector1 - vector2 << std::endl;
    std::cout << "vector1 * vector2 (operator '*'): " << vector1 << " * " << vector2 << " = " << vector1 * vector2 << std::endl;
    vector2 += vector1;
    expVector1 -= vector1;
    std::cout << "vector1 + vector2 (operator '+='):" << vector2 << " * " << vector1 << " = " << vector2 << std::endl;
    std::cout << "vector2 - vector1 (operator '-='): " << vector2 << " * " << vector1 << " = " << expVector1 << std::endl;
    std::cout << "Input scalar value to multiply vector1 on:" << std::endl;
    std::cin >> scalar;
    std::cout << "scalar * vector1 = " << scalar * vector1 << std::endl
              << "vector1 * scalar = " << vector1 * scalar << std::endl;
    std::cout << "Printing each element of the vector1 (operator []):" << std::endl;
    for (int i = 0; i < vector1.getDim(); ++i) {
        std::cout << vector1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Vector dimension (method getDim()) = " << vector1.getDim() << std::endl;
    std::cout << "Vector getLength (method detLength()) = " << vector1.getLength() << std::endl;
    double len {vector1};
    std::cout << "Vector getLength (operator double()) = " << len << std::endl;

    std::cout << "Input CSRMatrix(operator '>>'). ";
    std::cin.get();
    CSRMatrix expMatrix{nullptr, nullptr, nullptr, 0, 0};
    std::cin >> expMatrix;
    std::cout << "Initialized matrix (operators '<<', '>>'):" << std::endl;
    std::cout << expMatrix << std::endl;
    scalar = 5;
    std::cout << "scalar*matrix (operator '*') = \n" << scalar * expMatrix << "\n\n"
              << "matrix*scalar (operator '*') = \n" << expMatrix * scalar << "\n\n";

    std::cout << "vector1*matrix (operator '*') = " << vector1 * expMatrix << std::endl
              << "matrix*vector1 (operator '*') = " << expMatrix * vector1 << std::endl;
    std::cout << "Matrix dimension (method getDimension()) = " << expMatrix.getDimention() << std::endl;
    std::cout << "The amount of non-zero elements in the matrix (method getNumberOfValues()) = " << expMatrix.getNumberOfValues()
              << std::endl;
    std::cout << "Complex expression ((vector1*(matrix*2)+vector1)*(3*vector1)) = " << (vector1 * (expMatrix * 2) + vector1) * (3 * vector1) << std::endl;


    std::cout << "Trying to add vectors of different sizes:" << std::endl;
    Vector erVector{dim + 1};
    try {
        vector2 = vector1 + erVector;
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }
    std::cout << "Trying to get vector1 value out of vector1 range:" << std::endl;
    try {
        double a = vector1[dim + 10];
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }
    std::cout << "Trying to multiply vector1 and matrix of different dimensions:" << std::endl;
    Vector erVector2{dim + 10, 10};
    try {
        vector2 = expMatrix * erVector2;
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }




    return 0;
}