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
fNrPlWCvJvvwYJrfyr9ijitbw8DaexEXNHoW54+SCcm+Jr6rCF1RrKanJrSdLdJ+TfU8WzVxDkcARBPMicaD+Ai/PVmcJre4Md4M6NGVRo6ug0wpgchm4uP7oZmq1ilGVNbj9v7wvw2VriDvGFDhIjrX0iSOXwueuaRnzWVWuGbnD7iFvrPxJzi+NJxPp36iHjLa9Itl2qzx7KvYPwyf2eMqng1MZKIubdnW7aUecCXjphychroz2O1CUEw4qXMvoPb8pbTPIg0ZUB4v9dDzB5FiV/dqL7UmLGylyMOu9oInobLOIr0BkqWxR2NWXWhZFF47oj2c85p8A6zoiL1xHj1RG2ffuZfaox1XRCWNwmEr/4/e6dGeLmqwEFHmwhkuQpZC+1QEalesHjx+plCqt3AO8h/LPdKYs4n410k/p1WOqxbPu7llxm+kTRtUgmaQc/tfpnHBW1kre9DzyfK7zlH/svoH4qziUIMstgeTKe8FGooHbHE8ecJS5B4248xt7e4wFA6zJvzMV4S2gEEl1jBwui5AuiwJpUiLJBYB/hKnGpfkasbfOkkFWg==
*/