/*
 *  @author Thomas Cassimon
 *  @date   08/09/2022.
 */

#include "01_lists_iterators/name_generation.hpp"
#include <cstdlib> // srand, rand
#include <iostream>
#include <ostream>

#include "catch2/catch.hpp"
using namespace std;
// You can write this helper function and use it in the functions below
std::string generate_random_name(std::uint64_t seed) {
    // TODO: Implement This!
    string naam;
    for (int i = 0; i < 5; ++i) {
        naam += 'a' + (rand()%26);
    }
    cout << naam << endl;
    return naam;
}

std::vector<std::string> fill_vector(std::size_t n_names, std::uint64_t seed) {
    // TODO: Implement This!
    vector<std::string> vec;
    srand(seed);
    for (std::uint64_t i = 0; i < n_names; ++i) {
        vec.push_back(generate_random_name(rand()));
    }
    return vec;
}

std::list<std::string> fill_list(std::size_t n_names, std::uint64_t seed) {
    // TODO: Implement This!
    list<std::string> lijst;
    srand(seed);
    for (std::uint64_t i = 0; i < n_names; ++i) {
        lijst.push_back(generate_random_name(rand()));
    }
    return lijst;
}