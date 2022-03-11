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