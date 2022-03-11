/*!
@file
Defines `boost::hana::infix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_INFIX_HPP
#define BOOST_HANA_FUNCTIONAL_INFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return an equivalent function that can also be applied in infix
    //! notation.
    //!
    //! Specifically, `infix(f)` is an object such that:
    //! @code
    //!     infix(f)(x1, ..., xn) == f(x1, ..., xn)
    //!     x ^infix(f)^ y == f(x, y)
    //! @endcode
    //!
    //! Hence, the returned function can still be applied using the usual
    //! function call syntax, but it also gains the ability to be applied in
    //! infix notation. The infix syntax allows a great deal of expressiveness,
    //! especially when used in combination with some higher order algorithms.
    //! Since `operator^` is left-associative, `x ^infix(f)^ y` is actually
    //! parsed as `(x ^infix(f))^ y`. However, for flexibility, the order in
    //! which both arguments are applied in infix notation does not matter.
    //! Hence, it is always the case that
    //! @code
    //!     (x ^ infix(f)) ^ y == x ^ (infix(f) ^ y)
    //! @endcode
    //!
    //! However, note that applying more than one argument in infix
    //! notation to the same side of the operator will result in a
    //! compile-time assertion:
    //! @code
    //!     (infix(f) ^ x) ^ y; // compile-time assertion
    //!     y ^ (x ^ infix(f)); // compile-time assertion
    //! @endcode
    //!
    //! Additionally, a function created with `infix` may be partially applied
    //! in infix notation. Specifically,
    //! @code
    //!     (x ^ infix(f))(y1, ..., yn) == f(x, y1, ..., yn)
    //!     (infix(f) ^ y)(x1, ..., xn) == f(x1, ..., xn, y)
    //! @endcode
    //!
    //! @internal
    //! ### Rationales
    //! 1. The `^` operator was chosen because it is left-associative and
    //!    has a low enough priority so that most expressions will render
    //!    the expected behavior.
    //! 2. The operator can't be customimzed because that would require more
    //!    sophistication in the implementation; I want to keep it as simple
    //!    as possible. There is also an advantage in having a uniform syntax
    //!    for infix application.
    //! @endinternal
    //!
    //! @param f
    //! The function which gains the ability to be applied in infix notation.
    //! The function must be at least binary; a compile-time error will be
    //! triggered otherwise.
    //!
    //! ### Example
    //! @include example/functional/infix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto infix = [](auto f) {
        return unspecified;
    };
#else
    namespace infix_detail {
        // This needs to be in the same namespace as `operator^` so it can be
        // found by ADL.
        template <bool left, bool right, typename F>
        struct infix_t {
            F f;

            template <typename ...X>
            constexpr decltype(auto) operator()(X&& ...x) const&
            { return f(static_cast<X&&>(x)...); }

            template <typename ...X>
            constexpr decltype(auto) operator()(X&& ...x) &
            { return f(static_cast<X&&>(x)...); }

            template <typename ...X>
            constexpr decltype(auto) operator()(X&& ...x) &&
            { return std::move(f)(static_cast<X&&>(x)...); }
        };

        template <bool left, bool right>
        struct make_infix {
            template <typename F>
            constexpr infix_t<left, right, typename detail::decay<F>::type>
            operator()(F&& f) const { return {static_cast<F&&>(f)}; }
        };

        template <bool left, bool right>
        struct Infix;
        struct Object;

        template <typename T>
        struct dispatch { using type = Object; };

        template <bool left, bool right, typename F>
        struct dispatch<infix_t<left, right, F>> {
            using type = Infix<left, right>;
        };

        template <typename, typename>
        struct bind_infix;

        // infix(f) ^ y
        template <>
        struct bind_infix<Infix<false, false>, Object> {
            template <typename F, typename Y>
            static constexpr decltype(auto) apply(F&& f, Y&& y) {
                return make_infix<false, true>{}(
                    hana::reverse_partial(
                        static_cast<F&&>(f), static_cast<Y&&>(y)
                    )
                );
            }
        };

        // (x^infix(f)) ^ y
        template <>
        struct bind_infix<Infix<true, false>, Object> {
            template <typename F, typename Y>
            static constexpr decltype(auto) apply(F&& f, Y&& y) {
                return static_cast<F&&>(f)(static_cast<Y&&>(y));
            }
        };

        // x ^ infix(f)
        template <>
        struct bind_infix<Object, Infix<false, false>> {
            template <typename X, typename F>
            static constexpr decltype(auto) apply(X&& x, F&& f) {
                return make_infix<true, false>{}(
                    hana::partial(static_cast<F&&>(f), static_cast<X&&>(x))
                );
            }
        };

        // x ^ (infix(f)^y)
        template <>
        struct bind_infix<Object, Infix<false, true>> {
            template <typename X, typename F>
            static constexpr decltype(auto) apply(X&& x, F&& f) {
                return static_cast<F&&>(f)(static_cast<X&&>(x));
            }
        };

        template <typename T>
        using strip = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;

        template <typename X, typename Y>
        constexpr decltype(auto) operator^(X&& x, Y&& y) {
            return bind_infix<
                typename dispatch<strip<X>>::type,
                typename dispatch<strip<Y>>::type
            >::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
        }
    } // end namespace infix_detail

    constexpr infix_detail::make_infix<false, false> infix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_INFIX_HPP

/* infix.hpp
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
*/