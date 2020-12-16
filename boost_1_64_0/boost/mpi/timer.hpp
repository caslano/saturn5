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
VVN0CFdNzAZ2QFubRuqWmeaYhr9KFfSwtlzDFUq4Qv2E9tq+ih+Mm29gzgLLY6pPTVA34bSZ5PN2V+0x4QcEIJPZFCtRUqGQKFunBLEyrWsmZ+BwG5VcBiFF4cjULlAK8HLmQVFRCmjteu/Wz3bt+l/4mOtn3YKU9bf+JpCiPYCWtAmPm1xbPR4oK0rZdfVpV+dUfXEAwDdaYfdYK4XjaXnrV4hbDj5WIzF5EPE6m6FkkMz4ovJIQ2YG1EkMpkiLS8+h5mGOzWU+vg3Ycs5VxJZd1gt1/2/U/kzEL9oN/vVE+8G/3ujQxDilvVcake50wgxEu+yJt+ZyyhhAm3X3KmPg9bwBXxRuBpIRhszxX4Z/AM/vRQ4NzxR836xNwte7YBaMD3jcWnb7gyYWC3syZuea2I8lg9GK/YRugr3brHfxdYJ9plewvx+xf5Kx/+BKC/YrGqDJe+HvSfj7/u5D87sp//04V20eSUkfmCiJPomelOiuzZXEkFhfafU/mPtUyRMdFJ4gNI/cGo4xytME5aZVkCBg2UQJwGhzClL0dD/u/tJCXoMb0UDiHNoPzAU9h3kfEwooLqWt/haYG/mU7MdDje6YB/dnC9iqqa8rdEUHSbGgFCtsnOLjcoVb3Yd1awzpEUJ6PD3fQo9n3JoedzA9xoSJHhwaM457H4MZXt7MrqJW01XUQq6i/SwTYOMPVv9qo5yXhk5RNscXsOhuYnFbuJGx+NYVFix6m1aqj+TLCDF+uzIfXoQ1R7U0MPwXl27pq2r8rxBte4p0lkc+FzrJ+w+xIAw7JQQpIYgJIUoIUYI/dsjOdxO/AVb8MiyUuJPxW3u5tgYEP5spQETpd+EhWQN6/+d64Qdo/1zL/FjB7Reb7RdZ2m8jSwH3/oAooDh12n1oz+xlP0sv7+JWfnCZtNLdnHAIlq2ELsaXhEj+Xaf9qSjYjpmltEqIb9nvAvO7Re3N184C5w7sxNTXtQRRqLcURLvDv0XRUKI/XPYe8qK9Bl964Zeh8KU3fhkQfpewZ81uLtr/jHrTg6jZnY9DYgz0qaWrub6u2VVbFG6ROuH7AC+qtn0uV7uMX5GYWN4cHRD+0Ab7CVWozI0zdyHaJ1H0JMiyiP0JYN7oJZh37lLxpJCx2grGKpZ4l2jRutWFizRkCpMXu6LDjcgtWPMoqUl7TVP9zFWwvmP9p6Aah4LsBylVZVzUm1YGcmbgLCIFAJmJ+CIofBGCAQRBBlxaoLgULZ6/nMJ2JCfUFMVwrKWx6ACWJiQMi2PdVakqwGc4qKmgALRTcJv3PLZVZKvyn6XE/OgGGhk+xmTiKUTES9hfaFxTBz2lQMDTeLE75EX23/gx9yMPgj6t4nusbH1WFXRBWAwH6SMsfMdtOJhVt1u8bJiHHgai277aJOYZEP6hKRCvj1wGtBp7CTPc02rIjZyTVA2cJ66oH/51Rwclyth52Kq9EY15LpcoYzckJqB4kvAh0sreP1Era9WJfrCZKS3XUcub2SubGAtjCrWaidMOsJ5iangwuntdenSx3lKuZ9x5K3Qd6xpXRv4No6vjn4GXaERenpkSzZmJ82kKLYbp5T/Xh2pL6tpQ6ERD8KUXfukBX3rjl2CiFzFDIripgOK8KBQ74eEupt+vpPXvKuSf/cg44k3CmF0as60LkgY3m1R6kIwYo9L0e6ghiy4ok83IfdS4GekAo1RplPYgWTceottOZYZohjfWKRE6ZYC9yKrj767XNuNcr4xhNFIHY7jlQh77gsSj3GKl0daNwALmuASgN3hKgIy+eVKX5n4ImYv2zWtIzgcphiDokjohVrb2kznYgj7ilmqj5+WfzEd8KB/zPd7JkeT3RzA=
*/