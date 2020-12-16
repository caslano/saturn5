// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_AGGRESSIVE_PTR_CAST_HPP
#define BOOST_DLL_DETAIL_AGGRESSIVE_PTR_CAST_HPP

#include <boost/dll/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <cstring>              // std::memcpy

#if defined(__GNUC__) && defined(__GNUC_MINOR__) && (__GNUC__ * 100 + __GNUC_MINOR__ > 301)
#   pragma GCC system_header
#endif

namespace boost { namespace dll { namespace detail {

// GCC warns when reinterpret_cast between function pointer and object pointer occur.
// This method suppress the warnings and ensures that such casts are safe.
template <class To, class From>
BOOST_FORCEINLINE typename boost::disable_if_c<boost::is_member_pointer<To>::value || boost::is_reference<To>::value || boost::is_member_pointer<From>::value, To>::type
    aggressive_ptr_cast(From v) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT_MSG(
        boost::is_pointer<To>::value && boost::is_pointer<From>::value,
        "`agressive_ptr_cast` function must be used only for pointer casting."
    );

    BOOST_STATIC_ASSERT_MSG(
        boost::is_void< typename boost::remove_pointer<To>::type >::value
        || boost::is_void< typename boost::remove_pointer<From>::type >::value,
        "`agressive_ptr_cast` function must be used only for casting to or from void pointers."
    );

    BOOST_STATIC_ASSERT_MSG(
        sizeof(v) == sizeof(To),
        "Pointer to function and pointer to object differ in size on your platform."
    );

    return reinterpret_cast<To>(v);
}

#ifdef BOOST_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4172) // "returning address of local variable or temporary" but **v is not local!
#endif

template <class To, class From>
BOOST_FORCEINLINE typename boost::disable_if_c<!boost::is_reference<To>::value || boost::is_member_pointer<From>::value, To>::type
    aggressive_ptr_cast(From v) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT_MSG(
        boost::is_pointer<From>::value,
        "`agressive_ptr_cast` function must be used only for pointer casting."
    );

    BOOST_STATIC_ASSERT_MSG(
        boost::is_void< typename boost::remove_pointer<From>::type >::value,
        "`agressive_ptr_cast` function must be used only for casting to or from void pointers."
    );

    BOOST_STATIC_ASSERT_MSG(
        sizeof(v) == sizeof(typename boost::remove_reference<To>::type*),
        "Pointer to function and pointer to object differ in size on your platform."
    );
    return static_cast<To>(
        **reinterpret_cast<typename boost::remove_reference<To>::type**>(
            v
        )
    );
}

#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif

template <class To, class From>
BOOST_FORCEINLINE typename boost::disable_if_c<!boost::is_member_pointer<To>::value || boost::is_member_pointer<From>::value, To>::type
    aggressive_ptr_cast(From v) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT_MSG(
        boost::is_pointer<From>::value,
        "`agressive_ptr_cast` function must be used only for pointer casting."
    );

    BOOST_STATIC_ASSERT_MSG(
        boost::is_void< typename boost::remove_pointer<From>::type >::value,
        "`agressive_ptr_cast` function must be used only for casting to or from void pointers."
    );

    To res = 0;
    std::memcpy(&res, &v, sizeof(From));
    return res;
}

template <class To, class From>
BOOST_FORCEINLINE typename boost::disable_if_c<boost::is_member_pointer<To>::value || !boost::is_member_pointer<From>::value, To>::type
    aggressive_ptr_cast(From /* v */) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT_MSG(
        boost::is_pointer<To>::value,
        "`agressive_ptr_cast` function must be used only for pointer casting."
    );

    BOOST_STATIC_ASSERT_MSG(
        boost::is_void< typename boost::remove_pointer<To>::type >::value,
        "`agressive_ptr_cast` function must be used only for casting to or from void pointers."
    );

    BOOST_STATIC_ASSERT_MSG(
        !sizeof(From),
        "Casting from member pointers to void pointer is not implemnted in `agressive_ptr_cast`."
    );

    return 0;
}

}}} // boost::dll::detail

#endif // BOOST_DLL_DETAIL_AGGRESSIVE_PTR_CAST_HPP


