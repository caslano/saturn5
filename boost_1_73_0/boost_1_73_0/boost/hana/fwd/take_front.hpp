/*!
@file
Forward declares `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_FRONT_HPP
#define BOOST_HANA_FWD_TAKE_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_front(xs, n)`
    //! is a new sequence containing the first `n` elements of `xs`, in the
    //! same order. If `length(xs) <= n`, the whole sequence is returned and
    //! no error is triggered.
    //!
    //!
    //! @param xs
    //! The sequence to take the elements from.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to keep in the resulting sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_front = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_front_impl : take_front_impl<S, when<true>> { };

    struct take_front_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr take_front_t take_front{};
#endif

    //! Equivalent to `take_front`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_front_c = [](auto&& xs) {
        return hana::take_front(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_front_c_t;

    template <std::size_t n>
    constexpr take_front_c_t<n> take_front_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_FRONT_HPP

/* take_front.hpp
BfYNMnk++AK5evyrieJaKKFDOB0rUPzmgsy4CCsV4Jy+RpqvuM9vntBXGq19yzdGDVauJFqT+3kEm2/7Aihm68a4t+CNYLNxb5d9Y94I9tvXu97B4jTX+rDyIC18PceFZ00/MbGZwfbYwKxtVkBUVg8aGJK1UHXEYyBZm7UckRjAsogwrI99I7iGDBqA9e1vBNcsFR96KZTKGXc1eLG457k77qm1fS6Cnno5XFf2X3e4pfXpeSO4r78R3OoT+kZwax4hQyx9Ejnjq/Mz8sfeea+b+IrEQ/loWKZ3I76qtG3FVxUouPiqquWNr94fH/bPDyzBVaWULbiylotVyFquDRoWPNUGjQyeqnbQwVOjLj54aupCgqdKGrzZys7uC57q8duCJ+mD89jIqQUROnLSgQJFTlF4reSRIAlD6w3IlRLtk6qu7oyMMEerBcSjQuHmwHHFpp8YrmgACcsV2ygBuGI9aCBXbKHq4IogWZu1HFwRYFkEV6x2KTBXrCFzPxLUsiiStejmdLGWt73zTt+c+5SW/hfn6BbI6kmsxXwbcovH8I+mVlwGzGPE/cj0umYXj5G015mMBFSLyyR743FG7Ula+Zp8ttYjzRdVJdI8wYe1NJwWs4TQzPRqXvLxEUKfkdHNlqWO6eVwPk9z
*/