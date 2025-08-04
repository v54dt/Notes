#include "fixedpoint.h"
#include <cassert>
#include <iostream>
#include <sstream>

void test_constructors() {
    FixedPoint fp1;
    assert(fp1.value == 0 && fp1.precision == 0);
    
    FixedPoint fp2(123, 2);
    assert(fp2.value == 123 && fp2.precision == 2);
}

void test_conversions() {
    // to_string
    assert(fputil::to_string(FixedPoint(123, 0)) == "123");
    assert(fputil::to_string(FixedPoint(123, 2)) == "1.23");
    assert(fputil::to_string(FixedPoint(-123, 2)) == "-1.23");
    assert(fputil::to_string(FixedPoint(5, 3)) == "0.005");
    
    // to_double
    assert(fputil::to_double(FixedPoint(123, 0)) == 123.0);
    assert(fputil::to_double(FixedPoint(123, 2)) == 1.23);
    assert(fputil::to_double(FixedPoint(-123, 2)) == -1.23);
    
    // to_int
    assert(fputil::to_int(FixedPoint(123, 0)) == 123);
    assert(fputil::to_int(FixedPoint(123, 2)) == 1);
    assert(fputil::to_int(FixedPoint(-123, 2)) == -1);
    
    // from_double
    FixedPoint fp1 = fputil::from_double(1.23, 2);
    assert(fp1.value == 123 && fp1.precision == 2);
    
    // from_string
    FixedPoint fp2 = fputil::from_string("1.23");
    assert(fp2.value == 123 && fp2.precision == 2);
    
    FixedPoint fp3 = fputil::from_string("123");
    assert(fp3.value == 123 && fp3.precision == 0);
}

void test_arithmetic() {
    FixedPoint a(123, 2);  // 1.23
    FixedPoint b(456, 2);  // 4.56
    
    // Addition
    FixedPoint sum = fputil::add(a, b);
    assert(sum.value == 579 && sum.precision == 2);
    
    // Subtraction
    FixedPoint diff = fputil::subtract(b, a);
    assert(diff.value == 333 && diff.precision == 2);
    
    // Multiplication
    FixedPoint prod = fputil::multiply(a, b);
    assert(prod.value == 56088 && prod.precision == 4);
    
    // Division
    FixedPoint quot = fputil::divide(b, a);
    assert(quot.precision <= fputil::MAX_PRECISION);
}

void test_comparisons() {
    FixedPoint a(123, 2);  // 1.23
    FixedPoint b(456, 2);  // 4.56
    FixedPoint c(123, 2);  // 1.23
    
    assert(fputil::equals(a, c));
    assert(!fputil::equals(a, b));
    assert(fputil::less_than(a, b));
    assert(!fputil::less_than(b, a));
    assert(fputil::greater_than(b, a));
    assert(!fputil::greater_than(a, b));
}

void test_operators() {
    FixedPoint a(123, 2);
    FixedPoint b(456, 2);
    
    assert(a == FixedPoint(123, 2));
    assert(a != b);
    assert(a < b);
    assert(b > a);
    assert(a <= b);
    assert(b >= a);
    
    FixedPoint sum = a + b;
    assert(sum.value == 579);
    
    FixedPoint diff = b - a;
    assert(diff.value == 333);
}

void test_stream_operators() {
    FixedPoint fp(123, 2);
    
    std::ostringstream oss;
    oss << fp;
    assert(oss.str() == "1.23");
    
    std::istringstream iss("4.56");
    FixedPoint fp2;
    iss >> fp2;
    assert(fp2.value == 456 && fp2.precision == 2);
}

void test_edge_cases() {
    // Zero values
    FixedPoint zero1(0, 0);
    FixedPoint zero2(0, 3);
    assert(fputil::equals(zero1, zero2));
    
    // Negative values
    FixedPoint neg(-123, 2);
    assert(fputil::to_string(neg) == "-1.23");
    
    // Division by zero
    try {
        fputil::divide(FixedPoint(1, 0), FixedPoint(0, 0));
        assert(false); // Should not reach here
    } catch (const std::domain_error&) {
        // Expected
    }
}

int main() {
    test_constructors();
    test_conversions();
    test_arithmetic();
    test_comparisons();
    test_operators();
    test_stream_operators();
    test_edge_cases();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}