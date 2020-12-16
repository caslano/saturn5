// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_MODE_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_MODE_HPP

#include <boost/math/tools/minima.hpp> // function minimization for mode
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/fwd.hpp>

namespace boost{ namespace math{ namespace detail{

template <class Dist>
struct pdf_minimizer
{
   pdf_minimizer(const Dist& d)
      : dist(d) {}

   typename Dist::value_type operator()(const typename Dist::value_type& x)
   {
      return -pdf(dist, x);
   }
private:
   Dist dist;
};

template <class Dist>
typename Dist::value_type generic_find_mode(const Dist& dist, typename Dist::value_type guess, const char* function, typename Dist::value_type step = 0)
{
   BOOST_MATH_STD_USING
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;
   //
   // Need to begin by bracketing the maxima of the PDF:
   //
   value_type maxval;
   value_type upper_bound = guess;
   value_type lower_bound;
   value_type v = pdf(dist, guess);
   if(v == 0)
   {
      //
      // Oops we don't know how to handle this, or even in which
      // direction we should move in, treat as an evaluation error:
      //
      return policies::raise_evaluation_error(
         function, 
         "Could not locate a starting location for the search for the mode, original guess was %1%", guess, policy_type());
   }
   do
   {
      maxval = v;
      if(step != 0)
         upper_bound += step;
      else
         upper_bound *= 2;
      v = pdf(dist, upper_bound);
   }while(maxval < v);

   lower_bound = upper_bound;
   do
   {
      maxval = v;
      if(step != 0)
         lower_bound -= step;
      else
         lower_bound /= 2;
      v = pdf(dist, lower_bound);
   }while(maxval < v);

   boost::uintmax_t max_iter = policies::get_max_root_iterations<policy_type>();

   value_type result = tools::brent_find_minima(
      pdf_minimizer<Dist>(dist), 
      lower_bound, 
      upper_bound, 
      policies::digits<value_type, policy_type>(), 
      max_iter).first;
   if(max_iter >= policies::get_max_root_iterations<policy_type>())
   {
      return policies::raise_evaluation_error<value_type>(
         function, 
         "Unable to locate solution in a reasonable time:"
         " either there is no answer to the mode of the distribution"
         " or the answer is infinite.  Current best guess is %1%", result, policy_type());
   }
   return result;
}
//
// As above,but confined to the interval [0,1]:
//
template <class Dist>
typename Dist::value_type generic_find_mode_01(const Dist& dist, typename Dist::value_type guess, const char* function)
{
   BOOST_MATH_STD_USING
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;
   //
   // Need to begin by bracketing the maxima of the PDF:
   //
   value_type maxval;
   value_type upper_bound = guess;
   value_type lower_bound;
   value_type v = pdf(dist, guess);
   do
   {
      maxval = v;
      upper_bound = 1 - (1 - upper_bound) / 2;
      if(upper_bound == 1)
         return 1;
      v = pdf(dist, upper_bound);
   }while(maxval < v);

   lower_bound = upper_bound;
   do
   {
      maxval = v;
      lower_bound /= 2;
      if(lower_bound < tools::min_value<value_type>())
         return 0;
      v = pdf(dist, lower_bound);
   }while(maxval < v);

   boost::uintmax_t max_iter = policies::get_max_root_iterations<policy_type>();

   value_type result = tools::brent_find_minima(
      pdf_minimizer<Dist>(dist), 
      lower_bound, 
      upper_bound, 
      policies::digits<value_type, policy_type>(), 
      max_iter).first;
   if(max_iter >= policies::get_max_root_iterations<policy_type>())
   {
      return policies::raise_evaluation_error<value_type>(
         function, 
         "Unable to locate solution in a reasonable time:"
         " either there is no answer to the mode of the distribution"
         " or the answer is infinite.  Current best guess is %1%", result, policy_type());
   }
   return result;
}

}}} // namespaces

#endif // BOOST_MATH_DISTRIBUTIONS_DETAIL_MODE_HPP

