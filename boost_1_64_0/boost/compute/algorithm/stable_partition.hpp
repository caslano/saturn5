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
o0tGx6YlhvxCcgScl2VALfA0OyU0nTLvBmEPqnQHVb8DF+fWnq4iFqPe0H7mdxd1fFQCM3sjua3z4JD6Ro45LuMDG9J9UP2zfkgfcL22U+4DCCH3Io9SoaxZk0RUOz14lVPhwkvucfJsj7L2zxRoEK1m9qeGyQREayRH6+z+42J6BNrXYZnSYa2xrR1VvFs4Mz7aR/B45CcgCLlBHCDgcx2Ml4ZQOaRv9zb3RxpuS437HPgBbJjxnHjQZ/xgpgO2fdautNp7c4lGep3aY7Su7oPZU6iUVKu/A7TEXgB7KiFewKviWStw0Z8mz+GDLBOWnkN6w5op1V+14MyZiXRYYQ8hrUu3Bg3PPAFnwTOibbmQHhLQ8a4iZdr/uR3uRoYgzxwf2Uz0biac+kA0RBOBGeUQJZPbaMP5Ij7h7vCjOTWB3KNtGWxeLrAgL1Hg8HAsrC5YMMpk6cpACit/OuDgG/FBPsAlWralcBbxaw0FMLL3t88Z+3PyoFioqSkqpmDbL9m8KVtL3TkCUt/kncfCVuvpsjrBjswSkyapEakUcnB2cdEoZ3u85fl9Qw==
*/