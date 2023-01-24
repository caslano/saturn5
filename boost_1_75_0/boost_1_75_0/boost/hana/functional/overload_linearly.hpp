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
D9atJnZWvoXvt+OZfoHwnRs+HjRV6mEmiE3yeO0dkfVjp00JDvL6WoE6fq3H9+L7tPd0n3DXss7CrFIvZs1nfeVFBrpNpu5uFJjDR9b1ceSbS9KZNmJ4BsP9Wt+TGk2UT1iKWww55upEQismzGA5hktSGpeKDQOPvUOeeDaOXTGlI2bkhrr7rII+iEYqznZBbJFY26eYmbAfAcIuEv+Az6SCeD68QXsMETDwDkO6PepwxtFOlLC6MGEFco2yU2JJOakssFSWAyHwxhb5zc4zh77IhDU2UofuCAfjHhxZFuWn0OhB4NclchCE/FfVIA9D+2BBK7pkbAMO24XyfOxOZo4UtGMXWUT0dsl9MfX6NJiWAEMr8Tcw8HDqRbSajQ3A4DiwfV48lkEbOgSQ5cUhYQa5vBdL7uQdpEXLkxMa9fT1E9lBeQrf04bGwKcZg1OmOi3JulXqkBtGuP1aF7U+DBZo3SA0E0T5QLo8GTphBeRk1csSIz5eIkWbwvtp7ZWpUSzPOi1/gpFHtobf1tBOQVsVN/iNoa+ss13UqmVToeKNQK2fusU37mk4sZHuFQEVoskWosksZTQI5LACm/4wjO3XQO+40bpdG7HkgPiMxhW+hZDB1u3XRuYCA+Y49qztE8nRScNYXiYs+7SxG3ahxBPrr6pxgHjTy7q9Y9NBnDWA7KnkBMaOWZPftP5aTryGx1mTcPMCd9JWiLlT
*/