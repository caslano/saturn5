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
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
*/