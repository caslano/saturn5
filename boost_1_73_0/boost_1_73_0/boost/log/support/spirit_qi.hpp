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
txId77dmAuHoVwt71lp+RzHAm2Td6VKVcHHMqSZq8/OWzbneGihdYzRajdjvzflmXYdooxPOHJyN+OChvYRGbuqDfhjiQXoxH1ndS6VL3sAQYxs9kCaosNJziYmbhbbWD/yaW2ct7pcWuVIAxZ6j6qslji5oKisQjsfO/wBQSwMECgAAAAgALWdKUh5XX8EzAgAAzAQAAB8ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9wYXJzZWNmZy5oVVQFAAG2SCRgrVRbb9owFH7Pr/gELy3KSNendaumIXpDq6ACqgqpkmWSk8aTY0e201KpP37Hga6atJWXGsEx1nc7x4S+Kk1BJa7OR2fnczG+nV+L5Wx2LW5G88X5+OJSXCV9BihD72KywcetBAPsXaJ7C15cO8aNs78oD/9GC/GC7YtZ91z3mWR4o7yIQ+ynvOCgo4idy2ncC7HP6D5mix9ZZN6LuOUTpkXm2DbPTj1UAQfjQ3w+OfmCTzg+Oj5KcSaNIo1FILMm95DitOhOflRysxl6+p6CAqQe7qSWlfLwtgxP0hF4r1VOxlMB6VGQz51a8xdlECpCqTRhPLtZTaaXKZ4qlVdR5Nm28JVtdYFKPhIc5aQetxqNdAG2ZDqLF8oHFmyDsmbI3oRArvZRI9pL
*/