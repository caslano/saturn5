//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CARDINAL_B_SPLINE_HPP
#define BOOST_MATH_SPECIAL_CARDINAL_B_SPLINE_HPP

#include <array>
#include <cmath>
#include <limits>
#include <type_traits>

namespace boost { namespace math {

namespace detail {

  template<class Real>
  inline Real B1(Real x)
  {
    if (x < 0)
    {
      return B1(-x);
    }
    if (x < Real(1))
    {
      return 1 - x;
    }
    return Real(0);
  }
}

template<unsigned n, typename Real>
Real cardinal_b_spline(Real x) {
    static_assert(!std::is_integral<Real>::value, "Does not work with integral types.");

    if (x < 0) {
        // All B-splines are even functions:
        return cardinal_b_spline<n, Real>(-x);
    }

    if  (n==0)
    {
        if (x < Real(1)/Real(2)) {
            return Real(1);
        }
        else if (x == Real(1)/Real(2)) {
            return Real(1)/Real(2);
        }
        else {
            return Real(0);
        }
    }

    if (n==1)
    {
        return detail::B1(x);
    }

    Real supp_max = (n+1)/Real(2);
    if (x >= supp_max)
    {
        return Real(0);
    }

    // Fill v with values of B1:
    // At most two of these terms are nonzero, and at least 1.
    // There is only one non-zero term when n is odd and x = 0.
    std::array<Real, n> v;
    Real z = x + 1 - supp_max;
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = detail::B1(z);
        z += 1;
    }

    Real smx = supp_max - x;
    for (unsigned j = 2; j <= n; ++j)
    {
        Real a = (j + 1 - smx);
        Real b = smx;
        for(unsigned k = 0; k <= n - j; ++k)
        {
            v[k] = (a*v[k+1] + b*v[k])/Real(j);
            a += 1;
            b -= 1;
        }
    }

    return v[0];
}


template<unsigned n, typename Real>
Real cardinal_b_spline_prime(Real x)
{
    static_assert(!std::is_integral<Real>::value, "Cardinal B-splines do not work with integer types.");

    if (x < 0)
    {
        // All B-splines are even functions, so derivatives are odd:
        return -cardinal_b_spline_prime<n, Real>(-x);
    }


    if (n==0)
    {
        // Kinda crazy but you get what you ask for!
        if (x == Real(1)/Real(2))
        {
            return std::numeric_limits<Real>::infinity();
        }
        else
        {
            return Real(0);
        }
    }

    if (n==1)
    {
        if (x==0)
        {
            return Real(0);
        }
        if (x==1)
        {
            return -Real(1)/Real(2);
        }
        return Real(-1);
    }


    Real supp_max = (n+1)/Real(2);
    if (x >= supp_max)
    {
        return Real(0);
    }

    // Now we want to evaluate B_{n}(x), but stop at the second to last step and collect B_{n-1}(x+1/2) and B_{n-1}(x-1/2):
    std::array<Real, n> v;
    Real z = x + 1 - supp_max;
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = detail::B1(z);
        z += 1;
    }

    Real smx = supp_max - x;
    for (unsigned j = 2; j <= n - 1; ++j)
    {
        Real a = (j + 1 - smx);
        Real b = smx;
        for(unsigned k = 0; k <= n - j; ++k)
        {
            v[k] = (a*v[k+1] + b*v[k])/Real(j);
            a += 1;
            b -= 1;
        }
    }

    return v[1] - v[0];
}


template<unsigned n, typename Real>
Real cardinal_b_spline_double_prime(Real x)
{
    static_assert(!std::is_integral<Real>::value, "Cardinal B-splines do not work with integer types.");
    static_assert(n >= 3, "n>=3 for second derivatives of cardinal B-splines is required.");

    if (x < 0)
    {
        // All B-splines are even functions, so second derivatives are even:
        return cardinal_b_spline_double_prime<n, Real>(-x);
    }


    Real supp_max = (n+1)/Real(2);
    if (x >= supp_max)
    {
        return Real(0);
    }

    // Now we want to evaluate B_{n}(x), but stop at the second to last step and collect B_{n-1}(x+1/2) and B_{n-1}(x-1/2):
    std::array<Real, n> v;
    Real z = x + 1 - supp_max;
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = detail::B1(z);
        z += 1;
    }

    Real smx = supp_max - x;
    for (unsigned j = 2; j <= n - 2; ++j)
    {
        Real a = (j + 1 - smx);
        Real b = smx;
        for(unsigned k = 0; k <= n - j; ++k)
        {
            v[k] = (a*v[k+1] + b*v[k])/Real(j);
            a += 1;
            b -= 1;
        }
    }

    return v[2] - 2*v[1] + v[0];
}


