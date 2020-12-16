//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_GET_IO_CONTEXT_HPP
#define BOOST_BEAST_DETAIL_GET_IO_CONTEXT_HPP

#include <boost/beast/core/stream_traits.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/strand.hpp>
#include <memory>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

//------------------------------------------------------------------------------

inline
net::io_context*
get_io_context(net::io_context& ioc)
{
    return std::addressof(ioc);
}

inline
net::io_context*
get_io_context(net::io_context::executor_type const& ex)
{
    return std::addressof(ex.context());
}

inline
net::io_context*
get_io_context(net::strand<
    net::io_context::executor_type> const& ex)
{
    return std::addressof(
        ex.get_inner_executor().context());
}

template<class Executor>
net::io_context*
get_io_context(net::strand<Executor> const& ex)
{
    return get_io_context(ex.get_inner_executor());
}

template<
    class T,
    class = typename std::enable_if<
        std::is_same<T, net::executor>::value>::type>
net::io_context*
get_io_context(T const& ex)
{
    auto p = ex.template target<typename
        net::io_context::executor_type>();
    if(! p)
        return nullptr;
    return std::addressof(p->context());
}

inline
net::io_context*
get_io_context(...)
{
    return nullptr;
}

//------------------------------------------------------------------------------

template<class T>
net::io_context*
get_io_context_impl(T& t, std::true_type)
{
    return get_io_context(
        t.get_executor());
}

template<class T>
net::io_context*
get_io_context_impl(T const&, std::false_type)
{
    return nullptr;
}

// Returns the io_context*, or nullptr, for any object.
template<class T>
net::io_context*
get_io_context(T& t)
{
    return get_io_context_impl(t,
        has_get_executor<T>{});
}

} // detail
} // beast
} // boost

#endif

/* get_io_context.hpp
Xhf5irvI19hFvuYu8rV2wlcQpmTv3T7skzoAaged3t75fr3cbPh5g88+OgGKn6j34rntw+P+u+C9d411sv9O77s7dk6k6967LNBKkH+v3T31QfvtuNcu9D67zDuiZJ/dMZD6WGBv3Yw7onq8v24byNxDdwhkP6PIfb/cE4+47ZNz7pHrfG/cPd+L4P64wN64AuSrHnQP6GlQOyj6ziiVDSoAVYF2gZ4GtYNOgQbfhXBQPsgL2gl6GtQOimiCnkALQGWgRtAu0P6m3v12vVfv1Xv1Xr1X79V79V6913/migBd9SHu/7/Gu6ZO/osJgJ7ZALD24h/LwLs718AeiOQeuzB8PwbuAD6bhPfN/jLHtXB1QVHBvIVFvvsrZZyV48XSGX0GCvkbVKWK02vZHxW/OFkf1azA6zvnjLI+41yc06T8Grrtsnt53wi5b11JVb3vvgVa7np93wKHbEvgvpSV+/IsJsrjC3GyZ4g+i+lgvNgxFPn94I3R8sv0+vPbRe6SsFTcZ4cKM9eJMU6PyLfa5GGDgfuIqoVnQ9gCFa6+DNJrxwz5BCxZOuh3o4S2eT4w4vLq88Sul/A2zwSkpVl5dFwzHGlps+liY0nDxnLMjgdsAIwdIHv61VwVhW9tkTqePEc8+P5pnPPIc6pYD8pFd6laNt8h267TQFlfcWj+Agf/UepvkywELtTrxR6TtA7Q+2SS5L55Bu9KlUDep4T3Tmj5Wt7bukqqsIJMzP4lcM3/OcL3Oc/v1VyxE2Hle6743efpr+XmSYoT/HYdJK2vesbizgGe1eAJ6OQD4Zlp7J2pvUbWT9OWwtUSvj4sDz3JY6BHPGY+Vut8PC1puRbz0EWqP+vGAfFL8sSwPJA+vcd8t4SN94zBvHK0CuzX+kYy7pmB78Yg//+RnHNu6GTf1oPxdrt8aNc8v0r6A1lrhfbKMwJ1OxfeFmCE8EobFt79mle3TbHl2Kr9l4n7oHbXirstcA+J57B2B+o197DwDE2pp8J7VHjpZ9gInMd5/0PRSq4J4b429E/r0022Uk0DpU9EQutKpubMKPpYTS1WP3jLSyvXVZaW1FfWWGXOcsMcf3XNpnptb+R5kT0WxjrBuG7T6xy+O8hyPx9k72ODB2UkYb+WsPtT8D0W/WwytvggsXJNSfDZEggXG6KrPYkIu4pzm1dJ2I9UvNqrUikTAZog/r9U4dj5tVilq2q1VmUwPBr0R0nfdM88zFq1qb6YE8nHvCL2I4PHf6bIX4Tn5x7LbyNtgYVJvMfErwp+gy39DdR+sjcsyZqvNfyquW/1pOE3lN8VB0l8PxG/JH4bjzf8BvP7dj/xe0b8oDOZQ4gRv8c8ydRHDvxGi1+JZzi0cYFql/xUenzf+EdKWIvEMYjzEyPEb5/4JXBuIVn89orfQOVTdJ74oR+Xe3lwL/rpvnAu8sNyR43y+W1Ffpx+HpUV7BeebfjRZopeLxLFdVvNyvVa7LTjkcD2s0naBesp18KgfsGvwbYOJrq/kmtdhK/dFAA3W+1hiLQH39hgnrUed2llgzLbwLwiOOU5VgB8RvgnR3xZxbJv9MfRwmcv7j3Mct/EcQV69ETpf8PxdTE80eLRfs3h0xDPT9UPw2IC9+P4QcfLPYx+mc+Gx6hbQPp5LGnLx/9vCf/5Ed9k2gqMOBLFbb/vs+rZMLZHXIUc4+i84/LOUypw5uf3Ja6pEV9TkzC/vM/TX/yhPYlzlKQD9Y33+Lrcg+nEVanztUj0c4trvhL4zGqTe42JeMiII1pdpcdqxSLzgBqiZrEcmA7MerGeyzVP/FJVovhJPafspaofxpy1WKl0GJ3FLf3wHLT2P63bOjZu4Absm0yNHRc=
*/