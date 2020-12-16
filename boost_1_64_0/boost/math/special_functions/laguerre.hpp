
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
0LPK4E55KYk+2ij+rTqH/n62+snT7H+IOtPZviO8GJ+s8v6FnruZfT8uzh2JHxwk398uf/2AF1wgbrU1fmP5wyP40qP4Nv2yXr1j7j7+MT5a/4OPxhlPcazwGc+B161ObGtdaOtBZIlbiZ7janwgK6xPWby/Tb1tt/psH/6DhyTT/dI7s+cvxN2ddMEf4ImVdBvxrvIx+c06KItC4sCb9jN+Cy5aL47SVbLhqMJR6sDqYIV0om7sMH0TXEuPT9kWxsf5jf0q659lbz/D3fS1vDfVk/28JSzvZMIR9vurZrczr4CP6UP/0R77EqirdIH/j4c7d9KB7OO64iV2UIfPT4RH1HET4ZacLuxffMu/NWyfqBjXD36fb9+yxvPppk/qc5vdJjj/v/8H9Tp9B+wiaSe8epV4dmZbuDROn6N8cyXd/Vrz1c581egj3kH/w5t6wDWhA+qKq2OC8350HfXJ1PvEoc/x71vbwXPsCH/ab/+BTUPh0A/kJXWK6nR5X39IuX0D0yP4vLg2yD7yM8TbhaP8frU8maPuQF/Je0u8/kAcbsPvCvVv/6OfbB48xe/m/h0fHFfSCePVTc+kX32nTtIYnS86/zz65U/iyEJ42f1zf9TnoE5UmCGejQjOr64KjvvVHefSR/bTWXLEmcVwVNNgfayHRvT1+J5unv4vOlc5ftKAn2Q9GBf8/c3i0wlw/zLxMl+cONe+oPYHjTxDxxwaoiNbF8K+IOXi+yDjV1/Mbh5SxxwVgot9L9odDv1Dn1VHOCpq73fBgdfYT0m8rdvjOwzxsJL+mv0qnN0qOFbEx6s367c4WDxIplcuh9930gsGR/Ttqvel0U0SxVt6Y1mErnAEnecFuN/3YXWj4ON1/BAfL58irp7DTuHbdQvoJWfxq8T44O+myJf6JtvPjtadQvCrvhU8uP1wfXy/sXd9v/VJ8OIF4pY4krIIz7AfVkS9afMC/Sb05bnn4gHianka/6aHFF0Il15K/3sGDnmZHa3HH09Up7pZH6t4mHsoXJ0O58Ld1bfoq1rEP+6TP3byJ/vwFx8p/z+v/jUDXm+CQ8ap6wxiv86bP1yd7mT7MjeLKyF5RD7abH+Kpv7qpxH9nfq5NqWoR3RrY1yi+8jDT54j/ydxY6Z4drQ8Xc0/xOMNbemtp+g3vhA/mOQ6l0XEX/Wyr3yPuES8aQ//X4bnH8EPbmIXv9IdLoAv9tlHDA+v7wN3reGPpTF0Xfb1t77OZnjlIM+30nUXq9OcEvy+4oDjlfQcz1XvuDw+gc4Kj7dnT/SiVZPN52HmqTGOzqC+O4zu8aJ67iHqqivF+bvl46X0ibbwpn2NypvUp46Lo5fAiY36iv+EG7bq27yE322T/++gd13ieWr077Cb8mXwxx/6sj9gXxfKE1vgtFfEt53qGt2MZwbe3Ub+nw5H0Nv2r8SfTpYfb49Rn/feT8J/x7nPt55XP13SJPuInAF/45+FVXDnBvdvz85y8HC6Ttoe8c76Wyk71EvH8scu8li0nwBfmU2nWW7fluVPxNHFWuEJ5vMu+P9l+elEeTuL3f1MvxiMN8C3oUP52SDx+2DfZ+grT6YflNMhywepe6bp079H/Ld/ZwG/Suuln+lmdqHOPSPL+iLi4P7/eFUwXtbjdb+MZ+Cmufp3b8AH7T/a7PnTn4YDHWvolE1x8PLRwbF5GV3wKf257C9jtriyRL2ntz6HU+PU38PqYOwtqgPv0ve0Lmx/cPWz8/D8t/28xHo73mPuEXQi41V/nvf9g9+Vmjf20njA3/UQ73+M7t8q3nwoTx2LZ/vuLbdAnIzRf7GfLoCfV4bpG/prqpvZVxLcQH8ofDAGDlBv/dNzPqc=
*/