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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr unpack_t unpack{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_UNPACK_HPP

/* unpack.hpp
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
*/