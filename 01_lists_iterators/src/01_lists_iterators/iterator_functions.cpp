#include "01_lists_iterators/iterator_functions.hpp"
#include <iostream> // For std::cout and std::endl
#include <vector> // For std::vector
#include <algorithm> // For std::for_each, std::copy_if
#include <iterator>
#include <list> // For std::list
#include <string>

using namespace std;

template <typename IteratorType>
void print_names(IteratorType begin, IteratorType end)
{
    // TODO: Fill this in!
    using ValueType = typename std::iterator_traits<IteratorType>::value_type;
    copy(begin,end,ostream_iterator<ValueType>(std::cout, "\n"));
}

template <typename InputIteratorType, typename OutputIteratorType>
void filter_prefixed_names(
        InputIteratorType begin,
        InputIteratorType end,
        std::string prefix,
        OutputIteratorType output_begin
)
{
    // TODO: Fill this in!
    copy_if(begin,end,output_begin,[&prefix](const string& naam) {
        return naam.compare(0,prefix.size(),prefix) == 0;
    });

}

template <typename IteratorType>
void print_reverse(IteratorType begin, IteratorType end)
{
    // TODO: Fill this in!
    using ValueType = typename std::iterator_traits<IteratorType>::value_type;
    vector<ValueType> reverse(begin, end);
    copy(reverse.rbegin(),reverse.rend(),ostream_iterator<ValueType>(std::cout,"\n"));
}

// TODO: If you need explicit instantiations of the functions above, fill them in here!
// We will teach the templates course later in the course, so don't worry about this for now.
// If you want to learn more about templates, you can check out the following link:
// https://en.cppreference.com/w/cpp/language/templates

using VecIt   = std::vector<std::string>::iterator;
using VecCIt  = std::vector<std::string>::const_iterator;
using ListIt  = std::list<std::string>::iterator;
using BackIns = std::back_insert_iterator<std::vector<std::string>>;

template void print_names<VecIt>(VecIt, VecIt);
template void print_names<VecCIt>(VecCIt, VecCIt);
template void print_names<ListIt>(ListIt, ListIt);

template void print_reverse<VecIt>(VecIt, VecIt);
template void print_reverse<VecCIt>(VecCIt, VecCIt);
template void print_reverse<ListIt>(ListIt, ListIt);

template void filter_prefixed_names<VecIt, BackIns>(VecIt, VecIt, std::string, BackIns);
template void filter_prefixed_names<VecCIt, BackIns>(VecCIt, VecCIt, std::string, BackIns);
template void filter_prefixed_names<ListIt, BackIns>(ListIt, ListIt, std::string, BackIns);