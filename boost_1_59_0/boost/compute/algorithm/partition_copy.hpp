//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies all of the elements in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p first_true
/// and all of the elements for which \p predicate returns \c false to
/// the range beginning at \p first_false.
///
/// Space complexity: \Omega(2n)
///
/// \see partition()
template<class InputIterator,
         class OutputIterator1,
         class OutputIterator2,
         class UnaryPredicate>
inline std::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first,
               InputIterator last,
               OutputIterator1 first_true,
               OutputIterator2 first_false,
               UnaryPredicate predicate,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator2>::value);

    // copy true values
    OutputIterator1 last_true =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_true,
                                  predicate,
                                  queue);

    // copy false values
    OutputIterator2 last_false =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_false,
                                  not1(predicate),
                                  queue);

    // return iterators to the end of the true and the false ranges
    return std::make_pair(last_true, last_false);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
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
*/