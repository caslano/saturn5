/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    identity.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_IDENTITY_H
#define BOOST_HOF_GUARD_FUNCTION_IDENTITY_H

/// identity
/// ========
/// 
/// Description
/// -----------
/// 
/// The `identity` function is an unary function object that returns whats given to it. 
/// 
/// Semantics
/// ---------
/// 
///     assert(identity(x) == x);
/// 
/// Synopsis
/// --------
/// 
///     template<class T>
///     constexpr T identity(T&& x);
/// 

#include <utility>
#include <initializer_list>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace identity_detail {

struct identity_base
{
    template<class T>
    constexpr T operator()(T&& x) const 
    noexcept(std::is_reference<T>::value || BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T))
    {
        return BOOST_HOF_FORWARD(T)(x);
    }

    template<class T>
    constexpr std::initializer_list<T>& operator()(std::initializer_list<T>& x) const noexcept
    {
        return x;
    }

    template<class T>
    constexpr const std::initializer_list<T>& operator()(const std::initializer_list<T>& x) const noexcept
    {
        return x;
    }

    template<class T>
    constexpr std::initializer_list<T> operator()(std::initializer_list<T>&& x) const noexcept(noexcept(std::initializer_list<T>(std::move(x))))
    {
        return BOOST_HOF_FORWARD(std::initializer_list<T>)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(identity, identity_detail::identity_base);

}} // namespace boost::hof

#endif

/* identity.hpp
0qVGvDZZf8Qrohyngr266fSnECbr43zMXro15m0jDOWs/KFX28fxlyB+NaKXInrTq36rAWezl5FRA93S1RiTMMN7O+9jV57YiP33/tryePxfmzj+c6X+raJXecNUrD2fzwo7rzOxdSlbNX/2MloSoF73myDIpXbKbcDWXjr5FTvCsundypZDllwEXej9jUzAg8IXH29kAgj+HtZJCVmWr6jVsOVnvAd3PlZZ7PZq77YQmn/5WnNd+h5Cq0Kf5DT9VntPFV0rrFcAlG6Ct+hV8bVrTbIhbCGIb5krFzE79uBX1YrNVHotFQ6g6pjgsuNf/l3yn/jTl5VJ9vmAQ+5vksCpVOBsKmBQ/mCsRgXs7zA3IyQ+jWGxngdnXofmtJoAe0G8ILgE2ZjKtM6R8f4twydpfzA10MP+4IoWQA2BDVbIwAqV9D1jaZOgeCd104nwfor++57OY/KbzDnkhiFzVfQsB7a52Ltr60vOSgE0mw0r4tC21U97Eg0DDebzza5utav9A/z7xf3X2OVOxAO74sGKevHNs9PvHpDqjpbU3QM8t7aYpOc4O5sad261WVHWEO15wMAYWJXVi8oSbT6DoiW7v5t94nsR4DHRfy6Xy+NeLEcM/CHdfpO3bLRTfsHeH7zy+EcYMdFej1Px3oVQRSG4BBuD4KYS7iFFdZvRJkYqjtrmuWWQC1sXJLDkU4IXQybMa5BAr4PWi60vbZqr7odHKqwEB2vinoo7H0/w3qdyj1ef7QBuc3i1nMcJc4Xj+ZyKfOgqBPIqfa7paULtsKBO9u30m2lNxpQov9CM/ZGNLagHfaglrqzs9mrZDFhJyGyrXyIKLRl19cLfpGZVcau5p3oc4SYKnX62me5uzjrPuZVNZg3QPJxxbjxCMyV0a2Xsb4/7a/CvFz4/C18sMzdgLV6KP0xbxvF/OteMX8Lxt53P8Qvi8fMSAbs3Ht/BgJUn1LmRB1DlNWaUN6xmnR/RVJ3Lw2adf2hNyHpOPOtvWmkNdW67z0IgvVuZsiGcDw/aWnJxAzmZh5Kts5pbSw56YouZ41IDEp/ov5LRkNqfGYXPrTR9C61U6Ivb1B7SHd9DgvmCLHFysRl7yL4AiRD3Fau5Ph90WFy0ryGrd2xyl1/YNTRKWh8CqpbAGTKvJm77EXHwnqS+zSbixyduaDCb/mvwRsICS2CiTHg7J/xDs5kwpBIWgp5RCQOrAQxNsRF+B/Z1p19nMIx2cepVn+NZjygkfDW2nqkPfglRK+3m4ykDkcP5uYHI8xDZjsgukBk+4VqoyiFhAzfjc+3narnBAnajRtOdpa/+u+Ug/1N/2MNvov3EklsS9xN5sv2z/Ouwn9i8Jt1+Yv8GSbeqB8PzMrmnGLLhU+wpYEeTy//VzT2WH7syXfneDYn7mYOrZNl3NH6Ksp83zydiTTzMssHD1iGfp9c46NCeZQPI6lTEMMzEBMeEdtqBqPWgber210o++BPMQ+l72sXojD2R7N363oxnJ7QHTzZZG4/PVnTMhXV14Ho3KGctCffxQqQjz4yfZ+wp7ZCk8ex9zsdsC0Ee30wZlG40EN2mMWRNqtXMuUHmXINzSKJuymF/ns1CfGY79Ib926uBm9h0u5vJ83VnoRipYBDnjPjXwW0Tm+ITvRtUkKPBCINx9WvONXBeYDYEjxwL8XJBHPLiWWq+T0S/EYV63Ta108jVyxfRhgOd2pto1XrWzJvTwFkaKvcH+nsDTbYt4VxkiIF1fzpDMs2fBSq7q71Bb1/+j+FQd+26JuX8Y0uSG4ARZrd2kPTUtmu41onF8ogVD680CePgaO0RQnD70bCwxbpNMqhHXBFXtp6oTZ6S54oLG+TkyME=
*/