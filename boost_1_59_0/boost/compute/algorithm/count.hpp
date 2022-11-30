//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COUNT_HPP
#define BOOST_COMPUTE_ALGORITHM_COUNT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the number of occurrences of \p value in the range
/// [\p first, \p last).
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(n)
///
/// \see count_if()
template<class InputIterator, class T>
inline size_t count(InputIterator first,
                    InputIterator last,
                    const T &value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::count_if(first,
                                          last,
                                          _1 == value,
                                          queue);
    }
    else {
        return ::boost::compute::count_if(first,
                                          last,
                                          all(_1 == value),
                                          queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COUNT_HPP

/* count.hpp
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
*/