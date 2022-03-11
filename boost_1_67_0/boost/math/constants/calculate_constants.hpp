//  Copyright John Maddock 2010, 2012.
//  Copyright Paul A. Bristow 2011, 2012.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED
#define BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED

#include <boost/math/special_functions/trunc.hpp>

namespace boost{ namespace math{ namespace constants{ namespace detail{

template <class T>
template<int N>
inline T constant_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING

   return ldexp(acos(T(0)), 1);

   /*
   // Although this code works well, it's usually more accurate to just call acos
   // and access the number types own representation of PI which is usually calculated
   // at slightly higher precision...

   T result;
   T a = 1;
   T b;
   T A(a);
   T B = 0.5f;
   T D = 0.25f;

   T lim;
   lim = boost::math::tools::epsilon<T>();

   unsigned k = 1;

   do
   {
      result = A + B;
      result = ldexp(result, -2);
      b = sqrt(B);
      a += b;
      a = ldexp(a, -1);
      A = a * a;
      B = A - result;
      B = ldexp(B, 1);
      result = A - B;
      bool neg = boost::math::sign(result) < 0;
      if(neg)
         result = -result;
      if(result <= lim)
         break;
      if(neg)
         result = -result;
      result = ldexp(result, k - 1);
      D -= result;
      ++k;
      lim = ldexp(lim, 1);
   }
   while(true);

   result = B / D;
   return result;
   */
}

template <class T>
template<int N>
inline T constant_two_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return 2 * pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T> // 2 / pi
template<int N>
inline T constant_two_div_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return 2 / pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T>  // sqrt(2/pi)
template <int N>
inline T constant_root_two_div_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt((2 / pi<T, policies::policy<policies::digits2<N> > >()));
}

template <class T>
template<int N>
inline T constant_one_div_two_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return 1 / two_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T>
template<int N>
inline T constant_root_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T>
template<int N>
inline T constant_root_half_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(pi<T, policies::policy<policies::digits2<N> > >() / 2);
}

template <class T>
template<int N>
inline T constant_root_two_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(two_pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T>
template<int N>
inline T constant_log_root_two_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return log(root_two_pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T>
template<int N>
inline T constant_root_ln_four<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(log(static_cast<T>(4)));
}

template <class T>
template<int N>
inline T constant_e<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   //
   // Although we can clearly calculate this from first principles, this hooks into
   // T's own notion of e, which hopefully will more accurate than one calculated to
   // a few epsilon:
   //
   BOOST_MATH_STD_USING
   return exp(static_cast<T>(1));
}

template <class T>
template<int N>
inline T constant_half<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return static_cast<T>(1) / static_cast<T>(2);
}

template <class T>
template<int M>
inline T constant_euler<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, M>)))
{
   BOOST_MATH_STD_USING
   //
   // This is the method described in:
   // "Some New Algorithms for High-Precision Computation of Euler's Constant"
   // Richard P Brent and Edwin M McMillan.
   // Mathematics of Computation, Volume 34, Number 149, Jan 1980, pages 305-312.
   // See equation 17 with p = 2.
   //
   T n = 3 + (M ? (std::min)(M, tools::digits<T>()) : tools::digits<T>()) / 4;
   T lim = M ? ldexp(T(1), 1 - (std::min)(M, tools::digits<T>())) : tools::epsilon<T>();
   T lnn = log(n);
   T term = 1;
   T N = -lnn;
   T D = 1;
   T Hk = 0;
   T one = 1;

   for(unsigned k = 1;; ++k)
   {
      term *= n * n;
      term /= k * k;
      Hk += one / k;
      N += term * (Hk - lnn);
      D += term;

      if(term < D * lim)
         break;
   }
   return N / D;
}

template <class T>
template<int N>
inline T constant_euler_sqr<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
  BOOST_MATH_STD_USING
  return euler<T, policies::policy<policies::digits2<N> > >()
     * euler<T, policies::policy<policies::digits2<N> > >();
}

template <class T>
template<int N>
inline T constant_one_div_euler<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
  BOOST_MATH_STD_USING
  return static_cast<T>(1)
     / euler<T, policies::policy<policies::digits2<N> > >();
}


template <class T>
template<int N>
inline T constant_root_two<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(2));
}


template <class T>
template<int N>
inline T constant_root_three<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(3));
}

template <class T>
template<int N>
inline T constant_half_root_two<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(2)) / 2;
}

