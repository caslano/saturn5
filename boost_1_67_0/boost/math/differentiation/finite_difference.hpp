//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DIFFERENTIATION_FINITE_DIFFERENCE_HPP
#define BOOST_MATH_DIFFERENTIATION_FINITE_DIFFERENCE_HPP

/*
 * Performs numerical differentiation by finite-differences.
 *
 * All numerical differentiation using finite-differences are ill-conditioned, and these routines are no exception.
 * A simple argument demonstrates that the error is unbounded as h->0.
 * Take the one sides finite difference formula f'(x) = (f(x+h)-f(x))/h.
 * The evaluation of f induces an error as well as the error from the finite-difference approximation, giving
 * |f'(x) - (f(x+h) -f(x))/h| < h|f''(x)|/2 + (|f(x)|+|f(x+h)|)eps/h =: g(h), where eps is the unit roundoff for the type.
 * It is reasonable to choose h in a way that minimizes the maximum error bound g(h).
 * The value of h that minimizes g is h = sqrt(2eps(|f(x)| + |f(x+h)|)/|f''(x)|), and for this value of h the error bound is
 * sqrt(2eps(|f(x+h) +f(x)||f''(x)|)).
 * In fact it is not necessary to compute the ratio (|f(x+h)| + |f(x)|)/|f''(x)|; the error bound of ~\sqrt{\epsilon} still holds if we set it to one.
 *
 *
 * For more details on this method of analysis, see
 *
 * http://www.uio.no/studier/emner/matnat/math/MAT-INF1100/h08/kompendiet/diffint.pdf
 * http://web.archive.org/web/20150420195907/http://www.uio.no/studier/emner/matnat/math/MAT-INF1100/h08/kompendiet/diffint.pdf
 *
 *
 * It can be shown on general grounds that when choosing the optimal h, the maximum error in f'(x) is ~(|f(x)|eps)^k/k+1|f^(k-1)(x)|^1/k+1.
 * From this we can see that full precision can be recovered in the limit k->infinity.
 *
 * References:
 *
 * 1) Fornberg, Bengt. "Generation of finite difference formulas on arbitrarily spaced grids." Mathematics of computation 51.184 (1988): 699-706.
 *
 *
 * The second algorithm, the complex step derivative, is not ill-conditioned.
 * However, it requires that your function can be evaluated at complex arguments.
 * The idea is that f(x+ih) = f(x) +ihf'(x) - h^2f''(x) + ... so f'(x) \approx Im[f(x+ih)]/h.
 * No subtractive cancellation occurs. The error is ~ eps|f'(x)| + eps^2|f'''(x)|/6; hard to beat that.
 *
 * References:
 *
 * 1) Squire, William, and George Trapp. "Using complex variables to estimate derivatives of real functions." Siam Review 40.1 (1998): 110-112.
 */

#include <complex>
#include <boost/math/special_functions/next.hpp>

namespace boost{ namespace math{ namespace differentiation {

namespace detail {
    template<class Real>
    Real make_xph_representable(Real x, Real h)
    {
        using std::numeric_limits;
        // Redefine h so that x + h is representable. Not using this trick leads to large error.
        // The compiler flag -ffast-math evaporates these operations . . .
        Real temp = x + h;
        h = temp - x;
        // Handle the case x + h == x:
        if (h == 0)
        {
            h = boost::math::nextafter(x, (numeric_limits<Real>::max)()) - x;
        }
        return h;
    }
}

template<class F, class Real>
Real complex_step_derivative(const F f, Real x)
{
    // Is it really this easy? Yes.
    // Note that some authors recommend taking the stepsize h to be smaller than epsilon(), some recommending use of the min().
    // This idea was tested over a few billion test cases and found the make the error *much* worse.
    // Even 2eps and eps/2 made the error worse, which was surprising.
    using std::complex;
    using std::numeric_limits;
    constexpr const Real step = (numeric_limits<Real>::epsilon)();
    constexpr const Real inv_step = 1/(numeric_limits<Real>::epsilon)();
    return f(complex<Real>(x, step)).imag()*inv_step;
}

namespace detail {

   template <unsigned>
   struct fd_tag {};

