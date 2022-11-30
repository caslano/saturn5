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
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
*/