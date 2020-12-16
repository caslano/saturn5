//  (C) Copyright Nick Thompson 2017.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CHEBYSHEV_HPP
#define BOOST_MATH_SPECIAL_CHEBYSHEV_HPP
#include <cmath>
#include <boost/math/constants/constants.hpp>

#if (__cplusplus > 201103) || (defined(_CPPLIB_VER) && (_CPPLIB_VER >= 610))
#  define BOOST_MATH_CHEB_USE_STD_ACOSH
#endif

#ifndef BOOST_MATH_CHEB_USE_STD_ACOSH
#  include <boost/math/special_functions/acosh.hpp>
#endif

namespace boost { namespace math {

template<class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type chebyshev_next(T1 const & x, T2 const & Tn, T3 const & Tn_1)
{
    return 2*x*Tn - Tn_1;
}

namespace detail {

template<class Real, bool second>
inline Real chebyshev_imp(unsigned n, Real const & x)
{
#ifdef BOOST_MATH_CHEB_USE_STD_ACOSH
    using std::acosh;
#else
   using boost::math::acosh;
#endif
    using std::cosh;
    using std::pow;
    using std::sqrt;
    Real T0 = 1;
    Real T1;
    if (second)
    {
        if (x > 1 || x < -1)
        {
            Real t = sqrt(x*x -1);
            return static_cast<Real>((pow(x+t, (int)(n+1)) - pow(x-t, (int)(n+1)))/(2*t));
        }
        T1 = 2*x;
    }
    else
    {
        if (x > 1)
        {
            return cosh(n*acosh(x));
        }
        if (x < -1)
        {
            if (n & 1)
            {
                return -cosh(n*acosh(-x));
            }
            else
            {
                return cosh(n*acosh(-x));
            }
        }
        T1 = x;
    }

    if (n == 0)
    {
        return T0;
    }

    unsigned l = 1;
    while(l < n)
    {
       std::swap(T0, T1);
       T1 = boost::math::chebyshev_next(x, T0, T1);
       ++l;
    }
    return T1;
}
} // namespace detail

template <class Real, class Policy>
inline typename tools::promote_args<Real>::type
chebyshev_t(unsigned n, Real const & x, const Policy&)
{
   typedef typename tools::promote_args<Real>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::chebyshev_imp<value_type, false>(n, static_cast<value_type>(x)), "boost::math::chebyshev_t<%1%>(unsigned, %1%)");
}

template<class Real>
inline typename tools::promote_args<Real>::type chebyshev_t(unsigned n, Real const & x)
{
    return chebyshev_t(n, x, policies::policy<>());
}

template <class Real, class Policy>
inline typename tools::promote_args<Real>::type
chebyshev_u(unsigned n, Real const & x, const Policy&)
{
   typedef typename tools::promote_args<Real>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::chebyshev_imp<value_type, true>(n, static_cast<value_type>(x)), "boost::math::chebyshev_u<%1%>(unsigned, %1%)");
}

template<class Real>
inline typename tools::promote_args<Real>::type chebyshev_u(unsigned n, Real const & x)
{
    return chebyshev_u(n, x, policies::policy<>());
}

template <class Real, class Policy>
inline typename tools::promote_args<Real>::type
chebyshev_t_prime(unsigned n, Real const & x, const Policy&)
{
   typedef typename tools::promote_args<Real>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   if (n == 0)
   {
      return result_type(0);
   }
   return policies::checked_narrowing_cast<result_type, Policy>(n * detail::chebyshev_imp<value_type, true>(n - 1, static_cast<value_type>(x)), "boost::math::chebyshev_t_prime<%1%>(unsigned, %1%)");
}

template<class Real>
inline typename tools::promote_args<Real>::type chebyshev_t_prime(unsigned n, Real const & x)
{
   return chebyshev_t_prime(n, x, policies::policy<>());
}

/*
 * This is Algorithm 3.1 of
 * Gil, Amparo, Javier Segura, and Nico M. Temme.
 * Numerical methods for special functions.
 * Society for Industrial and Applied Mathematics, 2007.
 * https://www.siam.org/books/ot99/OT99SampleChapter.pdf
 * However, our definition of c0 differs by a factor of 1/2, as stated in the docs. . .
 */
template<class Real, class T2>
inline Real chebyshev_clenshaw_recurrence(const Real* const c, size_t length, const T2& x)
{
    using boost::math::constants::half;
    if (length < 2)
    {
        if (length == 0)
        {
            return 0;
        }
        return c[0]/2;
    }
    Real b2 = 0;
    Real b1 = c[length -1];
    for(size_t j = length - 2; j >= 1; --j)
    {
        Real tmp = 2*x*b1 - b2 + c[j];
        b2 = b1;
        b1 = tmp;
    }
    return x*b1 - b2 + half<Real>()*c[0];
}


}}
#endif

