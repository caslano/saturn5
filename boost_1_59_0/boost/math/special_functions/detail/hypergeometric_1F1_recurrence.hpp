
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
  inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling);

  template <class T>
  struct hypergeometric_1F1_recurrence_a_coefficients
  {
    typedef boost::math::tuple<T, T, T> result_type;

    hypergeometric_1F1_recurrence_a_coefficients(const T& a, const T& b, const T& z):
    a(a), b(b), z(z)
    {
    }

    result_type operator()(std::intmax_t i) const
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

    result_type operator()(std::intmax_t i) const
    {
      const T bi = b + i;

      const T an = bi * (bi - 1);
      const T bn = bi * (1 - bi - z);
      const T cn = z * (bi - a);

      return boost::math::make_tuple(an, bn, cn);
    }

  private:
    const T a, b, z;
    hypergeometric_1F1_recurrence_b_coefficients& operator=(const hypergeometric_1F1_recurrence_b_coefficients&) = delete;
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

     result_type operator()(std::intmax_t i) const
     {
        const T bi = b + (i + N);
        const T bi_minus_1 = b + (i + N - 1);

        const T an = bi * bi_minus_1;
        const T bn = bi * (-bi_minus_1 - z);
        const T cn = z * (bi - a);

        return boost::math::make_tuple(an, bn, cn);
     }

  private:
     hypergeometric_1F1_recurrence_small_b_coefficients operator=(const hypergeometric_1F1_recurrence_small_b_coefficients&) = delete;
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

    result_type operator()(std::intmax_t i) const
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
    hypergeometric_1F1_recurrence_a_and_b_coefficients operator=(const hypergeometric_1F1_recurrence_a_and_b_coefficients&) = delete;
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

     result_type operator()(std::intmax_t i) const
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

     result_type operator()(std::intmax_t i) const
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

     result_type operator()(std::intmax_t i) const
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

     result_type operator()(std::intmax_t i) const
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
  inline T hypergeometric_1F1_backward_recurrence_for_negative_a(const T& a, const T& b, const T& z, const Policy& pol, const char* function, long long& log_scaling)
  {
    BOOST_MATH_STD_USING // modf, frexp, fabs, pow

    std::intmax_t integer_part = 0;
    T ak = modf(a, &integer_part);
    //
    // We need ak-1 positive to avoid infinite recursion below:
    //
    if (0 != ak)
    {
       ak += 2;
       integer_part -= 2;
    }

    if (-integer_part > static_cast<std::intmax_t>(policies::get_max_series_iterations<Policy>()))
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
       long long scaling1(0), scaling2(0);
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
  T hypergeometric_1F1_backwards_recursion_on_b_for_negative_a(const T& a, const T& b, const T& z, const Policy& pol, const char*, long long& log_scaling)
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

     BOOST_MATH_ASSERT(a < -1); // Not tested nor taken for -1 < a < 0

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
     if (b_shift > static_cast<std::intmax_t>(boost::math::policies::get_max_series_iterations<Policy>()))
        return hypergeometric_1F1_checked_series_impl(a, b, z, pol, log_scaling);

     if (a_shift > static_cast<std::intmax_t>(boost::math::policies::get_max_series_iterations<Policy>()))
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

     BOOST_MATH_ASSERT(leading_a_shift > 1);
     BOOST_MATH_ASSERT(a_b_shift + leading_a_shift + (a_b_shift == 0 ? 1 : 0) == a_shift);
     BOOST_MATH_ASSERT(a_b_shift + trailing_b_shift == b_shift);

     if ((trailing_b_shift == 0) && (fabs(b) < 0.5) && a_b_shift)
     {
        // Better to have the final recursion on b alone, otherwise we lose precision when b is very small:
        int diff = (std::min)(a_b_shift, 3);
        a_b_shift -= diff;
        leading_a_shift += diff;
        trailing_b_shift += diff;
     }

     T first, second;
     long long scale1(0), scale2(0);
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