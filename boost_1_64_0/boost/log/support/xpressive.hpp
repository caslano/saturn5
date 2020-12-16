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
2B9FHshvGPZqwBmwI5wFB8JT4GD4FhwBF8BcmA+XwAL4D/bOA76q6gzg970MQhI0CRACIoQNAhrCMCAiUxQVAgiC1YaRMJQRk1BxA4qKRcVRiwiKsziwqFhBBVHBgYhhWJBVVLSKo0i1orW2//f5vcN9N+fdJC1a29+7evjnnO/sed9Z9zKVXwUvgtfCErgYlsGlcBp8Al4MV8NL4EZ4GdwEr4B/VH92qPlnqv8CXgW/gjNgkETMgoxXIk+Fs2E9eC08Fl4HW8DrYRc4Bw6Ec+FweCM8D94MJ8Nb4NXwLrgYLoL3wbvh7+FiuAveB9+D98N98AF4DHn4O5gNH4ZN4SOwJXwU9oDL4BD4BDwHPgnHwqfgeLgc3g7/ABfAZ+BCuAK+AZ+Db8FVcBO8C+6DL8HP4FqYQblugq3hVpgD/whPgttgX7gdDoA74DC4E46Er8Er4ZtwFtwI58FyrT+kTff20Idr/emFqqP15xGK5hT4JBwHl8Mr4dNwNlwBb4Ur4R3wOXg/XAWXwRfhM/AF+KLqX4Fr4Qa4Dm6Gr8B34avwEFwPE4jUGzAFvgmz4VuwOSyH7eFmeALcAk+F2+D58B14AdwBp8Fd8FL4J7ge7oUb4btwP3wffgn3QSfUj8FOMKTvCv8Ce8ODsBD+DV4Mv4aXwEPwVvgtXAC/g/fAf8B7IWmZ8RBMhEtgDbhczdfAJLgWJsPNMAVuhbXgx2r/W5gB/wHrwH/CujCBcsuEx8KQvik8Bp4CG8MBsAkcCZvCAtgCjoetYDFsDS+Fx8ErVT8TtoVyp2YgvPbOu5PWk64oxk0e5PGEB/8ML4Afw1lwP5wDP4N3wM/hAngA/g4ehMvhl/AZ+De4WvVvqL4cfqP9yLdwF/w7/AR+p/3GP2F9GEigfcIg7ADjYRdYA14Nk+BsWBMuginwdzAV/gHWgh+q/jNYD34BG8BQW2kEO8PG8ESYDc+ETeHZsDkcCVvAX8D2cBQ8Ho6BJ8Apal4Kc+DFMBfOhh3hdbAzXKj2l8JucBnsDp+EJ8M1sAfcpvpdsA/8BvaHiXGUFcyAA2AWPAtmw0GwDRwMc+AQKO81AV2r07XUUbA9qkzLOY3xU+YpYSY8FnaGp8NuMBueApvAfNgUDoHN4SjYAl4D2+j7TFt4HzwBroA5cBXMha+q/g3Vl8OOcLPqt6p+m+r3qv4z2An+RfVfqP5L1X8NO8NvVU9iRU5bE/N6qm+g+iaqb6H6VvBE2B/mwdNhN3iO6ovhSfARNX9c9btgb3gIngqdUDnBVHgarAvJRymHfDNHK7/ppBxqoBjb5fmedil/YD8BxMFjYSLMhTVgH5gMT4cp6m8Oaob6m6UqDhWey78RcYg3wXrwZhh2t9jH3Xx1d6e6W+Byt0bd1bG4m6Xuroa14TUud3vVXbLFXZG6GwdrwvFwe+DndSfqmhuSY/eiWu5Fnce9qEtQa1H7UKmPJTs5qHxUMWoxagPqU1Ta0mSn09LYPaqxJ/bEntgTe2LPz/35ae7/Kyk5Evf/NXBS08d15R01NfR+yREBdsYVjJs2ZSwbqBshuy2D38JHuWQlxIjFUYKVuwM7NHPM+YNR+hspV/OhA+qBOsxVHJL7uvoNGVIwaerowoIffCIackby3PQ47NXEh5lpomzrp+59FGa9NCkQbV0x+nrgqUxss/42fWxZv+z71n33zZLtlwzqMyL6+qd9/TDa+t6RW6+r7rpr+Dv3ktdaBjme79yP0d8MRTADjoPH6m+HdvAC2AFeCOfCT5/l3fa5ZPm9EP6tMEN/F7h/B3yEmqvv+HX0vd79/h6v7+fXeN7J9b3bvHMXouZ7vv07AtX6udj7b+yJPbEn9sQ=
*/