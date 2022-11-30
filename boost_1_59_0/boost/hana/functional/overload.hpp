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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_overload_t overload{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP

/* overload.hpp
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
*/