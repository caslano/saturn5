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
2Lx1gzpmzH9QDPJntQY2Qyj7QwalWcK5amzLNvGTnbHBm8tL0figxtcQY70ICB/eKpadbQX7xAJOIG9NQnbdGXWunMEQUtYrhHzA3U/Aa606pZGWC5VeWHhPO14ECcShewVNs9+WOu7JdAKMiNYR5hQ1taAakLjV99ArYUboYxe2oDeSjJ+AF9I4KH3BsW9iD9RtoWkWor3+g5wlzWDjkvpz5Hm6cBPW8MN4lVUO0cDINIFe8jDncyWoI1HdK7/VS9m98EM3qNkseBTEfj/54UOTlYtDQAgyJz805QiLAvIHDuRESFU5nhwN5dCPEyuhkXI1EVUK6WsEu0myxOtOoiWWN8j2tAWyrRCKKVwsPFQLF72zEq/y1BYybHy0jBE4l7KJr1poXyfqbcJG2ruKG8dsEPjzUyHwSjGZUn9+aku9ev/2SBei9l24uRUkXkFG41ydw/+/b7LWX9mtKN7vEh8YaOQKyfXyzVwLX07j+5oAamrK6Nkl4VYdHQ6JS/VOgygVfO3kf6pVgqO26uQ/7pO+Si1f6ZYep5fT1g562ey6NioHwB+jnr+IO/taPX21P3ucsp6fblRWRW3IVCIWXXALIAKMKN80YiIw7nWHvjdx57T7c9xgLli7/uXkRBdtALKN239I5e64qG7D
*/