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
      Real h = pow(11.25*eps, static_cast<Real>(1) / static_cast<Real>(5));
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
      Real h = pow(eps / 168, static_cast<Real>(1) / static_cast<Real>(7));
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
      Real h = pow(551.25*eps, static_cast<Real>(1) / static_cast<Real>(9));
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
      static_assert(sizeof(Real) == 0, "Finite difference not implemented for this order: try 1, 2, 4, 6 or 8");
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