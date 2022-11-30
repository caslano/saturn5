//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/mismatch.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the range [\p first1, \p last1) and the range
/// beginning at \p first2 are equal.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    return ::boost::compute::mismatch(first1,
                                      last1,
                                      first2,
                                      queue).first == last1;
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  InputIterator2 last2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) != std::distance(first2, last2)){
        return false;
    }

    return ::boost::compute::equal(first1, last1, first2, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

/* equal.hpp
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
*/