//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_ERF_INV_HPP
#define BOOST_MATH_SF_ERF_INV_HPP

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4127) // Conditional expression is constant
#pragma warning(disable:4702) // Unreachable code: optimization warning
#endif

#include <type_traits>

namespace boost{ namespace math{ 

namespace detail{
//
// The inverse erf and erfc functions share a common implementation,
// this version is for 80-bit long double's and smaller:
//
template <class T, class Policy>
T erf_inv_imp(const T& p, const T& q, const Policy&, const std::integral_constant<int, 64>*)
{
   BOOST_MATH_STD_USING // for ADL of std names.

   T result = 0;
   
   if(p <= 0.5)
   {
      //
      // Evaluate inverse erf using the rational approximation:
      //
      // x = p(p+10)(Y+R(p))
      //
      // Where Y is a constant, and R(p) is optimised for a low
      // absolute error compared to |Y|.
      //
      // double: Max error found: 2.001849e-18
      // long double: Max error found: 1.017064e-20
      // Maximum Deviation Found (actual error term at infinite precision) 8.030e-21
      //
      static const float Y = 0.0891314744949340820313f;
      static const T P[] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.000508781949658280665617),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00836874819741736770379),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0334806625409744615033),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.0126926147662974029034),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.0365637971411762664006),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0219878681111168899165),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00822687874676915743155),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00538772965071242932965)
      };
      static const T Q[] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.970005043303290640362),
         BOOST_MATH_BIG_CONSTANT(T, 64, -1.56574558234175846809),
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.56221558398423026363),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.662328840472002992063),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.71228902341542847553),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.0527396382340099713954),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0795283687341571680018),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00233393759374190016776),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000886216390456424707504)
      };
      T g = p * (p + 10);
      T r = tools::evaluate_polynomial(P, p) / tools::evaluate_polynomial(Q, p);
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
      // absolute error compared to Y.
      //
      // double : Max error found: 7.403372e-17
      // long double : Max error found: 6.084616e-20
      // Maximum Deviation Found (error term) 4.811e-20
      //
      static const float Y = 2.249481201171875f;
      static const T P[] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.202433508355938759655),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.105264680699391713268),
         BOOST_MATH_BIG_CONSTANT(T, 64, 8.37050328343119927838),
         BOOST_MATH_BIG_CONSTANT(T, 64, 17.6447298408374015486),
         BOOST_MATH_BIG_CONSTANT(T, 64, -18.8510648058714251895),
         BOOST_MATH_BIG_CONSTANT(T, 64, -44.6382324441786960818),
         BOOST_MATH_BIG_CONSTANT(T, 64, 17.445385985570866523),
         BOOST_MATH_BIG_CONSTANT(T, 64, 21.1294655448340526258),
         BOOST_MATH_BIG_CONSTANT(T, 64, -3.67192254707729348546)
      };
      static const T Q[] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, 6.24264124854247537712),
         BOOST_MATH_BIG_CONSTANT(T, 64, 3.9713437953343869095),
         BOOST_MATH_BIG_CONSTANT(T, 64, -28.6608180499800029974),
         BOOST_MATH_BIG_CONSTANT(T, 64, -20.1432634680485188801),
         BOOST_MATH_BIG_CONSTANT(T, 64, 48.5609213108739935468),
         BOOST_MATH_BIG_CONSTANT(T, 64, 10.8268667355460159008),
         BOOST_MATH_BIG_CONSTANT(T, 64, -22.6436933413139721736),
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.72114765761200282724)
      };
      T g = sqrt(-2 * log(q));
      T xs = q - 0.25f;
      T r = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
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
      // absolute error compared to Y.
      //
      // Note that almost all code will really go through the first
      // or maybe second approximation.  After than we're dealing with very
      // small input values indeed: 80 and 128 bit long double's go all the
      // way down to ~ 1e-5000 so the "tail" is rather long...
      //
      T x = sqrt(-log(q));
      if(x < 3)
      {
         // Max error found: 1.089051e-20
         static const float Y = 0.807220458984375f;
         static const T P[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.131102781679951906451),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.163794047193317060787),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.117030156341995252019),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.387079738972604337464),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.337785538912035898924),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.142869534408157156766),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.0290157910005329060432),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.00214558995388805277169),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.679465575181126350155e-6),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.285225331782217055858e-7),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.681149956853776992068e-9)
         };
         static const T Q[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.46625407242567245975),
            BOOST_MATH_BIG_CONSTANT(T, 64, 5.38168345707006855425),
            BOOST_MATH_BIG_CONSTANT(T, 64, 4.77846592945843778382),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.59301921623620271374),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.848854343457902036425),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.152264338295331783612),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.01105924229346489121)
         };
         T xs = x - 1.125f;
         T R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else if(x < 6)
      {
         // Max error found: 8.389174e-21
         static const float Y = 0.93995571136474609375f;
         static const T P[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.0350353787183177984712),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.00222426529213447927281),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.0185573306514231072324),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.00950804701325919603619),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.00187123492819559223345),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.000157544617424960554631),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.460469890584317994083e-5),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.230404776911882601748e-9),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.266339227425782031962e-11)
         };
         static const T Q[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.3653349817554063097),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.762059164553623404043),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.220091105764131249824),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.0341589143670947727934),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.00263861676657015992959),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.764675292302794483503e-4)
         };
         T xs = x - 3;
         T R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else if(x < 18)
      {
         // Max error found: 1.481312e-19
         static const float Y = 0.98362827301025390625f;
         static const T P[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.0167431005076633737133),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.00112951438745580278863),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.00105628862152492910091),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.000209386317487588078668),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.149624783758342370182e-4),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.449696789927706453732e-6),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.462596163522878599135e-8),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.281128735628831791805e-13),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.99055709973310326855e-16)
         };
         static const T Q[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.591429344886417493481),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.138151865749083321638),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.0160746087093676504695),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.000964011807005165528527),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.275335474764726041141e-4),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.282243172016108031869e-6)
         };
         T xs = x - 6;
         T R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else if(x < 44)
      {
         // Max error found: 5.697761e-20
         static const float Y = 0.99714565277099609375f;
         static const T P[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.0024978212791898131227),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.779190719229053954292e-5),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.254723037413027451751e-4),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.162397777342510920873e-5),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.396341011304801168516e-7),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.411632831190944208473e-9),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.145596286718675035587e-11),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.116765012397184275695e-17)
         };
         static const T Q[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.207123112214422517181),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.0169410838120975906478),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.000690538265622684595676),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.145007359818232637924e-4),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.144437756628144157666e-6),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.509761276599778486139e-9)
         };
         T xs = x - 18;
         T R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
      else
      {
         // Max error found: 1.279746e-20
         static const float Y = 0.99941349029541015625f;
         static const T P[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.000539042911019078575891),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.28398759004727721098e-6),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.899465114892291446442e-6),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.229345859265920864296e-7),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.225561444863500149219e-9),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.947846627503022684216e-12),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.135880130108924861008e-14),
            BOOST_MATH_BIG_CONSTANT(T, 64, -0.348890393399948882918e-21)
         };
         static const T Q[] = {    
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.0845746234001899436914),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.00282092984726264681981),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.468292921940894236786e-4),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.399968812193862100054e-6),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.161809290887904476097e-8),
            BOOST_MATH_BIG_CONSTANT(T, 64, 0.231558608310259605225e-11)
         };
         T xs = x - 44;
         T R = tools::evaluate_polynomial(P, xs) / tools::evaluate_polynomial(Q, xs);
         result = Y * x + R * x;
      }
   }
   return result;
}

