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

#include <boost/config.hpp>
#include <boost/lexical_cast.hpp>

#ifdef BOOST_MSVC
//
// We get a lot of warnings from the gmp, mpfr and gmpfrxx headers, 
// disable them here, so we only see warnings from *our* code:
//
#pragma warning(push)
#pragma warning(disable: 4127 4800 4512)
#endif

#include <mpreal.h>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/bindings/detail/big_digamma.hpp>
#include <boost/math/bindings/detail/big_lanczos.hpp>

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
   return boost::lexical_cast<mpfr::mpreal>("1.1395470994046486574927930193898461120875997958366");
}

template <class Policy>
inline mpfr::mpreal skewness(const rayleigh_distribution<mpfr::mpreal, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  return boost::lexical_cast<mpfr::mpreal>("0.63111065781893713819189935154422777984404221106391");
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 2 * root_pi<RealType>() * pi_minus_three<RealType>() / pow23_four_minus_pi<RealType>();
}

template <class Policy>
inline mpfr::mpreal kurtosis(const rayleigh_distribution<mpfr::mpreal, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
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
  return boost::lexical_cast<mpfr::mpreal>("0.2450893006876380628486604106197544154170667057995");
  // return -(6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  //   (four_minus_pi<RealType>() * four_minus_pi<RealType>());
} // kurtosis

namespace detail{

//
// Version of Digamma accurate to ~100 decimal digits.
//
template <class Policy>
mpfr::mpreal digamma_imp(mpfr::mpreal x, const boost::integral_constant<int, 0>* , const Policy& pol)
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
mpfr::mpreal erf_inv_imp(const mpfr::mpreal& p, const mpfr::mpreal& q, const Policy&, const boost::integral_constant<int, 64>*)
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
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
*/