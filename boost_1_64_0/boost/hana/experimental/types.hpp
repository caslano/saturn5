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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_TYPES_HPP

/* types.hpp
e2hiF/CwpdABYodg3a/QxdGzsY4QvfYx6CfiGeABOt9C6B+TgfczT4ROuwxzdih0p1ME8AlekosYX5drYvdZ+D1fFwMzZEQA8DzIgfPGY611YNz3YL18j2/B80JzQOeL8IYadO1Bv+g424d+gna77Y86q8CDoAMHIWOHfIv9QQ/E0cH4/vlXn7gZvOqtUZo4boEmrsDfb5ToIgLe+9rT0E8hZ/YOwK+rCfQMPlV9HdaVTxe/4btjMcbMm4WYNhE69hz4vRZjfUMnCLwG/esU4DkOfA3BuEO6uCYAHr0EcvV90Ock8Ox7sUfAOtzlIfDJUqyJGeAp0OPvzQUvgf54yEM+cRnWyImf4xx1H02cexvWxUGaGCzXHXTM9G0gv4HPpZAffwcvLFyoi7JtMef/wPsrmPu5SyD/LoYedx3oEzx/3t/Aux4CDxwvxOePgW7wu//7oAfoODI+xEXvQo7fBx/cfmgfovHHdPDbn/HWJGiw8k5NXPYD9E7oX7/uD/9O0EY65q7+EPBd4HBxT8iIdeB14Bfa96CFS3RxR6omumPN5RwFGjsP+sIwzFl/rE/obH8B/PKHcU4CWVr9Ic7EZ4MnQwYuPB9zuwNo4XjsQVZgjeyni5d7+cRK7KnasM4OT4UvO/SKMMq8EYGO70O/noLeBpl/aS5kyWrIjia83jYdfGI2aBPr6LTVmJsLIfvAyzN6Yi28gT5punjoN9DwxdhLBsE3wNtbVuniRuh8+TnQqV7WxInQlT/FHF31Mfp5B+gBbZY/r4lxBYi99DbW9kF44+RyzN9r4KersFawj9CXa6LlLPz9ki563AZ9GPzoY9BkPeY/Dl7Rejtwg/nYAXPcHTrg7aDRgjjoJ4C1g7VZCHy0VGriVPT/1gh0uUkYF/St7XcCH4Q8+gG8PXsl+A5o7McpwPcuoEfoiGt/EthDg6dBX5+OfWr7EcDZGbiTCD2xahr0zmt8ommAGc/g7AD0rZvRd+D43CfwRjv2SpnzMC7IrXFYN18fDN4MGvqmA21iv7v+r5A94Fv33QDcYE7G9kDs9HLsWY+DjD0aOh5k1WU+8Bas468hD98qwv7jIvAz6EwXTAcfhmzc6RzIKx17K7SnY6/zDOTR96PAQzG2M8AbzseYlhSBFoGjwzGu8XMhK0bA5/M86Bh9watKMH9YT+/erIsnwAeOaYdeAF5VuQL7oqux34Y/zNFngG+vxV7/KF1Er8cb6sBxK+hwB+z/3pyri0GY6/ngvcPfBB/thv5hvc0bBx4E2ngO83XYHJSHDr7rLPDf59FnrOco9MZ9QHclmO/gvqDL6Rgb+PB7h0I3/AC6H/Y8M08Hb/kE4+yDs2Tsryc8roknUxBf5FXwTaytIGhzHvr1pNyXHwQd/Ajgdgr8U6FHFEF+14G+GyFjarBHPwIyrHk66BHjXHGtT3xfB16+EmsV9R0HnL0FGdoMnjT6QfBW6A7Fj+nip2fBbzHnGv6+diL2dPdgD/KlJk57GHP3Cmj/dsiuHPQLuGiZDF4Buf4BdN69gcOiAeDv0CMuBL/9ZDnsEejb80eDj+0EPrAGex7wySzM5Z6n4e7ex1jn6PNx2D8fNh/0AJr4pNAnnoxDb0kBD3kJe5IvYBcZBr1uENZNN5wx3w0edJm8Nw8Z3wF9FXaF1eAdV2JvfVkF/LuxNl/uj3X6IfRjrN0YdOf+GEctyqe+CD4LnJ8zVhPHY08pXsd6+hIy7x2s6X+Bz4LWQ7dAlrwhxN+hJzw/BXH19sAc3Qmd7G/AFejtHezZSrHve7Ma+5Fy0PFTwHEc33b3iYu/Q90DsP+BLWfARcJoP9wfMjEFMuY6zBfkahNsTZdOgA0B9qA=
*/