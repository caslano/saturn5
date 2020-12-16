//
// Copyright (c) 2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_VARINT_HPP
#define BOOST_BEAST_DETAIL_VARINT_HPP

#include <boost/static_assert.hpp>
#include <cstdlib>
#include <iterator>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

// https://developers.google.com/protocol-buffers/docs/encoding#varints

inline
std::size_t
varint_size(std::size_t value)
{
    std::size_t n = 1;
    while(value > 127)
    {
        ++n;
        value /= 128;
    }
    return n;
}

template<class FwdIt>
std::size_t
varint_read(FwdIt& first)
{
    using value_type = typename
        std::iterator_traits<FwdIt>::value_type;
    BOOST_STATIC_ASSERT(
        std::is_integral<value_type>::value &&
        sizeof(value_type) == 1);
    std::size_t value = 0;
    std::size_t factor = 1;
    while((*first & 0x80) != 0)
    {
        value += (*first++ & 0x7f) * factor;
        factor *= 128;
    }
    value += *first++ * factor;
    return value;
}

template<class FwdIt>
void
varint_write(FwdIt& first, std::size_t value)
{
    using value_type = typename
        std::iterator_traits<FwdIt>::value_type;
    BOOST_STATIC_ASSERT(
        std::is_integral<value_type>::value &&
        sizeof(value_type) == 1);
    while(value > 127)
    {
        *first++ = static_cast<value_type>(
            0x80 | value);
        value /= 128;
    }
    *first++ = static_cast<value_type>(value);
}

} // detail
} // beast
} // boost

#endif

/* varint.hpp
Xj9KnzBP+hTeKd0B+EZ9j9+vMkr4AN8o+lm2c5RHOMpXOsrvOcpTylTZ5kv8FNcMdEXeh3JdKi7Q6HUu9+cIaJf0ehzSdJT6IbGo5/XI+81aT5/z/IV5WbyvKurlnH8o9VmMuW2n5V6cWFxui+XONoxLIefvxGY+4PHU9aQEsb7AqesZDsRccEzmIsfSlE85x8+Y7B/KsSzGYld7a2Kc9vU+Han0TMTgkoB/IPsgxKY5eT4ua07O1IVHVqOvJF1PdU+dLeWfrLH1c9RaDWnPOA58fhVK+QP/M89wfeaRZrCKL32ZlD90fd79bdbxeRfHGOH3ybEbcCzWiOfeK/E4MnK9nNc6eaYEfNpfkd9ahCdodx7DU0t+5ygcCTfa4rqIMNyfD4fXwXMhhs+FRtG8/63PBKP2z4R7ZV6ITcF7eqcq2+/pZXu539Ob1rteXyP0OmPSaO9p1uvvadRr72nUVX9Pb1q/e9/TgbUN8U0ZiwiDaw2cBywzb+4H6OPPD6z0HM0zlNdub2k/wkf+k763jv+s76nu5Z5SHu+rdD74Tk+S+kk+nh/SJ9nPD58jHaRuso/ni207VD5f/N44UOp3ICZrpOUckk7tsWGN9wOG2OK429vK+VLPl8wsxmaX+DNpwKnSNtHXDdeEecnfhvtldEt77PBhKI9BvgN1nZoFt84szeWameByzWS4XDPZjmsmz3HNxNj22TDnz/gs6hjnyXv+OZmjYaznPf9bRVnZGLbUwsbgHivbsz3Ute2h7VTz+G1xV2QnZ/UN737nS+83+6fHzXv+eoiGsD0oWYty4zLKkIcDA/7bZvl4+uWPZWzmExibeRwwDTgeiGxMAGYCM4A5wBOBs+nnfQb9vJcCTwZex3a3AE8BrqB/+1r6tT8DPA24mX7sbwNzGXN7JuORzAL+BMwD7o0xz2F8krnA9sDTGet5PjAVuBB4JPBM4KnAc4DTgEvMcQIvAhYCz2B8ktnA64FnA29g+zuBBfh3N3AxcDXwPOCLwAtVrGx+K/MbYZnDpnMEbStHAs1jR5FuE3Ia6RJ5Ppqb9l/SLUW7nsAr6Id/FTCV/vjj6J8/wfw9YDrwBsbivhE4D3gTcD7XmZwDvIXn4TaumygClgDvAJYyFvcTXIfyCmNwvwEsBu4ALgfuBN4K/AO4Qs2f3xWa+Y/k/Edx/qNJt1O9n3AuOP82+HubJU5Oa9qm+tIWdRhtUyNpcxpLW9NErks5jbawsxkr/jwZB84fsBNwFbArcA2wG6+7JOAWYA/g+8CejIPTC/gtsDfwF2AfoDnYfuZ8gP2BccAUxsE5mHFwDmEM7kHACcDBwHTgEOA8xs9ZGqRNrKa2sF0Zy9qziVUf5zrjvsg9zjZWRZxr2Gv3PBtZPs7BMuQNyOXIjUo9O5mXvOQlL3nJS17y0n85NYz9P3tKb7H+hxb/L45rAMpPNNcAmJ2K+786njyJx/v06YcadbxAHe8/wHp8S+B43xRb+4TJPN6/dx8cF7+DYYmQhWkDWaRZX5Cn/A5kxkGtK+ijYhm691lg6xMTC3K9QqDf7mHu/Rba+gVjatjvEk2/RdZ+wdiajvc9Tb+ltn5xYoLsN7C24U/6ipi2hnbAwcBynGvjPun3VIT71tmp2OZolmGpLK2I/55vSHvzOuR+5Ko9y4H2sZb2uWaUdLVfeSdpn+Tj3gyk78RYTP72OKrsLIlS30Paj1HtE6X9O2IUkctP2X1GS/12sXeskHh5eVMyLfH6E2gL2RYfoJVKFbOfNhBZ2zCmnT+PRj6WfwdyJPdNBe+Y3O2bGRb7ZqGLPWSZsleAr5X2RBbeybFilMEfOab2uwdijjjGOfL4cCDmh+Ocn2M=
*/