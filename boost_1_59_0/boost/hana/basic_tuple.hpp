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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_BASIC_TUPLE_HPP

/* basic_tuple.hpp
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
*/