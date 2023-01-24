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
Ts2UazFJdywj1Z3lnlVd6mOApV7qjHKF02+neqfmY80F++gy54J87q0tj1uv6I9QzZCfcIPXiKfaJ4aGhSheGO/0B+yjQj4L10sHiZnzGdoF3/nbJbGfOTHk9ATrbLP+3jVH8DKRGsCh/Un+Uk85wiRELd8m037Z9YYyXIXGsiRFNatYFCIFgRXLwFS84v0L/FvaGm7VnGP5Vp5ab4VOQBOTmIsJVeYGBMbqRh0rT2EdV822BtzddXkNeN/07CzF/Obgja9iAd9Nzw+PuARJ+2sugNS+b4Te3U0dBo1lGXyApV2wsqZmpFmWC/6B2G65Z4LanqQvGRyeHIqd4GWPBl4qXoYAVIDXm9wbae9s3GOJudeCk0K6AqAVE3gBURoCvSywjPJouar3+OaYfQSAtBRLqOAVx9sx8rowBo7l7zsog/cMxzvSa9g+sjel97DpbwmsGXQYPA8A7Qzo+lTYG9waSY2njS7qKVxGm3Erw9Zce5bbVy5aDlYk6paWLwZZbkOta3ZYh9GzWwKxjAsDWORZcWqlAstPf7fjNJCUgJRuK50AnUfu5R21A5r96fsVyvM95RcyOkI6AKmUUPL6N4SFqsZfBV+S+d9cbX45XHXaYI0+hFdRVdOVqENqZiTCs47C/JZD37ARVCwfRDc8UV3I4uq6vMw9VFwRWMtrh0DeQIghbJAPxf7Fg8UfVdQHOty486R45/HhPpn+
*/