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
cxH95VbWZSZSI6aqKvUTa5rLL/tynYviUJegQvNzwrvkPoB3rulakJugcYs0+YUW40VeWEXcFayde3OtlkeX5uowT5CazOKYB+MXiH9EAP+ODPcWFYEJ3dg6IjBjJ1990jHXNqdZ1GJu2BmyVjtmDlf0mS+gOa8KJYsxeNj5ih6w9eWR6fQaj9OMIFZFe3aP40zNZYcvM1if6ztT4l2PeafS6KNzEYnbmdsgJ9MAGa5vY720eKfxu+GZEa1A2HTlcyhllySQcU+p8RaKN7hdNjKn20Y/mcuhlfVYJEc2kloyPnd4GgHOAK/ZQfpf24bHlbXzqH3ZhsYfS8nnvkuXoSTczlsf8KqETYmSDYIRNE1FSP9yuegW06YCJNOtkylSmmU4sPlrvJybzkO7qNI8jEGxmNsXPlKCZqL9DywFU+6Xe4Ef95yv/BBkCNz5K6tVh9R9z1v+TPbbTBIt6mQwoLDzm6ubIFcLkNZNz9ckgJYLJ8M2az2qI2rQk8jSCuRc4pyyzDs1OW0+99I9Z4gyyQKWm+bZkuwmJBVWhvq8XT7qpCcqkaqD1ztKB9BM9DNYunD61PDb9pfiuS9UQIn2PzJXLEDZl8ZKdbR7t8Y8mmqI6z0gWJ4wN+L18bEUg9BQ2+/8lT9iGxkly45tGTrxoGOtOdWWvtqEvr/tzQV+Hd7wwN5YnaqCYoSHPBqxQSn2Ju1fIMle2vye0YTM
*/