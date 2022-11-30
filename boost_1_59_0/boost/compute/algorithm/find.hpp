//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) that equals \p value.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline InputIterator find(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::find_if(
                   first,
                   last,
                   _1 == value,
                   queue
               );
    }
    else {
        return ::boost::compute::find_if(
                   first,
                   last,
                   all(_1 == value),
                   queue
               );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_HPP

/* find.hpp
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
*/