/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/manipulators/auto_newline.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains implementation of a stream manipulator for inserting a newline, unless there is already one inserted.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_AUTO_NEWLINE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_AUTO_NEWLINE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Stream manipulator for inserting a newline character, unless the last character
 * inserted into the stream is already a newline.
 */
struct auto_newline_manip {}
const auto_newline = {};

/*!
 * Stream output operator for the \c auto_newline manipulator
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline basic_formatting_ostream< CharT, TraitsT, AllocatorT >& operator<< (basic_formatting_ostream< CharT, TraitsT, AllocatorT >& strm, auto_newline_manip)
{
    typedef basic_formatting_ostream< CharT, TraitsT, AllocatorT > stream_type;
    typedef typename stream_type::char_type char_type;
    typedef typename stream_type::string_type string_type;
    if (BOOST_LIKELY(strm.good()))
    {
        string_type* str = strm.rdbuf()->storage();
        if (BOOST_LIKELY(!!str))
        {
            strm.rdbuf()->pubsync();
            if (str->empty() || *str->rbegin() != static_cast< char_type >('\n'))
                strm.rdbuf()->push_back(static_cast< char_type >('\n'));
        }
    }

    return strm;
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_AUTO_NEWLINE_HPP_INCLUDED_

/* auto_newline.hpp
cZ+dpzwY8fi2x96MqeU/p87Dw3rC93qMp8zx1+VUF1MvYUk4Se+dmDP47nsuDxI+Zk7CxjxxY28EP7yApVPOJp7P2duT0y+Hxx967H7quVOc5DHMWDINM3/Mps5XzmLucu+rmCNy4pSFExgOk4+9JIUJs9QLg3VYm7OUx7ME58DlHT8JmfPV8XxnBAs5KZumaZRsb2y4WewD9Rvj0E02XLX99Wk60zv5AkTMnEcWRilLQ5YlvMewZ4/NwrE3wb/AEGiMspHvJdNeTg0sFYw3wpgl3PdxLhjn8USQzdm5ZE8Pu7EIKPZS/JOEQYJL3U/DmdUR+IizTLI4gIWAD9BpHAKbeywLxjymzrRztYTkKTG48mhyescsDIAY1tw/Z4fnTTZyEi/psc+HFx9PLi/Y5/2zs/3jiy/s5D3bP/6Ck/11ePwOjt6DxWLGH6KYJ7B4zLxZ5Ht8LNf8dZ+NxgsvcP1szFkzDUN/mPA0i9anzUbjxZhPvICzg+P9P48Ohm8vz47+OTw9Ozy+eN/Y6OLBsTCLWXgfsCj2gnTS7gArAxeFJmHWzCgWDzhpYTF3cosSVPJkHCb3XlDyAGa69cNRyZOvs8RuHT8Go2wi9qIbZ3w25qPsFpoZ7OKO80jIPOjA0f75BVM9YQOaBR+O
*/