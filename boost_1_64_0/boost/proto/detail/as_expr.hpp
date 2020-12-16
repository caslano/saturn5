///////////////////////////////////////////////////////////////////////////////
/// \file as_expr.hpp
/// Contains definition of the as_expr\<\> and as_child\<\> helper class
/// templates used to implement proto::domain's as_expr\<\> and as_child\<\>
/// member templates.
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_AS_EXPR_HPP_EAN_06_09_2010
#define BOOST_PROTO_DETAIL_AS_EXPR_HPP_EAN_06_09_2010

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto { namespace detail
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Generator>
    struct base_generator
    {
        typedef Generator type;
    };

    template<typename Generator>
    struct base_generator<use_basic_expr<Generator> >
    {
        typedef Generator type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator, bool WantsBasicExpr>
    struct as_expr;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, false>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::expr<proto::tag::terminal, term<value_type>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, true>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::basic_expr<proto::tag::terminal, term<value_type>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::default_generator, false>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::expr<proto::tag::terminal, term<value_type>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::default_generator, true>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::basic_expr<proto::tag::terminal, term<value_type>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator, bool WantsBasicExpr>
    struct as_child;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, false>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::expr<proto::tag::terminal, term<reference>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, true>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::basic_expr<proto::tag::terminal, term<reference>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::default_generator, false>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::expr<proto::tag::terminal, term<reference>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::default_generator, true>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::basic_expr<proto::tag::terminal, term<reference>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

}}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_expr.hpp
MkGmwxhwh24VxZwzea2LumvFFOVHmpFd8XsHvlCV0bkpWqgvUgv0oUyAQWxLkJLe930DOb+zVaZlzSv3AieWeaEz6D+PRjwqUStZwR2vf9/qH9V8qs9eUREcOYXPARDxKYTF5Dd1mvj3LSf1HPhOtDakz6quSNuK6MvzU+mDro/Tn+hMrnReSwGf3n/wbfrez4jqSkSa13WWFqWAauiuSFFBh++TrwDaSM+S4aqz/7VdNh5vPG7qpYhfJlJTWd2oXLQrq6Q8YWFpNlyEW5Iehefz04hPKkBQLUHey8UDV3a38Msdx7vX+BOe2QUF71b0WBn4XPn9sd0gsKlK2+VuPpCWxb/XjRMsemUWyzV4N86nFZnulCqSTjglOk+9GnIszwNNlGO5kY1qtSWiXtXjH3GgS95nz+d75zzmC11UbWU7FykI9pu+znA3eBjHH5up2lyPg09AB5NBsD4Ws3Azpis6mWR5ZrGiqXT3onka9REmqFZZqWvwp8O02OMHKmABLfW9C7QviWihjaqRRreG66J4L3m9b4lolTDSNlWSVGIRzk8Q/cHHBgSqUURe0RyNaKGPuWpgk0j93AJ7uD5lELQfOTjtOPtAsz4PTcSrEqpUKRxclYDIJy1jE9uTq67nk9D4/zH6znWXZrIDp/Gj/Y4Vfon9GkCgHeRY0SmGDiyBdNrqP9qbGXBes/49PeKVoG1Zp3SbT+cV63qORLSZ6FSVyVazeAA4IGY7nkyqG34bMegPvpMYU5YxHw1RcB5/EKtZH7PyIVHcwqwrurqqYVd0f/x917/n8Lpnm7bNcwkziq9LQbyPvCrmnXSdSnorEUZw3vu6Rv3KhVJtBURyPE/uz+fJHkw3F5ead4q+0R7nY0TbmSo1SStodB8AEQDi4ZhZozY/g9POpVmh08rYPoLLg3ybL/MxHj4w9B8r8hb2E/HfmcCM7QL+4v1hTAd3wkX33g/l3m8fSvWDHC6PswUXX0B15d7OQTbuPTCUX82VJ6685+1tGtA6qMf1dgtLD+xsssh5XLtvHxyu4I7Tl3u7BVC8I3PC97YL+kG2g2Iq97YKwAXNFVj59QN/hPg23iCUuzIfAwxUqYz+xsQ3aaIxuYnPQQ3fgZXflMbQFTvePhYYaMEY7q368cPcDZz37cflOFAP7BYU4mE8NXpvGj43QR1gE/FXgNOFncr+DmXsMj0u+6fDcyXM5+gdV8R6YDr1L+e36998n3EVLJ8mks94nCtfg+HEIrmPh/XH6yIOiH7u9X0s+s0wW/LPXw/hvTjO4n/d7QZYzq/yAbZ0Z4RFIr7vz5PuhjC8Y4GuN+hmIXdEfGZ0bZY3WW7JL6UXCSd0q1zOajgPlQpbpTpDfxSzDkJWkLQeB6FwvCUU8WZyzXM4H3TBh4PUGgOiO9C643A0fOd6BaeZA6FGG5OVYg8NAyjnE8nBr436Wggjmy5rcy0yVNfxd1HoLuNAdX2E05+qu1J3Umqxi72kPGo+n3RUVyZkqXIppRKLj9uAewfxBxu5zf3zW6MJm/PLnhLJ3HVTttJA6CEKFOvvV1E9UlSw80ub9TpgCMby2I2x4EOUXCf+y4i2FjLN6sK02UHfHkLe00Pq43z+qXfwduZFVWqTWLGys3uM+vQ4H2eV40Jv2razRZUnolXgII/Bv1itfC+HIz/ZCXr4e3M+x0BP3XQYpspVyOI2incMc0HWRZVo/R/rc3yC7RHnM6drAxfgRolgVs78o85FfWxAzq6zptONWNwDYX4F6gEjy40LU+sVzDZLHHFv6YjFwpY1tyO94zA3FuTF6nPsrBDO7FMGONkGGNGPkVZIB3Kbs3Dvp3r6uHoEu4+jh0NnmWxXt/w=
*/