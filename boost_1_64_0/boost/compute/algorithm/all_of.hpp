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
79UAbLzcbwrvkDs5vbVa9qkD8ukEwQL97H7Vnj1idKHS2+duEyCi9LDlWm7Db4m0Fwha04NTYzXTFFRzDEWEU5AvOnUsuax2IydpBxpVkiLJRyVW2Wg5lEFEXN/pch+ePvrcZFKwLmmIP1IJuVSzZvZp/lwQsnhAxMFyUuH7Csv9pJeME9r9WALxwK7ktcNHVgoQKFYsiLrogzLDef3kQInEwBFUWtH+9sTeHroMb8vu6hMRwbSiWpzsmGfjUJQBVq3hZYgzWBjwIzcQ0TOk8s0+M1JoIAh1lryklwm/rU16V1GCm/BkmvkNOnUpwbF6lCagNgGYVE7a8Kx66qucJhK3oRXmOLSA40V2acNlSlgHJBVYNlk5uNtl+uRFSCaDVBOxQl1ElN4JruYXzSDlir8v6XQWlKdPyO8x5uQD4Q1dlK8yqRCFttyjeZyLJcWK0klkD2Rit7JJ74xNssYy/a1Q/4z6XNiIF/ul7cgzTG0afZuQuf7UcWQca0Ywb8cBepZXHn05VAoSkzo6489m92W6VhXZ7R5ZIKKmQNOqF4wtDfEqagNmLHtHrw==
*/