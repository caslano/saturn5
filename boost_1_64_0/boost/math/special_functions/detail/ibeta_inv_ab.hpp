//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is not a complete header file, it is included by beta.hpp
// after it has defined it's definitions.  This inverts the incomplete
// beta functions ibeta and ibetac on the first parameters "a"
// and "b" using a generic root finding algorithm (TOMS Algorithm 748).
//

#ifndef BOOST_MATH_SP_DETAIL_BETA_INV_AB
#define BOOST_MATH_SP_DETAIL_BETA_INV_AB

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/toms748_solve.hpp>
#include <boost/cstdint.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
struct beta_inv_ab_t
{
   beta_inv_ab_t(T b_, T z_, T p_, bool invert_, bool swap_ab_) : b(b_), z(z_), p(p_), invert(invert_), swap_ab(swap_ab_) {}
   T operator()(T a)
   {
      return invert ? 
         p - boost::math::ibetac(swap_ab ? b : a, swap_ab ? a : b, z, Policy()) 
         : boost::math::ibeta(swap_ab ? b : a, swap_ab ? a : b, z, Policy()) - p;
   }
private:
   T b, z, p;
   bool invert, swap_ab;
};

template <class T, class Policy>
T inverse_negative_binomial_cornish_fisher(T n, T sf, T sfc, T p, T q, const Policy& pol)
{
   BOOST_MATH_STD_USING
   // mean:
   T m = n * (sfc) / sf;
   T t = sqrt(n * (sfc));
   // standard deviation:
   T sigma = t / sf;
   // skewness
   T sk = (1 + sfc) / t;
   // kurtosis:
   T k = (6 - sf * (5+sfc)) / (n * (sfc));
   // Get the inverse of a std normal distribution:
   T x = boost::math::erfc_inv(p > q ? 2 * q : 2 * p, pol) * constants::root_two<T>();
   // Set the sign:
   if(p < 0.5)
      x = -x;
   T x2 = x * x;
   // w is correction term due to skewness
   T w = x + sk * (x2 - 1) / 6;
   //
   // Add on correction due to kurtosis.
   //
   if(n >= 10)
      w += k * x * (x2 - 3) / 24 + sk * sk * x * (2 * x2 - 5) / -36;

   w = m + sigma * w;
   if(w < tools::min_value<T>())
      return tools::min_value<T>();
   return w;
}

