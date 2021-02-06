#include <iostream>
#include <algorithm>

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
        ForwardIterator first, ForwardIterator last, UnaryPredicate pred){
    ForwardIterator iterator_ = find_if(first, last, pred);

    for(auto current = iterator_; current != last; current++){
        if (current != last && pred(*current) && *current > *iterator_){
            iterator_ = current;
        }
    }

    return iterator_;
}

int main() {

    return 0;
}