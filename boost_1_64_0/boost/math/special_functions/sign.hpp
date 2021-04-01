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
bbej16U3v2ZHowV23u3Ol3iWd9yTkYuBqir6UmR89HU4DZABpafQROOTd2hC/yitNB6QHYPUBa4L3RdTrR0aMMxsaW1SzT3LokOvl36RwMmU3XDFPgR6/l73f25LtBtoxcNfcWzT+KOCRmVYC89M2k9H48k2jCrdNj/LA82ynH6sA4XhV0qAfGX5iyY01ZnJliQvKD9qt7gMmXEW+2CsmP+MWo1/Syat8sSG7dpRW2cT9RQ9YUmV02LGh9gyxuikV6pBMp3+otCXDv/YlULAySsmZ1xb0yGDmJBShzBOHtHRvF4qS2/RX+/BGWJYLxS0qNPS+57zBsVelSRFTiX+tle7wVPchKs3cvCU0boI507+h7g9sUdjdIbSD6GBnOZ7kWzLVjWpULyPBfXPuVKRGtlCzUdms59roVwzFU/HrJzgR6gv/26yhKO+eWuLFCnNq32KsO0+5BfA5/WneHGdEDx5u73bNgLY5bgvu64vpb4NBacokXqkZtfkkPJnC9v7xVBQsl+nYftoe5Q2stkuwPTFfe5Gk72iBv/PMo5rxfRsB897+wrci8ZPyg==
*/