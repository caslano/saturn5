/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DETAIL_PARSE_DEC_02_2009_0411PM)
#define BOOST_SPIRIT_DETAIL_PARSE_DEC_02_2009_0411PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/skip_flag.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Enable = void>
    struct parse_impl
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit qi expression.
        // Did you intend to use the auto_ facilities while forgetting to 
        // #include <boost/spirit/include/qi_auto.hpp>?
        BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Expr);
    };

    template <typename Expr>
    struct parse_impl<Expr
      , typename enable_if<traits::matches<qi::domain, Expr> >::type>
    {
        template <typename Iterator>
        static bool call(
            Iterator& first
          , Iterator last
          , Expr const& expr)
        {
            return compile<qi::domain>(expr).parse(
                first, last, unused, unused, unused);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Enable = void>
    struct phrase_parse_impl
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit qi expression.
        // Did you intend to use the auto_ facilities while forgetting to 
        // #include <boost/spirit/include/qi_auto.hpp>?
        BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Expr);
    };

    template <typename Expr>
    struct phrase_parse_impl<Expr
      , typename enable_if<traits::matches<qi::domain, Expr> >::type>
    {
        template <typename Iterator, typename Skipper>
        static bool call(
            Iterator& first
          , Iterator last
          , Expr const& expr
          , Skipper const& skipper
          , BOOST_SCOPED_ENUM(skip_flag) post_skip)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here,
            // then the skipper is not a valid spirit qi expression.
            BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Skipper);

            typedef
                typename result_of::compile<qi::domain, Skipper>::type
            skipper_type;
            skipper_type const skipper_ = compile<qi::domain>(skipper);

            if (!compile<qi::domain>(expr).parse(
                    first, last, unused, skipper_, unused))
                return false;

            if (post_skip == skip_flag::postskip)
                qi::skip_over(first, last, skipper_);
            return true;
        }
    };

}}}}

#endif


/* parse.hpp
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
*/