/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   basic_sink_backend.hpp
 * \author Andrey Semashev
 * \date   04.11.2007
 *
 * The header contains implementation of base classes for sink backends.
 */

#ifndef BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_

#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Base class for a logging sink backend
 *
 * The \c basic_sink_backend class template defines a number of types that
 * all sink backends are required to define. All sink backends have to derive from the class.
 */
template< typename FrontendRequirementsT >
struct basic_sink_backend
{
    //! Frontend requirements tag
    typedef FrontendRequirementsT frontend_requirements;

    BOOST_DEFAULTED_FUNCTION(basic_sink_backend(), {})

    BOOST_DELETED_FUNCTION(basic_sink_backend(basic_sink_backend const&))
    BOOST_DELETED_FUNCTION(basic_sink_backend& operator= (basic_sink_backend const&))
};

/*!
 * \brief A base class for a logging sink backend with message formatting support
 *
 * The \c basic_formatted_sink_backend class template indicates to the frontend that
 * the backend requires logging record formatting.
 *
 * The class allows to request encoding conversion in case if the sink backend
 * requires the formatted string in some particular encoding (e.g. if underlying API
 * supports only narrow or wide characters). In order to perform conversion one
 * should specify the desired final character type in the \c TargetCharT template
 * parameter.
 */
template<
    typename CharT,
    typename FrontendRequirementsT = synchronized_feeding
>
struct basic_formatted_sink_backend :
    public basic_sink_backend<
        typename combine_requirements< FrontendRequirementsT, formatted_records >::type
    >
{
private:
    typedef basic_sink_backend<
        typename combine_requirements< FrontendRequirementsT, formatted_records >::type
    > base_type;

public:
    //! Character type
    typedef CharT char_type;
    //! Formatted string type
    typedef std::basic_string< char_type > string_type;
    //! Frontend requirements
    typedef typename base_type::frontend_requirements frontend_requirements;
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_

/* basic_sink_backend.hpp
E+XmqQQsHVnilzitJLIdtFdnpvHXFyIWDPBp+0Q2ljrs8ufTXtygQYkLm8Q4crAwCaehQHLK2FfZ5gv4zuvUJ2dtwgn4r6Qg4SvF474Lqpz90/0u3vHAV1sevUc24jFwdB1OwB8vVSdBU9dban8QTw28qqm/hxtJZVY9G3k+8E0EBRNrrEX1AW4g7fcdemC49Iwz0MuwpmyKpe/p2H/7NEo87217rlFZ912fuK1Qn+wp64pe6V0JVXKn1h2WqteEJkaLEjnhaSJJAeljzxzTgm/3x4WAJpWiy6wehgWDJjBmSx88X/l+spdNHX7PtOhXCpqKUNiGg3Al2fuGlw+r02RXzVZ3+ibottP2OHqNlqws3KR0ldo7Ui3O8Ny4HAC3PR8NXia+Kn2MmsKTWDz2swvk2bbutDdXMDDcHFtWhT5AFixoKQTtcDt9V/621RQcYcPFGQf63AFDLmKttuPjSRiaZJbtfk3l1fi7WTFtb6yO83q1Em9vdNQ+u4CqgujAq64FDH3gnUSqqCPR9hzROjju34g90pxZ3vhvxP75/87ROTn/ZeYlnBwtbVwd/uXlsbz1pT1E7m2hrfar6RTrDftMq0kXK41lUPkYCr21qMbIFfZ0l8JEldqW5XkFza69y82VWPbqP1GRVn8qmumu2S83s5fR6snI6H76GJ7u5V0KEGNofmM7XkWIfzOHRD0RZHlUu9TYnL7gbxQC
*/