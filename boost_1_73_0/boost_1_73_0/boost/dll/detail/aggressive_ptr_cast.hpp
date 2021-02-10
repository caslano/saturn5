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
rmhc21BEOA2eoRKsZPRGlBQvFChukXtUkmsgGyqrurzmaVP7WlmTr6ZOI1hxpJt4XiJVktzaIQwq3gbTvhBo9LghVx0EjHYaq9gyDF/Agktt2YTLzKPsc2cYnHX+YfKN/OjciQanl1lAPtZMISVRkev7jCsseQoOmr1zSvM5Yv7CWNUEt826ukTugjhTOtJKh5QcMxrHrDalT5zJMDJGk+FQLwRjP/IH/jA0nKLQd0hJklJ4VJmUhTyC0ygKQhNO9F/v3KFH4Ad7+AjPcREbWdJodz8558HQNSyRGU3x6WC+3ShNLrjawvri2RYtPoX/GPB95dLCumLxYUKvazt4q0iFzErKRQ8V/VT6u3rv2QjYblKB6gwJv1Fkb4M//isKu2qZ5me/n4X/LiO1O39xEuy8yq6r0/Ig+3369Y/BZyfeO72Y7qnr8fnKffu6E1Ivdwdssqv+4F+/sJvJwf6Hm3iXXR1k47l7VQ7yqEz4OWOHK1G+bXBu20aDNmA1UYNOg5p9XTKpaHPTg6o50gT7tfFfw8p4c/EaPxD/up+isTPQNOdpNqJmuM61uwL+TW4WkGYmOkx801YnlV9bnsy4E9ooU0vnxhPK9Jqzh9o365l3SMRvNCfVLE5vG0BcGU9QBbKbXNa6FigluGiU
*/