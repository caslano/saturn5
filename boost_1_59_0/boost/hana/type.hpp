/*!
@file
Defines `boost::hana::type` and related utilities.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TYPE_HPP
#define BOOST_HANA_TYPE_HPP

#include <boost/hana/fwd/type.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/fwd/concept/metafunction.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/hash.hpp>
#include <boost/hana/integral_constant.hpp>

#include <type_traits>
#include <utility>


namespace boost { namespace hana {
    //////////////////////////////////////////////////////////////////////////
    // basic_type
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T>
    struct basic_type : detail::operators::adl<basic_type<T>> {
        using hana_tag = type_tag;

        using type = T;
        constexpr auto operator+() const { return *this; }
    };
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // type
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct type_impl {
        struct _ : basic_type<T> { };
    };

    //////////////////////////////////////////////////////////////////////////
    // decltype_
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename T, typename = type_tag>
        struct decltype_t {
            using type = typename std::remove_reference<T>::type;
        };

        template <typename T>
        struct decltype_t<T, typename hana::tag_of<T>::type> {
            using type = typename std::remove_reference<T>::type::type;
        };
    }

    //! @cond
    template <typename T>
    constexpr auto decltype_t::operator()(T&&) const
    { return hana::type_c<typename detail::decltype_t<T>::type>; }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // typeid_
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename T, typename = type_tag>
        struct typeid_t {
            using type = typename std::remove_cv<
                typename std::remove_reference<T>::type
            >::type;
        };

        template <typename T>
        struct typeid_t<T, typename hana::tag_of<T>::type> {
            using type = typename std::remove_reference<T>::type::type;
        };
    }
    //! @cond
    template <typename T>
    constexpr auto typeid_t::operator()(T&&) const
    { return hana::type_c<typename detail::typeid_t<T>::type>; }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // make<type_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<type_tag> {
        template <typename T>
        static constexpr auto apply(T&& t)
        { return hana::typeid_(static_cast<T&&>(t)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // sizeof_
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T>
    constexpr auto sizeof_t::operator()(T&&) const
    { return hana::size_c<sizeof(typename detail::decltype_t<T>::type)>; }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // alignof_
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T>
    constexpr auto alignof_t::operator()(T&&) const
    { return hana::size_c<alignof(typename detail::decltype_t<T>::type)>; }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // is_valid
    //////////////////////////////////////////////////////////////////////////
    namespace type_detail {
        template <typename F, typename ...Args, typename = decltype(
            std::declval<F&&>()(std::declval<Args&&>()...)
        )>
        constexpr auto is_valid_impl(int) { return hana::true_c; }

        template <typename F, typename ...Args>
        constexpr auto is_valid_impl(...) { return hana::false_c; }

        template <typename F>
        struct is_valid_fun {
            template <typename ...Args>
            constexpr auto operator()(Args&& ...) const
            { return is_valid_impl<F, Args&&...>(int{}); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto is_valid_t::operator()(F&&) const
    { return type_detail::is_valid_fun<F&&>{}; }

    template <typename F, typename ...Args>
    constexpr auto is_valid_t::operator()(F&&, Args&& ...) const
    { return type_detail::is_valid_impl<F&&, Args&&...>(int{}); }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // template_
    //////////////////////////////////////////////////////////////////////////
    // Note: We have to use the very complicated trick below instead of just
    // mentionning `F<T...>` in a SFINAE-able context because of CWG 1430
    // (http://www.open-std.org/Jtc1/sc22/wg21/docs/cwg_active.html#1430).
    namespace template_detail {
        template <typename ...T> struct args;
        template <typename ...> using always_void = void;

        template <template <typename ...> class F, typename Args, typename = void>
        struct specialization_is_valid
            : std::false_type
        { };

        template <template <typename ...> class F, typename ...T>
        struct specialization_is_valid<F, args<T...>, always_void<F<T...>>>
            : std::true_type
        { };
    } // end namespace detail

    template <template <typename ...> class F>
    struct template_t {
        template <typename ...T>
        struct apply {
            using type = F<T...>;
        };

        template <typename ...T, typename = std::enable_if_t<
            template_detail::specialization_is_valid<F, template_detail::args<typename T::type...>>::value
        >>
        constexpr auto operator()(T const& ...) const
        { return hana::type<F<typename T::type...>>{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // metafunction
    //////////////////////////////////////////////////////////////////////////
    template <template <typename ...> class F>
    struct metafunction_t {
        template <typename ...T>
        using apply = F<T...>;

        template <typename ...T>
        constexpr hana::type<typename F<typename T::type...>::type>
        operator()(T const& ...) const { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // metafunction_class
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename F, typename ...T>
        struct always_first { using type = F; };
    }
    template <typename F>
    struct metafunction_class_t {
        template <typename ...T>
        using apply = typename detail::always_first<F, T...>::type::template apply<T...>;

        template <typename ...T>
        constexpr hana::type<typename detail::always_first<F, T...>::type::template apply<typename T::type...>::type>
        operator()(T const& ...) const { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Metafunction
    //////////////////////////////////////////////////////////////////////////
    template <template <typename ...> class F>
    struct Metafunction<template_t<F>> {
        static constexpr bool value = true;
    };

    template <template <typename ...> class F>
    struct Metafunction<metafunction_t<F>> {
        static constexpr bool value = true;
    };

    template <typename F>
    struct Metafunction<metafunction_class_t<F>> {
        static constexpr bool value = true;
    };

    //////////////////////////////////////////////////////////////////////////
    // integral
    //////////////////////////////////////////////////////////////////////////
    template <typename F>
    struct integral_t {
        template <typename ...T, typename Result =
            typename detail::always_first<F, T...>::type::template apply<typename T::type...>::type
        >
        constexpr Result operator()(T const& ...) const {
            return Result{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<type_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<type_tag, type_tag> {
        template <typename T, typename U>
        static constexpr auto apply(basic_type<T> const&, basic_type<U> const&)
        { return hana::false_c; }

        template <typename T>
        static constexpr auto apply(basic_type<T> const&, basic_type<T> const&)
        { return hana::true_c; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Hashable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct hash_impl<hana::type_tag> {
        template <typename T>
        static constexpr T apply(T const& t)
        { return t; }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_TYPE_HPP

/* type.hpp
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
*/