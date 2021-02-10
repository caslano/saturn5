/*!
@file
Forward declares `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_BACK_HPP
#define BOOST_HANA_FWD_DROP_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop the last `n` elements of a finite sequence, and return the rest.
    //! @ingroup group-Sequence
    //!
    //! Given a finite `Sequence` `xs` with a linearization of `[x1, ..., xm]`
    //! and a non-negative `IntegralConstant` `n`, `drop_back(xs, n)` is a
    //! sequence with the same tag as `xs` whose linearization is
    //! `[x1, ..., xm-n]`. If `n` is not given, it defaults to an
    //! `IntegralConstant` with a value equal to `1`.
    //!
    //! In case `length(xs) <= n`, `drop_back` will simply drop the whole
    //! sequence without failing, thus returning an empty sequence.
    //!
    //!
    //! @param xs
    //! The sequence from which elements are dropped.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to be dropped from the end of the sequence. If `n` is not given, it
    //! defaults to an `IntegralConstant` with a value equal to `1`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_back = [](auto&& xs[, auto const& n]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct drop_back_impl : drop_back_impl<S, when<true>> { };

    struct drop_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;

        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr drop_back_t drop_back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DROP_BACK_HPP

/* drop_back.hpp
m85t7axMwD/wEiAFEy8nhCyC2mO01AV5JKQlniErP1Ms+wxZ+pli3GdeRP/Ah7p4+pJYZnTR6XRHI9sYpqIO8+zQAlOSSSz8OEYmsGZEvk782V+SLwWvMQfpojMYaKXjKx7F0ASGwNwxe3axjCjXJKMEU1YuJw2FexlGqgV6uPHM/YwJPMHUAFxqPkme8CFOppnCn3/6k57ErfjyEh7/5v/OEyFC3VraMTfPcpWmbRbr2C2U/IZA6tKQdVt92ZGQoZRQgUxCB4M2J7lbyprp8eAD1kfos+Anclrwj99av9dNBYzAT3pn3fHH8y6EEe+OuJMKcL1wAYG0rGHPhtiC91v1x3c/7g7XdW+P+nuGIt/ZQ1KoYIESrDrvBizhTmJKT1L0TsZht9M2VzymJe8Mz+KmGGECUecrERqlK6nBJCQwEP3LOHajO2DCK99jl1jHNhfDM8pqahOgsgUOcOtyr6YiLFpr6cZ3YhsDLFDr/Fw1pqBrGz9UuLXkzYaYVptI7cPSWnr+cgbaCQljBHMahwwueqYvQQ7hz51X8OG3FNrvub5WILitPkFfBWXnlXqkYkKVAdrGQMNZSIjFsXH/4uyMfBeK/GAoDMloBlMNC9CAjxYeZrJu1O9B/8swnIs4QMk7aZ+NukdpYAua
*/