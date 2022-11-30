//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_STABLE_PARTITION_HPP
#define BOOST_COMPUTE_ALGORITHM_STABLE_PARTITION_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Partitioning algorithm
///
/// Partitions the elements in the range [\p first, \p last) according to
/// \p predicate. The order of the elements is preserved.
/// \return Iterator pointing to end of true values
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param predicate Unary predicate to be applied on each element
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(3n)
///
/// \see is_partitioned() and partition()
///
template<class Iterator, class UnaryPredicate>
inline Iterator stable_partition(Iterator first,
                                 Iterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // make temporary copy of the input
    ::boost::compute::vector<value_type> tmp(first, last, queue);

    // copy true values
    Iterator last_true =
        ::boost::compute::copy_if(tmp.begin(),
                                  tmp.end(),
                                  first,
                                  predicate,
                                  queue);

    // copy false values
    Iterator last_false =
        ::boost::compute::copy_if(tmp.begin(),
                                  tmp.end(),
                                  last_true,
                                  not1(predicate),
                                  queue);

    // return iterator pointing to the last true value
    return last_true;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_STABLE_PARTITION_HPP

/* stable_partition.hpp
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
*/