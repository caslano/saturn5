//  (C) Copyright John Maddock 2006.
//  (C) Copyright Johan Rade 2006.
//  (C) Copyright Paul A. Bristow 2011 (added changesign).

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SIGN_HPP
#define BOOST_MATH_TOOLS_SIGN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/detail/fp_traits.hpp>

namespace boost{ namespace math{ 

namespace detail {

  // signbit

#ifdef BOOST_MATH_USE_STD_FPCLASSIFY
    template<class T> 
    inline int signbit_impl(T x, native_tag const&)
    {
        return (std::signbit)(x) ? 1 : 0;
    }
#endif

    // Generic versions first, note that these do not handle
    // signed zero or NaN.

    template<class T>
    inline int signbit_impl(T x, generic_tag<true> const&)
    {
        return x < 0;
    }

    template<class T> 
    inline int signbit_impl(T x, generic_tag<false> const&)
    {
        return x < 0;
    }

#if defined(__GNUC__) && (LDBL_MANT_DIG == 106)
    //
    // Special handling for GCC's "double double" type, 
    // in this case the sign is the same as the sign we
    // get by casting to double, no overflow/underflow
    // can occur since the exponents are the same magnitude
    // for the two types:
    //
    inline int signbit_impl(long double x, generic_tag<true> const&)
    {
       return (boost::math::signbit)(static_cast<double>(x));
    }
    inline int signbit_impl(long double x, generic_tag<false> const&)
    {
       return (boost::math::signbit)(static_cast<double>(x));
    }
#endif

    template<class T>
    inline int signbit_impl(T x, ieee_copy_all_bits_tag const&)
    {
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
        traits::get_bits(x,a);
        return a & traits::sign ? 1 : 0;
    }

    template<class T> 
    inline int signbit_impl(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
        traits::get_bits(x,a);

        return a & traits::sign ? 1 : 0;
    }

    // Changesign
    
    // Generic versions first, note that these do not handle
    // signed zero or NaN.

    template<class T>
    inline T (changesign_impl)(T x, generic_tag<true> const&)
    {
        return -x;
    }

    template<class T>
    inline T (changesign_impl)(T x, generic_tag<false> const&)
    {
        return -x;
    }
#if defined(__GNUC__) && (LDBL_MANT_DIG == 106)
    //
    // Special handling for GCC's "double double" type, 
    // in this case we need to change the sign of both
    // components of the "double double":
    //
    inline long double (changesign_impl)(long double x, generic_tag<true> const&)
    {
       double* pd = reinterpret_cast<double*>(&x);
       pd[0] = boost::math::changesign(pd[0]);
       pd[1] = boost::math::changesign(pd[1]);
       return x;
    }
    inline long double (changesign_impl)(long double x, generic_tag<false> const&)
    {
       double* pd = reinterpret_cast<double*>(&x);
       pd[0] = boost::math::changesign(pd[0]);
       pd[1] = boost::math::changesign(pd[1]);
       return x;
    }
#endif

    template<class T>
    inline T changesign_impl(T x, ieee_copy_all_bits_tag const&)
    {
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::sign_change_type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
        traits::get_bits(x,a);
        a ^= traits::sign;
        traits::set_bits(x,a);
        return x;
    }

    template<class T>
    inline T (changesign_impl)(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::sign_change_type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
        traits::get_bits(x,a);
        a ^= traits::sign;
        traits::set_bits(x,a);
        return x;
    }


}   // namespace detail

template<class T> int (signbit)(T x)
{ 
   typedef typename detail::fp_traits<T>::type traits;
   typedef typename traits::method method;
   // typedef typename boost::is_floating_point<T>::type fp_tag;
   typedef typename tools::promote_args_permissive<T>::type result_type;
   return detail::signbit_impl(static_cast<result_type>(x), method());
}

template <class T>
inline int sign BOOST_NO_MACRO_EXPAND(const T& z)
{
   return (z == 0) ? 0 : (boost::math::signbit)(z) ? -1 : 1;
}

template <class T> typename tools::promote_args_permissive<T>::type (changesign)(const T& x)
{ //!< \brief return unchanged binary pattern of x, except for change of sign bit. 
   typedef typename detail::fp_traits<T>::sign_change_type traits;
   typedef typename traits::method method;
   // typedef typename boost::is_floating_point<T>::type fp_tag;
   typedef typename tools::promote_args_permissive<T>::type result_type;

   return detail::changesign_impl(static_cast<result_type>(x), method());
}

template <class T, class U>
inline typename tools::promote_args_permissive<T, U>::type 
   copysign BOOST_NO_MACRO_EXPAND(const T& x, const U& y)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args_permissive<T, U>::type result_type;
   return (boost::math::signbit)(static_cast<result_type>(x)) != (boost::math::signbit)(static_cast<result_type>(y)) 
      ? (boost::math::changesign)(static_cast<result_type>(x)) : static_cast<result_type>(x);
}

} // namespace math
} // namespace boost


