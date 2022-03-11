//  Copyright John Maddock 2007, 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ZETA_HPP
#define BOOST_MATH_ZETA_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/sin_pi.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

namespace boost{ namespace math{ namespace detail{

#if 0
//
// This code is commented out because we have a better more rapidly converging series
// now.  Retained for future reference and in case the new code causes any issues down the line....
//

template <class T, class Policy>
struct zeta_series_cache_size
{
   //
   // Work how large to make our cache size when evaluating the series 
   // evaluation:  normally this is just large enough for the series
   // to have converged, but for arbitrary precision types we need a 
   // really large cache to achieve reasonable precision in a reasonable 
   // time.  This is important when constructing rational approximations
   // to zeta for example.
   //
   typedef typename boost::math::policies::precision<T,Policy>::type precision_type;
   typedef typename mpl::if_<
      mpl::less_equal<precision_type, boost::integral_constant<int, 0> >,
      boost::integral_constant<int, 5000>,
      typename mpl::if_<
         mpl::less_equal<precision_type, boost::integral_constant<int, 64> >,
         boost::integral_constant<int, 70>,
         typename mpl::if_<
            mpl::less_equal<precision_type, boost::integral_constant<int, 113> >,
            boost::integral_constant<int, 100>,
            boost::integral_constant<int, 5000>
         >::type
      >::type
   >::type type;
};

template <class T, class Policy>
T zeta_series_imp(T s, T sc, const Policy&)
{
   //
   // Series evaluation from:
   // Havil, J. Gamma: Exploring Euler's Constant. 
   // Princeton, NJ: Princeton University Press, 2003.
   //
   // See also http://mathworld.wolfram.com/RiemannZetaFunction.html
   //
   BOOST_MATH_STD_USING
   T sum = 0;
   T mult = 0.5;
   T change;
   typedef typename zeta_series_cache_size<T,Policy>::type cache_size;
   T powers[cache_size::value] = { 0, };
   unsigned n = 0;
   do{
      T binom = -static_cast<T>(n);
      T nested_sum = 1;
      if(n < sizeof(powers) / sizeof(powers[0]))
         powers[n] = pow(static_cast<T>(n + 1), -s);
      for(unsigned k = 1; k <= n; ++k)
      {
         T p;
         if(k < sizeof(powers) / sizeof(powers[0]))
         {
            p = powers[k];
            //p = pow(k + 1, -s);
         }
         else
            p = pow(static_cast<T>(k + 1), -s);
         nested_sum += binom * p;
        binom *= (k - static_cast<T>(n)) / (k + 1);
      }
      change = mult * nested_sum;
      sum += change;
      mult /= 2;
      ++n;
   }while(fabs(change / sum) > tools::epsilon<T>());

   return sum * 1 / -boost::math::powm1(T(2), sc);
}

//
// Classical p-series:
//
template <class T>
struct zeta_series2
{
   typedef T result_type;
   zeta_series2(T _s) : s(-_s), k(1){}
   T operator()()
   {
      BOOST_MATH_STD_USING
      return pow(static_cast<T>(k++), s);
   }
private:
   T s;
   unsigned k;
};

template <class T, class Policy>
inline T zeta_series2_imp(T s, const Policy& pol)
{
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();;
   zeta_series2<T> f(s);
   T result = tools::sum_series(
      f, 
      policies::get_epsilon<T, Policy>(),
      max_iter);
   policies::check_series_iterations<T>("boost::math::zeta_series2<%1%>(%1%)", max_iter, pol);
   return result;
}
#endif

template <class T, class Policy>
T zeta_polynomial_series(T s, T sc, Policy const &)
{
   //
   // This is algorithm 3 from:
   // 
   // "An Efficient Algorithm for the Riemann Zeta Function", P. Borwein, 
   // Canadian Mathematical Society, Conference Proceedings.
   // See: http://www.cecm.sfu.ca/personal/pborwein/PAPERS/P155.pdf
   //
   BOOST_MATH_STD_USING
   int n = itrunc(T(log(boost::math::tools::epsilon<T>()) / -2));
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
   return -sum / (two_n * (-powm1(T(2), sc)));
}

template <class T, class Policy>
T zeta_imp_prec(T s, T sc, const Policy& pol, const boost::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING
   T result;
   if(s >= policies::digits<T, Policy>())
      return 1;
   result = zeta_polynomial_series(s, sc, pol); 
#if 0
   // Old code archived for future reference:

   //
   // Only use power series if it will converge in 100 
   // iterations or less: the more iterations it consumes
   // the slower convergence becomes so we have to be very 
   // careful in it's usage.
   //
   if (s > -log(tools::epsilon<T>()) / 4.5)
      result = detail::zeta_series2_imp(s, pol);
   else
      result = detail::zeta_series_imp(s, sc, pol);
#endif
   return result;
}

template <class T, class Policy>
inline T zeta_imp_prec(T s, T sc, const Policy&, const boost::integral_constant<int, 53>&)
{
   BOOST_MATH_STD_USING
   T result;
   if(s < 1)
   {
      // Rational Approximation
      // Maximum Deviation Found:                     2.020e-18
      // Expected Error Term:                         -2.020e-18
      // Max error found at double precision:         3.994987e-17
      static const T P[6] = {    
         static_cast<T>(0.24339294433593750202L),
         static_cast<T>(-0.49092470516353571651L),
         static_cast<T>(0.0557616214776046784287L),
         static_cast<T>(-0.00320912498879085894856L),
         static_cast<T>(0.000451534528645796438704L),
         static_cast<T>(-0.933241270357061460782e-5L),
        };
      static const T Q[6] = {    
         static_cast<T>(1L),
         static_cast<T>(-0.279960334310344432495L),
         static_cast<T>(0.0419676223309986037706L),
         static_cast<T>(-0.00413421406552171059003L),
         static_cast<T>(0.00024978985622317935355L),
         static_cast<T>(-0.101855788418564031874e-4L),
      };
      result = tools::evaluate_polynomial(P, sc) / tools::evaluate_polynomial(Q, sc);
      result -= 1.2433929443359375F;
      result += (sc);
      result /= (sc);
   }
   else if(s <= 2)
   {
      // Maximum Deviation Found:        9.007e-20
      // Expected Error Term:            9.007e-20
      static const T P[6] = {    
         static_cast<T>(0.577215664901532860516L),
         static_cast<T>(0.243210646940107164097L),
         static_cast<T>(0.0417364673988216497593L),
         static_cast<T>(0.00390252087072843288378L),
         static_cast<T>(0.000249606367151877175456L),
         static_cast<T>(0.110108440976732897969e-4L),
      };
      static const T Q[6] = {    
         static_cast<T>(1.0),
         static_cast<T>(0.295201277126631761737L),
         static_cast<T>(0.043460910607305495864L),
         static_cast<T>(0.00434930582085826330659L),
         static_cast<T>(0.000255784226140488490982L),
         static_cast<T>(0.10991819782396112081e-4L),
      };
      result = tools::evaluate_polynomial(P, T(-sc)) / tools::evaluate_polynomial(Q, T(-sc));
      result += 1 / (-sc);
   }
   else if(s <= 4)
   {
      // Maximum Deviation Found:          5.946e-22
      // Expected Error Term:              -5.946e-22
      static const float Y = 0.6986598968505859375;
      static const T P[6] = {    
         static_cast<T>(-0.0537258300023595030676L),
         static_cast<T>(0.0445163473292365591906L),
         static_cast<T>(0.0128677673534519952905L),
         static_cast<T>(0.00097541770457391752726L),
         static_cast<T>(0.769875101573654070925e-4L),
         static_cast<T>(0.328032510000383084155e-5L),
      };
      static const T Q[7] = {    
         1.0f,
         static_cast<T>(0.33383194553034051422L),
         static_cast<T>(0.0487798431291407621462L),
         static_cast<T>(0.00479039708573558490716L),
         static_cast<T>(0.000270776703956336357707L),
         static_cast<T>(0.106951867532057341359e-4L),
         static_cast<T>(0.236276623974978646399e-7L),
      };
      result = tools::evaluate_polynomial(P, T(s - 2)) / tools::evaluate_polynomial(Q, T(s - 2));
      result += Y + 1 / (-sc);
   }
   else if(s <= 7)
   {
      // Maximum Deviation Found:                     2.955e-17
      // Expected Error Term:                         2.955e-17
      // Max error found at double precision:         2.009135e-16

      static const T P[6] = {    
         static_cast<T>(-2.49710190602259410021L),
         static_cast<T>(-2.60013301809475665334L),
         static_cast<T>(-0.939260435377109939261L),
         static_cast<T>(-0.138448617995741530935L),
         static_cast<T>(-0.00701721240549802377623L),
         static_cast<T>(-0.229257310594893932383e-4L),
      };
      static const T Q[9] = {    
         1.0f,
         static_cast<T>(0.706039025937745133628L),
         static_cast<T>(0.15739599649558626358L),
         static_cast<T>(0.0106117950976845084417L),
         static_cast<T>(-0.36910273311764618902e-4L),
         static_cast<T>(0.493409563927590008943e-5L),
         static_cast<T>(-0.234055487025287216506e-6L),
         static_cast<T>(0.718833729365459760664e-8L),
         static_cast<T>(-0.1129200113474947419e-9L),
      };
      result = tools::evaluate_polynomial(P, T(s - 4)) / tools::evaluate_polynomial(Q, T(s - 4));
      result = 1 + exp(result);
   }
   else if(s < 15)
   {
      // Maximum Deviation Found:                     7.117e-16
      // Expected Error Term:                         7.117e-16
      // Max error found at double precision:         9.387771e-16
      static const T P[7] = {    
         static_cast<T>(-4.78558028495135619286L),
         static_cast<T>(-1.89197364881972536382L),
         static_cast<T>(-0.211407134874412820099L),
         static_cast<T>(-0.000189204758260076688518L),
         static_cast<T>(0.00115140923889178742086L),
         static_cast<T>(0.639949204213164496988e-4L),
         static_cast<T>(0.139348932445324888343e-5L),
        };
      static const T Q[9] = {    
         1.0f,
         static_cast<T>(0.244345337378188557777L),
         static_cast<T>(0.00873370754492288653669L),
         static_cast<T>(-0.00117592765334434471562L),
         static_cast<T>(-0.743743682899933180415e-4L),
         static_cast<T>(-0.21750464515767984778e-5L),
         static_cast<T>(0.471001264003076486547e-8L),
         static_cast<T>(-0.833378440625385520576e-10L),
         static_cast<T>(0.699841545204845636531e-12L),
        };
      result = tools::evaluate_polynomial(P, T(s - 7)) / tools::evaluate_polynomial(Q, T(s - 7));
      result = 1 + exp(result);
   }
   else if(s < 36)
   {
      // Max error in interpolated form:             1.668e-17
      // Max error found at long double precision:   1.669714e-17
      static const T P[8] = {    
         static_cast<T>(-10.3948950573308896825L),
         static_cast<T>(-2.85827219671106697179L),
         static_cast<T>(-0.347728266539245787271L),
         static_cast<T>(-0.0251156064655346341766L),
         static_cast<T>(-0.00119459173416968685689L),
         static_cast<T>(-0.382529323507967522614e-4L),
         static_cast<T>(-0.785523633796723466968e-6L),
         static_cast<T>(-0.821465709095465524192e-8L),
      };
      static const T Q[10] = {    
         1.0f,
         static_cast<T>(0.208196333572671890965L),
         static_cast<T>(0.0195687657317205033485L),
         static_cast<T>(0.00111079638102485921877L),
         static_cast<T>(0.408507746266039256231e-4L),
         static_cast<T>(0.955561123065693483991e-6L),
         static_cast<T>(0.118507153474022900583e-7L),
         static_cast<T>(0.222609483627352615142e-14L),
      };
      result = tools::evaluate_polynomial(P, T(s - 15)) / tools::evaluate_polynomial(Q, T(s - 15));
      result = 1 + exp(result);
   }
   else if(s < 56)
   {
      result = 1 + pow(T(2), -s);
   }
   else
   {
      result = 1;
   }
   return result;
}

template <class T, class Policy>
T zeta_imp_prec(T s, T sc, const Policy&, const boost::integral_constant<int, 64>&)
{
   BOOST_MATH_STD_USING
   T result;
   if(s < 1)
   {
      // Rational Approximation
      // Maximum Deviation Found:                     3.099e-20
      // Expected Error Term:                         3.099e-20
      // Max error found at long double precision:    5.890498e-20
      static const T P[6] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.243392944335937499969),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.496837806864865688082),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0680008039723709987107),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00511620413006619942112),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000455369899250053003335),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.279496685273033761927e-4),
        };
      static const T Q[7] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.30425480068225790522),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.050052748580371598736),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00519355671064700627862),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000360623385771198350257),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.159600883054550987633e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.339770279812410586032e-6),
      };
      result = tools::evaluate_polynomial(P, sc) / tools::evaluate_polynomial(Q, sc);
      result -= 1.2433929443359375F;
      result += (sc);
      result /= (sc);
   }
   else if(s <= 2)
   {
      // Maximum Deviation Found:                     1.059e-21
      // Expected Error Term:                         1.059e-21
      // Max error found at long double precision:    1.626303e-19

      static const T P[6] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.577215664901532860605),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.222537368917162139445),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0356286324033215682729),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00304465292366350081446),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000178102511649069421904),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.700867470265983665042e-5),
      };
      static const T Q[7] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.259385759149531030085),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0373974962106091316854),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00332735159183332820617),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000188690420706998606469),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.635994377921861930071e-5),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.226583954978371199405e-7),
      };
      result = tools::evaluate_polynomial(P, T(-sc)) / tools::evaluate_polynomial(Q, T(-sc));
      result += 1 / (-sc);
   }
   else if(s <= 4)
   {
      // Maximum Deviation Found:          5.946e-22
      // Expected Error Term:              -5.946e-22
      static const float Y = 0.6986598968505859375;
      static const T P[7] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.053725830002359501027),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0470551187571475844778),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0101339410415759517471),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00100240326666092854528),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.685027119098122814867e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.390972820219765942117e-5),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.540319769113543934483e-7),
      };
      static const T Q[8] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.286577739726542730421),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0447355811517733225843),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00430125107610252363302),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000284956969089786662045),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.116188101609848411329e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.278090318191657278204e-6),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.19683620233222028478e-8),
      };
      result = tools::evaluate_polynomial(P, T(s - 2)) / tools::evaluate_polynomial(Q, T(s - 2));
      result += Y + 1 / (-sc);
   }
   else if(s <= 7)
   {
      // Max error found at long double precision: 8.132216e-19
      static const T P[8] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, -2.49710190602259407065),
         BOOST_MATH_BIG_CONSTANT(T, 64, -3.36664913245960625334),
         BOOST_MATH_BIG_CONSTANT(T, 64, -1.77180020623777595452),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.464717885249654313933),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.0643694921293579472583),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00464265386202805715487),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.000165556579779704340166),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.252884970740994069582e-5),
      };
      static const T Q[9] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.01300131390690459085),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.387898115758643503827),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0695071490045701135188),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00586908595251442839291),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000217752974064612188616),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.397626583349419011731e-5),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.927884739284359700764e-8),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.119810501805618894381e-9),
      };
      result = tools::evaluate_polynomial(P, T(s - 4)) / tools::evaluate_polynomial(Q, T(s - 4));
      result = 1 + exp(result);
   }
   else if(s < 15)
   {
      // Max error in interpolated form:              1.133e-18
      // Max error found at long double precision:    2.183198e-18
      static const T P[9] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, -4.78558028495135548083),
         BOOST_MATH_BIG_CONSTANT(T, 64, -3.23873322238609358947),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.892338582881021799922),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.131326296217965913809),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.0115651591773783712996),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.000657728968362695775205),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.252051328129449973047e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.626503445372641798925e-6),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.815696314790853893484e-8),
        };
      static const T Q[9] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.525765665400123515036),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.10852641753657122787),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0115669945375362045249),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.000732896513858274091966),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.30683952282420248448e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.819649214609633126119e-6),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.117957556472335968146e-7),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.193432300973017671137e-12),
        };
      result = tools::evaluate_polynomial(P, T(s - 7)) / tools::evaluate_polynomial(Q, T(s - 7));
      result = 1 + exp(result);
   }
   else if(s < 42)
   {
      // Max error in interpolated form:             1.668e-17
      // Max error found at long double precision:   1.669714e-17
      static const T P[9] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, -10.3948950573308861781),
         BOOST_MATH_BIG_CONSTANT(T, 64, -2.82646012777913950108),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.342144362739570333665),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.0249285145498722647472),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.00122493108848097114118),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.423055371192592850196e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.1025215577185967488e-5),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.165096762663509467061e-7),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.145392555873022044329e-9),
      };
      static const T Q[10] = {    
         BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.205135978585281988052),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.0192359357875879453602),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.00111496452029715514119),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.434928449016693986857e-4),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.116911068726610725891e-5),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.206704342290235237475e-7),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.209772836100827647474e-9),
         BOOST_MATH_BIG_CONSTANT(T, 64, -0.939798249922234703384e-16),
         BOOST_MATH_BIG_CONSTANT(T, 64, 0.264584017421245080294e-18),
      };
      result = tools::evaluate_polynomial(P, T(s - 15)) / tools::evaluate_polynomial(Q, T(s - 15));
      result = 1 + exp(result);
   }
   else if(s < 63)
   {
      result = 1 + pow(T(2), -s);
   }
   else
   {
      result = 1;
   }
   return result;
}

