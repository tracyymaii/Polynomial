#include "polynomial.h"

#include <sstream>
#include <iomanip>
using std::stringstream;
using std::showpos;
using std::fixed;
using std::setprecision;
/**
 Implement
 1. Constructors
 2. Destructor
 3. Copy Assignment Operator
 4. ToString
 5. Read and Write
 6. The rest  of the methods

*/

const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
    return Polynomial(0);
}
const Polynomial Polynomial::Divide(const Polynomial& rhs, Polynomial& remainder)const{
    remainder = Polynomial(0);
    return Polynomial(0);
}
float Polynomial::Integrate(float start, float end)const{
    return 0.0;
}
string Polynomial::ToString()const{
    stringstream ss;
    for (size_t i = _degree; i > 0; i--) {
        ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
    }
    ss << showpos << fixed << setprecision(2) << _coefficients[0];
    return ss.str();
}
ostream& Polynomial::Write(ostream& output)const{
    output << _degree << " ";
    for (size_t i = 0; i < _degree + 1; i++) {
        output << _coefficients[i] << " ";
    }
    return output;
}
istream& Polynomial::Read(istream& input){
    size_t degree;
    input >> degree;
    if (input.fail()){
        return input;
    }
    float* coefficients = new float[degree + 1];
    for (size_t i = 0; i < degree + 1; i++) {
        input >> coefficients[i];
        if (input.fail()){
            delete[] coefficients;
            return input;
        }
    }

    if (degree != _degree){
        if (_coefficients){
            delete[] _coefficients;
        }
        _degree = degree;
        _coefficients = coefficients;
    }else{
        for (size_t i = 0; i < _degree + 1; i++) {
            _coefficients[i] = coefficients[i];
        }
        delete[] coefficients;
    }
    return input;
}
