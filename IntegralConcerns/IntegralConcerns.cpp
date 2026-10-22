#include <concepts>
#include <iostream>
#include <cmath>

template<std::floating_point T>
using IntegrateCallback = T(*)(T);

template<std::floating_point T>
constexpr T integrate(IntegrateCallback<T> callback, T a, T b, size_t precision = 100) {
    T width = (b - a) / precision;
    T area = 0.0;

    for (size_t i = 0; i < precision; ++i) {
        T x = a + i * width;
        T height = callback(x);

        area += width * height;
    }

    return area;
}

namespace ops {

constexpr double keep(double x) {
    return x;
}

constexpr double square(double x) {
    return x * x;
}

constexpr double constant(double x) {
    return 5.0;
}

}

consteval bool runTests() {
    static_assert(integrate<double>(ops::keep, 0, 4.0, 4.0) == 6.0);
    static_assert(integrate<double>(ops::square, 0, 6.0, 3.0) == 40.0);
    static_assert(integrate<double>(ops::constant, 0.0, 10.0) == 50.0);

    static_assert(integrate<double>(ops::keep, 0.0, 4.0, 1) == 0.0);
    static_assert(integrate<double>(ops::keep, 0.0, 4.0, 2) == 4.0);

    return true;
}

int main()
{
    static_assert(runTests(), "Tests failed");

    double squared = integrate<double>(ops::square, 0, 4);

    std::cout << "Square of 0 & 4 (p100): " << squared << "\n";
}