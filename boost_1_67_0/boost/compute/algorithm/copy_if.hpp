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