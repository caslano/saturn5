//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Performs left rotation such that element at n_first comes to the
/// beginning and the output is stored in range starting at result.
///
/// Space complexity: \Omega(1)
///
/// \see rotate()
template<class InputIterator, class OutputIterator>
inline void rotate_copy(InputIterator first,
                        InputIterator n_first,
                        InputIterator last,
                        OutputIterator result,
                        command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, n_first);
    size_t count2 = detail::iterator_range_size(n_first, last);

    ::boost::compute::copy(first+count, last, result, queue);
    ::boost::compute::copy(first, first+count, result+count2, queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

/* rotate_copy.hpp
nEvrC2w1TKUMU8l5zsT1nexKqt3eOS8F5gs45Z2vwLK6I36j29TgdjYID2N1CbfzA+FhJDWyN9Xt3L7y8tI2VOEKf3gS7pm2hyfh3VXfyHuR7Gq26zlCPCCFCyyyScYQ+EXOgtRV98qTUrMbnJNSV8/3yQUWYOVgF3tNDbAhR6FmqJdm+3c1Zobqjwbae1F7fKnk/HlRpg93637lKjhX5b74Kgj3gGxPjKtP5fUJVLi9LXefMhCaYATQEPWtc2e8cf68uI9mG0efYyLFeLhmuT8yx8bPNGuX8RI7xsfiJTD4LexpYHpKVEwCmb/OxOnNKLjwhvN4VnlX3piUYIupeoNiwnJSvxZ8NeFV68Oed9HoPhZXNeypxpkzuSoo/z0nkwfJSjq40vz0G2mGCs+bbvl7d+XXropV/3ZXavBnjSvPKZS9DK3GGIVyK4vVCt6JNaOaUpgeMH8zW5PpkjMtOIXqv/8NC8GH08ji/5eE64cTrh/k1xFb0yfEx61XrmNlcamanvi2EWSOf0N3JfkjgrM8ZVowQ1wH91atiYZpUjEjfUneiEA3DqmaR9++7F3GcvPPDISf2XVUAehD+shNLH6k7Cc4y9Vx2O/1IHqU5K2ALaJtVXNK8lYFs8XQcWNwuFjykzE4BMeqQ/in0+zlzfAynydJHiyuHQ4z4c7LDfYH+r1J/36lQRxdHxxBk/TYpk5g7OFjxQjRKCUs
*/