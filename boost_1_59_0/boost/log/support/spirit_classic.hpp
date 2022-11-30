/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/spirit_classic.hpp
 * \author Andrey Semashev
 * \date   19.07.2009
 *
 * This header enables Boost.Spirit (classic) support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_SPIRIT_CLASSIC_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_SPIRIT_CLASSIC_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_LOG_NO_THREADS) && !defined(BOOST_SPIRIT_THREADSAFE) && !defined(BOOST_LOG_DOXYGEN_PASS)
/*
 * As Boost.Log filters may be called in multiple threads concurrently,
 * this may lead to using Boost.Spirit parsers in a multithreaded context.
 * In order to protect parsers properly, BOOST_SPIRIT_THREADSAFE macro should
 * be defined.
 *
 * If we got here, it means that the user did not define that macro and we
 * have to define it ourselves. However, it may also lead to ODR violations
 * or even total ignorance of this macro, if the user has included Boost.Spirit
 * headers before including this header, or uses Boost.Spirit without the macro
 * in other translation units. The only reliable way to settle this problem is to
 * define the macro for the whole project (i.e. all translation units).
 */
#if defined(__GNUC__)
#pragma message "Boost.Log: Boost.Spirit requires BOOST_SPIRIT_THREADSAFE macro to be defined if parsers are used in a multithreaded context. It is strongly recommended to define this macro project-wide."
#elif defined(_MSC_VER)
#pragma message("Boost.Log: Boost.Spirit requires BOOST_SPIRIT_THREADSAFE macro to be defined if parsers are used in a multithreaded context. It is strongly recommended to define this macro project-wide.")
#endif
#define BOOST_SPIRIT_THREADSAFE 1
#endif // !defined(BOOST_LOG_NO_THREADS) && !defined(BOOST_SPIRIT_THREADSAFE)

#include <boost/spirit/include/classic_parser.hpp>

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Spirit.Classic expression
struct boost_spirit_classic_expression_tag;

//! The trait verifies if the type can be converted to a Boost.Spirit (classic) parser
template< typename T >
struct is_spirit_classic_parser
{
private:
    typedef char yes_type;
    struct no_type { char dummy[2]; };

    template< typename U >
    static yes_type check_spirit_classic_parser(spirit::classic::parser< U > const&);
    static no_type check_spirit_classic_parser(...);
    static T& get_T();

public:
    enum { value = sizeof(check_spirit_classic_parser(get_T())) == sizeof(yes_type) };
    typedef mpl::bool_< value > type;
};

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename ExpressionT >
struct matching_expression_kind< ExpressionT, typename boost::enable_if_c< is_spirit_classic_parser< ExpressionT >::value >::type >
{
    typedef boost_spirit_classic_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_spirit_classic_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT >
    static bool matches(StringT const& str, ExpressionT const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        spirit::classic::parse_info< const_iterator > info =
            spirit::classic::parse(str.begin(), str.end(), expr);
        return info.full;
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_SPIRIT_CLASSIC_HPP_INCLUDED_

/* spirit_classic.hpp
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
*/