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
TLUVu4xeA15l2BtR8D/pQlcYER7wpFe1NG3PlEzxLtgqcHkr+7hhaGRWXq85qs+PjpIaIUf0Of/C0METEZP3rpvgtkKHEc7zBVgFFRzWEAEmYJ4tVd5WwiaDHPactjAScWiVD2PkjaharsaQK4UZejAdTq+cGJ+yLIhec1/BWrJ54JyQHjFmGZ1+zsWS+6DiKgtxvlF+hxmEExTrjt9MN3eHWkfplb6fFSMontcUBrbQCfpSSgKBaBFqwTIXcMC7Gy64lRNva+w134PxXxbcBvV1OMguj9V/31u6fHbsnmJQ+YDbgDB6YkEY1gEgEnzLxcOZDpZkulBhMu1Gj/jbgc07m80nP5PbOS8x/NZSsDC++hH+4kF6qAJtfT5ezCe/jNNYAD2qQCTeBhpmU4N+EMVces+RF9gwUdRHBpZ7nN0M7AL9tqFhrEzLqRrIvbMCRiaRUXIrMN1jFOCGC66UscnLsuzazXS2IActDKInvI5aduT4hxPXaejZgQVYXiyIcLQW1zLmPkp5bUUdBN4lXh8kfO2ymbcSbGVZFga48/Hi4nxKP528uRgPxlduKCmtpZYWWdN7MQ7FIZlKkcOMrlUUkj0pmQC6o8/ClotpHRSN5uMxnbyZzzCj//t8OB/nFWLcNjTC6ZRGwy0F
*/