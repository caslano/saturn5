/*!
@file
Defines `boost::hana::apply`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_APPLY_HPP
#define BOOST_HANA_FUNCTIONAL_APPLY_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Invokes a Callable with the given arguments.
    //!
    //! This is equivalent to [std::invoke][1] that will be added in C++17.
    //! However, `apply` is a function object instead of a function, which
    //! makes it possible to pass it to higher-order algorithms.
    //!
    //!
    //! @param f
    //! A [Callable][2] to be invoked with the given arguments.
    //!
    //! @param x...
    //! The arguments to call `f` with. The number of `x...` must match the
    //! arity of `f`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/apply.cpp
    //!
    //! [1]: http://en.cppreference.com/w/cpp/utility/functional/invoke
    //! [2]: http://en.cppreference.com/w/cpp/named_req/Callable
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto apply = [](auto&& f, auto&& ...x) -> decltype(auto) {
        return forwarded(f)(forwarded(x)...);
    };
#else
    struct apply_t {
        template <typename F, typename... Args>
        constexpr auto operator()(F&& f, Args&&... args) const ->
            decltype(static_cast<F&&>(f)(static_cast<Args&&>(args)...))
        {
            return static_cast<F&&>(f)(static_cast<Args&&>(args)...);
        }

        template <typename Base, typename T, typename Derived>
        constexpr auto operator()(T Base::*pmd, Derived&& ref) const ->
            decltype(static_cast<Derived&&>(ref).*pmd)
        {
            return static_cast<Derived&&>(ref).*pmd;
        }

        template <typename PMD, typename Pointer>
        constexpr auto operator()(PMD pmd, Pointer&& ptr) const ->
            decltype((*static_cast<Pointer&&>(ptr)).*pmd)
        {
            return (*static_cast<Pointer&&>(ptr)).*pmd;
        }

        template <typename Base, typename T, typename Derived, typename... Args>
        constexpr auto operator()(T Base::*pmf, Derived&& ref, Args&&... args) const ->
            decltype((static_cast<Derived&&>(ref).*pmf)(static_cast<Args&&>(args)...))
        {
            return (static_cast<Derived&&>(ref).*pmf)(static_cast<Args&&>(args)...);
        }

        template <typename PMF, typename Pointer, typename... Args>
        constexpr auto operator()(PMF pmf, Pointer&& ptr, Args&& ...args) const ->
            decltype(((*static_cast<Pointer&&>(ptr)).*pmf)(static_cast<Args&&>(args)...))
        {
            return ((*static_cast<Pointer&&>(ptr)).*pmf)(static_cast<Args&&>(args)...);
        }
    };

    BOOST_HANA_INLINE_VARIABLE constexpr apply_t apply{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_APPLY_HPP

/* apply.hpp
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
*/