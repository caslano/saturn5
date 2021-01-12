/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_SUPPORT_AS_CONST_HPP
#define BOOST_FUSION_SUPPORT_AS_CONST_HPP

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    // A customization point that allows certain wrappers around
    // Fusion sequence elements (e.g. adt_attribute_proxy) to be
    // unwrapped in contexts where the element only needs to be
    // read. The library wraps accesses to Fusion elements in
    // such contexts with calls to this function. Users can
    // specialize this function for their own wrappers.
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline const T& as_const(const T& obj) BOOST_NOEXCEPT
    {
        return obj;
    }

}}}

#endif

/* as_const.hpp
918o/pN67r9Jv35T3qP8Ixn3DlVIe9wl5TZIf5Px/M5J/fqLJ0s7NOrXhveL/BNkvpF4uueHMv5Jeb9+sbS7pN/5Pqmn1P9BqdftEhdORcaJlIwvd4kdL5Brs8SL5Lv4conDnRJvfxK9ErcXTst7jGSeDyrS3r+WeUHGoyvvlX7xF5nnG/Xrr2+VfnpUxre3Sn//ncTTq/Tr92XcvLFA2qFM1g8Pij3vlv79DpGXeeE2ee/R
*/