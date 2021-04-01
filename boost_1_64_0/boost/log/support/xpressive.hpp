/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/xpressive.hpp
 * \author Andrey Semashev
 * \date   18.07.2009
 *
 * This header enables Boost.Xpressive support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_XPRESSIVE_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_XPRESSIVE_HPP_INCLUDED_

#include <string>
#include <boost/xpressive/basic_regex.hpp>
#include <boost/xpressive/regex_constants.hpp>
#include <boost/xpressive/regex_algorithms.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Xpressive expression
struct boost_xpressive_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename T >
struct matching_expression_kind< xpressive::basic_regex< T > >
{
    typedef boost_xpressive_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_xpressive_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT, typename T >
    static bool matches(StringT const& str, xpressive::basic_regex< T > const& expr, xpressive::regex_constants::match_flag_type flags = xpressive::regex_constants::match_default)
    {
        return xpressive::regex_match(str, expr, flags);
    }

    template< typename CharT, typename TraitsT, typename AllocatorT >
    static bool matches(std::basic_string< CharT, TraitsT, AllocatorT > const& str, xpressive::basic_regex< const CharT* > const& expr, xpressive::regex_constants::match_flag_type flags = xpressive::regex_constants::match_default)
    {
        const CharT* p = str.c_str();
        return xpressive::regex_match(p, p + str.size(), expr, flags);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_XPRESSIVE_HPP_INCLUDED_

/* xpressive.hpp
rayVVAmAYBjV9xdtZET3cvJnkyP8lLGIyJZ057UV7JdEx1NlLqMz4g2TwWTUOQAHYZFGKa6yBpUt806WQUtNL0gLaMN842jL3oHQICGOCew/XHtMHkiFrxQeX1FE1T9oUXf5/SZY04nMA+juJrF2HtTYjKO+HTq6bXa1GNPk3k03Alwx4m0O+rCZ15cH5b7D7432Sfn5z1VBWJO5gKRcWhiOZiCBGZG9F6qgdfXLSiAtMnBCN/AX+39f+bmPOY6+Ux/6dGRt1K0HXT4JxLm+TuB15OL6OYBBIpMnm5Dcno2VWIapzr5x5515PZ1MgrDmTDmUqctwM8NQBIh8quQe8RwlUqkmfCCgvni6aYIRaT0io//69qm2IQwWGoK25baHALPApDwLn2EZq9nDDHFtbCRUHPu/z7ZghUcmnXMjrauW5O0kBM0wTjIWWPQfz8UjPhyZUtOEApmCwPQHw+a3P8KXsndO8y07NqF99QWecHC/vjTs/rA5fTBbioVU+4Ylzy7ulwdaiiV4VL2AHbf8ttrWpHwJBgM2twutM4pLEWtrWM6UN/ADUBtNVA==
*/