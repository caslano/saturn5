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
AtlqqmEV3r58Am/1vPnTRnZ9kONonRXEveRAo1uu0flv5u8t5/2RHQGyWnHsL7Nn3AZFlZrKSvzu0cZuQaUwWkCCtTwiUWqhG4Na0pRP+ppu0rvEGZGE3GIaLf7sDVecuAniiuYssoZcPt844KD2UVIvUwAZINReKdks502o866Nbfo34Ccok8iVMNkudzqoFCVyylLcZeUkJW/eOtRP2OPe44t5oQb5pIV1Sh4i2CC1ouhR6vLnnpTrEziLLPVqIibJsDd+o37t5wRIqVcPx9pWXpsbqdwwcRwBf9pLx46otj3aeF4nHr6VTSdbBexs6lt9eHnoDemrUcpkNfQ01t8HVMZTMeSkjLjWVwsijnkv6Iok0owg+2JA83e75d7W87htHOgZZ89X5O5VnxfHHfk+2X/TSmrVGvfctUbk1Lpk5krR3PtDTdPqDST2v072kvo4PbTn0ugqF7xsy9SAYPrKDDZezhU6tcK0m8uJiVl/MhaFjrCC1ym7yqVGilcK6K96IVP3v2D1NlLT06JM1DsMZcCf3w+nUvhfwPNs1Cuz1R7gMYORxyvwCg==
*/