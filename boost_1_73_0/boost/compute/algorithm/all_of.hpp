//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for all of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see any_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool all_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if_not(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

/* all_of.hpp
4C1wJLwNXgrnw1FwASyGi+BlcLGmq4WT4WNwClwBp8In4NVwFbwGPq3xn4PXwfVanxTr4PcMiV73PXz3EKnz1iQ982/2rgQwquIMz9s7u5s7hJBwKsRwCsglonKJERVREbkk5IKkJiSGgAFRFwgQORQElSpWqFCpgk0VKVWsWBEREVFB04oalSoqLWippZZqv/fv/2bf27y3SSq2td3Rjz9zz/wzb+afmX9moyZqoiZqoiZq
*/