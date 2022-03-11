//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2017 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_K0_HPP
#define BOOST_MATH_BESSEL_K0_HPP

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/assert.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

// Modified Bessel function of the second kind of order zero
// minimax rational approximations on intervals, see
// Russon and Blair, Chalk River Report AECL-3461, 1969,
// as revised by Pavel Holoborodko in "Rational Approximations 
// for the Modified Bessel Function of the Second Kind - K0(x) 
// for Computations with Double Precision", see 
// http://www.advanpix.com/2015/11/25/rational-approximations-for-the-modified-bessel-function-of-the-second-kind-k0-for-computations-with-double-precision/
//
// The actual coefficients used are our own derivation (by JM)
// since we extend to both greater and lesser precision than the
// references above.  We can also improve performance WRT to
// Holoborodko without loss of precision.

namespace boost { namespace math { namespace detail{

template <typename T>
T bessel_k0(const T& x);

template <class T, class tag>
struct bessel_k0_initializer
{
   struct init
   {
      init()
      {
         do_init(tag());
      }
      static void do_init(const boost::integral_constant<int, 113>&)
      {
         bessel_k0(T(0.5));
         bessel_k0(T(1.5));
      }
      static void do_init(const boost::integral_constant<int, 64>&)
      {
         bessel_k0(T(0.5));
         bessel_k0(T(1.5));
      }
      template <class U>
      static void do_init(const U&){}
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class tag>
const typename bessel_k0_initializer<T, tag>::init bessel_k0_initializer<T, tag>::initializer;


template <typename T, int N>
T bessel_k0_imp(const T& x, const boost::integral_constant<int, N>&)
{
   BOOST_ASSERT(0);
   return 0;
}

template <typename T>
T bessel_k0_imp(const T& x, const boost::integral_constant<int, 24>&)
{
   BOOST_MATH_STD_USING
   if(x <= 1)
   {
      // Maximum Deviation Found : 2.358e-09
      // Expected Error Term : -2.358e-09
      // Maximum Relative Change in Control Points : 9.552e-02
      // Max Error found at float precision = Poly : 4.448220e-08
      static const T Y = 1.137250900268554688f;
      static const T P[] = 
      {
         -1.372508979104259711e-01f,
         2.622545986273687617e-01f,
         5.047103728247919836e-03f
      };
      static const T Q[] = 
      {
         1.000000000000000000e+00f,
         -8.928694018000029415e-02f,
         2.985980684180969241e-03f
      };
      T a = x * x / 4;
      a = (tools::evaluate_rational(P, Q, a) + Y) * a + 1;

      // Maximum Deviation Found:                     1.346e-09
      // Expected Error Term : -1.343e-09
      // Maximum Relative Change in Control Points : 2.405e-02
      // Max Error found at float precision = Poly : 1.354814e-07
      static const T P2[] = {
         1.159315158e-01f,
         2.789828686e-01f,
         2.524902861e-02f,
         8.457241514e-04f,
         1.530051997e-05f
      };
      return tools::evaluate_polynomial(P2, T(x * x)) - log(x) * a;
   }
   else
   {
      // Maximum Deviation Found:                     1.587e-08
      // Expected Error Term : 1.531e-08
      // Maximum Relative Change in Control Points : 9.064e-02
      // Max Error found at float precision = Poly : 5.065020e-08

      static const T P[] =
      {
         2.533141220e-01f,
         5.221502603e-01f,
         6.380180669e-02f,
         -5.934976547e-02f
      };
      static const T Q[] =
      {
         1.000000000e+00f,
         2.679722431e+00f,
         1.561635813e+00f,
         1.573660661e-01f
      };
      if(x < tools::log_max_value<T>())
         return ((tools::evaluate_rational(P, Q, T(1 / x)) + 1) * exp(-x) / sqrt(x));
      else
      {
         T ex = exp(-x / 2);
         return ((tools::evaluate_rational(P, Q, T(1 / x)) + 1) * ex / sqrt(x)) * ex;
      }
   }
}

template <typename T>
T bessel_k0_imp(const T& x, const boost::integral_constant<int, 53>&)
{
   BOOST_MATH_STD_USING
   if(x <= 1)
   {
      // Maximum Deviation Found:                     6.077e-17
      // Expected Error Term : -6.077e-17
      // Maximum Relative Change in Control Points : 7.797e-02
      // Max Error found at double precision = Poly : 1.003156e-16
      static const T Y = 1.137250900268554688;
      static const T P[] =
      {
         -1.372509002685546267e-01,
         2.574916117833312855e-01,
         1.395474602146869316e-02,
         5.445476986653926759e-04,
         7.125159422136622118e-06
      };
      static const T Q[] =
      {
         1.000000000000000000e+00,
         -5.458333438017788530e-02,
         1.291052816975251298e-03,
         -1.367653946978586591e-05
      };

      T a = x * x / 4;
      a = (tools::evaluate_polynomial(P, a) / tools::evaluate_polynomial(Q, a) + Y) * a + 1;

      // Maximum Deviation Found:                     3.429e-18
      // Expected Error Term : 3.392e-18
      // Maximum Relative Change in Control Points : 2.041e-02
      // Max Error found at double precision = Poly : 2.513112e-16
      static const T P2[] =
      {
         1.159315156584124484e-01,
         2.789828789146031732e-01,
         2.524892993216121934e-02,
         8.460350907213637784e-04,
         1.491471924309617534e-05,
         1.627106892422088488e-07,
         1.208266102392756055e-09,
         6.611686391749704310e-12
      };

      return tools::evaluate_polynomial(P2, T(x * x)) - log(x) * a;
   }
   else
   {
      // Maximum Deviation Found:                     4.316e-17
      // Expected Error Term : 9.570e-18
      // Maximum Relative Change in Control Points : 2.757e-01
      // Max Error found at double precision = Poly : 1.001560e-16

      static const T Y = 1;
      static const T P[] =
      {
         2.533141373155002416e-01,
         3.628342133984595192e+00,
         1.868441889406606057e+01,
         4.306243981063412784e+01,
         4.424116209627428189e+01,
         1.562095339356220468e+01,
         -1.810138978229410898e+00,
         -1.414237994269995877e+00,
         -9.369168119754924625e-02
      };
      static const T Q[] =
      {
         1.000000000000000000e+00,
         1.494194694879908328e+01,
         8.265296455388554217e+01,
         2.162779506621866970e+02,
         2.845145155184222157e+02,
         1.851714491916334995e+02,
         5.486540717439723515e+01,
         6.118075837628957015e+00,
         1.586261269326235053e-01
      };
      if(x < tools::log_max_value<T>())
         return ((tools::evaluate_rational(P, Q, T(1 / x)) + Y) * exp(-x) / sqrt(x));
      else
      {
         T ex = exp(-x / 2);
         return ((tools::evaluate_rational(P, Q, T(1 / x)) + Y) * ex / sqrt(x)) * ex;
      }
   }
}

template <typename T>
T bessel_k0_imp(const T& x, const boost::integral_constant<int, 64>&)
{
   BOOST_MATH_STD_USING
      if(x <= 1)
      {
         // Maximum Deviation Found:                     2.180e-22
         // Expected Error Term : 2.180e-22
         // Maximum Relative Change in Control Points : 2.943e-01
         // Max Error found at float80 precision = Poly : 3.923207e-20
         static const T Y = 1.137250900268554687500e+00;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.372509002685546875002e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.566481981037407600436e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.551881122448948854873e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 6.646112454323276529650e-04),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.213747930378196492543e-05),
            BOOST_MATH_BIG_CONSTANT(T, 64, 9.423709328020389560844e-08)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, -4.843828412587773008342e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.088484822515098936140e-03),
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.374724008530702784829e-05),
            BOOST_MATH_BIG_CONSTANT(T, 64, 8.452665455952581680339e-08)
         };


