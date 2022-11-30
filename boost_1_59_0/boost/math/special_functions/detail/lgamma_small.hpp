//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_FUNCTIONS_DETAIL_LGAMMA_SMALL
#define BOOST_MATH_SPECIAL_FUNCTIONS_DETAIL_LGAMMA_SMALL

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/big_constant.hpp>

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

//
// These need forward declaring to keep GCC happy:
//
template <class T, class Policy, class Lanczos>
T gamma_imp(T z, const Policy& pol, const Lanczos& l);
template <class T, class Policy>
T gamma_imp(T z, const Policy& pol, const lanczos::undefined_lanczos& l);

//
// lgamma for small arguments:
//
template <class T, class Policy, class Lanczos>
T lgamma_small_imp(T z, T zm1, T zm2, const std::integral_constant<int, 64>&, const Policy& /* l */, const Lanczos&)
{
   // This version uses rational approximations for small
   // values of z accurate enough for 64-bit mantissas
   // (80-bit long doubles), works well for 53-bit doubles as well.
   // Lanczos is only used to select the Lanczos function.

   BOOST_MATH_STD_USING  // for ADL of std names
   T result = 0;
   if(z < tools::epsilon<T>())
   {
      result = -log(z);
   }
   else if((zm1 == 0) || (zm2 == 0))
   {
      // nothing to do, result is zero....
   }
   else if(z > 2)
   {
      //
      // Begin by performing argument reduction until
      // z is in [2,3):
      //
      if(z >= 3)
      {
         do
         {
            z -= 1;
            zm2 -= 1;
            result += log(z);
         }while(z >= 3);
         // Update zm2, we need it below:
         zm2 = z - 2;
      }

      //
      // Use the following form:
      //
      // lgamma(z) = (z-2)(z+1)(Y + R(z-2))
      //
      // where R(z-2) is a rational approximation optimised for
      // low absolute error - as long as it's absolute error
      // is small compared to the constant Y - then any rounding
      // error in it's computation will get wiped out.
      //
      // R(z-2) has the following properties:
      //
      // At double: Max error found:                    4.231e-18
      // At long double: Max error found:               1.987e-21
      // Maximum Deviation Found (approximation error): 5.900e-24
      //
      static const T P[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.180355685678449379109e-1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.25126649619989678683e-1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.494103151567532234274e-1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.172491608709613993966e-1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.259453563205438108893e-3)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.541009869215204396339e-3)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.324588649825948492091e-4))
      };
      static const T Q[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.1e1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.196202987197795200688e1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.148019669424231326694e1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.541391432071720958364e0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.988504251128010129477e-1)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.82130967464889339326e-2)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.224936291922115757597e-3)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.223352763208617092964e-6))
      };

      static const float Y = 0.158963680267333984375e0f;

      T r = zm2 * (z + 1);
      T R = tools::evaluate_polynomial(P, zm2);
      R /= tools::evaluate_polynomial(Q, zm2);

      result +=  r * Y + r * R;
   }
   else
   {
      //
      // If z is less than 1 use recurrence to shift to
      // z in the interval [1,2]:
      //
      if(z < 1)
      {
         result += -log(z);
         zm2 = zm1;
         zm1 = z;
         z += 1;
      }
      //
      // Two approximations, on for z in [1,1.5] and
      // one for z in [1.5,2]:
      //
      if(z <= 1.5)
      {
         //
         // Use the following form:
         //
         // lgamma(z) = (z-1)(z-2)(Y + R(z-1))
         //
         // where R(z-1) is a rational approximation optimised for
         // low absolute error - as long as it's absolute error
         // is small compared to the constant Y - then any rounding
         // error in it's computation will get wiped out.
         //
         // R(z-1) has the following properties:
         //
         // At double precision: Max error found:                1.230011e-17
         // At 80-bit long double precision:   Max error found:  5.631355e-21
         // Maximum Deviation Found:                             3.139e-021
         // Expected Error Term:                                 3.139e-021

         //
         static const float Y = 0.52815341949462890625f;

         static const T P[] = {
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.490622454069039543534e-1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.969117530159521214579e-1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.414983358359495381969e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.406567124211938417342e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.158413586390692192217e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.240149820648571559892e-1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.100346687696279557415e-2))
         };
         static const T Q[] = {
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.1e1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.302349829846463038743e1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.348739585360723852576e1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.191415588274426679201e1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.507137738614363510846e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.577039722690451849648e-1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.195768102601107189171e-2))
         };

         T r = tools::evaluate_polynomial(P, zm1) / tools::evaluate_polynomial(Q, zm1);
         T prefix = zm1 * zm2;

         result += prefix * Y + prefix * r;
      }
      else
      {
         //
         // Use the following form:
         //
         // lgamma(z) = (2-z)(1-z)(Y + R(2-z))
         //
         // where R(2-z) is a rational approximation optimised for
         // low absolute error - as long as it's absolute error
         // is small compared to the constant Y - then any rounding
         // error in it's computation will get wiped out.
         //
         // R(2-z) has the following properties:
         //
         // At double precision, max error found:              1.797565e-17
         // At 80-bit long double precision, max error found:  9.306419e-21
         // Maximum Deviation Found:                           2.151e-021
         // Expected Error Term:                               2.150e-021
         //
         static const float Y = 0.452017307281494140625f;

         static const T P[] = {
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.292329721830270012337e-1)), 
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.144216267757192309184e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.142440390738631274135e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.542809694055053558157e-1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.850535976868336437746e-2)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.431171342679297331241e-3))
         };
         static const T Q[] = {
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.1e1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.150169356054485044494e1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.846973248876495016101e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.220095151814995745555e0)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.25582797155975869989e-1)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.100666795539143372762e-2)),
            static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.827193521891290553639e-6))
         };
         T r = zm2 * zm1;
         T R = tools::evaluate_polynomial(P, T(-zm2)) / tools::evaluate_polynomial(Q, T(-zm2));

         result += r * Y + r * R;
      }
   }
   return result;
}
template <class T, class Policy, class Lanczos>
T lgamma_small_imp(T z, T zm1, T zm2, const std::integral_constant<int, 113>&, const Policy& /* l */, const Lanczos&)
{
   //
   // This version uses rational approximations for small
   // values of z accurate enough for 113-bit mantissas
   // (128-bit long doubles).
   //
   BOOST_MATH_STD_USING  // for ADL of std names
   T result = 0;
   if(z < tools::epsilon<T>())
   {
      result = -log(z);
      BOOST_MATH_INSTRUMENT_CODE(result);
   }
   else if((zm1 == 0) || (zm2 == 0))
   {
      // nothing to do, result is zero....
   }
   else if(z > 2)
   {
      //
      // Begin by performing argument reduction until
      // z is in [2,3):
      //
      if(z >= 3)
      {
         do
         {
            z -= 1;
            result += log(z);
         }while(z >= 3);
         zm2 = z - 2;
      }
      BOOST_MATH_INSTRUMENT_CODE(zm2);
      BOOST_MATH_INSTRUMENT_CODE(z);
      BOOST_MATH_INSTRUMENT_CODE(result);

      //
      // Use the following form:
      //
      // lgamma(z) = (z-2)(z+1)(Y + R(z-2))
      //
      // where R(z-2) is a rational approximation optimised for
      // low absolute error - as long as it's absolute error
      // is small compared to the constant Y - then any rounding
      // error in it's computation will get wiped out.
      //
      // Maximum Deviation Found (approximation error)      3.73e-37

      static const T P[] = {
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.018035568567844937910504030027467476655),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.013841458273109517271750705401202404195),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.062031842739486600078866923383017722399),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.052518418329052161202007865149435256093),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.01881718142472784129191838493267755758),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0025104830367021839316463675028524702846),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.00021043176101831873281848891452678568311),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.00010249622350908722793327719494037981166),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.11381479670982006841716879074288176994e-4),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.49999811718089980992888533630523892389e-6),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.70529798686542184668416911331718963364e-8)
      };
      static const T Q[] = {
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
         BOOST_MATH_BIG_CONSTANT(T, 113, 2.5877485070422317542808137697939233685),
         BOOST_MATH_BIG_CONSTANT(T, 113, 2.8797959228352591788629602533153837126),
         BOOST_MATH_BIG_CONSTANT(T, 113, 1.8030885955284082026405495275461180977),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.69774331297747390169238306148355428436),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.17261566063277623942044077039756583802),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.02729301254544230229429621192443000121),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.0026776425891195270663133581960016620433),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.00015244249160486584591370355730402168106),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.43997034032479866020546814475414346627e-5),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.46295080708455613044541885534408170934e-7),
         BOOST_MATH_BIG_CONSTANT(T, 113, -0.93326638207459533682980757982834180952e-11),
         BOOST_MATH_BIG_CONSTANT(T, 113, 0.42316456553164995177177407325292867513e-13)
      };

      T R = tools::evaluate_polynomial(P, zm2);
      R /= tools::evaluate_polynomial(Q, zm2);

      static const float Y = 0.158963680267333984375F;

      T r = zm2 * (z + 1);

      result +=  r * Y + r * R;
      BOOST_MATH_INSTRUMENT_CODE(result);
   }
   else
   {
      //
      // If z is less than 1 use recurrence to shift to
      // z in the interval [1,2]:
      //
      if(z < 1)
      {
         result += -log(z);
         zm2 = zm1;
         zm1 = z;
         z += 1;
      }
      BOOST_MATH_INSTRUMENT_CODE(result);
      BOOST_MATH_INSTRUMENT_CODE(z);
      BOOST_MATH_INSTRUMENT_CODE(zm2);
      //
      // Three approximations, on for z in [1,1.35], [1.35,1.625] and [1.625,1]
      //
      if(z <= 1.35)
      {
         //
         // Use the following form:
         //
         // lgamma(z) = (z-1)(z-2)(Y + R(z-1))
         //
         // where R(z-1) is a rational approximation optimised for
         // low absolute error - as long as it's absolute error
         // is small compared to the constant Y - then any rounding
         // error in it's computation will get wiped out.
         //
         // R(z-1) has the following properties:
         //
         // Maximum Deviation Found (approximation error)            1.659e-36
         // Expected Error Term (theoretical error)                  1.343e-36
         // Max error found at 128-bit long double precision         1.007e-35
         //
         static const float Y = 0.54076099395751953125f;

         static const T P[] = {
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.036454670944013329356512090082402429697),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.066235835556476033710068679907798799959),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.67492399795577182387312206593595565371),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.4345555263962411429855341651960000166),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.4894319559821365820516771951249649563),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.87210277668067964629483299712322411566),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.29602090537771744401524080430529369136),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.0561832587517836908929331992218879676),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.0053236785487328044334381502530383140443),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.00018629360291358130461736386077971890789),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.10164985672213178500790406939467614498e-6),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.13680157145361387405588201461036338274e-8)
         };
         static const T Q[] = {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 113, 4.9106336261005990534095838574132225599),
            BOOST_MATH_BIG_CONSTANT(T, 113, 10.258804800866438510889341082793078432),
            BOOST_MATH_BIG_CONSTANT(T, 113, 11.88588976846826108836629960537466889),
            BOOST_MATH_BIG_CONSTANT(T, 113, 8.3455000546999704314454891036700998428),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.6428823682421746343233362007194282703),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.97465989807254572142266753052776132252),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.15121052897097822172763084966793352524),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.012017363555383555123769849654484594893),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.0003583032812720649835431669893011257277)
         };

         T r = tools::evaluate_polynomial(P, zm1) / tools::evaluate_polynomial(Q, zm1);
         T prefix = zm1 * zm2;

         result += prefix * Y + prefix * r;
         BOOST_MATH_INSTRUMENT_CODE(result);
      }
      else if(z <= 1.625)
      {
         //
         // Use the following form:
         //
         // lgamma(z) = (2-z)(1-z)(Y + R(2-z))
         //
         // where R(2-z) is a rational approximation optimised for
         // low absolute error - as long as it's absolute error
         // is small compared to the constant Y - then any rounding
         // error in it's computation will get wiped out.
         //
         // R(2-z) has the following properties:
         //
         // Max error found at 128-bit long double precision  9.634e-36
         // Maximum Deviation Found (approximation error)     1.538e-37
         // Expected Error Term (theoretical error)           2.350e-38
         //
         static const float Y = 0.483787059783935546875f;

         static const T P[] = {
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.017977422421608624353488126610933005432),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.18484528905298309555089509029244135703),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.40401251514859546989565001431430884082),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.40277179799147356461954182877921388182),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.21993421441282936476709677700477598816),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.069595742223850248095697771331107571011),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.012681481427699686635516772923547347328),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.0012489322866834830413292771335113136034),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.57058739515423112045108068834668269608e-4),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.8207548771933585614380644961342925976e-6)
         };
         static const T Q[] = {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.9629552288944259229543137757200262073),
            BOOST_MATH_BIG_CONSTANT(T, 113, 3.7118380799042118987185957298964772755),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.5569815272165399297600586376727357187),
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.0546764918220835097855665680632153367),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.26574021300894401276478730940980810831),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.03996289731752081380552901986471233462),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.0033398680924544836817826046380586480873),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.00013288854760548251757651556792598235735),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.17194794958274081373243161848194745111e-5)
         };
         T r = zm2 * zm1;
         T R = tools::evaluate_polynomial(P, T(0.625 - zm1)) / tools::evaluate_polynomial(Q, T(0.625 - zm1));

         result += r * Y + r * R;
         BOOST_MATH_INSTRUMENT_CODE(result);
      }
      else
      {
         //
         // Same form as above.
         //
         // Max error found (at 128-bit long double precision) 1.831e-35
         // Maximum Deviation Found (approximation error)      8.588e-36
         // Expected Error Term (theoretical error)            1.458e-36
         //
         static const float Y = 0.443811893463134765625f;

         static const T P[] = {
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.021027558364667626231512090082402429494),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.15128811104498736604523586803722368377),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.26249631480066246699388544451126410278),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.21148748610533489823742352180628489742),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.093964130697489071999873506148104370633),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.024292059227009051652542804957550866827),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.0036284453226534839926304745756906117066),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.0002939230129315195346843036254392485984),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.11088589183158123733132268042570710338e-4),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.13240510580220763969511741896361984162e-6)
         };
         static const T Q[] = {
            BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
            BOOST_MATH_BIG_CONSTANT(T, 113, -2.4240003754444040525462170802796471996),
            BOOST_MATH_BIG_CONSTANT(T, 113, 2.4868383476933178722203278602342786002),
            BOOST_MATH_BIG_CONSTANT(T, 113, -1.4047068395206343375520721509193698547),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.47583809087867443858344765659065773369),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.09865724264554556400463655444270700132),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.012238223514176587501074150988445109735),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.00084625068418239194670614419707491797097),
            BOOST_MATH_BIG_CONSTANT(T, 113, 0.2796574430456237061420839429225710602e-4),
            BOOST_MATH_BIG_CONSTANT(T, 113, -0.30202973883316730694433702165188835331e-6)
         };
         // (2 - x) * (1 - x) * (c + R(2 - x))
         T r = zm2 * zm1;
         T R = tools::evaluate_polynomial(P, T(-zm2)) / tools::evaluate_polynomial(Q, T(-zm2));

         result += r * Y + r * R;
         BOOST_MATH_INSTRUMENT_CODE(result);
      }
   }
   BOOST_MATH_INSTRUMENT_CODE(result);
   return result;
}
template <class T, class Policy, class Lanczos>
T lgamma_small_imp(T z, T zm1, T zm2, const std::integral_constant<int, 0>&, const Policy& pol, const Lanczos& l)
{
   //
   // No rational approximations are available because either
   // T has no numeric_limits support (so we can't tell how
   // many digits it has), or T has more digits than we know
   // what to do with.... we do have a Lanczos approximation
   // though, and that can be used to keep errors under control.
   //
   BOOST_MATH_STD_USING  // for ADL of std names
   T result = 0;
   if(z < tools::epsilon<T>())
   {
      result = -log(z);
   }
   else if(z < 0.5)
   {
      // taking the log of tgamma reduces the error, no danger of overflow here:
      result = log(gamma_imp(z, pol, Lanczos()));
   }
   else if(z >= 3)
   {
      // taking the log of tgamma reduces the error, no danger of overflow here:
      result = log(gamma_imp(z, pol, Lanczos()));
   }
   else if(z >= 1.5)
   {
      // special case near 2:
      T dz = zm2;
      result = dz * log((z + lanczos_g_near_1_and_2(l) - T(0.5)) / boost::math::constants::e<T>());
      result += boost::math::log1p(dz / (lanczos_g_near_1_and_2(l) + T(1.5)), pol) * T(1.5);
      result += boost::math::log1p(Lanczos::lanczos_sum_near_2(dz), pol);
   }
   else
   {
      // special case near 1:
      T dz = zm1;
      result = dz * log((z + lanczos_g_near_1_and_2(l) - T(0.5)) / boost::math::constants::e<T>());
      result += boost::math::log1p(dz / (lanczos_g_near_1_and_2(l) + T(0.5)), pol) / 2;
      result += boost::math::log1p(Lanczos::lanczos_sum_near_1(dz), pol);
   }
   return result;
}

}}} // namespaces

#endif // BOOST_MATH_SPECIAL_FUNCTIONS_DETAIL_LGAMMA_SMALL


/* lgamma_small.hpp
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
*/