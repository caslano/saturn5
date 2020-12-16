//  Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTIBUTIONS_DETAIL_GENERIC_QUANTILE_HPP
#define BOOST_MATH_DISTIBUTIONS_DETAIL_GENERIC_QUANTILE_HPP

namespace boost{ namespace math{ namespace detail{

template <class Dist>
struct generic_quantile_finder
{
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;

   generic_quantile_finder(const Dist& d, value_type t, bool c)
      : dist(d), target(t), comp(c) {}

   value_type operator()(const value_type& x)
   {
      return comp ?
         value_type(target - cdf(complement(dist, x)))
         : value_type(cdf(dist, x) - target);
   }

private:
   Dist dist;
   value_type target;
   bool comp;
};

template <class T, class Policy>
inline T check_range_result(const T& x, const Policy& pol, const char* function)
{
   if((x >= 0) && (x < tools::min_value<T>()))
      return policies::raise_underflow_error<T>(function, 0, pol);
   if(x <= -tools::max_value<T>())
      return -policies::raise_overflow_error<T>(function, 0, pol);
   if(x >= tools::max_value<T>())
      return policies::raise_overflow_error<T>(function, 0, pol);
   return x;
}

template <class Dist>
typename Dist::value_type generic_quantile(const Dist& dist, const typename Dist::value_type& p, const typename Dist::value_type& guess, bool comp, const char* function)
{
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;
   typedef typename policies::normalise<
      policy_type, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   //
   // Special cases first:
   //
   if(p == 0)
   {
      return comp
      ? check_range_result(range(dist).second, forwarding_policy(), function)
      : check_range_result(range(dist).first, forwarding_policy(), function);
   }
   if(p == 1)
   {
      return !comp
      ? check_range_result(range(dist).second, forwarding_policy(), function)
      : check_range_result(range(dist).first, forwarding_policy(), function);
   }

   generic_quantile_finder<Dist> f(dist, p, comp);
   tools::eps_tolerance<value_type> tol(policies::digits<value_type, forwarding_policy>() - 3);
   boost::uintmax_t max_iter = policies::get_max_root_iterations<forwarding_policy>();
   std::pair<value_type, value_type> ir = tools::bracket_and_solve_root(
      f, guess, value_type(2), true, tol, max_iter, forwarding_policy());
   value_type result = ir.first + (ir.second - ir.first) / 2;
   if(max_iter >= policies::get_max_root_iterations<forwarding_policy>())
   {
      return policies::raise_evaluation_error<value_type>(function, "Unable to locate solution in a reasonable time:"
         " either there is no answer to quantile"
         " or the answer is infinite.  Current best guess is %1%", result, forwarding_policy());
   }
   return result;
}

}}} // namespaces

#endif // BOOST_MATH_DISTIBUTIONS_DETAIL_GENERIC_QUANTILE_HPP


/* generic_quantile.hpp
gGMuegjKm4N6ws1D9sAKMuaUhO3bpoh92vDxcBmrfyFyP3OTNO/3yvE+933nNpQKxnF9/PG5sUXQ/3na0xa7PnFzfz/mOsHq1Gsd5FrPIEMcbrh9PSDHTe06x81t31K1jAk+2TaeMcHW/73pLJTyuKCkoDhncTidb5HOV0Xmcbettp2H5PgddzmaLQ/R81/iQbyBO8tZ4Y409/kxLeWLudZ9UN70lQ2SMa4Am8lyvb1c7005/6jbTNv9T+T4dTfRPcMpo2YepMTE5qC5TpRcJ9lznWS5jv+bu5lFczVf73Gdd+T8Q274O7I/l+OX3Hh3qHMl17nHbajjoF5Hv0/bwnOdFuY6Ef3RPP+skXaSYMbTPXI8VMfncDt6jDaz1X8tia+t7iLuom2ko8gXIl/XScC1IkVdaSH94Uj62llOiqTxZfJXT9s4u/DMGLZL0trOPBPNkmvVkjLZT5hfy/kH3PKwheb70Y/LuVfd6ymXH7v1PWNVQYkOVcY+5Qsi+7S7ym3i3OrGm/EF2SIdX7QvoXcneboVuy9z8BsuNtG/kvDXuoedNM+4wUU8z6zHJNxEzvfTcY12LPk5m7Lril5R6LrbxaBtSXEuXTB8H/3SPGvqOZ8tyxcl7jP87czc436STHngLkvF6T2uT5Xtl8eFNJ0lTvKDbcklcj2n/fizevZx1G9huV/vsN+Ucr9eYb825X49Hc8YGay/Jjq+JXn17s1Y5N8jpOOy3k/beO6nSbpPr1Di1DFCw0tfG4S/9mP86CP6nWnT5xKkTYbu0VnB+KQOqBuOTd1EjOWdVJf6XS3Pt3G3DeLvVuGxPLtEnkXMs0++Ni3rcxjhrOOO0TVvL+d/RpgYJ50YHobBfhFjwrYy8amfbXwxOu6t5fwWpzlXH2H/rjtxWN9hzfgxXs7Hmf47X45PsY7lxGXGoXNFn99jx9P05+ycIr0Hhm2/3tgq1NYHM554+r3Jezc5/1Pt7+E4tC9qf7lKZM7lTl/PNi6Y/EwTubrm3v+ClmucE2vuHX3Fr5YZD9+U4zpO2KbrGvrbBvJ3c3yIHBvd/ZhKnh2SvPs1ta2YZ01LG46LaMN+m+daT2qvlPLGr1iOY0zfK5S9imnB9Gv83r0CW9Qo5wfBzgt3wg3IpLQOt++cxVkkJpML1TNtPMtpq+PmQJG7x+3MO/t83K8ogYA7yslyO1nbP/GatpbieS7guU1k35Tzp/CU08gpJPU3ww9wlucR4vI/N5BcHRY6aJsYLDLb3XSemS/GHcTFcu/ojVuCs/QH4rX30Q7aXkbI+fvdvtz9LsS9jwu4jZw0ph4LcZZ+QZz2ftpB+/1YOX+X251Qhbh3cN/wpNLBTXTm42zPMBqn77mZwvS09T+KTDNzb+qZEjx+kLochY7vaRJ2U9h+wzx5vTfzIFJHGi9nxf9T/MN7VtbFh53OYVT53uPtA1mm7af4xvo4M9abejXt399PGvv6CeElD+QNv/K8ISt5kGtpvoL9Y35r0z/k+H7fcUJK5PFA3/Fs3/Fm3/EHKdb+Zwy8L/TYu9yIzMo24f5HwvUe42uPtv5FOGs7M+PsZXJ+rpOh9rpjTJgc5oDaePqXicv/nmLtM8ja3zW847PInE+7C9j6iInD88xo3vFvlHMTneF6H0rm6N3j5AvNmL5Ozk2mlSMvfiqv75ll0mEo29BWL3Of2SgyE6r8DuhvhzGW8TrO8hwU738O0u8w/Lk1sjL3T9qy8+Z696aSZuQ9aaZdvdjG3q7W6mT3IG0X6bg7OYhvG25XZu7C365MfXUQ2XZcv579WaZt5W2trZzvwuhTzzZ+E77CeSZT78ki0523vLq2dqdx2Ochmsm5btzXYk4=
*/