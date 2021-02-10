/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_IO_HPP
#define BOOST_PHOENIX_OPERATOR_IO_HPP

#include <iosfwd>

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        typedef std::ios_base&  (*iomanip_type)(std::ios_base&);
        typedef std::istream&   (*imanip_type)(std::istream&);
        typedef std::ostream&   (*omanip_type)(std::ostream&);
    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  overloads for I/O manipulators.
    //
    /////////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_left
        , phoenix_domain
        , actor<Expr>
        , detail::iomanip_type
        >::type const
    operator<<(actor<Expr> const& a0, detail::iomanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_left, phoenix_domain>(a0, a1);
    }

    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_left
        , phoenix_domain
        , actor<Expr>
        , detail::omanip_type
        >::type const
    operator<<(actor<Expr> const& a0, detail::omanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_left, phoenix_domain>(a0, a1);
    }

    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_right
        , phoenix_domain
        , actor<Expr>
        , detail::iomanip_type
        >::type const
    operator>>(actor<Expr> const& a0, detail::iomanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_right, phoenix_domain>(a0, a1);
    }

    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_right
        , phoenix_domain
        , actor<Expr>
        , detail::imanip_type
        >::type const
    operator>>(actor<Expr> const& a0, detail::imanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_right, phoenix_domain>(a0, a1);
    }
    
    using proto::exprns_::operator<<;
    using proto::exprns_::operator>>;
}}

#endif

/* io.hpp
pBKYAzyWxgKwslIVPXAzWda5cRiOXmRGkbgRMhNLEAlLqbWl+cHzokpn8N6LVWS86P76vdTmDze5hBO52JAqLVlFleEuOc0u5SqWiVsREAjLaplJk3a33oCqiD2lyXCWOSzYSTaN20xBG56uU6MSHkvrFqMK46jWqcqfKCKODiWpdAEixAFKsUKYu1ShqXStXN/8nqKNaR3gZ1Oz9TcmVcAZ2ukHNAp2aCmMNF36NJpfTBZz+tSfzfrj+SVNzqg/vnRgH0fjIVIvQaaJb0vNBuSaZF5mkuOW8+s9XmdXFlFWxUw7hvUN69CwrcpeutPBXGguV5cTVoGKWWtp2YsyhYnSBkXoUng2sTBqVBOXoo2xjMCtcRVV2Q6aRdoegfBhIAX+eTD63ac3R8cEqlhYgcyuci4sGfkXN8oyoUY/RoeejxeDEA396hXtPbzSh1N6jSZHA4Lmkfz0lI5r3f8A/DIaT2b3ME9lDuvt/v5+Z5daK5r2Bx/9YRjMZ4vBHINF2Da7Yei4ShFdcww02HBm+FlL72A8mV+gelzQuUCt1xFeGFmsENoGh1A6FeYgOnIpC6E3rqVxqNVKi9wlYcmrlbNwQYYYDZijpJZNiOuCRSaAUyeT1gByKcOcwci45qa/0b5rbmZA896QoubY
*/