template <class T>
template<int N>
inline T constant_ln_two<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   //
   // Although there are good ways to calculate this from scratch, this hooks into
   // T's own notion of log(2) which will hopefully be accurate to the full precision
   // of T:
   //
   BOOST_MATH_STD_USING
   return log(static_cast<T>(2));
}

template <class T>
template<int N>
inline T constant_ln_ten<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return log(static_cast<T>(10));
}

template <class T>
template<int N>
inline T constant_ln_ln_two<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return log(log(static_cast<T>(2)));
}

template <class T>
template<int N>
inline T constant_third<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1) / static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_twothirds<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(2) / static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_two_thirds<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(2) / static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_three_quarters<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(3) / static_cast<T>(4);
}

template <class T>
template<int N>
inline T constant_sixth<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
  BOOST_MATH_STD_USING
  return static_cast<T>(1) / static_cast<T>(6);
}

// Pi and related constants.
template <class T>
template<int N>
inline T constant_pi_minus_three<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_four_minus_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return static_cast<T>(4) - pi<T, policies::policy<policies::digits2<N> > >();
}

//template <class T>
//template<int N>
//inline T constant_pow23_four_minus_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
//{
//   BOOST_MATH_STD_USING
//   return pow(four_minus_pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(1.5));
//}

template <class T>
template<int N>
inline T constant_exp_minus_half<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return exp(static_cast<T>(-0.5));
}

template <class T>
template<int N>
inline T constant_exp_minus_one<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
  BOOST_MATH_STD_USING
  return exp(static_cast<T>(-1.));
}

template <class T>
template<int N>
inline T constant_one_div_root_two<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return static_cast<T>(1) / root_two<T, policies::policy<policies::digits2<N> > >();
}

template <class T>
template<int N>
inline T constant_one_div_root_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return static_cast<T>(1) / root_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T>
template<int N>
inline T constant_one_div_root_two_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return static_cast<T>(1) / root_two_pi<T, policies::policy<policies::digits2<N> > >();
}

template <class T>
template<int N>
inline T constant_root_one_div_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(static_cast<T>(1) / pi<T, policies::policy<policies::digits2<N> > >());
}

template <class T>
template<int N>
inline T constant_four_thirds_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >() * static_cast<T>(4) / static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_half_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()  / static_cast<T>(2);
}


template <class T>
template<int N>
inline T constant_third_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()  / static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_sixth_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()  / static_cast<T>(6);
}

template <class T>
template<int N>
inline T constant_two_thirds_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >() * static_cast<T>(2) / static_cast<T>(3);
}

template <class T>
template<int N>
inline T constant_three_quarters_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >() * static_cast<T>(3) / static_cast<T>(4);
}

template <class T>
template<int N>
inline T constant_pi_pow_e<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pow(pi<T, policies::policy<policies::digits2<N> > >(), e<T, policies::policy<policies::digits2<N> > >()); //
}

template <class T>
template<int N>
inline T constant_pi_sqr<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >() ; //
}

template <class T>
template<int N>
inline T constant_pi_sqr_div_six<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >()
   / static_cast<T>(6); //
}


template <class T>
template<int N>
inline T constant_pi_cubed<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >()
   *      pi<T, policies::policy<policies::digits2<N> > >()
   ; //
}

template <class T>
template<int N>
inline T constant_cbrt_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pow(pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(1)/ static_cast<T>(3));
}

template <class T>
template<int N>
inline T constant_one_div_cbrt_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1)
   / pow(pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(1)/ static_cast<T>(3));
}

// Euler's e

template <class T>
template<int N>
inline T constant_e_pow_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pow(e<T, policies::policy<policies::digits2<N> > >(), pi<T, policies::policy<policies::digits2<N> > >()); //
}

template <class T>
template<int N>
inline T constant_root_e<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sqrt(e<T, policies::policy<policies::digits2<N> > >());
}

template <class T>
template<int N>
inline T constant_log10_e<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return log10(e<T, policies::policy<policies::digits2<N> > >());
}

template <class T>
template<int N>
inline T constant_one_div_log10_e<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return  static_cast<T>(1) /
     log10(e<T, policies::policy<policies::digits2<N> > >());
}

// Trigonometric

template <class T>
template<int N>
inline T constant_degree<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return pi<T, policies::policy<policies::digits2<N> > >()
   / static_cast<T>(180)
   ; //
}

template <class T>
template<int N>
inline T constant_radian<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(180)
   / pi<T, policies::policy<policies::digits2<N> > >()
   ; //
}

