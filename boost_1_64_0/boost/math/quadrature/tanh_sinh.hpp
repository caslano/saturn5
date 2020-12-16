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
          BOOST_ASSERT((left_min_complement * diff + a) > a);
          BOOST_ASSERT((b - right_min_complement * diff) < b);
          auto u = [&](Real z, Real zc)->result_type
          { 
             Real position;
             if (z < -0.5)
             {
                if(have_small_left)
                  return f(diff * (avg_over_diff_m1 - zc));
                position = a - diff * zc;
             }
             if (z > 0.5)
             {
                if(have_small_right)
                  return f(diff * (avg_over_diff_p1 - zc));
                position = b - diff * zc;
             }
             else
                position = avg + diff*z;
             BOOST_ASSERT(position != a);
             BOOST_ASSERT(position != b);
             return f(position);
          };
          result_type Q = diff*m_imp->integrate(u, error, L1, function, left_min_complement, right_min_complement, tolerance, levels);

          if (L1)
          {
             *L1 *= diff;
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
c8t8WY05YsxyGovJHndeYz55/1sQseST83/GIuKjlDGX7A+VNxZ+K+f/MFaeET2IRa7jtYw5X3A/1zcWkr3cJoh5MPdGc+iyh6/trY29K2enOxgLVklLrIuxuLzv6Qkfkm8/+BA2CFqV4/4bjphL83xjoNVuHjsBurxlnT+FXV3Z/0PMAWZBjB3BPbkA2sv985fIoxPbLUN8lziW76BBax77I+qRitfbmv+0Z/absehx1mA9enI+X8O2oJ/dXMsdYL3Z7x7kO5l9HARLxhochd8zcv4P80nM55GbnJmIQQPZt70OH3/z2DvIIwPHdx92btn/Qz0+Zg2ew64xz/cG/XKErzmJM9v1tK2c/zMWlHMtaY2F2/B8GYx5Yuw3i7GIl2POYcx9njXIAzaE53vfmEvODhaF31Ycn9uYrxizcsbiz7mfP0BuY5h9ZCz2hq/3NZFHBdn/gwbyHNAYsbTltf+xMUcfjrmVMW9x1q+9saic8+gMDabx2B7G/Plk/w+azuZ8B4KJLsMQ8xweOxqx3E1MLAA7H+cxBVq9kf0/Y86ecv4PGlxlu/mIuR7XfDHGii5fw6/E8j/EJ+8/VmA+sVttLFSW5/sVdvLeah10lrGbEbOw7eiDn1i/3fAh8x0A0///D/33LY89iTxEv3PQVK7Zl9Cno7lG1xBzRba7DXaTY/4H60O+B3sEDeT86TPYfcY+XkP7IswSZcE7B54vubF4frZLAzu5NqU3Fu7AMWc2FsnKfZAddil5LbiMuatxXxWAXWv2UcSY4wrXoyTs5LudssZ8mfh6Wgk+Gsj3v8accuapBuY7y/nWRb4v+brRyJinNY9thvhSsN+W0M8h+3+wk/cVnYwFJZbuxgL/43z7YL5NXF+/sehVZkOhgZzvHAW7HqzVeNToG2aTkVtO2f8Dk3dts4y5cnB95yHmlWy3CGNlj+wr2E1lH98iPnnf+APqIXaroJ889/xiLFaCdf4DrBxrsAl+03J8EWgq+4S70C9LWZf9xkKyfo+gbm05lhOY7wrnexZMzh9cRB4XmV1FPS5xHregyxD28TfykPcpD5HvUe6Dp+iDERmIvUIsU3hsQlbzUYx9JDMWPsD9l9qYayzXw2ksdkTO/8FOrn/vGYu8Yk1zG/P34FjyG/PuYQ0KGwu8x3YljHnkfrwMmLxfqGjMIXWrity2cB7VYfcFz1cHdrKf2NBYfDDn29SYbwXP1wLzSf+1hS7XuEY+zCd79d2MuX2sfW9jIemhAdDlErMh0GA0azASsTyW/T/kFmW7SWCFeS1MM6b/r+lM+MjB8c3FWDlrsBC9Id+vLjUWDLDfb9B/8n3j9+gNuc/+CfnK/kvYmDMda/A7dN6dmNhGzCf7Q9vQk/Xk/B/6rznb7QObzLEcRh7SG8dhJ+cnz0CD3NzPF1Dz8ez3CuwSsX430Qen2Mc99NoQ1uABdCkk+3+IRfabXkIX+U7Jkc20l329pMac0i+pjLnl3dg7xlzdmGXE2OG8zrPBh/RkLrDKsv+HsRtYg0LGgpJvcWORkjy2tLGY3EtVAPuF+6qKsfACtqsGO7nG1oZfuR9qgPjk3tELlkvO/xkLjU1CrI2xQAdmHcFWsI+uxvySby/kK+utv7H4Ztn/QyzP5fwf6laM2ViM3cs9ORGxdOH4piKPXLL/h7GiwRzEV57z+MKY96h8/2vMIe+sQ+ihvOx3OWJZz2NXgs2R73/ho6Hs/4G15vk2IOZdXKOtxjwRHrvTWPMAX+v2og9Ky/4fYmnE7BjqJu9XT0M/eTf2F7QawmMvo//kPfEN9OnJBGJ34Vd6I4758sj+H3KTa9gLzCfnFN5iDV5NRyzJexZzF75upDQ=
*/