         T a = x * x / 4;
         a = (tools::evaluate_polynomial(P, a) / tools::evaluate_polynomial(Q, a) + Y) * a + 1;

         // Maximum Deviation Found:                     2.440e-21
         // Expected Error Term : -2.434e-21
         // Maximum Relative Change in Control Points : 2.459e-02
         // Max Error found at float80 precision = Poly : 1.482487e-19
         static const T P2[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.159315156584124488110e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.764832791416047889734e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.926062887220923354112e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.660777862036966089410e-04),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.094942446930673386849e-06)
         };
         static const T Q2[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, -2.156100313881251616320e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.315993873344905957033e-04),
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.529444499350703363451e-06),
            BOOST_MATH_BIG_CONSTANT(T, 64, 5.524988589917857531177e-09)
         };
         return tools::evaluate_rational(P2, Q2, T(x * x)) - log(x) * a;
      }
      else
      {
         // Maximum Deviation Found:                     4.291e-20
         // Expected Error Term : 2.236e-21
         // Maximum Relative Change in Control Points : 3.021e-01
         //Max Error found at float80 precision = Poly : 8.727378e-20
         static const T Y = 1;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.533141373155002512056e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 5.417942070721928652715e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, 4.477464607463971754433e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.838745728725943889876e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 4.009736314927811202517e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 4.557411293123609803452e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.360222564015361268955e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.385435333168505701022e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.750195760942181592050e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, -4.059789241612946683713e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.612783121537333908889e-01)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.200669254769325861404e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.900177593527144126549e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 8.361003989965786932682e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.041319870804843395893e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.828491555113790345068e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.190342229261529076624e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 9.003330795963812219852e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.773371397243777891569e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.368634935531158398439e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.543310879400359967327e-01)
         };
         if(x < tools::log_max_value<T>())
            return ((tools::evaluate_rational(P, Q, T(1 / x)) + Y) * exp(-x) / sqrt(x));
         else
         {
            T ex = exp(-x / 2);
            return ((tools::evaluate_rational(P, Q, T(1 / x)) + Y) * ex / sqrt(x)) * ex;
         }
      }
}

