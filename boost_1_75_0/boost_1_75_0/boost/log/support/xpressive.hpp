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
CnO9qjWnqxoEcPbzN1bctDC37whqrAlCAPup2+8wMZ9C+jnD60JCQowRXWJCPu5fyXDeikOSoURpnbI54j+HvoL1hNfIadu2lV1YvRJxmytaWsq81OwVFVm+Y1FcdRxJg7SsVSUSlAnWTR4FdGIlvjh4n9JWbvi6W8B+F4X3v2A6JyCwmEnxcVue48ES7pEFiDmAxQdTd9d2o2P2Vs486uLODGB9gQqn+uxu+03pUo8IGmiHLYuJ42dP2rZbWqFtbmsUv3OVDqY0szwPi0lhor/FzUWu3vC4mUEWuFta3H5sJHSzJefxDPJ4L3p7q0ynVdWBXUOw0vm2tgaXdc2NzakTDf1YVNdp5o0zVeuaS0nbYzg+OuzmW6e55vWfRpp4cXj6gacXFmQ/MYp2L4ozCHQT703V1RlQBvdE7TwajjOuWqSqG3yf+5ZTHSapoodEqNWC/p5Zp9Urb4gOlYtF9fUu0Phz2vOvZnjV/Q7vsFufvI0vDVLVsRJnt2QZ5Z8d/Li26H7uLLzJLl8URagZd6NSIapnrvqJqTtuudxpmLs45yUXRNyi7mu19k/e8D2bmoIFc1fKFSe9T9UbPtlH2kwr+tXNbP7iejMAyd6QPoXWP8kEa9haudWhmoOrizimFI/MMXQUwZXXvoXORsJTd3oD+it4c3yVbLYn9HpOUW12TGAZ+a7PwVLaIs/c2us0p+Zc8xbef84/7nj9
*/