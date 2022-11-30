//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/replace.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies the value in the range [\p first, \p last) to the range
/// beginning at \p result while replacing each instance of \p old_value
/// with \p new_value.
///
/// Space complexity: \Omega(1)
///
/// \see replace()
template<class InputIterator, class OutputIterator, class T>
inline OutputIterator
replace_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             const T &old_value,
             const T &new_value,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);
    if(count == 0){
        return result;
    }

    // copy data to result
    ::boost::compute::copy(first, last, result, queue);

    // replace in result
    ::boost::compute::replace(result,
                              result + count,
                              old_value,
                              new_value,
                              queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

/* replace_copy.hpp
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
*/