/* chebyshev.hpp
jjKNn3sptM847qdy3477e0m7h7jDnp7/1tv+DbmXhP65vwB/vEcO8k7IyXxNfExSSz/H6Xvp+15rGM/6Hz7JYyXwg8jn4//cr+U9eUX8jLgiPjgfAz/7TPAcUC7R8w/qj90fVT0hesl3Hmed9dApyS90n2J/RX76VbHeyMegt/62H3lj/Fb6qEB8PYoc1C8IjlzkRWhX0Z96A8FpqZcGTj0xfnqG9XC2Wvg+Uv2wH/+OA/5M/hI5yPdCD/7QI/lQ9M/6n+fiBD71Y7XYgfumwBcIL3D8ATuNVX/kGGu/+lD90Cf1NvA/Dv6on07gN2Mf7EleAj/6q/drw62nyfSj7lH90FeG58kz7I+Oz8rO38+jvgt67CexF99l+nX2/FdkP7rR52tb1R99pM9dRwtOm77/Sn0F8XVzAh/Muoz4HCg4crxv+Tj/QA8PO54/8bqJ+gPkJD6gm14X1XKdLvMv8r3v+YDvLXKSV2HcZMHRI99vxo2wvdn/4V9vCQ/+0cLrnp62Yy9azvW8/2KfBp4Ztit17/g1dbr4bfreXAueOd/yd6GL+mMX/h0F8Nxpf6GOF365j8t4/BA7ML/Rsv5EH0NMn/009MmXwC/5EuL9CMdlTz1jL/49AeykOMbvG73v81P2/8DZf6M39lfYL32+R74F//K/27Ckp+Wgfgd7sd/Ez0a5Pu98wfHTl5ynQE74Yv2FvEfTMu953lyUtMPwc/pvU74S+Zhn6Icf4ydLnWfkO4L/NrQfcT6EnOk8MHXPwLlvib1W2X+5X4demqjlmfsR6Lkb/bh3pWfsRP0B9qNOEH1c5fw98wl2Y32FHvBn5B7m/RTrQ+yhef1Y6JMvQi7yTejpbeTj/pHXh+RH0AffJ+xHPRNw5kv0TZ0u8YXfgH9o+VQt5lvy2vjZwY6nq83vWT7P72K9FgCnHlTjsfNHguPfpwqO/agXpT/1B8hBnSN6Jb9LfHGvCvwfC04c1jV/1yuOiFf0g96454d97laLvJPs34ssp/jep8e2fk++DryvOr4X2M+ZX+GPOmbsif9gn1vs9+SXkIc6FfARB/DNPSH45d4u/orf4idZiZ1HU4eLH5V4H+B13/GTvZ5t6HmD+hrk+Fn7avwwvW8Z7PqL5xxPnEfBZ/ocQfM97VzdS6uM3ZaaH/pBh/oSnrc6z/aA4OBVvjsXu6SA8/0XHDrMr7T3e1/BfQveN3bdMHwRH+z7iFPnd3JYx0Cf9R70OLfHzvCP31F/jp+wr4I+dRD40xy18D/E8zvfM+Sb5rirYD+/VON4r/ulB0B3huhC73mv836R3oivRx0v4MP+zMfEG/FL/5H26+skF/rowvdb9r3ecO5BYI+zyIPLXgdLbux0v/eP6AH99LJfFdGqH3kb9ENdJHx+LzhxSH00fJAfA868j5+PT+9LbY8dHrfG+w7OB4GTbwTvvY4r5mf0lc57vQRf7LOMl/vp6Pkd2zXD8UodN3r4VXDsvlb0eS4x/9+4vmi3nqHP/S7knuS8T/rfwWI9ij1WeN7PS/o17u19MHki/F353XLwiZ15T56Z8b/BP3Uhogde7odgh5sEhy/6o7ebJA/9H0zXGXnf+Q742RdKTvhtwjjqyf29rEbL99rzP/tI/FHr54rIM01w+BpvPX8OHu7L0491qFr871OvY66zfz2SwK/3eewPo5J2M3zDF+exyMP5K3bYmeCd8Jb37fAF3iLHFXkw9IV90ceHnr85R0C/nC/wnDL9tuiL+dh+XKQWepwDoj/wIyffA/wSu/HMuQvPrOvQD/eu0Od96o/eWI8TL6eAj/PcBH685tkc9M/6hGfwQ4/1BnxTN4weeI/eusAf58Bqkb+P6zw=
*/