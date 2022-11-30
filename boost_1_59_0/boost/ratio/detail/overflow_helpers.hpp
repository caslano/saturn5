//  ratio.hpp  ---------------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes
//  Copyright 2009 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*

This code was derived by Beman Dawes from Howard Hinnant's time2_demo prototype.
Many thanks to Howard for making his code available under the Boost license.
The original code was modified to conform to Boost conventions and to section
20.4 Compile-time rational arithmetic [ratio], of the C++ committee working
paper N2798.
See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2798.pdf.

time2_demo contained this comment:

    Much thanks to Andrei Alexandrescu,
                   Walter Brown,
                   Peter Dimov,
                   Jeff Garland,
                   Terry Golubiewski,
                   Daniel Krugler,
                   Anthony Williams.
*/

// The way overflow is managed for ratio_less is taken from llvm/libcxx/include/ratio

#ifndef BOOST_RATIO_DETAIL_RATIO_OPERATIONS_HPP
#define BOOST_RATIO_DETAIL_RATIO_OPERATIONS_HPP

#include <boost/ratio/config.hpp>
#include <boost/ratio/detail/mpl/abs.hpp>
#include <boost/ratio/detail/mpl/sign.hpp>
#include <cstdlib>
#include <climits>
#include <limits>
#include <boost/cstdint.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/integer_traits.hpp>

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
// boost/integer.hpp:77:30: warning: use of C99 long long integer constant
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

namespace boost
{

//----------------------------------------------------------------------------//
//                                 helpers                                    //
//----------------------------------------------------------------------------//

namespace ratio_detail
{

  template <boost::intmax_t X, boost::intmax_t Y, boost::intmax_t = mpl::sign_c<boost::intmax_t, Y>::value>
  class br_add;

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_add<X, Y, 1>
  {
      static const boost::intmax_t min = boost::integer_traits<boost::intmax_t>::const_min;
      static const boost::intmax_t max = boost::integer_traits<boost::intmax_t>::const_max;

      BOOST_RATIO_STATIC_ASSERT(X <= max - Y , BOOST_RATIO_OVERFLOW_IN_ADD, ());
  public:
      static const boost::intmax_t value = X + Y;
  };

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_add<X, Y, 0>
  {
  public:
      static const boost::intmax_t value = X;
  };

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_add<X, Y, -1>
  {
      static const boost::intmax_t min = boost::integer_traits<boost::intmax_t>::const_min;
      static const boost::intmax_t max = boost::integer_traits<boost::intmax_t>::const_max;

      BOOST_RATIO_STATIC_ASSERT(min - Y <= X, BOOST_RATIO_OVERFLOW_IN_ADD, ());
  public:
      static const boost::intmax_t value = X + Y;
  };

  template <boost::intmax_t X, boost::intmax_t Y, boost::intmax_t = mpl::sign_c<boost::intmax_t, Y>::value>
  class br_sub;

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_sub<X, Y, 1>
  {
      static const boost::intmax_t min = boost::integer_traits<boost::intmax_t>::const_min;
      static const boost::intmax_t max = boost::integer_traits<boost::intmax_t>::const_max;

      BOOST_RATIO_STATIC_ASSERT(min + Y <= X, BOOST_RATIO_OVERFLOW_IN_SUB, ());
  public:
      static const boost::intmax_t value = X - Y;
  };

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_sub<X, Y, 0>
  {
  public:
      static const boost::intmax_t value = X;
  };

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_sub<X, Y, -1>
  {
      static const boost::intmax_t min = boost::integer_traits<boost::intmax_t>::const_min;
      static const boost::intmax_t max = boost::integer_traits<boost::intmax_t>::const_max;

      BOOST_RATIO_STATIC_ASSERT(X <= max + Y, BOOST_RATIO_OVERFLOW_IN_SUB, ());
  public:
      static const boost::intmax_t value = X - Y;
  };

  template <boost::intmax_t X, boost::intmax_t Y>
  class br_mul
  {
      static const boost::intmax_t nan =
          boost::intmax_t(BOOST_RATIO_UINTMAX_C(1) << (sizeof(boost::intmax_t) * CHAR_BIT - 1));
      static const boost::intmax_t min = boost::integer_traits<boost::intmax_t>::const_min;
      static const boost::intmax_t max = boost::integer_traits<boost::intmax_t>::const_max;

      static const boost::intmax_t a_x = mpl::abs_c<boost::intmax_t, X>::value;
      static const boost::intmax_t a_y = mpl::abs_c<boost::intmax_t, Y>::value;

