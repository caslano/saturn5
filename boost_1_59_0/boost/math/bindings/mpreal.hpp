//  Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Wrapper that works with mpfr::mpreal defined in gmpfrxx.h
// See http://math.berkeley.edu/~wilken/code/gmpfrxx/
// Also requires the gmp and mpfr libraries.
//

#ifndef BOOST_MATH_MPREAL_BINDINGS_HPP
#define BOOST_MATH_MPREAL_BINDINGS_HPP

#include <type_traits>

#ifdef _MSC_VER
//
// We get a lot of warnings from the gmp, mpfr and gmpfrxx headers, 
// disable them here, so we only see warnings from *our* code:
//
#pragma warning(push)
#pragma warning(disable: 4127 4800 4512)
#endif

#include <mpreal.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/bindings/detail/big_digamma.hpp>
#include <boost/math/bindings/detail/big_lanczos.hpp>
#include <boost/math/tools/config.hpp>
#ifndef BOOST_MATH_STANDALONE
#include <boost/lexical_cast.hpp>
#endif

namespace mpfr{

template <class T>
inline mpreal operator + (const mpreal& r, const T& t){ return r + mpreal(t); }
template <class T>
inline mpreal operator - (const mpreal& r, const T& t){ return r - mpreal(t); }
template <class T>
inline mpreal operator * (const mpreal& r, const T& t){ return r * mpreal(t); }
template <class T>
inline mpreal operator / (const mpreal& r, const T& t){ return r / mpreal(t); }

template <class T>
inline mpreal operator + (const T& t, const mpreal& r){ return mpreal(t) + r; }
template <class T>
inline mpreal operator - (const T& t, const mpreal& r){ return mpreal(t) - r; }
template <class T>
inline mpreal operator * (const T& t, const mpreal& r){ return mpreal(t) * r; }
template <class T>
inline mpreal operator / (const T& t, const mpreal& r){ return mpreal(t) / r; }

template <class T>
inline bool operator == (const mpreal& r, const T& t){ return r == mpreal(t); }
template <class T>
inline bool operator != (const mpreal& r, const T& t){ return r != mpreal(t); }
template <class T>
inline bool operator <= (const mpreal& r, const T& t){ return r <= mpreal(t); }
template <class T>
inline bool operator >= (const mpreal& r, const T& t){ return r >= mpreal(t); }
template <class T>
inline bool operator < (const mpreal& r, const T& t){ return r < mpreal(t); }
template <class T>
inline bool operator > (const mpreal& r, const T& t){ return r > mpreal(t); }

template <class T>
inline bool operator == (const T& t, const mpreal& r){ return mpreal(t) == r; }
template <class T>
inline bool operator != (const T& t, const mpreal& r){ return mpreal(t) != r; }
template <class T>
inline bool operator <= (const T& t, const mpreal& r){ return mpreal(t) <= r; }
template <class T>
inline bool operator >= (const T& t, const mpreal& r){ return mpreal(t) >= r; }
template <class T>
inline bool operator < (const T& t, const mpreal& r){ return mpreal(t) < r; }
template <class T>
inline bool operator > (const T& t, const mpreal& r){ return mpreal(t) > r; }

/*
inline mpfr::mpreal fabs(const mpfr::mpreal& v)
{
   return abs(v);
}
inline mpfr::mpreal pow(const mpfr::mpreal& b, const mpfr::mpreal e)
{
   mpfr::mpreal result;
   mpfr_pow(result.__get_mp(), b.__get_mp(), e.__get_mp(), GMP_RNDN);
   return result;
}
*/
inline mpfr::mpreal ldexp(const mpfr::mpreal& v, int e)
{
   return mpfr::ldexp(v, static_cast<mp_exp_t>(e));
}

inline mpfr::mpreal frexp(const mpfr::mpreal& v, int* expon)
{
   mp_exp_t e;
   mpfr::mpreal r = mpfr::frexp(v, &e);
   *expon = e;
   return r;
}

#if (MPFR_VERSION < MPFR_VERSION_NUM(2,4,0))
mpfr::mpreal fmod(const mpfr::mpreal& v1, const mpfr::mpreal& v2)
{
   mpfr::mpreal n;
   if(v1 < 0)
      n = ceil(v1 / v2);
   else
      n = floor(v1 / v2);
   return v1 - n * v2;
}
#endif

template <class Policy>
inline mpfr::mpreal modf(const mpfr::mpreal& v, long long* ipart, const Policy& pol)
{
   *ipart = lltrunc(v, pol);
   return v - boost::math::tools::real_cast<mpfr::mpreal>(*ipart);
}
template <class Policy>
inline int iround(mpfr::mpreal const& x, const Policy& pol)
{
   return boost::math::tools::real_cast<int>(boost::math::round(x, pol));
}

template <class Policy>
inline long lround(mpfr::mpreal const& x, const Policy& pol)
{
   return boost::math::tools::real_cast<long>(boost::math::round(x, pol));
}

template <class Policy>
inline long long llround(mpfr::mpreal const& x, const Policy& pol)
{
   return boost::math::tools::real_cast<long long>(boost::math::round(x, pol));
}

template <class Policy>
inline int itrunc(mpfr::mpreal const& x, const Policy& pol)
{
   return boost::math::tools::real_cast<int>(boost::math::trunc(x, pol));
}

template <class Policy>
inline long ltrunc(mpfr::mpreal const& x, const Policy& pol)
{
   return boost::math::tools::real_cast<long>(boost::math::trunc(x, pol));
}

template <class Policy>
inline long long lltrunc(mpfr::mpreal const& x, const Policy& pol)
{
   return boost::math::tools::real_cast<long long>(boost::math::trunc(x, pol));
}

}

