#ifndef POSIX_TIME_DURATION_HPP___
#define POSIX_TIME_DURATION_HPP___

/* Copyright (c) 2002,2003, 2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <boost/core/enable_if.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost {
namespace posix_time {

  //! Allows expression of durations as an hour count
  //! The argument must be an integral type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE hours : public time_duration
  {
  public:
      template <typename T>
      BOOST_CXX14_CONSTEXPR explicit hours(T const& h,
          typename boost::enable_if<boost::is_integral<T>, void>::type* = BOOST_DATE_TIME_NULLPTR) :
      time_duration(numeric_cast<hour_type>(h), 0, 0)
    {}
  };

  //! Allows expression of durations as a minute count
  //! The argument must be an integral type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE minutes : public time_duration
  {
  public:
      template <typename T>
      BOOST_CXX14_CONSTEXPR explicit minutes(T const& m,
          typename boost::enable_if<boost::is_integral<T>, void>::type* = BOOST_DATE_TIME_NULLPTR) :
      time_duration(0, numeric_cast<min_type>(m),0)
    {}
  };

  //! Allows expression of durations as a seconds count
  //! The argument must be an integral type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE seconds : public time_duration
  {
  public:
      template <typename T>
      BOOST_CXX14_CONSTEXPR explicit seconds(T const& s,
          typename boost::enable_if<boost::is_integral<T>, void>::type* = BOOST_DATE_TIME_NULLPTR) :
      time_duration(0,0, numeric_cast<sec_type>(s))
    {}
  };


  //! Allows expression of durations as milli seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration,1000> millisec;
  typedef date_time::subsecond_duration<time_duration,1000> milliseconds;

  //! Allows expression of durations as micro seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration,1000000> microsec;
  typedef date_time::subsecond_duration<time_duration,1000000> microseconds;

  //This is probably not needed anymore...
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)

  //! Allows expression of durations as nano seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration,1000000000> nanosec;
  typedef date_time::subsecond_duration<time_duration,1000000000> nanoseconds;

#endif

} }//namespace posix_time


#endif


/* posix_time_duration.hpp
VtqV32t2d+dp/twFboA13r2AWS00aFmZHVMc8HcjCt5qXgLTUHJdKLHCB9GCqTlUouEwS+Y3YXzpwq4WRT3E2cst6FpumxJqdstB8YKL2z5Mx5QBWWEEjF8KbTDm1gjZepieg+Fqo4cwVARrtAR2y0TDVpiOGaiN6fSvk0mxVQ12MilloSfFAQqvNpvPurrBajZsD7IzYCRsNXeB7F3YyFJUdEeIcLHbrhqha/dYFiZsy4lUoHnTDOHQVXDdt8AhHdByyRI6rF4YumnZasq2q+XmniHCOgSqtqrFdAgL2pUSgXdh25ZcWXsLxCHLgLKF/BsjO9ZegmyxKhj5KYTpCFZMC+3C2zC7Sq4zeOsvFn6c3UByAX58M8R7FcYvkRsCsyrgd53iGqtQIDZdI3h5L/kPVbrjZVcwu15EyTzLw8s4WQT5LImzIM7yKIgvcfchjKZP4I9tiySfPhrBqBErYgE89h4+9s5xgZ5yzvQ+19zQvPGL1NIYPb2C2H8dOF9PsTwDsW4lQlnIFsVjoOHt2tTWP72Jk3kapo7XVs5Poi2abcnhGSXt2Vg/d2z8QuL657WMaQdOa+RJg3T5ah2u8/8nQyPb9VDkyVNb18sgnS3CeRYmsRNWsKzCfntZzYkRmJ4YNo3cQ2+WUn1/
*/