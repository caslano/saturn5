/*!
@file
Forward declares `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REVERSE_HPP
#define BOOST_HANA_FWD_REVERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Reverse a sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `reverse(xs)` is a new sequence containing the same
    //! elements as `xs`, except in reverse order.
    //!
    //!
    //! @param xs
    //! The sequence to reverse.
    //!
    //!
    //! Example
    //! -------
    //! @include example/reverse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct reverse_impl : reverse_impl<S, when<true>> { };

    struct reverse_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr reverse_t reverse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REVERSE_HPP

/* reverse.hpp
vd5VRep2zYrMjtFbT9K5XW+Dxo7ZX70LQy0CO1ZvZUnhduUGdR27H1yjq98WaYWTZqt9bUiHVKkNn/I3VpQoMdoZswZw0LqXl6ejOhBgWAN4rdHFbT4aCHsAV6574Dw5AQ57AAevewH/jodjAL+texDcNgEQtzuWkKZHEc5ZB0dtOdpkODS3x0KurY40glz78CpeX5Xa2NRVpN4xda2nztrKVHWkzhF2Tdd76+kb9SqNY+p93vnaslR11tqGV+zzu9cGpa7Y1DOmbvVVrC1JVbHSMRK8Pv9kbUTqHjeNh+nsJ50INJpy34g1eBv7aVm10RDsrYDF3U9e2UxbejdG4+6ntmymKZ6bjewnv2ykov4OuPZzRNWWZIjeUe1nEdnShl7YbGc/x1QjajDMDgj7wmJd30D5dxdXftIP3wBmbISlTZZsRqbuAH5sNdPgyqod6REPYMlmS23GbI7JG8CVzZaavNlqZwALNNvZYIQWeFZPQqkyAn9uWwHprO91SP685ZHIGGGAm/Hnpp8hqw1wHf7c8h0q8PQBLsGfN3wCCeQAM//nlp2X9QYY7z9vWm9etZWuOCCIa7UzPaBrNqMdEty1GpoY6G0Bph0S9m22dWAA2GprejC4DeMRQsNmjkqbxlSbrUxkKQ5esyH9EKZqNTQ9e9Bq5uBMQqu1A5mq1dZBGYZWS4ey1FZaUt/PVFUOXTJTq/Z+ZqprS73U
*/