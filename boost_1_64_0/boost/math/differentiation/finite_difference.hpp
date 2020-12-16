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
QHxFFsLzYBG8ABbDy+Ac2B/OteVXJvk1NeQ3FDmLw2B9OAKqtRphJBwOm0jcUw+uT2VsxVAPPFQqvyawHmwGG8JoGAtjYCsYC9vBlrA9bAHPUXHxmemWeT4yZy0FdiHgN1dticg1gOfDJjAJdoQXws6wBxwKe8KRsBfMh33gHJgMF8JL4Fp4KfwVHACfgQPhDjgI/hEOhnvhXHgIXgk/gkPhCTgMBrupL1gXWnINYCqMgiNhHEyH7eEUmAinwm4wG/aBObAvzIUpcDocBmfAMTAP/gzmw3Q4C2bD2XAmLISzYDGcB+fAn0t5FsMx8BY4Fq6U9FXwZ/B+OA4+D8fDzWq/x2eozB2QuSYpDp+h24O5XrgTNobvwAvgu7AX3AOT4fewP9wHU+F7cCx8H14NP4GH4FH4IfwrPAr/Bhu6GY+HafAbOB1+B2fB43AZPAG5Ls6jrkvlew88BNdIfK3EH4N/gq/CD+E2Oe5t+Ak8CL+E38Gv4Pey3x1UUY44eAy2g1b6udA67lL4KRwLj8CJsj8H/hPmwpNwlqRb9ZsaJLa9YjeeAi8nDCRdfZEGVdTvtbAnvA4OhwtgKiyHo+FCmA5L4FS4CObAxTAX3gCL4Y1wMVwKb4K3wDvhI/AB+Ch8RPJdB1fA38Bb4Usit03kdorcbngH3AvvFN/Bq2AovBs2hL+AjeFqeC58EHaGD8Gr4a9gPnwE3gSt/FdA8lf39TF4N3wc3i/pD8J18CH4JNwMt1rlg9vgMbgHtgyivcE28H3YHX4Ah8O/wjHwSzgDfgVnw3I4Bx6C8+GHcBncDh+Fb8InRe43sAw+Bz+CL8KP4ctwA3wNPgPfhJvhHvgy/BL+Hn4Lt8DjcCP8ET4HW9AeXoDxsBwmwFdhEnwNdoefwtHwczgOfiE+lhODxDZRbEVTxKdAnLSrb6VdfQ/bwB9hJ+iiXQ4G10L1+whHwWA4GYbAbFgHzoT14CwYBotgOFwIG8IbYCN4E4yA98IouA52gs/CWXAzLICvw0L4NpwPd0k5SmEM3Adj4THYHJ6ALeGPMA66udg2MBTGw/awLUyE58CusAO8EHaC/WFneDnsCjNhd1gAe8A5cAhcBK+AD8Ir4SNwGNwAh8NdMBW+C9Pg+3A0PAzHwCNwLAwOor+FdeB4WA9OgPXhRBgO02EzmAE7wEzYFU6BveBU6Wey4ACYLf1MDiyG0+D1MBfeCOfA5XAuvA9eAx+G8yHPFPUr7cUtNnFiC5gC2xHipJ9fIv38LTAWLoPxcDk8F26E58NVsC+8G6bBX0g/fw8cB++FV8H74CT4AJwB18CZEn8Q/go+BB+Bj8F18HH4BHwC/hquh+vhBjnvRvg03AR/C1+Fz8JtUr634aPwPfgYfF/O9yVcC+u7eWYg/ZSSbwJ/A7tKei+VLv12iNjAiB1Yirwf8v6gthL+hcFbYRy8DbaFvxTf2rfL++KdsA9cBYfDX8AxlhycCh+GC+W4GyB9tOqv18J74KPwZdnP9Srf/9/Bp+A/4dOwnnUdMBzyzKnreg62hi/A8+Em2A2+BAfCl+EI+Hs4GW6BU+FrcKFbygO3EX9C4k/Bt4hvhTvgNrgLvgf/CMtgKfwM7obl8B34HXwXBlv9MqwHD8AYeBC2hmXwYvgx7Cv7h0DuherHj8Ex8FuYDr+D/O6qcl0N9xKfC/fBxfA9eDP8RNZE+ALeDf8Kn4Jfwt/CE/BV+A/4Bvwe7oI/wqPQLb6dg+CPcj76SldjOApGwrEwCk6BTeA02BQWwGi4GMbAm2AsvAM2h3fBOPggbAV/DVvDF2Eb+ApsB3fD9vAQTIAfww7we3getIyhO8NYeAE8FybBTrAb7AovhJc=
*/