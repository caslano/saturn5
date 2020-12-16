/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/regex.hpp
 * \author Andrey Semashev
 * \date   18.07.2009
 *
 * This header enables Boost.Regex support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_REGEX_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_REGEX_HPP_INCLUDED_

#include <string>
#include <boost/regex.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Regex expression
struct boost_regex_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename CharT, typename TraitsT >
struct matching_expression_kind< boost::basic_regex< CharT, TraitsT > >
{
    typedef boost_regex_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_regex_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT, typename CharT, typename TraitsT >
    static bool matches(StringT const& str, boost::basic_regex< CharT, TraitsT > const& expr, boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default)
    {
        return boost::regex_match(str.begin(), str.end(), expr, flags);
    }

    template< typename CharT, typename StringTraitsT, typename AllocatorT, typename ReTraitsT >
    static bool matches(
        std::basic_string< CharT, StringTraitsT, AllocatorT > const& str,
        boost::basic_regex< CharT, ReTraitsT > const& expr,
        boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default)
    {
        const CharT* p = str.c_str();
        return boost::regex_match(p, p + str.size(), expr, flags);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_REGEX_HPP_INCLUDED_

/* regex.hpp
uADOgwXwTLgQng+L4BZYAu+Ei+FOuATuV/1BuAZ2o/yshYXwXFgMz4OXwYvg1fBiuA1eBh+Al8O98Ar4AbwSOpS3jTAOXg3j4ZWwJbwOtoXXw55wLewPN8Nx8GY4B94CV8Lb4Dq4DV6i5tfCHVDGz+HL8B74CrwXvgcfgJ/Ch2C1aOo2rAEfhXXhWtgS7oQj4C44ET4N8+AzcB7cDYvgc3BT5Xj8bzoe3/yS6sc8Jp9yW+UYfOWv8lf5q/xV/ip/lb/KX+Wv8lf5+//+/Vbz/7/W/v+Wnv3/fXStKGsBnRqQNYKy/z/uoF/n/wk4fP+/GSOfLnZeIPTt1nl+/KjQ/uCy9grN3EgTkT3FuHrANl+vbu17whLhBJF/a52/97otdsrumWor8tZu2JyZxut9kZ2kema1fwjq4yPnocy+o/vE/jXefcRF3rsUF4vcb9YBrBD9y2bOZZnKPXfLm3nZNSJ71unLfECs7stZGT4PYO5lHqd/70F+vo7hf5cYfuaAbiMv98wBnvWY77k42h0mGVoeGZeS3zkoF7VG7/LdQZhh61EqcCYFbiLLnylXe0Q2nLFKv6VM2twWmnmgZ0U2hnpouc/E6naBmf+8V2SrCNl1ZqFs5RL3Fb4HGLu2Mmzm0X8SeQ+ZxUrBNHSXM+VAykkrVGPaktapFdmremx5HX537wKdbyn/nInMmo785hHB7nA0PBu7U3+MyHudcLGtRRpGXdss9ltGherWGaLvYCsj+F2xNqqsvUIJbyzh3S+yOia8baJvjlzLyyH0PKWlrFj8XSD+5uDvwyKLi2qpZecG0b/uf53TGD5GfY9K9C11vvE1dEb7u5j5ziucAP+3sJUtDc++hqc/YT4u8piotlpPNoi+YdQ9rH/ZS0p860thD20mZxHX5TzMJc73gYBpA++ScKtZyynhHnHdzQzCfkrsVDXpeN9P/rD1K5+IPmBdm6T+l3sn43KJW21T/4eKX815qppilmDSLRETf+QzSRxnE8cXJBwnyrs+JgFZH2Qrxc+hgfvdKd41LabdOEfk7QJ9NK/qGP9riP9L8eMCsdM7UKt0vco0x1OfvxD5CcSxmsQ+VMYukngdLONvMv72xN+7RV4v6hmX8WDUJ6if3Y9sa0okvdaI/drm7qCrRJ/KkrFLmLmuKs+cjb87JT41Aj7Ciuwnawf/+iUo/8yk+4NSF95kDmSy6eve/1na4sjyG37njz7/W2K3rpOs8cwQ/zu4LTA5ibeaQ0591s9EmX46/ZDYN2tIosTvdcwt9TRrLfaLnz0oV+mRcZC1Fl15zgESzhrfUvcOzqs+/PwTMP9Y3H7ke9A5r9w1KHPEzvOsd6EPUf86SbpdE0j05ZRZhyBz0/p814nbesStilnrUCJmCzCLQVKd+boG5q7RThJPf5nnaKDlYJm4He2XtQfYak4ee/YOF08rKpayOBW7WeLXeeHrSiRu/Xiuw7+Hxb+aZl2JZw3DzPwZpeX2fsmHiaxIqkFLGDBpHyfxy4AxTi1NmxKxO867Nkci5t2D31ni1oq1WE18ob71sLt67hhm0D5wfGZt0c9i/ijxX+fU0rp6vLi/vMyaklAYifBecbfPOZMZxIvoN5vpu9WuZOk/zbqL8fo+pWsvyl13cQBlX1dh7gfU9RVm/cQR11Hsdiq+joJyUO46iqPvO65YX56IWT3buojINRARdxLPwCN+nKjAu0iQ2u+n+WRNWES/nzu9IH9RMV825FXEO0B4367uXdOfR7wHSlyHRAWklhznTPL09+FuY8LcFhp7MRH2SJ/wdz6tw90Ccg6OM5M2exOz1snaZg8Vt2/5WP0rrcd21B85jdz01xH+46ZMv2362Ag=
*/