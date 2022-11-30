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
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
*/