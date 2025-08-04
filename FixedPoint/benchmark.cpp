#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cmath>

#if __cplusplus >= 202002L
#include <format>
#define HAS_STD_FORMAT 1
#else
#define HAS_STD_FORMAT 0
#endif

using namespace std::chrono;

const int ITERATIONS = 1000000;

// Test data
std::vector<int> test_ints = {0, 123, -456, 999999, -999999, 42, -1, 2147483647, -2147483648};
std::vector<double> test_doubles = {0.0, 1.23, -4.56, 999.999, -999.999, 3.14159, -0.001, 1234567.89};
std::vector<std::string> test_strings = {"0", "123", "-456", "1.23", "-4.56", "999.999", "3.14159", "1234567.89"};

template<typename Func>
double benchmark(const std::string& name, Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    std::cout << name << ": " << duration << " μs\n";
    return duration;
}

// INT TO STRING BENCHMARKS
void bench_int_to_string() {
    std::cout << "\n=== INT TO STRING ===\n";
    
    // std::to_string
    benchmark("std::to_string", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (int val : test_ints) {
                volatile auto s = std::to_string(val);
            }
        }
    });
    
    // sprintf
    benchmark("sprintf", []() {
        char buffer[32];
        for (int i = 0; i < ITERATIONS; ++i) {
            for (int val : test_ints) {
                sprintf(buffer, "%d", val);
                volatile std::string s(buffer);
            }
        }
    });
    
    // snprintf
    benchmark("snprintf", []() {
        char buffer[32];
        for (int i = 0; i < ITERATIONS; ++i) {
            for (int val : test_ints) {
                int len = snprintf(buffer, sizeof(buffer), "%d", val);
                volatile std::string s(buffer, len);
            }
        }
    });
    
    // stringstream
    benchmark("stringstream", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (int val : test_ints) {
                std::stringstream ss;
                ss << val;
                volatile auto s = ss.str();
            }
        }
    });

#if HAS_STD_FORMAT
    // std::format
    benchmark("std::format", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (int val : test_ints) {
                volatile auto s = std::format("{}", val);
            }
        }
    });
#endif
}

// DOUBLE TO STRING BENCHMARKS
void bench_double_to_string() {
    std::cout << "\n=== DOUBLE TO STRING ===\n";
    
    // std::to_string
    benchmark("std::to_string", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (double val : test_doubles) {
                volatile auto s = std::to_string(val);
            }
        }
    });
    
    // sprintf
    benchmark("sprintf", []() {
        char buffer[64];
        for (int i = 0; i < ITERATIONS; ++i) {
            for (double val : test_doubles) {
                sprintf(buffer, "%.6f", val);
                volatile std::string s(buffer);
            }
        }
    });
    
    // snprintf
    benchmark("snprintf", []() {
        char buffer[64];
        for (int i = 0; i < ITERATIONS; ++i) {
            for (double val : test_doubles) {
                int len = snprintf(buffer, sizeof(buffer), "%.6f", val);
                volatile std::string s(buffer, len);
            }
        }
    });
    
    // stringstream
    benchmark("stringstream", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (double val : test_doubles) {
                std::stringstream ss;
                ss << std::fixed << std::setprecision(6) << val;
                volatile auto s = ss.str();
            }
        }
    });

#if HAS_STD_FORMAT
    // std::format
    benchmark("std::format", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (double val : test_doubles) {
                volatile auto s = std::format("{:.6f}", val);
            }
        }
    });
#endif
}

// STRING TO INT BENCHMARKS
void bench_string_to_int() {
    std::cout << "\n=== STRING TO INT ===\n";
    
    // std::stoi
    benchmark("std::stoi", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                if (str.find('.') == std::string::npos) {
                    volatile int val = std::stoi(str);
                }
            }
        }
    });
    
    // atoi
    benchmark("atoi", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                if (str.find('.') == std::string::npos) {
                    volatile int val = atoi(str.c_str());
                }
            }
        }
    });
    
    // sscanf
    benchmark("sscanf", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                if (str.find('.') == std::string::npos) {
                    int val;
                    sscanf(str.c_str(), "%d", &val);
                    volatile int v = val;
                }
            }
        }
    });
    
    // Manual parsing
    benchmark("manual parsing", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                if (str.find('.') == std::string::npos) {
                    const char* p = str.c_str();
                    bool negative = (*p == '-');
                    if (negative || *p == '+') ++p;
                    
                    int val = 0;
                    while (*p >= '0' && *p <= '9') {
                        val = val * 10 + (*p++ - '0');
                    }
                    volatile int v = negative ? -val : val;
                }
            }
        }
    });
    
    // stringstream
    benchmark("stringstream", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                if (str.find('.') == std::string::npos) {
                    std::stringstream ss(str);
                    int val;
                    ss >> val;
                    volatile int v = val;
                }
            }
        }
    });
}

// STRING TO DOUBLE BENCHMARKS
void bench_string_to_double() {
    std::cout << "\n=== STRING TO DOUBLE ===\n";
    
    // std::stod
    benchmark("std::stod", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                volatile double val = std::stod(str);
            }
        }
    });
    
    // atof
    benchmark("atof", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                volatile double val = atof(str.c_str());
            }
        }
    });
    
    // sscanf
    benchmark("sscanf", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                double val;
                sscanf(str.c_str(), "%lf", &val);
                volatile double v = val;
            }
        }
    });
    
    // Manual parsing (simplified)
    benchmark("manual parsing", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                const char* p = str.c_str();
                bool negative = (*p == '-');
                if (negative || *p == '+') ++p;
                
                double integer_part = 0;
                while (*p >= '0' && *p <= '9') {
                    integer_part = integer_part * 10 + (*p++ - '0');
                }
                
                double fractional_part = 0;
                if (*p == '.') {
                    ++p;
                    double divisor = 10;
                    while (*p >= '0' && *p <= '9') {
                        fractional_part += (*p++ - '0') / divisor;
                        divisor *= 10;
                    }
                }
                
                volatile double val = negative ? -(integer_part + fractional_part) : (integer_part + fractional_part);
            }
        }
    });
    
    // stringstream
    benchmark("stringstream", []() {
        for (int i = 0; i < ITERATIONS; ++i) {
            for (const auto& str : test_strings) {
                std::stringstream ss(str);
                double val;
                ss >> val;
                volatile double v = val;
            }
        }
    });
}

int main() {
    std::cout << "String/Number Conversion Benchmark\n";
    std::cout << "Iterations: " << ITERATIONS << " x " << test_ints.size() << " values\n";
    std::cout << "Lower is better (microseconds)\n";
    
#if HAS_STD_FORMAT
    std::cout << "C++20 std::format: ENABLED\n";
#else
    std::cout << "C++20 std::format: NOT AVAILABLE\n";
#endif
    
    bench_int_to_string();
    bench_double_to_string();
    bench_string_to_int();
    bench_string_to_double();
    
    return 0;
}