/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sink_init_helpers.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SINK_INIT_HELPERS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SINK_INIT_HELPERS_HPP_INCLUDED_

#include <string>
#include <boost/mpl/bool.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/utility/string_view_fwd.hpp>
#include <boost/log/detail/config.hpp>
#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
#include <string_view>
#endif
#include <boost/log/core/core.hpp>
#include <boost/log/expressions/filter.hpp>
#include <boost/log/expressions/formatter.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/keywords/filter.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/detail/is_character_type.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// The function creates a filter functional object from the provided argument
template< typename CharT >
inline typename boost::enable_if_c<
    log::aux::is_character_type< CharT >::value,
    filter
>::type acquire_filter(const CharT* filter)
{
    return boost::log::parse_filter(filter);
}

template< typename CharT, typename TraitsT, typename AllocatorT >
inline filter acquire_filter(std::basic_string< CharT, TraitsT, AllocatorT > const& filter)
{
    return boost::log::parse_filter(filter);
}

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
template< typename CharT, typename TraitsT >
inline filter acquire_filter(std::basic_string_view< CharT, TraitsT > const& filter)
{
    const CharT* p = filter.data();
    return boost::log::parse_filter(p, p + filter.size());
}
#endif // !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

template< typename CharT, typename TraitsT >
inline filter acquire_filter(boost::basic_string_view< CharT, TraitsT > const& filter)
{
    const CharT* p = filter.data();
    return boost::log::parse_filter(p, p + filter.size());
}

template< typename FilterT >
inline typename boost::disable_if_c<
    boost::is_array< FilterT >::value,
    FilterT const&
>::type acquire_filter(FilterT const& filter)
{
    return filter;
}

// The function installs filter into the sink, if provided in the arguments pack
template< typename SinkT, typename ArgsT >
inline void setup_filter(SinkT&, ArgsT const&, mpl::true_)
{
}

template< typename SinkT, typename ArgsT >
inline void setup_filter(SinkT& s, ArgsT const& args, mpl::false_)
{
    s.set_filter(aux::acquire_filter(args[keywords::filter]));
}


// The function creates a formatter functional object from the provided argument
template< typename CharT >
inline typename boost::enable_if_c<
    log::aux::is_character_type< CharT >::value,
    basic_formatter< CharT >
>::type acquire_formatter(const CharT* formatter)
{
    return boost::log::parse_formatter(formatter);
}

template< typename CharT, typename TraitsT, typename AllocatorT >
inline basic_formatter< CharT > acquire_formatter(std::basic_string< CharT, TraitsT, AllocatorT > const& formatter)
{
    return boost::log::parse_formatter(formatter);
}

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
template< typename CharT, typename TraitsT >
inline basic_formatter< CharT > acquire_formatter(std::basic_string_view< CharT, TraitsT > const& formatter)
{
    const CharT* p = formatter.data();
    return boost::log::parse_formatter(p, p + formatter.size());
}
#endif // !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

template< typename CharT, typename TraitsT >
inline basic_formatter< CharT > acquire_formatter(boost::basic_string_view< CharT, TraitsT > const& formatter)
{
    const CharT* p = formatter.data();
    return boost::log::parse_formatter(p, p + formatter.size());
}

template< typename FormatterT >
inline typename boost::disable_if_c<
    boost::is_array< FormatterT >::value,
    FormatterT const&
>::type acquire_formatter(FormatterT const& formatter)
{
    return formatter;
}

// The function installs filter into the sink, if provided in the arguments pack
template< typename SinkT, typename ArgsT >
inline void setup_formatter(SinkT&, ArgsT const&, mpl::true_)
{
}

template< typename SinkT, typename ArgsT >
inline void setup_formatter(SinkT& s, ArgsT const& args, mpl::false_)
{
    s.set_formatter(aux::acquire_formatter(args[keywords::format]));
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SINK_INIT_HELPERS_HPP_INCLUDED_

/* sink_init_helpers.hpp
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
*/