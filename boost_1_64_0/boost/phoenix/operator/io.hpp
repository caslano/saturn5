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
aOOezwL52PoEA00y8G5PlU9x6UmmoW3mBZ5kJ2u0irpa1CZKhXealZi36zf4BNRSItcsIGLkcYT2w5w84kjRP48HiB/pxkferx7bvYxcxgRM+f+ktt4f4aWKO0RHZA4HaOJXLB547C42zQlm/goMYwxrluPAbkS7n+jm+TXU1OQpY81+ElqpqG9I0namjt8CZ42oCsa5kVOliAczR+rwi9S8MeNSmUKj/92nJps9Hv3rM6dQHKphdnoEg7LsanqhC2qKEp6Rcx3q8R2sA/ckw/rWhOKOGGYsRw5FQOZ+e8iAAQsSuMmlW4H436nOgzUsz1Agt6lRKfvqNXFs8Od5L4dyPqRkxsPW7K7T/IQaIc//GZyZWRsPlxh0vDMrJ5ZdR7g0tD84su0sSyyIHyQBK9urbIk3Y1fA6tv3AfkylqVegNhRGToOd+qdH76Hmhd9s/RokxHtqQkiiTvmYenogBEfsfm98VktWCBExLp9Nw8V5ehqBmd/40hYmMnZgh75QUKwPwF2AupyL0v/95WkmZaaZC711fbAvei95uLPcsX2vbgm6Dc51l8yhA==
*/