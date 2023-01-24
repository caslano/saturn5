// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_RETURN_TYPE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_RETURN_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // A metafunction that transforms void(*)(T) -> identity<T>
    template <typename UnaryFunctionPointer>
    struct unaryfunptr_return_type;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Arg>
    struct unaryfunptr_return_type<void(*)(Arg)>
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_identity<Arg>;
#else
        typedef ::boost::mpl::identity<Arg> type;
#endif
    };

    template <>
    struct unaryfunptr_return_type<void(*)(void)>
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_identity<void>;
#else
        typedef ::boost::mpl::identity<void> type;
#endif
    };
}}} // namespace boost::parameter::aux

#if !defined(BOOST_NO_SFINAE)
#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Pred, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::enable_if<Pred,Ret>)>
    {
        typedef ::boost::enable_if<Pred,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::enable_if_c<b,Ret>)>
    {
        typedef ::boost::enable_if_c<b,Ret> type;
    };

    template <typename Pred, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_enable_if<Pred,Ret>)>
    {
        typedef ::boost::lazy_enable_if<Pred,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_enable_if_c<b,Ret>)>
    {
        typedef ::boost::lazy_enable_if_c<b,Ret> type;
    };

    template <typename Pred, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::disable_if<Pred,Ret>)>
    {
        typedef ::boost::disable_if<Pred,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::disable_if_c<b,Ret>)>
    {
        typedef ::boost::disable_if_c<b,Ret> type;
    };

    template <typename B, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_disable_if<B,Ret>)>
    {
        typedef ::boost::lazy_disable_if<B,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_disable_if_c<b,Ret>)>
    {
        typedef ::boost::lazy_disable_if_c<b,Ret> type;
    };
}}} // namespace boost::parameter::aux

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::std::enable_if<b,Ret>)>
    {
        typedef ::std::enable_if<b,Ret> type;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_NO_CXX11_HDR_TYPE_TRAITS
#endif  // BOOST_NO_SFINAE

// A macro that takes a parenthesized C++ type name (T) and transforms it
// into an un-parenthesized type expression equivalent to identity<T>.
#define BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(x)                         \
    ::boost::parameter::aux::unaryfunptr_return_type< void(*)x >::type

#endif  // include guard


/* parenthesized_return_type.hpp
zBhNn6YnidhYWLrNZwj6XkSz/1AYdDd1GfvY/GWeeFrP5yIpYDEKnJHMe7eP5irOGzNhNjJidajvJavURThmSD4/573AI5w4eUzCxG+neFjC3peefRaPRv+RXV7Y3HyybR/X30G9obhWJiVd4XcxvflnbzKC4TtItLzgefP4gbAPkuSNHB+goX4+PzXSbks+z2BCZvODy94Ps50qSleTEkymqvUbk7D0hrNv34CVB/OKHJV5eXNzmIpSLqbt6RLmUk0TZoaZC3Ef+THOcedc2q0Gr8wXqIeKVGUKpahuRNJHMy7gyEb3vzBniwibxMWNKBInklQLm+xbzK2RUXo0KvdlyJ2yMxepfe/zCg0Ttr3Z+PPjoE93SrqkKSufQbC/I8UqwnBRja9HbtE4nJU00Vut4FBu8uk6y1zbe4w/PTvGfNI6hhS5SYpLLrF415AtJfP90tQ5GGO4DzewVrRsyCTPjC0fOaH/rXvHbAVUcnH5IBW22CMCyzGk+mHw8fL2OBrvKUkyu41hKNFXZ4Vcic5t3GPNjI8CixItm4/U7y9S28FkJwj8r0ovULFOCDK0hJNxd54eG+un+QDl5L7k+fXZ4l94R54k5OaJZL6yoh03YcBrRMOFszu9I0FAOYNvilKpYrvHMwUabNeY4IN/e3HTccml8lBEKk++W8RcgWKgSN3uWVMfcK01B1VQeiwlXJM4RcmUyoprSFn1
*/