template <class T, class Policy>
struct erf_roots
{
   boost::math::tuple<T,T,T> operator()(const T& guess)
   {
      BOOST_MATH_STD_USING
      T derivative = sign * (2 / sqrt(constants::pi<T>())) * exp(-(guess * guess));
      T derivative2 = -2 * guess * derivative;
      return boost::math::make_tuple(((sign > 0) ? static_cast<T>(boost::math::erf(guess, Policy()) - target) : static_cast<T>(boost::math::erfc(guess, Policy())) - target), derivative, derivative2);
   }
   erf_roots(T z, int s) : target(z), sign(s) {}
private:
   T target;
   int sign;
};

template <class T, class Policy>
T erf_inv_imp(const T& p, const T& q, const Policy& pol, const std::integral_constant<int, 0>*)
{
   //
   // Generic version, get a guess that's accurate to 64-bits (10^-19)
   //
   T guess = erf_inv_imp(p, q, pol, static_cast<std::integral_constant<int, 64> const*>(0));
   T result;
   //
   // If T has more bit's than 64 in it's mantissa then we need to iterate,
   // otherwise we can just return the result:
   //
   if(policies::digits<T, Policy>() > 64)
   {
      std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
      if(p <= 0.5)
      {
         result = tools::halley_iterate(detail::erf_roots<typename std::remove_cv<T>::type, Policy>(p, 1), guess, static_cast<T>(0), tools::max_value<T>(), (policies::digits<T, Policy>() * 2) / 3, max_iter);
      }
      else
      {
         result = tools::halley_iterate(detail::erf_roots<typename std::remove_cv<T>::type, Policy>(q, -1), guess, static_cast<T>(0), tools::max_value<T>(), (policies::digits<T, Policy>() * 2) / 3, max_iter);
      }
      policies::check_root_iterations<T>("boost::math::erf_inv<%1%>", max_iter, pol);
   }
   else
   {
      result = guess;
   }
   return result;
}

