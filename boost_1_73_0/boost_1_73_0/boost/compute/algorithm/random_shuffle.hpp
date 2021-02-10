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
Lep69lp3sPEkOseTBLM/c1y9mbOtfwFQSwMECgAAAAgALWdKUtldK5QpBAAA+ggAACkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9taW1lX25hbWUuM1VUBQABtkgkYK1VbW/bNhD+rl9x0D4sCRQ5TbF1bbJiSuItQh3bsJx2BgwItERZHGhSIKkkLvLje0cpjZMFaD5UtiXx5XnuePfcOV6GcPDTriAmOvjhlftfjhc+H0BTo//jhXsZkOf30H0QuMTnK0wN4BF1n+/Dq1D3sOdReW/rlN7z/BXmluQk3QYEXub0ijMdssef62ZrxLp2sHe+D2/ev/8DDuH46PgoggumBJeQOa5W3KwjOC39zF81u7uLLf8YAXfAZPyEcF4LC1ZX7pYZDvguRcGV5SUwCyW3hRErHAgFruZQCcnhfDJdpON/IritRVH3PFvdgq11K0uo2Q0HwwsubjqahhkHukIG5C+FdcjZOqFVjOY5OG42tqchJ5i0GtgNE5Kt0BxzUDvX2A+DQdEaiScZlLqwg+IhFHHtNs9OtUBvNmwLunHgNLSWR0D7I9joUlT0xBDhZNOupLB19OgWGlTlQBuwXMqeDqGC2+4IHLI+WhHthAa9F44eVitL1m5rvXmyEcPaE1Wt
*/