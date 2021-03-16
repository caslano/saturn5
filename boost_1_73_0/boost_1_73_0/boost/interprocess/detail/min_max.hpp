//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP
#define BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP


/* min_max.hpp
kmta8dBDB8OIrGsDgYOFMbBGwW+Lwpgdf7rDKKZciBsL6X8J3EkYWFiXb+MABPh+Gp+Df5bGV64/T+Mr118A3AjwbwA3Afw7wG0As118TpcD8G6AgwGiEx4O8ATAEQDfADgS4J8AjgLYA3A0QHTMYwBiHse6ePx8LkB0znkAcWlxnIuviI8HeAHACQDxbeD5APFI4CQXX/ibAnA1wGkuvkI+HWArwJkuviA4y8UNCK6LcwOCqUyGRobj5jokLqg=
*/