template <class T, class Policy>
struct erf_inv_initializer
{
   struct init
   {
      init()
      {
         do_init();
      }
      static bool is_value_non_zero(T);
      static void do_init()
      {
         // If std::numeric_limits<T>::digits is zero, we must not call
         // our initialization code here as the precision presumably
         // varies at runtime, and will not have been set yet.
         if(std::numeric_limits<T>::digits)
         {
            boost::math::erf_inv(static_cast<T>(0.25), Policy());
            boost::math::erf_inv(static_cast<T>(0.55), Policy());
            boost::math::erf_inv(static_cast<T>(0.95), Policy());
            boost::math::erfc_inv(static_cast<T>(1e-15), Policy());
            // These following initializations must not be called if
            // type T can not hold the relevant values without
            // underflow to zero.  We check this at runtime because
            // some tools such as valgrind silently change the precision
            // of T at runtime, and numeric_limits basically lies!
            if(is_value_non_zero(static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1e-130))))
               boost::math::erfc_inv(static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1e-130)), Policy());

            // Some compilers choke on constants that would underflow, even in code that isn't instantiated
            // so try and filter these cases out in the preprocessor:
#if LDBL_MAX_10_EXP >= 800
            if(is_value_non_zero(static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1e-800))))
               boost::math::erfc_inv(static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1e-800)), Policy());
            if(is_value_non_zero(static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1e-900))))
               boost::math::erfc_inv(static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1e-900)), Policy());
#else
            if(is_value_non_zero(static_cast<T>(BOOST_MATH_HUGE_CONSTANT(T, 64, 1e-800))))
               boost::math::erfc_inv(static_cast<T>(BOOST_MATH_HUGE_CONSTANT(T, 64, 1e-800)), Policy());
            if(is_value_non_zero(static_cast<T>(BOOST_MATH_HUGE_CONSTANT(T, 64, 1e-900))))
               boost::math::erfc_inv(static_cast<T>(BOOST_MATH_HUGE_CONSTANT(T, 64, 1e-900)), Policy());
#endif
         }
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class Policy>
const typename erf_inv_initializer<T, Policy>::init erf_inv_initializer<T, Policy>::initializer;

template <class T, class Policy>
bool erf_inv_initializer<T, Policy>::init::is_value_non_zero(T v)
{
   // This needs to be non-inline to detect whether v is non zero at runtime
   // rather than at compile time, only relevant when running under valgrind
   // which changes long double's to double's on the fly.
   return v != 0;
}

} // namespace detail

