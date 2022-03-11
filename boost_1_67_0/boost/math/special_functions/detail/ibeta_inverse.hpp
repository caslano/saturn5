//  Copyright John Maddock 2006.
//  Copyright Paul A. Bristow 2007
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_FUNCTIONS_IBETA_INVERSE_HPP
#define BOOST_MATH_SPECIAL_FUNCTIONS_IBETA_INVERSE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/beta.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/special_functions/detail/t_distribution_inv.hpp>

namespace boost{ namespace math{ namespace detail{

//
// Helper object used by root finding
// code to convert eta to x.
//
template <class T>
struct temme_root_finder
{
   temme_root_finder(const T t_, const T a_) : t(t_), a(a_) {}

   boost::math::tuple<T, T> operator()(T x)
   {
      BOOST_MATH_STD_USING // ADL of std names

      T y = 1 - x;
      if(y == 0)
      {
         T big = tools::max_value<T>() / 4;
         return boost::math::make_tuple(static_cast<T>(-big), static_cast<T>(-big));
      }
      if(x == 0)
      {
         T big = tools::max_value<T>() / 4;
         return boost::math::make_tuple(static_cast<T>(-big), big);
      }
      T f = log(x) + a * log(y) + t;
      T f1 = (1 / x) - (a / (y));
      return boost::math::make_tuple(f, f1);
   }
private:
   T t, a;
};
//
// See:
// "Asymptotic Inversion of the Incomplete Beta Function"
// N.M. Temme
// Journal of Computation and Applied Mathematics 41 (1992) 145-157.
// Section 2.
//
template <class T, class Policy>
T temme_method_1_ibeta_inverse(T a, T b, T z, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names

   const T r2 = sqrt(T(2));
   //
   // get the first approximation for eta from the inverse
   // error function (Eq: 2.9 and 2.10).
   //
   T eta0 = boost::math::erfc_inv(2 * z, pol);
   eta0 /= -sqrt(a / 2);

   T terms[4] = { eta0 };
   T workspace[7];
   //
   // calculate powers:
   //
   T B = b - a;
   T B_2 = B * B;
   T B_3 = B_2 * B;
   //
   // Calculate correction terms:
   //

   // See eq following 2.15:
   workspace[0] = -B * r2 / 2;
   workspace[1] = (1 - 2 * B) / 8;
   workspace[2] = -(B * r2 / 48);
   workspace[3] = T(-1) / 192;
   workspace[4] = -B * r2 / 3840;
   terms[1] = tools::evaluate_polynomial(workspace, eta0, 5);
   // Eq Following 2.17:
   workspace[0] = B * r2 * (3 * B - 2) / 12;
   workspace[1] = (20 * B_2 - 12 * B + 1) / 128;
   workspace[2] = B * r2 * (20 * B - 1) / 960;
   workspace[3] = (16 * B_2 + 30 * B - 15) / 4608;
   workspace[4] = B * r2 * (21 * B + 32) / 53760;
   workspace[5] = (-32 * B_2 + 63) / 368640;
   workspace[6] = -B * r2 * (120 * B + 17) / 25804480;
   terms[2] = tools::evaluate_polynomial(workspace, eta0, 7);
   // Eq Following 2.17:
   workspace[0] = B * r2 * (-75 * B_2 + 80 * B - 16) / 480;
   workspace[1] = (-1080 * B_3 + 868 * B_2 - 90 * B - 45) / 9216;
   workspace[2] = B * r2 * (-1190 * B_2 + 84 * B + 373) / 53760;
   workspace[3] = (-2240 * B_3 - 2508 * B_2 + 2100 * B - 165) / 368640;
   terms[3] = tools::evaluate_polynomial(workspace, eta0, 4);
   //
   // Bring them together to get a final estimate for eta:
   //
   T eta = tools::evaluate_polynomial(terms, T(1/a), 4);
   //
   // now we need to convert eta to x, by solving the appropriate
   // quadratic equation:
   //
   T eta_2 = eta * eta;
   T c = -exp(-eta_2 / 2);
   T x;
   if(eta_2 == 0)
      x = 0.5;
   else
      x = (1 + eta * sqrt((1 + c) / eta_2)) / 2;

   BOOST_ASSERT(x >= 0);
   BOOST_ASSERT(x <= 1);
   BOOST_ASSERT(eta * (x - 0.5) >= 0);
#ifdef BOOST_INSTRUMENT
   std::cout << "Estimating x with Temme method 1: " << x << std::endl;
#endif
   return x;
}
//
// See:
// "Asymptotic Inversion of the Incomplete Beta Function"
// N.M. Temme
// Journal of Computation and Applied Mathematics 41 (1992) 145-157.
// Section 3.
//
template <class T, class Policy>
T temme_method_2_ibeta_inverse(T /*a*/, T /*b*/, T z, T r, T theta, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names

   //
   // Get first estimate for eta, see Eq 3.9 and 3.10,
   // but note there is a typo in Eq 3.10:
   //
   T eta0 = boost::math::erfc_inv(2 * z, pol);
   eta0 /= -sqrt(r / 2);

   T s = sin(theta);
   T c = cos(theta);
   //
   // Now we need to perturb eta0 to get eta, which we do by
   // evaluating the polynomial in 1/r at the bottom of page 151,
   // to do this we first need the error terms e1, e2 e3
   // which we'll fill into the array "terms".  Since these
   // terms are themselves polynomials, we'll need another
   // array "workspace" to calculate those...
   //
   T terms[4] = { eta0 };
   T workspace[6];
   //
   // some powers of sin(theta)cos(theta) that we'll need later:
   //
   T sc = s * c;
   T sc_2 = sc * sc;
   T sc_3 = sc_2 * sc;
   T sc_4 = sc_2 * sc_2;
   T sc_5 = sc_2 * sc_3;
   T sc_6 = sc_3 * sc_3;
   T sc_7 = sc_4 * sc_3;
   //
   // Calculate e1 and put it in terms[1], see the middle of page 151:
   //
   workspace[0] = (2 * s * s - 1) / (3 * s * c);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co1[] = { -1, -5, 5 };
   workspace[1] = -tools::evaluate_even_polynomial(co1, s, 3) / (36 * sc_2);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co2[] = { 1, 21, -69, 46 };
   workspace[2] = tools::evaluate_even_polynomial(co2, s, 4) / (1620 * sc_3);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co3[] = { 7, -2, 33, -62, 31 };
   workspace[3] = -tools::evaluate_even_polynomial(co3, s, 5) / (6480 * sc_4);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co4[] = { 25, -52, -17, 88, -115, 46 };
   workspace[4] = tools::evaluate_even_polynomial(co4, s, 6) / (90720 * sc_5);
   terms[1] = tools::evaluate_polynomial(workspace, eta0, 5);
   //
   // Now evaluate e2 and put it in terms[2]:
   //
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co5[] = { 7, 12, -78, 52 };
   workspace[0] = -tools::evaluate_even_polynomial(co5, s, 4) / (405 * sc_3);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co6[] = { -7, 2, 183, -370, 185 };
   workspace[1] = tools::evaluate_even_polynomial(co6, s, 5) / (2592 * sc_4);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co7[] = { -533, 776, -1835, 10240, -13525, 5410 };
   workspace[2] = -tools::evaluate_even_polynomial(co7, s, 6) / (204120 * sc_5);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co8[] = { -1579, 3747, -3372, -15821, 45588, -45213, 15071 };
   workspace[3] = -tools::evaluate_even_polynomial(co8, s, 7) / (2099520 * sc_6);
   terms[2] = tools::evaluate_polynomial(workspace, eta0, 4);
   //
   // And e3, and put it in terms[3]:
   //
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co9[] = {449, -1259, -769, 6686, -9260, 3704 };
   workspace[0] = tools::evaluate_even_polynomial(co9, s, 6) / (102060 * sc_5);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co10[] = { 63149, -151557, 140052, -727469, 2239932, -2251437, 750479 };
   workspace[1] = -tools::evaluate_even_polynomial(co10, s, 7) / (20995200 * sc_6);
   static const BOOST_MATH_INT_TABLE_TYPE(T, int) co11[] = { 29233, -78755, 105222, 146879, -1602610, 3195183, -2554139, 729754 };
   workspace[2] = tools::evaluate_even_polynomial(co11, s, 8) / (36741600 * sc_7);
   terms[3] = tools::evaluate_polynomial(workspace, eta0, 3);
   //
   // Bring the correction terms together to evaluate eta,
   // this is the last equation on page 151:
   //
   T eta = tools::evaluate_polynomial(terms, T(1/r), 4);
   //
   // Now that we have eta we need to back solve for x,
   // we seek the value of x that gives eta in Eq 3.2.
   // The two methods used are described in section 5.
   //
   // Begin by defining a few variables we'll need later:
   //
   T x;
   T s_2 = s * s;
   T c_2 = c * c;
   T alpha = c / s;
   alpha *= alpha;
   T lu = (-(eta * eta) / (2 * s_2) + log(s_2) + c_2 * log(c_2) / s_2);
   //
   // Temme doesn't specify what value to switch on here,
   // but this seems to work pretty well:
   //
   if(fabs(eta) < 0.7)
   {
      //
      // Small eta use the expansion Temme gives in the second equation
      // of section 5, it's a polynomial in eta:
      //
      workspace[0] = s * s;
      workspace[1] = s * c;
      workspace[2] = (1 - 2 * workspace[0]) / 3;
      static const BOOST_MATH_INT_TABLE_TYPE(T, int) co12[] = { 1, -13, 13 };
      workspace[3] = tools::evaluate_polynomial(co12, workspace[0], 3) / (36 * s * c);
      static const BOOST_MATH_INT_TABLE_TYPE(T, int) co13[] = { 1, 21, -69, 46 };
      workspace[4] = tools::evaluate_polynomial(co13, workspace[0], 4) / (270 * workspace[0] * c * c);
      x = tools::evaluate_polynomial(workspace, eta, 5);
#ifdef BOOST_INSTRUMENT
      std::cout << "Estimating x with Temme method 2 (small eta): " << x << std::endl;
#endif
   }
   else
   {
      //
      // If eta is large we need to solve Eq 3.2 more directly,
      // begin by getting an initial approximation for x from
      // the last equation on page 155, this is a polynomial in u:
      //
      T u = exp(lu);
      workspace[0] = u;
      workspace[1] = alpha;
      workspace[2] = 0;
      workspace[3] = 3 * alpha * (3 * alpha + 1) / 6;
      workspace[4] = 4 * alpha * (4 * alpha + 1) * (4 * alpha + 2) / 24;
      workspace[5] = 5 * alpha * (5 * alpha + 1) * (5 * alpha + 2) * (5 * alpha + 3) / 120;
      x = tools::evaluate_polynomial(workspace, u, 6);
      //
      // At this point we may or may not have the right answer, Eq-3.2 has
      // two solutions for x for any given eta, however the mapping in 3.2
      // is 1:1 with the sign of eta and x-sin^2(theta) being the same.
      // So we can check if we have the right root of 3.2, and if not
      // switch x for 1-x.  This transformation is motivated by the fact
      // that the distribution is *almost* symmetric so 1-x will be in the right
      // ball park for the solution:
      //
      if((x - s_2) * eta < 0)
         x = 1 - x;
#ifdef BOOST_INSTRUMENT
      std::cout << "Estimating x with Temme method 2 (large eta): " << x << std::endl;
#endif
   }
   //
   // The final step is a few Newton-Raphson iterations to
   // clean up our approximation for x, this is pretty cheap
   // in general, and very cheap compared to an incomplete beta
   // evaluation.  The limits set on x come from the observation
   // that the sign of eta and x-sin^2(theta) are the same.
   //
   T lower, upper;
   if(eta < 0)
   {
      lower = 0;
      upper = s_2;
   }
   else
   {
      lower = s_2;
      upper = 1;
   }
   //
   // If our initial approximation is out of bounds then bisect:
   //
   if((x < lower) || (x > upper))
      x = (lower+upper) / 2;
   //
   // And iterate:
   //
   x = tools::newton_raphson_iterate(
      temme_root_finder<T>(-lu, alpha), x, lower, upper, policies::digits<T, Policy>() / 2);

   return x;
}
//
// See:
// "Asymptotic Inversion of the Incomplete Beta Function"
// N.M. Temme
// Journal of Computation and Applied Mathematics 41 (1992) 145-157.
// Section 4.
//
template <class T, class Policy>
T temme_method_3_ibeta_inverse(T a, T b, T p, T q, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names

   //
   // Begin by getting an initial approximation for the quantity
   // eta from the dominant part of the incomplete beta:
   //
   T eta0;
   if(p < q)
      eta0 = boost::math::gamma_q_inv(b, p, pol);
   else
      eta0 = boost::math::gamma_p_inv(b, q, pol);
   eta0 /= a;
   //
   // Define the variables and powers we'll need later on:
   //
   T mu = b / a;
   T w = sqrt(1 + mu);
   T w_2 = w * w;
   T w_3 = w_2 * w;
   T w_4 = w_2 * w_2;
   T w_5 = w_3 * w_2;
   T w_6 = w_3 * w_3;
   T w_7 = w_4 * w_3;
   T w_8 = w_4 * w_4;
   T w_9 = w_5 * w_4;
   T w_10 = w_5 * w_5;
   T d = eta0 - mu;
   T d_2 = d * d;
   T d_3 = d_2 * d;
   T d_4 = d_2 * d_2;
   T w1 = w + 1;
   T w1_2 = w1 * w1;
   T w1_3 = w1 * w1_2;
   T w1_4 = w1_2 * w1_2;
   //
   // Now we need to compute the perturbation error terms that
   // convert eta0 to eta, these are all polynomials of polynomials.
   // Probably these should be re-written to use tabulated data
   // (see examples above), but it's less of a win in this case as we
   // need to calculate the individual powers for the denominator terms
   // anyway, so we might as well use them for the numerator-polynomials
   // as well....
   //
   // Refer to p154-p155 for the details of these expansions:
   //
   T e1 = (w + 2) * (w - 1) / (3 * w);
   e1 += (w_3 + 9 * w_2 + 21 * w + 5) * d / (36 * w_2 * w1);
   e1 -= (w_4 - 13 * w_3 + 69 * w_2 + 167 * w + 46) * d_2 / (1620 * w1_2 * w_3);
   e1 -= (7 * w_5 + 21 * w_4 + 70 * w_3 + 26 * w_2 - 93 * w - 31) * d_3 / (6480 * w1_3 * w_4);
   e1 -= (75 * w_6 + 202 * w_5 + 188 * w_4 - 888 * w_3 - 1345 * w_2 + 118 * w + 138) * d_4 / (272160 * w1_4 * w_5);

   T e2 = (28 * w_4 + 131 * w_3 + 402 * w_2 + 581 * w + 208) * (w - 1) / (1620 * w1 * w_3);
   e2 -= (35 * w_6 - 154 * w_5 - 623 * w_4 - 1636 * w_3 - 3983 * w_2 - 3514 * w - 925) * d / (12960 * w1_2 * w_4);
   e2 -= (2132 * w_7 + 7915 * w_6 + 16821 * w_5 + 35066 * w_4 + 87490 * w_3 + 141183 * w_2 + 95993 * w + 21640) * d_2  / (816480 * w_5 * w1_3);
   e2 -= (11053 * w_8 + 53308 * w_7 + 117010 * w_6 + 163924 * w_5 + 116188 * w_4 - 258428 * w_3 - 677042 * w_2 - 481940 * w - 105497) * d_3 / (14696640 * w1_4 * w_6);

   T e3 = -((3592 * w_7 + 8375 * w_6 - 1323 * w_5 - 29198 * w_4 - 89578 * w_3 - 154413 * w_2 - 116063 * w - 29632) * (w - 1)) / (816480 * w_5 * w1_2);
   e3 -= (442043 * w_9 + 2054169 * w_8 + 3803094 * w_7 + 3470754 * w_6 + 2141568 * w_5 - 2393568 * w_4 - 19904934 * w_3 - 34714674 * w_2 - 23128299 * w - 5253353) * d / (146966400 * w_6 * w1_3);
   e3 -= (116932 * w_10 + 819281 * w_9 + 2378172 * w_8 + 4341330 * w_7 + 6806004 * w_6 + 10622748 * w_5 + 18739500 * w_4 + 30651894 * w_3 + 30869976 * w_2 + 15431867 * w + 2919016) * d_2 / (146966400 * w1_4 * w_7);
   //
   // Combine eta0 and the error terms to compute eta (Second equation p155):
   //
   T eta = eta0 + e1 / a + e2 / (a * a) + e3 / (a * a * a);
   //
   // Now we need to solve Eq 4.2 to obtain x.  For any given value of
   // eta there are two solutions to this equation, and since the distribution
   // may be very skewed, these are not related by x ~ 1-x we used when
   // implementing section 3 above.  However we know that:
   //
   //  cross < x <= 1       ; iff eta < mu
   //          x == cross   ; iff eta == mu
   //     0 <= x < cross    ; iff eta > mu
   //
   // Where cross == 1 / (1 + mu)
   // Many thanks to Prof Temme for clarifying this point.
   //
   // Therefore we'll just jump straight into Newton iterations
   // to solve Eq 4.2 using these bounds, and simple bisection
   // as the first guess, in practice this converges pretty quickly
   // and we only need a few digits correct anyway:
   //
   if(eta <= 0)
      eta = tools::min_value<T>();
   T u = eta - mu * log(eta) + (1 + mu) * log(1 + mu) - mu;
   T cross = 1 / (1 + mu);
   T lower = eta < mu ? cross : 0;
   T upper = eta < mu ? 1 : cross;
   T x = (lower + upper) / 2;
   x = tools::newton_raphson_iterate(
      temme_root_finder<T>(u, mu), x, lower, upper, policies::digits<T, Policy>() / 2);
#ifdef BOOST_INSTRUMENT
   std::cout << "Estimating x with Temme method 3: " << x << std::endl;
#endif
   return x;
}

template <class T, class Policy>
struct ibeta_roots
{
   ibeta_roots(T _a, T _b, T t, bool inv = false)
      : a(_a), b(_b), target(t), invert(inv) {}

