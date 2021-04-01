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
H57Po/FTV5X6um7non2EkCf60JMFbXel8hIx5HPK8kkiDLLVbhSCxJaFIkKHjM96NvzXUvsH1i9QQ2AuGfi1wiKX4WpgattYyBMHonxhm0knrsUZ3K0OPxtSL+iQmwXv/eObEpL5mVmEgIiLlsX2i19yaQ9TASBcEozslmNr9YzYQ8984blo5G2Crz2aA0SslqqDytl/I5KY4mFpJfsSl6JqrtJgPFP9d/V9AAo2HpTfzZwr5v/jSt/g3d693yfiCl/p4fX6Cf9JjBz7yHaTbz66VC7KeRhwyHJkEdNrhhX6FmJub4bRSjy1WRU03XgwIDw6MpfOvvSvmxiS8PAM6EwPbe0iAcEL/C6xYNYtF0L0oF3xuEgulzgydmncb/Q3bW8BVTNzKGMu+LGyxZuzUMsWIHv8BLU7IdObAr08sdbC/YyyBwouRwp/fzQNuCr16cSg4eUSnPHwaVqTHuVbnRmbp4OWlqEvZ+k8d/FHKWBkNUJ/zrsSguctElPzFz/h8Hsc/ufi5CPQhuVHw3Z1lDyLelEG9o4VlMesx2cep681ci6ycLS1G9ROFw==
*/