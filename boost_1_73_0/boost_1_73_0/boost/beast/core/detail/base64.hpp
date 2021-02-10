//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BASE64_HPP
#define BOOST_BEAST_DETAIL_BASE64_HPP

#include <boost/beast/core/string.hpp>
#include <cctype>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

namespace base64 {

BOOST_BEAST_DECL
char const*
get_alphabet();

BOOST_BEAST_DECL
signed char const*
get_inverse();

/// Returns max chars needed to encode a base64 string
BOOST_BEAST_DECL
std::size_t constexpr
encoded_size(std::size_t n)
{
    return 4 * ((n + 2) / 3);
}

/// Returns max bytes needed to decode a base64 string
inline
std::size_t constexpr
decoded_size(std::size_t n)
{
    return n / 4 * 3; // requires n&3==0, smaller
}

/** Encode a series of octets as a padded, base64 string.

    The resulting string will not be null terminated.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `encoded_size(len)` bytes.

    @return The number of characters written to `out`. This
    will exclude any null termination.
*/
BOOST_BEAST_DECL
std::size_t
encode(void* dest, void const* src, std::size_t len);

/** Decode a padded base64 string into a series of octets.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `decoded_size(len)` bytes.

    @return The number of octets written to `out`, and
    the number of characters read from the input string,
    expressed as a pair.
*/
BOOST_BEAST_DECL
std::pair<std::size_t, std::size_t>
decode(void* dest, char const* src, std::size_t len);

} // base64

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/base64.ipp>
#endif

#endif

/* base64.hpp
TOXulg26KlJfSFCUc2MLcYyqmjaFeZMe16hBiYyZNjclCmVcrXOxeqKIeTRWskoW6AjzgEqpwDS7UBUplVbZRt66aHJqE/y/pdnyTUEUSAb6wzlM532IiWLKhffTxZvwdgHvhzc3w2BxB+ElDIM7Y+ztNBhj6Rk6k0AfS0kVOpfAViVnNG18/rrL7/3GioRXKYUzpVMmvPziiUiyYmlkO0JT5LrSRu4fwtl4Mh9d2I7PafJBAQGFMF434nPMDvtoawcrzVYolVgITMvl4hpLKR+oNHHBmd/a8Xs9pYlmiUVG2Ci5FOuIrMlm8CBYCoellm57aG7dS7Giq9iFWislmji9Tz0AC3MQddq9mEPzhgGsqe3rQmicICw4VXo7TDkl2AsKmMa2y9yeHXwcAASJgm9wijQ2kFW1caJ8vZ0xRcyAeZ5nooJWeVCzdewdQ7esndPel14PCeB8sKImacknOZGQ6RJT/vc/cA59fMZhw78efSTYGdRLxMpfFpUfswKnlqvu4cWJd/zSO/Y0kV788aRvIh7d3szg0FSwfUtEataBMu9cFEtbOFurc3hxbKSpqOKmoJbzORx5R+YgwenSNcVDc1oQi8LOkUkuBzVtF577zx34HdCWwaAoWnIREx6xgumB4RBdzcLXw1k0
*/