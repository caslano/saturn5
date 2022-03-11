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