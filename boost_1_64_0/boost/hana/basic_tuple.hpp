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
445t7aoqOs0tVjbtXcmLEa8qwY6nu9nPTF3/A/wtzHz2cdb+/yWI95u5ouM9DPag67yoa23ZDt8ecYlcfWK3XTqH+kf928CGfyKm7/E62Lv42NK+EfHbLnN+XR/OF9EC1PX/wa8K8iGLxqtRq/MfLnd+3Wniotovty4qsWeBfYiJne1LWgLxLV3/4QrofpvYKrHHOTRTSQn9RW0/2tBjaoM92eXuEauvdH69l5FtdUlokGr9T7C3MbEdgmrCgakEcx691v+8yvl1wchPZ205IyuRKjrHxXFIFWRyFB5BO3YwtkPNP+b7TBr7qqudX2dM3HhCSZ/GE9zaVTr/F+yN/Wxb/FwZzdzXNOfKr3F+XeHnduNczauMdjXe3OuN7L4B/IaPwY+2t6Gy+0FJwTcjZdfi7eGnM1xPOdPuFlau/v4D90c3F/c99jVuiv9dFo31KtfhzaGrryFTtn8me1BG2eyUFWDm6/gv+C1u/i61NVEBjRdiznM98oCCTCXzLfPNOQjmHkGmLV3cebCa4cx1NWle/wr2lGbv2LhjxEmdiLU11UW35O1n4uZugJ/4noFbt2OUe04Tdxrczz322mkbjrnMXJpXe92Is/q9IFeZy8pcjXxhMB/5hJgNNZtvWiHCqrwJtX9crIrNtxBhXQHWHS7WpkLjtszN0IjU+28E+sb8upT6/QeY53iYic6EkkYpArjfbZEvv8Qt+LleG0ovTT04SSVtGWdc78vky61JeyHaMJ+7DQI5J8T7FryzaC61R2ucg5XXZyfevrdCb3XKxcunDuG+iyDe6+Cd8omH180dc9bvH27Dt6iHN+MnOVmmvDpptG6eBntbd98qBdl0ilYO7/lN3OrboSka5Cqz+bk6/x/c7TxcCMjaBsvl1Fbe4fy63cBWRouwaU5fA/ZCLrbEHkFnwAp3wiccd/GUByoxl3X+O5gtLqZEbJFs/BO8PVw8O9Ff4JyjOTRwF/KBvEx1RQgF5Bh/riX17zTYheEZtkQMVft/d0PTzz1n8S1lMdcEpH1pGMxB115sO7mbIh1b6G1hwz3QEvmUuHWV9hkgoFNPzEfA3MfNzOYKEtrl5Ieufy+0Q1xMbpbWvwErN8OqkOpTHf+9D7qjbqZyQ6XOFu3/grvFW8StaanHp6GSamOPGWn9//uRO+Xh2l4v+xzS73/AfPITD9Pi1sUgG6fAK/fYaF8aqq7lzTUm5m4PIA7oZto4fs1t6tfnwTxtzM3sPLhg8d6Lko3VDyJ3/SPwivtslVMSL9fJa6P2/8D8/UMPM6e2BPvottX0me++df7bQ8gfn3Sz4fkx+2E6/w3Mr732qmDyLrGmyO5i+dNkc9nDyD372MXf0vlalPKRLgGzZdrNRNoTJY0LsVd4BHluXnttkT+V9mX/gbu+lPZ/wX4owObNs9LvPx5Ffsikm4fUm0RBzA/NgXvd+24u//22vv8E701Pv9rbBcaTd38kO3d7DHpEHjv537do/VPwnv3Yy0tl4uxva4m57ePIk/QyrYzAnkjMe8Ac8zBl9mHaF8pnIefay4wnncCjikmpum9CcbgbwL7CO49Uwb0WkXpv1M+rPIH55N4fNi8e7eqMF+rnC8B8M8B0XP+8wBhTPy/xJM66EHbqQBnuELi/z3ZxN62gJyu98QQvV+v/PIW48qSX25/JxYt5DFuqVVx8fMi9d9BYHwt+bRhf4K042T7P0/AxzOx4vypbH++y2L+BtP4/+Ht4+fY8UwMuwvwSzPne9jBtTTFu/1G/f3sGP/fZqWwsJsrkLeacZuKOgjufj2sf+gouNa5tz+Ln3j4Wzft8Gcxqr604ENWeKXBfos//5/C+0sdW6Rrs5yHZ+wg=
*/