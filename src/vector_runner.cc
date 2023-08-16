#include <iostream>

#include "vector.h"

int main() {
    nstd::vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.append(i);
        std::cout << "size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;
        std::cout << vec;
    }
    nstd::vector<int> vec2(10, 5);
    std::cout << vec2;
    int idx = 0;
    std::cout << vec2[idx];
    nstd::vector<int> vec3(vec2);
    return 0;
}
