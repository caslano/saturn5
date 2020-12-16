//  Copyright (c) 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MATH_ELLINT_JZ_HPP
#define BOOST_MATH_ELLINT_JZ_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>

// Elliptic integral the Jacobi Zeta function.

namespace boost { namespace math { 
   
namespace detail{

// Elliptic integral - Jacobi Zeta
template <typename T, typename Policy>
T jacobi_zeta_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    bool invert = false;
    if(phi < 0)
    {
       phi = fabs(phi);
       invert = true;
    }

    T result;
    T sinp = sin(phi);
    T cosp = cos(phi);
    T s2 = sinp * sinp;
    T k2 = k * k;
    T kp = 1 - k2;
    if(k == 1)
       result = sinp * (boost::math::sign)(cosp);  // We get here by simplifying JacobiZeta[w, 1] in Mathematica, and the fact that 0 <= phi.
    else
       result = k2 * sinp * cosp * sqrt(1 - k2 * s2) * ellint_rj_imp(T(0), kp, T(1), T(1 - k2 * s2), pol) / (3 * ellint_k_imp(k, pol));
    return invert ? T(-result) : result;
}

} // detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::jacobi_zeta_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::jacobi_zeta<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi)
{
   return boost::math::jacobi_zeta(k, phi, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_D_HPP


/* jacobi_zeta.hpp
aOg5+GS1972BP86i40xTZw3pZ0i1D1oDXXy3I/5WkCqOp9JHY/CQLfrarqGTrpcv98B/3mf1qLD9hcW50Xif/Zvm78THDjbuqfoAV5rnCD55uTjse5mGXup9y/R9dIID6CCb3oioK8Wox8HhIXXgw40fHlUH/zaOURfb1Mq6tfTwfeJVJ3FuKLvjT9lZEfu/uV4fdYwhreFrdRt2kZIsTtALim/TD2Y/mPZleEpb330dqT53Ix5bzX+Xig/R4xJ68Rz6dLRf7E19yW+Y34jvH8YmwHf4Zt+IvjC4fLI+nnbe+2J53njEq2fm79APdpvxLtC3cKm4/wr+0k+faQZ/8v4F/8Db3dhJtG8xkd72ND+aLj4ewPOG0lHkx9KV4uO/+h6a8Ze/onkBjtMn1HIQXNIQHLN9/zcorI+mv/Wx8vmzuJcWpnemsrsJcA6dtOlpcfgn/r1PneIk9R/5u734shAOSVSXKb1G/DxfHvia33eQZ54QR96Psf+z63RS90pznx7ybQxdjt3Xwt25n9Kp0tXR6ST/bSsc/PtyeTQ7uk97mL3KRz3gs5706wZ59FjXTWEXx7Ffz5HqOZZPox99R5dXhy/smMBv9d3Z77L4EnFlDt4jL1autr/Y7exUHFwtT+x/CU7MDe6XF+vvh4jXvaL7cau3fWMftB/g9K3iUXSfct9ZFKSz2936V/G6iHpBczKc9LV5WwUXssOmNsYjyXjMDMm70fU+8Ocz1VHUM8vMd8624Fg7XL/8qXTwQfLZbDz6MX67F86I7ju2SX20JT64D92r4Q7PsVt+e4Veeh9e4++T2OP8MeLLSPES/6iAU6ramwc68ezOcFhE/+dAuq/vrecms79zYvQdx+mjUaedIM9/pL/vHn4zWL/Qreraf+GfX8KZx+Cf3dUJ1IsLYo3H8/zkRHq0/uRNZ1kPaCy/ebKVfaPgpH/dz3VmHOJ+eN32Ae3wan6sn75F/bmkVH7Zi0d3pjfjvdlr4avTEvAo9YLp4sNn7GuUcZjMPvDtsg/114bZyTj6fovnf87vrQ+3oQNeeia/vBZuOI399rW+Blw8wT5dtYe2tv4i/8vVB1YqLvzCDn+TNw71nAvk0w7qb+azwT406ReK09/TiaPfNX2gPviYecLvKpbQQ8+A3zr6Pry7+kU9u31X/Cpoa58Cum8P87zO9yzDfAd6m/GZH93HOhyM39386F06DX5dcor7w7sb6BGRB/nRlexiND5+ifxiP9Xt8/UnqJ/OmIBPzLfOcIn6FX5VI181zBPP6eGRVuz7HfM1Tf/J6fTbETHiGF1hHF6krjFhXiQYd/m423kx9tHR36W/sby1952hvp8hvw/AJ8WvpEvMW0f6ET2l+Sh+8yvdpLptcJ5xyxlIV5fva7rQA7Pwl3PZ52H0CfkhJ5EdvmfeUz1/tE8qWl/ZS/+J1v9utS+wfJ/7PT4FlzYky4/b8dGnxM8l8l4Xerz9axoG0Q2OgetuF886wYXiYO697OQUceV+vO1ifa7Tw+ps6rX8ouZP9YV/jAf+m3oGv4vA7RfSz5vx68Hsdgm7/FZ/9Y3qd4X6Be2rm5ytDvZFW30m+tUv4p8Xy4ftxLlkusEGeARfy4HjascmOOLd++Bgfrk5JThGdsFjf/Ln04yP92s/MC44xnnuo/Rxet+krgnBcVaMvg99I22i+5Owv4/1QesH29/efmNb5CtxrmAj/3pP3yE8ln0K+6iP0ydjfYsB3hu/249HNl3h+eyLURcLZ5TghUeKW7X88JLoOtfmuw/djj1mHUZ/P8O8TbKOSSr8/Sud9Gh9KuJhSW969a/4CF1j/9HGOdl+Hm+oC++U35Pos7/H6m+j7zY=
*/