template <class T, class Policy>
T ibeta_inv_ab_imp(const T& b, const T& z, const T& p, const T& q, bool swap_ab, const Policy& pol)
{
   BOOST_MATH_STD_USING  // for ADL of std lib math functions
   //
   // Special cases first:
   //
   BOOST_MATH_INSTRUMENT_CODE("b = " << b << " z = " << z << " p = " << p << " q = " << " swap = " << swap_ab);
   if(p == 0)
   {
      return swap_ab ? tools::min_value<T>() : tools::max_value<T>();
   }
   if(q == 0)
   {
      return swap_ab ? tools::max_value<T>() : tools::min_value<T>();
   }
   //
   // Function object, this is the functor whose root
   // we have to solve:
   //
   beta_inv_ab_t<T, Policy> f(b, z, (p < q) ? p : q, (p < q) ? false : true, swap_ab);
   //
   // Tolerance: full precision.
   //
   tools::eps_tolerance<T> tol(policies::digits<T, Policy>());
   //
   // Now figure out a starting guess for what a may be, 
   // we'll start out with a value that'll put p or q
   // right bang in the middle of their range, the functions
   // are quite sensitive so we should need too many steps
   // to bracket the root from there:
   //
   T guess = 0;
   T factor = 5;
   //
   // Convert variables to parameters of a negative binomial distribution:
   //
   T n = b;
   T sf = swap_ab ? z : 1-z;
   T sfc = swap_ab ? 1-z : z;
   T u = swap_ab ? p : q;
   T v = swap_ab ? q : p;
   if(u <= pow(sf, n))
   {
      //
      // Result is less than 1, negative binomial approximation
      // is useless....
      //
      if((p < q) != swap_ab)
      {
         guess = (std::min)(T(b * 2), T(1));
      }
      else
      {
         guess = (std::min)(T(b / 2), T(1));
      }
   }
   if(n * n * n * u * sf > 0.005)
      guess = 1 + inverse_negative_binomial_cornish_fisher(n, sf, sfc, u, v, pol);

   if(guess < 10)
   {
      //
      // Negative binomial approximation not accurate in this area:
      //
      if((p < q) != swap_ab)
      {
         guess = (std::min)(T(b * 2), T(10));
      }
      else
      {
         guess = (std::min)(T(b / 2), T(10));
      }
   }
   else
      factor = (v < sqrt(tools::epsilon<T>())) ? 2 : (guess < 20 ? 1.2f : 1.1f);
   BOOST_MATH_INSTRUMENT_CODE("guess = " << guess);
   //
   // Max iterations permitted:
   //
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   std::pair<T, T> r = bracket_and_solve_root(f, guess, factor, swap_ab ? true : false, tol, max_iter, pol);
   if(max_iter >= policies::get_max_root_iterations<Policy>())
      return policies::raise_evaluation_error<T>("boost::math::ibeta_invab_imp<%1%>(%1%,%1%,%1%)", "Unable to locate the root within a reasonable number of iterations, closest approximation so far was %1%", r.first, pol);
   return (r.first + r.second) / 2;
}

} // namespace detail

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibeta_inva(RT1 b, RT2 x, RT3 p, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::ibeta_inva<%1%>(%1%,%1%,%1%)";
   if(p == 0)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }
   if(p == 1)
   {
      return tools::min_value<result_type>();
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(b), 
         static_cast<value_type>(x), 
         static_cast<value_type>(p), 
         static_cast<value_type>(1 - static_cast<value_type>(p)), 
         false, pol), 
      function);
}

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibetac_inva(RT1 b, RT2 x, RT3 q, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::ibetac_inva<%1%>(%1%,%1%,%1%)";
   if(q == 1)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }
   if(q == 0)
   {
      return tools::min_value<result_type>();
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(b), 
         static_cast<value_type>(x), 
         static_cast<value_type>(1 - static_cast<value_type>(q)), 
         static_cast<value_type>(q), 
         false, pol),
      function);
}

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibeta_invb(RT1 a, RT2 x, RT3 p, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::ibeta_invb<%1%>(%1%,%1%,%1%)";
   if(p == 0)
   {
      return tools::min_value<result_type>();
   }
   if(p == 1)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(a), 
         static_cast<value_type>(x), 
         static_cast<value_type>(p), 
         static_cast<value_type>(1 - static_cast<value_type>(p)), 
         true, pol),
      function);
}

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibetac_invb(RT1 a, RT2 x, RT3 q, const Policy& pol)
{
   static const char* function = "boost::math::ibeta_invb<%1%>(%1%, %1%, %1%)";
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   if(q == 1)
   {
      return tools::min_value<result_type>();
   }
   if(q == 0)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(a), 
         static_cast<value_type>(x), 
         static_cast<value_type>(1 - static_cast<value_type>(q)), 
         static_cast<value_type>(q),
         true, pol),
         function);
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibeta_inva(RT1 b, RT2 x, RT3 p)
{
   return boost::math::ibeta_inva(b, x, p, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibetac_inva(RT1 b, RT2 x, RT3 q)
{
   return boost::math::ibetac_inva(b, x, q, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibeta_invb(RT1 a, RT2 x, RT3 p)
{
   return boost::math::ibeta_invb(a, x, p, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibetac_invb(RT1 a, RT2 x, RT3 q)
{
   return boost::math::ibetac_invb(a, x, q, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SP_DETAIL_BETA_INV_AB




/* ibeta_inv_ab.hpp
EOVx5qrfvgHS73hJpsvbG7YmTk5zVRpUU9DydNPL6LThxvZYpJvTH6TQM0AfEPxWXbogyyu80NJIh08bdMfETSRNxt8Ipvx7RHdMgMGk+Jl3/9d36agP+Fm6OPdDrKq6rQlrSBhEzcZ/vadC3A8DqmJ5F4RBPbv/ghOOchderSwuqoUbHeG28IBsoRz7TBV7EN6Phv0L0M7w0F0LwYw9r5bzQJTAAWLYf3Rnkx2+O+vW+bynYu8aVyrgMQaVeQyBbo77tYYLPLgzNY1S92ITd0HF3S1MwSgvgTV6LN//z3HnPntpFVcO4bVP8Oxd3Jvq9zD8SU3vYARH1WO4oG6zM5jadfmXXhe4cw4mMPDjm2W8/EsvrdalUgnhXCBYCSbOWdPuVqhE4OyJwXNl4r4OdWFcA051wqUBKVgdhi//vbdS/RZwZBPUtw+v/S1ltujdMN1ejv+Eir875B1FcDsv4EHqGc74L6j4Q2kZ1m7gLaUZk9LP2/bSa6qc+HB9IzgsPHd3ePie8K8As2149Ba6X1TcPJJWPbzA4UDBXzIBGTf5V9Cd9HAAHqYQ3/+Vf18J7i+/Y5zyla6T4+EjfrsmfKNwG4xdvjF8s0M8jDda8HCbjCMHvPJ4A50FWMbvDqZ7CH433TU59l5AK62JM3pNib0F/C5ePhGRymas+NUw3Szs01s7iuW4D3w3XICyzPdDvAhYdhB74Dr0dlY58SEXbI/LX4fb1MFvdfyGD09kcb8OnVNYuUg8VIvYJmDB5AK1tznM+b3rcH/k+V8XvykPk9DbuTuwY3u35fZMnf/eK8YXzpGSh6NHQAb5fbw7Xopx7H3h+K3BZQw6OwYorzOXnYtpDzc5rQuXK8RB6bncP7lCIWZHPOEOZCr3ja6k4MRaTsZ2cV7niW45NAhzn6voGC4P59O9KmMU5wal4V4d6Dx6IJW7ZiFKSlnfdA3CyMucEED09WsZ9K0R5MBxnQ+6jkHvj4n329e1aMLrT/RPXJ/oMldsJqI/8QZELyz7626o00fZcVvn9khfvbGg72c+cT2+n2HZJFJo45sKWidzBsM71uDIpzJc72YWrR2X+d3hZ95C0Mk8oVi7l9xSfh+PRWRhv3NQjUlNby1o3VHWamgYKvF9b7od0nepaYl29s5Aw1G70Zlq8YbjuxIN25Jpj74b04YjwcnlOX93pj2iP+hudCZd9e1D/56CDl0gU2UZ/tt9xPeCIC+lD2v3YwwH63C5XnBY0scnD2RKAuSH37X0kHb39sZxpS6/LtF3i+dQQLSt3i730y2r4juZilS+V9TEdzOYyKH42yfWgV58OkFGZd4+z7cxF4dqjdO8Y4RYPpmiRIByv7zCxsk8MR14M9Wmj0djHGYcq+rGFg6jRhlzx8TGYLk5HjcFjHW6Akqk1O0TBRguFaf1wfvbOMyRY59XAGO/GC8D09Wyv6JVjIM2pf5ZXS3GcMm4DulaMRbbjNJ0jyDOePGI0+QxdJ+LEAujHQSQZPnSR7PvfRGuD/souw7L7IVjkoZLNU7rjg8U3yGhLBdK6wv5d0hMLuCmTDv/IEGTe61QBJzPkOa3BS0f+RiELem4Bm8Ju68NoRmzAUSCgpNzZwLZXm0Z6YdUmxuWRNVakqbgHrTiP9R7w1WeFMIO4HK+JBV3vELq07bYCuqZfvwHrRpxRkFQrsDpd4OpfXJZ8tH69EaX0tegs9GA6nbAXH/2pXrwY6TPtPVeDG8bQIAEbAn/v+u9mzhXEefssC3Npszu6/g1zLV/knSl5dr9WW+7PZvlexSA2ZN7FEoC7dnxAZ4B+zPQ8R0v69y+oP/NoutvbP0b6HSODdO85HXtNNVzXb/OeYAljWA=
*/