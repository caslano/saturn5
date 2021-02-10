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
2NohN1dEG/tsscDwOhWUhtHtGsKCi5axPJgNDMAd2zEDUm7MRRsxc1ki/mK3rTexpW2H/AyN18Tl2Sg0UIo1gfbCLKK6EnGDgchgD0hRwJm6DowMiw8NttuFqfDZGDtdoH/01EFnYXw9qB/i9WavhFByhnEyECrYZ2nd3TGs/AqFtz90RsFhq9MdD9pm/asFgrBWgSiusbg41g6S2D8Z2fx5Nz48bA+81ewycgxelPJiz9C3g/6vT8CMeoqktskHn15F5wjZM5AK4EWozHn6Rsj4wEsSI/A8iOTST6+URXbb8mcBPOx3u/3Tbt9vjTr9ngdvus+EKvFyktSioi7K2n8H9umgM2ofjnu+RW1P3TORWyH/JuCD1qjlwevJ98haWxSptnwz4mIRbxF+q+TQ5YM1BVtcnvA5x6L6YNW9yESEvTnSty25Y1Ya9Le4kdYV2uKDDlIaUKVv6lTK5vzp1A2mi+ZRuas3IDTKO3MPLMoAr129u9zed1bQLUtdeVtLjj7nEvtJbflsDd13CB3e2vVRZ9Rt190ySIWyjX3bI+1Bvb5zc6O8cnHPOpyCAGBQuFBZsSYSeHl8QxzaafTtUVgTg/+LO+/1WZG5lW9GpDbG1iOhezrmCU4u9zvFEHIyDttzHHGc23Y9kHFr
*/