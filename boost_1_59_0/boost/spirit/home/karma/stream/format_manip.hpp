//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_FORMAT_MANIP_MAY_01_2007_1211PM)
#define BOOST_SPIRIT_KARMA_FORMAT_MANIP_MAY_01_2007_1211PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/generate.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/stream/detail/format_manip.hpp>
#include <boost/spirit/home/support/unused.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma 
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    inline typename detail::format<Expr>::type 
    format(Expr const& expr)
    {
        return detail::format<Expr>::call(expr);
    }

    template <typename Expr, typename Attribute>
    inline detail::format_manip<Expr, mpl::false_, mpl::false_, unused_type, Attribute> 
    format(
        Expr const& expr
      , Attribute const& attr)
    {
        using karma::detail::format_manip;

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        return format_manip<Expr, mpl::false_, mpl::false_, unused_type, Attribute>(
            expr, unused, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Delimiter>
    inline typename detail::format_delimited<Expr, Delimiter>::type 
    format_delimited(
        Expr const& expr
      , Delimiter const& d
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit = 
            delimit_flag::dont_predelimit)
    {
        return detail::format_delimited<Expr, Delimiter>::call(expr, d, pre_delimit);
    }

    template <typename Expr, typename Delimiter, typename Attribute>
    inline detail::format_manip<Expr, mpl::false_, mpl::false_, Delimiter, Attribute> 
    format_delimited(
        Expr const& xpr
      , Delimiter const& d
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , Attribute const& attr)
    {
        using karma::detail::format_manip;

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);
        return format_manip<Expr, mpl::false_, mpl::false_, Delimiter, Attribute>(
            xpr, d, pre_delimit, attr);
    }

    template <typename Expr, typename Delimiter, typename Attribute>
    inline detail::format_manip<Expr, mpl::false_, mpl::false_, Delimiter, Attribute> 
    format_delimited(
        Expr const& xpr
      , Delimiter const& d
      , Attribute const& attr)
    {
        using karma::detail::format_manip;

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);
        return format_manip<Expr, mpl::false_, mpl::false_, Delimiter, Attribute>(
            xpr, d, delimit_flag::dont_predelimit, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template<typename Char, typename Traits, typename Derived> 
    inline std::basic_ostream<Char, Traits> & 
    operator<< (std::basic_ostream<Char, Traits> &os, generator<Derived> const& g)
    {
        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Derived>::type
        > properties;
        typedef karma::ostream_iterator<Char, Char, Traits> outiter_type;

        outiter_type target_sink(os);
        karma::detail::output_iterator<outiter_type, properties> sink(target_sink);

        if (!g.derived().generate(sink, unused, unused, unused))
        {
            os.setstate(std::ios_base::failbit);
        }
        return os;
    }
}}}

#endif 


/* format_manip.hpp
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
*/