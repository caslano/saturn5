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
cy9saWJ0ZXN0L2xpYjE1NTQuY1VUBQABtkgkYK1V/0/bOBT/vX/Fo6eT2i5QbvfLbeWmywobHF2L2qIJCclyE4f45sY526FUg//93rPTpggm0GlB1PGz3+fzvqff+3lPC3rw4sP8P8MHV69xYfQ/InHP32bsHsIfal3j+hJJHxqVe9aFl1XuoeNVWM1yRO+MvUR0TbbRT580rxm9ogTVSHOoy7WRN7mDzrALv7179wfsw9vDt4cRHPNCCgUzJ4qFMDcRHKVe8lfO7+4OrPgQgXDA1UENNc+lBaszt+JGAL4rmYjCihS4hVTYxMgFbmQBLheQSSVgOLm4Oht/jmCVyyQnkLWuwOa6Uink/FaAEYmQtwGj5MaBzlAdwVNpHQJWTuriALkFOGGWljCIniurgd9yqfgCibiD3LnSvu/3k8ootL6f6sT2k437B7lbbj25QiOWfA26dOA0VFZEQDcjWOpUZrRiQFBYVgslbR411iBVkfa1ASuUIizUk8IGswXM6vBEdA1KtFg6WqwuLFGtcr18dBHjSChZZQokwjjgpVRjmCOoilQYf9l7vqGoY+oD/MPUNPamoAs0BtrxDM5mbVhwK20EX8/mp5PLOXyNp9N4PL+CySeIx1cEdn42PsbUSyQzIO5KIyySG5DL
*/