//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/transform_if.hpp>
#include <boost/compute/functional/identity.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

// like the copy_if() algorithm but writes the indices of the values for which
// predicate returns true.
template<class InputIterator, class OutputIterator, class Predicate>
inline OutputIterator copy_index_if(InputIterator first,
                                    InputIterator last,
                                    OutputIterator result,
                                    Predicate predicate,
                                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type T;

    return detail::transform_if_impl(
        first, last, result, identity<T>(), predicate, true, queue
    );
}

} // end detail namespace

/// Copies each element in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p result.
///
/// Space complexity: \Omega(2n)
template<class InputIterator, class OutputIterator, class Predicate>
inline OutputIterator copy_if(InputIterator first,
                              InputIterator last,
                              OutputIterator result,
                              Predicate predicate,
                              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type T;

    return ::boost::compute::transform_if(
        first, last, result, identity<T>(), predicate, queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_IF_HPP

/* copy_if.hpp
kDRGSDT06a8hhFJs6QR8iM/OX/z8wlTLZBjE2S1Mky/j4CXMCTrPocqwY7JFw2Id+FoYrWquHChWcx+YraazeZZmQXwFvwiVy7bgcElIncuqz0FsG/xvCmFeMQPvX2QZ5NhqB9370INCOPwdKbHCo9+Ms+tFOl+ms+lLdoMhtYtBo43z3t4b1qBzPE1q+tOxslU5TQgZlSkyccDrVjK0p3AWthyHTGCQd6DRO1GQbwFvyomcSRxYdFPJ8k4CJiXOAjfMCXUf2IN1vKZR7wTdtkIWlqwz6JTAQ7AX6uJ8GAeBn6UWy12Xqa+lNJwPLobrcu45d3qj9ciEFFhxRevgHZqz0AqLRGch69grk3xN0klylU7S5SrwTj6WiueQ5ZYAa02bozT9HPkhzZ/oJvOU9hEDxVH/ssX0PIbUBR5AYGc4KwioZqhK+LRJcBwOODetQVFyTYLlube6kodulh1RZ9a37OGpZx3xxXh5t5jC12RyNw4SbKFXmOYYibRSntD0CsXcsxIo/PRuMgFRYvlQIo1u8EvR5Qpsw3NR4ox5C3V5prPlOLjzO6FV4uG5bdC3LaJQP/jqHe5zdei4kCRdK+gsegF7rnOiE9QoqKESpcMNfV+B9qN+tMFeE9Bem+9kJUwnD0TZb+suCbXR
*/