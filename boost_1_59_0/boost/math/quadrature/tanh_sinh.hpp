// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 * This class performs tanh-sinh quadrature on the real line.
 * Tanh-sinh quadrature is exponentially convergent for integrands in Hardy spaces,
 * (see https://en.wikipedia.org/wiki/Hardy_space for a formal definition), and is optimal for a random function from that class.
 *
 * The tanh-sinh quadrature is one of a class of so called "double exponential quadratures"-there is a large family of them,
 * but this one seems to be the most commonly used.
 *
 * As always, there are caveats: For instance, if the function you want to integrate is not holomorphic on the unit disk,
 * then the rapid convergence will be spoiled. In this case, a more appropriate quadrature is (say) Romberg, which does not
 * require the function to be holomorphic, only differentiable up to some order.
 *
 * In addition, if you are integrating a periodic function over a period, the trapezoidal rule is better.
 *
 * References:
 *
 * 1) Mori, Masatake. "Quadrature formulas obtained by variable transformation and the DE-rule." Journal of Computational and Applied Mathematics 12 (1985): 119-130.
 * 2) Bailey, David H., Karthik Jeyabalan, and Xiaoye S. Li. "A comparison of three high-precision quadrature schemes." Experimental Mathematics 14.3 (2005): 317-329.
 * 3) Press, William H., et al. "Numerical recipes third edition: the art of scientific computing." Cambridge University Press 32 (2007): 10013-2473.
 *
 */

#ifndef BOOST_MATH_QUADRATURE_TANH_SINH_HPP
#define BOOST_MATH_QUADRATURE_TANH_SINH_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <boost/math/quadrature/detail/tanh_sinh_detail.hpp>

namespace boost{ namespace math{ namespace quadrature {

template<class Real, class Policy = policies::policy<> >
class tanh_sinh
{
public:
    tanh_sinh(size_t max_refinements = 15, const Real& min_complement = tools::min_value<Real>() * 4)
    : m_imp(std::make_shared<detail::tanh_sinh_detail<Real, Policy>>(max_refinements, min_complement)) {}

    template<class F>
    auto integrate(const F f, Real a, Real b, Real tolerance = tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr) ->decltype(std::declval<F>()(std::declval<Real>())) const;
    template<class F>
    auto integrate(const F f, Real a, Real b, Real tolerance = tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr) ->decltype(std::declval<F>()(std::declval<Real>(), std::declval<Real>())) const;

