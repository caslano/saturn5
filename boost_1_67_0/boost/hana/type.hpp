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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TYPE_HPP

/* type.hpp
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
*/