namespace boost{ namespace math{

#if defined(__GNUC__) && (__GNUC__ < 4)
   using ::iround;
   using ::lround;
   using ::llround;
   using ::itrunc;
   using ::ltrunc;
   using ::lltrunc;
   using ::modf;
#endif

namespace lanczos{

struct mpreal_lanczos
{
   static mpfr::mpreal lanczos_sum(const mpfr::mpreal& z)
   {
      unsigned long p = z.get_default_prec();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum(z);
   }
   static mpfr::mpreal lanczos_sum_expG_scaled(const mpfr::mpreal& z)
   {
      unsigned long p = z.get_default_prec();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum_expG_scaled(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum_expG_scaled(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum_expG_scaled(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum_expG_scaled(z);
   }
   static mpfr::mpreal lanczos_sum_near_1(const mpfr::mpreal& z)
   {
      unsigned long p = z.get_default_prec();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum_near_1(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum_near_1(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum_near_1(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum_near_1(z);
   }
   static mpfr::mpreal lanczos_sum_near_2(const mpfr::mpreal& z)
   {
      unsigned long p = z.get_default_prec();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum_near_2(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum_near_2(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum_near_2(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum_near_2(z);
   }
   static mpfr::mpreal g()
   { 
      unsigned long p = mpfr::mpreal::get_default_prec();
      if(p <= 72)
         return lanczos13UDT::g();
      else if(p <= 120)
         return lanczos22UDT::g();
      else if(p <= 170)
         return lanczos31UDT::g();
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::g();
   }
};

template<class Policy>
struct lanczos<mpfr::mpreal, Policy>
{
   typedef mpreal_lanczos type;
};

} // namespace lanczos

namespace tools
{

template<>
inline int digits<mpfr::mpreal>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpfr::mpreal))
{
   return mpfr::mpreal::get_default_prec();
}

namespace detail{

template<class I>
void convert_to_long_result(mpfr::mpreal const& r, I& result)
{
   result = 0;
   I last_result(0);
   mpfr::mpreal t(r);
   double term;
   do
   {
      term = real_cast<double>(t);
      last_result = result;
      result += static_cast<I>(term);
      t -= term;
   }while(result != last_result);
}

}

template <>
inline mpfr::mpreal real_cast<mpfr::mpreal, long long>(long long t)
{
   mpfr::mpreal result;
   int expon = 0;
   int sign = 1;
   if(t < 0)
   {
      sign = -1;
      t = -t;
   }
   while(t)
   {
      result += ldexp((double)(t & 0xffffL), expon);
      expon += 32;
      t >>= 32;
   }
   return result * sign;
}
/*
template <>
inline unsigned real_cast<unsigned, mpfr::mpreal>(mpfr::mpreal t)
{
   return t.get_ui();
}
template <>
inline int real_cast<int, mpfr::mpreal>(mpfr::mpreal t)
{
   return t.get_si();
}
template <>
inline double real_cast<double, mpfr::mpreal>(mpfr::mpreal t)
{
   return t.get_d();
}
template <>
inline float real_cast<float, mpfr::mpreal>(mpfr::mpreal t)
{
   return static_cast<float>(t.get_d());
}
template <>
inline long real_cast<long, mpfr::mpreal>(mpfr::mpreal t)
{
   long result;
   detail::convert_to_long_result(t, result);
   return result;
}
*/
template <>
inline long long real_cast<long long, mpfr::mpreal>(mpfr::mpreal t)
{
   long long result;
   detail::convert_to_long_result(t, result);
   return result;
}

template <>
inline mpfr::mpreal max_value<mpfr::mpreal>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpfr::mpreal))
{
   static bool has_init = false;
   static mpfr::mpreal val(0.5);
   if(!has_init)
   {
      val = ldexp(val, mpfr_get_emax());
      has_init = true;
   }
   return val;
}

template <>
inline mpfr::mpreal min_value<mpfr::mpreal>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpfr::mpreal))
{
   static bool has_init = false;
   static mpfr::mpreal val(0.5);
   if(!has_init)
   {
      val = ldexp(val, mpfr_get_emin());
      has_init = true;
   }
   return val;
}

template <>
inline mpfr::mpreal log_max_value<mpfr::mpreal>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpfr::mpreal))
{
   static bool has_init = false;
   static mpfr::mpreal val = max_value<mpfr::mpreal>();
   if(!has_init)
   {
      val = log(val);
      has_init = true;
   }
   return val;
}

template <>
inline mpfr::mpreal log_min_value<mpfr::mpreal>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpfr::mpreal))
{
   static bool has_init = false;
   static mpfr::mpreal val = max_value<mpfr::mpreal>();
   if(!has_init)
   {
      val = log(val);
      has_init = true;
   }
   return val;
}

template <>
inline mpfr::mpreal epsilon<mpfr::mpreal>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(mpfr::mpreal))
{
   return ldexp(mpfr::mpreal(1), 1-boost::math::policies::digits<mpfr::mpreal, boost::math::policies::policy<> >());
}

} // namespace tools