template <typename T>
T bessel_k0_imp(const T& x, const boost::integral_constant<int, 113>&)
{
   BOOST_MATH_STD_USING
      if(x <= 1)
      {
         // Maximum Deviation Found:                     5.682e-37
         // Expected Error Term : 5.682e-37
         // Maximum Relative Change in Control Points : 6.094e-04
         // Max Error found at float128 precision = Poly : 5.338213e-35
         static const T Y = 1.137250900268554687500000000000000000e+00f;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.372509002685546875000000000000000006e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.556212905071072782462974351698081303e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.742459135264203478530904179889103929e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.077860530453688571555479526961318918e-04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.868173911669241091399374307788635148e-05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.496405768838992243478709145123306602e-07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.752489221949580551692915881999762125e-09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.243010555737173524710512824955368526e-12)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.000000000000000000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, -4.095631064064621099785696980653193721e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.313880983725212151967078809725835532e-04),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.095229912293480063501285562382835142e-05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.022828799511943141130509410251996277e-07),
            BOOST_MATH_BIG_CONSTANT(T, 113, -6.860874007419812445494782795829046836e-10),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.107297802344970725756092082686799037e-12),
            BOOST_MATH_BIG_CONSTANT(T, 113, -7.460529579244623559164763757787600944e-15)
         };
         T a = x * x / 4;
         a = (tools::evaluate_rational(P, Q, a) + Y) * a + 1;

         // Maximum Deviation Found:                     5.173e-38
         // Expected Error Term : 5.105e-38
         // Maximum Relative Change in Control Points : 9.734e-03
         // Max Error found at float128 precision = Poly : 1.688806e-34
         static const T P2[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.159315156584124488107200313757741370e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.789828789146031122026800078439435369e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.524892993216269451266750049024628432e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.460350907082229957222453839935101823e-04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.491471929926042875260452849503857976e-05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.627105610481598430816014719558896866e-07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.208426165007797264194914898538250281e-09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 6.508697838747354949164182457073784117e-12),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.659784680639805301101014383907273109e-14),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.531090131964391104248859415958109654e-17),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.205195117066478034260323124669936314e-19),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.692219280289030165761119775783115426e-22),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.362350161092532344171965861545860747e-25),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.277990623924628999539014980773738258e-27)
         };

         return tools::evaluate_polynomial(P2, T(x * x)) - log(x) * a;
      }
      else
      {
         // Maximum Deviation Found:                     1.462e-34
         // Expected Error Term : 4.917e-40
         // Maximum Relative Change in Control Points : 3.385e-01
         // Max Error found at float128 precision = Poly : 1.567573e-34
         static const T Y = 1;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.533141373155002512078826424055226265e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.001949740768235770078339977110749204e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 6.991516715983883248363351472378349986e+02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.429587951594593159075690819360687720e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.911933815201948768044660065771258450e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.769943016204926614862175317962439875e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.170866154649560750500954150401105606e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.634687099724383996792011977705727661e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.989524036456492581597607246664394014e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.160394785715328062088529400178080360e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 9.778173054417826368076483100902201433e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.335667778588806892764139643950439733e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.283635100080306980206494425043706838e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.300616188213640626577036321085025855e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.277591957076162984986406540894621482e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.564360536834214058158565361486115932e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.043505161612403359098596828115690596e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, -7.217035248223503605127967970903027314e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.422938158797326748375799596769964430e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.229125746200586805278634786674745210e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, -4.201632288615609937883545928660649813e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.690820607338480548346746717311811406e+01)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.000000000000000000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.964877874035741452203497983642653107e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.808929943826193766839360018583294769e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.814524004679994110944366890912384139e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.897794522506725610540209610337355118e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.456339470955813675629523617440433672e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.057818717813969772198911392875127212e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.513821619536852436424913886081133209e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 9.255938846873380596038513316919990776e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.537077551699028079347581816919572141e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.176769339768120752974843214652367321e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.828722317390455845253191337207432060e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.698864296569996402006511705803675890e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.007803261356636409943826918468544629e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.016564631288740308993071395104715469e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.595893010619754750655947035567624730e+09),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.241241839120481076862742189989406856e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.168778094393076220871007550235840858e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.156200301360388147635052029404211109e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.752130382550379886741949463587008794e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.370574966987293592457152146806662562e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.871254714311063594080644835895740323e+01)
         };
         if(x < tools::log_max_value<T>())
            return  ((tools::evaluate_rational(P, Q, T(1 / x)) + Y) * exp(-x) / sqrt(x));
         else
         {
            T ex = exp(-x / 2);
            return ((tools::evaluate_rational(P, Q, T(1 / x)) + Y) * ex / sqrt(x)) * ex;
         }
      }
}

