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
Hb+zK/9mRETuMST2ME0YfPVmixunWn0Mws3R617Nssay6QnwuEFPBxG5UHMdXXncOXW3HNzBlgqgIpioMNXqhmA94ZPD4fr6wioV4Ouq2vYfKIDoQuKOgUOMmNnVLl3TT4QReqWcDRmLBROtGO7gPwTRLgHEiVdgunUjPnocKWI5uRNg7VPCMY5823iGnlDfZscjYb33NIEW5Bfj7DR6U2ESizsQ+nfuobevHFfXI/Q3CMj71VGUS0A1/RJdxtd0L8jl3byJN9o62KUa6gfcmd/atDGYFW+hmtXrXaltjlQK1BmYRw5xG0H196plylrm2bFJhhyC3jejEVI3XxNJHpH85sHDHsVBMzbxzsyhrTbhZePN3o5TbWmIvUhih7OzciFixLjTPl31Duf97J6Q/ls0rzLha8zVzGGqey4K9XapkudpAArkeUGadLQl6+3FUIniTIQBAKVBac08TYdVXLOtVpv1OdEBH8z0x1ePbsZgIA8PrCQVep2q78OKYB1b4Lk/MlwtXFz2oOHx7IPfH48sQOXFSKSrlB31j/+KKgx3p9mPdYPt5AdspjGg2hCMtWQB3RDF4r0X55tbd46RQQ6i8PhqgQ0yHNTKTV2iQ9JutA2pyzdJWxucBzCO3FvSwS8ifTpe/Bx92CJi9gKAgvsh+UpDWaTs7zdBW4diapN3cMWH7wVHH1ViiDhguGRRscbfIV0qEB7DE1NhVB/9Q3djwW1VJEnDkIOwafRdNFfbHs8BRz62HUZ+8KTKzM16BOT+2sOkFO5QCKTfcxElkRDArXGm++OM624/sPHn81S5MxLliep2IM4jzvNcZUd3jmddbn0Mt7yZv56F2Ei54Wdu44sQl+IFNP6TGHwPYnBArBTuB9sIQeLfhnhMYGmo0Sil1v4cd1tknUqePDliAMGwyYsQPgRs/ZVGrVzqS8ai27Wi7d7IrG26l8U8BgLpLsuMJctpAym9NjdXQkTg6pbavyieMTXXPW9iRzBrycejZDyNZxnsdMVEoCYzlxrzHiGLBpIVmVBxnaeEROCgFkR59lcjvfYlTXGMCLQ83G6DrVIKqdcsynDDF9DcYcDVBSMLdep6mtjPmqxX3Gfd968c9JYQvY3TyJhj7q3U0KzMJFIaKT+vUpb0x3JJuV7gTrLTeXjnAqUsidXIfp5mJcC0f4pAenqRZSjp5WibsSTktiYrjMVrLNMBM+2pWGL7l3n9PP/kN3f7TLAQlxpDxeqYYsaBenLJzM9xRgLBlaOSGUSw4WSeJOZTHnn3rrKljz9nLEGeKEtoCzmw6++WaUMa8164vBx6p5xvN1VNgtnxICDojSoZvm3w+JqnTkWuRpByAxUK4ZInAC0oG4z5OwPMAC5rjMMkUx61+t371df3i1kmOzfKd1NiPCu1imsec65kH0h67C6BhpHTcWyBg+9Xyg+ub/RzHSQ0duedjoPC6T1c2OhKg/l2FVgbBM5mN9U9qqu9KmBOvEx+6VfEC4jIUpdbPdSL76Xa8cZLJorDZ4mJuDJX3f0hS/tFEmB6CfL056iQ2pKV3br3bS9aOAPVWeooT+vJx34O3ynrWOh87bsOvYZai6sOblakaqU1ndglUaeMLGvsSQJf7dY81x7coCH1HTE1R0t2tX1qwaYoreeYPpwnlrRqTto0u6QxoAom5p7FhuxdGKOKtAcqn/mfzbHh2smgd85PxB1xfROV8WwW15Gntsw+B0eJuUZ7JR5J4AK7cGHvTi8kpbKdziFoYpOFkpnSjDdBBvrRJWRYhejamMEnHhzRHVd4KO9nyd5Iebc8cC+GIAr9/p4RyNftjwg2hVnDepZuYAKUTmwjexAm+M8jbLQAJiym9Pwnrf9hGMqy/hKo+Js9H0ZPPYMP8rK5rOFs0B8cg8QIdMRsChykJkf2VwmZvLX2E1zeU+d2iCdMfBvE7hCVnhpBi8wL+SMkjlyvg7vpecSXWMuv6VIGBIR5SUdyrIC0hm16pJAMdxst0i2DoeJgTvvtbHqMnD2kuFpFYana0L1WsfLNo5Jovw6tWlSND2SCYGS7Wlt0m71cE04gEX+3EQt800ToWSvRpslc86okVp2OxrQVLxSOlGuGJWs8snvEZwtiECCnTQfzeCzfm49aETzv8SQGJkhJ3Oyiug/kdcmpZBaxatt9ir1hYbFUG0yWaost+3DjbygIR1EeCocOX2oIts56GrBK+HrJ5UoTUCTlQWAhAV94V5DbcH7dLF6AUt/Kq7m1cUr6J+1CEceyGyqMPrDzZ32wShSE3/Fj3USOrWchWpBjp/FeA53AInTUjudfX+he6fZCu3zfQ0yL9KksK+BL4XxlSdd2W7Wj2UxsBZ20yE28cm7qNpTj7+PiUah4ooa5uqLoRI06ZotSWtIujOh0lW3BDcPoll/GL4evR/uMoBcV40BXqyqJXtbfJwvs7K+lC7gr9TpzZMBesmQ6ipjhz6mfIHqUAIjfsBuwZELSWvXDHvHr8ETKZkv7RczifPwbe7H3Nx5AuRzdLobvE3tfu8oEsknIB20ZsQfhomYs7zpHuTcgZM6pIM/HE8DhMcYCqnOwTcMXWlVAE7sARffjG4uPy4w6ulxggMticGhnIfyQ0BZfSQQwsR2I5H93AYtbzRPUWZdSJjLpGRYYCBdc4WHkPWMsbWYyQxRbwgUxRnSkJa+9iai+fGuh1RsQiH5ZLAWbW0TM9MYOkoMXuzNMPmLxN48JiTSsBPfPey0naCF1kz+gln4u40KP3hlDMRq5ByaBiAYmJw+kHFivryxGUZz6LAFj16cnMIO2dNDUcb5cqkjaxeoMkXAc7YVYwApK0mhZKixyu8SmLF7h8gjt1ZdzqvcMN6iR9A7q5UxTgvRcTq/we2kEGD74aiFsWc5rENH10BUoedANniXmDcwSQ2C0HXgBOHQieEMr7dn4di5DZz1yhWus2SPOaGXXYRU6siWF03uYKldfgtBCas3Y3LA0CyuBKo5ufOFEDla0wNWC209VmAl6RUIWEC6IS2oQqa1C+7j4YCrhtJkr5sp/x2t78HKI6NOUAAhKCwI58Arjb0yulyth67SoZxy46NIkUWCZMUxZwdTaZoDfRrQmLMX1VpOqo4+obnsJQ8g/MfcUDMUeVWjuMkxIhuTsobZEba2H0F6/dKKKKsUaHnFUQB5e7rbKU0+wyX/edbEgt/TUF83isG/+89Pw6eHaoqRCMhqBcOu7WjVYUiNqF3kVuk3pwa2DXPM10E6YX73E+SQU5eQrOOqMZfb007YV+kM5dhTSwAN/ND+y7+5vQJraAdlmN/Oo7K/7IQpJYNUAK0dWqfpTjgYDZwuXZKXIHlx37xz3aDrcTcCtg5KYSa32kxa23iu4hwIhMKAIhCdzk99vo9Wn0fNGZ3GyH4aM4xG2MZwwth+z/bruIou0gE91ma+CbHiQz4T4wVNREY6sYMQmi123XPTlRAOek0TbOWtZtJgoQYqXV5t/fg3XzW0N07s3hyD6AeU+fjNIeDYUq3zYqOOMkrllzS3+jABEaKLVLA3I3VISm5lPicI2xKmvFWKQww0EFdVEt2yZeDT+vrDmSye3qhhQE61fh+gbKUN7LLCIG/VU23ql40utqKwdF4iTJCAy8kTSVrpdXsUxI4JdFiUCia6LQteY60CBhRTr6mJEDESYfH96Ta6Ize72DX0aIpo9qEmKhntkgqPHNL2d52otvGmafu/yZyyidaFyWhP15uH4d8+d0ZvZjNNLMrHCUuG7mtyf2ZZdL8B+vSYQm6C4YyFxPlQu4C6cmrFg0BbsbYMZJucruR2oZYFYXJyUdg0Chik0HL6lUce0vX8psvLR3sxbBTp2nTEGKZEC+70L4XEqYlOmX6EmP9+th6NEJ5r0jgMfzrk7jByxR3GpO0tfkehcDfsuvoSKQWmU1/VW8hgvzChnDaeQoc78+edrI7RdIAtflcSUJdw6u26w89PVe2oP/gS57l05km6v0z8n/08A7lQHtXEO1DZY4dNoCQH5Kk4iyrawLpIcfQHnQ6O0nYxHfXHBtysCI/xfYHpr+u+Ow0dmZdfFiIHdS7aCh5DIUv+F6kvO8VUFM4KdNhzFjGJ0TQtzQX7tifm9qY2hDPKPhob0I6y+WoruSvkX++deqRAqytGDl64RFw51uWeJuD4DWRveOCb+KUsUpa9i4NTr1uv/Aw45tOoHgACAQ0sBAID/f7LJnjmWKcG+NBAJcAOC4orU5dGmczCpqr9wMmZOj9XAqU8XZZKxhURHxLhCAIzBELeF8d1sIVGOHwdOaSTNisbRDEyQ7V837ygPDKS2mg3yCgdkirdlgUamb0CEjgfSa2uJZ066WqZGcb7pWMRnBqMsz/DnSvarD2xBJA4IAY4Uf4J5fSgTygBdPJbWFqdu4vrwVUeHElLcy9qgfGPl9oTGmbORVMg9ALQWHpZPgc8hGGN7oW5bbkHjjIVxpXLnbkVelk6Sqkb2WvKMxqyQ1WEpCH4n5zJ4gJ7awdn160S3DLtDGkPLvXTibXRtHoXy6dSJl+jRkBoJQSe4Y3FCG9cGcn+EVw6zaWFRpEDiNECyf4SIPjigAxEIcMGr7uny83hFA3XuCNuj3BQzDpz36WjCsgPslYXKlq71XkxJ3Fks6h+6/GZbHl/ggWByCLb7Ybzw6sf0mY1IIjlCODRYf4EJ4MajfI1MP01u0yRRD3XV3m+QDrGp03K9kIzvR02PZ3zRxRl0JyVYURAIBGhBzjcOII+OUO4N0kMBWNpY5RqVBiRucH1KTIyqrkgYtou6H9znkHfn2wCKtQ9+Lh8OK/gzgsU8pi1Q7lH+4sgm2oFcYXjatLmPopprJinQchP1GnpCkxopPtyahDE/Y5vhVMw2y2FzX1m0NCHsqOJQ4WDHxaUxzwaVhPBb9+90n6UgnAFLByW9jEskJn+Dq1FhwFEgn97PNWGAKgJ7p4KKLQtRE+UWywpd4Cgpg3ToN14cpRKWTHuOcSag3zAyUnT7t+l5fFkQQ0WKb5hvxfQnSvjfDm/0FfMMwVo+eGnv+Mggs+TERVtU6NM5rD6mbf/Oe8w34PBjWgxuB691VqaIJEe6LHTJy0Tdf1PTU5zYv6gUedJEJDkawEKd28J3NFW2WNtGghX13niEjS16mOVS1Gmst++p4Kn60n5Ob1Sak9RDVObJH3F0gMratSDi7Jmp6GJQ4Y8s99RFk7HZwCCzr71FFBl1bGZOZN/SBg/hEsfV5wuMqJ3kZ1/n9UUwzsxV73Xzj0Yf2J9ZcP4G+QLdA3fxCiR7gMqVx56cz0T+5HffEAI90dnRqD6r22bRN2gDwsHTN9MZ/mJL/rJUQ2mq7blYTv9p2CmVmC1gZPj9qk2DbPH2Qh4udYQ2TXXTqljIE0gb3/qcuoFneElie5813meRLlpW+mWjyHp49gaXUcHNBnMnshSK3bKHXUK3xzA2VY8aPb72vef7rJKcDnCebSor/TWKQpSVH2UV0GHn4ch+1LD4NlhrM0yM9HnZLGK6A26iBhJyWAL1Iak/v0jjMbn6F/XpAjlKxBcPoQlFLIzq/9Ty2Hh0TpsUMpLd28NojYwxh5lwYAI6s1bHnl4wR9iwCCthwO71vde+QnjVURKrmjdMsXkU6GuuaPQm91iFDc4+uuC9vjGeFmoJAL/6t8MnQk+P0izxvNYKogEBK4h2NxJUtTI7CmjbNljl3lCTu/kfpWduC73Y6DDb92CBXXzi3qmPUUEld/iPrixCISHLnWF5nMany8l+mgDTuSb03X4vSzYWnj+3xrkzbqb6AJ1PX437df20318in4TKbylCh6NiofD44hLre6KvnT8WJ6HPyZOIvWvbr7FoH8gbzSkTsUzFOc4NQWG5J/jATMVhF2RxKlcFPF/sOs9QsPgcdy52GHsxvLt8HOmhiUsyNdVB6Xf0bmWsmuxUMn7KcI9G+68kqIiV14m1+ZqofnrWaALjhC2F9VUrCO84SEDtZaZ7Eo/6e5yTPxnjucSdho6vIUhGL6zQJiwGcgdtl61K6TUtyaRPprpZlBdw75xL9inGW+VGDkitgLQ2eKT7dZEkLFdHOpODd1hKxmQR4qR4js3qMjLz/okTUZ6IrIeCFgP6nXN1E51Cd0pG9FkZyXHd2zKy+hiMQO83uJ1PrLxWaxgJpbgB4nP4xk8jl3rWYPsQpyETxlWkrPlzGLckvHQEAVriQURfPZcn9VcygrsBnkLO8HnxNfQkwtChAMPEhkb99HlCDhx0wNi/I6w25bTpDZ0K0CaSiNSY6nt8O2e8IR5JnIzjSLTUFMj97U5pPZU7tIC7NSs/pwRcsrf8pn0Up8ELnAHtZsE1oiwV2rzWL9KSYCOH4bLmY20BK2LUWLEC8PUOTDLdRBj1HswF8vjYc0D526NoCYjBiSuP4V5VSZ7Zi6Vv6h7VCXTjwb46qdaogZLqb3nH3PJIUP2CddSOtBoL2XGnB14Kfq8A1TukkOgnFZu8eiCrHGKWEWByKjAVx9cXJG6chYD9u2Yzi7AFjxBQJAK93SeL76a2N56lpSySsgPJ6sKDSR+43LUwAdf6ypVfXmoVWHq1Xc4JjNsQxiYNQHgdKFMWNQ/68BHWi4SaTq4q90cI4wQwk+i5u+49El31oDbbxqHHFT+20kq1TzNDah+K2xOouZJy3yZXLkECx411S9VmoA5fKh79nRWdHFz4vWfPa1/Ynjezhz9bITsZyINbUhfD3PO80jQnydZ3uuNhm0ASRfnHZ1HduYopsMos6P/5SydJ1vyvOP+gCJxfL6W8b78A5z2bH+f7a7AKw6ogFAJh4naGfjEnOvo+FSQzSOS8ma6t1E2TdZUI5Z6HpYW0GmExanKWxsj+76HIKM8GWqDx/+aIn5yDE9OEm8GaZxtTwhQ0JANjyLl/sQz0epWwaCofqN/Yhe993Lv35XhJPIMk7FBQoukamhz2pdwfwiUB3JTxyoK0HXQMmsL0Pr02tW/KlFxNxO/V+9ZfEKsXu31Jfze5SAOQ2PBcFW7P7TtnGCvgx87ZW86STnicWGKij95VHHZYojxNdM42vYW4S4NI7QbGcX/ASZKfjG/c+OVr8x/oLHdpRaV92S+HbGSo/xbtho4juYOBTugMsAVXzTImnKfZHNdLslXwH45FyUlPuoI/QnMJTzCJ6cd5a+1TyU5+HV7oMBs/qlbYYtlQJyY0x4U+8G732DP8OWdEOymSbzAcLogjnN65LLUuOI6gNuIeOfSON4MyeoE+gnwTyBdhMqCzIfIGwOPPo2A8YYEyEeV9YMHf3ozLnSxQOWrVaJduVoHbbDKRrgXSLnM1GJa84JXjF0g4COhVPWBYux5Yjlzi1fT1Ar9SmcSiOf+WiThKPl+cdDMFvKU7lx7fHKHvKONgAuRzfnne9HsZMZCKnLupMp9V41cSEDU9o51t8kasKOTKGbd5iIj6ktpoRdYVd8RrxtnoMp4jKd8rRXaWqLzbGffPZAu0eluU7Is9bV5h7eCDEPUzEaX7PMyHF53pFEgYgk18lymdpbgwgWljgQUquL4WV25+YQSQoW7fvBJ7AXgTBMjuKQb/rkz25IaRMJbQViYSAEsn9V5egt014gsmzIdJgX74dybgi0EYbulMeurVJ2b8i2T54+8spznnusDYg5DByKt2vh1JkUe17GV3AdlrkNWXAv3l16grSkSh8mSHF+Bvzxj5uJ5++riUPox4yAIo5KrNxRjQfCoeGnV66Mgv2YTXkbKpCAtfD78KRXUvzYcMf0qDLiImI+9MrBfjrU5fQtGvl71nZMk81b14Oey8yVODoUwNbym7BYmB3IcaErV7gHb9fcNQA31sCG0epuZi3soiqZ/yt3PVja1o6r2Ot6mIVxCiOZ8XgrC1Fu4VRrkCduoxfUzQvxRGQW4DapG6LfUkClTffnv+iB4KL9g9+TlCALmSv8Xm3Affls40YV3w3vQYOgsheF1S3r/T+OkKmDGb8TgmNrOHc6z6TvwD9GZ/94XZ/JHmiXepbThR9I16AQnriKhkd1hG9w02lColmdhPHMSc/xZBaIY9g6UsDxfqslMBrUMWMj2cu0fePVRuAqaAT4TFWMMp6ZWzUd6JjZ4Ct5YZwIb7Hd+hSCAnCr6TZlkBrb/X5IDlqSSwEyw1l2Jcmr+mXHVvyOSwrA2KdQMCf9JMVRmi6tlLkhOrjqNgCL2ooM33rMur2k9nD1ITf+KixpdEK/4fFt4tnnqzYr7y6fxoMA3A5PE5kczx6YmuykCpRHoA/a7/XhigZwv+mF1ymC+iWjwhQwYrKBLHVyElFH9oSsO5H0vPyPtXRhFra6sZEzUqju1/B5dXPDHe6QY/V41Wl1Cumthj52M19yXImlCxzErIX8FLteFTWYKfplKvm4riLel2DEG+jPjqNmq/BCl3LEpCdifMOqAwChp7Tx7garKTxYDY4/hjYLYCwKjLVzvcf9vlD3xoexqdUPT5GIsmdNhNibEAdgmBBvHxlUdlI2o4g4FFD82n/JRfW7+31Sl7IetdtQl7fOR5lP0eAlcjKdD5MBgcVgPRqYA/8bqYwfQXEWuORM5vZx+orCWtY4kM6JJ1udum9Xe2OW+SPG9AJ4FBGPlmJP0/9yd8ILmXUHBOnrKdLxFnLwDxasDianOzd7LjrYTxAQD6UI8NEbNZuiUGOJZKvxaWS6km2+stbWmQ7bFF4KFu2rJqObswqZ8ZjHwJzkypixVXxgfOW7sus74c5ODiA0o3Bsdkva6rNDg4so/fJVxYnGo9gSFLsnPFOU5JtkURTTK7C31+t+/nLrswie7vyEHdpukQgnW6QyXjwZ78jJouIpFPPOHUGNsZaKRbO5DRssWkHueLZGKFd6TZSjYAEYotNR0GY64De1jEcfaAlPwENnbkvVqRwPe0KrjGnDErjP/vDnSHH3MvMGrcVXDQLDW2TIu7+AN+V9EQ2YcMu0/Ac7+YvCtTxJE7GSkSGCIACo4atNhnhsEWKypzjX71L79NAdNt5uv8PMlQACeBbSi0U/HES46csjmcKfgUt8xz9DaDkREtGbmb7u2TqIqHF76055ed7nEGguWmB8/IZzDndUqwj1zCO5cQRTmMdkGx7GCjWc9ECgAKLPXTB09/SYp4d4Qv1g8oDh9M07ne9/3rUXio+jQ2kibvA9peVEZyqNKBfauAtN2cs7s=
*/