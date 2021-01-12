//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for any of the elements in
/// the range [\p first, \p last).
///
/// For example, to test if a vector contains any negative values:
///
/// \snippet test/test_any_all_none_of.cpp any_of
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool any_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) != last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

/* any_of.hpp
vqP5/tf/+RW5Z/D3/0/o7v4X8YIN73FjrQd30GktICfdbX6nSS2J8UZTgztN8ve2JlEaA5W2SoL5vX/yV8L1reX94hLyP2y2zkdc6zcD6rEGziX/IfK37q4hewvTNT/Ssr7rzzrT11OYsWZ7AIgf+f74UZSnnML0luWZBrvlnfe7I94dp/sAVRSmi0yvkuzxJveljOkdpDtsUleXwh/jeztKGu0VVFZVhn7HawvF/UzsR9pJ
*/