template <class T>
template<int N>
inline T constant_sin_one<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sin(static_cast<T>(1)) ; //
}

template <class T>
template<int N>
inline T constant_cos_one<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return cos(static_cast<T>(1)) ; //
}

template <class T>
template<int N>
inline T constant_sinh_one<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return sinh(static_cast<T>(1)) ; //
}

template <class T>
template<int N>
inline T constant_cosh_one<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return cosh(static_cast<T>(1)) ; //
}

template <class T>
template<int N>
inline T constant_phi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return (static_cast<T>(1) + sqrt(static_cast<T>(5)) )/static_cast<T>(2) ; //
}

template <class T>
template<int N>
inline T constant_ln_phi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   //return  log(phi<T, policies::policy<policies::digits2<N> > >()); // ???
   return log((static_cast<T>(1) + sqrt(static_cast<T>(5)) )/static_cast<T>(2) );
}
template <class T>
template<int N>
inline T constant_one_div_ln_phi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING
   return static_cast<T>(1) /
     log((static_cast<T>(1) + sqrt(static_cast<T>(5)) )/static_cast<T>(2) );
}

// Zeta

template <class T>
template<int N>
inline T constant_zeta_two<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   BOOST_MATH_STD_USING

     return pi<T, policies::policy<policies::digits2<N> > >()
     *  pi<T, policies::policy<policies::digits2<N> > >()
     /static_cast<T>(6);
}

template <class T>
template<int N>
inline T constant_zeta_three<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   // http://mathworld.wolfram.com/AperysConstant.html
   // http://en.wikipedia.org/wiki/Mathematical_constant

   // http://oeis.org/A002117/constant
   //T zeta3("1.20205690315959428539973816151144999076"
   // "4986292340498881792271555341838205786313"
   // "09018645587360933525814619915");

  //"1.202056903159594285399738161511449990, 76498629234049888179227155534183820578631309018645587360933525814619915"  A002117
  // 1.202056903159594285399738161511449990, 76498629234049888179227155534183820578631309018645587360933525814619915780, +00);
  //"1.2020569031595942 double
  // http://www.spaennare.se/SSPROG/ssnum.pdf  // section 11, Algorithm for Apery's constant zeta(3).
  // Programs to Calculate some Mathematical Constants to Large Precision, Document Version 1.50

  // by Stefan Spannare  September 19, 2007
  // zeta(3) = 1/64 * sum
   BOOST_MATH_STD_USING
   T n_fact=static_cast<T>(1); // build n! for n = 0.
   T sum = static_cast<double>(77); // Start with n = 0 case.
   // for n = 0, (77/1) /64 = 1.203125
   //double lim = std::numeric_limits<double>::epsilon();
   T lim = N ? ldexp(T(1), 1 - (std::min)(N, tools::digits<T>())) : tools::epsilon<T>();
   for(unsigned int n = 1; n < 40; ++n)
   { // three to five decimal digits per term, so 40 should be plenty for 100 decimal digits.
      //cout << "n = " << n << endl;
      n_fact *= n; // n!
      T n_fact_p10 = n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact * n_fact; // (n!)^10
      T num = ((205 * n * n) + (250 * n) + 77) * n_fact_p10; // 205n^2 + 250n + 77
      // int nn = (2 * n + 1);
      // T d = factorial(nn); // inline factorial.
      T d = 1;
      for(unsigned int i = 1; i <= (n+n + 1); ++i) // (2n + 1)
      {
        d *= i;
      }
      T den = d * d * d * d * d; // [(2n+1)!]^5
      //cout << "den = " << den << endl;
      T term = num/den;
      if (n % 2 != 0)
      { //term *= -1;
        sum -= term;
      }
      else
      {
        sum += term;
      }
      //cout << "term = " << term << endl;
      //cout << "sum/64  = " << sum/64 << endl;
      if(abs(term) < lim)
      {
         break;
      }
   }
   return sum / 64;
}

