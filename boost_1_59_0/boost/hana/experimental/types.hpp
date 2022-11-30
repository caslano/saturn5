/*!
@file
Defines `boost::hana::experimental::types`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_TYPES_HPP
#define BOOST_HANA_EXPERIMENTAL_TYPES_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/metafunction.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/any_of.hpp>
#include <boost/hana/detail/type_at.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/type.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


namespace boost { namespace hana {
    namespace experimental {
        //! @ingroup group-experimental
        //! Container optimized for holding types.
        //!
        //! It is often useful to manipulate a sequence that contains types
        //! only, without any associated runtime value. This container allows
        //! storing and manipulating pure types in a much more compile-time
        //! efficient manner than using `hana::tuple`, which must assume that
        //! its contents might have runtime values.
        template <typename ...T>
        struct types;

        struct types_tag;

        template <typename ...T>
        struct types { };
    } // end namespace experimental

    template <typename ...T>
    struct tag_of<experimental::types<T...>> {
        using type = experimental::types_tag;
    };

    // Foldable
    template <>
    struct unpack_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr decltype(auto) apply(hana::experimental::types<T...> const&, F&& f) {
            return static_cast<F&&>(f)(hana::type<T>{}...);
        }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::type<typename F::template apply<T...>::type>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    // Functor
    template <>
    struct transform_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr auto apply(hana::experimental::types<T...> const&, F&& f)
            -> hana::experimental::types<typename decltype(+f(hana::type<T>{}))::type...>
        { return {}; }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::experimental::types<typename F::template apply<T>::type...>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    // Iterable
    template <>
    struct at_impl<hana::experimental::types_tag> {
        template <typename ...T, typename N>
        static constexpr auto
        apply(hana::experimental::types<T...> const&, N const&) {
            using Nth = typename detail::type_at<N::value, T...>::type;
            return hana::type<Nth>{};
        }
    };

    template <>
    struct is_empty_impl<hana::experimental::types_tag> {
        template <typename ...T>
        static constexpr hana::bool_<sizeof...(T) == 0>
        apply(hana::experimental::types<T...> const&)
        { return {}; }
    };

    template <>
    struct drop_front_impl<hana::experimental::types_tag> {
        template <std::size_t n, typename ...T, std::size_t ...i>
        static hana::experimental::types<typename detail::type_at<i + n, T...>::type...>
        helper(std::index_sequence<i...>);

        template <typename ...T, typename N>
        static constexpr auto
        apply(hana::experimental::types<T...> const&, N const&) {
            constexpr std::size_t n = N::value > sizeof...(T) ? sizeof...(T) : N::value;
            using Indices = std::make_index_sequence<sizeof...(T) - n>;
            return decltype(helper<n, T...>(Indices{})){};
        }
    };

    // Searchable
    template <>
    struct contains_impl<hana::experimental::types_tag> {
        template <typename U>
        struct is_same_as {
            template <typename T>
            struct apply {
                static constexpr bool value = std::is_same<U, T>::value;
            };
        };

        template <typename ...T, typename U>
        static constexpr auto apply(hana::experimental::types<T...> const&, U const&)
            -> hana::bool_<
                detail::any_of<is_same_as<typename U::type>::template apply, T...>::value
            >
        { return {}; }

        static constexpr hana::false_ apply(...) { return {}; }
    };

    // Comparable
    template <>
    struct equal_impl<hana::experimental::types_tag, hana::experimental::types_tag> {
        template <typename Types>
        static constexpr hana::true_ apply(Types const&, Types const&)
        { return {}; }

        template <typename Ts, typename Us>
        static constexpr hana::false_ apply(Ts const&, Us const&)
        { return {}; }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXPERIMENTAL_TYPES_HPP

/* types.hpp
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
*/