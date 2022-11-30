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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr infix_detail::make_infix<false, false> infix{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_INFIX_HPP

/* infix.hpp
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
*/