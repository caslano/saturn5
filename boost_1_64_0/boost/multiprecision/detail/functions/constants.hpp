// Copyright 2011 John Maddock. Distributed under the Boost
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// This file has no include guards or namespaces - it's expanded inline inside default_ops.hpp
//

template <class T>
void calc_log2(T& num, unsigned digits)
{
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename mpl::front<typename T::signed_types>::type                         si_type;

   //
   // String value with 1100 digits:
   //
   static const char* string_val = "0."
                                   "6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875"
                                   "4200148102057068573368552023575813055703267075163507596193072757082837143519030703862389167347112335"
                                   "0115364497955239120475172681574932065155524734139525882950453007095326366642654104239157814952043740"
                                   "4303855008019441706416715186447128399681717845469570262716310645461502572074024816377733896385506952"
                                   "6066834113727387372292895649354702576265209885969320196505855476470330679365443254763274495125040606"
                                   "9438147104689946506220167720424524529612687946546193165174681392672504103802546259656869144192871608"
                                   "2938031727143677826548775664850856740776484514644399404614226031930967354025744460703080960850474866"
                                   "3852313818167675143866747664789088143714198549423151997354880375165861275352916610007105355824987941"
                                   "4729509293113897155998205654392871700072180857610252368892132449713893203784393530887748259701715591"
                                   "0708823683627589842589185353024363421436706118923678919237231467232172053401649256872747782344535347"
                                   "6481149418642386776774406069562657379600867076257199184734022651462837904883062033061144630073719489";
   //
   // Check if we can just construct from string:
   //
   if (digits < 3640) // 3640 binary digits ~ 1100 decimal digits
   {
      num = string_val;
      return;
   }
   //
   // We calculate log2 from using the formula:
   //
   // ln(2) = 3/4 SUM[n>=0] ((-1)^n * N!^2 / (2^n(2n+1)!))
   //
   // Numerator and denominator are calculated separately and then
   // divided at the end, we also precalculate the terms up to n = 5
   // since these fit in a 32-bit integer anyway.
   //
   // See Gourdon, X., and Sebah, P. The logarithmic constant: log 2, Jan. 2004.
   // Also http://www.mpfr.org/algorithms.pdf.
   //
   num = static_cast<ui_type>(1180509120uL);
   T denom, next_term, temp;
   denom        = static_cast<ui_type>(1277337600uL);
   next_term    = static_cast<ui_type>(120uL);
   si_type sign = -1;

   ui_type limit = digits / 3 + 1;

   for (ui_type n = 6; n < limit; ++n)
   {
      temp = static_cast<ui_type>(2);
      eval_multiply(temp, ui_type(2 * n));
      eval_multiply(temp, ui_type(2 * n + 1));
      eval_multiply(num, temp);
      eval_multiply(denom, temp);
      sign = -sign;
      eval_multiply(next_term, n);
      eval_multiply(temp, next_term, next_term);
      if (sign < 0)
         temp.negate();
      eval_add(num, temp);
   }
   eval_multiply(denom, ui_type(4));
   eval_multiply(num, ui_type(3));
   INSTRUMENT_BACKEND(denom);
   INSTRUMENT_BACKEND(num);
   eval_divide(num, denom);
   INSTRUMENT_BACKEND(num);
}

template <class T>
void calc_e(T& result, unsigned digits)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   //
   // 1100 digits in string form:
   //
   const char* string_val = "2."
                            "7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274"
                            "2746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901"
                            "1573834187930702154089149934884167509244761460668082264800168477411853742345442437107539077744992069"
                            "5517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416"
                            "9283681902551510865746377211125238978442505695369677078544996996794686445490598793163688923009879312"
                            "7736178215424999229576351482208269895193668033182528869398496465105820939239829488793320362509443117"
                            "3012381970684161403970198376793206832823764648042953118023287825098194558153017567173613320698112509"
                            "9618188159304169035159888851934580727386673858942287922849989208680582574927961048419844436346324496"
                            "8487560233624827041978623209002160990235304369941849146314093431738143640546253152096183690888707016"
                            "7683964243781405927145635490613031072085103837505101157477041718986106873969655212671546889570350354"
                            "0212340784981933432106817012100562788023519303322474501585390473041995777709350366041699732972508869";
   //
   // Check if we can just construct from string:
   //
   if (digits < 3640) // 3640 binary digits ~ 1100 decimal digits
   {
      result = string_val;
      return;
   }

   T lim;
   lim = ui_type(1);
   eval_ldexp(lim, lim, digits);

   //
   // Standard evaluation from the definition of e: http://functions.wolfram.com/Constants/E/02/
   //
   result = ui_type(2);
   T denom;
   denom     = ui_type(1);
   ui_type i = 2;
   do
   {
      eval_multiply(denom, i);
      eval_multiply(result, i);
      eval_add(result, ui_type(1));
      ++i;
   } while (denom.compare(lim) <= 0);
   eval_divide(result, denom);
}

