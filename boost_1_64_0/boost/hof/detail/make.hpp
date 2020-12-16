/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    make.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_MAKE_H
#define BOOST_HOF_GUARD_MAKE_H

#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/join.hpp>
#include <boost/hof/detail/delegate.hpp>

namespace boost { namespace hof { namespace detail {

template<template<class...> class Adaptor>
struct make
{
    constexpr make() noexcept
    {}
    template<class... Fs, class Result=BOOST_HOF_JOIN(Adaptor, Fs...)>
    constexpr Result operator()(Fs... fs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Fs&&...)
    {
        return Result(static_cast<Fs&&>(fs)...);
    }
};

}}} // namespace boost::hof

#endif

/* make.hpp
9bNlBkFpfLIJpX2S8B2+o4qnpq31TeH6Pmpn1rdC1odpd0LZ0lNh2GpqbX0niqm+bbH6LuL6CKcsa2xF+Xouf22s/B+Hq/44qD96G/ujcX1dYvV93azPTvVpbawvg+trcJr1eWR9lA+RVOXi01fJ5/W6KZytUYVJprh2ymKEFf3+AxwQjPLOmEgI9Q65kiUx3zG70UB6A51ZY3oSzmavGJPPBzKJrx9/s2VCdBgm+nzhK8rDH4X+SE+xCbpTn3Cswa5DpaOhQTiB3NErpH8hNvlY+gqm1CfxosLxmILe8XHQ4NI7HZuwOgUx7dqG4DM8fSKIF0Xc29TFb0WHpZZ4+IRt0GW1hlV9ce8xfv+myvdvYhv9+T3Wx3iPdQ17Vm/PCmLUuxtEMp6lrXyCSvwjYMO/RaVi9XmYntoaUpsGTan9XGU4ZRPJo/j80McriT5BqeI7s5XQ53QnbrlLYFOssj3kMNKetAFvDo22V3biUKG94airvSd13cLUtVXsztDDP9j80szQKHvwanArQPzbOkddb5f6ESMmzDYvuK4IF4nb5ijNrbcjKSweG2xfKnZO41hwe8WxvlxCdnCiuHKOSUwq+uJodvyW/EfGvIDGPNcvB/392WrQQxV/isbumWUZ+9rZzcYuGWpPXWkO/7hEH9p4iTVlz7bQv+ZY6F9+C/1rloX+ZUl/w5J+qyXd3T8xXGbJf7clvN7Sv1cut9g/ia9fnTdrvYb9CeOkS6v5EJu+7o4HDAbf8CmMFA3Jo3PvogxFlHaGppcX+nkz+EGv7BHzRuglti0lu6VXg4HrKpwOVKx3o4TO0CLtIeUEPFqk57rp5TSX+z0avnn6tSgb7/1jNmdCNXZqRCM5ZlCn49qZgyPcHewLWgQIq+V+A2db1QURPhjIUBEVKUYb7HQBzeer5hdTc4tlc29I1BtZ6XjmYUEVfEt3NMfcjZ/po0JjbJV9wldg0bavna6HxtgrM8IT1BLu2FDr0ak+ncaBXjtmiNEzuU6urNK331NBSWJSd3MIYKjKzE6/kigXu338fEqnJXwgrS6MuGK/WFBKd8H2/jymsfRqXztWHz5oHRU/0WHl1VBHedXe1R2aXmGPTMC3I1KAb2dkBL5dkVx8uyOX4rswko3vrEjvsZfQjLjHbsJcB93rplfY7AR+/CBQRScRnjk8oSsb6dwmi6lI6cPAdfHIinzi5nSDqq1nQyKismN4igTSagLIagMgLq8YUBIDyAyfGINi/HuOr5axFzEAMfhdTb87TqHMZIusYLiB4bpuUCjrwOiT1bLaLNgn66uiu+M2MMiaTt3VyZZlw2lTzm0Q8b0bmOJ3bJaq1llY29o3eVE91o0dmNXeQTKTxG8Jsc96tW58IumTKHdU62un4O3Iz8F+CKK7W6i7SxCJ31ulVsAonssTVzIAR0FHgeaSWgY75fpsqQK+PJ/m9I1+DLuxs2kiqEmbmzD2xwcpnjlMj0/hnA/1U9KUhMKPi0cE0g1EYGieshmQRVPoEyuujJvC1bdT9egz2X6hnxh9XMzmu6Jd3Fvw/0H8vw//f4L/b8X9f8j82za9o/+Vzxntbyh8BajUZBDSttv1y7cT7e7teFpVb7AetKPxtKrUYZJ297sYueokT3Lq2e+uei8twvuviLdHOI06sWDnwBM92YnZglZ7Y9b7sArM9aJ/H25+fhnW1TRw/teweIW3UZzf39DEGBCYrDlvZ0NKt4Bc8PTliuKpilxhFFFOhshXSjUh0+EiUgfrNLrIJSmOaLYdKEyRZHL6VTiQjVv5I7eAH85ia4o3ntSJW8Cv9VAKktGs2a7M7YjotcqJylSE3ZzDJ77C5yk12TFwrdHlSCY=
*/