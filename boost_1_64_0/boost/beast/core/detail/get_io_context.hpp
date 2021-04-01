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
rbabM17zC4UXOB/fqvb2xViTD5MjglxOtaWF+/vXKNKRMtTwf0wBb4gi22BW1Ym9GwNfSn3Kuce0d3qq1J05QpN9jVjsjaHtcnJ329pFnh1M3J2t9Kqi0vY8gb2OZyPgjw/qmDeteN1wr3EeeM5gxvuFI/BrybLaqMn8mPGGeCXO0SAzZ4UPLMT0UN/DtPngHPviJXvoLsM/xvYGm2c4HuYWU+bEQFLJncpCsx65y1PMuzS6HHbY/t+V1u3k+7LYSOX4TzgthJm0Ydu1CbRDL8BKwf0b9ULSj5GT3oYzLTUfEidtwmD410vK9EXw1w8pgpLrFJCheHPOa6D6irZiOzdWP+TVPJmgpy7uO0uCELN+LbSl6nBTj2KrBPJX9n2IKDxo8VO0fPD4Batz8sSJGWG5t1dbv2ZSSX8JMEiDErBSI0Z7j+HNoat04cP0b3m/wEkvhBkEJrLSGh67l8dEpqScVgKauYw1wr9XwM2dpeiYLOigd6IfyyzVfFRIJByUClk1fAtUOv/6gCSAiTth+ksmqZrrVATOsiQ81dyD3atRLSZAmqMdm9TlnQ==
*/