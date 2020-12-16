/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/format.hpp
 * \author Andrey Semashev
 * \date   15.11.2012
 *
 * The header contains a generic log record formatter function.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_FORMAT_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_FORMAT_HPP_INCLUDED_

#include <string>
#include <boost/mpl/bool.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/format.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * \brief Template expressions terminal node with Boost.Format-like formatter
 */
template< typename CharT >
class format_terminal
{
public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Character type
    typedef CharT char_type;
    //! Boost.Format formatter type
    typedef boost::log::aux::basic_format< char_type > format_type;
    //! String type
    typedef std::basic_string< char_type > string_type;

    //! Terminal result type
    typedef typename format_type::pump result_type;

private:
    //! Formatter object
    mutable format_type m_format;

public:
    //! Initializing constructor
    explicit format_terminal(const char_type* format) : m_format(format) {}

    //! Invokation operator
    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        return m_format.make_pump(fusion::at_c< 1 >(phoenix::env(ctx).args()));
    }

    BOOST_DELETED_FUNCTION(format_terminal())
};

/*!
 * The function generates a terminal node in a template expression. The node will perform log record formatting
 * according to the provided format string.
 */
template< typename CharT >
BOOST_FORCEINLINE phoenix::actor< format_terminal< CharT > > format(const CharT* fmt)
{
    typedef format_terminal< CharT > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(fmt) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will perform log record formatting
 * according to the provided format string.
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_FORCEINLINE phoenix::actor< format_terminal< CharT > > format(std::basic_string< CharT, TraitsT, AllocatorT > const& fmt)
{
    typedef format_terminal< CharT > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(fmt.c_str()) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename CharT >
struct is_nullary< custom_terminal< boost::log::expressions::format_terminal< CharT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_FORMAT_HPP_INCLUDED_

/* format.hpp
CbQNTYf81q2m40u46w3vgMfCr2o7vROeATfCCfBuOAl+TdvrPbABfl3b68Pa/98P18MH4Qb4DXg3/Bb8Afw23A6/A/eqvwOwu1lnN3Nl+btA/z7J425/nO6c/vG5y43TXfc43ZW14G6Ex115nO4mx+lubpzuauN01xinu6YW3HXzuNvYijsnmXHCq+nO+lcTs1Pyn2aj5EjtkxyubZJRQ/1x2yfZekfaYdsoSdQ+ycSh/n+LjZJHX00/anZKxn909O2UzP2o3b/FVskO8qWZ872wYFe6MwqpRNYim5GdiPNautMPGY/UIuuRR5FdSPLvuIeMR6qRtcgmZCuyC/kIKf49v6mBzEAakU3IdmQfktvMPWQm0ohsQrYje5v/O+ym/Ov0/9k95RoAOEL9f1d3//xSx+ixMubiMH0v1L3GrCt5bPvJJh43JZjKC+5oMvbpLiC8C5GZyKw49x3/u23E2dcdE1+3TnTdMdY66Cv3+7ievGHw0O9Mf33BjgvvOOH3syq3J76ebV+HjrVenvg69H+ajTi7zbfEbcclut5sbMTp+msBkuYLn18V6vy4I0yBxTADlsAc2AXO8DsJjW/+V+2wHe44J94xzuGOb/7fbLAd7XHNv2NM08zfWa//d4wf2o62o+1oO9qOtqPt+O87/mXz/+rF846G/T/Xvt+LfJQrEPt+QYN8AVMJVQ2LllWqfb85Hvv/jWoHbxySofOeWnevb56sEYjnyuVLa+fMW7wsuL/u5YCuBjGPscc3L7RnbanoVSxb3mDbsxbh9pWA3QsUyQNuD6ID4Noq2MXVDT7WvYl3VvKArOw01cHUe89w79o8vu1lYElnAhYSktOzktNCe18rSoO2d6ZK/ox9gKup1vwx+jun5oX0uLIc72HXHXTzpFDyJLR/zk17oaada5KeV8SdpFH0r6blqf5np8B5jZ7/sZPqIGo53ZQcsr+YiaxG6imnpshyWlAbVxk1efK9uaDFMsJtbD2VjjA1n/vESsubYx7pC+nx3C/+L3J68GS3zNZQ53b6ceWWZ8kp/s4UWU5mVhJeW6wH0/CzCZF6kFOJB60Heu8FxK0H/lMy+6cmZ7XLyEwj5DR/ZD1wJagneqfq+21EEqkfz3vrRwwblK3VD/Jd64faGIioC758e13Yqx9WyrXNjkKWD+M839QF2a0eb3vFX4ttMI/8bcJhlxTuiB2QQQFdeL0+PiWi/aWlH1Hbm5TfatuLkbex21llfnjeXm7Ow22QDNUCvErb2UpkhdvOxL2xd+puN55XVReVv6ZN3JUf0+YMYUXqnS2sW7a81t728q06blZ9NHXr0VvEdEfD8nqvzthPxc0E1rJGGJ2xtALRwxV/edq+6yme4J7k/eRnrLrhtj3XJuTkdtr2hkjby8hwu+HsqD7YtLvbi0TQX0ys3W331I3cOGwtWNqd6p9JnkfopIVsFu2Xes81kxex69bvYtSlYrVPd7HWpaVI7xLeeQXhdUmNf0XWJaPHeKq4n40NtWT7+7Yg0i6Vhugp90pxczxDiwz7e7ig5T7AtVs3Aofl6WLri/dwWWZmZi9KOak4NTUru13IRon0p5Va3l3VX2261o98rR+Z2W4N8R9JPzG+wNNPJFgXwuxSmfyKXcazC+xlPE0fvFrLeBXSlzLeGl7G+gPJTswyflbcL3OG2suY8OLvM7YWxN9nGLcttO8u1OO5JO5OKb/ULH+H1DR/cmoyRW/KvEr1R0M2POpNOb0uz+hi+pvRhWI7T8o7GH5TptaPMz39R150/6HnxCWxfiOr8PDrSrz9Rqy606NQ607Ee3y7GgG6VevO55FLXb2lQlN35ONcvO9x/EWUu9iAs9YRr9s=
*/