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
+KiA9RuHSFpuY+e4QpczXPhTxcK75J7zhA3/wLbg8I9qf7jwLbYHh2+Lv6T0PygW/gD+ktK/9ZXg8BNfKTl8yo7g8Bk7Sg6/plj4zb8RvvtO73mXCd9rZ8nXe3xncPo/7yw5/QWvBoe//9WS089+LTj8+fhLSv+tYuH3/Eb4UbuCw0/aVXL4Kq+LvdmEL6v94cI/Vyz8C+KPLdpDthTrk44PsHklB+3/z29kgB2MvJHp3z4tTwqWZxW3Sz0vdqaBUz0x6wZXq/j+5oubznl2xpWnb2dytieFsz+dvj3sGGV9yPL99sp7iBxZuHv09wNVAtYhTYB5sAxsBhO1vC6sB5vA+vBC2ABeBhvCfrARHA4bwxthJpwBs+B9MBsuhTnwWZirvyNoAt+ETeFHOv9vdf6VZM0CwsN6sItdlP9R2ADOdRXl39hdlP8bsDEcHlWUf4KnKP8VMBsWRBfl/yXMhbyfSf51Y4vy3w7z4HVxRfmnUV/NYVXYAmbA8+G5sBWsD1vDRrANbAPbwm6wHbwGXggnwfZwFuwA74MXwyUwX++jn7QsttQ2uAbLIja4yBE5Isf//nHW9H/R/n/f9/+V+Jb0BD9Ecyd537wHjhzRb+yAYeOUyPs24Rl/Q5F8Qr/sgRRK7AWrA+wFe/RvciXfmBGuNz9URzab+QKB3wnIi4ql98Z3sA/oeFZAWCmPoz1AhzXjj0/r8cfg1nB+1yLt4D36fTKdXzLXXxt/3yvQM7zhhsj7lL5u5HqexA027+XwKnilt762mOsuaiOH6/bZSaZJ2M5O9UA6jvVg1ilsLOcL7AFqp9XETnSon+A0RrnNHo1mr4A8OX+RXcauqOrgHGwoQWkkydizvItK2Gv0d+f9uG5q4Cqf/IjIfWPzep9IPc48V9JzW3Gcz9B2Dcoj7dfpRVm7kN0AbGSVAvTVoWbduFkSP9e8Y3skTp7lDztRVdZhL5CwLe2qlKpQ7bLSbdI0+Q6UsW2bv+ZLuPq8qZeVuG5kUyXdjaoatVCAG6/XqovyXqmcqyR+m782Sfxk8bv5q5ucT0Siy1TM7pQC75Y4/f3fHsh7f/AaiwclTHbQ+gHnStpVpJ77U5/F8jBj9qlwiMQ/bj2kulq+9eu+qcycHH2fPHSa4/S/fc8U6Sf0Nb0vp8iknyQF6DHIpI/Qb5DRb7TskBlnp89oWX8z1k79BOg0MVZ4neMb2ysfXe28jOdS7nn6x0lrp78541gX7AGWV9557eOFn/z6ZMdvnvjjwrgVtRdh45R0MjOXdvv8rz+ldtlzY1qXxWk7mJcgOtMnT30a/XX2gqi4y7/MbTb5nRXhdaDyokutnTN6QYOZzw/Zn/Lzyu/OrZ57+jrWv6IzZfqeh/pZ3B/nwtXCcYgO4OUFsCK8HMocAEvf4/pZ1h/m4lbq53pfwklfgo3h1bAdHAoL4LWwB7wODoVj4DQ4Ft4Ox8EZcAJcCCfCJXASfBLeCDfDyXA3nAqPwtthe8owA3aEd8NL4Ez4BzgLFsLZ8FIdbogOd40Od60Od50ON1yHm6fDLdDh7tXh/qjDLdThNupwL+hwW3S4F3W4l3W4L3S4L3W4v+twh3W4r3W4MnZRuLJwJuSGlHDJcDasAOfBenABzIL3wFx4LyyAw+AfvH5dz/noVf1xe1vYRhdT6GKjcEdwg1oW6WULcYdwM1sV6WgtW9tmr9oMdLX2OJ/OthG3B7ewra1O4BLakQ4u5sIiXS4XN5E850Z0usgROSJH5IgckeNs6v+DB57B9f+eC1j/L8al5FiFK49bgTufF7/dL/jn/w8MWv9PzxnXazCbb80lfKKTbktaYfcDNPFbyruso15LfMc5BE76K2E=
*/