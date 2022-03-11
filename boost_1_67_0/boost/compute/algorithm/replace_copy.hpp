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