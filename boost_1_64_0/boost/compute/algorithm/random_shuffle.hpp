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
APx7soj7hz1ZM+SbTtpF3HIc6wT028/sC9Z61m8/6tbMKXd0zilLmWaK/1j59i9t41wXYPRI6rqA+/UcvDmYK/GpDutHqCiL1I8I6xy32Sj2s937kwnf2fSnDWIvU51mpj+ZPvOZ+J8u9lwTP93Zv7S/rBO/Qu1fgbBpRqfZyFTRURZxvcGh4h/rCB9Jp9lvkvbEiDrNxtVTp1ld+wJ15NoXwvUMfq+6Bc7WZ8QUzDx8KlPDxnVIvlY9gxKnrWmzZ8R+sMszQHUJin+ytnkgfopzjYi27xviN0jbNxC2e8Rngq/tH58JSyVOX8czgXCuz4SUCM+E9yWN/ka34Gtiz434bPhQ/Fur3db8YgPrhuTZMLkezwfiB54PddBJSH1H0EmYEvYsyNNnQbiOwitidR+U9o9ZmFvxyW3r0j8i6ygkvFNHYbnYT3K9n4dIeKeOwhKxn+Kqo7BY/ApM3yCuQ0fhu2JvEHEd2RvaJsHwke/n88RvQsT7uaie97O7jkL3tjP3ru6lP1/3p+9OR0qG8fBifFLamf3p0ixTCsYYHaFu9yLtQ5ygPpAR2LPF/pOvn671myVtVDw29P79PE1GQ7XNAmnsKfcPW2TDz6g3Oj72ay9taY8mv3PRnZOs+6wrJf50XxQnse1ut7MP88W6nkl/NRwiYbf4gufwnjymqDR4bWskjyizxvBeCf8DGkWi2bNVZidrv1oi4XrYSYR9zOpNvpz8rP2gofi19UVbX2p412t0jO8m6/juOgn3od2WU5TG2j2s+23qVvwC6e7i24Ud/8HnzkmBM+1rPRM/MP+QrGXrJOkttEupz1VoF5xNXqniF7jemb4mlHqSdSnX3N8axz3+nn18yNn5JYFzzsU+Pq2m7pK1b5wv6Y+yE0l/KiNYH5FSJ/ELpH+DL80awN7FCZJ+oX0xZw32tqgbzlyJkza7JKTNQp6rRqfUUPHb6Mvk/6Beh4LJFN7obDlNrqMBcbCbvK/xvYNb+HnMTXX+aYCE2erracVoGPOMNnMMAyXMt75euj41tSZvM1Z/iOQbp3ZWnHbQZ7hJL398WdGE0ex+N7oN3pI4DamJXPogbuZ6L/X1wjXJhz4YZ3wzP7GT1P9r1E5undqxB8+iRv4epM+hKZgSTCmmDFPudCNM8Pcmt5bfG8rq+L2pcP62iNv5kOcDbjwf1O1qo6dJ71vcssxvzklWIvYME8b0c9VxA8Vd+qW33nE7jH3Xd73jhTLnccaor+8YPuyFHmu3PJlx6c4TVv+31zvmWfqtCU9xOf+pg+5t7ghT4V6wJ+wCB8CucBDMhEfCbnAM7GH0h+q3Brw/XH+orqPcG+4GD4Ct4FjYGo6De8CpMAVeANvAK2AqnAPbQi2Hvh/zXu9Sjn11PWQf2B7uD3vD/nAgPBAOhgM1/xx4IhxsyqHvWPAml3IMVT2oh8F94XB4FBwBR8Mj4ElwpOpBzYMXwiPhLDhK8xnv03cKfcchH66BPqLjGsfp+tMCbZdxWq4TJH/dIw2L4D5wMhwGi+EI1VFQAktgBSyDM2E5vApOhQ/CafBZeDp8HZ4FV8Oz4Tp4HvwMXgS/hLN0b/ps2BZeCveCl8EseCXsC+fAAfBqmAOvhUPhXJgHK+FRcB48Dt4ET4Xz4RnwbTgdfgAvhR/CG+BdsAreCxfDKvgWfAiuhYvgOvgk/A0+DX3U6TMwDi6BqXApTIMvwz3hCpgBX4W94GuwD3wI5sA34HD4FjwCvg2PhO/DY+EZcCI8ExbBc2A5nA6nwlPgefBUeD68Hl4Fb4BXw2fhrXAZXAAXw4dhNVwI74fV8AH4NFwHX4KfwtfgKrgVfgZ/hp9D3pmlH0z01vPWaz0=
*/