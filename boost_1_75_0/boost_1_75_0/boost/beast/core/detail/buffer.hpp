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
CoPJLDtnee2XSAaUxW4VsYEiC3Pz2mH2rLbJhHQEgZSmRGsyhq3ZDC34eRGM6g9/IUUWdLNlG5TCATHL4TQRy35KzU/cwa6bhdxvnS1SkJxSBn5jRN00T10uzM4HjtM72WS67CcG88X6KZuH/GHUDRPWT9x1P2F47fS7JVvFb5LaaVQirVu+6B2fpaJBsTvfcLZNUaHA1KKhg7GiSQt/Q1rxBUK/FsqFhtkmboFNbII2voNtU2SCXhj61dfRm0uep9guwStNh+k3AgGoSXdby7W7ix7qACIL2bPBj0MK06lqFKhttzuD+bXwk4HD7M6Tc614vvrtvrJdPfMojNifKQfSuehjj/TwtOD63tflKtqhjQE1pXlGeJL+PNqhVfe2+GKI3k7QTqT32b22BS0ZbAgPPuFeBs8YxW0bn8Pkkppgd8weCNqIPv6y+uA/aKOVIy4gKrNbIXDBKXZL/cC5Qq8mXOq1tGVvxPDAX8I8g0vzx/9BM/UHj1SfzbPfuoiXEM+QHuDPu/224Bw+8XwgMa9vMipHPPrQCgfYQkaAYxJn05X2r7Z+5XnD6ZbNJj6C9/JXZ4RVMkgIz7DAT8IjdntuiYkuH2JHIbDA8X0rvjG+wvjx+TO8FDyOB3YzQp//B5GHKTXXTpTNj2o/2cuEtbBpbPwwmjF9ZPe7PsDM8C6mcaSyhD5zt1Zo89l9UBC0i7wzG4isJB+sj/Nj
*/