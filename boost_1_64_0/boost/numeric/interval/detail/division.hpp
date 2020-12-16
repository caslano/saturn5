/* Boost interval/detail/division.hpp file
 *
 * Copyright 2003 Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_DIVISION_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_DIVISION_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/rounded_arith.hpp>
#include <algorithm>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

template<class T, class Policies> inline
interval<T, Policies> div_non_zero(const interval<T, Policies>& x,
                                   const interval<T, Policies>& y)
{
  // assert(!in_zero(y));
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  const T& yl = y.lower();
  const T& yu = y.upper();
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    if (::boost::numeric::interval_lib::user::is_neg(yu))
      return I(rnd.div_down(xu, yl), rnd.div_up(xl, yu), true);
    else
      return I(rnd.div_down(xl, yl), rnd.div_up(xu, yu), true);
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    if (::boost::numeric::interval_lib::user::is_neg(yu))
      return I(rnd.div_down(xu, yu), rnd.div_up(xl, yu), true);
    else
      return I(rnd.div_down(xl, yl), rnd.div_up(xu, yl), true);
  else
    if (::boost::numeric::interval_lib::user::is_neg(yu))
      return I(rnd.div_down(xu, yu), rnd.div_up(xl, yl), true);
    else
      return I(rnd.div_down(xl, yu), rnd.div_up(xu, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_non_zero(const T& x, const interval<T, Policies>& y)
{
  // assert(!in_zero(y));
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& yl = y.lower();
  const T& yu = y.upper();
  if (::boost::numeric::interval_lib::user::is_neg(x))
    return I(rnd.div_down(x, yl), rnd.div_up(x, yu), true);
  else
    return I(rnd.div_down(x, yu), rnd.div_up(x, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_positive(const interval<T, Policies>& x, const T& yu)
{
  // assert(::boost::numeric::interval_lib::user::is_pos(yu));
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) &&
      ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    return x;
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    return I(checking::neg_inf(), rnd.div_up(xu, yu), true);
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    return I(checking::neg_inf(), checking::pos_inf(), true);
  else
    return I(rnd.div_down(xl, yu), checking::pos_inf(), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_positive(const T& x, const T& yu)
{
  // assert(::boost::numeric::interval_lib::user::is_pos(yu));
  typedef interval<T, Policies> I;
  if (::boost::numeric::interval_lib::user::is_zero(x))
    return I(static_cast<T>(0), static_cast<T>(0), true);
  typename Policies::rounding rnd;
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(x))
    return I(checking::neg_inf(), rnd.div_up(x, yu), true);
  else
    return I(rnd.div_down(x, yu), checking::pos_inf(), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_negative(const interval<T, Policies>& x, const T& yl)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(yl));
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) &&
      ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    return x;
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    return I(rnd.div_down(xu, yl), checking::pos_inf(), true);
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    return I(checking::neg_inf(), checking::pos_inf(), true);
  else
    return I(checking::neg_inf(), rnd.div_up(xl, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_negative(const T& x, const T& yl)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(yl));
  typedef interval<T, Policies> I;
  if (::boost::numeric::interval_lib::user::is_zero(x))
    return I(static_cast<T>(0), static_cast<T>(0), true);
  typename Policies::rounding rnd;
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(x))
    return I(rnd.div_down(x, yl), checking::pos_inf(), true);
  else
    return I(checking::neg_inf(), rnd.div_up(x, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_zero(const interval<T, Policies>& x)
{
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) &&
      ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    return x;
  else return interval<T, Policies>::whole();
}

template<class T, class Policies> inline
interval<T, Policies> div_zero(const T& x)
{
  if (::boost::numeric::interval_lib::user::is_zero(x))
    return interval<T, Policies>(static_cast<T>(0), static_cast<T>(0), true);
  else return interval<T, Policies>::whole();
}

template<class T, class Policies> inline
interval<T, Policies> div_zero_part1(const interval<T, Policies>& x,
                                     const interval<T, Policies>& y, bool& b)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(y.lower()) && ::boost::numeric::interval_lib::user::is_pos(y.upper()));
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) && ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    { b = false; return x; }
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  const T& yl = y.lower();
  const T& yu = y.upper();
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    { b = true;  return I(checking::neg_inf(), rnd.div_up(xu, yu), true); }
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    { b = false; return I(checking::neg_inf(), checking::pos_inf(), true); }
  else
    { b = true;  return I(checking::neg_inf(), rnd.div_up(xl, yl), true); }
}

template<class T, class Policies> inline
interval<T, Policies> div_zero_part2(const interval<T, Policies>& x,
                                     const interval<T, Policies>& y)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(y.lower()) && ::boost::numeric::interval_lib::user::is_pos(y.upper()) && (div_zero_part1(x, y, b), b));
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(x.upper()))
    return I(rnd.div_down(x.upper(), y.lower()), checking::pos_inf(), true);
  else
    return I(rnd.div_down(x.lower(), y.upper()), checking::pos_inf(), true);
}

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_DIVISION_HPP

/* division.hpp
uzWFmtOaO5o3mreaCs07zXvNB42rbW3bWNv2tsNsx+PvBba5tt/aHrG9bvvG1tUuyK6ZXXu7PnaT7Zbb/cvurN1tu/d2Hvb17DvZj7Sfa7/R/oj9Tfu39i7aKG0b7WDtLO067UHtVe1LrbmDj0Mjh84OYxwWOWxzOOXwwOGtg7tjqGMTxx6OgxwzHbMdVzrudDzheNPxpaO1k7NTmFN9p6ZObZ26OfV3Guk00SnLabnTNqd9TsVOV53+cXrnZKXT6Xx04boEXS9dqm66bo0uX7dWt063XrdBd0B3RfdMZ+3s7tzAuZPzMOevnNc7H3K+7PzK2dEl3KWlywCXTJc8l30u51yeuFi7Bro2de3tOsk12/V715Oupa4qN41bLbcWbiluE93muK1x+97tmNtNtwduJu6e7nXd27mnuk93X+y+2X2f+wn3y+6v3C08/D3iPbp7fOExz2O9x36P3zzue5h7+nk29kz2nOi5zPNfnsWeTzxtvLy9Gnp19xrvtcRrh9cZrxteb73cqgdXb169f/XM6surb6O/j1a/Vv15dRtvP+8G3h29e3t/4Z3tvcn7sPfv3k+9bWu414is0aJG7xrjayyvsa3G0RrXajzF32ofb58Yn9Y+XXyG+8zwWeGz0+ekzz2fDz52vrV8m/r28B3kO9V3ue8e37O+93zN/Jz8avu18OvvN9nvK781fnv8iv3K/F75mfjb+uv8nf29/P39a/lH+cf6N/Zv5d/Fv5f/EP90/2n+C/2X+uf5/8u/yP+y/xN/VYBDgH9AbMDnAQMDJgUsDcgPOBhwOeBlgG1N95pRNVvUTKrZp+aEmrk199e8WvPvmtrAgMCEwC6B6YG5gXsDLwX+Ffg+0CUoJqhtUMeglKBRQVODFgTlBa0KWh20Jig/aG3QuqCNQQeDTgT9FvQg6F2Qc3B48GfBvYLHBS8I/jb4YPDF4MfB5iHVQ+qGtA0ZGDIlZGnI9yHHQn4LeRDyPsSlVkSterXa1RpUa2qt5bV21CqqVVLr71oWodVDo0NbhfYNTQ9dFLox9GDohdC/Ql+G2oYFhDUM6xw2NGx6WG7Y9rBjYdfDSsP+DLsbdi/sfphpuF14SHhCeO/w9PCc8B3hp8PvhasiPCLqRrSL6B2RHvFlxLqIIxHnI25GvImwqR1Yu1HtnrUn1F5Se3vtU7Wv1H5Z2y4yNLJZZM/ItMgFkVsi90Yejbwe+SbSNapuVNuoQVFfRi2K2hZ1KupOVEWUS53IOol1BtSZXuebOj/UOVXnTp2KOrro8OjPolOi06MXRxdEfxe9I/p49Jnoy9FXoq/+z98Po99Hq2LsY7xjfGMCYoJiasWEx0TG1ImJiWkU0zamW8x/qLsO6CiqKLpiIRgjSIAQTEiwRGyhBcSu2LErVqJx2V1CJNnEbBKIvYsF9djRY6/H2Hv32Hs5x+Ox9xp77+3O3z9v3/5M+X92Zjky57OT+fPefe/999+vM9Pc0NlweMNJDYsaTm64Asc9DS82fNTwW8PvDStP5ccyiIsVsXIcVbFVYtWYmxiL/6vl2VhxrUb+beeOta/QNXEnnVXJNDY2zLoTv6vSAVrxdzVSVfYKzoeKM0JHTnWsFK1CCdq4MWiPV0IaqxzDwakc/w+ODUbumFgl9FgJRymoxIGzocgZbfEWv7W4ZzQSzpFTJfnif5yPi5XitwLHMnRYeUNwpQp5MfyWYqIacgsJh+HqStb/8oD9lANakNY11rnQe6j4HWlpIG0zXKRRkAu6gmMpkEYJSUaI81LlKLeuUVpJpDKcV+KsEry4/GOFVYZamuOoIouvKq0v5EQOl3uU0G+M0A+lISiH4erK4mxF8f8YmYYhDcU=
*/