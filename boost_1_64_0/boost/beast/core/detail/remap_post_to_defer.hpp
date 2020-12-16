//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_REMAP_POST_TO_DEFER_HPP
#define BOOST_BEAST_DETAIL_REMAP_POST_TO_DEFER_HPP

#include <boost/asio/is_executor.hpp>
#include <boost/core/empty_value.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class Executor>
class remap_post_to_defer
    : private boost::empty_value<Executor>
{
    BOOST_STATIC_ASSERT(
        net::is_executor<Executor>::value);

    Executor const&
    ex() const noexcept
    {
        return this->get();
    }

public:
    remap_post_to_defer(
        remap_post_to_defer&&) = default;

    remap_post_to_defer(
        remap_post_to_defer const&) = default;

    explicit
    remap_post_to_defer(
        Executor const& ex)
        : boost::empty_value<Executor>(
            boost::empty_init_t{}, ex)
    {
    }

    bool
    operator==(
        remap_post_to_defer const& other) const noexcept
    {
        return ex() == other.ex();
    }

    bool
    operator!=(
        remap_post_to_defer const& other) const noexcept
    {
        return ex() != other.ex();
    }

    decltype(std::declval<Executor const&>().context())
    context() const noexcept
    {
        return ex().context();
    }

    void
    on_work_started() const noexcept
    {
        ex().on_work_started();
    }

    void
    on_work_finished() const noexcept
    {
        ex().on_work_finished();
    }

    template<class F, class A>
    void
    dispatch(F&& f, A const& a) const
    {
        ex().dispatch(std::forward<F>(f), a);
    }

    template<class F, class A>
    void
    post(F&& f, A const& a) const
    {
        ex().defer(std::forward<F>(f), a);
    }

    template<class F, class A>
    void
    defer(F&& f, A const& a) const
    {
        ex().defer(std::forward<F>(f), a);
    }
};

} // detail
} // beast
} // boost

#endif

/* remap_post_to_defer.hpp
u9eQa+tA7ibKbaPcJwy5dspFuMjVUa4eaPlvolwB6DjltlLOPO+5DHwjgJXAicCrqG8vcB5wI7CQ5/fW0J/n7HLfKcqQ8Zrn7P6a59oeBg4E/gY4hG6/fCvlh7vIv0T53/Fc2JeBiXT75Y9Tvq+LfAP1sZl6/DgwGnhtQJ8QCF0OOyh/N+V3GnLxHchdT7kbKNdIuQpQOuWKKRcDXEO5Kzy+/H4UOIDuBLpnAK8EzgUWsf6XAC8GFgNX0X053f77NfN+ZS7368f79AemAgcApwDjgdOBA3nfoeyvBwGXAofwPonAKxn+N+lXuDcq0J9Kub7K++3lecCPAaNp8zWe53sn0fZrOm2/ZvGc7xye8z2D53vnAZ8E5tMWbAHP9S7ked7FwG8BK3ietxf4HWADsBX4SeD3aIvzB8AHgAdoI/RHQPCqZ3he+LPAF2lr9ihtzZ5UMv6Tc+J/pm2Scq8V8C7q2bRJmsd6PJ/1dwFwPPBCYC7wIuYvH3ghzy1eBlzEdC9lf70MeDPDWf+59wfPVJf6/3Pq+xfU7y9530PGOddeyidS3jznupnyX+A50Q8AY4AP8vmzh+35IePc6SbGF+3SLs4P88U3CxgFvACo++0O5KZRbjrlzg0LpL+Fcmku6X+Ocj8FRgJ/BhwAfB44WPpgX73/uRFfewfxfY3xPcH4nmR8X2d832B8+4344qNDx/ddxtfK+L7H+L7P+H7A+A4Y8eV1EN9DjO9hxvcI49vL+B5lfI8ZevdGh9b7JMY3mXrPMdLRSLlhLulYRrlLmI4CYBzwUqB8WwUmAVcY8TV3EN98xreA8S1kfBcyvosYX74RX2sH8X2E8a1hfB9lfFcyviLGV2zWiw7iu5Xx3cb4bmd82xnfHYzvTiM+1Td0fJWM7yrGt4HxVTG+jYyv2ogvvYP4rmV8WxjfdYzvesZ3A+NrNOtZ39D17LOM7x7Gdy/r2edYz+5jPdtlxOdlfMtc4tuhfOO+TwMnAD/Dfn8X8HwrXuB8uvU4qG/o5+9jfP5+kc/ffZ6A3PEO5PZQ7iHKPWyMc2R9F2CASz87lvrIYjsZB+wPHB8WkE/vQD6B8oMoP5jyQwz5vA7kUyg/gvKplE8z5Is7kO9D+SjKR1O+b6CfQMcfWm/3U2+7qbfPG3prigk9PvsW5Z6m3Lc5PvuOOb7sQP6rlP8a5Z+g/JOGfEsH8j+i/DOUP0j5Zw351g7k36D8m5Q/Tvm3DPm2DuR/QflfUv4Q5V8w5Ns7kP8D5V+h/KuUf82QP95Bub9L+feAUcDTwP7A93V74TwfcJxLuV/Acc0sYCbd/vZeQLkUeR4a7Z3jf8X3gTDgi4znt8ChHPcPN8b56XruCchx5UirnQCtawXfg1cDxwIvA06jDfZzaYP9ItpgXwIs5nixhOOrtXw/vgt4G7Cc48Mq4G7gRuBjQC/wCWAtbfLXAX8DrKct/o/RBn8D8J/Aj/PMgS3AMcDrgOOBNwAnAbcCpwNvBJ4HvAk4B7iNtt4/CSwA3kwb77cCy4C3ASuAdwK9Hkk3y4tzRMD+LuU1g3qfSX2fZ8g1hpJjuSqWcz9xs1wU5zo4fsS3Ivk/mHIXG3ytXeRr7yKf6t81vvRO+KJRMVt2RKk20DFQ9N1RKhOUB9p1K9y/j1ANtVGqeVOUKoPfNtBedOwHQMdAKTjMoADUCHoC1A4qhv+SGhAGulWgW0B+u/rHawK29SMuACFRWaDMCwK29g+/HKbugV+LN2B3/5AX8YGnCnQiO2CD/xT8nwPGT0R6gOnAuNlAi64OU7NAZaBc+OfBbyf+7wGtwf/9wHz4V4EaQTtBLbTj/5LFB2yFO77WZ9P/ObhPgHLhXgI=
*/