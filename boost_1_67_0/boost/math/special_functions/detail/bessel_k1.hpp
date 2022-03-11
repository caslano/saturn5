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
// http://www.advanpix.com/2016/01/05/rational-approximations-for-the-modified-bessel-function-of-the-second-kind-k1-for-computations-with-double-precision/
//
// The actual coefficients used are our own derivation (by JM)
// since we extend to both greater and lesser precision than the
// references above.  We can also improve performance WRT to
// Holoborodko without loss of precision.

namespace boost { namespace math { namespace detail{

   template <typename T>
   T bessel_k1(const T& x);

   template <class T, class tag>
   struct bessel_k1_initializer
   {
      struct init
      {
         init()
         {
            do_init(tag());
         }
         static void do_init(const boost::integral_constant<int, 113>&)
         {
            bessel_k1(T(0.5));
            bessel_k1(T(2));
            bessel_k1(T(6));
         }
         static void do_init(const boost::integral_constant<int, 64>&)
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
   inline T bessel_k1_imp(const T& x, const boost::integral_constant<int, N>&)
   {
      BOOST_ASSERT(0);
      return 0;
   }

   template <typename T>
   T bessel_k1_imp(const T& x, const boost::integral_constant<int, 24>&)
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
   T bessel_k1_imp(const T& x, const boost::integral_constant<int, 53>&)
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
   T bessel_k1_imp(const T& x, const boost::integral_constant<int, 64>&)
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
   T bessel_k1_imp(const T& x, const boost::integral_constant<int, 113>&)
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
    T bessel_k1_imp(const T& x, const boost::integral_constant<int, 0>&)
    {
       if(boost::math::tools::digits<T>() <= 24)
          return bessel_k1_imp(x, boost::integral_constant<int, 24>());
       else if(boost::math::tools::digits<T>() <= 53)
          return bessel_k1_imp(x, boost::integral_constant<int, 53>());
       else if(boost::math::tools::digits<T>() <= 64)
          return bessel_k1_imp(x, boost::integral_constant<int, 64>());
       else if(boost::math::tools::digits<T>() <= 113)
          return bessel_k1_imp(x, boost::integral_constant<int, 113>());
       BOOST_ASSERT(0);
       return 0;
    }

    template <typename T>
   inline T bessel_k1(const T& x)
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