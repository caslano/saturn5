//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H
#define BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H

#include <cstddef>
#include <algorithm>
#include <iterator>

namespace boost {
namespace compute {
namespace detail {

// This is a convenience function which returns the size of a range
// bounded by two iterators. This function has two differences from
// the std::distance() function: 1) the return type (size_t) is
// unsigned, and 2) the return value is always positive.
template<class Iterator>
inline size_t iterator_range_size(Iterator first, Iterator last)
{
    typedef typename
        std::iterator_traits<Iterator>::difference_type
        difference_type;

    difference_type difference = std::distance(first, last);

    return static_cast<size_t>(
        (std::max)(difference, static_cast<difference_type>(0))
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H

/* iterator_range_size.hpp
uS5yZ32Lv3UkQ6mQC3+2jDSM+2BTcWacYI/iQqsPqqx6X1J9FxXVu0z8cLaLsTE5E76BS0DWoOCbdBtCxnePOJnkA1JkvTM/moTJdPSFXPhGrLwKcj6i4icCUjZHuiMgkS7OFZC4n/Erbh4tTyIyqkWrIuWuo1MJUajlsUrVNkm12iYOU6m2HK3YgNZImNOLlQlDi4bJwJJsr0wlVc0+DZRzokQlVW7VJEVNdNTeecvphKG8Tky4zu9L5FJ4yKcYeF1u82q1TTafnV4ucy90+O6ldJ1sRsNEH7ovkbkUKnJeShe05zRMhF9viWw++JKWSYbQD1s/7PpN4RA4+aFSFTLf6Kyy94m+LY9SoGOhpJZU1bWYqqpFsdtBlTl410ndYn3l1lcbDxXFLlFerC9kQjr052jZMn87WrYJeix5L13ml/R6KVWAl2a/f7jkS9Rq6XNHFeu9dG3ULHZu+rvczOFSi7OHBZOJG0caKSBxJz2KLQUkX47UXUAK5UjhEfKkcI4UICBFc6SxAlI8R7IVkBI5kqmAlMyR2glIeRxpz1LB7MiR7vSSb2M5R4oUpGJqc3OzgKTHkSYISPocaaiAZMiRkhbLk8w40obH7+XlxZGWCEjRHGnGY9hXI6VbUEeXiiZpErITcqtoEkxDHhVNfCXcVxEFG0262SbbleBU2SQymQ1Ld1WsTR1RWI07sRrhY/6etawlRXOHvOe3
*/