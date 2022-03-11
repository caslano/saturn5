
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HYPERGEOMETRIC_1F1_RECURRENCE_HPP_
#define BOOST_HYPERGEOMETRIC_1F1_RECURRENCE_HPP_

#include <boost/math/special_functions/modf.hpp>
#include <boost/math/special_functions/next.hpp>

#include <boost/math/tools/recurrence.hpp>
#include <boost/math/special_functions/detail/hypergeometric_pFq_checked_series.hpp>

  namespace boost { namespace math { namespace detail {

  // forward declaration for initial values
  template <class T, class Policy>
  inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol);

  template <class T, class Policy>
  inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling);

  template <class T>
  struct hypergeometric_1F1_recurrence_a_coefficients
  {
    typedef boost::math::tuple<T, T, T> result_type;

    hypergeometric_1F1_recurrence_a_coefficients(const T& a, const T& b, const T& z):
    a(a), b(b), z(z)
    {
    }

    result_type operator()(boost::intmax_t i) const
    {
      const T ai = a + i;

      const T an = b - ai;
      const T bn = (2 * ai - b + z);
      const T cn = -ai;

      return boost::math::make_tuple(an, bn, cn);
    }

  private:
    const T a, b, z;
    hypergeometric_1F1_recurrence_a_coefficients operator=(const hypergeometric_1F1_recurrence_a_coefficients&);
  };

  template <class T>
  struct hypergeometric_1F1_recurrence_b_coefficients
  {
    typedef boost::math::tuple<T, T, T> result_type;

    hypergeometric_1F1_recurrence_b_coefficients(const T& a, const T& b, const T& z):
    a(a), b(b), z(z)
    {
    }

    result_type operator()(boost::intmax_t i) const
    {
      const T bi = b + i;

      const T an = bi * (bi - 1);
      const T bn = bi * (1 - bi - z);
      const T cn = z * (bi - a);

      return boost::math::make_tuple(an, bn, cn);
    }

  private:
    const T a, b, z;
    hypergeometric_1F1_recurrence_b_coefficients& operator=(const hypergeometric_1F1_recurrence_b_coefficients&);
  };
  //
  // for use when we're recursing to a small b:
  //
  template <class T>
  struct hypergeometric_1F1_recurrence_small_b_coefficients
  {
     typedef boost::math::tuple<T, T, T> result_type;

     hypergeometric_1F1_recurrence_small_b_coefficients(const T& a, const T& b, const T& z, int N) :
        a(a), b(b), z(z), N(N)
     {
     }

     result_type operator()(boost::intmax_t i) const
     {
        const T bi = b + (i + N);
        const T bi_minus_1 = b + (i + N - 1);

        const T an = bi * bi_minus_1;
        const T bn = bi * (-bi_minus_1 - z);
        const T cn = z * (bi - a);

        return boost::math::make_tuple(an, bn, cn);
     }

  private:
     hypergeometric_1F1_recurrence_small_b_coefficients operator=(const hypergeometric_1F1_recurrence_small_b_coefficients&);
     const T a, b, z;
     int N;
  };

  template <class T>
  struct hypergeometric_1F1_recurrence_a_and_b_coefficients
  {
    typedef boost::math::tuple<T, T, T> result_type;

    hypergeometric_1F1_recurrence_a_and_b_coefficients(const T& a, const T& b, const T& z, int offset = 0):
    a(a), b(b), z(z), offset(offset)
    {
    }

    result_type operator()(boost::intmax_t i) const
    {
      const T ai = a + (offset + i);
      const T bi = b + (offset + i);

      const T an = bi * (b + (offset + i - 1));
      const T bn = bi * (z - (b + (offset + i - 1)));
      const T cn = -ai * z;

      return boost::math::make_tuple(an, bn, cn);
    }

  private:
    const T a, b, z;
    int offset;
    hypergeometric_1F1_recurrence_a_and_b_coefficients operator=(const hypergeometric_1F1_recurrence_a_and_b_coefficients&);
  };
#if 0
  //
  // These next few recurrence relations are archived for future reference, some of them are novel, though all
  // are trivially derived from the existing well known relations:
  //
  // Recurrence relation for double-stepping on both a and b:
  // - b(b-1)(b-2) / (2-b+z) M(a-2,b-2,z) + [b(a-1)z / (2-b+z) + b(1-b+z) + abz(b+1) /(b+1)(z-b)] M(a,b,z) - a(a+1)z^2 / (b+1)(z-b) M(a+2,b+2,z)
  //
  template <class T>
  struct hypergeometric_1F1_recurrence_2a_and_2b_coefficients
  {
     typedef boost::math::tuple<T, T, T> result_type;

     hypergeometric_1F1_recurrence_2a_and_2b_coefficients(const T& a, const T& b, const T& z, int offset = 0) :
        a(a), b(b), z(z), offset(offset)
     {
     }

     result_type operator()(boost::intmax_t i) const
     {
        i *= 2;
        const T ai = a + (offset + i);
        const T bi = b + (offset + i);

        const T an = -bi * (b + (offset + i - 1)) * (b + (offset + i - 2)) / (-(b + (offset + i - 2)) + z);
        const T bn = bi * (a + (offset + i - 1)) * z / (z - (b + (offset + i - 2)))
           + bi * (z - (b + (offset + i - 1)))
           + ai * bi * z * (b + (offset + i + 1)) / ((b + (offset + i + 1)) * (z - bi));
        const T cn = -ai * (a + (offset + i + 1)) * z * z / ((b + (offset + i + 1)) * (z - bi));

        return boost::math::make_tuple(an, bn, cn);
     }

  private:
     const T a, b, z;
     int offset;
     hypergeometric_1F1_recurrence_2a_and_2b_coefficients operator=(const hypergeometric_1F1_recurrence_2a_and_2b_coefficients&);
  };

  //
  // Recurrence relation for double-stepping on a:
  // -(b-a)(1 + b - a)/(2a-2-b+z)M(a-2,b,z)  + [(b-a)(a-1)/(2a-2-b+z) + (2a-b+z) + a(b-a-1)/(2a+2-b+z)]M(a,b,z)   -a(a+1)/(2a+2-b+z)M(a+2,b,z)
  //
  template <class T>
  struct hypergeometric_1F1_recurrence_2a_coefficients
  {
     typedef boost::math::tuple<T, T, T> result_type;

     hypergeometric_1F1_recurrence_2a_coefficients(const T& a, const T& b, const T& z, int offset = 0) :
        a(a), b(b), z(z), offset(offset)
     {
     }

     result_type operator()(boost::intmax_t i) const
     {
        i *= 2;
        const T ai = a + (offset + i);
        // -(b-a)(1 + b - a)/(2a-2-b+z)
        const T an = -(b - ai) * (b - (a + (offset + i - 1))) / (2 * (a + (offset + i - 1)) - b + z);
        const T bn = (b - ai) * (a + (offset + i - 1)) / (2 * (a + (offset + i - 1)) - b + z) + (2 * ai - b + z) + ai * (b - (a + (offset + i + 1))) / (2 * (a + (offset + i + 1)) - b + z);
        const T cn = -ai * (a + (offset + i + 1)) / (2 * (a + (offset + i + 1)) - b + z);

        return boost::math::make_tuple(an, bn, cn);
     }

  private:
     const T a, b, z;
     int offset;
     hypergeometric_1F1_recurrence_2a_coefficients operator=(const hypergeometric_1F1_recurrence_2a_coefficients&);
  };

  //
  // Recurrence relation for double-stepping on b:
  // b(b-1)^2(b-2)/((1-b)(2-b-z)) M(a,b-2,z)  + [zb(b-1)(b-1-a)/((1-b)(2-b-z)) + b(1-b-z) + z(b-a)(b+1)b/((b+1)(b+z)) ] M(a,b,z) + z^2(b-a)(b+1-a)/((b+1)(b+z)) M(a,b+2,z)
  //
  template <class T>
  struct hypergeometric_1F1_recurrence_2b_coefficients
  {
     typedef boost::math::tuple<T, T, T> result_type;

     hypergeometric_1F1_recurrence_2b_coefficients(const T& a, const T& b, const T& z, int offset = 0) :
        a(a), b(b), z(z), offset(offset)
     {
     }

     result_type operator()(boost::intmax_t i) const
     {
        i *= 2;
        const T bi = b + (offset + i);
        const T bi_m1 = b + (offset + i - 1);
        const T bi_p1 = b + (offset + i + 1);
        const T bi_m2 = b + (offset + i - 2);

        const T an = bi * (bi_m1) * (bi_m1) * (bi_m2) / (-bi_m1 * (-bi_m2 - z));
        const T bn = z * bi * bi_m1 * (bi_m1 - a) / (-bi_m1 * (-bi_m2 - z)) + bi * (-bi_m1 - z) + z * (bi - a) * bi_p1 * bi / (bi_p1 * (bi + z));
        const T cn = z * z * (bi - a) * (bi_p1 - a) / (bi_p1 * (bi + z));

        return boost::math::make_tuple(an, bn, cn);
     }

  private:
     const T a, b, z;
     int offset;
     hypergeometric_1F1_recurrence_2b_coefficients operator=(const hypergeometric_1F1_recurrence_2b_coefficients&);
  };

  //
  // Recurrence relation for a+ b-:
  // -z(b-a)(a-1-b)/(b(a-1+z)) M(a-1,b+1,z) + [(b-a)(a-1)b/(b(a-1+z)) + (2a-b+z) + a(b-a-1)/(a+z)] M(a,b,z) + a(1-b)/(a+z) M(a+1,b-1,z)
  //
  // This is potentially the most useful of these novel recurrences.
  //              -                                      -                  +        -                           +
  template <class T>
  struct hypergeometric_1F1_recurrence_a_plus_b_minus_coefficients
  {
     typedef boost::math::tuple<T, T, T> result_type;

     hypergeometric_1F1_recurrence_a_plus_b_minus_coefficients(const T& a, const T& b, const T& z, int offset = 0) :
        a(a), b(b), z(z), offset(offset)
     {
     }

     result_type operator()(boost::intmax_t i) const
     {
        const T ai = a + (offset + i);
        const T bi = b - (offset + i);

        const T an = -z * (bi - ai) * (ai - 1 - bi) / (bi * (ai - 1 + z));
        const T bn = z * ((-1 / (ai + z) - 1 / (ai + z - 1)) * (bi + z - 1) + 3) + bi - 1;
        const T cn = ai * (1 - bi) / (ai + z);

        return boost::math::make_tuple(an, bn, cn);
     }

  private:
     const T a, b, z;
     int offset;
     hypergeometric_1F1_recurrence_a_plus_b_minus_coefficients operator=(const hypergeometric_1F1_recurrence_a_plus_b_minus_coefficients&);
  };
#endif

  template <class T, class Policy>
  inline T hypergeometric_1F1_backward_recurrence_for_negative_a(const T& a, const T& b, const T& z, const Policy& pol, const char* function, int& log_scaling)
  {
    BOOST_MATH_STD_USING // modf, frexp, fabs, pow

    boost::intmax_t integer_part = 0;
    T ak = modf(a, &integer_part);
    //
    // We need ak-1 positive to avoid infinite recursion below:
    //
    if (0 != ak)
    {
       ak += 2;
       integer_part -= 2;
    }

    if (-integer_part > static_cast<boost::intmax_t>(policies::get_max_series_iterations<Policy>()))
       return policies::raise_evaluation_error<T>(function, "1F1 arguments sit in a range with a so negative that we have no evaluation method, got a = %1%", std::numeric_limits<T>::quiet_NaN(), pol);

    T first, second;
    if(ak == 0)
    { 
       first = 1;
       ak -= 1;
       second = 1 - z / b;
    }
    else
    {
       int scaling1(0), scaling2(0);
       first = detail::hypergeometric_1F1_imp(ak, b, z, pol, scaling1);
       ak -= 1;
       second = detail::hypergeometric_1F1_imp(ak, b, z, pol, scaling2);
       if (scaling1 != scaling2)
       {
          second *= exp(T(scaling2 - scaling1));
       }
       log_scaling += scaling1;
    }
    ++integer_part;

    detail::hypergeometric_1F1_recurrence_a_coefficients<T> s(ak, b, z);

    return tools::apply_recurrence_relation_backward(s,
                                                     static_cast<unsigned int>(std::abs(integer_part)),
                                                     first,
                                                     second, &log_scaling);
  }


  template <class T, class Policy>
  T hypergeometric_1F1_backwards_recursion_on_b_for_negative_a(const T& a, const T& b, const T& z, const Policy& pol, const char*, int& log_scaling)
  {
     using std::swap;
     BOOST_MATH_STD_USING // modf, frexp, fabs, pow
     //
     // We compute 
     //
     // M[a + a_shift, b + b_shift; z] 
     //
     // and recurse backwards on a and b down to
     //
     // M[a, b, z]
     //
     // With a + a_shift > 1 and b + b_shift > z
     // 
     // There are 3 distinct regions to ensure stability during the recursions:
     //
     // a > 0         :  stable for backwards on a
     // a < 0, b > 0  :  stable for backwards on a and b
     // a < 0, b < 0  :  stable for backwards on b (as long as |b| is small). 
     // 
     // We could simplify things by ignoring the middle region, but it's more efficient
     // to recurse on a and b together when we can.
     //

     BOOST_ASSERT(a < -1); // Not tested nor taken for -1 < a < 0

     int b_shift = itrunc(z - b) + 2;

     int a_shift = itrunc(-a);
     if (a + a_shift != 0)
     {
        a_shift += 2;
     }
     //
     // If the shifts are so large that we would throw an evaluation_error, try the series instead,
     // even though this will almost certainly throw as well:
     //
     if (b_shift > static_cast<boost::intmax_t>(boost::math::policies::get_max_series_iterations<Policy>()))
        return hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);

     if (a_shift > static_cast<boost::intmax_t>(boost::math::policies::get_max_series_iterations<Policy>()))
        return hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);

     int a_b_shift = b < 0 ? itrunc(b + b_shift) : b_shift;   // The max we can shift on a and b together
     int leading_a_shift = (std::min)(3, a_shift);        // Just enough to make a negative
     if (a_b_shift > a_shift - 3)
     {
        a_b_shift = a_shift < 3 ? 0 : a_shift - 3;
     }
     else
     {
        // Need to ensure that leading_a_shift is large enough that a will reach it's target
        // after the first 2 phases (-,0) and (-,-) are over:
        leading_a_shift = a_shift - a_b_shift;
     }
     int trailing_b_shift = b_shift - a_b_shift;
     if (a_b_shift < 5)
     {
        // Might as well do things in two steps rather than 3:
        if (a_b_shift > 0)
        {
           leading_a_shift += a_b_shift;
           trailing_b_shift += a_b_shift;
        }
        a_b_shift = 0;
        --leading_a_shift;
     }

     BOOST_ASSERT(leading_a_shift > 1);
     BOOST_ASSERT(a_b_shift + leading_a_shift + (a_b_shift == 0 ? 1 : 0) == a_shift);
     BOOST_ASSERT(a_b_shift + trailing_b_shift == b_shift);

     if ((trailing_b_shift == 0) && (fabs(b) < 0.5) && a_b_shift)
     {
        // Better to have the final recursion on b alone, otherwise we lose precision when b is very small:
        int diff = (std::min)(a_b_shift, 3);
        a_b_shift -= diff;
        leading_a_shift += diff;
        trailing_b_shift += diff;
     }

     T first, second;
     int scale1(0), scale2(0);
     first = boost::math::detail::hypergeometric_1F1_imp(T(a + a_shift), T(b + b_shift), z, pol, scale1);
     //
     // It would be good to compute "second" from first and the ratio - unfortunately we are right on the cusp
     // recursion on a switching from stable backwards to stable forwards behaviour and so this is not possible here.
     //
     second = boost::math::detail::hypergeometric_1F1_imp(T(a + a_shift - 1), T(b + b_shift), z, pol, scale2);
     if (scale1 != scale2)
        second *= exp(T(scale2 - scale1));
     log_scaling += scale1;

     //
     // Now we have [a + a_shift, b + b_shift, z] and [a + a_shift - 1, b + b_shift, z]
     // and want to recurse until [a + a_shift - leading_a_shift, b + b_shift, z] and [a + a_shift - leadng_a_shift - 1, b + b_shift, z]
     // which is leading_a_shift -1 steps.
     //
     second = boost::math::tools::apply_recurrence_relation_backward(
        hypergeometric_1F1_recurrence_a_coefficients<T>(a + a_shift - 1, b + b_shift, z), 
        leading_a_shift, first, second, &log_scaling, &first);

     if (a_b_shift)
     {
        //
        // Now we need to switch to an a+b shift so that we have:
        // [a + a_shift - leading_a_shift, b + b_shift, z] and [a + a_shift - leadng_a_shift - 1, b + b_shift - 1, z]
        // A&S 13.4.3 gives us what we need:
        //
        {
           // local a's and b's:
           T la = a + a_shift - leading_a_shift - 1;
           T lb = b + b_shift;
           second = ((1 + la - lb) * second - la * first) / (1 - lb);
        }
        //
        // Now apply a_b_shift - 1 recursions to get down to
        // [a + 1, b + trailing_b_shift + 1, z] and [a, b + trailing_b_shift, z]
        //
        second = boost::math::tools::apply_recurrence_relation_backward(
           hypergeometric_1F1_recurrence_a_and_b_coefficients<T>(a, b + b_shift - a_b_shift, z, a_b_shift - 1),
           a_b_shift - 1, first, second, &log_scaling, &first);
        //
        // Now we need to switch to a b shift, a different application of A&S 13.4.3
        // will get us there, we leave "second" where it is, and move "first" sideways:
        //
        {
           T lb = b + trailing_b_shift + 1;
           first = (second * (lb - 1) - a * first) / -(1 + a - lb);
        }
     }
     else
     {
        //
        // We have M[a+1, b+b_shift, z] and M[a, b+b_shift, z] and need M[a, b+b_shift-1, z] for
        // recursion on b: A&S 13.4.3 gives us what we need.
        //
        T third = -(second * (1 + a - b - b_shift) - first * a) / (b + b_shift - 1);
        swap(first, second);
        swap(second, third);
        --trailing_b_shift;
     }
     //
     // Finish off by applying trailing_b_shift recursions:
     //
     if (trailing_b_shift)
     {
        second = boost::math::tools::apply_recurrence_relation_backward(
           hypergeometric_1F1_recurrence_small_b_coefficients<T>(a, b, z, trailing_b_shift), 
           trailing_b_shift, first, second, &log_scaling);
     }
     return second;
  }



  } } } // namespaces

#endif // BOOST_HYPERGEOMETRIC_1F1_RECURRENCE_HPP_

/* hypergeometric_1F1_recurrence.hpp
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
*/