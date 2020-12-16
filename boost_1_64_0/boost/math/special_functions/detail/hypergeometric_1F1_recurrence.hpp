
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
OH0rtor2l/g8sXLDGO58gGO1o8xR6T5YeeAFsOSL+S9YiIk/qb1JsA8+O5HDae/9NywmTuv3YjxpLvWszphlRdu5ozOTqDOYPmMdyzQjvoPjtM8zxojroLtaAcSYgngOHreMM+M4TlK8DWPU+A22T1nuOR6t2+tKud+Zdk4odrTzCw3LqsRYK59Rx6V+7pLHkZ6Wmt2AdKmGyXahBr0h74+Y9Mlo92JCKfeVGOVBtcTnSm+7UEDP9gh7oAanyt025/W0DJXDa5k9lqOi2LwJ7U9euhiH1gqld4HzLYrfm5DO4PQKzxSf0+nbrOuVGEADw7qe92/O307BbIuZFcy8hyr3p/DcyeeWlf1G59tcH2v+yw4KDUlH7YfFwyi0l/Mdxipyp9kPe8UYTEl5p70Yx8dboIzXybFKf8OqdofsNp4LhIz3u1LTs1249DmDjrYu7Tfz+US5S05b0plS7NLe3hsKcBlmi3zGb9QxnIzTp/d6uR5yeUy872FeMc30u2h2q+94fId4cTcpM+uAtEX7El+1MHJx2D6RGRXdHvf70teKsRKGmo7mDwuboU5QhBBj9/bB4geOQ9kP+/CdzkC+Izhl/+r3GK8EGuV22YB0zteKcJiurKWy578flpfjvWXEO1+fg6dbRpmJ9mmKebDBZVtz/O/7SBZQCNimP8c0jt9V72k7y3TleBXraosORPVNb9YrqKfpMZAl8rHymELTMdtZBFKPMKzj5IhjPcjpuJcxMKwH+S0gHi+qh4PvcFDTmDMXLv3y6oyheUzMqc4SyZWKsee6Eel/NT+e6wZkm6p0a/7iNbRzWQVnzzd8z4uGs2PFnVNMxzjnh5IsME2NcWYb4aMsCzwvdne2x9yP6ccKMCiVpENZj3M9cFLQzonYOFb46tz13WIcTwzcjqnabzvj8Wgy6ymnSnjdeHtuC5pNlXY+U0CHZPiMGce8Yyy4jPsm+tLnmS6WIzgk+A5wk97rEm1P6WPc+RgQjfuQPFNkS9/BpMlZiWNMrlZIN26kZl+w8xlq986MT/zwmY1iunXHzdnPFuPQDue3Rj6n4OwTRmxTqTjtdI+T0J7F51XMifwusjxP7scvGDiZEJcptelqFdnGsXBqFTm9C8U4XEYoa1W+V+Lk3fiNveN8Z+XVdfpE/OBdfsqvGDcGoervOkrbX6IQB+9ewxJBvZflkhZuowMvS8BV04S5YGGyim72lfipSxVhKD9+N8bGYR3ZBnAubWOmWCx1/Xb+ChYO1Mm0p93FciUTQ2/tS+0PkBPLiF2ag8WXpUY7k40enlXmGOxY45n2u/nLwKMJ1v4E9UliYdU+HlGfpBbO6pN1C2O342kbU9yOFs5ux737W5i57Xjaws5vR6rzdZTxoe4mqm9nqxh+57FL9S2i89DeojncxvEugho7dN1iHO8k8F7R2SKsYfedyt6CeIDyTsQu7Ysw7e4HkEbvOYcZLUriKpDYjkQefniC0ztLNEpwl9bMP72soLWnWx24A6XtBy3cPhaWjnqX4aUvIXCd5ewxezxLzrEO7seQ3s/oQbzWDFa81cBX4hR0jPXe9elP6fTWKjxiWnVWib589ZxeDWJIPZJXBhC/c9Vr5PQw9XwfXhhrOQ7znyugt+Myvyf+wisL+nGgp0ca8kmSFq09X8S0bKurIRqI43heXECXSfCcu6Rgdo7DugAg2ptdNh2TYP/9uTfINugCBh6NhgqILiuvhOkq3E2k3BPuHmNcK+wmkxWpf0KaY3Q6LOnk4qu8NYKHkZW96r1i3NRR7/JYviRjoN9K4Sr2HWP2TEwzRQhjThPGkqENsjcMDApC+IDAXw1BFsj+LMZhntxvzt10XOgdzDE=
*/