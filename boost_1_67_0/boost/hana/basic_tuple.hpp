/*!
@file
Defines `boost::hana::basic_tuple`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BASIC_TUPLE_HPP
#define BOOST_HANA_BASIC_TUPLE_HPP

#include <boost/hana/fwd/basic_tuple.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/ebo.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/bool.hpp>
#include <boost/hana/fwd/concept/sequence.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/integral_constant.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/unpack.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        //////////////////////////////////////////////////////////////////////
        // basic_tuple_impl<n, Xn>
        //////////////////////////////////////////////////////////////////////
        template <std::size_t> struct bti; // basic_tuple_index

        struct from_other { };

        template <typename Indices, typename ...Xn>
#ifdef BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE
        struct __declspec(empty_bases) basic_tuple_impl;
#else
        struct basic_tuple_impl;
#endif

        template <std::size_t ...n, typename ...Xn>
#ifdef BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE
        struct __declspec(empty_bases) basic_tuple_impl<std::index_sequence<n...>, Xn...>
#else
        struct basic_tuple_impl<std::index_sequence<n...>, Xn...>
#endif
            : detail::ebo<bti<n>, Xn>...
        {
            static constexpr std::size_t size_ = sizeof...(Xn);

            constexpr basic_tuple_impl() = default;

            template <typename Other>
            explicit constexpr basic_tuple_impl(detail::from_other, Other&& other)
                : detail::ebo<bti<n>, Xn>(detail::ebo_get<bti<n>>(static_cast<Other&&>(other)))...
            { }

            template <typename ...Yn>
            explicit constexpr basic_tuple_impl(Yn&& ...yn)
                : detail::ebo<bti<n>, Xn>(static_cast<Yn&&>(yn))...
            { }
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // basic_tuple
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename ...Xn>
    struct basic_tuple final
        : detail::basic_tuple_impl<std::make_index_sequence<sizeof...(Xn)>, Xn...>
    {
        using Base = detail::basic_tuple_impl<std::make_index_sequence<sizeof...(Xn)>, Xn...>;

        constexpr basic_tuple() = default;

        // copy constructor
        template <typename Other, typename = typename std::enable_if<
            std::is_same<typename detail::decay<Other>::type, basic_tuple>::value
        >::type>
        constexpr basic_tuple(Other&& other)
            : Base(detail::from_other{}, static_cast<Other&&>(other))
        { }

        template <typename ...Yn>
        explicit constexpr basic_tuple(Yn&& ...yn)
            : Base(static_cast<Yn&&>(yn)...)
        { }
    };
    //! @endcond

    template <typename ...Xn>
    struct tag_of<basic_tuple<Xn...>> {
        using type = basic_tuple_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<basic_tuple_tag> {
        template <std::size_t ...i, typename ...Xn, typename F>
        static constexpr decltype(auto)
        apply(detail::basic_tuple_impl<std::index_sequence<i...>, Xn...> const& xs, F&& f) {
            return static_cast<F&&>(f)(
                detail::ebo_get<detail::bti<i>>(
                    static_cast<detail::ebo<detail::bti<i>, Xn> const&>(xs)
                )...
            );
        }

        template <std::size_t ...i, typename ...Xn, typename F>
        static constexpr decltype(auto)
        apply(detail::basic_tuple_impl<std::index_sequence<i...>, Xn...>& xs, F&& f) {
            return static_cast<F&&>(f)(
                detail::ebo_get<detail::bti<i>>(
                    static_cast<detail::ebo<detail::bti<i>, Xn>&>(xs)
                )...
            );
        }

        template <std::size_t ...i, typename ...Xn, typename F>
        static constexpr decltype(auto)
        apply(detail::basic_tuple_impl<std::index_sequence<i...>, Xn...>&& xs, F&& f) {
            return static_cast<F&&>(f)(
                detail::ebo_get<detail::bti<i>>(
                    static_cast<detail::ebo<detail::bti<i>, Xn>&&>(xs)
                )...
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Functor
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct transform_impl<basic_tuple_tag> {
        template <std::size_t ...i, typename ...Xn, typename F>
        static constexpr auto
        apply(detail::basic_tuple_impl<std::index_sequence<i...>, Xn...> const& xs, F const& f) {
            return hana::make_basic_tuple(
                f(detail::ebo_get<detail::bti<i>>(
                    static_cast<detail::ebo<detail::bti<i>, Xn> const&>(xs)
                ))...
            );
        }

        template <std::size_t ...i, typename ...Xn, typename F>
        static constexpr auto
        apply(detail::basic_tuple_impl<std::index_sequence<i...>, Xn...>& xs, F const& f) {
            return hana::make_basic_tuple(
                f(detail::ebo_get<detail::bti<i>>(
                    static_cast<detail::ebo<detail::bti<i>, Xn>&>(xs)
                ))...
            );
        }

        template <std::size_t ...i, typename ...Xn, typename F>
        static constexpr auto
        apply(detail::basic_tuple_impl<std::index_sequence<i...>, Xn...>&& xs, F const& f) {
            return hana::make_basic_tuple(
                f(detail::ebo_get<detail::bti<i>>(
                    static_cast<detail::ebo<detail::bti<i>, Xn>&&>(xs)
                ))...
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<basic_tuple_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t index = N::value;
            return detail::ebo_get<detail::bti<index>>(static_cast<Xs&&>(xs));
        }
    };

    template <>
    struct drop_front_impl<basic_tuple_tag> {
        template <std::size_t N, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make_basic_tuple(
                detail::ebo_get<detail::bti<i+N>>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t len = detail::decay<Xs>::type::size_;
            return drop_front_helper<N::value>(static_cast<Xs&&>(xs), std::make_index_sequence<
                (N::value < len) ? len - N::value : 0
            >{});
        }
    };

    template <>
    struct is_empty_impl<basic_tuple_tag> {
        template <typename ...Xs>
        static constexpr hana::bool_<sizeof...(Xs) == 0>
        apply(basic_tuple<Xs...> const&)
        { return {}; }
    };

    // compile-time optimizations (to reduce the # of function instantiations)
    template <std::size_t n, typename ...Xs>
    constexpr decltype(auto) at_c(basic_tuple<Xs...> const& xs) {
        return detail::ebo_get<detail::bti<n>>(xs);
    }

    template <std::size_t n, typename ...Xs>
    constexpr decltype(auto) at_c(basic_tuple<Xs...>& xs) {
        return detail::ebo_get<detail::bti<n>>(xs);
    }

    template <std::size_t n, typename ...Xs>
    constexpr decltype(auto) at_c(basic_tuple<Xs...>&& xs) {
        return detail::ebo_get<detail::bti<n>>(static_cast<basic_tuple<Xs...>&&>(xs));
    }

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct Sequence<basic_tuple_tag> {
        static constexpr bool value = true;
    };

    template <>
    struct make_impl<basic_tuple_tag> {
        template <typename ...Xn>
        static constexpr basic_tuple<typename detail::decay<Xn>::type...>
        apply(Xn&& ...xn) {
            return basic_tuple<typename detail::decay<Xn>::type...>{
                static_cast<Xn&&>(xn)...
            };
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // length
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<basic_tuple_tag> {
        template <typename ...Xn>
        static constexpr auto apply(basic_tuple<Xn...> const&) {
            return hana::size_t<sizeof...(Xn)>{};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_BASIC_TUPLE_HPP

/* basic_tuple.hpp
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
*/