/*!
@file
Forward declares `boost::hana::intersperse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSPERSE_HPP
#define BOOST_HANA_FWD_INTERSPERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Insert a value between each pair of elements in a finite sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a finite `Sequence` `xs` with a linearization of
    //! `[x1, x2, ..., xn]`, `intersperse(xs, z)` is a new sequence with a
    //! linearization of `[x1, z, x2, z, x3, ..., xn-1, z, xn]`. In other
    //! words, it inserts the `z` element between every pair of elements of
    //! the original sequence. If the sequence is empty or has a single
    //! element, `intersperse` returns the sequence as-is. In all cases,
    //! the sequence must be finite.
    //!
    //!
    //! @param xs
    //! The sequence in which a value is interspersed.
    //!
    //! @param z
    //! The value to be inserted between every pair of elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/intersperse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto intersperse = [](auto&& xs, auto&& z) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct intersperse_impl : intersperse_impl<S, when<true>> { };

    struct intersperse_t {
        template <typename Xs, typename Z>
        constexpr auto operator()(Xs&& xs, Z&& z) const;
    };

    constexpr intersperse_t intersperse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSPERSE_HPP

/* intersperse.hpp
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
*/