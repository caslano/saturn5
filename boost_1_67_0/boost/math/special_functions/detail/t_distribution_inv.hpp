//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_DETAIL_INV_T_HPP
#define BOOST_MATH_SF_DETAIL_INV_T_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/trunc.hpp>

namespace boost{ namespace math{ namespace detail{

//
// The main method used is due to Hill:
//
// G. W. Hill, Algorithm 396, Student's t-Quantiles,
// Communications of the ACM, 13(10): 619-620, Oct., 1970.
//
template <class T, class Policy>
T inverse_students_t_hill(T ndf, T u, const Policy& pol)
{
   BOOST_MATH_STD_USING
   BOOST_ASSERT(u <= 0.5);

   T a, b, c, d, q, x, y;

   if (ndf > 1e20f)
      return -boost::math::erfc_inv(2 * u, pol) * constants::root_two<T>();

   a = 1 / (ndf - 0.5f);
   b = 48 / (a * a);
   c = ((20700 * a / b - 98) * a - 16) * a + 96.36f;
   d = ((94.5f / (b + c) - 3) / b + 1) * sqrt(a * constants::pi<T>() / 2) * ndf;
   y = pow(d * 2 * u, 2 / ndf);

   if (y > (0.05f + a))
   {
      //
      // Asymptotic inverse expansion about normal:
      //
      x = -boost::math::erfc_inv(2 * u, pol) * constants::root_two<T>();
      y = x * x;

      if (ndf < 5)
         c += 0.3f * (ndf - 4.5f) * (x + 0.6f);
      c += (((0.05f * d * x - 5) * x - 7) * x - 2) * x + b;
      y = (((((0.4f * y + 6.3f) * y + 36) * y + 94.5f) / c - y - 3) / b + 1) * x;
      y = boost::math::expm1(a * y * y, pol);
   }
   else
   {
      y = static_cast<T>(((1 / (((ndf + 6) / (ndf * y) - 0.089f * d - 0.822f)
              * (ndf + 2) * 3) + 0.5 / (ndf + 4)) * y - 1)
              * (ndf + 1) / (ndf + 2) + 1 / y);
   }
   q = sqrt(ndf * y);

   return -q;
}
//
// Tail and body series are due to Shaw:
//
// www.mth.kcl.ac.uk/~shaww/web_page/papers/Tdistribution06.pdf
//
// Shaw, W.T., 2006, "Sampling Student's T distribution - use of
// the inverse cumulative distribution function."
// Journal of Computational Finance, Vol 9 Issue 4, pp 37-73, Summer 2006
//
template <class T, class Policy>
T inverse_students_t_tail_series(T df, T v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   // Tail series expansion, see section 6 of Shaw's paper.
   // w is calculated using Eq 60:
   T w = boost::math::tgamma_delta_ratio(df / 2, constants::half<T>(), pol)
      * sqrt(df * constants::pi<T>()) * v;
   // define some variables:
   T np2 = df + 2;
   T np4 = df + 4;
   T np6 = df + 6;
   //
   // Calculate the coefficients d(k), these depend only on the
   // number of degrees of freedom df, so at least in theory
   // we could tabulate these for fixed df, see p15 of Shaw:
   //
   T d[7] = { 1, };
   d[1] = -(df + 1) / (2 * np2);
   np2 *= (df + 2);
   d[2] = -df * (df + 1) * (df + 3) / (8 * np2 * np4);
   np2 *= df + 2;
   d[3] = -df * (df + 1) * (df + 5) * (((3 * df) + 7) * df -2) / (48 * np2 * np4 * np6);
   np2 *= (df + 2);
   np4 *= (df + 4);
   d[4] = -df * (df + 1) * (df + 7) *
      ( (((((15 * df) + 154) * df + 465) * df + 286) * df - 336) * df + 64 )
      / (384 * np2 * np4 * np6 * (df + 8));
   np2 *= (df + 2);
   d[5] = -df * (df + 1) * (df + 3) * (df + 9)
            * (((((((35 * df + 452) * df + 1573) * df + 600) * df - 2020) * df) + 928) * df -128)
            / (1280 * np2 * np4 * np6 * (df + 8) * (df + 10));
   np2 *= (df + 2);
   np4 *= (df + 4);
   np6 *= (df + 6);
   d[6] = -df * (df + 1) * (df + 11)
            * ((((((((((((945 * df) + 31506) * df + 425858) * df + 2980236) * df + 11266745) * df + 20675018) * df + 7747124) * df - 22574632) * df - 8565600) * df + 18108416) * df - 7099392) * df + 884736)
            / (46080 * np2 * np4 * np6 * (df + 8) * (df + 10) * (df +12));
   //
   // Now bring everything together to provide the result,
   // this is Eq 62 of Shaw:
   //
   T rn = sqrt(df);
   T div = pow(rn * w, 1 / df);
   T power = div * div;
   T result = tools::evaluate_polynomial<7, T, T>(d, power);
   result *= rn;
   result /= div;
   return -result;
}

template <class T, class Policy>
T inverse_students_t_body_series(T df, T u, const Policy& pol)
{
   BOOST_MATH_STD_USING
   //
   // Body series for small N:
   //
   // Start with Eq 56 of Shaw:
   //
   T v = boost::math::tgamma_delta_ratio(df / 2, constants::half<T>(), pol)
      * sqrt(df * constants::pi<T>()) * (u - constants::half<T>());
   //
   // Workspace for the polynomial coefficients:
   //
   T c[11] = { 0, 1, };
   //
   // Figure out what the coefficients are, note these depend
   // only on the degrees of freedom (Eq 57 of Shaw):
   //
   T in = 1 / df;
   c[2] = static_cast<T>(0.16666666666666666667 + 0.16666666666666666667 * in);
   c[3] = static_cast<T>((0.0083333333333333333333 * in
      + 0.066666666666666666667) * in 
      + 0.058333333333333333333);
   c[4] = static_cast<T>(((0.00019841269841269841270 * in
      + 0.0017857142857142857143) * in 
      + 0.026785714285714285714) * in 
      + 0.025198412698412698413);
   c[5] = static_cast<T>((((2.7557319223985890653e-6 * in
      + 0.00037477954144620811287) * in 
      - 0.0011078042328042328042) * in 
      + 0.010559964726631393298) * in 
      + 0.012039792768959435626);
   c[6] = static_cast<T>(((((2.5052108385441718775e-8 * in
      - 0.000062705427288760622094) * in 
      + 0.00059458674042007375341) * in 
      - 0.0016095979637646304313) * in 
      + 0.0061039211560044893378) * in 
      + 0.0038370059724226390893);
   c[7] = static_cast<T>((((((1.6059043836821614599e-10 * in
      + 0.000015401265401265401265) * in 
      - 0.00016376804137220803887) * in
      + 0.00069084207973096861986) * in 
      - 0.0012579159844784844785) * in 
      + 0.0010898206731540064873) * in 
      + 0.0032177478835464946576);
   c[8] = static_cast<T>(((((((7.6471637318198164759e-13 * in
      - 3.9851014346715404916e-6) * in
      + 0.000049255746366361445727) * in
      - 0.00024947258047043099953) * in 
      + 0.00064513046951456342991) * in
      - 0.00076245135440323932387) * in
      + 0.000033530976880017885309) * in 
      + 0.0017438262298340009980);
   c[9] = static_cast<T>((((((((2.8114572543455207632e-15 * in
      + 1.0914179173496789432e-6) * in
      - 0.000015303004486655377567) * in
      + 0.000090867107935219902229) * in
      - 0.00029133414466938067350) * in
      + 0.00051406605788341121363) * in
      - 0.00036307660358786885787) * in
      - 0.00031101086326318780412) * in 
      + 0.00096472747321388644237);
   c[10] = static_cast<T>(((((((((8.2206352466243297170e-18 * in
      - 3.1239569599829868045e-7) * in
      + 4.8903045291975346210e-6) * in
      - 0.000033202652391372058698) * in
      + 0.00012645437628698076975) * in
      - 0.00028690924218514613987) * in
      + 0.00035764655430568632777) * in
      - 0.00010230378073700412687) * in
      - 0.00036942667800009661203) * in
      + 0.00054229262813129686486);
   //
   // The result is then a polynomial in v (see Eq 56 of Shaw):
   //
   return tools::evaluate_odd_polynomial<11, T, T>(c, v);
}

template <class T, class Policy>
T inverse_students_t(T df, T u, T v, const Policy& pol, bool* pexact = 0)
{
   //
   // df = number of degrees of freedom.
   // u = probability.
   // v = 1 - u.
   // l = lanczos type to use.
   //
   BOOST_MATH_STD_USING
   bool invert = false;
   T result = 0;
   if(pexact)
      *pexact = false;
   if(u > v)
   {
      // function is symmetric, invert it:
      std::swap(u, v);
      invert = true;
   }
   if((floor(df) == df) && (df < 20))
   {
      //
      // we have integer degrees of freedom, try for the special
      // cases first:
      //
      T tolerance = ldexp(1.0f, (2 * policies::digits<T, Policy>()) / 3);

      switch(itrunc(df, Policy()))
      {
      case 1:
         {
            //
            // df = 1 is the same as the Cauchy distribution, see
            // Shaw Eq 35:
            //
            if(u == 0.5)
               result = 0;
            else
               result = -cos(constants::pi<T>() * u) / sin(constants::pi<T>() * u);
            if(pexact)
               *pexact = true;
            break;
         }
      case 2:
         {
            //
            // df = 2 has an exact result, see Shaw Eq 36:
            //
            result =(2 * u - 1) / sqrt(2 * u * v);
            if(pexact)
               *pexact = true;
            break;
         }
      case 4:
         {
            //
            // df = 4 has an exact result, see Shaw Eq 38 & 39:
            //
            T alpha = 4 * u * v;
            T root_alpha = sqrt(alpha);
            T r = 4 * cos(acos(root_alpha) / 3) / root_alpha;
            T x = sqrt(r - 4);
            result = u - 0.5f < 0 ? (T)-x : x;
            if(pexact)
               *pexact = true;
            break;
         }
      case 6:
         {
            //
            // We get numeric overflow in this area:
            //
            if(u < 1e-150)
               return (invert ? -1 : 1) * inverse_students_t_hill(df, u, pol);
            //
            // Newton-Raphson iteration of a polynomial case,
            // choice of seed value is taken from Shaw's online
            // supplement:
            //
            T a = 4 * (u - u * u);//1 - 4 * (u - 0.5f) * (u - 0.5f);
            T b = boost::math::cbrt(a);
            static const T c = static_cast<T>(0.85498797333834849467655443627193);
            T p = 6 * (1 + c * (1 / b - 1));
            T p0;
            do{
               T p2 = p * p;
               T p4 = p2 * p2;
               T p5 = p * p4;
               p0 = p;
               // next term is given by Eq 41:
               p = 2 * (8 * a * p5 - 270 * p2 + 2187) / (5 * (4 * a * p4 - 216 * p - 243));
            }while(fabs((p - p0) / p) > tolerance);
            //
            // Use Eq 45 to extract the result:
            //
            p = sqrt(p - df);
            result = (u - 0.5f) < 0 ? (T)-p : p;
            break;
         }
#if 0
         //
         // These are Shaw's "exact" but iterative solutions
         // for even df, the numerical accuracy of these is
         // rather less than Hill's method, so these are disabled
         // for now, which is a shame because they are reasonably
         // quick to evaluate...
         //
      case 8:
         {
            //
            // Newton-Raphson iteration of a polynomial case,
            // choice of seed value is taken from Shaw's online
            // supplement:
            //
            static const T c8 = 0.85994765706259820318168359251872L;
            T a = 4 * (u - u * u); //1 - 4 * (u - 0.5f) * (u - 0.5f);
            T b = pow(a, T(1) / 4);
            T p = 8 * (1 + c8 * (1 / b - 1));
            T p0 = p;
            do{
               T p5 = p * p;
               p5 *= p5 * p;
               p0 = p;
               // Next term is given by Eq 42:
               p = 2 * (3 * p + (640 * (160 + p * (24 + p * (p + 4)))) / (-5120 + p * (-2048 - 960 * p + a * p5))) / 7;
            }while(fabs((p - p0) / p) > tolerance);
            //
            // Use Eq 45 to extract the result:
            //
            p = sqrt(p - df);
            result = (u - 0.5f) < 0 ? -p : p;
            break;
         }
      case 10:
         {
            //
            // Newton-Raphson iteration of a polynomial case,
            // choice of seed value is taken from Shaw's online
            // supplement:
            //
            static const T c10 = 0.86781292867813396759105692122285L;
            T a = 4 * (u - u * u); //1 - 4 * (u - 0.5f) * (u - 0.5f);
            T b = pow(a, T(1) / 5);
            T p = 10 * (1 + c10 * (1 / b - 1));
            T p0;
            do{
               T p6 = p * p;
               p6 *= p6 * p6;
               p0 = p;
               // Next term given by Eq 43:
               p = (8 * p) / 9 + (218750 * (21875 + 4 * p * (625 + p * (75 + 2 * p * (5 + p))))) /
                  (9 * (-68359375 + 8 * p * (-2343750 + p * (-546875 - 175000 * p + 8 * a * p6))));
            }while(fabs((p - p0) / p) > tolerance);
            //
            // Use Eq 45 to extract the result:
            //
            p = sqrt(p - df);
            result = (u - 0.5f) < 0 ? -p : p;
            break;
         }
#endif
      default:
         goto calculate_real;
      }
   }
   else
   {
calculate_real:
      if(df > 0x10000000)
      {
         result = -boost::math::erfc_inv(2 * u, pol) * constants::root_two<T>();
         if((pexact) && (df >= 1e20))
            *pexact = true;
      }
      else if(df < 3)
      {
         //
         // Use a roughly linear scheme to choose between Shaw's
         // tail series and body series:
         //
         T crossover = 0.2742f - df * 0.0242143f;
         if(u > crossover)
         {
            result = boost::math::detail::inverse_students_t_body_series(df, u, pol);
         }
         else
         {
            result = boost::math::detail::inverse_students_t_tail_series(df, u, pol);
         }
      }
      else
      {
         //
         // Use Hill's method except in the extreme tails
         // where we use Shaw's tail series.
         // The crossover point is roughly exponential in -df:
         //
         T crossover = ldexp(1.0f, iround(T(df / -0.654f), typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type()));
         if(u > crossover)
         {
            result = boost::math::detail::inverse_students_t_hill(df, u, pol);
         }
         else
         {
            result = boost::math::detail::inverse_students_t_tail_series(df, u, pol);
         }
      }
   }
   return invert ? (T)-result : result;
}

template <class T, class Policy>
inline T find_ibeta_inv_from_t_dist(T a, T p, T /*q*/, T* py, const Policy& pol)
{
   T u = p / 2;
   T v = 1 - u;
   T df = a * 2;
   T t = boost::math::detail::inverse_students_t(df, u, v, pol);
   *py = t * t / (df + t * t);
   return df / (df + t * t);
}

template <class T, class Policy>
inline T fast_students_t_quantile_imp(T df, T p, const Policy& pol, const boost::false_type*)
{
   BOOST_MATH_STD_USING
   //
   // Need to use inverse incomplete beta to get
   // required precision so not so fast:
   //
   T probability = (p > 0.5) ? 1 - p : p;
   T t, x, y(0);
   x = ibeta_inv(df / 2, T(0.5), 2 * probability, &y, pol);
   if(df * y > tools::max_value<T>() * x)
      t = policies::raise_overflow_error<T>("boost::math::students_t_quantile<%1%>(%1%,%1%)", 0, pol);
   else
      t = sqrt(df * y / x);
   //
   // Figure out sign based on the size of p:
   //
   if(p < 0.5)
      t = -t;
   return t;
}

template <class T, class Policy>
T fast_students_t_quantile_imp(T df, T p, const Policy& pol, const boost::true_type*)
{
   BOOST_MATH_STD_USING
   bool invert = false;
   if((df < 2) && (floor(df) != df))
      return boost::math::detail::fast_students_t_quantile_imp(df, p, pol, static_cast<boost::false_type*>(0));
   if(p > 0.5)
   {
      p = 1 - p;
      invert = true;
   }
   //
   // Get an estimate of the result:
   //
   bool exact;
   T t = inverse_students_t(df, p, T(1-p), pol, &exact);
   if((t == 0) || exact)
      return invert ? -t : t; // can't do better!
   //
   // Change variables to inverse incomplete beta:
   //
   T t2 = t * t;
   T xb = df / (df + t2);
   T y = t2 / (df + t2);
   T a = df / 2;
   //
   // t can be so large that x underflows,
   // just return our estimate in that case:
   //
   if(xb == 0)
      return t;
   //
   // Get incomplete beta and it's derivative:
   //
   T f1;
   T f0 = xb < y ? ibeta_imp(a, constants::half<T>(), xb, pol, false, true, &f1)
      : ibeta_imp(constants::half<T>(), a, y, pol, true, true, &f1);

   // Get cdf from incomplete beta result:
   T p0 = f0 / 2  - p;
   // Get pdf from derivative:
   T p1 = f1 * sqrt(y * xb * xb * xb / df);
   //
   // Second derivative divided by p1:
   //
   // yacas gives:
   //
   // In> PrettyForm(Simplify(D(t) (1 + t^2/v) ^ (-(v+1)/2)))
   //
   //  |                        | v + 1     |     |
   //  |                       -| ----- + 1 |     |
   //  |                        |   2       |     |
   // -|             |  2     |                   |
   //  |             | t      |                   |
   //  |             | -- + 1 |                   |
   //  | ( v + 1 ) * | v      |               * t |
   // ---------------------------------------------
   //                       v
   //
   // Which after some manipulation is:
   //
   // -p1 * t * (df + 1) / (t^2 + df)
   //
   T p2 = t * (df + 1) / (t * t + df);
   // Halley step:
   t = fabs(t);
   t += p0 / (p1 + p0 * p2 / 2);
   return !invert ? -t : t;
}

template <class T, class Policy>
inline T fast_students_t_quantile(T df, T p, const Policy& pol)
{
   typedef typename policies::evaluation<T, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   typedef boost::integral_constant<bool,
      (std::numeric_limits<T>::digits <= 53)
       &&
      (std::numeric_limits<T>::is_specialized)
       &&
      (std::numeric_limits<T>::radix == 2)
   > tag_type;
   return policies::checked_narrowing_cast<T, forwarding_policy>(fast_students_t_quantile_imp(static_cast<value_type>(df), static_cast<value_type>(p), pol, static_cast<tag_type*>(0)), "boost::math::students_t_quantile<%1%>(%1%,%1%,%1%)");
}

}}} // namespaces

#endif // BOOST_MATH_SF_DETAIL_INV_T_HPP




/* t_distribution_inv.hpp
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
*/