template <class T>
void calc_pi(T& result, unsigned digits)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type    real_type;
   //
   // 1100 digits in string form:
   //
   const char* string_val = "3."
                            "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
                            "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"
                            "4428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273"
                            "7245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094"
                            "3305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912"
                            "9833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132"
                            "0005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235"
                            "4201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859"
                            "5024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303"
                            "5982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989"
                            "3809525720106548586327886593615338182796823030195203530185296899577362259941389124972177528347913152";
   //
   // Check if we can just construct from string:
   //
   if (digits < 3640) // 3640 binary digits ~ 1100 decimal digits
   {
      result = string_val;
      return;
   }

   T a;
   a = ui_type(1);
   T b;
   T A(a);
   T B;
   B = real_type(0.5f);
   T D;
   D = real_type(0.25f);

   T lim;
   lim = ui_type(1);
   eval_ldexp(lim, lim, -(int)digits);

   //
   // This algorithm is from:
   // Schonhage, A., Grotefeld, A. F. W., and Vetter, E. Fast Algorithms: A Multitape Turing
   // Machine Implementation. BI Wissenschaftverlag, 1994.
   // Also described in MPFR's algorithm guide: http://www.mpfr.org/algorithms.pdf.
   //
   // Let:
   // a[0] = A[0] = 1
   // B[0] = 1/2
   // D[0] = 1/4
   // Then:
   // S[k+1] = (A[k]+B[k]) / 4
   // b[k] = sqrt(B[k])
   // a[k+1] = a[k]^2
   // B[k+1] = 2(A[k+1]-S[k+1])
   // D[k+1] = D[k] - 2^k(A[k+1]-B[k+1])
   // Stop when |A[k]-B[k]| <= 2^(k-p)
   // and PI = B[k]/D[k]

   unsigned k = 1;

   do
   {
      eval_add(result, A, B);
      eval_ldexp(result, result, -2);
      eval_sqrt(b, B);
      eval_add(a, b);
      eval_ldexp(a, a, -1);
      eval_multiply(A, a, a);
      eval_subtract(B, A, result);
      eval_ldexp(B, B, 1);
      eval_subtract(result, A, B);
      bool neg = eval_get_sign(result) < 0;
      if (neg)
         result.negate();
      if (result.compare(lim) <= 0)
         break;
      if (neg)
         result.negate();
      eval_ldexp(result, result, k - 1);
      eval_subtract(D, result);
      ++k;
      eval_ldexp(lim, lim, 1);
   } while (true);

   eval_divide(result, B, D);
}

template <class T, const T& (*F)(void)>
struct constant_initializer
{
   static void do_nothing()
   {
      init.do_nothing();
   }

 private:
   struct initializer
   {
      initializer()
      {
         F();
      }
      void do_nothing() const {}
   };
   static const initializer init;
};

template <class T, const T& (*F)(void)>
typename constant_initializer<T, F>::initializer const constant_initializer<T, F>::init;

