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
0x3/bLBq/IeOb/gd/12F/ZN5Rsc7qNw/mGDz9LM6fmr7/+qqpE++IPqbjN/Eizo036f9V/co83vy+zqm2fZHXTX7t6Cj1Y6PHOr0zzKPbNEx3JJvc7f82E90nOsn/pPXdQzZEWhR/QfK81NDfKjbpX99H1HW97vbPDPahyFMvwnfk/k3hS8i/T+2pw9Tfd489XkfPiLxzamJPoxk8dPC34TTvyvWP7n9fRiqO/unFf7H/CQf
*/