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
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
*/