      BOOST_RATIO_STATIC_ASSERT(X != nan, BOOST_RATIO_OVERFLOW_IN_MUL, ());
      BOOST_RATIO_STATIC_ASSERT(Y != nan, BOOST_RATIO_OVERFLOW_IN_MUL, ());
      BOOST_RATIO_STATIC_ASSERT(a_x <= max / a_y, BOOST_RATIO_OVERFLOW_IN_MUL, ());
  public:
      static const boost::intmax_t value = X * Y;
  };

  template <boost::intmax_t Y>
  class br_mul<0, Y>
  {
  public:
      static const boost::intmax_t value = 0;
  };

  template <boost::intmax_t X>
  class br_mul<X, 0>
  {
  public:
      static const boost::intmax_t value = 0;
  };

  template <>
  class br_mul<0, 0>
  {
  public:
      static const boost::intmax_t value = 0;
  };

  // Not actually used but left here in case needed in future maintenance
  template <boost::intmax_t X, boost::intmax_t Y>
  class br_div
  {
      static const boost::intmax_t nan = boost::intmax_t(BOOST_RATIO_UINTMAX_C(1) << (sizeof(boost::intmax_t) * CHAR_BIT - 1));
      static const boost::intmax_t min = boost::integer_traits<boost::intmax_t>::const_min;
      static const boost::intmax_t max = boost::integer_traits<boost::intmax_t>::const_max;

      BOOST_RATIO_STATIC_ASSERT(X != nan, BOOST_RATIO_OVERFLOW_IN_DIV, ());
      BOOST_RATIO_STATIC_ASSERT(Y != nan, BOOST_RATIO_OVERFLOW_IN_DIV, ());
      BOOST_RATIO_STATIC_ASSERT(Y != 0, BOOST_RATIO_DIVIDE_BY_0, ());
  public:
      static const boost::intmax_t value = X / Y;
  };

  // ratio arithmetic
  template <class R1, class R2> struct ratio_add;
  template <class R1, class R2> struct ratio_subtract;
  template <class R1, class R2> struct ratio_multiply;
  template <class R1, class R2> struct ratio_divide;

  template <class R1, class R2>
  struct ratio_add
  {
      //The nested typedef type shall be a synonym for ratio<T1, T2>::type where T1 has the value R1::num *
      //R2::den + R2::num * R1::den and T2 has the value R1::den * R2::den.
      // As the preceding doesn't works because of overflow on boost::intmax_t we need something more elaborated.
  private:
      static const boost::intmax_t gcd_n1_n2 = mpl::gcd_c<boost::intmax_t, R1::num, R2::num>::value;
      static const boost::intmax_t gcd_d1_d2 = mpl::gcd_c<boost::intmax_t, R1::den, R2::den>::value;
  public:
      // No need to normalize as ratio_multiply is already normalized
      typedef typename ratio_multiply
         <
             ratio<gcd_n1_n2, R1::den / gcd_d1_d2>,
             ratio
             <
                 boost::ratio_detail::br_add
                 <
                     boost::ratio_detail::br_mul<R1::num / gcd_n1_n2, R2::den / gcd_d1_d2>::value,
                     boost::ratio_detail::br_mul<R2::num / gcd_n1_n2, R1::den / gcd_d1_d2>::value
                 >::value,
                 R2::den
             >
         >::type type;
  };
  template <class R, boost::intmax_t D>
  struct ratio_add<R, ratio<0,D> >
  {
    typedef R type;
  };

  template <class R1, class R2>
  struct ratio_subtract
  {
      //The nested typedef type shall be a synonym for ratio<T1, T2>::type where T1 has the value
      // R1::num *R2::den - R2::num * R1::den and T2 has the value R1::den * R2::den.
      // As the preceding doesn't works because of overflow on boost::intmax_t we need something more elaborated.
  private:
      static const boost::intmax_t gcd_n1_n2 = mpl::gcd_c<boost::intmax_t, R1::num, R2::num>::value;
      static const boost::intmax_t gcd_d1_d2 = mpl::gcd_c<boost::intmax_t, R1::den, R2::den>::value;
  public:
      // No need to normalize as ratio_multiply is already normalized
      typedef typename ratio_multiply
         <
             ratio<gcd_n1_n2, R1::den / gcd_d1_d2>,
             ratio
             <
                 boost::ratio_detail::br_sub
                 <
                     boost::ratio_detail::br_mul<R1::num / gcd_n1_n2, R2::den / gcd_d1_d2>::value,
                     boost::ratio_detail::br_mul<R2::num / gcd_n1_n2, R1::den / gcd_d1_d2>::value
                 >::value,
                 R2::den
             >
         >::type type;
  };

