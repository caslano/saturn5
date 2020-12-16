/*!
@file
Defines `boost::hana::tuple`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TUPLE_HPP
#define BOOST_HANA_TUPLE_HPP

#include <boost/hana/fwd/tuple.hpp>

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/detail/index_if.hpp>
#include <boost/hana/detail/intrinsics.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/iterable.hpp>
#include <boost/hana/detail/operators/monad.hpp>
#include <boost/hana/detail/operators/orderable.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/index_if.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/optional.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/type.hpp> // required by fwd decl of tuple_t

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename Xs, typename Ys, std::size_t ...n>
        constexpr void assign(Xs& xs, Ys&& ys, std::index_sequence<n...>) {
            int sequence[] = {int{}, ((void)(
                hana::at_c<n>(xs) = hana::at_c<n>(static_cast<Ys&&>(ys))
            ), int{})...};
            (void)sequence;
        }

        struct from_index_sequence_t { };

        template <typename Tuple, typename ...Yn>
        struct is_same_tuple : std::false_type { };

        template <typename Tuple>
        struct is_same_tuple<typename detail::decay<Tuple>::type, Tuple>
            : std::true_type
        { };

        template <bool SameTuple, bool SameNumberOfElements, typename Tuple, typename ...Yn>
        struct enable_tuple_variadic_ctor;

        template <typename ...Xn, typename ...Yn>
        struct enable_tuple_variadic_ctor<false, true, hana::tuple<Xn...>, Yn...>
            : std::enable_if<
                detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Yn&&)...>::value
            >
        { };
    }

    //////////////////////////////////////////////////////////////////////////
    // tuple
    //////////////////////////////////////////////////////////////////////////
    template <>
#ifdef BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE
    struct __declspec(empty_bases) tuple<> final
#else
    struct tuple<> final
#endif
        : detail::operators::adl<tuple<>>
        , detail::iterable_operators<tuple<>>
    {
        constexpr tuple() { }
        using hana_tag = tuple_tag;
    };

    template <typename ...Xn>
#ifdef BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE
    struct __declspec(empty_bases) tuple final
#else
    struct tuple final
#endif
        : detail::operators::adl<tuple<Xn...>>
        , detail::iterable_operators<tuple<Xn...>>
    {
        basic_tuple<Xn...> storage_;
        using hana_tag = tuple_tag;

    private:
        template <typename Other, std::size_t ...n>
        explicit constexpr tuple(detail::from_index_sequence_t, std::index_sequence<n...>, Other&& other)
            : storage_(hana::at_c<n>(static_cast<Other&&>(other))...)
        { }

    public:
        template <typename ...dummy, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, dummy...)...>::value
        >::type>
        constexpr tuple()
            : storage_()
        { }

        template <typename ...dummy, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Xn const&, dummy...)...>::value
        >::type>
        constexpr tuple(Xn const& ...xn)
            : storage_(xn...)
        { }

        template <typename ...Yn, typename = typename detail::enable_tuple_variadic_ctor<
            detail::is_same_tuple<tuple, Yn...>::value,
            sizeof...(Xn) == sizeof...(Yn), tuple, Yn...
        >::type>
        constexpr tuple(Yn&& ...yn)
            : storage_(static_cast<Yn&&>(yn)...)
        { }

        template <typename ...Yn, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Yn const&)...>::value
        >::type>
        constexpr tuple(tuple<Yn...> const& other)
            : tuple(detail::from_index_sequence_t{},
                    std::make_index_sequence<sizeof...(Xn)>{},
                    other.storage_)
        { }

        template <typename ...Yn, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Yn&&)...>::value
        >::type>
        constexpr tuple(tuple<Yn...>&& other)
            : tuple(detail::from_index_sequence_t{},
                    std::make_index_sequence<sizeof...(Xn)>{},
                    static_cast<tuple<Yn...>&&>(other).storage_)
        { }

        // The three following constructors are required to make sure that
        // the tuple(Yn&&...) constructor is _not_ preferred over the copy
        // constructor for unary tuples containing a type that is constructible
        // from tuple<...>. See test/tuple/cnstr.trap.cpp
        template <typename ...dummy, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Xn const&, dummy...)...>::value
        >::type>
        constexpr tuple(tuple const& other)
            : tuple(detail::from_index_sequence_t{},
                    std::make_index_sequence<sizeof...(Xn)>{},
                    other.storage_)
        { }

        template <typename ...dummy, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Xn const&, dummy...)...>::value
        >::type>
        constexpr tuple(tuple& other)
            : tuple(const_cast<tuple const&>(other))
        { }

        template <typename ...dummy, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_CONSTRUCTIBLE(Xn, Xn&&, dummy...)...>::value
        >::type>
        constexpr tuple(tuple&& other)
            : tuple(detail::from_index_sequence_t{},
                    std::make_index_sequence<sizeof...(Xn)>{},
                    static_cast<tuple&&>(other).storage_)
        { }


        template <typename ...Yn, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_ASSIGNABLE(Xn&, Yn const&)...>::value
        >::type>
        constexpr tuple& operator=(tuple<Yn...> const& other) {
            detail::assign(this->storage_, other.storage_,
                           std::make_index_sequence<sizeof...(Xn)>{});
            return *this;
        }

        template <typename ...Yn, typename = typename std::enable_if<
            detail::fast_and<BOOST_HANA_TT_IS_ASSIGNABLE(Xn&, Yn&&)...>::value
        >::type>
        constexpr tuple& operator=(tuple<Yn...>&& other) {
            detail::assign(this->storage_, static_cast<tuple<Yn...>&&>(other).storage_,
                           std::make_index_sequence<sizeof...(Xn)>{});
            return *this;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<tuple_tag> {
            static constexpr bool value = true;
        };
        template <>
        struct orderable_operators<tuple_tag> {
            static constexpr bool value = true;
        };
        template <>
        struct monad_operators<tuple_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<tuple_tag> {
        template <typename F>
        static constexpr decltype(auto) apply(tuple<>&&, F&& f)
        { return static_cast<F&&>(f)(); }
        template <typename F>
        static constexpr decltype(auto) apply(tuple<>&, F&& f)
        { return static_cast<F&&>(f)(); }
        template <typename F>
        static constexpr decltype(auto) apply(tuple<> const&, F&& f)
        { return static_cast<F&&>(f)(); }

        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs).storage_, static_cast<F&&>(f));
        }
    };

    template <>
    struct length_impl<tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(tuple<Xs...> const&)
        { return hana::size_c<sizeof...(Xs)>; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<tuple_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t index = N::value;
            return hana::at_c<index>(static_cast<Xs&&>(xs).storage_);
        }
    };

    template <>
    struct drop_front_impl<tuple_tag> {
        template <std::size_t N, typename Xs, std::size_t ...i>
        static constexpr auto helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<tuple_tag>(hana::at_c<i+N>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return helper<N::value>(static_cast<Xs&&>(xs), std::make_index_sequence<
                (N::value < len) ? len - N::value : 0
            >{});
        }
    };

    template <>
    struct is_empty_impl<tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(tuple<Xs...> const&)
        { return hana::bool_c<sizeof...(Xs) == 0>; }
    };

    // compile-time optimizations (to reduce the # of function instantiations)
    template <std::size_t n, typename ...Xs>
    constexpr decltype(auto) at_c(tuple<Xs...> const& xs) {
        return hana::at_c<n>(xs.storage_);
    }

    template <std::size_t n, typename ...Xs>
    constexpr decltype(auto) at_c(tuple<Xs...>& xs) {
        return hana::at_c<n>(xs.storage_);
    }

    template <std::size_t n, typename ...Xs>
    constexpr decltype(auto) at_c(tuple<Xs...>&& xs) {
        return hana::at_c<n>(static_cast<tuple<Xs...>&&>(xs).storage_);
    }

    template <>
    struct index_if_impl<tuple_tag> {
        template <typename ...Xs, typename Pred>
        static constexpr auto apply(tuple<Xs...> const&, Pred const&)
            -> typename detail::index_if<Pred, Xs...>::type
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct Sequence<tuple_tag> {
        static constexpr bool value = true;
    };

    template <>
    struct make_impl<tuple_tag> {
        template <typename ...Xs>
        static constexpr
        tuple<typename detail::decay<Xs>::type...> apply(Xs&& ...xs)
        { return {static_cast<Xs&&>(xs)...}; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TUPLE_HPP

/* tuple.hpp
J6b83DFbed80vslzaRxmuKPH4+bUBsXwvua5k7NrJ71zHvexVd68hhvs6FdPe4C80+et5PCv+CDVRA9uVf6dHva8iW2vdo1sXdwEjkOCTNapWTRxP/rxFno840NVDV54GgtL3IcxboD20aV83qS6BqYGrQZo2/iSctSikCt35W8r6uCY4Ub4mldsi3gspPeE/Rtrtn+FtIlh/CLV51nHeaW9sDnJnrTj9hdXob2w/BCTG/qPF/XiYR/XNqKSS0V5y71eFc4HEz26Vc5r0y315G3+ej14Liv0SCZCqrSa66WerfPFSchS9G8bV6FfwPMnmGiNGxrT9ktdiHlTaCL9XWG8KtU1sE62rtW2YeD0jJaPvE/P5+RHUJnrhK2Na3jPHveE5K+M/iWlbjcYa2vpVrpuuv9lRfs0s51zVVd3DJsFxj/0hsfPvrTFFzocc9VQK9UO6DuBRhiCzF+qqvC++/mTXLOqHhplCJZf6C1EosIP9qIFw0kIs30O28DYEqrrMUZzbZoOuuTCBFPgk2Xf1b4auNKKoaMn7JEujzLXcE8y6W8jnNKmYtuXHjO6fK6R+dbk/aumV0NrmKkursigTX8y/oZ+6JwdOoYeplPRjRp9YcryVGt1H6AHqi0L91lj3123j5J4jrzxC+iY01UIsTOCxbGdy3hU/j4o7+N1P/BatLB1vQ5D7Uv/oNsXuqVTovJN+JpqF/ameW5B/jtR/seaWnqnuI38tD7Lc3yhf9C1bF0Fdb+MnyO5d0i86BNmWy+E7Rme4umMHrZ+03WPYLoVugxTXSMrMzSoCz8hiLZd1cPwXF3o6VjT60a3XLLkHbwmZiRrYW3edxc6HOPcyjDOZv/z57jEQPvspD5OKNmLxmB9SPhG+jjR9QPvowsdlsm6drJuHFZoVUdZn5Q39WV3ge/uBhFPYZdAKWzcGbDBvn4nGO9/CjQ484VDcnoegRUiZlh2mVs+v3F8juGfERNpcZeE95DAtwACatNUPcgEWsYB8643IuBU4fPbZQyn2vSKPL9TwpHq64BLhs8TvhbAQEmzSfQkbC3rtsFnFB5jne6e8tcqqM8zlbRU5h5JJgbaSovP75lzI8EUTvnvFZ8PW0bt6Ep0+PzeOceSrJ6zRfjvk59r94zNreXz++bnW0pQ/feLz40NXUH13H/si60IgUWePzA8T+60Qc8d0/MHjZhsVW9k4s24X2N+KMmXOh6e6wL9tkX67RH5OeivtlzRb49Emna9hH5Jzx+FzyOimhvMVqgX0h+9pFeUJWLUAZ2NmB8YfbYgGEiHNwrhJ8GZFvzHHvsYxEC6043hOYzrBPeB/D+8LjxPMA2hXen5455Eno8A1Ui7j6C0xclLd/dQXz8ALeQQvjLfv56UI/fS83E/jbp+ejU9z9GDAYco0R4yC7TgR00sDDtjgOIGqetnXhr4xpvQnfRt3i+1e+Ma0Nb7GiMeyrdOkCft9gm20yLQ5kfJQzyDP2H+15+eBfp4AgzSM8CyovhRd70+0GNgTghGoC1Z7v2fOMFq1bruKmVZidMKkDIECUOqTZIo9ibot0V19UwLNThjKlRF8HAv4nxOZUTH+trzXou6zC0b958lUGe+L4Dy857oS1TXY7qACuFgIl7BrfxK5kPbrG+8iHN2WDQWBeBD8hFDzIZCtmNeCg4dVrP9JYjCfP98D+TB9wiVlHuQJxUYEb3WQ4iQnl+9Ctfak5wnt6e8nDPlG95y3WXuizAk5mXfnqA/WFGOaWXv1cDG3BiJGf3nLhTldMwKF/yxXWaH947xqqFQWmTu/2c/mu5nfN+0bdtDTfM1A/o5FWU5plujGm05iypjSQejRRhEKeDOouzHE6o=
*/