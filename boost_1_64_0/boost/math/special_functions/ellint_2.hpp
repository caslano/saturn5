//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2006 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to ensure
//  that the code continues to work no matter how many digits
//  type T has.

#ifndef BOOST_MATH_ELLINT_2_HPP
#define BOOST_MATH_ELLINT_2_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rg.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the second kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { 
   
template <class T1, class T2, class Policy>
typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol);
   
namespace detail{

template <typename T, typename Policy>
T ellint_e_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_e_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    bool invert = false;
    if (phi == 0)
       return 0;

    if(phi < 0)
    {
       phi = fabs(phi);
       invert = true;
    }

    T result;

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>("boost::math::ellint_e<%1%>(%1%,%1%)", 0, pol);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_e_imp(k, pol) / constants::pi<T>();
    }
    else if(k == 0)
    {
       return invert ? T(-phi) : phi;
    }
    else if(fabs(k) == 1)
    {
       return invert ? T(-sin(phi)) : T(sin(phi));
    }
    else
    {
       // Carlson's algorithm works only for |phi| <= pi/2,
       // use the integrand's periodicity to normalize phi
       //
       // Xiaogang's original code used a cast to long long here
       // but that fails if T has more digits than a long long,
       // so rewritten to use fmod instead:
       //
       T rphi = boost::math::tools::fmod_workaround(phi, T(constants::half_pi<T>()));
       T m = boost::math::round((phi - rphi) / constants::half_pi<T>());
       int s = 1;
       if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
       {
          m += 1;
          s = -1;
          rphi = constants::half_pi<T>() - rphi;
       }
       T k2 = k * k;
       if(boost::math::pow<3>(rphi) * k2 / 6 < tools::epsilon<T>() * fabs(rphi))
       {
          // See http://functions.wolfram.com/EllipticIntegrals/EllipticE2/06/01/03/0001/
          result = s * rphi;
       }
       else
       {
          // http://dlmf.nist.gov/19.25#E10
          T sinp = sin(rphi);
          if (k2 * sinp * sinp >= 1)
          {
             return policies::raise_domain_error<T>("boost::math::ellint_2<%1%>(%1%, %1%)", "The parameter k is out of range, got k = %1%", k, pol);
          }
          T cosp = cos(rphi);
          T c = 1 / (sinp * sinp);
          T cm1 = cosp * cosp / (sinp * sinp);  // c - 1
          result = s * ((1 - k2) * ellint_rf_imp(cm1, T(c - k2), c, pol) + k2 * (1 - k2) * ellint_rd(cm1, c, T(c - k2), pol) / 3 + k2 * sqrt(cm1 / (c * (c - k2))));
       }
       if(m != 0)
          result += m * ellint_e_imp(k, pol);
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_e_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (abs(k) > 1)
    {
       return policies::raise_domain_error<T>("boost::math::ellint_e<%1%>(%1%)",
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if (abs(k) == 1)
    {
        return static_cast<T>(1);
    }

    T x = 0;
    T t = k * k;
    T y = 1 - t;
    T z = 1;
    T value = 2 * ellint_rg_imp(x, y, z, pol);

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_2(T k, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_e_imp(static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%)");
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const boost::false_type&)
{
   return boost::math::ellint_2(k, phi, policies::policy<>());
}

} // detail

// Complete elliptic integral (Legendre form) of the second kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_2(T k)
{
   return ellint_2(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_2(k, phi, tag_type());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_e_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%,%1%)");
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_2_HPP


/* ellint_2.hpp
RPpSdr8GP1+nv1T9lxCnwvsR2M1nxsnvFj6uTr0Un4EPqPT90rPYw8POE+my0sP4DBJf4ZOmLn3XSNeRGsbrbHX1SusgJlm3ugUO138ZegX+5FP42HPK8q+OcQ2c3W295oNwRT/+8YskLt/TRZdxhTo8Xtc1FO7IgbMPTtaZvR/zC+erZM979u8PH/Krje4f7q2ZxU9c9zJ6m+478Jd0uIla63jL8TbsrQ2fNGVnqnWIeLhL4G39w95V7Npz53cVup7D4DTxLqtTvlJHr434ycxgn36fjS9a0SMOVtBl1+MFT4YjJrAX9VnRh/iwJeqU/u7/E/XG2fSEd8Mb+IKWp+m559P9wW+99Oe5oc4L2zgexfztBnn0efHyf9Z7TLH/nViPxu/eSujv4yEnWS9QJG/h5avobDMT8MfR4lYpPZZx/xSf3nYHPY141DRDH+dK820ehhvfDnV8/n+soyvBFy1I8lg9/4zXJbr/I9TH7+Id+FHzaO+DM867m9gTfVnXz5J23h3sJ/yfbjPnK/HmG/ip0XjfZl1mBr1QuvH6UpzZzv6uURfG7/myTjTxE7xnlB9Sw7gFPi6cd2Y6npOOeIO65vmwDeu6+J9t4kX1m223bdbL4r9t3cdwCL6+lJ4/JV5nhV/79B33d0q4rvB+Oe+VgHOK8GMV6oVM+GKX+NUlTgydSS99GP/Zzq73ir9niVtzxZlNeJt09lmgT4BP6MGzrWY/g8/AT/zZeppzxH/na3h/QFLX8LK6rJG/0YFVmKfcu93vDDx1l7h7GXy+Vf/4NX6yz7qmFnbNv1rUJXnX8BOfq9V1hcfjtZfhd8L67vD7heLtB/pDI9X58uJQvHfWT/FD48WXiC/ZGvjmB9n5sfoMJwzEs+8vv4pn+OysDrjhWH5Klz/ce4rX0vP0jjVP7LTuXfm82Pmb6W+OwMe6vrL1meoi9f9t+hC7+Q8/yuZHha+pD/BM9a6zwLxOWY93/6n5+LXfXw/P34sHWMofw/yE/cW+38pP7lG3/9M8jRN/Ih3RfuH+6ozXZueP1neeHexrDrycKi6JDzX58vVZrsd4FPY6T4Sri1Kj89TjIy6gk1TH9xrHvEmx3QX8EfCLfKiPnetzlm3PtdYF38XP+xnnaH9quJ7R+tqLjPd69ub/5f9VH/vc9uOkny/wuQqvV+25Aqs78N7T4Bj8TYKfVnYar3J64HJ9bccpflL9+3O86LfqmLPp+egvck+TJ1/XL19k3A7np9dleA9xEm+15GSIA3R6P1Knev5pGZyVqw6sP0EesG6i+0o4bpTzbsa7X2O9e7DH8HkOHv9PeMuN5i8DDne9NeJOU7G4O15c3uS4qfjTH+jTnigv9OCBrAtcAM8WXq4fd7r89pDjX0tXlaPu+0a/a6b4jT/agCeqGaduSoOj6YHa1KGNg/Fu6sfu56wH2Srffha24ff6Yceo536sbuGXXXfhQZrh+vn0BPBGl37jgr36hTvpF/hP/XK80QfqyMnqN3qAIc/z25nmYaY6jv6t4MfyyQEDHV8epi+suER8Mt/Db3XdM/FZcG9FFnx6Iv/8jL/8Wr9BnNwxV9/oGeML/y58C47yuadCnJgIX9vfIM7npqhP+8kT8XvHNiWfq5Oym/2rnzrPUC9V4R930LWeAN9OHOC8/AuvslZeqCh2nQ/oEwceMJzvVfnxP/jHC/Fr3hcw+Cw892L+G+l8soOdf984ZMEtOepBOLa0Et4qUvfgm3pT5M857HSCzxfDge4rcad4Jm+vCPMWzovHa7oPb1II94r3JZONj/zckamPuV+69ZXWH97DX1+jJ8GPzc3Bl+DnavEyLRdmWKcOX0+gTyiVvx+HN2Y=
*/