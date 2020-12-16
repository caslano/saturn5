
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_1F0_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F0_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>


namespace boost { namespace math { namespace detail {

template <class T, class Policy>
inline T hypergeometric_1F0_imp(const T& a, const T& z, const Policy& pol)
{
   static const char* function = "boost::math::hypergeometric_1F0<%1%,%1%>(%1%, %1%)";
   BOOST_MATH_STD_USING // pow

   if (z == 1)
      return policies::raise_pole_error<T>(
         function,
         "Evaluation of 1F0 with z = %1%.",
         z,
         pol);
   if (1 - z < 0)
   {
      if (floor(a) != a)
         return policies::raise_domain_error<T>(function,
            "Result is complex when a is non-integral and z > 1, but got z = %1%", z, pol);
   }
   // more naive and convergent method than series
   return pow(T(1 - z), T(-a));
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z, const Policy&)
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
      detail::hypergeometric_1F0_imp<value_type>(
         static_cast<value_type>(a),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_1F0<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z)
{
   return hypergeometric_1F0(a, z, policies::policy<>());
}


  } } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_1F0_HPP

/* hypergeometric_1F0.hpp
k/PffQPdjF/3lVfH0SfW68+P1ZcxyXusCckL5nmbuqv+p9LRdJTJMexdn6r417JG3fIu37XrUyqtxDcONj500m5N/Otj+Ovw4PnW9dXfcJvvKOvMx6Pi+3D9IevhMc8x+0Hj1gjnt2VvcfqIj+ZHR+rLeVK8OYFfbqWH1PEPeW5RDr01K7hv3ud4Vbp68wY68KX4xM8x/o03/OA7AnXR9OfEf/Wm3GfopluNq++kZ3cXpwr1leTzD/pO4rnuF6MuP0696TT1s6X6ZK/XX7pC/jqU3vZTvO+c9F9/5Lxj2dtLnrNAv6X69aav+fOd/Dw1Wr+Dl+vl8f5waV9x/1f590G6weXym3rc8k70pCXimHpgqbpTlj6b+XTYzEfoq3vlmcviA3vp4v4n65sbmeD7huDvCh/TR4eXpL2A/0yiG+yXB2fqM4yFE7rpA5pM70ym7xwrzj/ifX9tHbzvnfj+k/gAHrv8R7qh/swJF6orDYAX/4afH6IDfso+2F01HS1yG31nOn5yFD9oZR2IQ8XzKvb4Brvp2U6eUQ9bq154t/eCa/P0j1X01OeunpTzL9w4Bd8dLi52wWvupr96/8TL3GcffnqXekRfcSgGz/D8oWP0T32mv68rnUF+WV4n3kygT+CJg9xvxiK/Xyx/VsDXT8jT3zsmOq+D9QLgkvosfYynxbIP/UR4atVIuFNdKu1Q9vE0XB/Hz1wvcYXvpvepM/zuu6AXxGU6eo8b9e2cpL6bBidMxTMPotOshoeNd673rkziJ75Tyh5BJ79cnIaXVrtf1ix9Gd/QgejXiVez13vhvDR9ZcXqD2eap7vYHXtdrI8tN1sc6iB/zsAby8X5I+hkWerA6oft50bzLR7b2fMNDI4LD5cP3lDfp+OtO5X+HsPPnxEnztN/M0g/7Hr49OjgvMXPue4vdJK29IBq4/YN/txLPlhDj4wP/r5phbwLf858ni7M3/P+oXf4zqJ2NFwgzzRd7j0+hvv4f5HvOTedyE+eM/5fiGv0gVVXyDs3iNe75bOh4vsWdf264Oez1Y+bu7GHY9jPMXDUw/p7d+B5T8k/2XS9WHGSjlrfTv+5Ok7zOeqRlXT49ey70HP0l//0j8+YFQ7G9Q52F0fPOiL4ff344Pz8JjoOvJonb636Tf3kYnFRHSjku/0q/p78vbxZBw/2V3ejC9eU05+NR9Gnzn/XuC+VF++RV78Nfp67Wx9wDf7/gnrlcDi9B/yanBC8X3bwd9vxrrpF6m/yR73nXjVaHDVeC+XxklvxiOXsrS+7ndM2+P0k9bhnjdOJ8By8UERPzYj2/5eoZ66AG6ti6MvsMJ+/RuSFkrjg+fvj5/HyPp198xL9873hs6je53qlcOSKB8Tx5OC6Zcvg4m3s/Wt1sBFt4ImoDibfLjOOvYPxyunH7+CS2vutEzFCfawoRPeR7zuoE9fig1/xy836N88zz2X44fnGYzBcLF5UZqiT7sOH6O51N9Mf6EqhZPlzgLgT1UFu8rxD4eDX4Q9xNbeTOvMznieCl02Dey6KgZvhpY/57wvmYwI/X6uv5DXvO8P8p8Xom8Zv5+jzb1Yv36fedZ95NL6hE41DP7w92p/Nn5bvZRf0kNyRePzU4PqZy+GRIri6QTzhr82X+16mQj7d7f76JetKjftF6olvs/cU9bCscPDzo+SLH/V7vGg+6EFJrYzfY/jfjfrS5J2pA+lT/KduWGzwvNvjgvmMUS96CU+4Uz8Y3FbVAd/po6/ze/WqyfjuSM+/wfHdkD4n8WCZeYz2EQ+gX8+nf/juteUs8TJePO4F36br7/5bPqnDe9RR9ouvqxbQsU7gB9Y3argILmNPneP9XTo94SI=
*/