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