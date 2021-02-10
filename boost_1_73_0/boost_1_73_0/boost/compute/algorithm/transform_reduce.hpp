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
Cv4ETn8nclZ6vOtpNlkly3WySANfnKqThfM3dYGlihtKosfpk3DF36NzpW8PLtvO25QJ4UuvXCUCz3Z2hKIqGtWg5Q0ZUWOFWvcuYubVFV2vuqPQClagGVo3oJ7pGpSWHRuPuy1SqnC080227huXkdsJ27RKllze9ttWBbsqeSZCIZAq0J58PN1VS3I89u8HRW3gCZwtC0UGQuvcSyKtpuvNKoV/xrPNNEiGl8F3QqWb2Wy4ae3YD5QxHLSiqWs295YpmJTKOvX8vbxY3knf0EzPGGbTKYxn2YIq9WUF32cPIeUfhf3OrVB7JnrzPF9HZh6eVsPgP1BLAwQKAAAACAAtZ0pSdSeh6WwIAAAQFAAALQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX211bHRpX3BlcmZvcm0uM1VUBQABtkgkYK1YbXPbyA3+zl+BKtNYSmVKTqZzTZzeVHGUi+b8NpLd1B3PaFbkUtozxVW5pB21uf/eB9iVRel8ST6cPLbIJRbAAg8egI5vW/TiD/tEMaujb36m8jvFB9+bTZel/UUn1dMbptMv5H+w8Rbf32GqR9tdX6Yd+q5dX6gtu6bB1lu+nk6/w9wtO8l/erz5dsqXWPE7w/4Tu1qXZr6oqH3SoaPX
*/