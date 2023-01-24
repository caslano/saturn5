/* Boost interval/arith3.hpp template implementation file
 *
 * This headers provides arithmetical functions
 * which compute an interval given some base
 * numbers. The resulting interval encloses the
 * real result of the arithmetic operation.
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ARITH3_HPP
#define BOOST_NUMERIC_INTERVAL_ARITH3_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

template<class I> inline
I add(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.add_down(x, y), rnd.add_up(x, y), true);
}

template<class I> inline
I sub(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.sub_down(x, y), rnd.sub_up(x, y), true);
}

template<class I> inline
I mul(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.mul_down(x, y), rnd.mul_up(x, y), true);
}

template<class I> inline
I div(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y) || user::is_zero(y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.div_down(x, y), rnd.div_up(x, y), true);
}

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ARITH3_HPP

/* arith3.hpp
wEmTrw9rH7qE9YCOAaEPK77DJcQ7J74YWB1oTgtUpwFDNLkt3LnT9EP20VAyIUAxDNppao5giVhloLD9NZTVBLcN+kXQJmGFyLgjwDLaSbvU65uI4trc8jVS8S1/qON8WG73HiS6uyhVL5yXmPURi/mlkfV7n2YdWw+g2ouvH2rCrcy9SFBMj9aKcdtrJC8SY1PsqWoyiyoKsyel/2T6DqQAQN+9wG95g/lpkUhD8zfHzQKmDXSCSKFMVdUvkwWBOW7J01gusnWnqE8LU09cvhUGpmeq7vZPnUeLjsU6rj7TQK9MkuRrmFuPuFbUrD/X0bH+M8ZnAIHKAAYs+dOsQcq1u02+sS1zv5Jn4CF2KZdTHAeZPMlDP/qgevptPf7iej0X3OgXIrngyF39OPpZmpMw9ygK3uGoirhkgSd5oyxFC1iWIinaTIx5x9YLZtRRbHiBnLv64D0J/fEpwDR9O+B3H81aWY1uAm0VjbqbgJ6RLXuTQeB5HhMBCCzTCaUku3U4nX5FlIeqw3qwEEbzzc9HgkngOE31siNVVVOQsJOij4Uu8GiSHqzLHITMorfItwfz6311JhYJit/qEJPVkZcu47w09dfp/AjLcPMmhvnpQE2R6hyNb3VR5ku2focVR1BchUntxmtbky9BWmreiddKfpGaeLZ3FfPj9JXtGOEZXvqWAmiv52BDSF3xXARSeiaadkq+55Zb4CBT
*/