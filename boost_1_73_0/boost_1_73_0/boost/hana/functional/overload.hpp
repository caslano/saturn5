/*!
@file
Defines `boost::hana::overload`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP
#define BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Pick one of several functions to call based on overload resolution.
    //!
    //! Specifically, `overload(f1, f2, ..., fn)` is a function object such
    //! that
    //! @code
    //!     overload(f1, f2, ..., fn)(x...) == fk(x...)
    //! @endcode
    //!
    //! where `fk` is the function of `f1, ..., fn` that would be called if
    //! overload resolution was performed amongst that set of functions only.
    //! If more than one function `fk` would be picked by overload resolution,
    //! then the call is ambiguous.
    //!
    //! ### Example
    //! @include example/functional/overload.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto overload = [](auto&& f1, auto&& f2, ..., auto&& fn) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(fk)(forwarded(x)...);
        };
    };
#else
    template <typename F, typename ...G>
    struct overload_t
        : overload_t<F>::type
        , overload_t<G...>::type
    {
        using type = overload_t;
        using overload_t<F>::type::operator();
        using overload_t<G...>::type::operator();

        template <typename F_, typename ...G_>
        constexpr explicit overload_t(F_&& f, G_&& ...g)
            : overload_t<F>::type(static_cast<F_&&>(f))
            , overload_t<G...>::type(static_cast<G_&&>(g)...)
        { }
    };

    template <typename F>
    struct overload_t<F> { using type = F; };

    template <typename R, typename ...Args>
    struct overload_t<R(*)(Args...)> {
        using type = overload_t;
        R (*fptr_)(Args...);

        explicit constexpr overload_t(R (*fp)(Args...))
            : fptr_(fp)
        { }

        constexpr R operator()(Args ...args) const
        { return fptr_(static_cast<Args&&>(args)...); }
    };

    struct make_overload_t {
        template <typename ...F,
            typename Overload = typename overload_t<
                typename detail::decay<F>::type...
            >::type
        >
        constexpr Overload operator()(F&& ...f) const {
            return Overload(static_cast<F&&>(f)...);
        }
    };

    constexpr make_overload_t overload{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP

/* overload.hpp
dnRscy9zZWN0cmFuc3AuaFVUBQABtkgkYK1UUU/bMBB+76/41L4AyhKG9rQhRFW6UW1qUVOEOiFFbnIh3hw7sh0oEz9+51BaIY31BUfJXez7vu/uLHsgS11Qicvx8GI8z0bX8x9ZOh4t5sNpepVd9ga8KDW9uZ4cvd/o4Qh7R9a9GQ+2HeLKml+U+39HZ9kTnh9G3bLdJ5JgB3nKDrEf8oSDDpJtVE6Dn2X7hG5DbuGTBORtFlyeYVhAjkzzaOVd5XEwOsTJ8ccTfAjmU4SpzH/jp/R/aqF1hFPN/8E/v6uFVHFu6rP4PxQnxxEuhJakkHrSK7J3TFJ0M+eVWK9jR2cRyEOoeJPNopIOzpT+QVgC+0rmpB0VEA4FudzKFf9IDV8RSqkIo9nVcjL9FuGhknkVSB5NC1eZVhWoxD3BUk7y/pmjEdbDlAxn8kI6z4Stl0bHrE3wZGsXOIK8UM5A3HOtYsVCwqPyvnGfkyRvreLsk8LkLslfyo8rX28rWXIStXiEaTy8QesoQoiMUJtClsFyQ3iyaVdKuiraZcNSukiMhSOlAhfjJLnntAnppj1RCEPDGUsfjDPaBamHytSvArmPgaVsrWYh7gMHFYbbHKHlM2m74K7yF4lNT7sGv7k1u3wLGM3JoD9MMUn7
*/