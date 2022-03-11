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
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
*/