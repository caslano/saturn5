//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/detail/search_all.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Substring matching algorithm
///
/// Searches for the first match of the pattern [p_first, p_last)
/// in text [t_first, t_last).
/// \return Iterator pointing to beginning of first occurrence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param p_first Iterator pointing to start of pattern
/// \param p_last Iterator pointing to end of pattern
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p t_first, \p t_last))
template<class TextIterator, class PatternIterator>
inline TextIterator search(TextIterator t_first,
                           TextIterator t_last,
                           PatternIterator p_first,
                           PatternIterator p_last,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<PatternIterator>::value);

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last)
            - detail::iterator_range_size(p_first, p_last) + 1,
        queue.get_context()
    );

    // search_kernel puts value 1 at every index in vector where pattern starts at
    detail::search_kernel<PatternIterator,
                          TextIterator,
                          vector<uint_>::iterator> kernel;

    kernel.set_range(p_first, p_last, t_first, t_last, matching_indices.begin());
    kernel.exec(queue);

    vector<uint_>::iterator index = ::boost::compute::find(
        matching_indices.begin(), matching_indices.end(), uint_(1), queue
    );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SEARCH_HPP

/* search.hpp
lMWxk3yRdZDkx1trgH0dHLsTofcyWOPjOvS9vGzlklXLSktGlVVWDq8YdB6q+jdc2tskV/9kHIwnx2IMxo/UONhp+GbDJwyfWjYMLCMri3HO5l9PsA8TpM1Kq5p92FbyLda6YNjeKsu7puD9iOW3Z961X/Yaw+WbIX8vZp58jJtEMemXGpc1+WIiGSd71FlunCx0rJJjPUHWlDzGHI/7cX3xCMdjjfwu8xjB97/8ifG4gY5qZHzVILGCw/vjAuss6v3zL248b4be07XeWXP6uXRW3wCpjPsflZMwpz/Lq3fSjuJOmjWnd2O8i7JivNF/1q9w30tws+TXstx5/J+4x2fHUnvvIVfS0JtR/w2RRqD8y179s+9dztBi3NNtjHD78D770N/vrmS8R7YBpUyJW2cs83i7BO2g75MVQ7wH/bk4c1cPsc3mtA2GgmBP2mYqUhXKV6bfQ8LbUfo4TquX/vTGeP7puMixUraR1wxdd6RV7d5/eFOT09/itQrHQ8qthnrFKDut6prVMdagz1K5z5RVjlg5va5qqJaPR3Kva2yuPSRpb0Npr8y9P2l7rgxbDh/ifWlNaaNyUNvrcQebwLbaJty/oW1n1rhxy4ItkW5HwFEibduMPWIdpzk9y8a0Keus7N4zjpb8hHw2dvtzupSrEvuqAKIPkNL2tVz7nq9+Q0rbtzqvfU/JY99V/oR9+9L2HXJs6PQs+3rH7nLadw3e30fRvou0fWnY/HbVZVdyrzkr/Yn32eTQjb5//5yP3xsSG3lY6X2NN/186VZbti9/sPjpc64wvn9++/59b0mMnmBZHfTAMf9iWvocGof/f4qk9oHkXEVS86/Z3DP5iP9vQVrK8t8ivcf//4rEmDk+K1FjTv6WETP3DQa5kt9Crg65HFLXu5311slR7xfW+xVybciS4v56S1hvpRz1PkF52buCrID8DFLHuH3AeqMt6bP+v+BolktY3GPmfWY215NhltuJsWiTIEvFPul+TYZUdtsNslbVhdyR+V0g94BsgWyDRFlrT8gpzCveQ5Fmkndz8q7EODuFseRdG3IY5LqQ5ZDbQFYwlnQUZC3kmpCbMuatDnIiy2n7LSDPyur/Wfb7fFqa5wtIxf8lpNbvGtbbLod+Z9Ie8/kt5fMgx0Cezxi8C5U+zKv+LWRM4GWMtV3gscPn5GnIwTO7KM0zB1LxHAOp+n0c5GjIEyBVX06CrIWcC6n6fxrkFpDz3PGHxD2N1cnjtUOMPHHIkZC9rLc/Uivr1bJehfqN9e5gvUXU7y7IKsh7IMdA3ge5LuT9kMoeD0KuD7mY7TchnZil1zDaQuFhtv8o5EqQj0GuCvk49XzCo+dCthPKoech1KOD9pkF6cZoMj8J8nDIKZBHQM5knu1zjwd2zNH+mUUcD7TD2Tw+F0HWML825HmQG0GeD7kZ/66/3d3O9kfn+Hb3JWz/FsjhkLdBjoC8lfW7uX/inscc7+iD4B6YuQzyXsi1GYM7njG4So9HILdgDK7S5UnISYzF3ZkxuM2Qz3LczkN6hnzvkm9VpGPJV0s7bAK5IeRWkPWQ20DuArktpNJzB8gDIHeCPAiyBVK1tRvk+ZBTIBdD7gH5OGQr5JOQ0yBfhqxj/1UdWfdDXsx8JVKU+uzP60cn5PaQRzAmOQrZB9nD2Og45FxIB/JUxjyfwdjpsyFtyPMgT7DS+p3kxhRzzQhZQ37v9fYYlmvSayzIDXKM9yt5fbsKcjXI6xjbezNjw2/xxAS/zHY2YzvemOAXeLxf5fX6LV6X3uZ1G8dMjstSS49vrhEg98wxvvEHtAcBuQrzI5XgeVXC4zyM153hPL4jIN1Yara/Ddv3xlKvyfs=
*/