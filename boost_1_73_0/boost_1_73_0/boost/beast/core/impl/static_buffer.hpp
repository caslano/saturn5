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
8sZX1vwzwK8xLR3ge3KT9y/HHnPvf/SOHw7djFfgXkX9hw4NvWvTt9ZdO/vF7+oj696tpvfdQ//meVe27hu0buPKTeW7dz50y28Z2039f2/wjemauG7tr0bPXjdk95d/ZWxCEfa/uvy1F459evPBZTeNHbV17XygThf1V/xmxdqj41qfvqFnzs+uf+o/dzL2K+qvqdkY+uDVI6MDf1w+JnD/mOcZO0j9G948Y9Z1xZ4vms474+nfn7fnBcaqirE=
*/