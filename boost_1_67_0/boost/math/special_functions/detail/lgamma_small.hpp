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
T lgamma_small_imp(T z, T zm1, T zm2, const boost::integral_constant<int, 64>&, const Policy& /* l */, const Lanczos&)
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
T lgamma_small_imp(T z, T zm1, T zm2, const boost::integral_constant<int, 113>&, const Policy& /* l */, const Lanczos&)
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
T lgamma_small_imp(T z, T zm1, T zm2, const boost::integral_constant<int, 0>&, const Policy& pol, const Lanczos&)
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
      result = dz * log((z + Lanczos::g() - T(0.5)) / boost::math::constants::e<T>());
      result += boost::math::log1p(dz / (Lanczos::g() + T(1.5)), pol) * T(1.5);
      result += boost::math::log1p(Lanczos::lanczos_sum_near_2(dz), pol);
   }
   else
   {
      // special case near 1:
      T dz = zm1;
      result = dz * log((z + Lanczos::g() - T(0.5)) / boost::math::constants::e<T>());
      result += boost::math::log1p(dz / (Lanczos::g() + T(0.5)), pol) / 2;
      result += boost::math::log1p(Lanczos::lanczos_sum_near_1(dz), pol);
   }
   return result;
}

}}} // namespaces

#endif // BOOST_MATH_SPECIAL_FUNCTIONS_DETAIL_LGAMMA_SMALL


/* lgamma_small.hpp
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
*/