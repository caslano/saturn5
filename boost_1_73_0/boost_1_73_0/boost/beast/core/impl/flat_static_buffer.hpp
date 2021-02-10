//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_FLAT_STATIC_BUFFER_HPP
#define BOOST_BEAST_IMPL_FLAT_STATIC_BUFFER_HPP

namespace boost {
namespace beast {

template<std::size_t N>
flat_static_buffer<N>::
flat_static_buffer(
    flat_static_buffer const& other)
    : flat_static_buffer_base(buf_, N)
{
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
}

template<std::size_t N>
auto
flat_static_buffer<N>::
operator=(flat_static_buffer const& other) ->
    flat_static_buffer<N>&
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
/* flat_static_buffer.hpp
W/IP8EoDBivqKnI4257mJv3e3/2pd9nuD2bjXrOojDJEZtSJBo8z/YCHIUzVLjiRG7eODutg88CsuaH+8Iz0Yrnmm8NvFPSnfqTCixwpYNmYpReuyzdKhlWc2z+Ofogiww5Gi6dx1DqHMFzvUDi33zbKqvc6IQr/xqpkcIpTHF1NPRw24jdK8Z/xvx73p73L2bAz7Y+GzsnN8uIA3fa07dBpvQRxORoMRteDUaddcjYGp5Xh3ybeLEmBO93zY87SPDvYO3r5N7tlKtZx501mnU5vMqGX519QSwMECgAAAAgALWdKUvdc84BABgAAgQ8AACQACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2h0bWx0aWR5LmNVVAUAAbZIJGCtV21z2jgQ/s6v2OMmLXAu0E7n5pq3HiGkZS4HGUOayTUdRtgi1tVYHkkO4dr899uVbGOStsmHOpNYXu0++75SOq2f99SgBY8+M/s7wwffVuJMyX95YL7NPZt9BfeDUlf4fkxJBzYiX2dNeFzkKzSsyCzXsk/r2ewxRVdkG/3pkOTVjJZIQTGS7Mt0rcR1ZKDRb8LLN2/+gBfwqvuq68ExSwSPYWJ4Mufq2oP90FL+jNjtbVvzQw+4ARa3c6hpJDRouTArpjjgOhYB
*/