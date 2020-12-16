// Copyright John Maddock 2012.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HANKEL_HPP
#define BOOST_MATH_HANKEL_HPP

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/bessel.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
std::complex<T> hankel_imp(T v, T x, const bessel_no_int_tag&, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::cyl_hankel_1<%1%>(%1%,%1%)";

   if(x < 0)
   {
      bool isint_v = floor(v) == v;
      T j, y;
      bessel_jy(v, -x, &j, &y, need_j | need_y, pol);
      std::complex<T> cx(x), cv(v);
      std::complex<T> j_result, y_result;
      if(isint_v)
      {
         int s = (iround(v) & 1) ? -1 : 1;
         j_result = j * s;
         y_result = T(s) * (y - (2 / constants::pi<T>()) * (log(-x) - log(cx)) * j);
      }
      else
      {
         j_result = pow(cx, v) * pow(-cx, -v) * j;
         T p1 = pow(-x, v);
         std::complex<T> p2 = pow(cx, v);
         y_result = p1 * y / p2
            + (p2 / p1 - p1 / p2) * j / tan(constants::pi<T>() * v);
      }
      // multiply y_result by i:
      y_result = std::complex<T>(-sign * y_result.imag(), sign * y_result.real());
      return j_result + y_result;
   }

   if(x == 0)
   {
      if(v == 0)
      {
         // J is 1, Y is -INF
         return std::complex<T>(1, sign * -policies::raise_overflow_error<T>(function, 0, pol));
      }
      else
      {
         // At least one of J and Y is complex infinity:
         return std::complex<T>(policies::raise_overflow_error<T>(function, 0, pol), sign * policies::raise_overflow_error<T>(function, 0, pol));
      }
   }

   T j, y;
   bessel_jy(v, x, &j, &y, need_j | need_y, pol);
   return std::complex<T>(j, sign * y);
}

template <class T, class Policy>
std::complex<T> hankel_imp(int v, T x, const bessel_int_tag&, const Policy& pol, int sign);

template <class T, class Policy>
inline std::complex<T> hankel_imp(T v, T x, const bessel_maybe_int_tag&, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING  // ADL of std names.
   int ival = detail::iconv(v, pol);
   if(0 == v - ival)
   {
      return hankel_imp(ival, x, bessel_int_tag(), pol, sign);
   }
   return hankel_imp(v, x, bessel_no_int_tag(), pol, sign);
}

template <class T, class Policy>
inline std::complex<T> hankel_imp(int v, T x, const bessel_int_tag&, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING
   if((std::abs(v) < 200) && (x > 0))
      return std::complex<T>(bessel_jn(v, x, pol), sign * bessel_yn(v, x, pol));
   return hankel_imp(static_cast<T>(v), x, bessel_no_int_tag(), pol, sign);
}

