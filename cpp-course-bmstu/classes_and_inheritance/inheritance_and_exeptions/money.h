#ifndef CLASSES_AND_INHERITANCE_MONEY_H
#define CLASSES_AND_INHERITANCE_MONEY_H
#include "array.h"
#include <string>
#include "exception.h"

class Money : public Array {
public:
    Money(const double d);
    explicit Money(int newSize = 0, const unsigned char *arr = nullptr);
    
    void arrSum(const Array &p_other, Array &p_result) const override; //!!! Где override?
    //добавила
    
    void operator=(const Money &mon); //!!! У этого метода нет реализации и неверный тип возвращаемого значения.
    
    const std::string toString() const override;
    friend std::ostream &operator<<(std::ostream &out, const Money &m);
    friend std::istream &operator>>(std::istream &in,  Money &m);
};

#endif
