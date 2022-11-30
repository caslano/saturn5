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
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
*/