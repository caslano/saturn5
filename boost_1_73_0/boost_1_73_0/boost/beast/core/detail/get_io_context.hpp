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
usL3x5x0YaPyxW/B4ypfwDEqfuXllJ59/zFHV4SN/nRJ88qnRzxBNdLsy/yuENexBqffgpevX/8GL+DV0asjFwYsEzyBuebZkhfXLpyG5uRtzG5vO4q/cYFrYEmnMrWIhQIlI71iBQd8TkTAM8VDYApCroJCLPGDyEDHHCKRcOhPppfD8XsXVrEIYjJyJ0tQsSyTEGJ2w6HgARc31kbOCg0yQnU0Hgql0WCphcw66JuD5kWqyAa5Z4mSwG6YSNgSHTENsda5Ou52g7JIEH03lIHqBnX4nVin60guEUTK7kDmGrSEUnEXSNKFVIYionckBA/zcpkIFbsbNOgqC7uyAMWThGyhnuDKwuYwr+hxSQxyRCw0vSmZKXK1imW6I4g8kpWoLDJ0hDygUCiRZhfKLOSFETaR1y4qTg3B/5uaDd4QZIZgoNmbw3DehCVTQrlwMVx8mJwv4KI3m/XGi0uYnEFvfEnGPg7HA0y9QGcF8Nu84AqdFyDSPBE8rHz+vFe30W3D6cCb99+Q+/M8kczwcLaYulggqkxFdg0R5pr4KVimImSUcMBpt9brNhq/iCxIypDDqdJhIpad+M3umZC7R1Qqtl7wmFBgBSoOMWfIvIIIg+7LDO+HfjHi2bWOyY3STIsAlPiX+xquuQ6s
*/