/*!
@file
Defines `boost::hana::overload_linearly`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP
#define BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Call the first function that produces a valid call expression.
    //!
    //! Given functions `f1, ..., fn`, `overload_linearly(f1, ..., fn)` is
    //! a new function that calls the first `fk` producing a valid call
    //! expression with the given arguments. Specifically,
    //! @code
    //!     overload_linearly(f1, ..., fn)(args...) == fk(args...)
    //! @endcode
    //!
    //! where `fk` is the _first_ function such that `fk(args...)` is a valid
    //! expression.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/overload_linearly.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto overload_linearly = [](auto&& f1, auto&& f2, ..., auto&& fn) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(fk)(forwarded(x)...);
        };
    };
#else
    template <typename F, typename G>
    struct overload_linearly_t {
        F f;
        G g;

    private:
        template <typename ...Args, typename =
            decltype(std::declval<F const&>()(std::declval<Args>()...))>
        constexpr F const& which(int) const& { return f; }

        template <typename ...Args, typename =
            decltype(std::declval<F&>()(std::declval<Args>()...))>
        constexpr F& which(int) & { return f; }

        template <typename ...Args, typename =
            decltype(std::declval<F&&>()(std::declval<Args>()...))>
        constexpr F which(int) && { return static_cast<F&&>(f); }

        template <typename ...Args>
        constexpr G const& which(long) const& { return g; }

        template <typename ...Args>
        constexpr G& which(long) & { return g; }

        template <typename ...Args>
        constexpr G which(long) && { return static_cast<G&&>(g); }

    public:
        template <typename ...Args>
        constexpr decltype(auto) operator()(Args&& ...args) const&
        { return which<Args...>(int{})(static_cast<Args&&>(args)...); }

        template <typename ...Args>
        constexpr decltype(auto) operator()(Args&& ...args) &
        { return which<Args...>(int{})(static_cast<Args&&>(args)...); }

        template <typename ...Args>
        constexpr decltype(auto) operator()(Args&& ...args) &&
        { return which<Args...>(int{})(static_cast<Args&&>(args)...); }
    };

    struct make_overload_linearly_t {
        template <typename F, typename G>
        constexpr overload_linearly_t<
            typename detail::decay<F>::type,
            typename detail::decay<G>::type
        > operator()(F&& f, G&& g) const {
            return {static_cast<F&&>(f), static_cast<G&&>(g)};
        }

        template <typename F, typename G, typename ...H>
        constexpr decltype(auto) operator()(F&& f, G&& g, H&& ...h) const {
            return (*this)(static_cast<F&&>(f),
                    (*this)(static_cast<G&&>(g), static_cast<H&&>(h)...));
        }

        template <typename F>
        constexpr typename detail::decay<F>::type operator()(F&& f) const {
            return static_cast<F&&>(f);
        }
    };

    constexpr make_overload_linearly_t overload_linearly{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP

/* overload_linearly.hpp
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
*/