template <class T, class Policy>
T zeta_imp_prec(T s, T sc, const Policy&, const boost::integral_constant<int, 113>&)
{
   BOOST_MATH_STD_USING
   T result;
   if(s < 1)
   {
      // Rational Approximation
      // Maximum Deviation Found:                     9.493e-37
      // Expected Error Term:                         9.492e-37
      // Max error found at long double precision:    7.281332e-31

      static const T P[10] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, -1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0353008629988648122808504280990313668),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0107795651204927743049369868548706909),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000523961870530500751114866884685172975),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.661805838304910731947595897966487515e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.658932670403818558510656304189164638e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.103437265642266106533814021041010453e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.116818787212666457105375746642927737e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.660690993901506912123512551294239036e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.113103113698388531428914333768142527e-10),
        };
      static const T Q[11] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.387483472099602327112637481818565459),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0802265315091063135271497708694776875),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0110727276164171919280036408995078164),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00112552716946286252000434849173787243),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.874554160748626916455655180296834352e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.530097847491828379568636739662278322e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.248461553590496154705565904497247452e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.881834921354014787309644951507523899e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.217062446168217797598596496310953025e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.315823200002384492377987848307151168e-11),
      };
      result = tools::evaluate_polynomial(P, sc) / tools::evaluate_polynomial(Q, sc);
      result += (sc);
      result /= (sc);
   }
   else if(s <= 2)
   {
      // Maximum Deviation Found:                     1.616e-37
      // Expected Error Term:                         -1.615e-37

      static const T P[10] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.577215664901532860606512090082402431),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.255597968739771510415479842335906308),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0494056503552807274142218876983542205),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00551372778611700965268920983472292325),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00043667616723970574871427830895192731),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.268562259154821957743669387915239528e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.109249633923016310141743084480436612e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.273895554345300227466534378753023924e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.583103205551702720149237384027795038e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.835774625259919268768735944711219256e-11),
      };
      static const T Q[11] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.316661751179735502065583176348292881),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0540401806533507064453851182728635272),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00598621274107420237785899476374043797),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000474907812321704156213038740142079615),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.272125421722314389581695715835862418e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.112649552156479800925522445229212933e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.301838975502992622733000078063330461e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.422960728687211282539769943184270106e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.377105263588822468076813329270698909e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.581926559304525152432462127383600681e-13),
      };
      result = tools::evaluate_polynomial(P, T(-sc)) / tools::evaluate_polynomial(Q, T(-sc));
      result += 1 / (-sc);
   }
   else if(s <= 4)
   {
      // Maximum Deviation Found:                     1.891e-36
      // Expected Error Term:                         -1.891e-36
      // Max error found: 2.171527e-35

      static const float Y = 0.6986598968505859375;
      static const T P[11] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0537258300023595010275848333539748089),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0429086930802630159457448174466342553),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0136148228754303412510213395034056857),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00190231601036042925183751238033763915),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000186880390916311438818302549192456581),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.145347370745893262394287982691323657e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.805843276446813106414036600485884885e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.340818159286739137503297172091882574e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.115762357488748996526167305116837246e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.231904754577648077579913403645767214e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.340169592866058506675897646629036044e-12),
      };
      static const T Q[12] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.363755247765087100018556983050520554),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0696581979014242539385695131258321598),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00882208914484611029571547753782014817),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000815405623261946661762236085660996718),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.571366167062457197282642344940445452e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.309278269271853502353954062051797838e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.12822982083479010834070516053794262e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.397876357325018976733953479182110033e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.8484432107648683277598472295289279e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.105677416606909614301995218444080615e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.547223964564003701979951154093005354e-15),
      };
      result = tools::evaluate_polynomial(P, T(s - 2)) / tools::evaluate_polynomial(Q, T(s - 2));
      result += Y + 1 / (-sc);
   }
   else if(s <= 6)
   {
      // Max error in interpolated form:             1.510e-37
      // Max error found at long double precision:   2.769266e-34

      static const T Y = 3.28348541259765625F;

      static const T P[13] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.786383506575062179339611614117697622),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.495766593395271370974685959652073976),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.409116737851754766422360889037532228),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.57340744006238263817895456842655987),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.280479899797421910694892949057963111),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0753148409447590257157585696212649869),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0122934003684672788499099362823748632),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.00126148398446193639247961370266962927),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.828465038179772939844657040917364896e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.361008916706050977143208468690645684e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.109879825497910544424797771195928112e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.214539416789686920918063075528797059e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.15090220092460596872172844424267351e-10),
      };
      static const T Q[14] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.69490865837142338462982225731926485),
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.22697696630994080733321401255942464),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.495409420862526540074366618006341533),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.122368084916843823462872905024259633),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0191412993625268971656513890888208623),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00191401538628980617753082598351559642),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000123318142456272424148930280876444459),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.531945488232526067889835342277595709e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.161843184071894368337068779669116236e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.305796079600152506743828859577462778e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.233582592298450202680170811044408894e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.275363878344548055574209713637734269e-13),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.221564186807357535475441900517843892e-15),
      };
      result = tools::evaluate_polynomial(P, T(s - 4)) / tools::evaluate_polynomial(Q, T(s - 4));
      result -= Y;
      result = 1 + exp(result);
   }
   else if(s < 10)
   {
      // Max error in interpolated form:             1.999e-34
      // Max error found at long double precision:   2.156186e-33

      static const T P[13] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, -4.0545627381873738086704293881227365),
         BOOST_MATH_BIG_CONSTANT(T, 113, -4.70088348734699134347906176097717782),
         BOOST_MATH_BIG_CONSTANT(T, 113, -2.36921550900925512951976617607678789),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.684322583796369508367726293719322866),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.126026534540165129870721937592996324),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.015636903921778316147260572008619549),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.00135442294754728549644376325814460807),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.842793965853572134365031384646117061e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.385602133791111663372015460784978351e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.130458500394692067189883214401478539e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.315861074947230418778143153383660035e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.500334720512030826996373077844707164e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.420204769185233365849253969097184005e-12),
        };
      static const T Q[14] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.97663511666410096104783358493318814),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.40878780231201806504987368939673249),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0963890666609396058945084107597727252),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0142207619090854604824116070866614505),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00139010220902667918476773423995750877),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.940669540194694997889636696089994734e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.458220848507517004399292480807026602e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.16345521617741789012782420625435495e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.414007452533083304371566316901024114e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.68701473543366328016953742622661377e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.603461891080716585087883971886075863e-12),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.294670713571839023181857795866134957e-16),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.147003914536437243143096875069813451e-18),
        };
      result = tools::evaluate_polynomial(P, T(s - 6)) / tools::evaluate_polynomial(Q, T(s - 6));
      result = 1 + exp(result);
   }
   else if(s < 17)
   {
      // Max error in interpolated form:             1.641e-32
      // Max error found at long double precision:   1.696121e-32
      static const T P[13] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, -6.91319491921722925920883787894829678),
         BOOST_MATH_BIG_CONSTANT(T, 113, -3.65491257639481960248690596951049048),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.813557553449954526442644544105257881),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0994317301685870959473658713841138083),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.00726896610245676520248617014211734906),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.000317253318715075854811266230916762929),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.66851422826636750855184211580127133e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.879464154730985406003332577806849971e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.113838903158254250631678791998294628e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.379184410304927316385211327537817583e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.612992858643904887150527613446403867e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.347873737198164757035457841688594788e-13),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.289187187441625868404494665572279364e-15),
        };
      static const T Q[14] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.427310044448071818775721584949868806),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.074602514873055756201435421385243062),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00688651562174480772901425121653945942),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000360174847635115036351323894321880445),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.973556847713307543918865405758248777e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.853455848314516117964634714780874197e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.118203513654855112421673192194622826e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.462521662511754117095006543363328159e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.834212591919475633107355719369463143e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.5354594751002702935740220218582929e-13),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.406451690742991192964889603000756203e-15),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.887948682401000153828241615760146728e-19),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.34980761098820347103967203948619072e-21),
        };
      result = tools::evaluate_polynomial(P, T(s - 10)) / tools::evaluate_polynomial(Q, T(s - 10));
      result = 1 + exp(result);
   }
   else if(s < 30)
   {
      // Max error in interpolated form:             1.563e-31
      // Max error found at long double precision:   1.562725e-31

      static const T P[13] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, -11.7824798233959252791987402769438322),
         BOOST_MATH_BIG_CONSTANT(T, 113, -4.36131215284987731928174218354118102),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.732260980060982349410898496846972204),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0744985185694913074484248803015717388),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.00517228281320594683022294996292250527),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.000260897206152101522569969046299309939),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.989553462123121764865178453128769948e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.286916799741891410827712096608826167e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.637262477796046963617949532211619729e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.106796831465628373325491288787760494e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.129343095511091870860498356205376823e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.102397936697965977221267881716672084e-13),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.402663128248642002351627980255756363e-16),
      };
      static const T Q[14] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.311288325355705609096155335186466508),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0438318468940415543546769437752132748),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00374396349183199548610264222242269536),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.000218707451200585197339671707189281302),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.927578767487930747532953583797351219e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.294145760625753561951137473484889639e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.704618586690874460082739479535985395e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.126333332872897336219649130062221257e-9),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.16317315713773503718315435769352765e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.137846712823719515148344938160275695e-13),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.580975420554224366450994232723910583e-16),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.291354445847552426900293580511392459e-22),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.73614324724785855925025452085443636e-25),
      };
      result = tools::evaluate_polynomial(P, T(s - 17)) / tools::evaluate_polynomial(Q, T(s - 17));
      result = 1 + exp(result);
   }
   else if(s < 74)
   {
      // Max error in interpolated form:             2.311e-27
      // Max error found at long double precision:   2.297544e-27
      static const T P[14] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, -20.7944102007844314586649688802236072),
         BOOST_MATH_BIG_CONSTANT(T, 113, -4.95759941987499442499908748130192187),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.563290752832461751889194629200298688),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0406197001137935911912457120706122877),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.0020846534789473022216888863613422293),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.808095978462109173749395599401375667e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.244706022206249301640890603610060959e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.589477682919645930544382616501666572e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.113699573675553496343617442433027672e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.174767860183598149649901223128011828e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.210051620306761367764549971980026474e-12),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.189187969537370950337212675466400599e-14),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.116313253429564048145641663778121898e-16),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.376708747782400769427057630528578187e-19),
      };
      static const T Q[16] = {    
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.205076752981410805177554569784219717),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0202526722696670378999575738524540269),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.001278305290005994980069466658219057),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.576404779858501791742255670403304787e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.196477049872253010859712483984252067e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.521863830500876189501054079974475762e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.109524209196868135198775445228552059e-8),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.181698713448644481083966260949267825e-10),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.234793316975091282090312036524695562e-12),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.227490441461460571047545264251399048e-14),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.151500292036937400913870642638520668e-16),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.543475775154780935815530649335936121e-19),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.241647013434111434636554455083309352e-28),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.557103423021951053707162364713587374e-31),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.618708773442584843384712258199645166e-34),
      };
      result = tools::evaluate_polynomial(P, T(s - 30)) / tools::evaluate_polynomial(Q, T(s - 30));
      result = 1 + exp(result);
   }
   else if(s < 117)
   {
      result = 1 + pow(T(2), -s);
   }
   else
   {
      result = 1;
   }
   return result;
}

