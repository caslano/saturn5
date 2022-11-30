//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Transforms the elements in the range [\p first, \p last) using
/// operator \p op and stores the results in the range beginning at
/// \p result.
///
/// For example, to calculate the absolute value for each element in a vector:
///
/// \snippet test/test_transform.cpp transform_abs
///
/// Space complexity: \Omega(1)
///
/// \see copy()
template<class InputIterator, class OutputIterator, class UnaryOperator>
inline OutputIterator transform(InputIterator first,
                                InputIterator last,
                                OutputIterator result,
                                UnaryOperator op,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return copy(
               ::boost::compute::make_transform_iterator(first, op),
               ::boost::compute::make_transform_iterator(last, op),
               result,
               queue
           );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class BinaryOperator>
inline OutputIterator transform(InputIterator1 first1,
                                InputIterator1 last1,
                                InputIterator2 first2,
                                OutputIterator result,
                                BinaryOperator op,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::difference_type difference_type;

    difference_type n = std::distance(first1, last1);

    return transform(
               ::boost::compute::make_zip_iterator(boost::make_tuple(first1, first2)),
               ::boost::compute::make_zip_iterator(boost::make_tuple(last1, first2 + n)),
               result,
               detail::unpack(op),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_HPP

/* transform.hpp
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
*/