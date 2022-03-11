/*!
@file
Forward declares `boost::hana::unpack`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNPACK_HPP
#define BOOST_HANA_FWD_UNPACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Invoke a function with the elements of a Foldable as arguments.
    //! @ingroup group-Foldable
    //!
    //! Given a function and a foldable structure whose length can be known at
    //! compile-time, `unpack` invokes the function with the contents of that
    //! structure. In other words, `unpack(xs, f)` is equivalent to `f(x...)`,
    //! where `x...` are the elements of the structure. The length of the
    //! structure must be known at compile-time, because the version of `f`'s
    //! `operator()` that will be compiled depends on the number of arguments
    //! it is called with, which has to be known at compile-time.
    //!
    //! To create a function that accepts a foldable instead of variadic
    //! arguments, see `fuse` instead.
    //!
    //!
    //! @param xs
    //! The structure to expand into the function.
    //!
    //! @param f
    //! A function to be invoked as `f(x...)`, where `x...` are the elements
    //! of the structure as-if they had been linearized with `to<tuple_tag>`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/unpack.cpp
    //!
    //!
    //! Rationale: `unpack`'s name and parameter order
    //! ----------------------------------------------
    //! It has been suggested a couple of times that `unpack` be called
    //! `apply` instead, and that the parameter order be reversed to match
    //! that of the [proposed std::apply function][1]. However, the name
    //! `apply` is already used to denote normal function application, an use
    //! which is consistent with the Boost MPL library and with the rest of
    //! the world, especially the functional programming community.
    //! Furthermore, the author of this library considers the proposed
    //! `std::apply` to have both an unfortunate name and an unfortunate
    //! parameter order. Indeed, taking the function as the first argument
    //! means that using `std::apply` with a lambda function looks like
    //! @code
    //! std::apply([](auto ...args) {
    //!     use(args...);
    //! }, tuple);
    //! @endcode
    //!
    //! which is undeniably ugly because of the trailing `, tuple)` part
    //! on the last line. On the other hand, taking the function as a
    //! second argument allows one to write
    //! @code
    //! hana::unpack(tuple, [](auto ...args) {
    //!     use(args...);
    //! });
    //! @endcode
    //!
    //! which looks much nicer. Because of these observations, the author
    //! of this library feels justified to use `unpack` instead of `apply`,
    //! and to use a sane parameter order.
    //!
    //! [1]: http://en.cppreference.com/w/cpp/experimental/apply
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto unpack = [](auto&& xs, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct unpack_impl : unpack_impl<T, when<true>> { };

    struct unpack_t {
        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr unpack_t unpack{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNPACK_HPP

/* unpack.hpp
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
*/