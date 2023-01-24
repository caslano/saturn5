
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_LAGUERRE_HPP
#define BOOST_MATH_SPECIAL_LAGUERRE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{
namespace math{

// Recurrence relation for Laguerre polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type  
   laguerre_next(unsigned n, T1 x, T2 Ln, T3 Lnm1)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ((2 * n + 1 - result_type(x)) * result_type(Ln) - n * result_type(Lnm1)) / (n + 1);
}

namespace detail{

// Implement Laguerre polynomials via recurrence:
template <class T>
T laguerre_imp(unsigned n, T x)
{
   T p0 = 1;
   T p1 = 1 - x;

   if(n == 0)
      return p0;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = laguerre_next(c, x, p0, p1);
      ++c;
   }
   return p1;
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
laguerre(unsigned n, T x, const Policy&, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::laguerre_imp(n, static_cast<value_type>(x)), "boost::math::laguerre<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, unsigned m, T x, const boost::false_type&)
{
   return boost::math::laguerre(n, m, x, policies::policy<>());
}

} // namespace detail

template <class T>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, T x)
{
   return laguerre(n, x, policies::policy<>());
}

// Recurrence for associated polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type  
   laguerre_next(unsigned n, unsigned l, T1 x, T2 Pl, T3 Plm1)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ((2 * n + l + 1 - result_type(x)) * result_type(Pl) - (n + l) * result_type(Plm1)) / (n+1);
}

namespace detail{
// Laguerre Associated Polynomial:
template <class T, class Policy>
T laguerre_imp(unsigned n, unsigned m, T x, const Policy& pol)
{
   // Special cases:
   if(m == 0)
      return boost::math::laguerre(n, x, pol);

   T p0 = 1;
   
   if(n == 0)
      return p0;

   T p1 = m + 1 - x;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = laguerre_next(c, m, x, p0, p1);
      ++c;
   }
   return p1;
}

}

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, unsigned m, T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::laguerre_imp(n, m, static_cast<value_type>(x), pol), "boost::math::laguerre<%1%>(unsigned, unsigned, %1%)");
}

template <class T1, class T2>
inline typename laguerre_result<T1, T2>::type 
   laguerre(unsigned n, T1 m, T2 x)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::laguerre(n, m, x, tag_type());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_LAGUERRE_HPP




/* laguerre.hpp
RMXPYOz1rvd+vZ52Zel5qOQ67NV97I82uzGLfuY+tbaNVrMkRwl2qKNwQ4+82SNPzWL0Nk+O8lRCpwC0HBJyGvBtVywSWK/YKracNh+sK9hn/o53wGt6299xjP45hPNbbEfAXLV9ccs6U+bw60XwusN0mVil+4/Uq68wG9kWdl6j3bvfyxVifNan5qVP4E/niBOAcA5fa3QrUL8uhr8srVIO/1mC+zQMUhFjrXM6xfwEH2R+otTPb6BwNXATNRNQ3SONkC4A+n5SCnnB4bYTyX9JmnGNi22NzSW1R3parJi8lCiDw4c9aNyLp6CqayAPUVsEpCa7xhG4Q0r18vITiCYuUaYAQhPlD3pZr0F6UthwK00H5f8lbstS/ilfAuN0bE4AKqHBmjMOk/BUf4EJKLxkAhB89o9tryjff3tUrOl17rr4LTp9GddojQMFHr17SqyY702NcXQVhHP+UxUQ6K4x78f9f/b1d38PbVcpCyc7R29OcycLczcON7vv5/6YfilLmTB57naQI97nQOrAIhnhGrVy/mUDhqCU8dLMoDepqViZ1MS5UzE8+H9N2NhZlypgstRUtPC3alorbi2W2i4XKWPWNEenaeut+XzTbD72YWbR/qEGewYe+ANF0hMCQBeXT+ewySpOSN6pqxDQe8Y1z1V+w8ojifdzRGQPZYDcmOAfVTEhGI8MKBg1niDBf02Vg0y1QaJ9du0y
*/