template<unsigned n, class Real>
Real forward_cardinal_b_spline(Real x)
{
    static_assert(!std::is_integral<Real>::value, "Cardinal B-splines do not work with integral types.");
    return cardinal_b_spline<n>(x - (n+1)/Real(2));
}

}}
#endif

/* cardinal_b_spline.hpp
eT+x1nQnp/Ml2fJX9u2OH/L0yHW+14HHOG9DngL/2WL9pPNWnBOB7y/en94rOsjN+Rv2IW+C/qlPwr/TeftVpneM8zzEA/hYd6FH8uDokXN54oT6G+xQ7HwP+SrwMS8jZ0/1Qx+t/cy5P+/7229qWV/UIaJP8unY8yzzS50Yds1nHHVJjmu+a9jvcfilXtH561qVUjngx1/R32TBwcv+D/2fi7ys5/WMHIxjPH5A+zfvV8hzQedotejZ+upuvAMZh5347uDnQ9UCP9D7GO3naqBn5i349/nGpFuStv4z4GPfqPfIudfrer7TyOX+I6eJHnwyj6Hv8R7HPE8ckO9Frmmii7/95v2h55V5RcCph7U/t8lMNcKO1G/hd/gvdAd7Pq3qfGabpK3MuRT+drvpn6L+8JWeN/aqLoT2LT1DlzwFfvOu46me6irQz+Pehzxs/cI3+MjzMq6H16tLXb/E+SFysd6j3wZ/x6lbY/wir1vsH6upI0Qu1jPYiX0K8m+zXr9UC/7vaDm/976aOkLkzVOL3hs5DqgjRL8FasHTgpa4tB92paXeTS3+dZXnuYVeT1BHiNzklaFT6nikjhB+xzqeqSPk/WOOg5/1HvrU9SHPYO+v0CfvyXcRR+S3kece0YHPe5yPqSH60HnOfF1huzI/4Uf0gy7nIsiNX8FnJfk5/sq5Lnav5PWG/HU08lMniv96/tozTHgY96jg4HldcOz1tM8VyL/g55w74q/Iw/tj0q33XXxnkYv8H/7Cvg5//d5xP1LP6OMS88V5He3kpN15aQJfznkT/sA8RNyTp2H8FvRBHsZ12pwDIqfPfypvcJ0ZfoD9hqqF75FeD71pP92jFvnPch5svFrkmih8yJtej5NPgt7F8MV6nJY6IccZ9ZSMcx3sgorCQzxd7e/ggT7XeUXjoEMeF7nIP8FXtvXBeTxyHuE8H+dL4E/vH2/29/RtWtb1gsMn+gdO/o+4LvK81kF4eGbeYXxP++cdPgdvYT6oV0SvuwXnPc/4KfXLyEU9Gf5Ww/tx5k/0PURw9AA/6Ds9fxYJjryXCz/6uzMzVZP4IZ+APFXVop/zPL8+4vw23w/w/khL3a+/V3lq8dt6jqtmzntdq2f0ma5nHaZn6NdXC/4rba9flU/CH8nPo2/nu6erDiYbfO+pP/h/Eh/0G6uW+HvXzxu836EOGvm/ERy/utj7Qerx4Xdq+VQ5/P8m+8HT6o8/t3FctnOegLon/PAo0cXu1Ccw/ii9h2/Pz43e0zkx+lrh+nLmffCwzkRv5G/RD3UI2Jnx+FvqAMkr/VM/hD6Z97HnUOMhjw0fJd5P67d1PtV/tGIeZPwBtHpul9R9HQ9/+AH44ZtzZOK6wHnpvjqPQ07yWPgTeTb8hfME/DTN10TX0z9t/1ytFj5Kfa6OPDyTpwV/hr//bzlfRT4GvZNnJU6ot8EezKPo8QPXv67ROOyXITzY3/uIy1/y+qbIci5WP+jdYr3AN/TI26CvR/1+HS31z2qh11X90Af5E/qVqj96cD52+kD7STuvx9m3EX/oEb3y3cYPh+kZPvqqP/xeYT94z3LPVIsfFep8Cn2cavlfS+BrqbvDj5mXoYN/owfqf4iLdY7bTrafz20mFeg9enredG+zX3XmPflP4OQZ7WcbnS/iGTxzvO88jf7ssxwf7K+xbzouKvic7CLdjwGO3sD3Ey3nYo5nvk/oUX6Yhb+QR8Ie2ebnFuenH5bc8LnHdO5UP+zK9w65+/o7Rl4K/tkXYoeqzud2Uj/g3dQP+Tkvxe/u9/hXNY7+twgO3TWCY5+L1B/6n1rvrR1vU/UePnKz9sXbevBhP6+PWs4VPug2sb7J7xE=
*/