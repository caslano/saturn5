/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   debug_output_backend.hpp
 * \author Andrey Semashev
 * \date   07.11.2008
 *
 * The header contains a logging sink backend that outputs log records to the debugger.
 */

#ifndef BOOST_LOG_SINKS_DEBUG_OUTPUT_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_DEBUG_OUTPUT_BACKEND_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_WITHOUT_DEBUG_OUTPUT

#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief An implementation of a logging sink backend that outputs to the debugger
 *
 * The sink uses Windows API in order to write log records as debug messages, if the
 * application process is run under debugger. The sink backend also provides a specific
 * filter that allows to check whether the debugger is available and thus elide unnecessary
 * formatting.
 */
template< typename CharT >
class basic_debug_output_backend :
    public basic_formatted_sink_backend< CharT, concurrent_feeding >
{
    //! Base type
    typedef basic_formatted_sink_backend< CharT, concurrent_feeding > base_type;

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef typename base_type::string_type string_type;

public:
    /*!
     * Constructor. Initializes the sink backend.
     */
    BOOST_LOG_API basic_debug_output_backend();
    /*!
     * Destructor
     */
    BOOST_LOG_API ~basic_debug_output_backend();

    /*!
     * The method passes the formatted message to debugger
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);
};

#ifdef BOOST_LOG_USE_CHAR
typedef basic_debug_output_backend< char > debug_output_backend;      //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_debug_output_backend< wchar_t > wdebug_output_backend;  //!< Convenience typedef for wide-character logging
#endif

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_WITHOUT_DEBUG_OUTPUT

#endif // BOOST_LOG_SINKS_DEBUG_OUTPUT_BACKEND_HPP_INCLUDED_

/* debug_output_backend.hpp
YT04QQoVQxLosOBVx4mPdzK2VAgGzXozcdXqWB0EV0/MZEM7lkPk0z393cHcZBthdYSvl3HwYCfXml4+52juUZFt4O9bf7UFzyZG01WV8kZmD1M/y+55uF+F5NYMQywJEJ6TldgJr3fztNY5XfOHZ8bHAnb+IX9QHV3miE+wNArmMFI0ECwrcat2vmWknGxzr18LdMqtokKAs2IPiQfQtRCn1bQQty82lE63EH1moqYf3bNVsBDs+qdj2ta8n/z5KOie6UZg5SDKHotvg+QuCTPOTuqqP74fVAwKCnxyx8NMP6bok54UT8RCiwH0rwgXy8xbCeGBgUAOUX5swcQPKkOA+TSOAhkrEYUlRNBMOvtiCI5K+S/sJXOmfafWhrZS8Dpal7xRsxxT5CyoFC+UvuEnN7MW/vfWgylbe/Tk9q9/q6MM5DVACfARtFLmHIz7lm7OxQ+wTtX15OKnBsE9/pvaQRxTxBFGjOSlalsBP3yjB0r41fRo17xtv+/iLadUr6uLgiHIeKtGv4O1acAk21dHb0QfV3gQih0iWsmM3PEAZj/1k3slFRCvGe4yHueB80Y+JtA2QMMIq/Srh9DTwd/3W+xEuwVhjywZ+DT4O4gh89sDUVILTCG5XOmEltCDPM+HTwrPouBOJS7Q
*/