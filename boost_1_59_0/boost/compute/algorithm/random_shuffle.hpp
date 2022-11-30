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
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
*/