template <class T>
template<int N>
inline T constant_catalan<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{ // http://oeis.org/A006752/constant
  //T c("0.915965594177219015054603514932384110774"
 //"149374281672134266498119621763019776254769479356512926115106248574");

  // 9.159655941772190150546035149323841107, 74149374281672134266498119621763019776254769479356512926115106248574422619, -01);

   // This is equation (entry) 31 from
   // http://www-2.cs.cmu.edu/~adamchik/articles/catalan/catalan.htm
   // See also http://www.mpfr.org/algorithms.pdf
   BOOST_MATH_STD_USING
   T k_fact = 1;
   T tk_fact = 1;
   T sum = 1;
   T term;
   T lim = N ? ldexp(T(1), 1 - (std::min)(N, tools::digits<T>())) : tools::epsilon<T>();

   for(unsigned k = 1;; ++k)
   {
      k_fact *= k;
      tk_fact *= (2 * k) * (2 * k - 1);
      term = k_fact * k_fact / (tk_fact * (2 * k + 1) * (2 * k + 1));
      sum += term;
      if(term < lim)
      {
         break;
      }
   }
   return boost::math::constants::pi<T, boost::math::policies::policy<> >()
      * log(2 + boost::math::constants::root_three<T, boost::math::policies::policy<> >())
       / 8
      + 3 * sum / 8;
}

namespace khinchin_detail{

template <class T>
T zeta_polynomial_series(T s, T sc, int digits)
{
   BOOST_MATH_STD_USING
   //
   // This is algorithm 3 from:
   //
   // "An Efficient Algorithm for the Riemann Zeta Function", P. Borwein,
   // Canadian Mathematical Society, Conference Proceedings, 2000.
   // See: http://www.cecm.sfu.ca/personal/pborwein/PAPERS/P155.pdf
   //
   BOOST_MATH_STD_USING
   int n = (digits * 19) / 53;
   T sum = 0;
   T two_n = ldexp(T(1), n);
   int ej_sign = 1;
   for(int j = 0; j < n; ++j)
   {
      sum += ej_sign * -two_n / pow(T(j + 1), s);
      ej_sign = -ej_sign;
   }
   T ej_sum = 1;
   T ej_term = 1;
   for(int j = n; j <= 2 * n - 1; ++j)
   {
      sum += ej_sign * (ej_sum - two_n) / pow(T(j + 1), s);
      ej_sign = -ej_sign;
      ej_term *= 2 * n - j;
      ej_term /= j - n + 1;
      ej_sum += ej_term;
   }
   return -sum / (two_n * (1 - pow(T(2), sc)));
}

template <class T>
T khinchin(int digits)
{
   BOOST_MATH_STD_USING
   T sum = 0;
   T term;
   T lim = ldexp(T(1), 1-digits);
   T factor = 0;
   unsigned last_k = 1;
   T num = 1;
   for(unsigned n = 1;; ++n)
   {
      for(unsigned k = last_k; k <= 2 * n - 1; ++k)
      {
         factor += num / k;
         num = -num;
      }
      last_k = 2 * n;
      term = (zeta_polynomial_series(T(2 * n), T(1 - T(2 * n)), digits) - 1) * factor / n;
      sum += term;
      if(term < lim)
         break;
   }
   return exp(sum / boost::math::constants::ln_two<T, boost::math::policies::policy<> >());
}

}

template <class T>
template<int N>
inline T constant_khinchin<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   int n = N ? (std::min)(N, tools::digits<T>()) : tools::digits<T>();
   return khinchin_detail::khinchin<T>(n);
}

template <class T>
template<int N>
inline T constant_extreme_value_skewness<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{ // from e_float constants.cpp
  // Mathematica: N[12 Sqrt[6]  Zeta[3]/Pi^3, 1101]
   BOOST_MATH_STD_USING
   T ev(12 * sqrt(static_cast<T>(6)) * zeta_three<T, policies::policy<policies::digits2<N> > >()
    / pi_cubed<T, policies::policy<policies::digits2<N> > >() );

//T ev(
//"1.1395470994046486574927930193898461120875997958365518247216557100852480077060706857071875468869385150"
//"1894272048688553376986765366075828644841024041679714157616857834895702411080704529137366329462558680"
//"2015498788776135705587959418756809080074611906006528647805347822929577145038743873949415294942796280"
//"0895597703063466053535550338267721294164578901640163603544404938283861127819804918174973533694090594"
//"3094963822672055237678432023017824416203652657301470473548274848068762500300316769691474974950757965"
//"8640779777748741897542093874605477776538884083378029488863880220988107155275203245233994097178778984"
//"3488995668362387892097897322246698071290011857605809901090220903955815127463328974447572119951192970"
//"3684453635456559086126406960279692862247058250100678008419431185138019869693206366891639436908462809"
//"9756051372711251054914491837034685476095423926553367264355374652153595857163724698198860485357368964"
//"3807049634423621246870868566707915720704996296083373077647528285782964567312903914752617978405994377"
//"9064157147206717895272199736902453130842229559980076472936976287378945035706933650987259357729800315");

  return ev;
}

