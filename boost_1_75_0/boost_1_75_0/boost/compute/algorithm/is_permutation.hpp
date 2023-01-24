//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/algorithm/equal.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Permutation checking algorithm
///
/// Checks if the range [first1, last1) can be permuted into the
/// range [first2, last2)
/// \return True, if it can be permuted. False, otherwise.
///
/// \param first1 Iterator pointing to start of first range
/// \param last1 Iterator pointing to end of first range
/// \param first2 Iterator pointing to start of second range
/// \param last2 Iterator pointing to end of second range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p first1, \p last1) + distance(\p first2, \p last2))
template<class InputIterator1, class InputIterator2>
inline bool is_permutation(InputIterator1 first1,
                           InputIterator1 last1,
                           InputIterator2 first2,
                           InputIterator2 last2,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type1;
    typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;

    size_t count1 = detail::iterator_range_size(first1, last1);
    size_t count2 = detail::iterator_range_size(first2, last2);

    if(count1 != count2) return false;

    vector<value_type1> temp1(first1, last1, queue);
    vector<value_type2> temp2(first2, last2, queue);

    sort(temp1.begin(), temp1.end(), queue);
    sort(temp2.begin(), temp2.end(), queue);

    return equal(temp1.begin(), temp1.end(),
                 temp2.begin(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP

/* is_permutation.hpp
Re7yrwPjcstaAqM3dIpBe4FGt7SHBXfpo9e25A2hw3qufJfPIlZF08XKb+8PkK7CWm04uqYMPPPtXVLNAozOTfbUBOXT62h9YR7UAWYhYq7faRCLA5GNh3ksHHhpoXi8z9Xu09m9iPcxcFKn4h1aXfvjAUppqUWheF/5SX+Mc1VAIB5pLeeR1j9PPNKGDngkOg+n3WrkdzJ9yK83MS1snoLG+NJnqJRCuk8ZRQ9QUglLWpnWpBItDYTjSRER21Etgsd+og80fcou5f2zxNKWbWNG+tfYyjZwPxqq9tNbkSjnxYFySBKDe+Doq8YEBQsCLWGLU/rJJV106QT2k4DI8Gi6RU5ehj1ZAP1qmoMchIUOx9Lb4dMlQmAwXsyBvk48FX0A9FeGEPPsj8/Yvk9RK8JmqRpnntU6kmq1lfdlxJpqnzcI1aGNRA+M0sg7rAvV8HN5VVaYjGIzdrsPVBKOh9t0URbNUE61X8cKBY57pLo2r3ppr0Qp7JPOQ08z/N4id841/rFEgu9WOv2VRgkUxQ4ATyUjKua5hcBPogwXMbjdzB+7c4aOC7T45BHjPMEaM5S6Xwh84JG6krZHtS+G8wS4P6DZ6ZWt7M+kAMbXAWSUfkxG1fceZei3QIjep9r/2o9zPkeTkfN5EW5Ru8lZnz8NRKgoBJXBOuvjkXoi5RH3uklAqXWJU60A6uMWOWEY2q9CPcqJ10zYqGo/
*/