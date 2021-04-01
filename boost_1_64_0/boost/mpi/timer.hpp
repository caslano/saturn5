// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file timer.hpp
 *
 *  This header provides the @c timer class, which provides access to
 *  the MPI timers.
 */
#ifndef BOOST_MPI_TIMER_HPP
#define BOOST_MPI_TIMER_HPP

#include <boost/mpi/config.hpp>
#include <boost/limits.hpp>

namespace boost { namespace mpi {

/** @brief A simple timer that provides access to the MPI timing
 * facilities.
 *
 *  The @c timer class is a simple wrapper around the MPI timing
 *  facilities that mimics the interface of the Boost Timer library.
 */
class BOOST_MPI_DECL timer {
public:
  /** Initializes the timer
   *
   * @post @c elapsed() == 0
   */
  timer();

  /** Restart the timer.
   *
   * @post @c elapsed() == 0
   */
  void restart();

  /** Return the amount of time that has elapsed since the last
   *  construction or reset, in seconds.
   */
  double elapsed() const;

  /** Return an estimate of the maximum possible value of
   *  elapsed(). Note that this routine may return too high a value on
   *  some systems. 
   */
  double elapsed_max() const;  

  /** Returns the minimum non-zero value that @c elapsed() may
   *  return. This is the resolution of the timer.
   */
  double elapsed_min() const;

  /** Determines whether the elapsed time values are global times or
      local processor times. */
  static bool time_is_global();

private:
  double start_time;
}; // timer

inline timer::timer() 
{ 
  restart(); 
}

inline void timer::restart()
{
  start_time = MPI_Wtime();
}

inline double timer::elapsed() const
{
  return MPI_Wtime() - start_time;
}

inline double timer::elapsed_max() const
{
  return (std::numeric_limits<double>::max)();
}

inline double timer::elapsed_min() const
{
  return MPI_Wtick();
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_TIMER_HPP

/* timer.hpp
6ymrSmQY1urX2hoJbL7RGoZxv35jNmejINcLHiwBJ1bqjfkxTfuF56NDZY8lvAJ803OcxPGSrZhQQKUTOpnfjZgmKvfvjKNOunKHfSde6BoImsBMcEMpm7EzKjlU+JU8LAIfpbBsYprV+QuFYjc8GYNptXUGYUAF8L5CXs+m+s1DUgFswQKvN3Ixzl+ImsQ9zy6CuskPd5mi7o2SP5eNPFjau7hIsvq7MOaclDLVPLuRIpVIK4gcqy46t96Bgl5fukAC6g/dD5HRWxE3heXNa831GFlLhf/vtAeDpz5VCHOkAXXK55LKth245puDpF6RRQ0DcCGgREOQbaUKgPMd+gvdsww9v5PV1HOU576hndjKJOiuM11jIoEvljLMIdGia/6oMV4rW+uZFyVUlLt8D+3VCCymjUFZ2NgKHCzw7FdMzH2DGxQXB7mKaWKrY4l5wtF9B3UieXbncGXelJoJVpCHKEffXnkhguI0I3iLP+QBhgNYUA2d5OmZQEaFxKJOVXeqeofcLJdIXCmgj52kgJjnosD3r6lLR38j9plcEVw7EBmYpuf1fA5yRQ==
*/