template <class T>
const T& get_constant_ln2()
{
   static BOOST_MP_THREAD_LOCAL T    result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
#ifndef BOOST_MP_USING_THREAD_LOCAL
   static BOOST_MP_THREAD_LOCAL bool b = false;
   constant_initializer<T, &get_constant_ln2<T> >::do_nothing();

   if (!b || (digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      b = true;
#else
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
#endif
      calc_log2(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value());
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}

template <class T>
const T& get_constant_e()
{
   static BOOST_MP_THREAD_LOCAL T    result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
#ifndef BOOST_MP_USING_THREAD_LOCAL
   static BOOST_MP_THREAD_LOCAL bool b = false;
   constant_initializer<T, &get_constant_e<T> >::do_nothing();

   if (!b || (digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      b = true;
#else
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
#endif
      calc_e(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value());
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}

template <class T>
const T& get_constant_pi()
{
   static BOOST_MP_THREAD_LOCAL T    result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
#ifndef BOOST_MP_USING_THREAD_LOCAL
   static BOOST_MP_THREAD_LOCAL bool b = false;
   constant_initializer<T, &get_constant_pi<T> >::do_nothing();

   if (!b || (digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      b = true;
#else
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
#endif
      calc_pi(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value());
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}

template <class T>
const T& get_constant_one_over_epsilon()
{
   static BOOST_MP_THREAD_LOCAL T    result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
#ifndef BOOST_MP_USING_THREAD_LOCAL
   static BOOST_MP_THREAD_LOCAL bool b = false;
   constant_initializer<T, &get_constant_one_over_epsilon<T> >::do_nothing();

   if (!b || (digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      b = true;
#else
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
#endif
      typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
      result = static_cast<ui_type>(1u);
      eval_divide(result, std::numeric_limits<number<T> >::epsilon().backend());
   }

   return result;
}

/* constants.hpp
ViZkI9GbnoeNItXBV14fbhp5mFql52dlswjipg8oziU8F2Hucdj1bGMe3SkK1/HE9HSoTttS/8JXZefZ5tufQZwGUSPf63eBzZ1alO702TzdYZEGnh+Verqrwzbc710mVwjH8wort11uv/5rfTgJI6EKAu1/4GkPyiBzoySs0q4ZBuppW337mO1UuGFcRHHumbbpTOnM8ot6xl0EH+N2s7KABIQRJBtW9pfX18z0XmE2MxEkfhY7ZkGru8J91ROOuuZ46Ne6nkzYjhVbTmmLabB7ZIosszWbW0ZeF2nkl16Utdqeg4ONC2unWVOn9cP3PcfoKyWhHduFLRMOtW5jocfST2vRTK6s3i1Iy2KT9OO5sbS+hpziQG+RMV2eiMOi8P2wqJ1Qx4J7w1fnOphsKhI3dq3Adf5LPPAZ5MY+qbfqeg7HVhgmdlBKLxTaGyCH6QwSs5uL2I/8orTDVrvLa/Ny7mDQOxd0ZkPXk4rQ8sLCtqw66Zpp7TzcNV3GsUUQJlEeFG22qaXDc819LPtgm+7VP2bMHfihXRZuqOW9nvilWO330uUcS+RJVDhhGrTa11oaaG1Vdae8FywOrigdx0oD32F5zz2xQGuXTLYUthPGYe63l8HBNfgYDSqDtG/3GMv/MimKuCyr9fkX4U2oUkJ7u5rZTkXkJ0XqRu0+wO3h8mtLdgW9FWbkgVf6mZUEMJkdgVHHuN1haJXe1DlmlIHC8fxyk7SvUtqrWOhrkob/vSxJ4jISZRLl0Qy/3MGcpx56Lq8DYZAWQeFHrXGAuytnVPtb1wE6E67rOWwnTmLnQV67IHEds+7tfy5PuxPndhl7m7oejhNqxX9IPEOVHxZ/X8RRmvhZ6g/m3tD4lBoCNfamrBnxsL0syeOgPQ/wNRG4cJh8oN0Z/faP63fop4Xl2PIVlQlY6j5clzs6r8vinIjQtaMybfqc3t4ftPqn6byurmMyTKzEdpJYHJucPNS4v++y4aPEy6zMTnzTXvfMXB9/V/d5Kls/YLayrEytOItFmLg+2aL3jY20xXlcOI5jm7Prh71pN8QNKINTYqfvVv3fUWjXhjqdhdMr8Fsf1nYW1vBsjcJvcXx2ES7SU/gIVsxt9xsaHuosn3hhZ26xN7u0vtKBIdKQnaux5PP0PC8EVpY4ygtxZBL+n6h+X16BLVT9RdiKemQSfu0/eWRirjqRPAGKe0K/f+95zD+u54dxmKG2fY6/uE77cx84tOO+z3octFN78E3X/hLGsA+ACr/xRAxfZOHPhvDjT8dwTA4CVTg65MbBoaHRIXgor7O00IV/3w/CjwG/+1IMn+3C4RkZ9lwIK1Npc3mo1vs8CLt0EsNAVupF+fH7Ph/CLdf13E5hx0NV2CyEFXbcya3MQ/m7IewkhPVfJIM6/rNyZ7oDr5v2Tq4vzVX4YgPHK6QG+FoLvvJShT+qqtvD0EeTliEtEEdcKMDw3TW+f0ThJ6onOTsD2R80sN5GR8b9MdV+0DETX1wa0vBPmDja1/B0i4n3l/S4XSMcDuHAdxPDHlFj57ZyrE5aX5e/vE1xTvXW9ne6MHUzSPe4wmAsdmptXpc7N8CWJiBrdazcrjAqM4RdIQzCJxZZWo7fQ8cgshr2V4ZxH5y9p8JAZoLbe+wOHVvbWNOwu+6tsH4jDV8iDGQMncfuo2EUzyq/3J2AVXWiahhOr1Behvfl2Pxsf14vC+H9EK+bkgOd7vLs4qKOX9TxiSa+9/4afpBwitsbJY4dlI6MhCwrNXZdYovzHaqUTf3zuxocrIyk45tNfAG+hatrmo5jDzA5WEgG8bjaxOFwGRzAOtMberzS8cAGB9Z0Ib4vWeosLs/KdD2w5v4=
*/