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
4uNUxqIoDluWDWIvccwyiTMsTjWTeCjJmTLJ49wjdXrDN5s7zI8GaJDPHWucLxFABTUkZOb1Ed88+orzuqp6/cSnMbdY3JPD5OtkxLQEiLSVBMOi3Extr2l+mbR9wM4eIs5BMDNTW4C9OTIHXQAUJxML1NIZ/1O02G64CsT7ZtgbZthL5NJbRaMRUiWe5BAh/owvLtwowcgSeZo9OnGBxxIrkIeofuEZa65ZZxgJcLbJpy+fyxPL5l415KU/tOUH3cz9YpFMX5pZoFesHmMW2NNIgAKlknJmgT76Q4FfuswC35OMt4cB+1muWc4KSzqcNp5i6hCTK/6DzOPl811Rmo64VglwWZKZJR+9QAljs4/F6xCBVRTyx88Hc1GKyQ8h6L100PGy2kATTmLM+kVjjqltsMeAWUQ7m+eIH6ZFttQUCVYGVO/BaxyxzE9X9bxlP7A+aJFgnZxOe4tFgT8iHagzjy4rLRT9VURsHkoljr4wW34cm06y48/yVMIfUGaEvGeGjAI4LOAVj52o5FBDaXbwkV//FIsWWo1jImcmk0+iwtswtAzLe25m8wuQpo75/MA3nrD/5T8abp0f/zAGyCtOQafsd6fP61+YX0f8WCFbvISWDFuuktYcQYWGGfnOqlQvudvAaFU4aSEKir6HG2vzKuuB1lq1/mH1E7dzZY6spGr/Pm6kpJc+oBOmYY06kBYTFYyxrqbYzNOQuNhjgQR0GWGdRGrgBSvWxDvPSKxPcSKWh4MN6yMqUAhbFmtFO7rUmSlwovRkBcmEn3fgfyaLax3mo+zuJZexuLc0FcdaMnSQQt35EQoI06vNeRJxz0zFneGwcJhJTmuX5MTU+eVI8u5hKslwJHFyYylVgVyd/SGkedJM0y0sftpJ8nFbmu2J51K1S1OxzhFxu4MDeYC2uQxG7990vC3lq1ceL8///CwHiYRIgszjdaNDjZePCG1IJB3molaKnpfifiyJkEyopPHjRlZ6YqOhWhU7PnU+M2U39lRxfVLnMz+2zAzJnSbLmVbHCMFuwupi8N99xQ9RKht62ImkXWun1WGwZRKxqZw47G02JdZ5zXDli+fZxeMPF1JTPNpQF5YrBtqJ49YcRaiqWLTGuyu0Y4EZXmisMT7xZg8FLYv+/WKDGeAo2trchRkMHlLJt2/mauWC2r2rMaK1aOi/XGInz8NXH0fv8fEpd9HWou0j6zzupc8igtsonraZq9KfEUidHWDh2nZbhnANCDgVvXz2eOrli6yqb+dYldKChyS94SAtqCgXUSd2Uj03nlpOA79WHsqqzqSRv98M6h+1Ej841qcCXI2VzME+Sf/JnlzG1TlqwM7IbnxaAlYnyce3PgyHnovspt1LASBNYHr2m63f2EOp4gf00liN0oJxV4xqOe8DU+DfIM8BDgwAUXCimXR5iTpf/YkdOR1Sdeolld5cAZ7itJ6GA5SPPW2b4vcO7bB4vB8GsZ4KzXhfN2oRb6kdaXyAdh0fgp0OvtyjvSL5cme+wZc3BDUSmfKaU1nEefaz+1H77RjB5xV3fdFCA22mM/dTNmo1UtBH3IMbOdzYdLw1M/6y9vGWzPiois9u3xZUL9t3mPaYah+//K+9LZs4eGgHTZx1rNHEg7oMldnebr1as9qr3pcfiDJpla8KJ1o7uy99iOrKW9ra3+nhJ6jdS8ciRD3p5QtyA/OFu7WFD/Hk4jJFt9DWMSjucMo1zoEZM5674EUcDFFOF1n0QFUyw1DY5k1xkx7ox3NJHkncsbvF1OWoJXBBYflrgPKgYUhAgcLAFAi7VETMlxP+OQbm6aDokwHMwwxMmQGMB8AUmsDcSMBwfJ4Chjx9soFhoS+UKHs=
*/