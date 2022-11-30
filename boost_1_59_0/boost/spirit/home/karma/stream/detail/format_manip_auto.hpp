//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_FORMAT_MANIP_AUTO_DEC_02_2009_1246PM)
#define BOOST_SPIRIT_KARMA_FORMAT_MANIP_AUTO_DEC_02_2009_1246PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/stream/detail/format_manip.hpp>
#include <boost/spirit/home/karma/auto/create_generator.hpp>
#include <boost/utility/enable_if.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct format<Expr
      , typename enable_if<traits::meta_create_exists<karma::domain, Expr> >::type>
    {
        typedef typename result_of::create_generator<Expr>::type expr_type;
        typedef format_manip<
            expr_type, mpl::true_, mpl::false_, unused_type, Expr
        > type;

        static type call(Expr const& expr)
        {
            return type(create_generator<Expr>(), unused, expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Delimiter>
    struct format_delimited<Expr, Delimiter
      , typename enable_if<traits::meta_create_exists<karma::domain, Expr> >::type>
    {
        typedef typename result_of::create_generator<Expr>::type expr_type;
        typedef format_manip<
            expr_type, mpl::true_, mpl::false_, Delimiter, Expr
        > type;

        static type call(Expr const& expr
          , Delimiter const& delimiter
          , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit)
        {
            return type(create_generator<Expr>(), delimiter, pre_delimit, expr);
        }
    };

}}}}

#endif

/* format_manip_auto.hpp
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
*/