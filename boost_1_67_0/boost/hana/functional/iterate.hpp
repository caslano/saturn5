/*!
@file
Defines `boost::hana::iterate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ITERATE_HPP
#define BOOST_HANA_FUNCTIONAL_ITERATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Applies another function `n` times to its argument.
    //!
    //! Given a function `f` and an argument `x`, `iterate<n>(f, x)` returns
    //! the result of applying `f` `n` times to its argument. In other words,
    //! @code
    //!     iterate<n>(f, x) == f(f( ... f(x)))
    //!                         ^^^^^^^^^^ n times total
    //! @endcode
    //!
    //! If `n == 0`, `iterate<n>(f, x)` returns the `x` argument unchanged
    //! and `f` is never applied. It is important to note that the function
    //! passed to `iterate<n>` must be a unary function. Indeed, since `f`
    //! will be called with the result of the previous `f` application, it
    //! may only take a single argument.
    //!
    //! In addition to what's documented above, `iterate` can also be
    //! partially applied to the function argument out-of-the-box. In
    //! other words, `iterate<n>(f)` is a function object applying `f`
    //! `n` times to the argument it is called with, which means that
    //! @code
    //!     iterate<n>(f)(x) == iterate<n>(f, x)
    //! @endcode
    //!
    //! This is provided for convenience, and it turns out to be especially
    //! useful in conjunction with higher-order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a function \f$ f : T \to T \f$ and `x` and argument of data
    //! type `T`, the signature is
    //! \f$
    //!     \mathtt{iterate_n} : (T \to T) \times T \to T
    //! \f$
    //!
    //! @tparam n
    //! An unsigned integer representing the number of times that `f`
    //! should be applied to its argument.
    //!
    //! @param f
    //! A function to apply `n` times to its argument.
    //!
    //! @param x
    //! The initial value to call `f` with.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/iterate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto iterate = [](auto&& f) {
        return [perfect-capture](auto&& x) -> decltype(auto) {
            return f(f( ... f(forwarded(x))));
        };
    };
#else
    template <std::size_t n, typename = when<true>>
    struct iterate_t;

    template <>
    struct iterate_t<0> {
        template <typename F, typename X>
        constexpr X operator()(F&&, X&& x) const
        { return static_cast<X&&>(x); }
    };

    template <>
    struct iterate_t<1> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(static_cast<X&&>(x));
        }
    };

    template <>
    struct iterate_t<2> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(static_cast<X&&>(x)));
        }
    };

    template <>
    struct iterate_t<3> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(static_cast<X&&>(x))));
        }
    };

    template <>
    struct iterate_t<4> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(f(static_cast<X&&>(x)))));
        }
    };

    template <>
    struct iterate_t<5> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(f(f(static_cast<X&&>(x))))));
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 6) && (n < 12)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 6>{}(f,
                f(f(f(f(f(f(static_cast<X&&>(x)))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 12) && (n < 24)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 12>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 24) && (n < 48)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 24>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 48)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 48>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
                ))))))))))))
                ))))))))))))
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct make_iterate_t {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const
        { return hana::partial(iterate_t<n>{}, static_cast<F&&>(f)); }

        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n>{}(static_cast<F&&>(f),
                                  static_cast<X&&>(x));
        }
    };

    template <std::size_t n>
    constexpr make_iterate_t<n> iterate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ITERATE_HPP

/* iterate.hpp
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
*/