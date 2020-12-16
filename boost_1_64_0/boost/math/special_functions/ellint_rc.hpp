//  Copyright (c) 2006 Xiaogang Zhang, 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to correctly
//  handle the y < 0 case.
//  Updated 2015 to use Carlson's latest methods.
//

#ifndef BOOST_MATH_ELLINT_RC_HPP
#define BOOST_MATH_ELLINT_RC_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>
#include <iostream>

// Carlson's degenerate elliptic integral
// R_C(x, y) = R_F(x, y, y) = 0.5 * \int_{0}^{\infty} (t+x)^{-1/2} (t+y)^{-1} dt
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T ellint_rc_imp(T x, T y, const Policy& pol)
{
    BOOST_MATH_STD_USING

    static const char* function = "boost::math::ellint_rc<%1%>(%1%,%1%)";

    if(x < 0)
    {
       return policies::raise_domain_error<T>(function,
            "Argument x must be non-negative but got %1%", x, pol);
    }
    if(y == 0)
    {
       return policies::raise_domain_error<T>(function,
            "Argument y must not be zero but got %1%", y, pol);
    }

    // for y < 0, the integral is singular, return Cauchy principal value
    T prefix, result;
    if(y < 0)
    {
        prefix = sqrt(x / (x - y));
        x = x - y;
        y = -y;
    }
    else
       prefix = 1;

    if(x == 0)
    {
       result = constants::half_pi<T>() / sqrt(y);
    }
    else if(x == y)
    {
       result = 1 / sqrt(x);
    }
    else if(y > x)
    {
       result = atan(sqrt((y - x) / x)) / sqrt(y - x);
    }
    else
    {
       if(y / x > 0.5)
       {
          T arg = sqrt((x - y) / x);
          result = (boost::math::log1p(arg) - boost::math::log1p(-arg)) / (2 * sqrt(x - y));
       }
       else
       {
          result = log((sqrt(x) + sqrt(x - y)) / sqrt(y)) / sqrt(x - y);
       }
    }
    return prefix * result;
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   ellint_rc(T1 x, T2 y, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_rc_imp(
         static_cast<value_type>(x),
         static_cast<value_type>(y), pol), "boost::math::ellint_rc<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   ellint_rc(T1 x, T2 y)
{
   return ellint_rc(x, y, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_RC_HPP


/* ellint_rc.hpp
dXv7jGeFug/+GXaD/78Lp5+Ar3pNvhmr3re/DM9U5T6WHWbcovi7JHz/InrES9hxJ9zxa/HjeH51Eh7o7rAN/CW+a0s4fqi38ZL6ElNS063zy0jqQ15lz2PFqbiv8CE/cL8FxySvs6kRz+O9WYlf0p2uw3tMxAvQ7RRPx/f+DR/Zj55iqfWBUb4+ODXEVXhzMF5+hHx9jjixHX43r9Xt5gX/O/iN6HrC+foG4HHoYtVF5ZerazYZx5PwIKuT+1u9D77sj9bLxricvn7ucP5Bl9Lo+ocM5Jf8oQh/Uvk6nPwaXISf6/R+hjXwVP2T6jDHX12urykOTcFrtsjD7UcO6JcI81GvP6v/3/Q53UmpPGQ9we7+4vHTcM5YfHhUj6eFvF+Il/sTHTNevLY97ifhb1rpUtlX1Wh5hs6jeYD9xnWY8cl8Gk5iz13l9DZ57MP75fKfMs/0fynx+zDh3A7+0mVeEkXwr+c1lOABSvFuWZn0N4v126fT4431npUF8od+ZPZT4u+z8pv4VTtT/gm4PezH25U9jM/wvpD2nfQFj+F78Jm78f9z4/ev68cULKbb6REnvzXPjew7fk+f+2rADw3+MNSlgadl99el0fupcw7DG5wr3zyPp4/en/SXlGg84MhquGntRa4v2Ef4jKfpKYPfHhUX9VXbxqu7ptBt/Czg7VDn69f+ix+vo3P8r/Hqkh+3husP/C+88Gf1a/x+NX3JHWfpD8X62GvFsVR+kZvEx12PwFHea1B0YDqduT7dJ+oauDUfbqx+0fXdrS8S84hX+l25+hafXDJLvnpBXM1nf1fIaz8L+TKs46Xve955OuDFOXSb7eqjWOd+Ycyrit/4osxzxJX9rI8Jfh7232184ahdl7Gf4Kdh6zmve/AMC2dbD99k/Od7D32hvFzObr6I+OBw/GPUpacl1y8NG6k+oHfLX46f6havonrjx+E6Y7/4Kz9fYT1AHM8myL9wfcE7+BJ6w2XReo7UcLzb6dNq4XF9jOHN6n7nydysX9omT8Tr6TYa1yL+vk0/9A48zEXwVZe+CJ3q4G/YN56sEZ9Seon68hr+8lP82za480S8Gb10y3n2ww29N8CV6rladjPa+sKEONTxX324A+W/1X6fIW+8rZ/aod6In8dwv/wSvVciIxw3wtlp4X66xacL5IlqvAx/GbYj6YdzL6eDcf3D72Nf+PdGcajqI+O5m17MeNZ+Ky834/G2yY/mo8x8dtTRj87QF/yt44c6NJwXPqx7QZ2Nz+l6nC5ggOt7Vl6tsx5l6f50NPSqF4lbqzL5Pb/LgMusBykpps+7Eb6lv9vzArv1/+wquq2fsJtv8dzyzqdp+nXpYRvyMhzn91nq8trj4DJ1TX7Im+F84n/TyXSDP0/OX9lNcC3cV2j9f+5yfNgxdJP6YYPn6m/TDe6Y5/kUEd98RJjvc+XniG/aL5zvR+qHq9WDvfjvWCeOB0jJd79lcNSb+7se6+LvpU+K3z+fR3f4cgZ8zc9q9BlL8Jmltkv0TfFFu/eqm1x/m3W9C37Oz/7HXx/zHmR2MHyvOHsDHuFG83crHiCfX67D+48Sr+fgA/A9RbFeNsX6r/nJ/Nsd3VdqOO+/EtYTsK885zdPLeLU1Hfwruw5/xJ5+Tr8+/n0pfDA+E3wl3W8nYEnD5/xcnn14fsBN6hvpri+AnqlDnHDdReUiYMd4o/nIWxw/GG74eT56tXf8O+36Bo/1N9cIT/G78m/L2yDToAd7jGvO43fm67zK/0luKV+gTrG+5hW708XUw5f3sqeB4g/8FXWn/iX/m+tuqTd7/NWWXdnWwS/N8J9yzbBFdE4HxK2bXijJ9UjM+hrDhI3ctQ=
*/