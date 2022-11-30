//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2017 John Maddock 
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_K1_HPP
#define BOOST_MATH_BESSEL_K1_HPP

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/assert.hpp>

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
// http://www.advanpix.com/2016/01/05/rational-approximations-for-the-modified-bessel-function-of-the-second-kind-k1-for-computations-with-double-precision/
//
// The actual coefficients used are our own derivation (by JM)
// since we extend to both greater and lesser precision than the
// references above.  We can also improve performance WRT to
// Holoborodko without loss of precision.

namespace boost { namespace math { namespace detail{

   template <typename T>
   T bessel_k1(const T&);

   template <class T, class tag>
   struct bessel_k1_initializer
   {
      struct init
      {
         init()
         {
            do_init(tag());
         }
         static void do_init(const std::integral_constant<int, 113>&)
         {
            bessel_k1(T(0.5));
            bessel_k1(T(2));
            bessel_k1(T(6));
         }
         static void do_init(const std::integral_constant<int, 64>&)
         {
            bessel_k1(T(0.5));
            bessel_k1(T(6));
         }
         template <class U>
         static void do_init(const U&) {}
         void force_instantiate()const {}
      };
      static const init initializer;
      static void force_instantiate()
      {
         initializer.force_instantiate();
      }
   };

   template <class T, class tag>
   const typename bessel_k1_initializer<T, tag>::init bessel_k1_initializer<T, tag>::initializer;


   template <typename T, int N>
   inline T bessel_k1_imp(const T&, const std::integral_constant<int, N>&)
   {
      BOOST_MATH_ASSERT(0);
      return 0;
   }

