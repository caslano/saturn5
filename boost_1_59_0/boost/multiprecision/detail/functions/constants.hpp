// Copyright 2011 John Maddock.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// This file has no include guards or namespaces - it's expanded inline inside default_ops.hpp
//

template <class T>
void calc_log2(T& num, unsigned digits)
{
   using ui_type = typename boost::multiprecision::detail::canonical<std::uint32_t, T>::type;
   using si_type = typename std::tuple_element<0, typename T::signed_types>::type                        ;

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
   using ui_type = typename std::tuple_element<0, typename T::unsigned_types>::type;
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
   using ui_type = typename std::tuple_element<0, typename T::unsigned_types>::type;
   using real_type = typename std::tuple_element<0, typename T::float_types>::type   ;
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
   eval_ldexp(lim, lim, -static_cast<int>(digits));

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

template <class T>
const T& get_constant_ln2()
{
   static BOOST_MP_THREAD_LOCAL T    result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      boost::multiprecision::detail::maybe_promote_precision(&result);
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
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      boost::multiprecision::detail::maybe_promote_precision(&result);
      calc_e(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value());
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}

template <class T>
const T& get_constant_pi()
{
   static BOOST_MP_THREAD_LOCAL T             result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      boost::multiprecision::detail::maybe_promote_precision(&result);
      calc_pi(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value());
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif
template <class T>
const T& get_constant_one_over_epsilon()
{
   static BOOST_MP_THREAD_LOCAL T             result;
   static BOOST_MP_THREAD_LOCAL long digits = 0;
   if ((digits != boost::multiprecision::detail::digits2<number<T> >::value()))
   {
      using ui_type = typename std::tuple_element<0, typename T::unsigned_types>::type;
      boost::multiprecision::detail::maybe_promote_precision(&result);
      result = static_cast<ui_type>(1u);
      BOOST_IF_CONSTEXPR(std::numeric_limits<number<T> >::is_specialized)
         eval_divide(result, std::numeric_limits<number<T> >::epsilon().backend());
      else
         eval_ldexp(result, result, boost::multiprecision::detail::digits2<number<T> >::value() - 1);
      digits = boost::multiprecision::detail::digits2<number<T> >::value();
   }

   return result;
}
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

/* constants.hpp
vPmmTLIABjQdbm8IG6TplNfDjnI+M1ME8ReD2ueX80V+E5bXQkknl1vz2UH+VpqWmcDhhSnG+d2ZSCBCIAWeIiAkxwz1EwcLBrZQMng+p4W6IdEIU7TXUgZUfkcn+AXZT0cjbWiv6FkxHRHmW9efV1mJnpnKypkrS6TXEHkpWihJJk4Y68zAMVWy/e+oN08Ca8BRMgER9Ie3l6G8+X1Lw0ToI9PKEFm8/Is+NaoFAhtIjuV8GsgX7QI5kDpKSwDu8zqhIzE2yCNs0N77o47Uo32oNDhZjQnzkZld4AeIVIQ2s1O0bTmrlMspyGqodZOBW4z2i5Ua4IHLSdsLLU+DUwKV0BAZ85/oG/iVqI/RdaRP+d/TQw85/M1YsZB/sAoIaEV3B9ixIjuLgJnQjQh/QXKJqAMcd6tTK/J2xOxXfXNZrLOfIGhDQUn2aCeo0cTAHKsjUNoZE6J8V2A60eASKOVifNFiq++iIuMha3B7wh+latkkjJhNopTTIy21kh5zSRgxl0RpZ/g+wtTStH4jaeQdMwKtvVoP8j5cFqjsRpDrzgiKdhoWxBfMz0RLCDON+bjz04NjKe6cKAvYxQcRVOx0/AC0f2dRZriS/EglvgzKBvUARcFDjpUGAD4YIz1mfxvId8/msP87BDI6KoUeWgUM0Yr+YHr3BzslpaFaaVjiabkaf5aolu7H90gB9yynZ9asV6U6ncvzWSH4JXPuVC0vN2DMtH50cI5NHEZUipUGm9JQqDQsUBocSkOF0rAoFGU6POwObopPyE5Uq7sLC04VH/VluAva6S2zxCqzQOkNoOFm+GNS3A7FXQE6tgptd7lL7VDshiK3zWvDE8+Ws9MwlmWGj1gvxqRLe5XK/uKD3rHMkYNhDWiqagznVprYnFlMLg9U9pa7HOx2hM2xG2oV9wLFvUhxVyvuJW6NgGPHBGE40n3szRe84dZQGpM/KWqwecdQYazMBHMWYn+RkGOtO7S/ANqja/Pw8xFaHOgWMUKJoJFtktcIJVOuOChddoR34WLLSdBy8eHRREm5mE7d1g7ERtZDUKe7/vErNbT+geHCrqbINc4Uu3yRawxzdf0sdF3FelYfRsQib34VWOLf/cM8KTAnxxFYmMPPrIfhfo5Dmetgd1coCytY1SLFtYjNqVbmVrsPxqwXgJWoYjOwbV2s3sBscl6fK++wo7xKxNRr3eGVhrZHDg+O74M8J0fmS4nVGya/f22gDWuWrEhQPZi+4cjO8ALMflwudgXT+6EGbt48XiD3tzpwzv6zL20UKGd2ExhSpRmBIhQyt8pLJfCCUutNrN+DVwAEvR+/+eLI7Y90hBeHiIqtX1BaOLhEUvkuoHFQHrbklCBuvnldkvHyQanehizve/J3oDOGv44Xxo+QZy6E158xMLx9uwAqENiKzeX0TAc9AAFJkzA5lQfKXlmnc8ANPdwIbN1E71wf9c4Y7Z2y8Dtb6J3G++gdGW75b5WMjVg9e44SAq8lHyunHOYL91JiIUzrhRDnbH4OW1tCcPF1Upky26taDJjpAGWbGxnLPKddkriZHxnEYPRmK3PqZtahpbNsQsvVGx4HZDEO+NVRvlyUlWFSgjg+Hnhfi9EohWhIaIfbemL7l7Ze9tkNUN4tVug6nhmiH/2J2XJYNsLga/LxPIyZe9QTnhtCL5TkRD8qU09o7dry/HgY4IQYgs04ZGRQmuV9wjNVNiKNQjJVHv99IfVQLTm4OrHRocmvzYRfHfFIRijcIXakejqrw693hNyf6BkBW00CWI21q1Nt0walI495XtA+xPqmCSY8BhgqLkCnqKKVPwNNgb1jaqlGN/Z5NjenKN17BYzvd0JbwU+5FiYS+KSgfXWDjFmQa40bxJ1I+TC+uAAHLPjTAvuxdhdf8uxdwnfw/oi1onDYKKE3zREB1brj4kc4G1vdoJcoI/gF31Qut96FxE3yN8gTfWP4ycBdZFH1UphavYRgIZb2GTu0JxF52LD+LDDQyjjmkJUyPXMYlDKZ2UzK7YaDzDIJnAFl3PYc/Od2PbNY8UeZvD2XbhgS7C8fcT0YUfyHXA/OG2E9uPDDBOND76PD57sEr+u/12WHuh87HkyvhmL4+hVwr1mfIjzXYLNB+wWzTKUZT4OwTGK/lXarW0gGG810n8TQmkX3SRQb8RCDAtPc4S2yoLdw76aR7SeSGFok8L2TnZztT1oeJ1i8PFYuzwarYQLvSLl7mYsdV0g2Qi4U3j+9ORsPavBmEBw4acyepWyswP7UjOnRg83oeUSPKXEUmhPvJ0CvqwXrUlrxb3EUSNmIf7MWme7j37hoxT6EqjfiW6TcRXfketOV5mW6sJ6f8e/HjRSS7wH/fmpa70+r+L+maHl4j7u7ruvIlvz7qa29JYwqdPGz+dCj6Te/cA387CVI/uN8wSvZEia8Ra7b386W+P13XlDFi0rJjFos7+TH2ZFuKtazQzVn81nRr8PMDpgtRzZebsiW3In3V4j4Q/2b0SHiyHprYexSiSN8dmXpQqBUV3DKCfZYnoyWk9/2+dUwMceYH8K5I8R6m06ctMGMDU2U4XKtXuS2LORnLqoY2Dd7qmjdFTNiWrWwJCLLLwo0d+OEHfN3VOHM9VwRPDC24mEtqGLdKESM98KdwCVJErlTDLucHikTRpCZjW2Ss4xvry3F47mHzMUXvR5RM9gfcNmvAvvDSmSlwpoL5gdtzwJrPlzNAIZnfn2t6IaiA26nnrcAXsykflcBL94JLy6wzgzA5+VaPk5Hn4qLne2+0jlE1Lp7VOJuEeklEBfiFGrPiES0aMXVEbviWghz9CurxRx95BJY8Ot9Uauy2J57sIuovtH+PdhLVO84fuUAbaCS2ZGarpsfzUaDo+kCvM97L9FTM4w+ZdCKv3BlC11H/S5ojzUoor+fuBQ130jgH4EHvor2XGK5S5ltiYOyMdEK+4r+sHtC6a/WZ0T5JugiIxn0OgaYWQ85cCGHpOmcLzXQoIvLhRkc6tig6B9VmPKGQqlaZ/WOQ+2s0BIAUMcAKwQ1O3B1+vwT4c4i5o/Uxbbhhy4QKzn2knci7WdW7L1ohaG0s6jYtLytfoJJxKGg6XuypSp+REi/LlT3ff9X2/eAR3FcefZoRmIMwjNgyZZjYbT2QMgJx8SSfZIlFmFrYCAS9MxIGhnEn7uQzazCZdnNjE0SgSSPJOgtZlA4kHGMgXVwDi5OjiQ+W2x8skAsgxwWyzIx+GAvts+3aRbdt/bZBzLG39z7veqeP5L447s9fV+rp6urq1699+pVvVevXiGmcZlfhjQW56JdW9lT6k2SZ4aXayLfg/VzHB5gblVrVgLG2vlnL2IUQVaLEcS2jCNycXn5VfThyhQKxNGSwbjCXcxj0zxOzZOreewDafMDHGD/iFhkb04QCDpPCxbZRYNNLLfxUSaDIVvncHiS5LFu8ZD2jchRW+SYzRP+hISQWLi+ZLDc86lj11FxdCB1vr09coQPow/Pgj5dhCkWdrjbfImhSJkSzolstCmh26Sdgfic+kFyfwyE8yJbPAdAw5k0xeu34LGD7wO8yNKZMN2XiLKd/Rut2iJnZyJ8H5WNowwzrMol/Wu0RbnaIrvkhGU2f+dg+FGxyKltsleMtlo1N05Ut563nvcn8t+jz/yYVy6y6daVteD2yHHnSm2zHYXIElbnVnzeOpcQWTHqiHGozrPFQ9Zh67AvamvHIvIbKzgwIX8lPyHo+sMu+uTZyAeTrMeOjlojo7ZNk6QHd+58HIW8ObsXN+tAxeimbILpUjbBJ+IVA5uMlvJBRRJCsYyJeI6gsw5aB73Wfh+98+s/f2o0AQK/WXyS06N5EdIA9EcJHsKMgRXqCJHjLm21TVuWBiLb8ywgi1hiI76we2XuJ8bNj37/l2n+irn+honPztNWjZSvsbUWso0NWgbLh1XX4m4IfuUiXPWC+q+OKKSf1NwtKX4ykd971wuKlCcFD7xgnNK+6hoXEqz7+0PytDgnzcSD+sPG0zzKGHXrQPz5Nx6nguzyQHW8KzQPvNMNr52Mr6gXBD996BBO59V9euziAuPsXuvEH/P+2tPSBEfNk7LLFFInxlrUkv6MO79Ix9eECudi4trWKX9jW/Rbpeqn+K8ttokcbOEMf42q9+pPp06oV6PL7dJFKSko9YvHbgWbhm54c2TW6+Ca2OAEyJRLwBNiM+oeaVB1e02V8ZVxsqHxIZ9QaEIuSxnJOB1+orOP12QueUt8TvswzXll7UQz3shmmxF3OOrereovfjbJnJ16IyfssKR+1JC0pFokHXfrsbvscuVhCWtqifyXvk86pUbC0RU+oqQEU2SBEpqdBHq3PvvzSeNtqpIB0nIplGucZ854+Ubte/+/p7WvaSJ+ibTaEqEnCNJ6bt/fjSbb1+CNxGUDA+Mb+It8ezpE37s6Hu41hryemAS9G/9+An1pc7o8sPuva1NrzBpnU5OLEPGcmtOHlNSsIRrj0Krmc1Y0dlA6Myfy7ZJ5rMI9Ele2LXiRDfDRGDxo0t9ni9qRuCXvoRfl0Zex3TAY9WlL+WhMNsvl0fRZ6zrAW0fApFoPwNO6ulkBCfLvJv6/Nsv0b6aP7bLztNyX1nmYs2Ny5RDMTYqMajaBn2sLRX2RxuYMrQcTDT6g02T3G5i6C8f7q/5f+Jd/suEW7MegAEHCxxNJdLV2LpXnkzJ2qYsXplMjkV9UmEktYzlEMVGR3rbrGOQIPr+YAaOYMaxHu1C2GlxBk68ATECo2htcIx/bTwCwhuBq+chLUhlN7q06PQF/Nm+7mT+uNFlJpwAYZuTu5ZbEEGwHpA+CcZH0dIhNRazPBTAfO4dG3YUjITbIox+H+DSMCnr/r4NwNodjtvR4CM0O1vUc4lmckZBf/qOQo3M/fdg+II3DYLj2PjAiTeOVsFfEkBL5wcassDt5cKpp9ruafnaqaRodw4rjRKtc/pvvLH4B+m/irGDjtBp8wir7Jox2NHBQOri1nDvIphzZUUQMvNts8aomC5QS5Ryv9iCr49Wu/ZynEohgU9/RD5xThnzU8b8tDXqih0vpwrqoj/TKbGkCNAvDorusQnCJXp/BiE9uX0pfHeChj1NSthX9n/56qYKzMxP5ZTBidgF3879JyAsVzI/hNm1+JW6T49yzWdrFUFQFd8fQpPm330uYnkQz778wrQDjXZoncBdiLmvAQZ9YVEWTggq3Rx72eafWtR5cw+vmWMV8L2Wf8DeIDc4Af/qZ2J781Cs/tX5U8SpAaymveBXIaF0onkGeBgNjPpmtIbqdkXORhBoWoFbHGSErebZZi2dL6rkez1nJ53T7YaQPeFFCQQPZ725ZqlQw8VtmVDBJW/NV2cAkyWQTWTCCjcWyIpWA70cYO07kTtVQRJT/lK2vBPJr9FKK0tUDY+w1WJ+2o/87A6offbH7KzSzWJHGkBWj4YbI5/YQ9YeTisldwJ+Bt7fFaAWrbS2zKliRa50hepAzkMTZ2wGjfUe2pjMMi5BMf9JNdguhhTQJhjatbeJ0qnX6Y4oED1tDUoIXyk0SLao88m8MWrCgnTQkJ+0zj/0mbUl7jBP8vOT5tr+FNFAcHd+yAqsGy0cYJQ9noERNvCNG9dUDV1MBalwcLyRe7SrjwiLcUcD7ji2TrCh0CiU8cLSQUt9CJVs+zkJw5G5PFXY97sqjG5Yu4dAWCH5RyFskn2PB+DgIjZTgNAtXffEVJE8TT8vM1wpZZsrM30Tma2ZmL2XWMjLbZ4zNjJRk5qaMzLeNy3xbeuYHMzJPHpd5cnrmrIzMueMy56Zn/r0lPfPUcZmnpmc+mJF5971jMyMlmflHGZmfHZf52fTMy5D5NzxE4DzJwmnKxQp4KA06OkqMckpRTmYR/enYn4J8ES6iPyT+oP/kXirkMsvjEaiKHlsi31PMUWPKwD2FZSvZdZjDHCExC4nBlTKHtdkpTfHYHGCDIyRSbTRR9cpKxFZssDBDMpOWeafcifGt15xsUYWXDdyU/jyRwDammZ2XvFf+GQcFHL2aLd44enGm9Q2v3vPvp0vvWdQoBMpV9YVttyviOa7DXxTMZpNEM4RlN/W/JPQmoNJBsPaDywk8wWJ5hz5zMbsil7GJ/NhR3jA4b3x87Vf+dIkSnL9E2UXXMbqepOd/pnsh3SvofjtdS+j3T+n6R7o+XrBEUXL/P/9Zsqy27JzcSfbb/kWKm3yzDFPS56NyangrE1Izf9Gt5yfheCh80/mrnPgnF+qhGFxv1SB9jSluKR0+lOkPCbAIxngO3twafAXz9t1wfaRBX7dzulIyqNVei5xMxHNee/sQjYU4h1eLYdp4/XUeY33n5N6bz99RqLm+8+Ku6V9mfafg6i3oB6W/T/qX6G4xG701V86JX5Zz4tP6L781O22T6drnZ39pBwNDv3EX3KJ+I9o34nD2tnMO6XUm2+P54hbaU3g+hS/36VsE9eIUypmub6wbGrd/lMfz8vT1lsbUeouaObQHUxs4P5ab2apKEryZrUhrcXnoqqFLpatObmgr7ws5MVj/T8J5+fy1rUcUR+f70s6db/vaCwpphlU4eT5PdCFjKMdCRV6yfa3a5aGrhoTtPB+VVorjueiqpKuK5hFcMiy6oaVEuRO5XyXyhheILiQJz/qKN0MPlf+gKPSAUEuxjiLUMhk6oZJuZaKqykNVVrJ/+tIGSqrSS8qJTU5vupKQLFKTY7i+rafiv0PFV8RD/0b0oPiKs6FA+d9iDhNaXt67jsgZWlzeh3t4QaQPu/xs4UfEUsDwIGD4V+KxUizRiMfKsJwjHqvEMpbwVUWOZVHVldzEBv3XZUBQ5bYjSuiv4B9flMh/j6aV1N4NEtEqobnF1UhXE11r6cJeDUzz6lx1otrVVFxN9xpXY3GNSw0WKacUH71pxL+5PlU8bvMGAjS7C07n4XCDsTewMJH/IVWjv91yJcHnDDi9wrc2GtvohEtorA03EQNpmhc2r4Mrvgf/mrx+UrqGy2mgo+k0ky5w5ZzKr6kOgkpvlyVWibLIiFOc0SbTQ5221AYQtaU41KBJW5orAk0NXBSWLHKlvWVYjFJZYDcPtu6hiV0uB+aojtj70gm/ilpVLfbOoVSaKs6jFA8TuI74r8YFYldGPrc+9Y2E6/l1S5Yo1riV2Ap4v3Rv8cniN/HNpTxKq7bGwQmX7MVDxWe5hPmVONMzEZ7Mhh9svxkN6OGH76NJPDYRqnBMxsLa1wP6g5u/mnwO3U6M0+QqEDtwMvClhwK699m0tzl4dykvoK/8GafSY5F8cwd9t8NYhJznlbiI9u0EQkld5d3a4Uf10h8RMmPdTA2Hic/lNqBzuR3YXJ5L7ZgjFKAUq4Pdh+HFkxiO9KkOnoL3KnIJ1Di4GF6aNfo//PBKomSwPBaiPKLMsecopiBE7zoHZiNmPbFGoJmqijXxD7uIreUfueIZFJuk30h62e2ZZe8zy16Hsi3JsoNm2evNsjeMKzvaVzUtHR/+kvPle9ei591evreM7o59A5GBrEu3JZ90K9XuFzNlNV8Ra2zaCptYYxetudoKO/VwksGIaKL9MJf7R2Io3lXgMNTtGhJzGUugaskp/Y4F5qbTuxYvUe6n6wG6yulKl++9bZnytVd5a6y8
*/