   boost::math::tuple<T, T, T> operator()(T x)
   {
      BOOST_MATH_STD_USING // ADL of std names

      BOOST_FPU_EXCEPTION_GUARD
      
      T f1;
      T y = 1 - x;
      T f = ibeta_imp(a, b, x, Policy(), invert, true, &f1) - target;
      if(invert)
         f1 = -f1;
      if(y == 0)
         y = tools::min_value<T>() * 64;
      if(x == 0)
         x = tools::min_value<T>() * 64;

      T f2 = f1 * (-y * a + (b - 2) * x + 1);
      if(fabs(f2) < y * x * tools::max_value<T>())
         f2 /= (y * x);
      if(invert)
         f2 = -f2;

      // make sure we don't have a zero derivative:
      if(f1 == 0)
         f1 = (invert ? -1 : 1) * tools::min_value<T>() * 64;

      return boost::math::make_tuple(f, f1, f2);
   }
private:
   T a, b, target;
   bool invert;
};

template <class T, class Policy>
T ibeta_inv_imp(T a, T b, T p, T q, const Policy& pol, T* py)
{
   BOOST_MATH_STD_USING  // For ADL of math functions.

   //
   // The flag invert is set to true if we swap a for b and p for q,
   // in which case the result has to be subtracted from 1:
   //
   bool invert = false;
   //
   // Handle trivial cases first:
   //
   if(q == 0)
   {
      if(py) *py = 0;
      return 1;
   }
   else if(p == 0)
   {
      if(py) *py = 1;
      return 0;
   }
   else if(a == 1)
   {
      if(b == 1)
      {
         if(py) *py = 1 - p;
         return p;
      }
      // Change things around so we can handle as b == 1 special case below:
      std::swap(a, b);
      std::swap(p, q);
      invert = true;
   }
   //
   // Depending upon which approximation method we use, we may end up
   // calculating either x or y initially (where y = 1-x):
   //
   T x = 0; // Set to a safe zero to avoid a
   // MSVC 2005 warning C4701: potentially uninitialized local variable 'x' used
   // But code inspection appears to ensure that x IS assigned whatever the code path.
   T y; 

   // For some of the methods we can put tighter bounds
   // on the result than simply [0,1]:
   //
   T lower = 0;
   T upper = 1;
   //
   // Student's T with b = 0.5 gets handled as a special case, swap
   // around if the arguments are in the "wrong" order:
   //
   if(a == 0.5f)
   {
      if(b == 0.5f)
      {
         x = sin(p * constants::half_pi<T>());
         x *= x;
         if(py)
         {
            *py = sin(q * constants::half_pi<T>());
            *py *= *py;
         }
         return x;
      }
      else if(b > 0.5f)
      {
         std::swap(a, b);
         std::swap(p, q);
         invert = !invert;
      }
   }
   //
   // Select calculation method for the initial estimate:
   //
   if((b == 0.5f) && (a >= 0.5f) && (p != 1))
   {
      //
      // We have a Student's T distribution:
      x = find_ibeta_inv_from_t_dist(a, p, q, &y, pol);
   }
   else if(b == 1)
   {
      if(p < q)
      {
         if(a > 1)
         {
            x = pow(p, 1 / a);
            y = -boost::math::expm1(log(p) / a, pol);
         }
         else
         {
            x = pow(p, 1 / a);
            y = 1 - x;
         }
      }
      else
      {
         x = exp(boost::math::log1p(-q, pol) / a);
         y = -boost::math::expm1(boost::math::log1p(-q, pol) / a, pol);
      }
      if(invert)
         std::swap(x, y);
      if(py)
         *py = y;
      return x;
   }
   else if(a + b > 5)
   {
      //
      // When a+b is large then we can use one of Prof Temme's
      // asymptotic expansions, begin by swapping things around
      // so that p < 0.5, we do this to avoid cancellations errors
      // when p is large.
      //
      if(p > 0.5)
      {
         std::swap(a, b);
         std::swap(p, q);
         invert = !invert;
      }
      T minv = (std::min)(a, b);
      T maxv = (std::max)(a, b);
      if((sqrt(minv) > (maxv - minv)) && (minv > 5))
      {
         //
         // When a and b differ by a small amount
         // the curve is quite symmetrical and we can use an error
         // function to approximate the inverse. This is the cheapest
         // of the three Temme expansions, and the calculated value
         // for x will never be much larger than p, so we don't have
         // to worry about cancellation as long as p is small.
         //
         x = temme_method_1_ibeta_inverse(a, b, p, pol);
         y = 1 - x;
      }
      else
      {
         T r = a + b;
         T theta = asin(sqrt(a / r));
         T lambda = minv / r;
         if((lambda >= 0.2) && (lambda <= 0.8) && (r >= 10))
         {
            //
            // The second error function case is the next cheapest
            // to use, it brakes down when the result is likely to be
            // very small, if a+b is also small, but we can use a
            // cheaper expansion there in any case.  As before x won't
            // be much larger than p, so as long as p is small we should
            // be free of cancellation error.
            //
            T ppa = pow(p, 1/a);
            if((ppa < 0.0025) && (a + b < 200))
            {
               x = ppa * pow(a * boost::math::beta(a, b, pol), 1/a);
            }
            else
               x = temme_method_2_ibeta_inverse(a, b, p, r, theta, pol);
            y = 1 - x;
         }
         else
         {
            //
            // If we get here then a and b are very different in magnitude
            // and we need to use the third of Temme's methods which
            // involves inverting the incomplete gamma.  This is much more
            // expensive than the other methods.  We also can only use this
            // method when a > b, which can lead to cancellation errors
            // if we really want y (as we will when x is close to 1), so
            // a different expansion is used in that case.
            //
            if(a < b)
            {
               std::swap(a, b);
               std::swap(p, q);
               invert = !invert;
            }
            //
            // Try and compute the easy way first:
            //
            T bet = 0;
            if(b < 2)
               bet = boost::math::beta(a, b, pol);
            if(bet != 0)
            {
               y = pow(b * q * bet, 1/b);
               x = 1 - y;
            }
            else 
               y = 1;
            if(y > 1e-5)
            {
               x = temme_method_3_ibeta_inverse(a, b, p, q, pol);
               y = 1 - x;
            }
         }
      }
   }
   else if((a < 1) && (b < 1))
   {
      //
      // Both a and b less than 1,
      // there is a point of inflection at xs:
      //
      T xs = (1 - a) / (2 - a - b);
      //
      // Now we need to ensure that we start our iteration from the
      // right side of the inflection point:
      //
      T fs = boost::math::ibeta(a, b, xs, pol) - p;
      if(fabs(fs) / p < tools::epsilon<T>() * 3)
      {
         // The result is at the point of inflection, best just return it:
         *py = invert ? xs : 1 - xs;
         return invert ? 1-xs : xs;
      }
      if(fs < 0)
      {
         std::swap(a, b);
         std::swap(p, q);
         invert = !invert;
         xs = 1 - xs;
      }
      T xg = pow(a * p * boost::math::beta(a, b, pol), 1/a);
      x = xg / (1 + xg);
      y = 1 / (1 + xg);
      //
      // And finally we know that our result is below the inflection
      // point, so set an upper limit on our search:
      //
      if(x > xs)
         x = xs;
      upper = xs;
   }
   else if((a > 1) && (b > 1))
   {
      //
      // Small a and b, both greater than 1,
      // there is a point of inflection at xs,
      // and it's complement is xs2, we must always
      // start our iteration from the right side of the
      // point of inflection.
      //
      T xs = (a - 1) / (a + b - 2);
      T xs2 = (b - 1) / (a + b - 2);
      T ps = boost::math::ibeta(a, b, xs, pol) - p;

      if(ps < 0)
      {
         std::swap(a, b);
         std::swap(p, q);
         std::swap(xs, xs2);
         invert = !invert;
      }
      //
      // Estimate x and y, using expm1 to get a good estimate
      // for y when it's very small:
      //
      T lx = log(p * a * boost::math::beta(a, b, pol)) / a;
      x = exp(lx);
      y = x < 0.9 ? T(1 - x) : (T)(-boost::math::expm1(lx, pol));

      if((b < a) && (x < 0.2))
      {
         //
         // Under a limited range of circumstances we can improve
         // our estimate for x, frankly it's clear if this has much effect!
         //
         T ap1 = a - 1;
         T bm1 = b - 1;
         T a_2 = a * a;
         T a_3 = a * a_2;
         T b_2 = b * b;
         T terms[5] = { 0, 1 };
         terms[2] = bm1 / ap1;
         ap1 *= ap1;
         terms[3] = bm1 * (3 * a * b + 5 * b + a_2 - a - 4) / (2 * (a + 2) * ap1);
         ap1 *= (a + 1);
         terms[4] = bm1 * (33 * a * b_2 + 31 * b_2 + 8 * a_2 * b_2 - 30 * a * b - 47 * b + 11 * a_2 * b + 6 * a_3 * b + 18 + 4 * a - a_3 + a_2 * a_2 - 10 * a_2)
                    / (3 * (a + 3) * (a + 2) * ap1);
         x = tools::evaluate_polynomial(terms, x, 5);
      }
      //
      // And finally we know that our result is below the inflection
      // point, so set an upper limit on our search:
      //
      if(x > xs)
         x = xs;
      upper = xs;
   }
   else /*if((a <= 1) != (b <= 1))*/
   {
      //
      // If all else fails we get here, only one of a and b
      // is above 1, and a+b is small.  Start by swapping
      // things around so that we have a concave curve with b > a
      // and no points of inflection in [0,1].  As long as we expect
      // x to be small then we can use the simple (and cheap) power
      // term to estimate x, but when we expect x to be large then
      // this greatly underestimates x and leaves us trying to
      // iterate "round the corner" which may take almost forever...
      //
      // We could use Temme's inverse gamma function case in that case,
      // this works really rather well (albeit expensively) even though
      // strictly speaking we're outside it's defined range.
      //
      // However it's expensive to compute, and an alternative approach
      // which models the curve as a distorted quarter circle is much
      // cheaper to compute, and still keeps the number of iterations
      // required down to a reasonable level.  With thanks to Prof Temme
      // for this suggestion.
      //
      if(b < a)
      {
         std::swap(a, b);
         std::swap(p, q);
         invert = !invert;
      }
      if(pow(p, 1/a) < 0.5)
      {
         x = pow(p * a * boost::math::beta(a, b, pol), 1 / a);
         if(x == 0)
            x = boost::math::tools::min_value<T>();
         y = 1 - x;
      }
      else /*if(pow(q, 1/b) < 0.1)*/
      {
         // model a distorted quarter circle:
         y = pow(1 - pow(p, b * boost::math::beta(a, b, pol)), 1/b);
         if(y == 0)
            y = boost::math::tools::min_value<T>();
         x = 1 - y;
      }
   }

   //
   // Now we have a guess for x (and for y) we can set things up for
   // iteration.  If x > 0.5 it pays to swap things round:
   //
   if(x > 0.5)
   {
      std::swap(a, b);
      std::swap(p, q);
      std::swap(x, y);
      invert = !invert;
      T l = 1 - upper;
      T u = 1 - lower;
      lower = l;
      upper = u;
   }
   //
   // lower bound for our search:
   //
   // We're not interested in denormalised answers as these tend to
   // these tend to take up lots of iterations, given that we can't get
   // accurate derivatives in this area (they tend to be infinite).
   //
   if(lower == 0)
   {
      if(invert && (py == 0))
      {
         //
         // We're not interested in answers smaller than machine epsilon:
         //
         lower = boost::math::tools::epsilon<T>();
         if(x < lower)
            x = lower;
      }
      else
         lower = boost::math::tools::min_value<T>();
      if(x < lower)
         x = lower;
   }
   //
   // Figure out how many digits to iterate towards:
   //
   int digits = boost::math::policies::digits<T, Policy>() / 2;
   if((x < 1e-50) && ((a < 1) || (b < 1)))
   {
      //
      // If we're in a region where the first derivative is very
      // large, then we have to take care that the root-finder
      // doesn't terminate prematurely.  We'll bump the precision
      // up to avoid this, but we have to take care not to set the
      // precision too high or the last few iterations will just
      // thrash around and convergence may be slow in this case.
      // Try 3/4 of machine epsilon:
      //
      digits *= 3;  
      digits /= 2;
   }
   //
   // Now iterate, we can use either p or q as the target here
   // depending on which is smaller:
   //
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   x = boost::math::tools::halley_iterate(
      boost::math::detail::ibeta_roots<T, Policy>(a, b, (p < q ? p : q), (p < q ? false : true)), x, lower, upper, digits, max_iter);
   policies::check_root_iterations<T>("boost::math::ibeta<%1%>(%1%, %1%, %1%)", max_iter, pol);
   //
   // We don't really want these asserts here, but they are useful for sanity
   // checking that we have the limits right, uncomment if you suspect bugs *only*.
   //
   //BOOST_ASSERT(x != upper);
   //BOOST_ASSERT((x != lower) || (x == boost::math::tools::min_value<T>()) || (x == boost::math::tools::epsilon<T>()));
   //
   // Tidy up, if we "lower" was too high then zero is the best answer we have:
   //
   if(x == lower)
      x = 0;
   if(py)
      *py = invert ? x : 1 - x;
   return invert ? 1-x : x;
}

} // namespace detail

template <class T1, class T2, class T3, class T4, class Policy>
inline typename tools::promote_args<T1, T2, T3, T4>::type  
   ibeta_inv(T1 a, T2 b, T3 p, T4* py, const Policy& pol)
{
   static const char* function = "boost::math::ibeta_inv<%1%>(%1%,%1%,%1%)";
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T1, T2, T3, T4>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   if(a <= 0)
      return policies::raise_domain_error<result_type>(function, "The argument a to the incomplete beta function inverse must be greater than zero (got a=%1%).", a, pol);
   if(b <= 0)
      return policies::raise_domain_error<result_type>(function, "The argument b to the incomplete beta function inverse must be greater than zero (got b=%1%).", b, pol);
   if((p < 0) || (p > 1))
      return policies::raise_domain_error<result_type>(function, "Argument p outside the range [0,1] in the incomplete beta function inverse (got p=%1%).", p, pol);

   value_type rx, ry;

   rx = detail::ibeta_inv_imp(
         static_cast<value_type>(a),
         static_cast<value_type>(b),
         static_cast<value_type>(p),
         static_cast<value_type>(1 - p),
         forwarding_policy(), &ry);

   if(py) *py = policies::checked_narrowing_cast<T4, forwarding_policy>(ry, function);
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(rx, function);
}

template <class T1, class T2, class T3, class T4>
inline typename tools::promote_args<T1, T2, T3, T4>::type  
   ibeta_inv(T1 a, T2 b, T3 p, T4* py)
{
   return ibeta_inv(a, b, p, py, policies::policy<>());
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   ibeta_inv(T1 a, T2 b, T3 p)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ibeta_inv(a, b, p, static_cast<result_type*>(0), policies::policy<>());
}

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type 
   ibeta_inv(T1 a, T2 b, T3 p, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ibeta_inv(a, b, p, static_cast<result_type*>(0), pol);
}

template <class T1, class T2, class T3, class T4, class Policy>
inline typename tools::promote_args<T1, T2, T3, T4>::type 
   ibetac_inv(T1 a, T2 b, T3 q, T4* py, const Policy& pol)
{
   static const char* function = "boost::math::ibetac_inv<%1%>(%1%,%1%,%1%)";
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T1, T2, T3, T4>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   if(a <= 0)
      return policies::raise_domain_error<result_type>(function, "The argument a to the incomplete beta function inverse must be greater than zero (got a=%1%).", a, pol);
   if(b <= 0)
      return policies::raise_domain_error<result_type>(function, "The argument b to the incomplete beta function inverse must be greater than zero (got b=%1%).", b, pol);
   if((q < 0) || (q > 1))
      return policies::raise_domain_error<result_type>(function, "Argument q outside the range [0,1] in the incomplete beta function inverse (got q=%1%).", q, pol);

   value_type rx, ry;

   rx = detail::ibeta_inv_imp(
         static_cast<value_type>(a),
         static_cast<value_type>(b),
         static_cast<value_type>(1 - q),
         static_cast<value_type>(q),
         forwarding_policy(), &ry);

   if(py) *py = policies::checked_narrowing_cast<T4, forwarding_policy>(ry, function);
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(rx, function);
}

template <class T1, class T2, class T3, class T4>
inline typename tools::promote_args<T1, T2, T3, T4>::type 
   ibetac_inv(T1 a, T2 b, T3 q, T4* py)
{
   return ibetac_inv(a, b, q, py, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
   ibetac_inv(RT1 a, RT2 b, RT3 q)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   return ibetac_inv(a, b, q, static_cast<result_type*>(0), policies::policy<>());
}

template <class RT1, class RT2, class RT3, class Policy>
inline typename tools::promote_args<RT1, RT2, RT3>::type
   ibetac_inv(RT1 a, RT2 b, RT3 q, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   return ibetac_inv(a, b, q, static_cast<result_type*>(0), pol);
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_FUNCTIONS_IGAMMA_INVERSE_HPP





/* ibeta_inverse.hpp
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
*/