   template<class F, class Real>
   Real finite_difference_derivative(const F f, Real x, Real* error, const fd_tag<1>&)
   {
      using std::sqrt;
      using std::pow;
      using std::abs;
      using std::numeric_limits;

      const Real eps = (numeric_limits<Real>::epsilon)();
      // Error bound ~eps^1/2
      // Note that this estimate of h differs from the best estimate by a factor of sqrt((|f(x)| + |f(x+h)|)/|f''(x)|).
      // Since this factor is invariant under the scaling f -> kf, then we are somewhat justified in approximating it by 1.
      // This approximation will get better as we move to higher orders of accuracy.
      Real h = 2 * sqrt(eps);
      h = detail::make_xph_representable(x, h);

      Real yh = f(x + h);
      Real y0 = f(x);
      Real diff = yh - y0;
      if (error)
      {
         Real ym = f(x - h);
         Real ypph = abs(yh - 2 * y0 + ym) / h;
         // h*|f''(x)|*0.5 + (|f(x+h)+|f(x)|)*eps/h
         *error = ypph / 2 + (abs(yh) + abs(y0))*eps / h;
      }
      return diff / h;
   }

   template<class F, class Real>
   Real finite_difference_derivative(const F f, Real x, Real* error, const fd_tag<2>&)
   {
      using std::sqrt;
      using std::pow;
      using std::abs;
      using std::numeric_limits;

      const Real eps = (numeric_limits<Real>::epsilon)();
      // Error bound ~eps^2/3
      // See the previous discussion to understand determination of h and the error bound.
      // Series[(f[x+h] - f[x-h])/(2*h), {h, 0, 4}]
      Real h = pow(3 * eps, static_cast<Real>(1) / static_cast<Real>(3));
      h = detail::make_xph_representable(x, h);

      Real yh = f(x + h);
      Real ymh = f(x - h);
      Real diff = yh - ymh;
      if (error)
      {
         Real yth = f(x + 2 * h);
         Real ymth = f(x - 2 * h);
         *error = eps * (abs(yh) + abs(ymh)) / (2 * h) + abs((yth - ymth) / 2 - diff) / (6 * h);
      }

      return diff / (2 * h);
   }

   template<class F, class Real>
   Real finite_difference_derivative(const F f, Real x, Real* error, const fd_tag<4>&)
   {
      using std::sqrt;
      using std::pow;
      using std::abs;
      using std::numeric_limits;

      const Real eps = (numeric_limits<Real>::epsilon)();
      // Error bound ~eps^4/5
      Real h = pow(11.25*eps, (Real)1 / (Real)5);
      h = detail::make_xph_representable(x, h);
      Real ymth = f(x - 2 * h);
      Real yth = f(x + 2 * h);
      Real yh = f(x + h);
      Real ymh = f(x - h);
      Real y2 = ymth - yth;
      Real y1 = yh - ymh;
      if (error)
      {
         // Mathematica code to extract the remainder:
         // Series[(f[x-2*h]+ 8*f[x+h] - 8*f[x-h] - f[x+2*h])/(12*h), {h, 0, 7}]
         Real y_three_h = f(x + 3 * h);
         Real y_m_three_h = f(x - 3 * h);
         // Error from fifth derivative:
         *error = abs((y_three_h - y_m_three_h) / 2 + 2 * (ymth - yth) + 5 * (yh - ymh) / 2) / (30 * h);
         // Error from function evaluation:
         *error += eps * (abs(yth) + abs(ymth) + 8 * (abs(ymh) + abs(yh))) / (12 * h);
      }
      return (y2 + 8 * y1) / (12 * h);
   }

