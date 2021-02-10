//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in range
/// [\p first, \p last) with the minimum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with minimum first component in given vector:
/// \code
/// // comparison function object
/// BOOST_COMPUTE_FUNCTION(bool, compare_first, (const int2_ &a, const int2_ &b),
/// {
///     return a.x < b.x;
/// });
///
/// // create vector
/// boost::compute::vector<uint2_> data = ...
///
/// boost::compute::vector<uint2_>::iterator min =
///     boost::compute::min_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element()
template<class InputIterator, class Compare>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, true, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::min_element(
            first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

/* min_element.hpp
nanI804r3sBf7BvgOa8d8M3WxkpobzdJPTGeCvbwwKBiBzH1VI2WmqybVW/nyIW+d9fQt6DOiB3w/qRQnqPebDCgdDSbYFK+nd4HSj00r/jbhx7sg092w/ehp7dPetH/UEsDBAoAAAAIAC1nSlK29eABxAQAAK8KAAAtAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfbWltZV9maWxlbmFtZS4zVVQFAAG2SCRgrVZtb9s2EP6uX3HQPiwJFLlNsXVtumJq4i5CHduwnHYBAgi0RFlcaVIgqaQB+uN3R8px0mRoP1RB9ELyeZ67493R6VUMBz/tilKig+9epf8v8cLnFjQ3+l9euacBZfkVwh8Cr/D5A1Ij2KG+lvvwQ6ivsOdR5aD1ht7L8gfkrshIuo0IfFXSK44E5IA/0d2tEevWwd7JPjx/9eoPOISjZ0fPEjhlSnAJheNqxc06gTe1H/mrZV++pJa/TYA7YDJ9QLhshQWrG3fDDAd8l6LiyvIamIWa28qIFX4IBa7l0AjJ4WQ2v8ynfydw04qqHXhudQ+21b2soWXXHAyvuLgONB0zDnSDDMhfC+uQs3dCqxTlOThuNnagISOYtBrYNROSrVCOOWid6+zr0ajqjURPRrWu7KjahiJt
*/