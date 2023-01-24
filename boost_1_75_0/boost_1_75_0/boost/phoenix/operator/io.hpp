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
+go538jS8qKbR+LT+KRaS2LCdMmxU0+FiGWPg6LZTMCMk+PJsWxb75C8uK90gzMDuLzC2HT3nVrQOqcLlzIhm81ljPs6nn6xNSeh49D2rwcl5gHMJ/7YJZc469JK9rBMrrxfSiHr6845nAffPFGEsKut/J+2R0aK6DcSyXlHLUG4HE+8/IPzHVN7H/r85NpJmZP/MGjJ0OREGfElKPKmdACDHL7klnhFeOYbg5w9b7207nQZS9p/Sx9nZkX9ji5AfblwQoqc9l9YmykMpG4bOaCiVNp1M8GsFU8OWS80KzVs1Kh6MupkcY2ZrdNgCXIyRWsXjf1LrOuDakehJQIouSZgxCcWlF+jcT2x3POKZlgps4O2rBUiV4Twury7jlItW6dg2hQjFeysGybQDTMrQJfeHPzUxDn0xR3oWWA5jgHU/qhv26Qya8SSWtNnXEKx8juRTPHzJebhW+/EbZ9qJaEJrEMB36pM7YXyqaLy/IZ+VSBjAC9jkHVy6XWvdybQt+zuliRuYlWv5mbdb09s+tfOFukEvjJDgHHCwAvHUzcrXuDkEJETENOOfJUJ5gy3TXfCC14tl65BnSnCWmW3w9D+Xnut0K3/5dl2zLu4+4qifpB2UoE6kayPoLnK1bhmxLgYzD66FgBIJklnPnnoT5xCQMEnu+tPwjWBp9C4uUf4slCH9tyGAHnCeE5AOLZRyqKtEy/b1PX41jNY
*/