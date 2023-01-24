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
q2a5HDtdMysoO1czOkt7ywT/Akd/it0t4+GQe+T643Et7sbjkOuPRUmwqD6aXwJlCaNZWQ5QSmksZWsStGSaBRFr3uqfev0orAASheSGWlZlv2JqgbLAbevrlf2VL2/hzIXqq3pF45SjqCf7kCNOhkMoFmlJ+uufLpdupZ4+MCHY4RTHm2IgJUjB/fgA1y+Rac0j21u3J3Q4LRxfJ+MIzEW2foPrqz6NldBCdET/xGCll+8w0zPdM9sz03K0pQ990cxLtLAqQvFbCp7q2n4yfuIcedJfnm49L+Z8HPI1zUmCRkHl+e2y7ooaRvLqFuU/MLppB98ILTmuwCspxovV+aecKcAnzINX4gWA/BFemg9WSV2H/uejaVVHq1wxFNMA1fFbXvMYMucZSTvZIVylKWGD+LqRIw1myEIdls7cirIQeHa57BtL5lVdYcEKNpPByLETmar2qC3rQ3DzbFX6d3Ru2nIuxQpMTGFpYdo8VzedxVj6OZ3VmW9Pl1bOvONORGbjxbglCcxFNU4KQVsTretP0e9942gBP4iPUQpHRAEjVcQFhEq731lh8tB8DrQJv+oBc4GcyDGtIbbYHBPgkuzYRNfet5TekvxsJxAZkRDtkHV7D2HGmx7rCR2GwsoAt8TRST1FSBVJDsG2eGr4o0p9lgo3D16kv4EISRFVKFWC74/ZnPeHrvI2b9frppJxG0jsr6L2TvFmRylH
*/