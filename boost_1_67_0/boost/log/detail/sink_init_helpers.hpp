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