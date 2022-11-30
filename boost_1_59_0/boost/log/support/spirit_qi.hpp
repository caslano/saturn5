/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/spirit_qi.hpp
 * \author Andrey Semashev
 * \date   19.07.2009
 *
 * This header enables Boost.Spirit.Qi support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_SPIRIT_QI_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_SPIRIT_QI_HPP_INCLUDED_

#include <boost/core/enable_if.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_domain.hpp>
#include <boost/spirit/include/support_unused.hpp>
#include <boost/spirit/home/support/meta_compiler.hpp> // spirit::compile()
#include <boost/spirit/home/qi/nonterminal/nonterminal_fwd.hpp> // rule forward declaration
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Spirit.Qi expression
struct boost_spirit_qi_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename ExpressionT >
struct matching_expression_kind< ExpressionT, typename boost::enable_if_c< spirit::traits::matches< spirit::qi::domain, ExpressionT >::value >::type >
{
    typedef boost_spirit_qi_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_spirit_qi_expression_tag >
{
    typedef typename spirit::result_of::compile< spirit::qi::domain, ExpressionT, spirit::unused_type >::type compiled_type;

    static compiled_type compile(ExpressionT const& expr)
    {
        return spirit::compile< spirit::qi::domain >(expr);
    }

    template< typename StringT >
    static bool matches(StringT const& str, ExpressionT const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        const_iterator it = str.begin(), end = str.end();
        return (spirit::qi::parse(it, end, expr) && it == end);
    }
};

//! The matching function implementation
template< typename IteratorT, typename T1, typename T2, typename T3, typename T4 >
struct match_traits< spirit::qi::rule< IteratorT, T1, T2, T3, T4 >, boost_spirit_qi_expression_tag >
{
    typedef spirit::qi::rule< IteratorT, T1, T2, T3, T4 > compiled_type;
    static compiled_type compile(compiled_type const& expr) { return expr; }

    template< typename StringT >
    static bool matches(StringT const& str, compiled_type const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        const_iterator it = str.begin(), end = str.end();
        return (spirit::qi::parse(it, end, expr) && it == end);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_SPIRIT_QI_HPP_INCLUDED_

/* spirit_qi.hpp
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
*/