   template<class F, class Real>
   Real finite_difference_derivative(const F f, Real x, Real* error, const fd_tag<6>&)
   {
      using std::sqrt;
      using std::pow;
      using std::abs;
      using std::numeric_limits;

      const Real eps = (numeric_limits<Real>::epsilon)();
      // Error bound ~eps^6/7
      // Error: h^6f^(7)(x)/140 + 5|f(x)|eps/h
      Real h = pow(eps / 168, (Real)1 / (Real)7);
      h = detail::make_xph_representable(x, h);

      Real yh = f(x + h);
      Real ymh = f(x - h);
      Real y1 = yh - ymh;
      Real y2 = f(x - 2 * h) - f(x + 2 * h);
      Real y3 = f(x + 3 * h) - f(x - 3 * h);

      if (error)
      {
         // Mathematica code to generate fd scheme for 7th derivative:
         // Sum[(-1)^i*Binomial[7, i]*(f[x+(3-i)*h] + f[x+(4-i)*h])/2, {i, 0, 7}]
         // Mathematica to demonstrate that this is a finite difference formula for 7th derivative:
         // Series[(f[x+4*h]-f[x-4*h] + 6*(f[x-3*h] - f[x+3*h]) + 14*(f[x-h] - f[x+h] + f[x+2*h] - f[x-2*h]))/2, {h, 0, 15}]
         Real y7 = (f(x + 4 * h) - f(x - 4 * h) - 6 * y3 - 14 * y1 - 14 * y2) / 2;
         *error = abs(y7) / (140 * h) + 5 * (abs(yh) + abs(ymh))*eps / h;
      }
      return (y3 + 9 * y2 + 45 * y1) / (60 * h);
   }

   template<class F, class Real>
   Real finite_difference_derivative(const F f, Real x, Real* error, const fd_tag<8>&)
   {
      using std::sqrt;
      using std::pow;
      using std::abs;
      using std::numeric_limits;

      const Real eps = (numeric_limits<Real>::epsilon)();
      // Error bound ~eps^8/9.
      // In double precision, we only expect to lose two digits of precision while using this formula, at the cost of 8 function evaluations.
      // Error: h^8|f^(9)(x)|/630 + 7|f(x)|eps/h assuming 7 unstabilized additions.
      // Mathematica code to get the error:
      // Series[(f[x+h]-f[x-h])*(4/5) + (1/5)*(f[x-2*h] - f[x+2*h]) + (4/105)*(f[x+3*h] - f[x-3*h]) + (1/280)*(f[x-4*h] - f[x+4*h]), {h, 0, 9}]
      // If we used Kahan summation, we could get the max error down to h^8|f^(9)(x)|/630 + |f(x)|eps/h.
      Real h = pow(551.25*eps, (Real)1 / (Real)9);
      h = detail::make_xph_representable(x, h);

      Real yh = f(x + h);
      Real ymh = f(x - h);
      Real y1 = yh - ymh;
      Real y2 = f(x - 2 * h) - f(x + 2 * h);
      Real y3 = f(x + 3 * h) - f(x - 3 * h);
      Real y4 = f(x - 4 * h) - f(x + 4 * h);

      Real tmp1 = 3 * y4 / 8 + 4 * y3;
      Real tmp2 = 21 * y2 + 84 * y1;

      if (error)
      {
         // Mathematica code to generate fd scheme for 7th derivative:
         // Sum[(-1)^i*Binomial[9, i]*(f[x+(4-i)*h] + f[x+(5-i)*h])/2, {i, 0, 9}]
         // Mathematica to demonstrate that this is a finite difference formula for 7th derivative:
         // Series[(f[x+5*h]-f[x- 5*h])/2 + 4*(f[x-4*h] - f[x+4*h]) + 27*(f[x+3*h] - f[x-3*h])/2 + 24*(f[x-2*h]  - f[x+2*h]) + 21*(f[x+h] - f[x-h]), {h, 0, 15}]
         Real f9 = (f(x + 5 * h) - f(x - 5 * h)) / 2 + 4 * y4 + 27 * y3 / 2 + 24 * y2 + 21 * y1;
         *error = abs(f9) / (630 * h) + 7 * (abs(yh) + abs(ymh))*eps / h;
      }
      return (tmp1 + tmp2) / (105 * h);
   }

   template<class F, class Real, class tag>
   Real finite_difference_derivative(const F, Real, Real*, const tag&)
   {
      // Always fails, but condition is template-arg-dependent so only evaluated if we get instantiated.
      BOOST_STATIC_ASSERT_MSG(sizeof(Real) == 0, "Finite difference not implemented for this order: try 1, 2, 4, 6 or 8");
   }

}

template<class F, class Real, size_t order=6>
inline Real finite_difference_derivative(const F f, Real x, Real* error = nullptr)
{
   return detail::finite_difference_derivative(f, x, error, detail::fd_tag<order>());
}

}}}  // namespaces
#endif

/* finite_difference.hpp
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
*/