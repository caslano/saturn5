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
T2miDNKWmXH+SGbChwq7guD76dx7Jz0pzicJaFIoqUHenkFlpIAf+ZfR1XEjatTbLaMnUHvnao7OEEQJh8uPgpt0fBqN3R5LmmodPiaKBT8Jmf5M9V7EZzF0ihg9NA9kjSt9O/gEq61JZSXYMH14KDCp/xmnqUUcpX2vrlnMKEFJdZ0fSu7gLsnGvZIJBx65ZtolqMJ9K7HbZzLB9E5MyjSh0wD8H/fjROrNae3OLi2JO9peHaCj/r1Gs6S+1TEMDahAT/N0DCvbtpIK9L82SjXiAQLItJm/KzJbCG+5olGZPiXAQ+QiSi2d8BeU4FwBE9rPYFys1v3YJvZH8BWz1wCvdQ1izYvSX16bcdEodcRjufGUIQcgv3edZjdLJAhsYYCrC8UxUtEJciKpe54pi5Hyvy/wZRJBcegFVBD5vchqXbgktlLOT1zYXZmlxGh/M5bS8VDImLnhrG74A4+IQXCYEdxp+9uwYjkJ9Zor+KMOQ5pB6H0TcprNRsk3q9J1KEPtyCP8Az+Rty1x3EgtVRVY6HwPE5cet2xs+jjfG+YB9EA15a4fQIkCKQ==
*/