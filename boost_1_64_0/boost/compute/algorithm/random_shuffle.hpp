//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_RANDOM_SHUFFLE_HPP
#define BOOST_COMPUTE_ALGORITHM_RANDOM_SHUFFLE_HPP

#include <vector>
#include <algorithm>

#ifdef BOOST_COMPUTE_USE_CPP11
#include <random>
#endif

#include <boost/static_assert.hpp>
#include <boost/range/algorithm_ext/iota.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/scatter.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Randomly shuffles the elements in the range [\p first, \p last).
///
/// Space complexity: \Omega(2n)
///
/// \see scatter()
template<class Iterator>
inline void random_shuffle(Iterator first,
                           Iterator last,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    // generate shuffled indices on the host
    std::vector<cl_uint> random_indices(count);
    boost::iota(random_indices, 0);
#ifdef BOOST_COMPUTE_USE_CPP11
    std::random_device nondeterministic_randomness;
    std::default_random_engine random_engine(nondeterministic_randomness());
    std::shuffle(random_indices.begin(), random_indices.end(), random_engine);
#else
    std::random_shuffle(random_indices.begin(), random_indices.end());
#endif

    // copy random indices to the device
    const context &context = queue.get_context();
    vector<cl_uint> indices(count, context);
    ::boost::compute::copy(random_indices.begin(),
                           random_indices.end(),
                           indices.begin(),
                           queue);

    // make a copy of the values on the device
    vector<value_type> tmp(count, context);
    ::boost::compute::copy(first,
                           last,
                           tmp.begin(),
                           queue);

    // write values to their new locations
    ::boost::compute::scatter(tmp.begin(),
                              tmp.end(),
                              indices.begin(),
                              first,
                              queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_RANDOM_SHUFFLE_HPP

/* random_shuffle.hpp
jQg0EQpXB5NMZeB2sbwY37iyTdQG0kI6xTTMKE9Ozvufs7wAsshA2o9ucdLu1bmdUJqEKti9D6jOViZt6iBZK8F+YDtj2IfmWar9C8YULehOWt3QA2K1DgAEfFXa02dqkipj/sBgKB2If8RIsXpJZXhADtp/zgtr6C+HiWlkrr/aspeUeZ6iSfQUb73fexFsZWiq45gOyIpwRo603RxOxwgyF+FZQei2Mb9F4haBghzJ9yjFDQYisOGbKV49qQ/lmArVO1rBiJJtnzRsg5UFH7ExCSJ2KTlvlLJIFd7lo3oVu61shupqjKlq9lhJ9kbzUG0kzqgM7gXdt20Qg8bUo9M9rDRs/oz3zVUUPN285+p/920dQqEsDLPQnJ7Slv4FuoXFVYy7R7CHCxtJD1VWRJ/XTo9L1PYA7ZrkcZeZH0DXVNKj+qit7Z0bZH9I9+ONoXc4WUOT3bPI/BGNCjcEE95vagNw9e+fg3kjfumWXBeeZMFNQax0EL6A8HAbrTocYWQtp/BQS42HdTsgqfrL/rCnV+bVuUz9eeaZy5D1ECYv68Nth+eSTSs22g==
*/