template <class T, class Policy>
inline std::complex<T> sph_hankel_imp(T v, T x, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING
   return constants::root_half_pi<T>() * hankel_imp(v + 0.5f, x, bessel_no_int_tag(), pol, sign) / sqrt(std::complex<T>(x));
}

} // namespace detail

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> cyl_hankel_1(T1 v, T2 x, const Policy& pol)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::hankel_imp<value_type>(v, static_cast<value_type>(x), tag_type(), pol, 1), "boost::math::cyl_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> cyl_hankel_1(T1 v, T2 x)
{
   return cyl_hankel_1(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> cyl_hankel_2(T1 v, T2 x, const Policy& pol)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::hankel_imp<value_type>(v, static_cast<value_type>(x), tag_type(), pol, -1), "boost::math::cyl_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> cyl_hankel_2(T1 v, T2 x)
{
   return cyl_hankel_2(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> sph_hankel_1(T1 v, T2 x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::sph_hankel_imp<value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy(), 1), "boost::math::sph_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> sph_hankel_1(T1 v, T2 x)
{
   return sph_hankel_1(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> sph_hankel_2(T1 v, T2 x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::sph_hankel_imp<value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy(), -1), "boost::math::sph_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> sph_hankel_2(T1 v, T2 x)
{
   return sph_hankel_2(v, x, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_HANKEL_HPP


/* hankel.hpp
dPVHp2svRI3Ltn1c7ep2jU/b1Z/oOk5RvV20Ve37i+b38/6h8ztT940Lz1R5FJny3WTeP7fFhFvyoOqPynnd77XXyfWqjyGd181TdH7mdbny+8ibNZ57j8Y9u7T3ja7HCrXDTT/Vee3RXkhPq599v9pPQHvSvdN8fvu12qNri+rx34vUHrSX3a5Jpj28w7y/cb72cpmjfvhc7b33XdWL6drb61n1E7qvvHS2+f28SvN6/pj2zlO/uK5CxzXf2ax68OIFJr2b79eeOrpOi3U/nP4lXceZGv/dUGyO/1zjlcfN687J2stL48HzP6w9Bp86S+Nf87mXvq55hdeU44GrTL52T1J/3W7eX/aMeX3ydO356lU51Gsv4WiRif9+ja9qLSb+u8zrZTr/2RmNH2Pas22Xxt9T1Q8qvweu1F7cq83vK9ZrT9xztGel3l+cMfGv1/1lwzL1r93mfPe2ak/AOboPa/w5+XmdzyXq/5NqD9qb+QHNG7e9qPvPPJvmTxoP6b7x0IDuE2u0l9AFGp/ntNe9Vdf/neZ1Xr8JP/ur2oPxixqHNJvzW/NN8/lD67UX5F3ql0a1h+xtGtfUm9/nz9R13K89od+j89mrcU2zrssbJpn2pPq4V+P/Tedp3KrrPy9iXp/+gs3UZ/WLU8evy8MmnTXbtWfRLoX/pPq1hPbOn6q9nSer3v7ZhJubm2LK6XMaHy/RXpOf0Z5Iw2oHDWr/79ZemxqnHbpTewXu0zznPOXzrRq3v8e8Ln5ce/Ot156NHzPvP31Qe4Tp+p/9iObDyue27bp/zjDxz16kfv2g9rhfqH75a+b85izVXl03mHQePKrrv0h71H3FhDt0htWcT4Wuf0TzpOvN9dto03Wu17hf47MNL+j9+7XH90KTzrMztOeV5rUP3ay922arvr5B4yCtkyyZpvHZi+onRovMdX9a89yHVE++p/n2Lu1BqXnQDI2PN33QpLNN4+3pk9TeA9oj7Zsm/Eav9vT8p8Ybj5vznl2u9niRxgtnaN6rfM7U+GVBTnvLfVqf+6d5fe40E37zeebzb35Je929rHGTR/XsD7qPvUnrCJdoPGpTOLf2InxBewWuMOF32jWPPWzRfHWyKedW7cWleeWauzXPKFO70Th+pu7fs8416S2p0TgpazHva363/2kT3wG75p1JjRN0n19WqvLZr3xuMfGf26b53E61k2fUT02aZN4/T/eVhZpn6H6y+watS1yl+nmtxvNnTTLpTdf5PqL7+VPay/hifX6h9ti7UfXgat0fyjX++KHuh7pfP32b2r/G7XM+oL0WGzXu1Xj8fLWjAzbNOw4r/hXmdc+7zeud39Z4TvfL85Zqz9OP6X6i9Z8XH9Se1q9o71yrSX+u1pEml6ueqr28+aOqxwe0Z/4K9ZNfV735ieYn12lvuC+o39P4dWqX2nev5sMXaDz5e6037jTpTd2p+vug9ji9QHvdtmp8lTHny2madIsnmfp5kcYVC8zrco/qRZ3679M0rh88y7yvcU+RxsvLHtN4+ofas3e83V5t0pv1rMaz95vzWPA5tbtJyscvTbrPTTeff2qB5hUaDz71jMp7jvaAfEzjz/Uql2e1R6DWFXbcpHKaf5q5PjXaazOq+flq3R/+pHGu1pOKYibe/Z0WjaN0H9c8fe8szTNe1HpcpfaIXajyuVzzjVUm3PxFVq0zqbwu1TjlRnN8seZ/D+3T/aHtLJMPyxkm3Aetpp5fpnWSQxqXfkf3EfXvD2zS9bxd8+krtPd2l/YyvVB7HX5G7V/jj92t6l/maY/ETsWzR/X8JfUL39cemyGld7PWRzapPkzSOOpy7S14m8p/t9rHpVov1Xhn/Rc=
*/