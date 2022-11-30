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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_TUPLE_HPP

/* tuple.hpp
JY8hVjgST16lqOZz6Rymdw87UIuc4Y4VciLk69WdCRav8JBNbe4wjGjmFnkrvT5d5QLuMJV7GZpLPmKBZukXbhx/AtCS+oMYdMvquQ1kAZCgWF8RUipFJlwCYk3Bc5XhVZoAenxUtbwN0MdzA2jYnJ/7ADhecrS//lzUJjtp5XLG53G3gY5tPBDYNgz6WC/BbGbJkr4ooTfJ4XEiWImnbq5OnNcmbP1Ersa+hj3eq1MZ+fD5Jj8U8mXd+66EvUVkUZd29eIZn1zpleD88L0x5x3OTy/Klab4vsYYX3SPVJTQFD41Pi3uSVP1HME2E8jbA+kjD7aTw47eCIEYwQzWk+hr54IdUYEUCfeTg9n6xdYi7x+Bz/jQgDxeAZ3aAghyh6k6aELuOoBFaBt4LxTGcZbRNAluIqeAjiGDj7do4EMK0U67+vxaW3a9PBt2WU97jWPjFTiTYjkeoliOS1uHZwMopoAZT5kFcGeDHZMBjYObLfmPQxTjluMDduT6Ize8gwwb37NyN3+UCnFF22wtAeySA/wgA6KSAtx8EKPs88X6EvSPLQLkcogDVC0CspYCeh9HAfImgN1BAtq/JTH7g1oAoPkx9JMtAYCB9uuVAG97kaLsbxDpQdxdMPtvAO3PXADcigO/TdGBvUlj9ufQIfUrXADQyQK3f0UBtpYAahMBtOZIAL9ZUqPkSwPoVAA4JFTGgkyfLelzgkyzQDSRAzZxwJ4y+X0MiraWAXofAABip+2OYzQsgzpO5fE28b+UAnZoAXCgS2nh+3HlQBlPmgU8FQNmkPifX/D7unK2WNlh/wzW4ogDuzvyAWbjSF1pymD21wDcQYP9ymP240H4r9ch+yti9lvxAdfTBybPQU7WAv9Ykx4PWcRPgR6PWxSmOYzHwZcI+j4++4VS9ljQ73lF6KfmyQqlbBYsSyzooeVK3RYwwxHwfiWAPBsBXuLJs4YgnxWz3HauLXHlctKRLebToM63EjGbAW064ZUJYrlfQ5N9GGP2N31C7CcWNHtAlgB+3dKBjS8B/CgCYL+zw+4Hx80UHEHUf7SwK/H2P6IWMy63FDp/jllIv8cMLC/GJi/qyVL5lJB/5zwt8klQfW9WXVB/A9TJBt37wg+03xwxp+JKBzn8Vp16cuu3Dq2v5rFCcIHEMwW9K0o2x98FZWZ/DPJj60brhRWGo41ylp7d1b3KW89V+khE8KQMWNEOrCUMiJ2mmDeRrFxA2wApsHJHv9zJs/hCVlEAw7cXLj5KztvHaa1GJgb6Mi6kZKLrO8ar5mTTh/in6kQnlj/mGVO+qzHOvKkxpvxQZZj+3y9Vxml2EkV4OW0WsyBqeOw7Jb3eAR9gKz6Ounc81RzbQ9Tv+/jn4gADB8LXX57zbU0zJTUDKREV4CyAOKkd2q71291JodgRgQXfsjFivLGkt1QlY05aVhU4mhm0UiUJYuNtcypYdi3aZCFaEVq9FefgKp40Bfu3n3Djjn3IyFk+XKhsABKLOqWImq/l3FwXqhZNlvQj3bwXbJOv/slJ325Er49MXSL3jHqIK88BczmWSouYqLAmcBq6jBCQRJdPimS3zZixo49LnyUEPl07VzYUZ9c2hwPK5zbZ0n1VvM5IBKdbuSTrL9ndITZ8H5OTBaisjcGz5igovKDqTKpK5im/TL37Ap5vUStc7uC4YXYvpqg7ED8L7dLKMuHcCIkzidxfR9xdq625i19HB9OImtEzTI3+H0kX1wqTZphLxMdApWZv6IFCJKyq6vUylrVnUBA8CHXi7r61ukFrMRifUfWnsVGCTN6Zf6SfYClyflFsvN2uO3jdFznfyX4JFALHrN/d4sj97brNZSFdRQl2RzL0Btb9dIkHADRYwf3vwzyJ+SSn9eQNvFJWo9PvGUtJemYiO4Cl0JoHvL/n6dCX3xEAufkUq/WUioVNx396NlJL71uKD7etJxbWU7FKFTYexyVzVlPPy6kZoZqW5Uz8HDx1hpSy3Dy/GRpZct9aM8nz65bI06hY1dDCCasvqd0W6NyZZBIcWfYWwTU2RfTBvzk/3ogsiKlvPVI0ieHp57O+YO04OOCLm75qrXF073Dv0+t7jyVvrLYbZI4YoEwNCuBYH6lGHpU+A7qaN+f7JWdQ99SpgJ2X1u4JQ6nz5Nz9RfpvIw1wMWbLZG04LQIrWA56WFhHvMXRjngKjW/ztEPzdYZFmNs8k2EsX24+Do+IGlX0ttZFho8OW5/uwYC8I0aVbD8g799nG0Y9FS/rib9SSdaE85uj0kqkGgFwDyToWxon8zQSSEqDaVYos1udtcxD+gl8CMVCEzD5NDL+lCP8EgrFLxoaFvEsG/O8fA4fZAMXOr2b/Jhw72qKT97ZZ+5Qc6AnhrhkjgQgI6SZ/SDk+I8tgNzjTYNofL+UcHXjzEz3vJwfuR73Rw1I5lm5hL0Chg2LFijmFCPxtK27ZdJgztnoreigJfHrEI6JMSZGwe0N1wZRxCWZlhTqv71wgJ0RLOTGws6kXzshnWoGUtXOq41CdbaMXFFlFttrRNaGnsA3AIih7k5K2R6bWqi3uxJh3OFIkndR0PQfNE4aPD6tYtjzh0d1fZRvYh45Kh3bt0ddw4gOIQveCdDwFA5ulC8hN6YeQmkdUgKjRjRvSfLMHwLqll2YaItCPvXxs+Z6WTSwJir/5e7Xl6NZejgHSVEiDz0rjwSjWL7PnfVHid0LfpkxNisnTyLo9ankFFqLnhMnD8lVzoWSJYxUyiLT1RT8rQZTAvRxBic2X1D4x5YbpUi8HIn+FAlki7Qgsm68yMUzDLRO79Gqj8GNccn335eSyDlCc2Xv/BOCdBjuc0z7zN7FKFMZ7jRyLD4JwKSIz3IludlSu6wmppPnB0/utxyTX/Ju0/cLpk6y0e5VvIMYgDCxGSLqVKGCgrq3i/KK9AabUIg9HDa9K0qHtam221KkD4pE5PGLMYnPXzwKVh0rTTOFumDUJTfpwRfOr1iJUgjh6QF0IWSW0c/hNvKLqamF7mY5Y9bi9asZdY2MvugxWGX2c+oSn3rXSkBYCuvW0L5vZJyvVEOH0nlVgHOrf1QJvAcZBtVOIk1HvjEsOkZzeofcHkIT3xJngm6+tqBUIgRjfbvFKxcy/85CLUVLI4eAtfd5gIkK0CLl1PCxszp4jL6y8P1OwCDHNZfcc8PzyCUgxUeAx4hydfPWfRyhb95m+G0pBm8rOwz2TVMappkQKpgndauc+zgt9pZzpypjjzx8co9M6B5zc8ixSI+XB5eREHF8VW+He1jDM3BpZTfohkS09HanVzhfty4VYWTcROrIurp3t+XONuAvZxgEchgwMB9+5uIX4Iw9rQ8C9RHO9f1KxV4OzhTnD3Fn/bM+5/tC8462MXDOxsSviscsKUQr24KTgaqTUVc/EGw4kfSg47auxHInyogSjhJG6tGj3uL0hKmrhCk9MYGZiqFYyKwP9j5BNpBhK0O80ZwhJM3a22ugKKbX9oRUYaVBLDYMdK5XsuIeK88Al1U5BwGWDy3TZF8TKofomam7wOIQ4p9PDYywIld3cB+LW3xVR55n0pH673NuExj3XK/haWJnz7lg+GhxBuX0w6QamGTRq7j4kc279sPuH4Waf1gsZv8hFu180ev9gPluqL9au/WVGDeg1J63HPLPLETYmYqIhdUEQoQ3+Eg5gAEV2BHP5Tm7UWCgN3oDWITU4s6vCHVG7qAkuW0GjV5C6VyDF4iogbuwlFaNCeACL0ipdfQ8g//z2TYwdO/P415cKjjej4N2G3b2wqUq4L7E/mmp2+/Y7rdb7SDMHfM2gD6nTNF5IjgdES82pcH3tngkkMUSG9bh2xZRW2z4cAgOLAynoxBB0oBGEH6KHAao13CK90hYIg/HR5xG1CYYg3z3Pm7myb3gmMiEb/oAdlf2nHtqqsay1Y3p8TT1hH98kn3FngRJ7MzxkDX2ZDfF0M+9Tjc6Xll/AnR71I/i7vmxN/3G37qtvbSbNfbHyb3O0LGVqzZBVoKXUfNiWknXwvFXw/9CCY6pD/CawwODmv8Cw/kmR3C/uV1MLUw6//pidObXFLCvHjMpWX+/LMLPWoGPahitQyYBGmi+7BTcvll4wufP4U4K3gk4Zwt8urgLGG6LUD1IwxumANs7RzkIrgNGf3KqFGknMBT0cJLGgb4YmBdBXlqguwN1NJ4PSwx8Yjkcph0bBk8Cm8oCX7Hxno6zeDxQa8i1gCnCqT7U4uRwuldGVFn+Hlgw3jG0iulws0NlTsXzDO8tDNRTxyz+vjmElqr4fjNw1or3c0O6i8QFRlcw2tlLd3O5PKMSh9eDhfoPCW6kIueNP09NDK+eIAGhryDb945+IuqAonc+WHrJjJvfIxJpTzL3QbYXWfWtjnWYzy37C2GxLChfHjvglfyWSlxYNme8DOKS0iGR0Fb5YkS6z4dMT7LTUM7FjM8faGoj4Fh0ahXWAouGQXmOMkCxaReM2J0O55Pf18d7V3IAOd7Qr96nCq3POHm7RwIvxykU2wMA73Uzc497rQdOVeajYVu/ctiGzb+X5YpYked6NenfzcUhk2sZlTY9f4nh3j1k8QXfcPvJ85tCNEF5ZnDVi57AZkK7a0pMVhgtYHpOqCejA7Fao42stRZDaw19i42s/KXS5inMs+GW75Mtr0+Jph3q5v5rLp8YljXvxQ2pjT1rPhKtvTnhzaiBrtkGr1vb9wDcKxX577ckdpcnuQgstk1lgFufFNKjHW5uNvoNxzrJ3PgZfBsT8hCtyzdJj9Tc78FjJ/PVNi2HYpfzER3B9bzH8qbez8meghXS4t6okkT013ktsegL7EEpM1G84+6El124TeZ85pmDko8A6CZwN0H+uM79HAIvSGaObg/rYQ2Ty0jyA9du/HAFJo265w4m6656Gyb5YGfK6CvDMeBraKsOXpDI813W+7/fo99CQiH0YyHeum30zosFGHA8W6B3M5arkw63DGhl1rRdUAOpdZRO1swDiJPf4UOIgpkIO3ZSkl6pG/Dhozk2xF77Ty0KKmaIQ8EoglhSDH8MdneYtm2wdaqvq/MDCZ5iEIgPxew8XHXkz2QFTTEFn70HKhpFzXEInHgqa3IIT0rU8HciqcgnMLRfimMwA3m6k9Yh55uvyjcymnsmr+qRFUt+PeIft/ue5gV+PqIUkS94eWkr54G9zWGws+SD5xfSUrMHJH/8ljkMMN91SD5jDcMbgzHgnebRf5BiKgktotEJFufSN/UrH2alPgb/EIR/cFl7/kv/rFZU9S2T6gnOs2CC+XJ+E/4B3O7Iqr4kz7UhQTJtzcPrw0Jfo1R7zxnpp1JFabpkufl2Rs6eK2OrNlgh2PaRGkt7v1AKIbCQEsppDMezKJKpmX/u2BRNK9bGogXNAG3T+P5ie3c/72pdCzXMDBPGkE+Zqn4qqLGdA4z+WbiCh5SE49jQRlYaHELn90JAOIHbvr1xUQjsQmp+Ge51Ei2T+BwM7FJ0XxOoNUzXMUQzD3Swezc5nObhDsRlY6v0OKGxskhFa+9KgQ7cjgmzPERD8X1gb+DJbu1gutPHRSMVsi1BiIp+iMApUcgQrIPVw4nKUJJs0h8iWpVfeVxXTIu/wTiuik2vMn85In+qjVaGXdV2YBH1VpyWd3UnbN3GWCM1kOAJ9LZcyDNA2Ku/tUzVgv1MdSu4FdLobde8llKrCuvFUatCK9LsYa9Vdbvmb9lMq1VdMjLXyZWvopKoeflrWifkykmBZo96+Qr0vlhW1DtxiW5Wl79tauo1dNr2dKdSLzGzUAlRZIC5DhZpEl+9APXIy1CyziAjgQXWqMBB6i+d0O5JMvAAINRB8nH99xftV+AxiR8q7elgKy12xNUefyR3cgvn7ufKRU/cDs7tt+R/35Put14/8BZ7uOgqLtc8SdKJgKHTAJAgkOgMysjy1vwRBMwQSIdE7BPjMOGAzQhjiCyDGP1RAofE4xcO7dpRqarF65p6K6g14vIBwvHE4+AK5PnyETQ1XLKVBaIQ/5x6n7U+p4n8e+B/xWczfF4+G140veqeteaKnh/bn98TVh/l9HDafsbtzByvzkQ05+h609qfx0MNt2drxLiTej6AyadP92j9+qlEY2/wuLjcQqjmt2hEqdi/aYPLKkho76/UGsC01YExnrK2OJOsTOt0IzUuJwrnOmizesD2LV5yRL6vuaDNB5sDaGhJXobZScidLUSI76S7JnR5AgkXiTR49xWzcOUOC7T9khwvZF4wtcHiq6WCOefhdppZvyUAOlsE9cAEiIHbDFoBr2pQKn01FVJV42FPA4dLKkHbTXU4gMjCLO8dVjYcD3+ONvuRXvOoCTguj1LlruLi9oRznLpvPX/6UH/Fqkt/68cCnwFTwDMovWW0DaSgnkiQnlv8M6GPzq2VD5R5U8OVEcSdNckQxMpWzumfS3IF0ZLiS1FliXlVaKj3dccVy+RKJitDRJDtoGTSB/d1dbaqZPPSl45pFXhAn3RydI8DUW2xQixHri+fAt+cD3od7f/5zrnmC3N65pS8v6wiHsGMz/BqmJlM5Oi/0Max4gZPQEtc3smK6xz82E4sB/F+bulsKnzbywjtQ7ep83PMxOg6P/WLIMLbgqSvJDc5sLbi2h0/ZcFWPFBhFks2OraI8QF1sBe2t+jljp0IBawhiSPuuVx6vmEyfFGD/0JoYEPCxw7vEhttfUPiCvUPgz1qwLP0NTiEQTLt+zIQlc0WgTL2WDLcU4mtYORUL6/lrtU+MTaXDfm8vwFNs03ZzjYjfhTRG/IFQzf2tp9n9rvBjg2l7gceDZ8xN43Bb1AWdpshszeH/VCk/gJZCumWEMULC9qwU9UtdpqL65bYXPBjR/oXFc4c1gq7Uo315no1l7CKwaviMoKLHquaUmjTtBEYgNGrlaqzVH45RmWWyTaESKw6kLcNrH6Z8tgrL+cFVO4XBPfj18R1tIt0jRjS8lbsGPY0qpu3rddS23IdSQPXQl+zw9F1mVgvS/k8HJ+SU5LyclZfdaSMGbj4Zn8Q6jIwfHuMR2Q0KJFkufq8QcWpu4ZmAHGZQCKRZSkT9BDT6at8eMJEoMN+Ms2qTr3V1+G7bqKN0cFYs7Im1vnSvOcG7E+E42SNYWu4/mef0aGbFzGZfQNcWgXCaEBfGL3UyRtG1KDHce9YVPsIKZIvP00LeMa/zB7nCu3MneCXrRf38ppEl/b5OYVm6Ep7yI2Ecisl/DVjR0w6nlHUjF9YthNNmWlT+D8AHYDifym8jr6HL9eSWWxhFduIIm07V/Rhi7Y//LHUpo2zPi7GuW4fYrNamM3i5tz0jWFFH0FkWn6QpSW0fiTjMr3ycyIv6AZpLrWhNF4FcYM48XPGAjBTPuK9g6mmyIaOuwgtHyKt9vEOiNvh3hC/pOtUvxmeMfk3rdXAP4Bi0MHLP1bhEDgBrZhW/7WGF13iDcKo81Md8Zb/JV44dMjRhfuPYA+WaVbx4L9okk1QhjAYQDR09b84mx/RxApfRnmNqPuJyQR/vmkiIxqpgYSAnfhAzEm0LlVtEPPjzifF53/QDceO4jfP0ppguEVT4A4f2JAQY36Bkfvkd0wnZYCrgR+IoadvkJJnfXA7UMKSFw0U6/4g61BkFa9T
*/