/* generic_mode.hpp
/mgsfBq33PP3xZ6/L/T8vdTz9zL9pk1r3Ar9ewtuif59v+rvrA/PjcIsXKneN9fiHP0WSpCHYBz8CMbD38Ku8LDqXXwBu8Hfw37wYzgQHoHD4B/gSPgJHA8/hRPhUTgVfgZnwc/hHI0vrN+zX9PXFlfq0+/5StN3DEbDP8G68BvYEP4FnqLHbeC3Gm+hzhF6v5ES6yn7H6vey0OwBXwYpsJHYC+4XfP5KBwFd8Ap8CcwX48L9XixHof1Y7bpdWtbvunSTvPTXvOT6tHX2KnhrtZwXn2Nc9Qe2nSYBmfAHnCm1sMsOASeD78HZ2t5Z8KLYTZcBXPgajgXroG58Eo91vTrHAf3IEv6W2n6W2s9pGi4o2ZOQeY0JFxz3EGco/pcsbAvbA/7afsaAHGipzUWjoTj4Bg4AZ6u6U+Hl8BR8HI4Gv5A5a6Bg+BTcDDcpXIvqtyrKvc6HAJd0jcU1oajYCwcDRPgGNgIDoOj4HA4VuUmqNxkOMboreh7OmyBK/XprdzvkZutctG4sT65p716Y1WUW1lFubIqym2sgpy0b5VLsLSPjdo+Nuk4coeGG2CeTWlDGq4WLk3DcYJwANaDAdgSRkH5lpA+N3q/RXUK7i0NvlOv+6y2y12wOXwOtoYf6PiwG3aHL8LT1D8d/gKeA1+G58E9MA++CpfB1+BKlV8F31A9xje1/7yl7fBteD38JbwFvgM3w/fhFg1/L3wXblP/Z9Rfy1ef2ej/lvK9R/O5Rcfrez31F2/C2dvhFVW0o9fpo1hnKG4mLqgXtRXn+VbPd6oH9V3rQP23fZ/nP07PiTaxAbcLdxjX+LexTjpuHm49bgduPy7mMPbzcDNxV+A2457E7cUdPVyj91Tzq/nV/Gp+Nb+aX82v5lfzq/nV/Gp+Nb+a3//a719j/w9dwJzSoPr/P637vzaox98nuO6XxXXlw4Li/wP8+/QV/f7Mub0WzVlanCO6/atSHWNHJy5wvM2J3HbMHyb79fpClpIyckrVVpLRcbWv6yf7bSUtrkgHBVmrHr1Vx0xlzfr3JalV1xcgzcfpen5t9DKNjplfv93oBKdHHV9W6yjjoxWXVUZuoSP52t9Y8lWhbamj1Sivo9Uor6P/RHmRZsqBNFezvMJtq5Mq+6zUtZlluF3oPMafclx5YSnm3CmjBzg+WxzWsiK8v6xUV1f1TVLl/FzWWDpay0/DW/WSj/j0kr063IUSrqHRKV0rx7UknlYaD9oQxs5Tooln4Zxg6TiePSkDJOwAPXadK+W4jmd/gHRjI58m5+OOk9d6NTrPjatQr5SvtR94dZ6P+HSWE732oDSf3rrergr5A/SC/XF9KPBtobqe1rfHwIyzhmETyowiTpXGkW2eurpP6nrRQqt+hcr69d2zc7DuZtdXRd7aj0w72i7ne5DfWlZ9eQ1v9udcSh2srkb/so1HwTw20Twm+XTPNS+6N6ficapMFX2+pxedgVs/KDhwWetCR6mqjVNOs6rXh9OsevWBfKX1UUvOT6YHnmqrDxPe1n+bwt5yPta0O3ay0Y7L7YE2kfNdkHCd8LcIb4sP1etGuDq16jpVZuw8SXXbz6eH/6Ze+w2127qyWbntLfQm87Iz5hUsJsbyMVKPdTxZLfINrXVMXMbObhu5WmFRzoVZ8yQ1Wp7J8Bcid77acUPHPpQG1v/y+D5ZXVPvjlxb7DmJbBL8gcg+5zzO/ztx9YxsnrGx9qzIXM63y+rgJ3tjNC70Sz37RcpE7ml0H1hzwiWadEemuRFcI7KvhPYBiMySvOzieXI+wNEdcr4D9cyxydPVpK8Ra5rR7Ec501lx/Dht0ny1yO/CclzZCe2yJXrtrmn9ePUux2o=
*/