  template <class R, boost::intmax_t D>
  struct ratio_subtract<R, ratio<0,D> >
  {
    typedef R type;
  };

  template <class R1, class R2>
  struct ratio_multiply
  {
      // The nested typedef type  shall be a synonym for ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>::type.
      // As the preceding doesn't works because of overflow on boost::intmax_t we need something more elaborated.
  private:
     static const boost::intmax_t gcd_n1_d2 = mpl::gcd_c<boost::intmax_t, R1::num, R2::den>::value;
     static const boost::intmax_t gcd_d1_n2 = mpl::gcd_c<boost::intmax_t, R1::den, R2::num>::value;
  public:
      typedef typename ratio
         <
             boost::ratio_detail::br_mul<R1::num / gcd_n1_d2, R2::num / gcd_d1_n2>::value,
             boost::ratio_detail::br_mul<R2::den / gcd_n1_d2, R1::den / gcd_d1_n2>::value
         >::type type;
  };

  template <class R1, class R2>
  struct ratio_divide
  {
      // The nested typedef type  shall be a synonym for ratio<R1::num * R2::den, R2::num * R1::den>::type.
      // As the preceding doesn't works because of overflow on boost::intmax_t we need something more elaborated.
  private:
      static const boost::intmax_t gcd_n1_n2 = mpl::gcd_c<boost::intmax_t, R1::num, R2::num>::value;
      static const boost::intmax_t gcd_d1_d2 = mpl::gcd_c<boost::intmax_t, R1::den, R2::den>::value;
  public:
      typedef typename ratio
         <
             boost::ratio_detail::br_mul<R1::num / gcd_n1_n2, R2::den / gcd_d1_d2>::value,
             boost::ratio_detail::br_mul<R2::num / gcd_n1_n2, R1::den / gcd_d1_d2>::value
         >::type type;
  };
  template <class R1, class R2>
  struct is_evenly_divisible_by
  {
  private:
      static const boost::intmax_t gcd_n1_n2 = mpl::gcd_c<boost::intmax_t, R1::num, R2::num>::value;
      static const boost::intmax_t gcd_d1_d2 = mpl::gcd_c<boost::intmax_t, R1::den, R2::den>::value;
  public:
      typedef integral_constant<bool,
             ((R2::num / gcd_n1_n2 ==1) && (R1::den / gcd_d1_d2)==1)
      > type;
  };

  template <class T>
  struct is_ratio : public boost::false_type
  {};
  template <boost::intmax_t N, boost::intmax_t D>
  struct is_ratio<ratio<N, D> > : public boost::true_type
  {};

  template <class R1, class R2,
            boost::intmax_t Q1 = R1::num / R1::den, boost::intmax_t M1 = R1::num % R1::den,
            boost::intmax_t Q2 = R2::num / R2::den, boost::intmax_t M2 = R2::num % R2::den>
  struct ratio_less1
  {
    static const bool value = Q1 < Q2;
  };

  template <class R1, class R2, boost::intmax_t Q>
  struct ratio_less1<R1, R2, Q, 0, Q, 0>
  {
    static const bool value = false;
  };

  template <class R1, class R2, boost::intmax_t Q, boost::intmax_t M2>
  struct ratio_less1<R1, R2, Q, 0, Q, M2>
  {
    static const bool value = true;
  };

  template <class R1, class R2, boost::intmax_t Q, boost::intmax_t M1>
  struct ratio_less1<R1, R2, Q, M1, Q, 0>
  {
    static const bool value = false;
  };

  template <class R1, class R2, boost::intmax_t Q, boost::intmax_t M1, boost::intmax_t M2>
  struct ratio_less1<R1, R2, Q, M1, Q, M2>
  {
    static const bool value = ratio_less1<ratio<R2::den, M2>, ratio<R1::den, M1>
                                            >::value;
  };

  template <
      class R1,
      class R2,
      boost::intmax_t S1 = mpl::sign_c<boost::intmax_t, R1::num>::value,
    boost::intmax_t S2 = mpl::sign_c<boost::intmax_t, R2::num>::value
>
  struct ratio_less
  {
      static const bool value = S1 < S2;
  };

  template <class R1, class R2>
  struct ratio_less<R1, R2, 1LL, 1LL>
  {
      static const bool value = ratio_less1<R1, R2>::value;
  };

  template <class R1, class R2>
  struct ratio_less<R1, R2, -1LL, -1LL>
  {
      static const bool value = ratio_less1<ratio<-R2::num, R2::den>,
                                            ratio<-R1::num, R1::den> >::value;
  };


}  // namespace ratio_detail

}  // namespace boost

#endif  // BOOST_RATIO_HPP

/* overflow_helpers.hpp
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
*/