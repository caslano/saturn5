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

namespace boost{ namespace math{ 

namespace detail{
//
// The inverse erf and erfc functions share a common implementation,
// this version is for 80-bit long double's and smaller:
//
template <class T, class Policy>
T erf_inv_imp(const T& p, const T& q, const Policy&, const boost::integral_constant<int, 64>*)
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
T erf_inv_imp(const T& p, const T& q, const Policy& pol, const boost::integral_constant<int, 0>*)
{
   //
   // Generic version, get a guess that's accurate to 64-bits (10^-19)
   //
   T guess = erf_inv_imp(p, q, pol, static_cast<boost::integral_constant<int, 64> const*>(0));
   T result;
   //
   // If T has more bit's than 64 in it's mantissa then we need to iterate,
   // otherwise we can just return the result:
   //
   if(policies::digits<T, Policy>() > 64)
   {
      boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
      if(p <= 0.5)
      {
         result = tools::halley_iterate(detail::erf_roots<typename remove_cv<T>::type, Policy>(p, 1), guess, static_cast<T>(0), tools::max_value<T>(), (policies::digits<T, Policy>() * 2) / 3, max_iter);
      }
      else
      {
         result = tools::halley_iterate(detail::erf_roots<typename remove_cv<T>::type, Policy>(q, -1), guess, static_cast<T>(0), tools::max_value<T>(), (policies::digits<T, Policy>() * 2) / 3, max_iter);
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
   typedef boost::integral_constant<int,
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
   typedef boost::integral_constant<int,
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