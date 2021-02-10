//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_BUFFER_HPP
#define BOOST_BEAST_CORE_DETAIL_BUFFER_HPP

#include <boost/beast/core/error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace detail {

template<
    class DynamicBuffer,
    class ErrorValue>
auto
dynamic_buffer_prepare_noexcept(
    DynamicBuffer& buffer,
    std::size_t size,
    error_code& ec,
    ErrorValue ev) ->
        boost::optional<typename
        DynamicBuffer::mutable_buffers_type>
{
    if(buffer.max_size() - buffer.size() < size)
    {
        // length error
        ec = ev;
        return boost::none;
    }
    boost::optional<typename
        DynamicBuffer::mutable_buffers_type> result;
    result.emplace(buffer.prepare(size));
    ec = {};
    return result;
}

template<
    class DynamicBuffer,
    class ErrorValue>
auto
dynamic_buffer_prepare(
    DynamicBuffer& buffer,
    std::size_t size,
    error_code& ec,
    ErrorValue ev) ->
        boost::optional<typename
        DynamicBuffer::mutable_buffers_type>
{
#ifndef BOOST_NO_EXCEPTIONS
    try
    {
        boost::optional<typename
            DynamicBuffer::mutable_buffers_type> result;
        result.emplace(buffer.prepare(size));
        ec = {};
        return result;
    }
    catch(std::length_error const&)
    {
        ec = ev;
    }
    return boost::none;

#else
    return dynamic_buffer_prepare_noexcept(
        buffer, size, ec, ev);
#endif
}

} // detail
} // beast
} // boost

#endif

/* buffer.hpp
z7Qpm8ptWZnkmHylVqEdaow2toudSswAbz56V6fx4kvQ5p5VhjjMBrQEyYQq9r2LADL6y8P0A/xsb1U/7Fhrr72cnPFu2VcQ+LnzUYliIx4tJAUKVVff89m+2OXyjU2zpNC01LaVZyQv8tOzN1rNzDbaO9aeq2/nq7PYrbUDXlr/AFBLAwQKAAAACAAtZ0pShX0WvyQFAACQCwAAIwAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZnRwc2dldC5jVVQFAAG2SCRgrVbvb9s2EP3uv+LqYWtsqHbbT2udBnUTuzNq2EHsLAgQQKAkKuIqiypJxcnW/O97R8k/kq5IB1RBIoni3b17d/eYfvfnXS3q0pNX6H9DXLh7i1Oj/5Kx++/dYfiV6h9YXeH+VJA+7Uy+hh162uQrHXiTsIlyyM9h+FSgK8bGf/pseRXyI1ZgxpbHurwz6jpzdHDcoVdv3vxOL+j1y9cvAzoRhZI5LZwsImmuAzpM/Mr7TNze9qw8Ckg6EnmvcbXMlCWrU7cWRhKecxXLwsqEhKVE2tioCC+qIJdJSlUu6Xh+ejmZfQxonak4Yyd3uiKb6SpPKBM3koyMpbqpfZTCONIpzOE8UdbBYeWULnqILclJs7Lsg8OL3GoSN0LlIkIg
*/