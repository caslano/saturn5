/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#//Try to avoid including <utility>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_pair.h>
#else
#  include <utility>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP

/* minimal_pair_header.hpp
r1U8ZVaRUvLVLSU5WDCZAFbGUmna/agsLrE7M6+gHF1kfiS3pODo0aGbtl684aaF+9akR855d5L5DrySgm2Lr205PGjDluu3lh185Wd37gXwRO2vr97/0vEjd3zWu37CqCduvxII2kHtVVVb9PdfPzY6+ObqccGfjPsv82qYkoKR57Z5X738cOdFk+9dd13vo0fwTa3Yfml57Oj3lyydVrRy6TnX/SW2H9an9t/ceeilulj8/rWfXtu6Y9IjAxk=
*/