template <typename T>
T bessel_k0_imp(const T& x, const boost::integral_constant<int, 0>&)
{
   if(boost::math::tools::digits<T>() <= 24)
      return bessel_k0_imp(x, boost::integral_constant<int, 24>());
   else if(boost::math::tools::digits<T>() <= 53)
      return bessel_k0_imp(x, boost::integral_constant<int, 53>());
   else if(boost::math::tools::digits<T>() <= 64)
      return bessel_k0_imp(x, boost::integral_constant<int, 64>());
   else if(boost::math::tools::digits<T>() <= 113)
      return bessel_k0_imp(x, boost::integral_constant<int, 113>());
   BOOST_ASSERT(0);
   return 0;
}

template <typename T>
inline T bessel_k0(const T& x)
{
   typedef boost::integral_constant<int,
      ((std::numeric_limits<T>::digits == 0) || (std::numeric_limits<T>::radix != 2)) ?
      0 :
      std::numeric_limits<T>::digits <= 24 ?
      24 :
      std::numeric_limits<T>::digits <= 53 ?
      53 :
      std::numeric_limits<T>::digits <= 64 ?
      64 :
      std::numeric_limits<T>::digits <= 113 ?
      113 : -1
   > tag_type;

   bessel_k0_initializer<T, tag_type>::force_instantiate();
   return bessel_k0_imp(x, tag_type());
}

}}} // namespaces

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_BESSEL_K0_HPP


/* bessel_k0.hpp
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
*/