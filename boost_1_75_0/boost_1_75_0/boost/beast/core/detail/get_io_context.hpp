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
U02h5M2pAFq7gahgKO6+ElbyWDdFQpz9VvcXHVtJpdkT7O+pIn3wt18/CL3uCedfSMx5r9nXI78UFlsj92F6XaZ58xbzmcnIrmMiC/QnlvPlJHgVoHZMmkVnDRwjOPHIWKh1xXvJd5DOGXeaDpKId9bGE6x213BqEu1xgdMkEstJirMAeTAnEdFmmTCFid8p0CQ9Xwnl3DNkkeS+sWdLuY+Kp6jEjpFMtrFiF6aOKlYe9YceV5STIgiTfwjCOe5Qf7PvurmMNoT4KhkthxidsQKvk03m3jOSEHqei57FVGB6sP3RXkhnkXtvUviDd759Ir7kq3Pv+chFhO98W0PokZlH6FEQl2p4/wlC7JF5I9t7AIq+BC4ih+/IkVJ/GJ+T9t+4NhgTZC7dbWBT1wlL3NbPXXm9En3Wk92W997kn3bNw7WI7D6Maun3Hh0HXDCzZyvapIxF3B06syec4uXZdpBgMa0TPIxxl/YdOBTrELAn7R/+zuEv3R47m3tnnlMEkri4veFmf47j6zKMyteTeMBd09Ejwclpwm3oOLJgDiyIvt2Uhow879jROT5/u+nudrjsYAjw4Q8kiuGzRYPLseEusQ6Fa+zCaRQ9oOB8v/mQrFASyw0MFpRFwrz+FicHNSalhI/JkS1Trlhu6c937gBpYMW3MBa9H5WwJMxOsshIwZrPDDv0umuIOY/Z1tNuddAs3GnRSq0Sbuob
*/