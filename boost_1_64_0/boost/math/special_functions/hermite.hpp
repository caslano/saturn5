
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_HERMITE_HPP
#define BOOST_MATH_SPECIAL_HERMITE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{
namespace math{

// Recurrence relation for Hermite polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   hermite_next(unsigned n, T1 x, T2 Hn, T3 Hnm1)
{
   return (2 * x * Hn - 2 * n * Hnm1);
}

namespace detail{

// Implement Hermite polynomials via recurrence:
template <class T>
T hermite_imp(unsigned n, T x)
{
   T p0 = 1;
   T p1 = 2 * x;

   if(n == 0)
      return p0;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = hermite_next(c, x, p0, p1);
      ++c;
   }
   return p1;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   hermite(unsigned n, T x, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::hermite_imp(n, static_cast<value_type>(x)), "boost::math::hermite<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   hermite(unsigned n, T x)
{
   return boost::math::hermite(n, x, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_HERMITE_HPP




/* hermite.hpp
NO49x3xu8Vxzvg+erXb3lPbK3q7xpVXt8xfqb/6icXLRJHNe5arHP9P64ttVz3Q+z16lco9qHHq6Of6A8jejXuN33d8X6/6++dcaf37InN923Wc2qV7dqXnsVoVbbVG/2K58+DXu+KH2Vn6XVfdN9Xdf0Xxtne5LO7VuNl31+CKVk9Zjpv9J13Om7sfqz5dpvPzm6zVP+Zfmhz61qx9oHPINrYt/T+NAzWfOe0LtVP3a/Tdp3euDFq3vaU/Xm3Tf0318/1+naLyu8Z7mG/NVP+e/RXs8a55YtEj16VaVwzU6PkfzZY0LZ12sPeUdWjd6TP19m+L9ga5Tv/qHHTqf95nrdP028/kH88qP1tX3qr+bcbHuQ1qHv/5crRvoec3mv+p+d0T9xvMaVztM/Avcprznr9I6/zu1t/fz6v91npM/pXHYVzSv+Y7mNWHNK3zqv+ZqXjFT97fn9dxpquY3z5jwO0s1vqhWP61x6bJ9uv85tS6r8fnm+/Sc5bOaT2v+NGeBxqeaR29cpz2UJ2ucv0Tr3g9r/Kzru1XXd8/PTfhHvqvnQRpfzGkw6T9xmeZr12ie+0Xdh+aZ3x/RutOS92rd7Hn1x3outPOgiX/7ErUrjUtmbFe/Oct8fu4PVc4XnaZ6r71sD+s+8qzmF3/Xerfay7NlWg+/VevEf9F1iqlfVX+6uFb3b60rzwioHz5g0ThWe/Lqvnh4pvawrVf5O7QOofWwrX/Vcz+tqz9521mmPGeb358bXxd6Tv3KHO3Vq+s8T+uUmzo1T/m9+uunVP6zFP/dp5nwOt97S5XOWzWvuLrYlMN29YsblB+Nkx/Rev+iWVov13OXjVq/ffAL6j/u07iiRPViv+LRc8MNf9FewTO0TvK01qteKVL90XObTs0/rp1sroPmTytatAf621TuQ0V6jqI94i9Vvdb94NyLzfsrdF+aU6R5v9rtA1s1j7hkiol3ofq1SzV/1Dr3tpfN8fN1faemdd7X6zov0PV9r67rc+b9l7QeuUTrq5d93MR3fZmJZ4322t6i/Oy5XO3261oX0Th20VLz+4v/0jrVdvWb90zR+HKK1n9MvlYMaHyb1Lpyh+YRlRovPK95vp77bdB1euppE/6lxBQTbq/6y/lWzbc0f/iS+tltGidpz/PNz6hdqT9Z0KN+4g4959a86M2XarzwsvrTmepH36H7XlDPk5/Tur1V92+tc296QP2U1kF3/1nriauVnmuKKed/qP9Q/7Jlm/qJ99pMOudoPaZP7eZsrSf2aK/5b6icd+l51Va96jpv0rh39k6Nj9dpnL5N5X69SX+rXfM/je93fkPPW27V+OeaIqWj54Iv67nK33WfP0fjv4Ceu2jde2fSpLf3g+b1+gVa13ybzcTXqHo5Q/eP2yeb9n/rmeb396l+Xq5xn9r5mpdUPqfp+eBFmpdfZ8KfvU7xarw0/RETfutnVZ4h7fVv13M5zW/vtZnXZZdo3DJd99kztWf6HpPOvU9pvVLPl7cfVjtJa979oO7vHfq+wV1qX30ab5yp6/R1jasatK6u9Ga+rPBaz39Qz8Umz9FzBKW/46DGQVWqH2MaB67ROvyw2uMbTTp7NmvdQf3yoc9ofW651mn26botMr/ffLX53I41Jvz2KfpeRljPl9VON87Tc40HtE50UPP3A+o3rGqXHs1Pc7offG2KCXeneT20WuPAc4tNOK3v7P2FxjOXmM/vfOp0Pe/QuOByzfu+ouu/X/3vLu3ZPkvzjDb1I33a636r7pcPqx19UutPOzRuu1b9zzVqR7q/zrhD6xd6rn1Az4H2xrVuvsBcp8lZPR+6U/cTXafNmves/u5kc751Ws+ZrnUgtfs=
*/