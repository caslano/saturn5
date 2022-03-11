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