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