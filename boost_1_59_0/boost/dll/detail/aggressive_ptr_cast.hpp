// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
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
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
*/