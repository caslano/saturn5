/*!
@file
Defines `boost::hana::pair`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PAIR_HPP
#define BOOST_HANA_PAIR_HPP

#include <boost/hana/fwd/pair.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/ebo.hpp>
#include <boost/hana/detail/intrinsics.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/orderable.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/first.hpp>
#include <boost/hana/fwd/second.hpp>

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <int> struct pix; // pair index
    }

    //////////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename First, typename Second>
#ifdef BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE
    struct __declspec(empty_bases) pair : detail::operators::adl<pair<First, Second>>
#else
    struct pair : detail::operators::adl<pair<First, Second>>
#endif
                , private detail::ebo<detail::pix<0>, First>
                , private detail::ebo<detail::pix<1>, Second>
    {
        // Default constructor
        template <typename ...dummy, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(First, dummy...) &&
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(Second, dummy...)
        >::type>
        constexpr pair()
            : detail::ebo<detail::pix<0>, First>()
            , detail::ebo<detail::pix<1>, Second>()
        { }

        // Variadic constructors
        template <typename ...dummy, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(First, First const&, dummy...) &&
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(Second, Second const&, dummy...)
        >::type>
        constexpr pair(First const& fst, Second const& snd)
            : detail::ebo<detail::pix<0>, First>(fst)
            , detail::ebo<detail::pix<1>, Second>(snd)
        { }

        template <typename T, typename U, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_CONVERTIBLE(T&&, First) &&
            BOOST_HANA_TT_IS_CONVERTIBLE(U&&, Second)
        >::type>
        constexpr pair(T&& t, U&& u)
            : detail::ebo<detail::pix<0>, First>(static_cast<T&&>(t))
            , detail::ebo<detail::pix<1>, Second>(static_cast<U&&>(u))
        { }


        // Possibly converting copy and move constructors
        template <typename T, typename U, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(First, T const&) &&
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(Second, U const&) &&
            BOOST_HANA_TT_IS_CONVERTIBLE(T const&, First) &&
            BOOST_HANA_TT_IS_CONVERTIBLE(U const&, Second)
        >::type>
        constexpr pair(pair<T, U> const& other)
            : detail::ebo<detail::pix<0>, First>(hana::first(other))
            , detail::ebo<detail::pix<1>, Second>(hana::second(other))
        { }

        template <typename T, typename U, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(First, T&&) &&
            BOOST_HANA_TT_IS_CONSTRUCTIBLE(Second, U&&) &&
            BOOST_HANA_TT_IS_CONVERTIBLE(T&&, First) &&
            BOOST_HANA_TT_IS_CONVERTIBLE(U&&, Second)
        >::type>
        constexpr pair(pair<T, U>&& other)
            : detail::ebo<detail::pix<0>, First>(hana::first(static_cast<pair<T, U>&&>(other)))
            , detail::ebo<detail::pix<1>, Second>(hana::second(static_cast<pair<T, U>&&>(other)))
        { }


        // Copy and move assignment
        template <typename T, typename U, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_ASSIGNABLE(First&, T const&) &&
            BOOST_HANA_TT_IS_ASSIGNABLE(Second&, U const&)
        >::type>
        constexpr pair& operator=(pair<T, U> const& other) {
            hana::first(*this) = hana::first(other);
            hana::second(*this) = hana::second(other);
            return *this;
        }

        template <typename T, typename U, typename = typename std::enable_if<
            BOOST_HANA_TT_IS_ASSIGNABLE(First&, T&&) &&
            BOOST_HANA_TT_IS_ASSIGNABLE(Second&, U&&)
        >::type>
        constexpr pair& operator=(pair<T, U>&& other) {
            hana::first(*this) = hana::first(static_cast<pair<T, U>&&>(other));
            hana::second(*this) = hana::second(static_cast<pair<T, U>&&>(other));
            return *this;
        }

        // Prevent the compiler from defining the default copy and move
        // constructors, which interfere with the SFINAE above.
        ~pair() = default;

        friend struct first_impl<pair_tag>;
        friend struct second_impl<pair_tag>;
        template <typename F, typename S> friend struct pair;
    };
    //! @endcond

    template <typename First, typename Second>
    struct tag_of<pair<First, Second>> {
        using type = pair_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<pair_tag> {
            static constexpr bool value = true;
        };
        template <>
        struct orderable_operators<pair_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Product
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<pair_tag> {
        template <typename F, typename S>
        static constexpr pair<
            typename detail::decay<F>::type,
            typename detail::decay<S>::type
        > apply(F&& f, S&& s) {
            return {static_cast<F&&>(f), static_cast<S&&>(s)};
        }
    };

    template <>
    struct first_impl<pair_tag> {
        template <typename First, typename Second>
        static constexpr decltype(auto) apply(hana::pair<First, Second>& p) {
            return detail::ebo_get<detail::pix<0>>(
                static_cast<detail::ebo<detail::pix<0>, First>&>(p)
            );
        }
        template <typename First, typename Second>
        static constexpr decltype(auto) apply(hana::pair<First, Second> const& p) {
            return detail::ebo_get<detail::pix<0>>(
                static_cast<detail::ebo<detail::pix<0>, First> const&>(p)
            );
        }
        template <typename First, typename Second>
        static constexpr decltype(auto) apply(hana::pair<First, Second>&& p) {
            return detail::ebo_get<detail::pix<0>>(
                static_cast<detail::ebo<detail::pix<0>, First>&&>(p)
            );
        }
    };

    template <>
    struct second_impl<pair_tag> {
        template <typename First, typename Second>
        static constexpr decltype(auto) apply(hana::pair<First, Second>& p) {
            return detail::ebo_get<detail::pix<1>>(
                static_cast<detail::ebo<detail::pix<1>, Second>&>(p)
            );
        }
        template <typename First, typename Second>
        static constexpr decltype(auto) apply(hana::pair<First, Second> const& p) {
            return detail::ebo_get<detail::pix<1>>(
                static_cast<detail::ebo<detail::pix<1>, Second> const&>(p)
            );
        }
        template <typename First, typename Second>
        static constexpr decltype(auto) apply(hana::pair<First, Second>&& p) {
            return detail::ebo_get<detail::pix<1>>(
                static_cast<detail::ebo<detail::pix<1>, Second>&&>(p)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PAIR_HPP

/* pair.hpp
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
*/