/*
    Title:      Lab 01 – polynomial.cpp
    Purpose:    implement the polynomial class methods
    Author:     Tracy Mai
    Date:       April 12, 2024
*/

#include "polynomial.h"

#include <sstream>
#include <iomanip>
#include <math.h>
#include <cmath>
using std::stringstream;
using std::showpos;
using std::fixed;
using std::setprecision;
using std::max;
/**
 Implement
 1. Constructors
 2. Destructor
 3. Copy Assignment Operator
 4. ToString
 5. Read and Write
 6. The rest of the methods
*/


/**
* Polynomial Constructor
* Constructs a polynomial with each coefficient set to 0.0 to the size given
* by only the degree.
* @param the greatest degree of the polynomial, this degree + 1 is equal to
* the size of the polynomial
* @returns the newly constructed polynomial
*/
Polynomial::Polynomial(size_t degree): _degree(degree){
    _coefficients = new float[_degree + 1];
    for (size_t i = 0; i <= _degree; ++i) {
        _coefficients[i] = 0.0;
    }
}

/**
* Polynomial Constructor
* Constructs a polynomial with the given degree and coefficients by traversing
 * through the length of the polynomial and copying the coefficients to _coefficient
* @param the greatest degree of the polynomial, coefficients
* @returns the newly constructed polynomial
*/
Polynomial::Polynomial(size_t degree, const float* coefficients): _degree(degree) {
    _coefficients = new float[_degree + 1];
    for (size_t i = 0; i <= _degree; ++i) {
        _coefficients[i] = coefficients[i];
    }
}

/**
 * Polynomial Copy Constructor
 * Constructs a deep copy of the other polynomial. Allocates the same size
 * and traverses through the original polynomial and makes puts them
 * into the deep copy
 * @param other polynomial
 * @returns nothing
 */
Polynomial::Polynomial(const Polynomial& other):_degree(other._degree) {
    _coefficients = new float[_degree + 1];
    for (size_t i = 0; i <= _degree; ++i) {
        _coefficients[i] = other._coefficients[i];
    }
}

/**
* Polynomial Destructor
* Deletes the array memory originally allocated for _coefficients
* @param none
* @returns none
*/
Polynomial::~Polynomial() {
    delete[] _coefficients;
}

/**
 * Polynomial Copy Assignment Operator
 * Enables the deep copy assignment with the operator
 * @param rhs polynomial
 * @return *this to make copies
 */
const Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    delete[] _coefficients;
    _degree = rhs._degree;
    _coefficients = new float[_degree + 1];

    for (size_t i = 0; i <= _degree; ++i) {
        _coefficients[i] = rhs._coefficients[i];
    }
    return *this;
}

/**
* Polynomial Sum
* Adds the coefficients of two polynomials together when the degree is the same
* Cases to consider: When the polynomials are equal and when they are not
      * The notes in the function are spcified for when the polynomials are not equal in degree
      * Function still runs normally when the polynomials are equal in degree
* @param another polynomial, rhs
* @returns a new polynomial, that is the sum of the private this polynomial,
* and the rhs polynomial
*/
const Polynomial Polynomial:: Sum(const Polynomial& rhs)const {

    size_t smallerSize = fmin(_degree, rhs._degree);

    size_t biggerSize = max(_degree, rhs._degree);

    Polynomial sumPoly(biggerSize);

    /**
     * Adds the coefficients together up to and including the maximum degree
     * both polynomials share
     */
    for (size_t i = 0; i <= smallerSize; ++i) {
        sumPoly._coefficients[i] = _coefficients[i] + rhs._coefficients[i];
    }

    /**
     * Appends the rest of the longer polynomial to sumPoly
     */
    for (size_t j = smallerSize + 1; j <= biggerSize; ++j) {
        sumPoly._coefficients[j] = (_degree > rhs._degree) ? _coefficients[j] : rhs._coefficients[j];
    }

    return sumPoly;

}

/**
 * Polynomial Subtract
 * Subtracts coefficients of rhs polynomial from coefficients of this polynomial
 * Cases to consider: When the polynomials are equal and when they are not
      * The notes in the function are spcified for when the polynomials are not equal in degree
      * Function still runs normally when the polynomials are equal in degree
 * @param rhs polynomial
 * @returns the newly subtracted polynomial
 */
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const {

    size_t smallerSize = fmin(_degree, rhs._degree);

    size_t biggerSize = max(_degree, rhs._degree);

    Polynomial subPoly(biggerSize);

    for (size_t i = 0; i <= smallerSize; ++i) {
        subPoly._coefficients[i] = _coefficients[i] - rhs._coefficients[i];
    }

    /**
     * Appends the rest of the longer polynomial onto subPoly, making the rest of
     * rhs coefficients negative if it is larger than this._degree
     */
    for (size_t j = smallerSize + 1; j <= biggerSize; ++j) {
        subPoly._coefficients[j] = (_degree > rhs._degree) ? _coefficients[j] : -rhs._coefficients[j];
    }

    return subPoly;
}

/**
 * Polynomial Minus
 * Makes the this polynomial negative by multiplying every
 * coefficient by -1
 * @param none
 * @return a negative version of this polynomial
 */
const Polynomial Polynomial::Minus()const {
    Polynomial negPoly(*this);

    for (size_t i = 0; i <= _degree; ++i) {
        negPoly._coefficients[i] = negPoly._coefficients[i] * -1;
    }
    return negPoly;
}

