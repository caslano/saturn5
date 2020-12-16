/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/std_regex.hpp
 * \author Andrey Semashev
 * \date   19.03.2014
 *
 * This header enables \c std::regex support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_STD_REGEX_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_STD_REGEX_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_NO_CXX11_HDR_REGEX)

#if defined(__GNUC__)
#pragma message "Boost.Log: This header requires support for std::regex in the standard library."
#elif defined(_MSC_VER)
#pragma message("Boost.Log: This header requires support for std::regex in the standard library.")
#endif

#else // defined(BOOST_NO_CXX11_HDR_REGEX)

#include <regex>
#include <string>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as \c std::regex
struct std_regex_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename CharT, typename ReTraitsT >
struct matching_expression_kind< std::basic_regex< CharT, ReTraitsT > >
{
    typedef std_regex_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, std_regex_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT, typename CharT, typename ReTraitsT >
    static bool matches(StringT const& str, std::basic_regex< CharT, ReTraitsT > const& expr, std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
    {
        return std::regex_match(str.begin(), str.end(), expr, flags);
    }

    template< typename CharT, typename StringTraitsT, typename AllocatorT, typename ReTraitsT >
    static bool matches(std::basic_string< CharT, StringTraitsT, AllocatorT > const& str, std::basic_regex< CharT, ReTraitsT > const& expr, std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
    {
        const CharT* p = str.c_str();
        return std::regex_match(p, p + str.size(), expr, flags);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // defined(BOOST_NO_CXX11_HDR_REGEX)

#endif // BOOST_LOG_SUPPORT_STD_REGEX_HPP_INCLUDED_

/* std_regex.hpp
Xgk3pjRerZE9YOJl5CZe2cjuMfFaua+8eI1OCq13omxgf4eJ18rPI+PVQOOV2cHk56MxgWgJNCjbids0ZMSpjOxtZO2RzQ+XSbgHkLXuYMJ9qbz02KvhkmZLYgLVpagEfQnKuyLbo2FHyoPhT0C2G6XlaAMSaxlH7ByUNGkpcVuKm10ozautkXHTO55C6zLk/aC55f3AvjYyz5xLQfuDXudu9T0gJYCZ6ft4FzD26NfMee5qZvoiXTOh/f8KvSBmCKoGajBqajf8rl9e/z92pPb+nu+gPNMntBF3fWx9Pn4euc/vJPLOtj4ft9Y+3/adhl1rP2/ts7Fr77Pt62SxX6Y/Nm1fb5G1i+zXTF+cKfKGqqdEid5XgfvZKBPw1H9zmeiiZeLKdEd+ofGmJNRjLWgrD5cJWTczjQnB4NqZ3JkLvXXElu+4i5wPzLPlsbEn/Q3lcmx6qH2qWm5/s7p+aX9TFfs5qMN1sbbpbyR9rb+UISZ9I+YJqqre3JWjafN6Rtm0mUl9ud6eNrlcnmPKij19cBtRpuzpo/Y0fa7hOddlaHtWUx5XzFtjdkHG0dNtkyfd+mB/LcqbbseadsXetDP6vLB75a6Uty+pR/KrjXqccrXTlnZMxC2fWVSAFWv8d4mbKFt6qn+uPNubPNeMzqFni3WO5Zm0PITlf1rmYZvV1UU1fYZ9tmdYsCgP8VHrxz6N7z8Tr2/5e8IR7uWIewjlPrp46ae3XDRhQOqXJUP/fsHousd+7s3411zM29R/aXf7q2/6qOmahi9/NurLKr/evRz284Uq7+v4T9/XETyfR4u81CFZC4aar3+fhZqnf1+E4v1L/r4KpXcp6P4o2RtW5i6FtnqHRkfYEqbBHjAd9oITYX+YCUfC4+BU2AXOgd3gYtgdroEneO5CuAFmwbtgX/gI7A8fgwPgi3AwfBMOgX+Bw+ABOBxWdZHDWDgKtoBjYQc4DnaGE2AvOFHvUpgd2kuje4+malsRWjM0We82uRgmwEvh8fAy2A1eDkfDm+EYuAHOU/18eI08J3oNb6tP9yzofpepcHTQnk/XlLn4D7vAYbArXAK7wctgH3g9zIIPwL7wcdgfvgwHwNfgILgPDob74VD4DRwOf1B9dVf0kl45sC4cBRvC0bAVHAO7wrFwNDwJToInwzw4BZbAqXAtnAGvhXPgJjgTPgxPgU/BuXAvnAffhfPhx3AB/BwWwCjSogiOgYvgeFgMF8HF8DS4BK6DS+FO1b8M18DP4DlwP1wLfX7mbWEAXgDbwAvhc6p/RfS4g5fB7+Hl8ABcL0OR1A/YFm6E7eHVMAteCwfD6+EIeAPMgbfAE+GtcDy8DU5X89lwG5wPb4fL4R1wBbwTXqL2b4T3wc3wAbgFPgh3wIfgs6rfAx+H78Nn4JfwKfgDfBpGR+ldNfB1eBx8E/aEf4QD4J/gUPg2HA3fgZRXEi+0PpiwtLwORxVreT3Zx9AfzIfdYAEcBQvhGJgd4C4fuAj9XFgCl8PF8HS4FJ4Pl8ONcAX8HTwdXqfu71bzJ1X/B7gK/bvwHPgJXAu/hOfBQ/ACmOiSvnAkfBoug8/DC+FeeCt8He6Eb8On4TvwVfgu/Aj+Gf4V7oOH4Hswmmf/CLaHf4Gd4SdwFPwU/kn176n+e/gZPAg/hz/CL2GSn3VRMBN+D0+EfXi+k2AWnAH7wnmwHyyG/eE5cCC8GA6CV8BseAv82ke5gN/C9+F3frKQcvB32Aw62GsNXTgI+uEMGA0LYVV4KawOb1fze2AcvBfGw10wAb4Pa0OXctEQxsFGMAE2gXVgCkyDzWA2bA0nwg5whbpbqfqzYVt4IewJt8NekHJI/67r5nTd41Q=
*/