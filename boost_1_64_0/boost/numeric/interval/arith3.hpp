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
5ewiVmxq/Lo/U0FJsp14rloP/FganxTHGOOdrerBIpcv1kYzggu/4LxlOueBNhBTw8pwHGKq5ShmbrHkHpQh5rZouzHLzRoGYQrrSFdSXAhDnoBdqCCMiINOswNlAGfm2TSWUA4rh/0HqAl6+K4m3JKMKENTCOlVI1VkhiJdSfPNhO6PbGWPwPSIT8mwub/12HSD2PDpmjdGhFmPEn28rhpgxEJUQg9qRG7r9wZbuSuf9fHDHWKcsITVcK2vbiJeHyVV5zWth5xLSleJk0EDeLv1yJ0nQf7thnDq6i7e3GMYurFX7jwEIazHWhWEMuXmQqvWRZxphfCJWWojPSG4dZS7ES9qYhoRI2EEaojuytByfLpxWuqQ+7mHgTOmJe0ZMm0D4b8TzxUEUsY7M/PiFEFzF2YXxJ1jNsX1JkN9Y7iMgmKXF092kk3gb3oE9l5xKNfpWsXCemCldQFtODZvaAPXnfvp4gNtZ9X2HEEWdGVDjoeRrokO7c3btVBoF0Ckc7n4OMfz1pa+HdtGTXgRmH/gL6bzLv4GVllLDhvOZeNUHUHIPqMEh7kj+g==
*/