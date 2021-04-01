//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/max_element.hpp>
#include <boost/compute/algorithm/min_element.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators with the first pointing to the minimum
/// element and the second pointing to the maximum element in the range
/// [\p first, \p last).
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element(), min_element()
template<class InputIterator, class Compare>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               Compare compare,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, compare, queue),
                          max_element(first, last, compare, queue));
}

///\overload
template<class InputIterator>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, queue),
                          max_element(first, last, queue));
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

/* minmax_element.hpp
kkBw/eKvYqF0JNwPITgz3FsPPYEL8SPXjSooT8VpnMNf+Bg1oiFb5pETFb+qYNxFlCyIgaTnRCUTeU54LLvy4gpN6FTF4J+rx9t2ca03QLfdtz+4DBwC80IO2VLn9uPB4dw1zWt00ltTnPVWvH+MFtnM9ASsLS3QArQ70XZSucvpO2EqavSY/+AFV0Tliuad7IR/ce8Zv4YqiUVY0WuTzJa5xehmchG6Mj65Eid46RCfCDnyHns+ocUsCTj25pd5Ro3suHosWnfSzFyGlnESy++tT3VLgSsrsPuCgsvz9ai4+mC+36WO4ouxoMVQARLwy1UGe8oVMrglcwi/kZzMm14b+ni/ISEN3ZejpGvaOble+r2zdVNAWyCF64vPB4h1UscRZH4tAQ+flVsQxLr6ulCUvcwR6N2+o1wa2xqZ5dsc3jrJCTDZHGgqAmwQ99F7gtUUMxxOj5jz51diwsvJuNbhQPV97zIvLdvV4JqE8kQYxLktMUsPGwZYQYwy1ly5fj/Jl09nqOYLoq9/oEyvXYGiQ1HYZSSZPnp6XkU5uEubN1xrqt6HCrj16A==
*/