template <class T, class Policy>
typename tools::promote_args<T>::type erfc_inv(T z, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;

   //
   // Begin by testing for domain errors, and other special cases:
   //
   static const char* function = "boost::math::erfc_inv<%1%>(%1%, %1%)";
   if((z < 0) || (z > 2))
      return policies::raise_domain_error<result_type>(function, "Argument outside range [0,2] in inverse erfc function (got p=%1%).", z, pol);
   if(z == 0)
      return policies::raise_overflow_error<result_type>(function, 0, pol);
   if(z == 2)
      return -policies::raise_overflow_error<result_type>(function, 0, pol);
   //
   // Normalise the input, so it's in the range [0,1], we will
   // negate the result if z is outside that range.  This is a simple
   // application of the erfc reflection formula: erfc(-z) = 2 - erfc(z)
   //
   result_type p, q, s;
   if(z > 1)
   {
      q = 2 - z;
      p = 1 - q;
      s = -1;
   }
   else
   {
      p = 1 - z;
      q = z;
      s = 1;
   }
   //
   // A bit of meta-programming to figure out which implementation
   // to use, based on the number of bits in the mantissa of T:
   //
   typedef typename policies::precision<result_type, Policy>::type precision_type;
   typedef std::integral_constant<int,
      precision_type::value <= 0 ? 0 :
      precision_type::value <= 64 ? 64 : 0
   > tag_type;
   //
   // Likewise use internal promotion, so we evaluate at a higher
   // precision internally if it's appropriate:
   //
   typedef typename policies::evaluation<result_type, Policy>::type eval_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   detail::erf_inv_initializer<eval_type, forwarding_policy>::force_instantiate();

   //
   // And get the result, negating where required:
   //
   return s * policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::erf_inv_imp(static_cast<eval_type>(p), static_cast<eval_type>(q), forwarding_policy(), static_cast<tag_type const*>(0)), function);
}

template <class T, class Policy>
typename tools::promote_args<T>::type erf_inv(T z, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;

   //
   // Begin by testing for domain errors, and other special cases:
   //
   static const char* function = "boost::math::erf_inv<%1%>(%1%, %1%)";
   if((z < -1) || (z > 1))
      return policies::raise_domain_error<result_type>(function, "Argument outside range [-1, 1] in inverse erf function (got p=%1%).", z, pol);
   if(z == 1)
      return policies::raise_overflow_error<result_type>(function, 0, pol);
   if(z == -1)
      return -policies::raise_overflow_error<result_type>(function, 0, pol);
   if(z == 0)
      return 0;
   //
   // Normalise the input, so it's in the range [0,1], we will
   // negate the result if z is outside that range.  This is a simple
   // application of the erf reflection formula: erf(-z) = -erf(z)
   //
   result_type p, q, s;
   if(z < 0)
   {
      p = -z;
      q = 1 - p;
      s = -1;
   }
   else
   {
      p = z;
      q = 1 - z;
      s = 1;
   }
   //
   // A bit of meta-programming to figure out which implementation
   // to use, based on the number of bits in the mantissa of T:
   //
   typedef typename policies::precision<result_type, Policy>::type precision_type;
   typedef std::integral_constant<int,
      precision_type::value <= 0 ? 0 :
      precision_type::value <= 64 ? 64 : 0
   > tag_type;
   //
   // Likewise use internal promotion, so we evaluate at a higher
   // precision internally if it's appropriate:
   //
   typedef typename policies::evaluation<result_type, Policy>::type eval_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   //
   // Likewise use internal promotion, so we evaluate at a higher
   // precision internally if it's appropriate:
   //
   typedef typename policies::evaluation<result_type, Policy>::type eval_type;

   detail::erf_inv_initializer<eval_type, forwarding_policy>::force_instantiate();
   //
   // And get the result, negating where required:
   //
   return s * policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::erf_inv_imp(static_cast<eval_type>(p), static_cast<eval_type>(q), forwarding_policy(), static_cast<tag_type const*>(0)), function);
}

template <class T>
inline typename tools::promote_args<T>::type erfc_inv(T z)
{
   return erfc_inv(z, policies::policy<>());
}

template <class T>
inline typename tools::promote_args<T>::type erf_inv(T z)
{
   return erf_inv(z, policies::policy<>());
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_SF_ERF_INV_HPP


/* erf_inv.hpp
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
*/