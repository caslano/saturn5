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
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
*/