   template <typename T>
   T bessel_k1_imp(const T& x, const std::integral_constant<int, 24>&)
   {
      BOOST_MATH_STD_USING
      if(x <= 1)
      {
         // Maximum Deviation Found:                     3.090e-12
         // Expected Error Term : -3.053e-12
         // Maximum Relative Change in Control Points : 4.927e-02
         // Max Error found at float precision = Poly : 7.918347e-10
         static const T Y = 8.695471287e-02f;
         static const T P[] =
         {
            -3.621379531e-03f,
            7.131781976e-03f,
            -1.535278300e-05f
         };
         static const T Q[] =
         {
            1.000000000e+00f,
            -5.173102701e-02f,
            9.203530671e-04f
         };

         T a = x * x / 4;
         a = ((tools::evaluate_rational(P, Q, a) + Y) * a * a + a / 2 + 1) * x / 2;

         // Maximum Deviation Found:                     3.556e-08
         // Expected Error Term : -3.541e-08
         // Maximum Relative Change in Control Points : 8.203e-02
         static const T P2[] =
         {
            -3.079657469e-01f,
            -8.537108913e-02f,
            -4.640275408e-03f,
            -1.156442414e-04f
         };

         return tools::evaluate_polynomial(P2, T(x * x)) * x + 1 / x + log(x) * a;
      }
      else
      {
         // Maximum Deviation Found:                     3.369e-08
         // Expected Error Term : -3.227e-08
         // Maximum Relative Change in Control Points : 9.917e-02
         // Max Error found at float precision = Poly : 6.084411e-08
         static const T Y = 1.450342178f;
         static const T P[] =
         {
            -1.970280088e-01f,
            2.188747807e-02f,
            7.270394756e-01f,
            2.490678196e-01f
         };
         static const T Q[] =
         {
            1.000000000e+00f,
            2.274292882e+00f,
            9.904984851e-01f,
            4.585534549e-02f
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
   T bessel_k1_imp(const T& x, const std::integral_constant<int, 53>&)
   {
      BOOST_MATH_STD_USING
      if(x <= 1)
      {
         // Maximum Deviation Found:                     1.922e-17
         // Expected Error Term : 1.921e-17
         // Maximum Relative Change in Control Points : 5.287e-03
         // Max Error found at double precision = Poly : 2.004747e-17
         static const T Y = 8.69547128677368164e-02f;
         static const T P[] =
         {
            -3.62137953440350228e-03,
            7.11842087490330300e-03,
            1.00302560256614306e-05,
            1.77231085381040811e-06
         };
         static const T Q[] =
         {
            1.00000000000000000e+00,
            -4.80414794429043831e-02,
            9.85972641934416525e-04,
            -8.91196859397070326e-06
         };

         T a = x * x / 4;
         a = ((tools::evaluate_rational(P, Q, a) + Y) * a * a + a / 2 + 1) * x / 2;

         // Maximum Deviation Found:                     4.053e-17
         // Expected Error Term : -4.053e-17
         // Maximum Relative Change in Control Points : 3.103e-04
         // Max Error found at double precision = Poly : 1.246698e-16

         static const T P2[] =
         {
            -3.07965757829206184e-01,
            -7.80929703673074907e-02,
            -2.70619343754051620e-03,
            -2.49549522229072008e-05
         };
         static const T Q2[] = 
         {
            1.00000000000000000e+00,
            -2.36316836412163098e-02,
            2.64524577525962719e-04,
            -1.49749618004162787e-06
         };

         return tools::evaluate_rational(P2, Q2, T(x * x)) * x + 1 / x + log(x) * a;
      }
      else
      {
         // Maximum Deviation Found:                     8.883e-17
         // Expected Error Term : -1.641e-17
         // Maximum Relative Change in Control Points : 2.786e-01
         // Max Error found at double precision = Poly : 1.258798e-16

         static const T Y = 1.45034217834472656f;
         static const T P[] =
         {
            -1.97028041029226295e-01,
            -2.32408961548087617e+00,
            -7.98269784507699938e+00,
            -2.39968410774221632e+00,
            3.28314043780858713e+01,
            5.67713761158496058e+01,
            3.30907788466509823e+01,
            6.62582288933739787e+00,
            3.08851840645286691e-01
         };
         static const T Q[] =
         {
            1.00000000000000000e+00,
            1.41811409298826118e+01,
            7.35979466317556420e+01,
            1.77821793937080859e+02,
            2.11014501598705982e+02,
            1.19425262951064454e+02,
            2.88448064302447607e+01,
            2.27912927104139732e+00,
            2.50358186953478678e-02
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
   T bessel_k1_imp(const T& x, const std::integral_constant<int, 64>&)
   {
      BOOST_MATH_STD_USING
      if(x <= 1)
      {
         // Maximum Deviation Found:                     5.549e-23
         // Expected Error Term : -5.548e-23
         // Maximum Relative Change in Control Points : 2.002e-03
         // Max Error found at float80 precision = Poly : 9.352785e-22
         static const T Y = 8.695471286773681640625e-02f;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, -3.621379534403483072861e-03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 7.102135866103952705932e-03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 4.167545240236717601167e-05),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.537484002571894870830e-06),
            BOOST_MATH_BIG_CONSTANT(T, 64, 6.603228256820000135990e-09)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, -4.354457194045068370363e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 8.709137201220209072820e-04),
            BOOST_MATH_BIG_CONSTANT(T, 64, -9.676151796359590545143e-06),
            BOOST_MATH_BIG_CONSTANT(T, 64, 5.162715192766245311659e-08)
         };

         T a = x * x / 4;
         a = ((tools::evaluate_rational(P, Q, a) + Y) * a * a + a / 2 + 1) * x / 2;

         // Maximum Deviation Found:                     1.995e-23
         // Expected Error Term : 1.995e-23
         // Maximum Relative Change in Control Points : 8.174e-04
         // Max Error found at float80 precision = Poly : 4.137325e-20
         static const T P2[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, -3.079657578292062244054e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, -7.963049154965966503231e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, -3.103277523735639924895e-03),
            BOOST_MATH_BIG_CONSTANT(T, 64, -4.023052834702215699504e-05),
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.719459155018493821839e-07)
         };
         static const T Q2[] = 
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.863917670410152669768e-02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.699367098849735298090e-04),
            BOOST_MATH_BIG_CONSTANT(T, 64, -9.309358790546076298429e-07),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.708893480271612711933e-09)
         };

