//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_GENERATE_DEC_01_2009_0734PM)
#define BOOST_SPIRIT_KARMA_GENERATE_DEC_01_2009_0734PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/context.hpp>
#include <boost/spirit/home/support/nonterminal/locals.hpp>
#include <boost/spirit/home/karma/detail/generate.hpp>

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Expr>
    inline bool
    generate(
        OutputIterator& sink
      , Expr const& expr)
    {
        return detail::generate_impl<Expr>::call(sink, expr);
    }

    template <typename OutputIterator, typename Expr>
    inline bool
    generate(
        OutputIterator const& sink_
      , Expr const& expr)
    {
        OutputIterator sink = sink_;
        return karma::generate(sink, expr);
    }

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T>
        struct make_context
        {
            typedef context<fusion::cons<T const&>, locals<> > type;
        };

        template <>
        struct make_context<unused_type>
        {
            typedef unused_type type;
        };
    }

    template <typename OutputIterator, typename Properties, typename Expr
      , typename Attr>
    inline bool
    generate(
        detail::output_iterator<OutputIterator, Properties>& sink
      , Expr const& expr
      , Attr const& attr)
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

        typename detail::make_context<Attr>::type context(attr);
        return compile<karma::domain>(expr).generate(sink, context, unused, attr);
    }

    template <typename OutputIterator, typename Expr, typename Attr>
    inline bool
    generate(
        OutputIterator& sink_
      , Expr const& expr
      , Attr const& attr)
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Expr>::type
        > properties;

        // wrap user supplied iterator into our own output iterator
        detail::output_iterator<OutputIterator
          , mpl::int_<properties::value> > sink(sink_);
        return karma::generate(sink, expr, attr);
    }

    template <typename OutputIterator, typename Expr, typename Attr>
    inline bool
    generate(
        OutputIterator const& sink_
      , Expr const& expr
      , Attr const& attr)
    {
        OutputIterator sink = sink_;
        return karma::generate(sink, expr, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Expr, typename Delimiter>
    inline bool
    generate_delimited(
        OutputIterator& sink
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit = 
            delimit_flag::dont_predelimit)
    {
        return detail::generate_delimited_impl<Expr>::call(
            sink, expr, delimiter, pre_delimit);
    }

    template <typename OutputIterator, typename Expr, typename Delimiter>
    inline bool
    generate_delimited(
        OutputIterator const& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit = 
            delimit_flag::dont_predelimit)
    {
        OutputIterator sink = sink_;
        return karma::generate_delimited(sink, expr, delimiter, pre_delimit);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Properties, typename Expr
      , typename Delimiter, typename Attribute>
    inline bool
    generate_delimited(
        detail::output_iterator<OutputIterator, Properties>& sink
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , Attribute const& attr)
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then either the expression (expr) or skipper is not a valid
        // spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);

        typename result_of::compile<karma::domain, Delimiter>::type const 
            delimiter_ = compile<karma::domain>(delimiter);

        if (pre_delimit == delimit_flag::predelimit &&
            !karma::delimit_out(sink, delimiter_))
        {
            return false;
        }

        typename detail::make_context<Attribute>::type context(attr);
        return compile<karma::domain>(expr).
            generate(sink, context, delimiter_, attr);
    }

    template <typename OutputIterator, typename Expr, typename Delimiter
      , typename Attribute>
    inline bool
    generate_delimited(
        OutputIterator& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , Attribute const& attr)
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
        > sink(sink_);
        return karma::generate_delimited(sink, expr, delimiter, pre_delimit, attr);
    }

    template <typename OutputIterator, typename Expr, typename Delimiter
      , typename Attribute>
    inline bool
    generate_delimited(
        OutputIterator const& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , Attribute const& attr)
    {
        OutputIterator sink = sink_;
        return karma::generate_delimited(sink, expr, delimiter, pre_delimit, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Expr, typename Delimiter
      , typename Attribute>
    inline bool
    generate_delimited(
        OutputIterator& sink
      , Expr const& expr
      , Delimiter const& delimiter
      , Attribute const& attr)
    {
        return karma::generate_delimited(sink, expr, delimiter
          , delimit_flag::dont_predelimit, attr);
    }

    template <typename OutputIterator, typename Expr, typename Delimiter
      , typename Attribute>
    inline bool
    generate_delimited(
        OutputIterator const& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , Attribute const& attr)
    {
        OutputIterator sink = sink_;
        return karma::generate_delimited(sink, expr, delimiter
          , delimit_flag::dont_predelimit, attr);
    }
}}}

#endif


/* generate.hpp
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
*/