/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 */
#ifndef POSIX_TIME_TYPES_HPP___
#define POSIX_TIME_TYPES_HPP___

#include "boost/date_time/time_clock.hpp"
#include "boost/date_time/microsec_time_clock.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/posix_time/date_duration_operators.hpp"
#endif
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/posix_time/posix_time_system.hpp"
#include "boost/date_time/posix_time/time_period.hpp"
#include "boost/date_time/time_iterator.hpp"
#include "boost/date_time/dst_rules.hpp"

namespace boost {

//!Defines a non-adjusted time system with nano-second resolution and stable calculation properties
namespace posix_time {

  //! Iterator over a defined time duration
  /*! \ingroup time_basics
   */
  typedef date_time::time_itr<ptime> time_iterator;
  //! A time clock that has a resolution of one second
  /*! \ingroup time_basics
   */
  typedef date_time::second_clock<ptime> second_clock;

#ifdef BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK
  //! A time clock that has a resolution of one microsecond
  /*! \ingroup time_basics
   */
  typedef date_time::microsec_clock<ptime> microsec_clock;
#endif

  //! Define a dst null dst rule for the posix_time system
  typedef date_time::null_dst_rules<ptime::date_type, time_duration> no_dst;
  //! Define US dst rule calculator for the posix_time system
  typedef date_time::us_dst_rules<ptime::date_type, time_duration> us_dst;


} } //namespace posix_time




#endif


/* posix_time_types.hpp
hTNOjO37MrxeMDpXnGeqq2D4lHkMcDEy+1UGlOR5wpvHsPNtO/QdtUwPTSr8q7d1nCoX0gziNUDamQhbp2CIFufFC/FDTyaz+WhC6kgvSJAr/Tqmo5lprZGpjpfDMdmyGGmOYDkNSHd/CNXdQT+4uT7zo1jBaiMx5IIinm+jdvQvdlfaUpKgbfqfhM/USKzkOWO91yIv+cg9exqibP/h+4iqldooPRrPLS2tIP24RrU/3cT1onfib6Kr6zrW661GSzBtngO+wD2TU7o8aYRC23Y285l2G3eDnelsfn482HS83IloD+Reb2/gPhtO2fNtP+SeR/4lUBNGK2FDJOsByH2ju0O0o7vjTv30292rlu70jTgQsCO5Q7tj8U+TPtnDMtBtX2Dfc9mTGSQYKBjE0mNgIy+yZd+z2eOxQ7ZjuAMwRnbqLmAK3TRfe7Ycwa9ehqGiuQxVuUImg91CIoHpwvD6widdO+V/HQawIJlXGoz6EOfC5RQtIZOLIskk4f0Zrm3DTMaR0J/C75AZ7jX9FYiEc1s2ygmvabpRdzEquOXUTtgsRRXCz2HztAIyz5FdlbxLc1664nYTNCcUa9FR6efYp4LlrNFLHH7QRi2Mjabbk9wgO6uXVDUb+UTZ0sZ2ZiFWYv55HcXW5UTTzOVbixTFT3saU9UFCg0iAbgQLCqemrGaLMV2n9BpY+nbOAjV9x/BbsObG+zzMYSK
*/