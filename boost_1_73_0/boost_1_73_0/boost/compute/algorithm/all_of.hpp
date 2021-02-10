//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for all of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see any_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool all_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if_not(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

/* all_of.hpp
Iuk7tunQtvzeC0yOpwNqlGolp+XBro/ipSjoQ8M6q301fKolPzR0tqYGHf8T+xWJdXjTj3oPg/FkcD/ynueDA2Onx8/zMahTAibGouB3myaDTUr7rJ9nMZD7b05IsfFapkRBuAwpDDv2d0vax0nPboh+yzRAO88c2mx6GMH2WbkEz7DMe9rHwtsBe8VKAptkchmrOZjgeAtJhHcoAjTqrGTCJb6XCwBJ0Ojx7o5NF4xjZGDcfYgY2TfdST8CDm9oMhj2I69LDfbcYCNie3AIuhRK86WROFiRkiolaGIke2XIzzZcibDlXMTSbs3LisRljQN18jCqVisoFAo1kKh7gA8uFrUrXOsNzVPxkhXMRs/qdwDYMYXBlWKkxCKVOsHJWxtWwOuBdzO5S1Ky2+9abJCxIawvSSNPBuoaRE03LF8uCylPUlly+qRecDnyxGxWyBcluEiCvw4FTg8qv8kiOwFN5+qVCywfIcLcSOyH40Dyqc0EPkNlWKjSBF7/VYDM0nQovKBR9sKd48zHzQluTq7PrJH68iLgUDlKC4w6iQkMuzhd+XFp2yHC1S8rjwJEC5R+zTqBK8UVsOlk2QqtUWvownO7c3flOsMBpAi3Q7e3neGwE0U4y8zCacvLnROlD/nte2uVpoj+Vyc0
*/