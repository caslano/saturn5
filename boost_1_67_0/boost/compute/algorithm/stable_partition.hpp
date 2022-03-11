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