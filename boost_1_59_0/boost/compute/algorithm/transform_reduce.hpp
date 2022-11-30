//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Transforms each value in the range [\p first, \p last) with the unary
/// \p transform_function and then reduces each transformed value with
/// \p reduce_function.
///
/// For example, to calculate the sum of the absolute values of a vector
/// of integers:
///
/// \snippet test/test_transform_reduce.cpp sum_abs_int
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see reduce(), inner_product()
template<class InputIterator,
         class OutputIterator,
         class UnaryTransformFunction,
         class BinaryReduceFunction>
inline void transform_reduce(InputIterator first,
                             InputIterator last,
                             OutputIterator result,
                             UnaryTransformFunction transform_function,
                             BinaryReduceFunction reduce_function,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    ::boost::compute::reduce(
        ::boost::compute::make_transform_iterator(first, transform_function),
        ::boost::compute::make_transform_iterator(last, transform_function),
        result,
        reduce_function,
        queue
    );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class BinaryTransformFunction,
         class BinaryReduceFunction>
inline void transform_reduce(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator2 first2,
                             OutputIterator result,
                             BinaryTransformFunction transform_function,
                             BinaryReduceFunction reduce_function,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::difference_type difference_type;

    difference_type n = std::distance(first1, last1);

    ::boost::compute::transform_reduce(
        ::boost::compute::make_zip_iterator(
            boost::make_tuple(first1, first2)
        ),
        ::boost::compute::make_zip_iterator(
            boost::make_tuple(last1, first2 + n)
        ),
        result,
        detail::unpack(transform_function),
        reduce_function,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_reduce.hpp
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
*/