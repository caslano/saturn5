//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_STATIC_BUFFER_HPP
#define BOOST_BEAST_IMPL_STATIC_BUFFER_HPP

#include <boost/asio/buffer.hpp>
#include <stdexcept>

namespace boost {
namespace beast {

template<std::size_t N>
static_buffer<N>::
static_buffer(static_buffer const& other) noexcept
    : static_buffer_base(buf_, N)
{
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
}

template<std::size_t N>
auto
static_buffer<N>::
operator=(static_buffer const& other) noexcept ->
    static_buffer<N>&
{
    if(this == &other)
        return *this;
    this->consume(this->size());
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
    return *this;
}

} // beast
} // boost

#endif

/* static_buffer.hpp
PL3Qd6/VMGv43KPygCa8jY9+hounNLzbhHfrZ1g/g84FF7hDvGZCpEsjY3ExIKPONeve4t0NLs/VheWgkit+s0FK/1YkjrquH73Ao/Ih3KCOVzfMKz3M0/PAZCMLtDW49/bXJWZ27nBGPU3xyB/JCdBHaVkV10BcKwRyyLiVvcrZ/2WsQAk6HpnYY22Vq78NL9zwtBDOB3y8zncz3G1ws3D566Dfw7P2E9DPwZ0N1wy3Aa4P
*/