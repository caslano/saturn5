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
HUunbzGgjJf8eDuUj2Emvce4HD5XKThD2d0AeTo3aqFhc7WMdaghMWb7ioYOl3Fq5mcP5EeZnyUx99NH00nOibj1ZUCIqA2zf2ViUeaB8nv9JXYivohXrmaz3t9OzUbxauXEzZ8BtC5n+t1eLKizpiVrvo1pybClvJci/LdB7vnOvIjcc/nDs2EEx0XpdIDrtZZ9Cb1CQUXT+4JmUsqCzpI8Oxebfv84rDHMadhDk1LaysqJOjCF3WT7TzOkyUCtlm/MgnRrgSZuTqdvB15KbMkhHb6BORqysPb4mqTbwC/2Q3MF2f7Ov9ESezulN0RXK2mP1KonFSaZ5r9u7VCm2SaP8Ibm7nBUfLsUymYAF2CV79OP50Z4E5qaVgDraDow3eiRm+8NbeFYhWEXBNrkRuThUYrZRXvtxqC39k6fMl1sbJEr5yZkN+2jzrC4UiVK79dhIXgkFQmJPI90hpL0QomrX9JKLAD86JWAtNpMkY/cOSPSANBmnpv4Ndre4RhP8BNzkTOnb1rgJ+Tp07SQdR+d43HClEdfZ/R7XngJSVh/OIrdxcgNz59D5vdfcB9i0dlHc/+kxmMaH2krewCzIVtafHpcDU8hfs8+YAEcPCx83S1QnZJRyMPXDT3GHBTzkOflERECvTxMGZan/Ps13qumMoFlHl5GxPY06I3USrKRWyIdk5Ozib86xsTBIc69YP8+xYTBFoBUDdpa
*/