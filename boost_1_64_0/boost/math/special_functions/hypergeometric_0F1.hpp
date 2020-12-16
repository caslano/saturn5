///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_0F1_HPP
#define BOOST_MATH_HYPERGEOMETRIC_0F1_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/detail/hypergeometric_0F1_bessel.hpp>

namespace boost { namespace math { namespace detail {


   template <class T>
   struct hypergeometric_0F1_cf
   {
      //
      // We start this continued fraction at b on index -1
      // and treat the -1 and 0 cases as special cases.
      // We do this to avoid adding the continued fraction result
      // to 1 so that we can accurately evaluate for small results
      // as well as large ones.  See http://functions.wolfram.com/07.17.10.0002.01
      //
      T b, z;
      int k;
      hypergeometric_0F1_cf(T b_, T z_) : b(b_), z(z_), k(-2) {}
      typedef std::pair<T, T> result_type;

      result_type operator()()
      {
         ++k;
         if (k <= 0)
            return std::make_pair(z / b, 1);
         return std::make_pair(-z / ((k + 1) * (b + k)), 1 + z / ((k + 1) * (b + k)));
      }
   };

   template <class T, class Policy>
   T hypergeometric_0F1_cf_imp(T b, T z, const Policy& pol, const char* function)
   {
      hypergeometric_0F1_cf<T> evaluator(b, z);
      boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
      T cf = tools::continued_fraction_b(evaluator, policies::get_epsilon<T, Policy>(), max_iter);
      policies::check_series_iterations<T>(function, max_iter, pol);
      return cf;
   }


   template <class T, class Policy>
   inline T hypergeometric_0F1_imp(const T& b, const T& z, const Policy& pol)
   {
      const char* function = "boost::math::hypergeometric_0f1<%1%,%1%>(%1%, %1%)";
      BOOST_MATH_STD_USING

         // some special cases
         if (z == 0)
            return T(1);

      if ((b <= 0) && (b == floor(b)))
         return policies::raise_pole_error<T>(
            function,
            "Evaluation of 0f1 with nonpositive integer b = %1%.", b, pol);

      if (z < -5 && b > -5)
      {
         // Series is alternating and divergent, need to do something else here,
         // Bessel function relation is much more accurate, unless |b| is similarly
         // large to |z|, otherwise the CF formula suffers from cancellation when
         // the result would be very small.
         if (fabs(z / b) > 4)
            return hypergeometric_0F1_bessel(b, z, pol);
         return hypergeometric_0F1_cf_imp(b, z, pol, function);
      }
      // evaluation through Taylor series looks
      // more precisious than Bessel relation:
      // detail::hypergeometric_0f1_bessel(b, z, pol);
      return detail::hypergeometric_0F1_generic_series(b, z, pol);
   }

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_0F1_imp<value_type>(
         static_cast<value_type>(b),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_0F1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z)
{
   return hypergeometric_0F1(b, z, policies::policy<>());
}


} } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_HPP

/* hypergeometric_0F1.hpp
t87HwdV0ufJ8elx8cP66o+E7+H6TfFe2kg5Xok6+Ag+gTxTcRBdcRH98DW5vb1zo00V4QU2s/p9bY+hT7PcidnUQv6C7RWKC8xt+817nwfPXee9m4/iOvPcBHPEHnIUnDRpG31oLbzWKM8XscJ789Gc0vumHOMl4mdd1P4SC81+iHxXCFe2C55s6Fa7O8nzuV14JjxwBr9OP0+XR2tvi6H/BcXl79d2d8Ib5WD0Rz/yLPn6R8Yg+3yH8wr+LTuYPr4uzf/GXjXTqrvyBHW/CD6si8Hi/BLhNfB0nv9+L3/wrDtAr49fSnc8Prj/zbnW1S9RNj9MXksCeR4p/fl7fGa8VH2sPoXPicavvDM5bxz/KhtGFWsTv+Fh1m3AQb68X59LNfzv1I3xgqvdLfTWi/yH4+YwX1e3K4MvD6Ft0u8LbxanC4OcpdPiUvfIPP6rfHQ7+zb6m1uN33n9dMb/rIA7Npd+M049SZ96G8ps1rvMynPg3O2Q/Ux/1nq/L44/FB+8rvubG6AeJF0fw89Vfml+8IG8gfeMt/j3Ye/9Fj74sxvj5/YHg5xVp/LgNfWi2uEqfbHjFeF3uuS9uxW7pK/Jv/Wr64Cb8fh07/wxuWax+3QEu+d77JqkfTMFzE+njxfjeYHaCr9QsxDOflfcyg/NmeI8ydf3NP5uvfeLMf/8LdBZ2IV/XJ8m3m+A11yl4UB1wOn0Lz6/717xvcF3nJc6mFw2htz2k/7On9y9Wv2gRJ9hFoj6CueqgWVvx2dXi2y/y9TS4ukB/jvpYy4n00nfEnb70YXys86+x6tHBe88/w/PdHDz3hu/xry3G+SV5Gz5uvDX4u4xr6Z0Pwu2JdMN+8uq3dHn5N+UD9a/d5uuU4LlXfB1ct/ap4FhRKP7tVbeuxwOeNl6ZscFz3sAOH6dfHBAnb4EH1fE2N8cFz/tEXPC+aXCE84onev5d+AN9ZNFEeetm+aU9vWOXuvNuefcu+HoWfcH7lOFnpWcbx83igLpM1ojgWN0VH1hMJ+muDhaS7w8Pjvn48IRjzf9T/JgOuWi7+kO+cejGjvUbbp6mvy9Wf2FEX/AQ43ClPKC/L/MueC7at3KV95zI/sfTM8ShGX3wOfp0jfiZvSC4Tt5s+P90f/+Avpu1rYPzJsrTafzs+eB9Zqov5NAXk8XtFs9bWwQvxAb3zR+MB5+jjqUPuWQ7P3pdX1OiOKUOXvS7/oO/2FUmf1vGv5rwjpBxOF1dckFb+ZJ+Nj3O9xrOV/dZ+A5cARet/gZuPF1+/BmOvz8cPO9B+u/xm+SldO2v3W9H8PuiwXQ1fTbZeG+Tuk63B9Ql94sHrfHeHfpGrqErPMAvJtHDxJeCMcb1ETz0CHaVjj/1dEyRF5vhwXw8coQ+ZH3rc7frp9T3Uve7+uC3EflKv+sZ8s/KcPA+aex4kPr9wcFxxa/BsUmeLWmt/vWEegQdMaV18P4hfRJzz4eTOgX3WQjPLppgHLqrPxUF5xc/AJ9H+wKPld+6wxvR+u9b/PIwOund5udh9yuWzx/nH/hz6e3qB//CcfwktR99eRFd60T4emBcMP876FujxOdWxl1f5Iy9cOxN4ql8tbm9eRP3ioeIC3BJ2tDgvrPbwFVx7GY33EK3y1MnzouBS1eKc5eGg3Hsql7wHz4NdBQ83nOt5vd5b+ATH8IfS8LB836Ez3wA10+n5zRH6Dd0u4v48xrfjeDHdafxg178Aj/LmO3nF0Z5jz74OXSjyXBpj3jf97YK/q4vO+/m+Xuqc230d/S0sk76xbrAg/jb/rGeoxy+P14c9nyVcF7zPXjaJjrfFrxjBD75cjiYnxvpoWvxwQ7qIW2C++f8FRf4Nz4=
*/