template <class T, class Policy>
T zeta_imp_odd_integer(int s, const T&, const Policy&, const true_type&)
{
   static const T results[] = {
      BOOST_MATH_BIG_CONSTANT(T, 113, 1.2020569031595942853997381615114500), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0369277551433699263313654864570342), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0083492773819228268397975498497968), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0020083928260822144178527692324121), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0004941886041194645587022825264699), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0001227133475784891467518365263574), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000305882363070204935517285106451), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000076371976378997622736002935630), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000019082127165539389256569577951), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000004769329867878064631167196044), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000001192199259653110730677887189), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000298035035146522801860637051), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000074507117898354294919810042), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000018626597235130490064039099), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000004656629065033784072989233), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000001164155017270051977592974), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000291038504449709968692943), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000072759598350574810145209), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000018189896503070659475848), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000004547473783042154026799), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000001136868407680227849349), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000284217097688930185546), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000071054273952108527129), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000017763568435791203275), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000004440892103143813364), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000001110223025141066134), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000277555756213612417), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000069388939045441537), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000017347234760475766), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000004336808690020650), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000001084202172494241), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000271050543122347), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000067762635780452), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000016940658945098), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000004235164736273), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000001058791184068), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000264697796017), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000066174449004), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000016543612251), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000004135903063), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000001033975766), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000258493941), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000064623485), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000016155871), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000004038968), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000001009742), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000252435), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000063109), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000015777), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000003944), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000000986), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000000247), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000000062), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000000015), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000000004), BOOST_MATH_BIG_CONSTANT(T, 113, 1.0000000000000000000000000000000001),
   };
   return s > 113 ? 1 : results[(s - 3) / 2];
}

