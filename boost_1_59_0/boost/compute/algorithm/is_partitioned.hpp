//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_PARTITIONED_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_PARTITIONED_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the values in the range [\p first, \p last)
/// are partitioned according to \p predicate.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class UnaryPredicate>
inline bool is_partitioned(InputIterator first,
                           InputIterator last,
                           UnaryPredicate predicate,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               ::boost::compute::find_if_not(first,
                                             last,
                                             predicate,
                                             queue),
                last,
                predicate,
                queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

/* is_partitioned.hpp
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
*/