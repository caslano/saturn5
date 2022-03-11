//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP
#define BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the inner product of the elements in the range
/// [\p first1, \p last1) with the elements in the range beginning
/// at \p first2.
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when binary operator is recognized as associative: \Omega(n)
template<class InputIterator1, class InputIterator2, class T>
inline T inner_product(InputIterator1 first1,
                       InputIterator1 last1,
                       InputIterator2 first2,
                       T init,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type input_type;

    ptrdiff_t n = std::distance(first1, last1);

    return ::boost::compute::accumulate(
        ::boost::compute::make_transform_iterator(
            ::boost::compute::make_zip_iterator(
                boost::make_tuple(first1, first2)
            ),
            detail::unpack(multiplies<input_type>())
        ),
        ::boost::compute::make_transform_iterator(
            ::boost::compute::make_zip_iterator(
                boost::make_tuple(last1, first2 + n)
            ),
            detail::unpack(multiplies<input_type>())
        ),
        init,
        queue
    );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class T,
         class BinaryAccumulateFunction,
         class BinaryTransformFunction>
inline T inner_product(InputIterator1 first1,
                       InputIterator1 last1,
                       InputIterator2 first2,
                       T init,
                       BinaryAccumulateFunction accumulate_function,
                       BinaryTransformFunction transform_function,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    size_t count = detail::iterator_range_size(first1, last1);
    vector<value_type> result(count, queue.get_context());
    transform(first1,
              last1,
              first2,
              result.begin(),
              transform_function,
              queue);

    return ::boost::compute::accumulate(result.begin(),
                                        result.end(),
                                        init,
                                        accumulate_function,
                                        queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP

/* inner_product.hpp
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
*/