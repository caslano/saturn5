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
+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
*/