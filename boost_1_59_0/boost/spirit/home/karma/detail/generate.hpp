//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DETAIL_GENERATE_FEB_20_2007_0959AM)
#define BOOST_SPIRIT_KARMA_DETAIL_GENERATE_FEB_20_2007_0959AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/delimit_flag.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Enable = void>
    struct generate_impl
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (Expr) is not a valid spirit karma expression.
        // Did you intend to use the auto_ facilities while forgetting to 
        // #include <boost/spirit/include/karma_auto.hpp>?
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
    };

    template <typename Expr>
    struct generate_impl<Expr
      , typename enable_if<traits::matches<karma::domain, Expr> >::type>
    {
        template <typename OutputIterator>
        static bool call(
            OutputIterator& target_sink
          , Expr const& expr)
        {
            typedef traits::properties_of<
                typename result_of::compile<karma::domain, Expr>::type
            > properties;

            // wrap user supplied iterator into our own output iterator
            output_iterator<OutputIterator
              , mpl::int_<properties::value> > sink(target_sink);
            return compile<karma::domain>(expr).
                generate(sink, unused, unused, unused);
        }

        template <typename OutputIterator, typename Properties>
        static bool call(
            detail::output_iterator<OutputIterator, Properties>& sink
          , Expr const& expr)
        {
            return compile<karma::domain>(expr).
                generate(sink, unused, unused, unused);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Enable = void>
    struct generate_delimited_impl
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (Expr) is not a valid spirit karma expression.
        // Did you intend to use the auto_ facilities while forgetting to 
        // #include <boost/spirit/include/karma_auto.hpp>?
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
    };

    template <typename Expr>
    struct generate_delimited_impl<Expr
      , typename enable_if<traits::matches<karma::domain, Expr> >::type>
    {
        template <typename OutputIterator, typename Delimiter>
        static bool call(
            OutputIterator& target_sink
          , Expr const& expr
          , Delimiter const& delimiter
          , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit)
        {
            typedef traits::properties_of<
                typename result_of::compile<karma::domain, Expr>::type
            > properties;
            typedef traits::properties_of<
                typename result_of::compile<karma::domain, Delimiter>::type
            > delimiter_properties;

            // wrap user supplied iterator into our own output iterator
            detail::output_iterator<OutputIterator
              , mpl::int_<properties::value | delimiter_properties::value>
            > sink(target_sink);
            return call(sink, expr, delimiter, pre_delimit);
        }

        template <typename OutputIterator, typename Properties
          , typename Delimiter>
        static bool call(
            detail::output_iterator<OutputIterator, Properties>& sink
          , Expr const& expr
          , Delimiter const& delimiter
          , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here,
            // then the delimiter is not a valid spirit karma expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);

            typename result_of::compile<karma::domain, Delimiter>::type const 
                delimiter_ = compile<karma::domain>(delimiter);

            if (pre_delimit == delimit_flag::predelimit &&
                !karma::delimit_out(sink, delimiter_))
            {
                return false;
            }
            return compile<karma::domain>(expr).
                generate(sink, unused, delimiter_, unused);
        }
    };

}}}}

#endif


/* generate.hpp
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
*/