#endif // BOOST_MATH_TOOLS_SIGN_HPP



/* sign.hpp
JZvr+yOkmRF9ozYoM2fzTWJz8/U9Dwo0GBGo6D9x8mTkM5ZLpKYtspRpMWJB5F1qTpIyC6LvFp8EeWp0Ka3X+Qfq6k2fBdMvmffvxv/K6fo69GV15BrsMH63vJyX5vp1Y8O9tD3QVtC+XeKn89UYLD8bCuz6n+xbpDiiSeS18iRNkTpxpgyP1Y6zX+fx2+Xkf8lvtLRNmgo95sQ+ZrxJUnqd8fqIrynRpmXfYdPnBzYY12z9z7w9DqnQZc7Gu8UiRZkusbp9pCjTZcHWe8WkSJMxkfeFAjcmRZ0Tbe99WE3ep15vlr9tmiJ14t7jRbvq9FF9bhn3j/937f7Qczf/sHmXEouFx5sN9eD6H1BnFmx/0JiS46wPmV9NY/kR15A4BfKnsViy9Unnc8DWp7zvSoYCZ4vd9H+JsvI4sQ0fhty3wWvyaXti1tgR91jc3MfMuY6+3MsPzh2/adv7oNi0mtqSb50hRW20mXHWaR8/LIY2M/cLBfqPVDvbY3ZJil+iy4IN+e+05Ki9xSf+ey+C0afVyHmN9X0hVnQ/qr2WGuhn2XE5x0TsT6nRjhgrKmIMPd8RI/EBOVJno+V5es5rtP97D4Mz75dHw/kf0bbYnY/99z4LE+fGPdduGA/P7Xpu/DHHODf8aXVqypE0h2Le62P6LGbaeeHO6ecHc/b94jS8Rjo/4/yAuLuf0OanxfRcWE4jz5U/Kp7nMp7b+zQdManQYUzwM8aHXdIc02XCzbv2f0EfKNJgxIqtL8qNE1Zs9eRNiiPqzI1V2P+f2fY7qK6vM44r0eLMNbymsHP6c0rbJSd+FhnyHn32dbUfmJskKNBiRvQbziHFMR3mbHxTXclT54Sjb/uaPnMi39F/+iOxiHxPHpQYMfyz/v5FbIo0GDAn8lfHEifNEU2GLIgu5cseWY5pMWJJ7G/mO/sMWazX6t6YPbIc02LEktg/jAELeR3+zVjKo3Yaw74sJRrr9bpn2CNHjT5zous1ugkKNBiyZONf5jtJjlivz/U7C+PJ2RyQp0qHKcGAvwNgm322zukzvG2JBgMWxM7hMxz7HFKhw4TgOW0JnEssbs6+x2edy+saSfbO6XuFbcb2iAYDZozW63Rj6zW69yJNkSodds/t95AUqLIt/sFQf6jSZWo+hL+rftyLLMe0GJFW+8mXXXdfUV8O+2r6VePChJt/7b/3jTghIN4mZzMh+G3XLjukWIoXW9/DYZ8c2/6fZKJrvzY68hvLO7heP3xj+w44osU1TtunxogVW/KJU6HLlIS8irSJyi9JiTZnXFtxslToEpH7GfbIUaEqt/j39J8mSza+r2+kOGJJ9AfmPfciR40+c2In+scBJTpMCf3QOeyTo0qfBbEfqRcZyrQZcebH2iDDMS2GRMaeY/tn2uGI9qlfmu+/dv0zZMWe+ZKmQIcq11DnCSti5zGXiHN982KPMl1S9k3UL6Reze+LScncaJJdrzG/vteu1r38jo4Vm/cW8z6e+9h5A8fyKU0D/hZIf+kyIWD/WbSm+smS2K/MERLU6DMjog/XZ4+t36gHZ/6gjkzX9zq4MQkKNBiwIPYnMUlxxIqNhX0s1vfdWCxs/ywm8VPySjMmMNUmu6Rore+RsO+cQyr0SPxEzen/NOBvjLRFVm5lOtR+GwzEx8aRMm3GhH+ib+QZEVzfo2OXNBXmxIxtU8wRKzZn5iQpjukwJfpbfSPJES0mhH+nRiQ4os2Y8PreE/sUaHBCcC4P9shRZ0jwD/L5sTaeoP9USD1JTBIZ7Wbx/Sx/Pn/PQIsRS6LnN1fYI8MRdXpM2Dn9HTJnUeCAKj3O9jOrGoPrindDsU/b6Krltf0MiDkb67W3JxQ=
*/