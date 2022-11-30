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
        typedef typename fp_traits<T>::type traits;

        typename traits::bits a;
        traits::get_bits(x,a);
        return a & traits::sign ? 1 : 0;
    }

    template<class T> 
    inline int signbit_impl(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef typename fp_traits<T>::type traits;

        typename traits::bits a;
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
        typedef typename fp_traits<T>::sign_change_type traits;

        typename traits::bits a;
        traits::get_bits(x,a);
        a ^= traits::sign;
        traits::set_bits(x,a);
        return x;
    }

    template<class T>
    inline T (changesign_impl)(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef typename fp_traits<T>::sign_change_type traits;

        typename traits::bits a;
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
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
*/