/* aggressive_ptr_cast.hpp
KuO3LQYu/A55qYwvtPCbJrWG29ugIIbWNSe0p3bT+toJCFyQREBXBG6SydIQ2LWZCmwhSJHAH11F6TO0UvA7dO8PovTRWvh4DL+Vwq/Swv+K4VdQeIkWPhLDz4oRfgLW4pMuRN5IIAKPMgjgegSQegSGIJAsk51PtGZruPoirq3bRRlHaeH4HXqLwg/Rwttg+FIID41sRkh/T4cSxv1AZX+PwOMy5gsEPpDAe+mi7C+/MHDhd+haKmOdFr4Rw8+n8Oe18DUYfjKFz9PCazH8CKQp0UeFDceSP+5EwGAE3pXAQAQ+SyTgNATi3QT0QiBH1iMDgYDE1h6B9jKmFQInSsCJwK0/E7CjCwD/kOV8hcCiznL8A4D81WjuhTTfCGMu9NjhlOh5SnSMlsiPiQZAIghP1cJ9GH48Zr5ByoVSLG6kBK5D4J9y0F+OwI1yEJ2HwDQJ5CBQ/QclOwmBuyVwNALXSGwdEXhQxngR6Cdj4hDY2oGw/XyEIP+uzw0y58B36E4YsqHN6ZRoAyWq1BJNx0RXQSIIL9XCJ2L4OZj5SVn2dMgcOkUCkxEY8SsBtyJQto2AGxB4QQIFCPSQeS5AYL4EzkRglgR6IxAngWMQeE0Opk4IuGRMawTO/JaABKrLls0Gzd/Dd2gOxIcqv6BEmzqLRF9piSKYqBgSQfjbWvhHGD4YM78r+91DkDkUDRGmmQjcl0Ix5QhcmUrAKASchxFwEwKz2hJwBQJ/yOnsQgSO2kXYggicKoFTEPhEIjiOKL5Qo2woUrbiG0FxXy38Egx/HMJDY+RBku1AeShVlr4Fgee3Uhn/QuCRnQS8gcBLEngZgUtl6Yt9onSPVkp7LCWHSt+5yQhPwfBjsPT3ZYcegZimHkrA1QgMkKPxEgQSZCfMRaCfBE5F4F+S/BOo9DVaKRvhO7Rymyj9GS18HYY/BeGhAlndn6Cs0LkSCCHQRwIfIdBKtuNbCEz+kYDaTg07/j74O/jbBz/5/lVL+UywHJbDOkJv7CiBizqK7u/6FLq5k7r5H59AN18Vhm4+6UtKdDzmeDBZqsiUY8snRg78RtMphoe08G0YPhoxDZGZv+oAmGYcLqfIDgLTe1oO/A6dTZiWa+ErMbwnYrpUzq/zENPVEqhEYKAEJiCQLoGbEZgvSx+OwGmJUkVA4KkWUkXosD8GpX7+L5nfcwrkiBNcuGjOi6e/7tCOj027WsVtssU6nc1HvlCvfl5Hk15/MZ0HXNxC7qdl0K7X+I/Vend655hV15+uClCC2PHBBuJ9DcQHGohPayDehic2T8suSpJ8aE18GPkR7CsKi8jWjeYWoJdj0SpR7lafQbjkq77z4OJ5k9uj7ntgeMlH2ARebXT6YBPT+2KlNyfH1LCfQombQn+gKfj9Tcef1hT8yU3Hn0VZmvLe9lA3ydTc3ZE6G6Fj+UxDRmgkKG9gHKenrAoobCZoEPgyF4YHxQCn8GGfiXA4xCDPhedReNkHGB7rxUTcu6F0bWF1undvZNlW9eZEUVWxq8uH3gOhH96nbV2CPnwrEm14LNjiP5Twy/P+DrhCHKATPcoZ28M0UhPfT8GZIAv+hK6DU/mKHSqjQVs0j7hCb7S15gQ4aPEGvZNDxOmbTgxSZv8yF290V8O+LUcPC/RB6x/f1u304d4yvKH3rxK0R7duWReJmm2o53wdIcndWH4Hxf0XQsqVzAvdCdwky7lwJNddfmfJG1L50oNvnmRRfoWjtxMst8cBBor3TNyKyChN0B2aicsleuLvFLJxVqeIvY/u2GgXiIMMLU96L8VB7rSX4V5rdTMkLm072kLD57rQRooI82FuXID1xIOWEucNFOEl1CtamW/T9cI=
*/