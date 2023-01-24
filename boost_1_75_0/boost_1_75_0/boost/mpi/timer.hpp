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
HKFe+Vwiy3X2S5qo4ZQ1uQ/d9dPWN85prsA+HOj796177m7nguzWiJAn/jf09gXYm3NSmDe/8bO/az//YM6XHE+9+P0fjF2LsQPW8/Z854rTHxt7aOuja58sT14x++kYWcd/OrvqiszvtWX1/G1TV0HB/K2Nkl7ylcJrb7kxLb+//JpnavW3rcZeH9aMuxpueML8fE3BYc3rxz/7186vpct9r+0rHJduviy78Nirh+57t/7w+U5JX/mlv/7vP0/25XTv7vzB3LsevwX7hKB//ca/zfnHJ58tbL73/ucv+8aPJ6yS/vv7fpU999Qfcr79x7trHvz41z87Iul/ffLJy37ZfTL73uHhu75wYoETe4yYVzxef2/ZP/M+kf+pLf/QFBx/ZiHWoLAe9RdLQfeq47MyO4OrDA8/lv0M9iIRT8GetGseM23a8pXcFTFP3/nnW7A/iTHebaet11ke/2Lul+OfWXb0gQVN2LOE/9/Fm2q+VPm9jHvyfxL25paQXuxjYn0l7w9H/sfSlm76UpLDXLIreyv2NrG+unlbyKOvfeTNgh/kv/nqV7/o/D72OzH2qn3GmHPypugtJ+bc/vulya8swh4o1rQu/ejbTzd+ri39m397477SiUfysS+KtZWe0dcf+8Syr2y950DL4tc++smfYK8UKub51JaKFZ942nTkumdeueZjjV/F/ilkccMTX/lFdbfT1PfO+l/9
*/