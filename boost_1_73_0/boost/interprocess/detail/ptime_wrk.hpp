//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP
#define BOOST_INTERPROCESS_PTIME_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/posix_time/ptime.hpp>

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP


/* ptime_wrk.hpp
kp30yGeUY7ZHFufFSpEWaHS5yVq5Ro8tHhccscRjxwggqKTq97yUqlY3tAvYmfGjuhu6Bt3QmKMO3fMeBLdY+k+4pcupmZcR/AHektKM4IPvxr6X92QEd+P9Ld4evEMANwbvJLyz8PbpX4zcuzDg+jTQcHQrZWbFU7YMaKqCn3Xd3o9QPKBV3SQa5v77N8OQJL8gSZImODlUp0Ze1cbZzxn1AvZFazwIYryiRB9lhV/lBzD/
*/