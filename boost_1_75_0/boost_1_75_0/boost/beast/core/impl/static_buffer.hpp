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
h6BlxcXcKv5KKTviNJjWLjfRToKyOrb08HxSh1eIgHoVKCbOdTMUDLBDQFg17Sk9M7lObeN87tYk/WmlxvaF5tD+nrjCxpyfRZocR8FdbebVeP51WyEh38oFKuDexeIg9Jb/QPErincuBpMm0y3VdpVMtR1gYvOI27gffrG8fbZRcGCUfTzz5ZDENucgiqfjYeUuPmEU/A0GXUqyWtYjr4SyoQs5m4H1hlDhTLl2zjIK7USx3fOIZ31/Gl9+J0lZ1AWnKx//ANPhRabDi0wH1EfCwYQKDANFOhId834XVhXwk4/v6mwUrePZazV/RaEciR1CEBbxhs9jrGVSm6I4pVogiW/gorGbH63maworfxpJ1ZpFLtapP8/SDgiuxVduh3qQIR4sjMTP2cKwGtopAe0zauSHkOeQ14Q5jy79O14PgTLU5QGo6iLYdlRno+1TaYzUFUouq6rSC5sSx2RxS+KsLEHzRlZ997JU77TLf8zQ3fLxCYtFFnFadlxWxGnZmVnc1Cl1o70Q0GucUTzdKPY8KPb7gPtt7bUrDyMnWlld4WKmTrSn4Gm+Ekgacj7rJ4zkPz9j6iGP5iV91wBmz547QDu3Sn4PWvyDHzJ0Z4TYQaYmNOjiYDpuYwewIqJaBpdYUTOOga/p9gzWOdq3x2W52XUnwVHQsc+pY+RckBvu1QI1RBYdhSohR+QSLbTle6WcxuZqBwpzwwfB
*/