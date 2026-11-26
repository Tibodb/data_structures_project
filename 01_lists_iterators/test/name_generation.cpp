#include <catch2/catch.hpp>
#include "01_lists_iterators/name_generation.hpp"
#include "01_lists_iterators/iterator_functions.hpp"
#include <algorithm>
#include <iostream> // For std::cout and std::endl
#include <list>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>


TEST_CASE("fill_vector, Same Seed Yields Same Names", "[vector]") {
    const std::size_t n_names = 10;
    const std::uint64_t seed = 42;

    std::vector<std::string> first = fill_vector(n_names, seed);
    std::vector<std::string> second = fill_vector(n_names, seed);

    SECTION("Correct amount of names is returned") {
        REQUIRE(first.size() == n_names);
        REQUIRE(second.size() == n_names);
    }

    SECTION("Same seed yields the same names") {
        REQUIRE(first == second);
    }
}

TEST_CASE("fill_list, Same Seed Yields Same Names", "[list]") {
    const std::size_t n_names = 10;
    const std::uint64_t seed = 42;

    std::list<std::string> first = fill_list(n_names, seed);
    std::list<std::string> second = fill_list(n_names, seed);

    SECTION("Correct amount of names is returned") {
        REQUIRE(first.size() == n_names);
        REQUIRE(second.size() == n_names);
    }

    SECTION("Same seed yields the same names") {
        REQUIRE(first == second);
    }

    SECTION("List and vector contain the same names") {
        std::vector<std::string> vec = fill_vector(n_names, seed);
        REQUIRE(std::equal(first.begin(), first.end(), vec.begin(), vec.end()));
    }
}

// Hulpfunctie: vangt alles op wat naar cout geschreven wordt tijdens f()
template <typename Func>
std::string capture_cout(Func f) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    f();
    std::cout.rdbuf(old);
    return buffer.str();
}

TEST_CASE("print_names prints one name per line", "[print]") {
    SECTION("vector") {
        std::vector<std::string> names = {"Anna", "Bob", "Chris"};
        std::string out = capture_cout([&] { print_names(names.begin(), names.end()); });
        REQUIRE(out == "Anna\nBob\nChris\n");
    }

    SECTION("list") {
        std::list<std::string> names = {"Anna", "Bob"};
        std::string out = capture_cout([&] { print_names(names.begin(), names.end()); });
        REQUIRE(out == "Anna\nBob\n");
    }

    SECTION("empty range prints nothing") {
        std::vector<std::string> names;
        std::string out = capture_cout([&] { print_names(names.begin(), names.end()); });
        REQUIRE(out.empty());
    }
}

TEST_CASE("filter_prefixed_names filters on prefix", "[filter]") {
    std::vector<std::string> names = {"Anna", "Annabel", "Bob", "Andre", "anna"};
    std::vector<std::string> result;

    SECTION("matching prefix (case sensitive)") {
        filter_prefixed_names(names.begin(), names.end(), "An", std::back_inserter(result));
        REQUIRE(result == std::vector<std::string>{"Anna", "Annabel", "Andre"});
    }

    SECTION("no match gives empty result") {
        filter_prefixed_names(names.begin(), names.end(), "Z", std::back_inserter(result));
        REQUIRE(result.empty());
    }

    SECTION("empty prefix copies everything") {
        filter_prefixed_names(names.begin(), names.end(), "", std::back_inserter(result));
        REQUIRE(result == names);
    }

    SECTION("prefix longer than name") {
        std::vector<std::string> short_names = {"An", "Anna"};
        filter_prefixed_names(short_names.begin(), short_names.end(), "Anna", std::back_inserter(result));
        REQUIRE(result == std::vector<std::string>{"Anna"});
    }

    SECTION("works on a list as input") {
        std::list<std::string> list_names = {"Anna", "Bob", "Andre"};
        filter_prefixed_names(list_names.begin(), list_names.end(), "A", std::back_inserter(result));
        REQUIRE(result == std::vector<std::string>{"Anna", "Andre"});
    }
}

TEST_CASE("print_reverse prints names in reverse order", "[print]") {
    SECTION("vector") {
        std::vector<std::string> names = {"Anna", "Bob", "Chris"};
        std::string out = capture_cout([&] { print_reverse(names.begin(), names.end()); });
        REQUIRE(out == "Chris\nBob\nAnna\n");
    }

    SECTION("list") {
        std::list<std::string> names = {"Anna", "Bob", "Chris"};
        std::string out = capture_cout([&] { print_reverse(names.begin(), names.end()); });
        REQUIRE(out == "Chris\nBob\nAnna\n");
    }

    SECTION("empty range prints nothing") {
        std::vector<std::string> names;
        std::string out = capture_cout([&] { print_reverse(names.begin(), names.end()); });
        REQUIRE(out.empty());
    }
}

TEST_CASE("generated names work with the iterator functions", "[integration]") {
    const std::vector<std::string> names = fill_vector(10, 42);

    SECTION("print_names and print_reverse are each other's mirror") {
        std::string forward = capture_cout([&] { print_names(names.begin(), names.end()); });
        std::string backward = capture_cout([&] { print_reverse(names.begin(), names.end()); });

        std::ostringstream expected;
        for (auto it = names.rbegin(); it != names.rend(); ++it) expected << *it << "\n";

        REQUIRE(backward == expected.str());
        REQUIRE(forward != backward);  // alleen waar als de namen niet allemaal gelijk zijn
    }

    SECTION("filtering on the first letter of the first name finds at least that name") {
        std::vector<std::string> result;
        std::string prefix(1, names.front()[0]);
        filter_prefixed_names(names.begin(), names.end(), prefix, std::back_inserter(result));

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::all_of(result.begin(), result.end(), [&](const std::string& s) {
            return s.compare(0, prefix.size(), prefix) == 0;
        }));
    }
}