namespace detail{
//
// Calculation of the Glaisher constant depends upon calculating the
// derivative of the zeta function at 2, we can then use the relation:
// zeta'(2) = 1/6 pi^2 [euler + ln(2pi)-12ln(A)]
// To get the constant A.
// See equation 45 at http://mathworld.wolfram.com/RiemannZetaFunction.html.
//
// The derivative of the zeta function is computed by direct differentiation
// of the relation:
// (1-2^(1-s))zeta(s) = SUM(n=0, INF){ (-n)^n / (n+1)^s  }
// Which gives us 2 slowly converging but alternating sums to compute,
// for this we use Algorithm 1 from "Convergent Acceleration of Alternating Series",
// Henri Cohen, Fernando Rodriguez Villegas and Don Zagier, Experimental Mathematics 9:1 (1999).
// See http://www.math.utexas.edu/users/villegas/publications/conv-accel.pdf
//
template <class T>
T zeta_series_derivative_2(unsigned digits)
{
   // Derivative of the series part, evaluated at 2:
   BOOST_MATH_STD_USING
   int n = digits * 301 * 13 / 10000;
   boost::math::itrunc((std::numeric_limits<T>::digits10 + 1) * 1.3);
   T d = pow(3 + sqrt(T(8)), n);
   d = (d + 1 / d) / 2;
   T b = -1;
   T c = -d;
   T s = 0;
   for(int k = 0; k < n; ++k)
   {
      T a = -log(T(k+1)) / ((k+1) * (k+1));
      c = b - c;
      s = s + c * a;
      b = (k + n) * (k - n) * b / ((k + T(0.5f)) * (k + 1));
   }
   return s / d;
}

template <class T>
T zeta_series_2(unsigned digits)
{
   // Series part of zeta at 2:
   BOOST_MATH_STD_USING
   int n = digits * 301 * 13 / 10000;
   T d = pow(3 + sqrt(T(8)), n);
   d = (d + 1 / d) / 2;
   T b = -1;
   T c = -d;
   T s = 0;
   for(int k = 0; k < n; ++k)
   {
      T a = T(1) / ((k + 1) * (k + 1));
      c = b - c;
      s = s + c * a;
      b = (k + n) * (k - n) * b / ((k + T(0.5f)) * (k + 1));
   }
   return s / d;
}

template <class T>
inline T zeta_series_lead_2()
{
   // lead part at 2:
   return 2;
}

template <class T>
inline T zeta_series_derivative_lead_2()
{
   // derivative of lead part at 2:
   return -2 * boost::math::constants::ln_two<T>();
}

template <class T>
inline T zeta_derivative_2(unsigned n)
{
   // zeta derivative at 2:
   return zeta_series_derivative_2<T>(n) * zeta_series_lead_2<T>()
      + zeta_series_derivative_lead_2<T>() * zeta_series_2<T>(n);
}

}  // namespace detail

template <class T>
template<int N>
inline T constant_glaisher<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{

   BOOST_MATH_STD_USING
   typedef policies::policy<policies::digits2<N> > forwarding_policy;
   int n = N ? (std::min)(N, tools::digits<T>()) : tools::digits<T>();
   T v = detail::zeta_derivative_2<T>(n);
   v *= 6;
   v /= boost::math::constants::pi<T, forwarding_policy>() * boost::math::constants::pi<T, forwarding_policy>();
   v -= boost::math::constants::euler<T, forwarding_policy>();
   v -= log(2 * boost::math::constants::pi<T, forwarding_policy>());
   v /= -12;
   return exp(v);

 /*
   // from http://mpmath.googlecode.com/svn/data/glaisher.txt
     // 20,000 digits of the Glaisher-Kinkelin constant A = exp(1/2 - zeta'(-1))
     // Computed using A = exp((6 (-zeta'(2))/pi^2 + log 2 pi + gamma)/12)
  // with Euler-Maclaurin summation for zeta'(2).
  T g(
  "1.282427129100622636875342568869791727767688927325001192063740021740406308858826"
  "46112973649195820237439420646120399000748933157791362775280404159072573861727522"
  "14334327143439787335067915257366856907876561146686449997784962754518174312394652"
  "76128213808180219264516851546143919901083573730703504903888123418813674978133050"
  "93770833682222494115874837348064399978830070125567001286994157705432053927585405"
  "81731588155481762970384743250467775147374600031616023046613296342991558095879293"
  "36343887288701988953460725233184702489001091776941712153569193674967261270398013"
  "52652668868978218897401729375840750167472114895288815996668743164513890306962645"
  "59870469543740253099606800842447417554061490189444139386196089129682173528798629"
  "88434220366989900606980888785849587494085307347117090132667567503310523405221054"
  "14176776156308191919997185237047761312315374135304725819814797451761027540834943"
  "14384965234139453373065832325673954957601692256427736926358821692159870775858274"
  "69575162841550648585890834128227556209547002918593263079373376942077522290940187");

  return g;
  */
}