template <class T, class Policy>
T zeta_imp_odd_integer(int s, const T& sc, const Policy& pol, const false_type&)
{
   static BOOST_MATH_THREAD_LOCAL bool is_init = false;
   static BOOST_MATH_THREAD_LOCAL T results[50] = {};
   static BOOST_MATH_THREAD_LOCAL int digits = tools::digits<T>();
   int current_digits = tools::digits<T>();
   if(digits != current_digits)
   {
      // Oh my precision has changed...
      is_init = false;
   }
   if(!is_init)
   {
      is_init = true;
      digits = current_digits;
      for(unsigned k = 0; k < sizeof(results) / sizeof(results[0]); ++k)
      {
         T arg = k * 2 + 3;
         T c_arg = 1 - arg;
         results[k] = zeta_polynomial_series(arg, c_arg, pol);
      }
   }
   unsigned index = (s - 3) / 2;
   return index >= sizeof(results) / sizeof(results[0]) ? zeta_polynomial_series(T(s), sc, pol): results[index];
}

template <class T, class Policy, class Tag>
T zeta_imp(T s, T sc, const Policy& pol, const Tag& tag)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::zeta<%1%>";
   if(sc == 0)
      return policies::raise_pole_error<T>(
         function, 
         "Evaluation of zeta function at pole %1%", 
         s, pol);
   T result;
   //
   // Trivial case:
   //
   if(s > policies::digits<T, Policy>())
      return 1;
   //
   // Start by seeing if we have a simple closed form:
   //
   if(floor(s) == s)
   {
#ifndef BOOST_NO_EXCEPTIONS
      // Without exceptions we expect itrunc to return INT_MAX on overflow
      // and we fall through anyway.
      try
      {
#endif
         int v = itrunc(s);
         if(v == s)
         {
            if(v < 0)
            {
               if(((-v) & 1) == 0)
                  return 0;
               int n = (-v + 1) / 2;
               if(n <= (int)boost::math::max_bernoulli_b2n<T>::value)
                  return T((-v & 1) ? -1 : 1) * boost::math::unchecked_bernoulli_b2n<T>(n) / (1 - v);
            }
            else if((v & 1) == 0)
            {
               if(((v / 2) <= (int)boost::math::max_bernoulli_b2n<T>::value) && (v <= (int)boost::math::max_factorial<T>::value))
                  return T(((v / 2 - 1) & 1) ? -1 : 1) * ldexp(T(1), v - 1) * pow(constants::pi<T, Policy>(), v) *
                     boost::math::unchecked_bernoulli_b2n<T>(v / 2) / boost::math::unchecked_factorial<T>(v);
               return T(((v / 2 - 1) & 1) ? -1 : 1) * ldexp(T(1), v - 1) * pow(constants::pi<T, Policy>(), v) *
                  boost::math::bernoulli_b2n<T>(v / 2) / boost::math::factorial<T>(v);
            }
            else
               return zeta_imp_odd_integer(v, sc, pol, boost::integral_constant<bool, (Tag::value <= 113) && Tag::value>());
         }
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(const boost::math::rounding_error&){} // Just fall through, s is too large to round
      catch(const std::overflow_error&){}
#endif
   }

   if(fabs(s) < tools::root_epsilon<T>())
   {
      result = -0.5f - constants::log_root_two_pi<T, Policy>() * s;
   }
   else if(s < 0)
   {
      std::swap(s, sc);
      if(floor(sc/2) == sc/2)
         result = 0;
      else
      {
         if(s > max_factorial<T>::value)
         {
            T mult = boost::math::sin_pi(0.5f * sc, pol) * 2 * zeta_imp(s, sc, pol, tag);
            result = boost::math::lgamma(s, pol);
            result -= s * log(2 * constants::pi<T>());
            if(result > tools::log_max_value<T>())
               return sign(mult) * policies::raise_overflow_error<T>(function, 0, pol);
            result = exp(result);
            if(tools::max_value<T>() / fabs(mult) < result)
               return boost::math::sign(mult) * policies::raise_overflow_error<T>(function, 0, pol);
            result *= mult;
         }
         else
         {
            result = boost::math::sin_pi(0.5f * sc, pol)
               * 2 * pow(2 * constants::pi<T>(), -s) 
               * boost::math::tgamma(s, pol) 
               * zeta_imp(s, sc, pol, tag);
         }
      }
   }
   else
   {
      result = zeta_imp_prec(s, sc, pol, tag);
   }
   return result;
}

