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
TyeGwmw2a1fEN9+zExw/FTSewmwybWfEt96z4zq0ojB+sz06xLfsVzK+k8KkmO3JIX54Pyun2Jqe0/nkPxDjQKYuTL4WhtLrSmEGgJ+Zuj00alHDG4jrKFwL2IfSfkUt2Rfzfp6MozaA5N2vKEwF2xXRjda9dl1Z5mhlId50p/CZ+A5s7IZXB8itVmyEW6R9wNZ38z4gvik77E+F7d05vtM7MrJvhr31Jvub6b6d+Bf27X6I
*/