template <class T>
template<int N>
inline T constant_rayleigh_skewness<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{  // From e_float
  // 1100 digits of the Rayleigh distribution skewness
  // Mathematica: N[2 Sqrt[Pi] (Pi - 3)/((4 - Pi)^(3/2)), 1100]

   BOOST_MATH_STD_USING
   T rs(2 * root_pi<T, policies::policy<policies::digits2<N> > >()
      * pi_minus_three<T, policies::policy<policies::digits2<N> > >()
      / pow(four_minus_pi<T, policies::policy<policies::digits2<N> > >(), static_cast<T>(3./2))
      );
 //   6.31110657818937138191899351544227779844042203134719497658094585692926819617473725459905027032537306794400047264,

  //"0.6311106578189371381918993515442277798440422031347194976580945856929268196174737254599050270325373067"
  //"9440004726436754739597525250317640394102954301685809920213808351450851396781817932734836994829371322"
  //"5797376021347531983451654130317032832308462278373358624120822253764532674177325950686466133508511968"
  //"2389168716630349407238090652663422922072397393006683401992961569208109477307776249225072042971818671"
  //"4058887072693437217879039875871765635655476241624825389439481561152126886932506682176611183750503553"
  //"1218982627032068396407180216351425758181396562859085306247387212297187006230007438534686340210168288"
  //"8956816965453815849613622117088096547521391672977226658826566757207615552041767516828171274858145957"
  //"6137539156656005855905288420585194082284972984285863898582313048515484073396332610565441264220790791"
  //"0194897267890422924599776483890102027823328602965235306539844007677157873140562950510028206251529523"
  //"7428049693650605954398446899724157486062545281504433364675815915402937209673727753199567661561209251"
  //"4695589950526053470201635372590001578503476490223746511106018091907936826431407434894024396366284848");  ;
  return rs;
}

template <class T>
template<int N>
inline T constant_rayleigh_kurtosis_excess<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{ // - (6 Pi^2 - 24 Pi + 16)/((Pi - 4)^2)
    // Might provide and calculate this using pi_minus_four.
   BOOST_MATH_STD_USING
   return - (((static_cast<T>(6) * pi<T, policies::policy<policies::digits2<N> > >()
        * pi<T, policies::policy<policies::digits2<N> > >())
   - (static_cast<T>(24) * pi<T, policies::policy<policies::digits2<N> > >()) + static_cast<T>(16) )
   /
   ((pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4))
   * (pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4)))
   );
}

template <class T>
template<int N>
inline T constant_rayleigh_kurtosis<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{ // 3 - (6 Pi^2 - 24 Pi + 16)/((Pi - 4)^2)
  // Might provide and calculate this using pi_minus_four.
   BOOST_MATH_STD_USING
   return static_cast<T>(3) - (((static_cast<T>(6) * pi<T, policies::policy<policies::digits2<N> > >()
        * pi<T, policies::policy<policies::digits2<N> > >())
   - (static_cast<T>(24) * pi<T, policies::policy<policies::digits2<N> > >()) + static_cast<T>(16) )
   /
   ((pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4))
   * (pi<T, policies::policy<policies::digits2<N> > >() - static_cast<T>(4)))
   );
}

template <class T>
template<int N>
inline T constant_log2_e<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return 1 / boost::math::constants::ln_two<T>();
}

template <class T>
template<int N>
inline T constant_quarter_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return boost::math::constants::pi<T>() / 4;
}

template <class T>
template<int N>
inline T constant_one_div_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return 1 / boost::math::constants::pi<T>();
}

template <class T>
template<int N>
inline T constant_two_div_root_pi<T>::compute(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC((boost::integral_constant<int, N>)))
{
   return 2 * boost::math::constants::one_div_root_pi<T>();
}

}
}
}
} // namespaces

#endif // BOOST_MATH_CALCULATE_CONSTANTS_CONSTANTS_INCLUDED

/* calculate_constants.hpp
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
*/