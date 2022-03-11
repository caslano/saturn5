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
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
*/