         return tools::evaluate_rational(P2, Q2, T(x * x)) * x + 1 / x + log(x) * a;
      }
      else
      {
         // Maximum Deviation Found:                     9.785e-20
         // Expected Error Term : -3.302e-21
         // Maximum Relative Change in Control Points : 3.432e-01
         // Max Error found at float80 precision = Poly : 1.083755e-19
         static const T Y = 1.450342178344726562500e+00f;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, -1.970280410292263112917e-01),
            BOOST_MATH_BIG_CONSTANT(T, 64, -4.058564803062959169322e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, -3.036658174194917777473e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, -9.576825392332820142173e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, -6.706969489248020941949e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.264572499406168221382e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 8.584972047303151034100e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 8.422082733280017909550e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.738005441471368178383e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 7.016938390144121276609e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 4.319614662598089438939e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.710715864316521856193e-02)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.298433045824439052398e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.082047745067709230037e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 9.662367854250262046592e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.504148628460454004686e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.712730364911389908905e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.108002081150068641112e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 1.400149940532448553143e+03),
            BOOST_MATH_BIG_CONSTANT(T, 64, 3.083303048095846226299e+02),
            BOOST_MATH_BIG_CONSTANT(T, 64, 2.748706060530351833346e+01),
            BOOST_MATH_BIG_CONSTANT(T, 64, 6.321900849331506946977e-01),
         };
         if(x < tools::log_max_value<T>())
            return ((tools::evaluate_polynomial(P, T(1 / x)) / tools::evaluate_polynomial(Q, T(1 / x)) + Y) * exp(-x) / sqrt(x));
         else
         {
            T ex = exp(-x / 2);
            return ((tools::evaluate_polynomial(P, T(1 / x)) / tools::evaluate_polynomial(Q, T(1 / x)) + Y) * ex / sqrt(x)) * ex;
         }
      }
   }

   template <typename T>
   T bessel_k1_imp(const T& x, const std::integral_constant<int, 113>&)
   {
      BOOST_MATH_STD_USING
      if(x <= 1)
      {
         // Maximum Deviation Found:                     7.120e-35
         // Expected Error Term : -7.119e-35
         // Maximum Relative Change in Control Points : 1.207e-03
         // Max Error found at float128 precision = Poly : 7.143688e-35
         static const T Y = 8.695471286773681640625000000000000000e-02f;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.621379534403483072916666666666595475e-03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.074117676930975433219826471336547627e-03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 9.631337631362776369069668419033041661e-05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.468935967870048731821071646104412775e-06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.956705020559599861444492614737168261e-08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.347140307321161346703214099534250263e-10),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.569608494081482873946791086435679661e-13)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.000000000000000000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.580768910152105375615558920428350204e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 6.197467671701485365363068445534557369e-04),
            BOOST_MATH_BIG_CONSTANT(T, 113, -6.707466533308630411966030561446666237e-06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.846687802282250112624373388491123527e-08),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.248493131151981569517383040323900343e-10),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.319279786372775264555728921709381080e-13)
         };

         T a = x * x / 4;
         a = ((tools::evaluate_rational(P, Q, a) + Y) * a * a + a / 2 + 1) * x / 2;

         // Maximum Deviation Found:                     4.473e-37
         // Expected Error Term : 4.473e-37
         // Maximum Relative Change in Control Points : 8.550e-04
         // Max Error found at float128 precision = Poly : 8.167701e-35
         static const T P2[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.079657578292062244053600156878870690e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, -8.133183745732467770755578848987414875e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.548968792764174773125420229299431951e-03),
            BOOST_MATH_BIG_CONSTANT(T, 113, -5.886125468718182876076972186152445490e-05),
            BOOST_MATH_BIG_CONSTANT(T, 113, -4.506712111733707245745396404449639865e-07),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.632502325880313239698965376754406011e-09),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.311973065898784812266544485665624227e-12)
         };
         static const T Q2[] = 
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.000000000000000000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.311471216733781016657962995723287450e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.571876054797365417068164018709472969e-05),
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.630181215268238731442496851497901293e-07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.070176111227805048604885986867484807e-09),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.129046580769872602793220056461084761e-12),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.294906469421390890762001971790074432e-15)
         };

         return tools::evaluate_rational(P2, Q2, T(x * x)) * x + 1 / x + log(x) * a;
      }
      else if(x < 4)
      {
         // Max error in interpolated form: 5.307e-37
         // Max Error found at float128 precision = Poly: 7.087862e-35
         static const T Y = 1.5023040771484375f;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.489899398329369710528254347931380044e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, -6.819080211203854781858815596508456873e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, -7.599915699069767382647695624952723034e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, -4.450211910821295507926582231071300718e+02),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.451374687870925175794150513723956533e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.405805746895098802803503988539098226e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, -5.638808326778389656403861103277220518e+02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.513958744081268456191778822780865708e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.121301640926540743072258116122834804e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.080094900175649541266613109971296190e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.896531083639613332407534434915552429e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.856602122319645694042555107114028437e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.237121918853145421414003823957537419e+02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.842072954561323076230238664623893504e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.039705646510167437971862966128055524e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.008418100718254816100425022904039530e-02)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.000000000000000000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.927456835239137986889227412815459529e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.598985593265577043711382994516531273e+02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.449897377085510281395819892689690579e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.025555887684561913263090023158085327e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.774140447181062463181892531100679195e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.962055507843204417243602332246120418e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.908269326976180183216954452196772931e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.655160454422016855911700790722577942e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.383586885019548163464418964577684608e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.679920375586960324298491662159976419e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.478586421028842906987799049804565008e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.565384974896746094224942654383537090e+02),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.902617937084010911005732488607114511e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.429293010387921526110949911029094926e-01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.880342607911083143560111853491047663e-04)
         };
         return ((tools::evaluate_polynomial(P, T(1 / x)) / tools::evaluate_polynomial(Q, T(1 / x)) + Y) * exp(-x) / sqrt(x));
      }
      else
      {
         // Maximum Deviation Found:                     4.359e-37
         // Expected Error Term : -6.565e-40
         // Maximum Relative Change in Control Points : 1.880e-01
         // Max Error found at float128 precision = Poly : 2.943572e-35
         static const T Y = 1.308816909790039062500000000000000000f;
         static const T P[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, -5.550277247453881129211735759447737350e-02),
            BOOST_MATH_BIG_CONSTANT(T, 113, -3.485883080219574328217554864956175929e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, -8.903760658131484239300875153154881958e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.144813672213626237418235110712293337e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, -6.498400501156131446691826557494158173e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.573531831870363502604119835922166116e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.417416550054632009958262596048841154e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.271266450613557412825896604269130661e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.898386013314389952534433455681107783e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 5.353798784656436259250791761023512750e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 9.839619195427352438957774052763490067e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.169246368651532232388152442538005637e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.696368884166831199967845883371116431e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.810226630422736458064005843327500169e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.854996610560406127438950635716757614e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.981057433937398731355768088809437625e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.519440069856232098711793483639792952e+04)
         };
         static const T Q[] =
         {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.000000000000000000000000000000000000e+00),
            BOOST_MATH_BIG_CONSTANT(T, 113, 7.127348248283623146544565916604103560e+01),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.205092684176906740104488180754982065e+03),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.911249195069050636298346469740075758e+04),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.426103406579046249654548481377792614e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.365861555422488771286500241966208541e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.765377714160383676864913709252529840e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 6.453822726931857253365138260720815246e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.643207885048369990391975749439783892e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.882540678243694621895816336640877878e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.410120808992380266174106812005338148e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.628138016559335882019310900426773027e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.250794693811010646965360198541047961e+08),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.378723408195485594610593014072950078e+07),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.488253856312453816451380319061865560e+06),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.202167197882689873967723350537104582e+05),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.673233230356966539460728211412989843e+03)
         };
         if(x < tools::log_max_value<T>())
            return ((tools::evaluate_polynomial(P, T(1 / x)) / tools::evaluate_polynomial(Q, T(1 / x)) + Y) * exp(-x) / sqrt(x));
         else
         {
            T ex = exp(-x / 2);
            return ((tools::evaluate_polynomial(P, T(1 / x)) / tools::evaluate_polynomial(Q, T(1 / x)) + Y) * ex / sqrt(x)) * ex;
         }
      }
    }

    template <typename T>
    T bessel_k1_imp(const T& x, const std::integral_constant<int, 0>&)
    {
       if(boost::math::tools::digits<T>() <= 24)
          return bessel_k1_imp(x, std::integral_constant<int, 24>());
       else if(boost::math::tools::digits<T>() <= 53)
          return bessel_k1_imp(x, std::integral_constant<int, 53>());
       else if(boost::math::tools::digits<T>() <= 64)
          return bessel_k1_imp(x, std::integral_constant<int, 64>());
       else if(boost::math::tools::digits<T>() <= 113)
          return bessel_k1_imp(x, std::integral_constant<int, 113>());
       BOOST_MATH_ASSERT(0);
       return 0;
    }

    template <typename T>
   inline T bessel_k1(const T& x)
   {
      typedef std::integral_constant<int,
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

      bessel_k1_initializer<T, tag_type>::force_instantiate();
      return bessel_k1_imp(x, tag_type());
   }

}}} // namespaces

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_BESSEL_K1_HPP


/* bessel_k1.hpp
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
*/