    template<class F>
    auto integrate(const F f, Real tolerance = tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr) ->decltype(std::declval<F>()(std::declval<Real>())) const;
    template<class F>
    auto integrate(const F f, Real tolerance = tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr) ->decltype(std::declval<F>()(std::declval<Real>(), std::declval<Real>())) const;

private:
    std::shared_ptr<detail::tanh_sinh_detail<Real, Policy>> m_imp;
};

template<class Real, class Policy>
template<class F>
auto tanh_sinh<Real, Policy>::integrate(const F f, Real a, Real b, Real tolerance, Real* error, Real* L1, std::size_t* levels) ->decltype(std::declval<F>()(std::declval<Real>())) const
{
    BOOST_MATH_STD_USING
    using boost::math::constants::half;
    using boost::math::quadrature::detail::tanh_sinh_detail;

    static const char* function = "tanh_sinh<%1%>::integrate";

    typedef decltype(std::declval<F>()(std::declval<Real>())) result_type;
    static_assert(!std::is_integral<result_type>::value,
                  "The return type cannot be integral, it must be either a real or complex floating point type.");
    if (!(boost::math::isnan)(a) && !(boost::math::isnan)(b))
    {

       // Infinite limits:
       if ((a <= -tools::max_value<Real>()) && (b >= tools::max_value<Real>()))
       {
          auto u = [&](const Real& t, const Real& tc)->result_type
          {
             Real t_sq = t*t;
             Real inv;
             if (t > 0.5f)
                inv = 1 / ((2 - tc) * tc);
             else if(t < -0.5)
                inv = 1 / ((2 + tc) * -tc);
             else
                inv = 1 / (1 - t_sq);
             return f(t*inv)*(1 + t_sq)*inv*inv;
          };
          Real limit = sqrt(tools::min_value<Real>()) * 4;
          return m_imp->integrate(u, error, L1, function, limit, limit, tolerance, levels);
       }

       // Right limit is infinite:
       if ((boost::math::isfinite)(a) && (b >= tools::max_value<Real>()))
       {
          auto u = [&](const Real& t, const Real& tc)->result_type
          {
             Real z, arg;
             if (t > -0.5f)
                z = 1 / (t + 1);
             else
                z = -1 / tc;
             if (t < 0.5)
                arg = 2 * z + a - 1;
             else
                arg = a + tc / (2 - tc);
             return f(arg)*z*z;
          };
          Real left_limit = sqrt(tools::min_value<Real>()) * 4;
          result_type Q = Real(2) * m_imp->integrate(u, error, L1, function, left_limit, tools::min_value<Real>(), tolerance, levels);
          if (L1)
          {
             *L1 *= 2;
          }
          if (error)
          {
             *error *= 2;
          }

          return Q;
       }

       if ((boost::math::isfinite)(b) && (a <= -tools::max_value<Real>()))
       {
          auto v = [&](const Real& t, const Real& tc)->result_type
          {
             Real z;
             if (t > -0.5)
                z = 1 / (t + 1);
             else
                z = -1 / tc;
             Real arg;
             if (t < 0.5)
                arg = 2 * z - 1;
             else
                arg = tc / (2 - tc);
             return f(b - arg) * z * z;
          };

          Real left_limit = sqrt(tools::min_value<Real>()) * 4;
          result_type Q = Real(2) * m_imp->integrate(v, error, L1, function, left_limit, tools::min_value<Real>(), tolerance, levels);
          if (L1)
          {
             *L1 *= 2;
          }
          if (error)
          {
             *error *= 2;
          }
          return Q;
       }

       if ((boost::math::isfinite)(a) && (boost::math::isfinite)(b))
       {
          if (a == b)
          {
             return result_type(0);
          }
          if (b < a)
          {
             return -this->integrate(f, b, a, tolerance, error, L1, levels);
          }
          Real avg = (a + b)*half<Real>();
          Real diff = (b - a)*half<Real>();
          Real avg_over_diff_m1 = a / diff;
          Real avg_over_diff_p1 = b / diff;
          bool have_small_left = fabs(a) < 0.5f;
          bool have_small_right = fabs(b) < 0.5f;
          Real left_min_complement = float_next(avg_over_diff_m1) - avg_over_diff_m1;
          Real min_complement_limit = (std::max)(tools::min_value<Real>(), Real(tools::min_value<Real>() / diff));
          if (left_min_complement < min_complement_limit)
             left_min_complement = min_complement_limit;
          Real right_min_complement = avg_over_diff_p1 - float_prior(avg_over_diff_p1);
          if (right_min_complement < min_complement_limit)
             right_min_complement = min_complement_limit;
          //
          // These asserts will fail only if rounding errors on
          // type Real have accumulated so much error that it's
          // broken our internal logic.  Should that prove to be
          // a persistent issue, we might need to add a bit of fudge
          // factor to move left_min_complement and right_min_complement
          // further from the end points of the range.
          //
          BOOST_MATH_ASSERT((left_min_complement * diff + a) > a);
          BOOST_MATH_ASSERT((b - right_min_complement * diff) < b);
          auto u = [&](Real z, Real zc)->result_type
          {
             Real position;
             if (z < -0.5)
             {
                if(have_small_left)
                  return f(diff * (avg_over_diff_m1 - zc));
                position = a - diff * zc;
             }
             else if (z > 0.5)
             {
                if(have_small_right)
                  return f(diff * (avg_over_diff_p1 - zc));
                position = b - diff * zc;
             }
             else
                position = avg + diff*z;
             BOOST_MATH_ASSERT(position != a);
             BOOST_MATH_ASSERT(position != b);
             return f(position);
          };
          result_type Q = diff*m_imp->integrate(u, error, L1, function, left_min_complement, right_min_complement, tolerance, levels);

          if (L1)
          {
             *L1 *= diff;
          }
          if (error)
          {
             *error *= diff;
          }
          return Q;
       }
    }
    return policies::raise_domain_error(function, "The domain of integration is not sensible; please check the bounds.", a, Policy());
}

template<class Real, class Policy>
template<class F>
auto tanh_sinh<Real, Policy>::integrate(const F f, Real a, Real b, Real tolerance, Real* error, Real* L1, std::size_t* levels) ->decltype(std::declval<F>()(std::declval<Real>(), std::declval<Real>())) const
{
   BOOST_MATH_STD_USING
      using boost::math::constants::half;
   using boost::math::quadrature::detail::tanh_sinh_detail;

   static const char* function = "tanh_sinh<%1%>::integrate";

   if ((boost::math::isfinite)(a) && (boost::math::isfinite)(b))
   {
      if (b <= a)
      {
         return policies::raise_domain_error(function, "Arguments to integrate are in wrong order; integration over [a,b] must have b > a.", a, Policy());
      }
      auto u = [&](Real z, Real zc)->Real
      {
         if (z < 0)
            return f((a - b) * zc / 2 + a, (b - a) * zc / 2);
         else
            return f((a - b) * zc / 2 + b, (b - a) * zc / 2);
      };
      Real diff = (b - a)*half<Real>();
      Real left_min_complement = tools::min_value<Real>() * 4;
      Real right_min_complement = tools::min_value<Real>() * 4;
      Real Q = diff*m_imp->integrate(u, error, L1, function, left_min_complement, right_min_complement, tolerance, levels);

      if (L1)
      {
         *L1 *= diff;
      }
      if (error)
      {
         *error *= diff;
      }
      return Q;
   }
   return policies::raise_domain_error(function, "The domain of integration is not sensible; please check the bounds.", a, Policy());
}

template<class Real, class Policy>
template<class F>
auto tanh_sinh<Real, Policy>::integrate(const F f, Real tolerance, Real* error, Real* L1, std::size_t* levels) ->decltype(std::declval<F>()(std::declval<Real>())) const
{
   using boost::math::quadrature::detail::tanh_sinh_detail;
   static const char* function = "tanh_sinh<%1%>::integrate";
   Real min_complement = tools::epsilon<Real>();
   return m_imp->integrate([&](const Real& arg, const Real&) { return f(arg); }, error, L1, function, min_complement, min_complement, tolerance, levels);
}

template<class Real, class Policy>
template<class F>
auto tanh_sinh<Real, Policy>::integrate(const F f, Real tolerance, Real* error, Real* L1, std::size_t* levels) ->decltype(std::declval<F>()(std::declval<Real>(), std::declval<Real>())) const
{
   using boost::math::quadrature::detail::tanh_sinh_detail;
   static const char* function = "tanh_sinh<%1%>::integrate";
   Real min_complement = tools::min_value<Real>() * 4;
   return m_imp->integrate(f, error, L1, function, min_complement, min_complement, tolerance, levels);
}

}
}
}
#endif

/* tanh_sinh.hpp
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
*/