template <class Policy>
inline mpfr::mpreal skewness(const extreme_value_distribution<mpfr::mpreal, Policy>& /*dist*/)
{
   //
   // This is 12 * sqrt(6) * zeta(3) / pi^3:
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   //
   #ifdef BOOST_MATH_STANDALONE
   static_assert(sizeof(Policy) == 0, "mpreal skewness can not be calculated in standalone mode");
   #endif

   return boost::lexical_cast<mpfr::mpreal>("1.1395470994046486574927930193898461120875997958366");
}

template <class Policy>
inline mpfr::mpreal skewness(const rayleigh_distribution<mpfr::mpreal, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  #ifdef BOOST_MATH_STANDALONE
  static_assert(sizeof(Policy) == 0, "mpreal skewness can not be calculated in standalone mode");
  #endif

  return boost::lexical_cast<mpfr::mpreal>("0.63111065781893713819189935154422777984404221106391");
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 2 * root_pi<RealType>() * pi_minus_three<RealType>() / pow23_four_minus_pi<RealType>();
}

template <class Policy>
inline mpfr::mpreal kurtosis(const rayleigh_distribution<mpfr::mpreal, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  #ifdef BOOST_MATH_STANDALONE
  static_assert(sizeof(Policy) == 0, "mpreal kurtosis can not be calculated in standalone mode");
  #endif

  return boost::lexical_cast<mpfr::mpreal>("3.2450893006876380628486604106197544154170667057995");
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 3 - (6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  // (four_minus_pi<RealType>() * four_minus_pi<RealType>());
}

template <class Policy>
inline mpfr::mpreal kurtosis_excess(const rayleigh_distribution<mpfr::mpreal, Policy>& /*dist*/)
{
  //using namespace boost::math::constants;
  // Computed using NTL at 150 bit, about 50 decimal digits.
  #ifdef BOOST_MATH_STANDALONE
  static_assert(sizeof(Policy) == 0, "mpreal excess kurtosis can not be calculated in standalone mode");
  #endif

  return boost::lexical_cast<mpfr::mpreal>("0.2450893006876380628486604106197544154170667057995");
  // return -(6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  //   (four_minus_pi<RealType>() * four_minus_pi<RealType>());
} // kurtosis

namespace detail{

//
// Version of Digamma accurate to ~100 decimal digits.
//
template <class Policy>
mpfr::mpreal digamma_imp(mpfr::mpreal x, const std::integral_constant<int, 0>* , const Policy& pol)
{
   //
   // This handles reflection of negative arguments, and all our
   // empfr_classor handling, then forwards to the T-specific approximation.
   //
   BOOST_MATH_STD_USING // ADL of std functions.

   mpfr::mpreal result = 0;
   //
   // Check for negative arguments and use reflection:
   //
   if(x < 0)
   {
      // Reflect:
      x = 1 - x;
      // Argument reduction for tan:
      mpfr::mpreal remainder = x - floor(x);
      // Shift to negative if > 0.5:
      if(remainder > 0.5)
      {
         remainder -= 1;
      }
      //
      // check for evaluation at a negative pole:
      //
      if(remainder == 0)
      {
         return policies::raise_pole_error<mpfr::mpreal>("boost::math::digamma<%1%>(%1%)", 0, (1-x), pol);
      }
      result = constants::pi<mpfr::mpreal>() / tan(constants::pi<mpfr::mpreal>() * remainder);
   }
   result += big_digamma(x);
   return result;
}
//
// Specialisations of this function provides the initial
// starting guess for Halley iteration:
//
template <class Policy>
mpfr::mpreal erf_inv_imp(const mpfr::mpreal& p, const mpfr::mpreal& q, const Policy&, const std::integral_constant<int, 64>*)
{
   BOOST_MATH_STD_USING // for ADL of std names.

   mpfr::mpreal result = 0;
   
   if(p <= 0.5)
   {
      //
      // Evaluate inverse erf using the rational approximation:
      //
      // x = p(p+10)(Y+R(p))
      //
      // Where Y is a constant, and R(p) is optimised for a low
      // absolute empfr_classor compared to |Y|.
      //
      // double: Max empfr_classor found: 2.001849e-18
      // long double: Max empfr_classor found: 1.017064e-20
      // Maximum Deviation Found (actual empfr_classor term at infinite precision) 8.030e-21
      //
      static const float Y = 0.0891314744949340820313f;
      static const mpfr::mpreal P[] = {    
         -0.000508781949658280665617,
         -0.00836874819741736770379,
         0.0334806625409744615033,
         -0.0126926147662974029034,
         -0.0365637971411762664006,
         0.0219878681111168899165,
         0.00822687874676915743155,
         -0.00538772965071242932965
      };
      static const mpfr::mpreal Q[] = {    
         1,
         -0.970005043303290640362,
         -1.56574558234175846809,
         1.56221558398423026363,
         0.662328840472002992063,
         -0.71228902341542847553,
         -0.0527396382340099713954,
         0.0795283687341571680018,
         -0.00233393759374190016776,
         0.000886216390456424707504
      };
      mpfr::mpreal g = p * (p + 10);
      mpfr::mpreal r = tools::evaluate_polynomial(P, p) / tools::evaluate_polynomial(Q, p);
      result = g * Y + g * r;
   }
   else if(q >= 0.25)
   {
      //
      // Rational approximation for 0.5 > q >= 0.25
      //
      // x = sqrt(-2*log(q)) / (Y + R(q))
      //
      // Where Y is a constant, and R(q) is optimised for a low
      // absolute empfr_classor compared to Y.
      //
      // double : Max empfr_classor found: 7.403372e-17
      // long double : Max empfr_classor found: 6.084616e-20
      // Maximum Deviation Found (empfr_classor term) 4.811e-20
      //
      static const float Y = 2.249481201171875f;
      static const mpfr::mpreal P[] = {    
         -0.202433508355938759655,
         0.105264680699391713268,
         8.37050328343119927838,
         17.6447298408374015486,
         -18.8510648058714251895,
         -44.6382324441786960818,
         17.445385985570866523,
         21.1294655448340526258,
         -3.67192254707729348546
      };
      static const mpfr::mpreal Q[] = {    
         1,
         6.24264124854247537712,
         3.9713437953343869095,
         -28.6608180499800029974,
         -20.1432634680485188801,
         48.5609213108739935468,
         10.8268667355460159008,
         -22.6436933413139721736,
         1.72114765761200282724
      };
      mpfr::mpreal g = sqrt(-2 * log(q));
      mpfr::mpreal xs = q - 0.25;
      mpfr::mpreal r = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
      result = g / (Y + r);
   }
   else
   {
      //
      // For q < 0.25 we have a series of rational approximations all
      // of the general form:
      //
      // let: x = sqrt(-log(q))
      //
      // Then the result is given by:
      //
      // x(Y+R(x-B))
      //
      // where Y is a constant, B is the lowest value of x for which 
      // the approximation is valid, and R(x-B) is optimised for a low
      // absolute empfr_classor compared to Y.
      //
      // Note that almost all code will really go through the first
      // or maybe second approximation.  After than we're dealing with very
      // small input values indeed: 80 and 128 bit long double's go all the
      // way down to ~ 1e-5000 so the "tail" is rather long...
      //
      mpfr::mpreal x = sqrt(-log(q));
      if(x < 3)
      {
         // Max empfr_classor found: 1.089051e-20
         static const float Y = 0.807220458984375f;
         static const mpfr::mpreal P[] = {    
            -0.131102781679951906451,
            -0.163794047193317060787,
            0.117030156341995252019,
            0.387079738972604337464,
            0.337785538912035898924,
            0.142869534408157156766,
            0.0290157910005329060432,
            0.00214558995388805277169,
            -0.679465575181126350155e-6,
            0.285225331782217055858e-7,
            -0.681149956853776992068e-9
         };
         static const mpfr::mpreal Q[] = {    
            1,
            3.46625407242567245975,
            5.38168345707006855425,
            4.77846592945843778382,
            2.59301921623620271374,
            0.848854343457902036425,
            0.152264338295331783612,
            0.01105924229346489121
         };
         mpfr::mpreal xs = x - 1.125;
         mpfr::mpreal R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else if(x < 6)
      {
         // Max empfr_classor found: 8.389174e-21
         static const float Y = 0.93995571136474609375f;
         static const mpfr::mpreal P[] = {    
            -0.0350353787183177984712,
            -0.00222426529213447927281,
            0.0185573306514231072324,
            0.00950804701325919603619,
            0.00187123492819559223345,
            0.000157544617424960554631,
            0.460469890584317994083e-5,
            -0.230404776911882601748e-9,
            0.266339227425782031962e-11
         };
         static const mpfr::mpreal Q[] = {    
            1,
            1.3653349817554063097,
            0.762059164553623404043,
            0.220091105764131249824,
            0.0341589143670947727934,
            0.00263861676657015992959,
            0.764675292302794483503e-4
         };
         mpfr::mpreal xs = x - 3;
         mpfr::mpreal R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else if(x < 18)
      {
         // Max empfr_classor found: 1.481312e-19
         static const float Y = 0.98362827301025390625f;
         static const mpfr::mpreal P[] = {    
            -0.0167431005076633737133,
            -0.00112951438745580278863,
            0.00105628862152492910091,
            0.000209386317487588078668,
            0.149624783758342370182e-4,
            0.449696789927706453732e-6,
            0.462596163522878599135e-8,
            -0.281128735628831791805e-13,
            0.99055709973310326855e-16
         };
         static const mpfr::mpreal Q[] = {    
            1,
            0.591429344886417493481,
            0.138151865749083321638,
            0.0160746087093676504695,
            0.000964011807005165528527,
            0.275335474764726041141e-4,
            0.282243172016108031869e-6
         };
         mpfr::mpreal xs = x - 6;
         mpfr::mpreal R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else if(x < 44)
      {
         // Max empfr_classor found: 5.697761e-20
         static const float Y = 0.99714565277099609375f;
         static const mpfr::mpreal P[] = {    
            -0.0024978212791898131227,
            -0.779190719229053954292e-5,
            0.254723037413027451751e-4,
            0.162397777342510920873e-5,
            0.396341011304801168516e-7,
            0.411632831190944208473e-9,
            0.145596286718675035587e-11,
            -0.116765012397184275695e-17
         };
         static const mpfr::mpreal Q[] = {    
            1,
            0.207123112214422517181,
            0.0169410838120975906478,
            0.000690538265622684595676,
            0.145007359818232637924e-4,
            0.144437756628144157666e-6,
            0.509761276599778486139e-9
         };
         mpfr::mpreal xs = x - 18;
         mpfr::mpreal R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else
      {
         // Max empfr_classor found: 1.279746e-20
         static const float Y = 0.99941349029541015625f;
         static const mpfr::mpreal P[] = {    
            -0.000539042911019078575891,
            -0.28398759004727721098e-6,
            0.899465114892291446442e-6,
            0.229345859265920864296e-7,
            0.225561444863500149219e-9,
            0.947846627503022684216e-12,
            0.135880130108924861008e-14,
            -0.348890393399948882918e-21
         };
         static const mpfr::mpreal Q[] = {    
            1,
            0.0845746234001899436914,
            0.00282092984726264681981,
            0.468292921940894236786e-4,
            0.399968812193862100054e-6,
            0.161809290887904476097e-8,
            0.231558608310259605225e-11
         };
         mpfr::mpreal xs = x - 44;
         mpfr::mpreal R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
   }
   return result;
}

inline mpfr::mpreal bessel_i0(mpfr::mpreal x)
{
   #ifdef BOOST_MATH_STANDALONE
   static_assert(sizeof(x) == 0, "mpreal bessel_i0 can not be calculated in standalone mode");
   #endif
    
    static const mpfr::mpreal P1[] = {
        boost::lexical_cast<mpfr::mpreal>("-2.2335582639474375249e+15"),
        boost::lexical_cast<mpfr::mpreal>("-5.5050369673018427753e+14"),
        boost::lexical_cast<mpfr::mpreal>("-3.2940087627407749166e+13"),
        boost::lexical_cast<mpfr::mpreal>("-8.4925101247114157499e+11"),
        boost::lexical_cast<mpfr::mpreal>("-1.1912746104985237192e+10"),
        boost::lexical_cast<mpfr::mpreal>("-1.0313066708737980747e+08"),
        boost::lexical_cast<mpfr::mpreal>("-5.9545626019847898221e+05"),
        boost::lexical_cast<mpfr::mpreal>("-2.4125195876041896775e+03"),
        boost::lexical_cast<mpfr::mpreal>("-7.0935347449210549190e+00"),
        boost::lexical_cast<mpfr::mpreal>("-1.5453977791786851041e-02"),
        boost::lexical_cast<mpfr::mpreal>("-2.5172644670688975051e-05"),
        boost::lexical_cast<mpfr::mpreal>("-3.0517226450451067446e-08"),
        boost::lexical_cast<mpfr::mpreal>("-2.6843448573468483278e-11"),
        boost::lexical_cast<mpfr::mpreal>("-1.5982226675653184646e-14"),
        boost::lexical_cast<mpfr::mpreal>("-5.2487866627945699800e-18"),
    };
    static const mpfr::mpreal Q1[] = {
        boost::lexical_cast<mpfr::mpreal>("-2.2335582639474375245e+15"),
        boost::lexical_cast<mpfr::mpreal>("7.8858692566751002988e+12"),
        boost::lexical_cast<mpfr::mpreal>("-1.2207067397808979846e+10"),
        boost::lexical_cast<mpfr::mpreal>("1.0377081058062166144e+07"),
        boost::lexical_cast<mpfr::mpreal>("-4.8527560179962773045e+03"),
        boost::lexical_cast<mpfr::mpreal>("1.0"),
    };
    static const mpfr::mpreal P2[] = {
        boost::lexical_cast<mpfr::mpreal>("-2.2210262233306573296e-04"),
        boost::lexical_cast<mpfr::mpreal>("1.3067392038106924055e-02"),
        boost::lexical_cast<mpfr::mpreal>("-4.4700805721174453923e-01"),
        boost::lexical_cast<mpfr::mpreal>("5.5674518371240761397e+00"),
        boost::lexical_cast<mpfr::mpreal>("-2.3517945679239481621e+01"),
        boost::lexical_cast<mpfr::mpreal>("3.1611322818701131207e+01"),
        boost::lexical_cast<mpfr::mpreal>("-9.6090021968656180000e+00"),
    };
    static const mpfr::mpreal Q2[] = {
        boost::lexical_cast<mpfr::mpreal>("-5.5194330231005480228e-04"),
        boost::lexical_cast<mpfr::mpreal>("3.2547697594819615062e-02"),
        boost::lexical_cast<mpfr::mpreal>("-1.1151759188741312645e+00"),
        boost::lexical_cast<mpfr::mpreal>("1.3982595353892851542e+01"),
        boost::lexical_cast<mpfr::mpreal>("-6.0228002066743340583e+01"),
        boost::lexical_cast<mpfr::mpreal>("8.5539563258012929600e+01"),
        boost::lexical_cast<mpfr::mpreal>("-3.1446690275135491500e+01"),
        boost::lexical_cast<mpfr::mpreal>("1.0"),
    };
    mpfr::mpreal value, factor, r;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (x < 0)
    {
        x = -x;                         // even function
    }
    if (x == 0)
    {
        return static_cast<mpfr::mpreal>(1);
    }
    if (x <= 15)                        // x in (0, 15]
    {
        mpfr::mpreal y = x * x;
        value = evaluate_polynomial(P1, y) / evaluate_polynomial(Q1, y);
    }
    else                                // x in (15, \infty)
    {
        mpfr::mpreal y = 1 / x - mpfr::mpreal(1) / 15;
        r = evaluate_polynomial(P2, y) / evaluate_polynomial(Q2, y);
        factor = exp(x) / sqrt(x);
        value = factor * r;
    }

    return value;
}

inline mpfr::mpreal bessel_i1(mpfr::mpreal x)
{
    static const mpfr::mpreal P1[] = {
        static_cast<mpfr::mpreal>("-1.4577180278143463643e+15"),
        static_cast<mpfr::mpreal>("-1.7732037840791591320e+14"),
        static_cast<mpfr::mpreal>("-6.9876779648010090070e+12"),
        static_cast<mpfr::mpreal>("-1.3357437682275493024e+11"),
        static_cast<mpfr::mpreal>("-1.4828267606612366099e+09"),
        static_cast<mpfr::mpreal>("-1.0588550724769347106e+07"),
        static_cast<mpfr::mpreal>("-5.1894091982308017540e+04"),
        static_cast<mpfr::mpreal>("-1.8225946631657315931e+02"),
        static_cast<mpfr::mpreal>("-4.7207090827310162436e-01"),
        static_cast<mpfr::mpreal>("-9.1746443287817501309e-04"),
        static_cast<mpfr::mpreal>("-1.3466829827635152875e-06"),
        static_cast<mpfr::mpreal>("-1.4831904935994647675e-09"),
        static_cast<mpfr::mpreal>("-1.1928788903603238754e-12"),
        static_cast<mpfr::mpreal>("-6.5245515583151902910e-16"),
        static_cast<mpfr::mpreal>("-1.9705291802535139930e-19"),
    };
    static const mpfr::mpreal Q1[] = {
        static_cast<mpfr::mpreal>("-2.9154360556286927285e+15"),
        static_cast<mpfr::mpreal>("9.7887501377547640438e+12"),
        static_cast<mpfr::mpreal>("-1.4386907088588283434e+10"),
        static_cast<mpfr::mpreal>("1.1594225856856884006e+07"),
        static_cast<mpfr::mpreal>("-5.1326864679904189920e+03"),
        static_cast<mpfr::mpreal>("1.0"),
    };
    static const mpfr::mpreal P2[] = {
        static_cast<mpfr::mpreal>("1.4582087408985668208e-05"),
        static_cast<mpfr::mpreal>("-8.9359825138577646443e-04"),
        static_cast<mpfr::mpreal>("2.9204895411257790122e-02"),
        static_cast<mpfr::mpreal>("-3.4198728018058047439e-01"),
        static_cast<mpfr::mpreal>("1.3960118277609544334e+00"),
        static_cast<mpfr::mpreal>("-1.9746376087200685843e+00"),
        static_cast<mpfr::mpreal>("8.5591872901933459000e-01"),
        static_cast<mpfr::mpreal>("-6.0437159056137599999e-02"),
    };
    static const mpfr::mpreal Q2[] = {
        static_cast<mpfr::mpreal>("3.7510433111922824643e-05"),
        static_cast<mpfr::mpreal>("-2.2835624489492512649e-03"),
        static_cast<mpfr::mpreal>("7.4212010813186530069e-02"),
        static_cast<mpfr::mpreal>("-8.5017476463217924408e-01"),
        static_cast<mpfr::mpreal>("3.2593714889036996297e+00"),
        static_cast<mpfr::mpreal>("-3.8806586721556593450e+00"),
        static_cast<mpfr::mpreal>("1.0"),
    };
    mpfr::mpreal value, factor, r, w;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    w = abs(x);
    if (x == 0)
    {
        return static_cast<mpfr::mpreal>(0);
    }
    if (w <= 15)                        // w in (0, 15]
    {
        mpfr::mpreal y = x * x;
        r = evaluate_polynomial(P1, y) / evaluate_polynomial(Q1, y);
        factor = w;
        value = factor * r;
    }
    else                                // w in (15, \infty)
    {
        mpfr::mpreal y = 1 / w - mpfr::mpreal(1) / 15;
        r = evaluate_polynomial(P2, y) / evaluate_polynomial(Q2, y);
        factor = exp(w) / sqrt(w);
        value = factor * r;
    }

    if (x < 0)
    {
        value *= -value;                 // odd function
    }
    return value;
}

} // namespace detail
} // namespace math

}

#endif // BOOST_MATH_MPLFR_BINDINGS_HPP


/* mpreal.hpp
+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
*/