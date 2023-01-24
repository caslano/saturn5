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
eIvl/e8WCr0w687g3e0pGpePtEz8pvZgI750+ZIl3DGl+vbk+w/6T4Nk8CZ3Sx/uv/3J804cqsoj/eZiJ+imD/FdxR/kkSv3Fyt3IQ9fWliQ+QB0p3ZDts33Pgbf6IU98GPJ3Fi36+c7eAk+BxX9GPk+hfWx1/WX2Hm3sqvO3F9DGx/lVlQb/ml/7m4+zL5b/8Nembq1n+orfWi34ectn/T5IN/zb6Huv/ZXhSIFB11HDmdHv1OpnkbDMZ/NKZOBje31N3CG+3RllAsCvGM+0YO17I3Fu1x3Gxm8ZX7zMPYShnKBa3IZ3Lu61o94n9wUuIqQwZvmY4cQtmbdLtfVcAbvmo/l4Y/lf/2ne3TxDN467zzE9mwtUdcf8eZ5Zxp3FH7jv8aJQbx/fqEPZ0+/9ssRVwEzsKkuvIXw9Z/bFXbBncF76MMHIVt63o65BpHB2+inc6D5rcdjrtFk8E56C+RPS/+xCPGYwbvTV/bCTmfhFDU5wv12hp3XNPpty++XikdF7YjsKN4pyeWhZ5T87xKPxyXwo0cxn/a8p3zmmXdJzrNMGP+NwkDBt3kCff3boN/cjjMIm378AL8H8QcWubrTfABnAU/9YGHTngHEHzzMZ7tfsBy08YyIsJ4Cxskrr205ROXlyUTNlQhL4+zBm/5+vnMNr1hyl33kHcwzqx8vHNBYRT/SC/onHkE+bfr6PsiA//HTmhy0kzyv
*/