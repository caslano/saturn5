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
s0v+FRz7IUZarZXHrfyBjjHYwI/QP9SGZmcU4a8hM4/8F3u2QJJzbLi+9lLlXeS9v4uxIPZTTG6wnye+2gUYJ1IVTGoQ75Jn7HL5ZiyAMvlC6UFbWT/6SCzacYbGohkHXRIfQE/gP9izRfx0ja3kSqq8j1rcx1rsNTKgxX2ixX16i559Lp9nEZRRiyfoEIbqZGsF/1AVIjDSmT8Tff0kPxJIhxnxeP4Jw/mFDxjt1kt+OIZ36h0mG+vJoRdPOrr8OW0ZYB/ARiTmWRhIbc2FiIby0JXstbnKL19BqE78wNvvAO9HzQX56owpG7KrIOaUljA70QJHHjPGV3kSoM5iTQZr/eyzZwmFs4hCAdTPwQgeQLSl/JySxwaZwK9/RzjD92fPDhP9DjP6HZ9oNaYqOyzod5jkFGLLeA5LPs9SKJutWsCZPG62CqLosTrkvyAhxRE8MsZ6sR9WcCgkb7O/o9h9s4+yVh4ZxRdgWfIR1lIbcbCqPT9YJbKizTgq+Wa8jYWO2X9hY5exG3Rdb5Jd+pOtbDoeC/kJ1KPWuPzZoycMn0hH1+A8Az8rwcglyIkyNYAghb5M60T9OBeckzir9WStpyObTMvJz1ScpxxvOE8pjk6OF0cnGU+c2qdjxdNY7SmJOD61iWMcNu0YR2cYElZ0oiHBRMcvoOsaj18U3VozDkJUsbXlBNb5gb/93+b8lXcph8bxwgxD4dZx
*/