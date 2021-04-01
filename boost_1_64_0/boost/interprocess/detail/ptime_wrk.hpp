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
Tmp89a+97FkARQsHFHUS7eSUVQu2m/p/158j/38s+cJuvealF8N2T2NNnphFaXXgwGRFFWwrzi+Bh4Iw2Cj1a4khfSSnYMRNkkEhLSbeDLFugWh6NYy/31cG+5rFHLE1+ebclDpjcYf9leegTZhlhcjGIpGvprjR6wTKk3Lwfm4MG57f1c2q4xMiDUGYffxVzX9EjQ7MCV/ccbSC/Bgq3v1V3hqZJGo0IjoiJaqMywOuK5fC9nbc69mnqcpVPjRxjtdEN6AUUOwbpqGoTJQ4f8NASJUVIlO5tU7UEFRX3+iNZjKJyVfxDCYqToXTMjQyjC+edzDxgUF/oyws//oQYIPBlZI5jX8aUCN37lobEfOII3yxSM7aus4UUrREL37z8DrptRW0fal29TMULcUvweWQuUkOjegycBavzEyy+IVKBCZ41Zkk2W8UQtSsARv/E4QD4mW2r8x335+3wTpt35ypWhdKwpiVI6g+U7sMWCb0q4hU8y8x4rOO6zJj8ExXDnJM88QBldBTl/yWxtiysdo1EyYNuyKICG/pEVLsAGAUDzq8pMfCu3MKBw==
*/