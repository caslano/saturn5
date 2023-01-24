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
dVYwsaGbhfSItFGr1ZHHPto3iGlypteB79zxrGv8KsgQeIVykYHeBMpeHDdEOiYaHU6dHsTkoo0+Hxx4vO2+3vh1aD4mU3ZZ8I/yxcBzX7AQGn8omnROYEguy1ILnrNcidXzkIksu/AK8Vt84Iv9MEH07typ1IFkirkX3F5fHenCw2Jzd6eMNEHucUgd1BMki8psR1mIy3E1yy7HnIf/mFFuBZYQ8a1ghjsxxuI7oulKamLY+PPwQaEasYY626ulOrfeB+N+YyxY7PASdLknz5ib28XGehzfi+7tpOjwdczj73lZ5wwTpOIk2v/pHwpyRfi44ID4XOuvXbyOwevGSecxFoodXWS7k7m1KZXzJSMHefLb/TVvfJlumn7NInMVHVQV9ttd0rmh7KBk/fkiIdYzYt2mUxHXdfOm1M7RTHnE4wiA8wHC8XB6M2KFFgVnfpThcDgj/nADutTq0kmWy1kzHgHyh/9cUwnYT8FF5cK4x8ApOKoxpmceKHisNNj6r+KlR7ZrHPTEHbPTlxuxJ98DCvuHeTmczOQh5xQu2f3hydLkdd88gVaBwx3wCj1TJkljrUpG6AxpLoctFuXKleHmXopOR9efD+3UJiqUsgRtLB3ALNZDRg0OtL+rlrI0hZtfOQBvIh28EAofev0mBpYseFNkySKqJxMLXqKjS9eOHTSzoaxsg8lNlhEbmQy5mZRhR9f3eaCs9iwM
*/