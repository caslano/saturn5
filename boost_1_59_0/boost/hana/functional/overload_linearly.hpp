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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_overload_linearly_t overload_linearly{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP

/* overload_linearly.hpp
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
*/