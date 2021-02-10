/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   thread_id.hpp
 * \author Andrey Semashev
 * \date   08.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/cstdint.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The thread id descriptor
struct thread
{
#if defined(BOOST_WINDOWS)
    typedef uint32_t native_type;
#else
    typedef uintmax_t native_type;
#endif
    typedef boost::log::aux::id< thread > id;
};

namespace this_thread {

//! The function returns current thread identifier
BOOST_LOG_API thread::id const& get_id();

} // namespace this_thread

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, thread::id const& tid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_

/* thread_id.hpp
BqVnqVHAVkykbI6JmIXE2sy8a7XCXKdYfStSoWmF1fabiV1ud3KHRSzZBlRmwSrIDfeBPH1YqkjE9ERCcDHL56kwib+rBlPJqKU0GJ6mhIVxgpuibA7Tkh6f3CDDioWlh1HSUKp1opYHjsgjocS5lpgIeUCnSCHNPuQy4to5u51XKUpOHcH/eTS7eiNQEouBWnsK/WkN5swI48Ntf3Y9upnBbXsyaQ9ndzC6hPbwjsB+6w+7ePQCk2ngD5nmBpNrEMssFTwqc36/T8t7KWSY5hGHmlUqDQy3edZMah4a4ojHcN3+oxeMb7vBtfcSHC8xdtdwFAx7s6A97kPrBIX0Ty40bjfGUue5SCMhF+5LeykWbDQFSgRQpfqQraNmcuG95BKP/DDV9G4aTGftGeXb+puNaRnL7F7QfsxlZzgbHATEobTpYYrKRBptLTMtpI3J45gBVAmPhC45qExLvoz4PF/gMu34M+dZ0SvYO4P2dLbdG+7Uo1JFCGHCNJxccduTq3qIKrTl0oppQa3T8L54UK5FeYbKPeFy9d7DRXzCR6BagwXHKbGqb4Peo1nE9Re42PBoCmk8My1heDMYuFiCwmBUIb7VyY1CHFasOd+ulHHk/t579Dx3km6JtE48oJZxSFilN1UHIIrm0lLf
*/