template <class T, class Policy, class tag>
struct zeta_initializer
{
   struct init
   {
      init()
      {
         do_init(tag());
      }
      static void do_init(const boost::integral_constant<int, 0>&){ boost::math::zeta(static_cast<T>(5), Policy()); }
      static void do_init(const boost::integral_constant<int, 53>&){ boost::math::zeta(static_cast<T>(5), Policy()); }
      static void do_init(const boost::integral_constant<int, 64>&)
      {
         boost::math::zeta(static_cast<T>(0.5), Policy());
         boost::math::zeta(static_cast<T>(1.5), Policy());
         boost::math::zeta(static_cast<T>(3.5), Policy());
         boost::math::zeta(static_cast<T>(6.5), Policy());
         boost::math::zeta(static_cast<T>(14.5), Policy());
         boost::math::zeta(static_cast<T>(40.5), Policy());

         boost::math::zeta(static_cast<T>(5), Policy());
      }
      static void do_init(const boost::integral_constant<int, 113>&)
      {
         boost::math::zeta(static_cast<T>(0.5), Policy());
         boost::math::zeta(static_cast<T>(1.5), Policy());
         boost::math::zeta(static_cast<T>(3.5), Policy());
         boost::math::zeta(static_cast<T>(5.5), Policy());
         boost::math::zeta(static_cast<T>(9.5), Policy());
         boost::math::zeta(static_cast<T>(16.5), Policy());
         boost::math::zeta(static_cast<T>(25.5), Policy());
         boost::math::zeta(static_cast<T>(70.5), Policy());

         boost::math::zeta(static_cast<T>(5), Policy());
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class Policy, class tag>
const typename zeta_initializer<T, Policy, tag>::init zeta_initializer<T, Policy, tag>::initializer;

} // detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type zeta(T s, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::precision<result_type, Policy>::type precision_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   typedef boost::integral_constant<int,
      precision_type::value <= 0 ? 0 :
      precision_type::value <= 53 ? 53 :
      precision_type::value <= 64 ? 64 :
      precision_type::value <= 113 ? 113 : 0
   > tag_type;

   detail::zeta_initializer<value_type, forwarding_policy, tag_type>::force_instantiate();

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(detail::zeta_imp(
      static_cast<value_type>(s),
      static_cast<value_type>(1 - static_cast<value_type>(s)),
      forwarding_policy(),
      tag_type()), "boost::math::zeta<%1%>(%1%)");
}

template <class T>
inline typename tools::promote_args<T>::type zeta(T s)
{
   return zeta(s, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ZETA_HPP




/* zeta.hpp
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
*/