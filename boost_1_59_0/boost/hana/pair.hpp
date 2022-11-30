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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_PAIR_HPP

/* pair.hpp
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
*/