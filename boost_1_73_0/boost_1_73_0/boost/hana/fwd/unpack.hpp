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
621+rCIvm+vKbu88ymn37P5ep9zzM3vPz2BnOqa5hrzmoz3RIDHgaacR4PwOnu3UuttiwdOgSPC0s+OdVrzoavKMrKDuuHLuiSrb5eoi2C7nmRZ7uYYzKpqcdxRLzkMjyXlEHDlHRZFzLDOYIyLI+Wrjx3l09DgPiR3DIFvJAZFO+y13rlV62J6Y6+ratQi7tFq4bcdFEda/iQOjdkDYqr7gsLT9hn0ZMptf7y7S4qN4S+D+hPz6yfp/28+fP5H+u7/+x6tWcztNc4RhaRUkefULlVSP4cftXZfAzvDjc73DR7TivFyo51110U6r6Omj5LF8L0ml8eYfRO7hPzcfvlKKhrxg88toUy/Y4gXDl3rBNi/Y3dELnvGCzS29YKddYNKTD6aZ53tv2N69wVvZqMZSv/Mh/r2uHuN9J5pqneVZbm7JeEO0c7rKiDbhlav+CJKIWlfp1ehqvlYP6f7Wj9tPtnZfPtna3HyydZ+w4mfrVJ9NaJsGQHcthid9F2m5xnySraMNnrtDBU3mtcJDJqleIDzk5aZe8FLYe1sv+JEXbO20mhKd7ExaJaKXSbtk26pY5YkXrRLhii92WyXPxUR4qZdsPwe5767FfXc3EoG0MImCt9l/d9H+u9v47y7ef3cj/JcP6f4kfbn5
*/