/**
 * Polynomial Multiply
 * Multiplies this polynomial and rhs polynomial
 * @param rhs polynomial
 * @returns a new polynomial that results from mutiplying this and rhs
 */
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const {

    Polynomial multPoly(_degree + rhs._degree);

    for (size_t i = 0; i <= _degree; ++i) {

        for (size_t j = 0; j <= rhs._degree; ++j) {
            multPoly._coefficients[j+i] += _coefficients[i] * rhs._coefficients[j];
        }
    }
    return multPoly;

}

/**
 * Polynomial Divide
 * Divides this polynomial and rhs polynomial and ignores any remainders
 * If rhs._degree is larger than this._degree then the function simply returns zero
 * @param rhs polynomial
 * @returns a new polynomial that results from dividing this and rhs
 */
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{

    if (rhs._degree > _degree) {
        return Polynomial(0);
    }

    Polynomial divPoly(_degree - rhs._degree);

    for (size_t j = 0; j <= _degree; ++j) {
        divPoly._coefficients[j] = _coefficients[j] / rhs._coefficients[0];

        for (size_t i = 0; i <= rhs._degree; ++i) {
            _coefficients[i+j] =  _coefficients[i+j] - (divPoly._coefficients[j] * rhs._coefficients[i]);
        }
    }

    return divPoly;
}

/**
 * Polynomial Divide with Quotient and remainder
 * Divides this polynomial and rhs polynomial and stores the remainder in the variable remainder
 * @param rhs polynomial and remainder polynomial
 * @returns the quotient as a new polynomial that results from dividing this and rhs
 */
const Polynomial Polynomial::Divide(const Polynomial& rhs, Polynomial& remainder)const{

    if (rhs._degree > _degree) {
        remainder._degree = rhs._degree;

        for (size_t i = 0; i <= rhs._degree; ++i) {
            remainder._coefficients[i] = rhs._coefficients[i];
        }
    }

    /**
     * The following function is exactly the same as the divide function above
     * to determine the quotient
     */
    Polynomial divPoly(_degree - rhs._degree);

    for (size_t j = 0; j <= _degree; ++j) {
        divPoly._coefficients[j] = _coefficients[j] / rhs._coefficients[0];

        for (size_t i = 0; i <= rhs._degree; ++i) {
            _coefficients[i+j] =  _coefficients[i+j] - (divPoly._coefficients[j] * rhs._coefficients[i]);
        }
    }

    /**
     * This is my attempt to store the remainder of the coefficients in "remainder"
     */

    remainder._degree = _degree;

    for (size_t k = 0; k <= remainder._degree; ++k) {
        remainder._coefficients[k] = _coefficients[k];
    }

    return divPoly;
}

/**
 * Polynomial Derive
 * Find the derivative of the polynomial
 * @param ostream& output, the ostream output to write the polynomial
 * @returns the polynomial, written in the form: coefficient ^degree + or - ....
 */
const Polynomial Polynomial::Derive()const {

    if (_degree == 0) {
        return Polynomial(0);
    }

    Polynomial derPoly(_degree-1);

    for (size_t i = 1; i <= _degree; ++i) {
         derPoly._coefficients[i-1] = _coefficients[i] * i;
    }
    return derPoly;
}

/**
 * Polynomial Evaluate
 * Evaluates the polynomial by using the parameter float x as the x value
 * @param x
 * @return the total as a float, based on x
 */
float Polynomial::Evaluate(float x)const {

    float total = 0;

    for (size_t i = 0; i <= _degree; ++i) {
        total += pow(x, i) * _coefficients[i];
    }
    return total;
}

/**
 * Polynomial Integrate
 * Integrates the polynomial based on the parameters given
 * @param float start and float end, the borders of the polynomial
 * @returns the total of the integration as a float
 */
float Polynomial::Integrate(float start, float end)const{

    float total = 0;

    for (size_t i = 0; i <= _degree; ++i) {
        total += ((_coefficients[i] / i + 1) * pow(end, i + 1)) -
                ((_coefficients[i] / i + 1) * pow(start, i + 1));
    }
    return total;
}

/**
 * Polynomial To String
 * Writes out the polynomial in normal math form
 * @param none
 * @returns the polynomial as a string, written in the form: coefficient x ^degree + (or) - ....
 */
string Polynomial::ToString()const{
    stringstream ss;
    for (size_t i = _degree; i > 0; i--) {
        ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
    }
    ss << showpos << fixed << setprecision(2) << _coefficients[0];
    return ss.str();
}

/**
 * Polynomial Equals
 * Checks to see if this polynomial and rhs polynomial are equal by iterating
 * through the polynomials and comparing every coefficients
 * @param rhs polynomial
 * @returns true if the polynomials are equal and false if they are not
 */
bool Polynomial::Equals(const Polynomial& rhs)const {
    if (_degree != rhs._degree) {
        return false;
    }

    for (size_t i = 0; i <= _degree; ++i) {
        if (_coefficients[i] != rhs._coefficients[i]) {
            return false;
        }
    }

    return true;
}

/**
* Polynomial Write
* Writes out the largest degree of the polynomial to the ostream, followed
* by all the coefficients in the polynomial to the ostream
* @param the the ostream& output
* @returns the output with the information described above
*/
ostream& Polynomial::Write(ostream& output)const{
    output << _degree << " ";
    for (size_t i = 0; i < _degree + 1; i++) {
        output << _coefficients[i] << " ";
    }
    return output;
}

/**
* Polynomial Read
* Reads various parts of the code, ultimately to delete[] coefficients when
* necessary
* @param istream& input
* @returns the input
*/
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
