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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr apply_t apply{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_APPLY_HPP

/* apply.hpp
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
*/