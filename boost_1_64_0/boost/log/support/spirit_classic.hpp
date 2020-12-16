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
uzybva/V+hPvl/VN3j7UuNd1s+Xel/m02Mug92lo7p0fJ2aXRUX0J+b+5eYS3tOBZuwi3eJ7wl0f8Gs6sBpQZD/5azrMT6Jao9pzm0KCfjs1FPlL9DHV5ZlYEsSvsGDJzKK8klmla+z+fDgMTlfw82TtWA8wmzVVehZElK6N1fMMJkt8L4iy9VkLJL8eM+/sV0XLmmx3KOGvcDqZ++YGiZ+3YG+Fts2ckCBmI3x+bvsocEcTm2WR/YI5+2qLT/yNSiYlsllP+a5vrHnvOFv8GeBxW1zgPaNho7hNcGs472h8aF/k+Xu5c5znTd86KyBpovpQnP3m/IjrxZ/BUaXtYH7Jgpxg0i4y/p4r/vZ30vSMip24u0zMxgUSxZ03P4bNZA+pSbtrxV661PfGjs+ccTFJwr04qpY5n2nagtA6+63ILX2iKbvFVXBL7euiZWuMhDGX8lGTfK8u4bSgv+zmpjpr3U6cl1/Xae+b5Nzgb+h86V+u/vBEVUrXzdYxefcUb9UPu6EzSi4QvycHQvGsqmdlJHr6wE6SxlMJfbj0jbXVfJqYx2B3gKxv/BD/eovZrf5Bzmp51j2YldcHJcC/SNnrjd/J5j3yWzG7ktrXmWcxcddnYY0hfh7Wz+WpO7uJZerMwKKZhNJL82ik7/B62K60OKtRW1BD3GZOPi1Rku9p54CvB3etJDpPcaHLkMAK56tAiZMfFUeMvGVqDWV+t/MSYxZbKPc/U+71TK0j9ZWmf9wYZ/o++kqofd2dmF+j53ykqbxNqij6xDBKX9lW9d6/6TelvzzZ+m3rnpXg6S8THZ/0l9Q/zxhHDXMGk+pN3zgNojd9Y6Hq66h+gerrQdptabUT0DfSflJbZrGzVc/coiaIfo/qKXFh5z5tq+/I79LgHf7KKfStU6sFLN/JuUsKimZE9pP2b+Fq3jsXtZ/U84W+F9lPPnZqmrObvhaz051oXPfl/4moYpT1+xm7kd/PzbQdLBBZvNsdf+ajHqIWv0X9PWgb87P6tcD0qXeJbB99SJRzFmoj6l6U9Vu42lHOFKyOnNti+vmird+06v6I/exd4kes/ZvVhG/vZ9uI2+bU/TpmTPJMcVPoD9ufofZXiv2FqucrJ0a/o8K/RSUea6sfbh/a+qp45MUmHS8V+VRfPmdXfcr70VVufe4zaKP9uUvBC8rv4StyGYvObuN+hGmmT1kvbk/2aTnit8Q801cic33X4VdkPMvb33C1yKPNuVHLqx1eU23Zb2H6x2clft2dGqRfM21Lv5SwHV8HzE7mDeNmWrp5xPsVN6X0TDgJK9aMCVwr/nxAHjxr3h2+E39+dst87+n7Sk2Rb/O9xZ6OsHX2Kv9E5NV9CSZ98mcupZ46nr0HPgm3rzuOklzLbXLEdNd2Vsd9be3t0b9PQt8kJSjaWW1DI81VH/4t4pVJO1vvKOPH62Iq9i1S4vz63yLe8cb5ejjTRtrPrnAVDI4176sZ2Y4WzZxeGDEHouNlLWvJXht/fZ9rxmKqiFlXX+i9ok8cevYxTWDcBnc8r4ZByLm487bBmEeOR5oxg7bib47/FzfJ7Ok7JPb7iJ2q5fir5pHtrxm36ij+DvPHe57hSonzCeY9sonYuVHcxJQTTow1nAWmnU8SPza4xdg8jzZ5DG9aM1ElKPwlT+3+qrm9rcZdJs+QIX5n+2viLtR+x4rZEl+aL8qc49Y7XvJC3NUpJzw1P2LbfL743ZAnqW7asSlBvzFJ0LGW7mKnjz9K0tWcCT3N+y4biNXxP21/4kUfkHGn1sGxZfHjKd9aN4rT9u70jrGZuPxR3LTh7NPdJr/Ok/wbY86crS/6UW6A01Cqu829Y2umT3hV/Jk=
*/