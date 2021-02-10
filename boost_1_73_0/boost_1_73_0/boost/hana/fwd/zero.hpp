/*!
@file
Forward declares `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZERO_HPP
#define BOOST_HANA_FWD_ZERO_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of `plus`.
    //! @ingroup group-Monoid
    //!
    //! @tparam M
    //! The tag (a `Monoid`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zero.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto zero = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct zero_impl : zero_impl<M, when<true>> { };

    template <typename M>
    struct zero_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename M>
    constexpr zero_t<M> zero{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZERO_HPP

/* zero.hpp
iOzqdhnFLlE7jdISdreRKodbPGDXUfqN3nnMYAbtPkY0oTuQDApmFzJZwbcTwSyH3Y2UGYDfkWQAALuSyW4hO5PBaN7dqX+y/2vvvLt9qZiN/kzLu5Ml5foac6UcGvzWxet586a/Hx5TyW1H4pQr50qfWiSkWWWRaEEAT6gKEyPTqq2dTdvXPmc5bXjbXHpRjHm39/SdTdm9uIwhlaZuWn8E5XMrnMKyulVtaG6Xy6N2o2buQfK8XNqa7UXZIyAbrKEZlBNWMQVnhqOgXQmpw4DtzCJbJ0C3vC3YeIY2kFwt3Hh4flb1FcvMWnCFcDIdLyAbE4NH5J41hD0ZaIC03Xoedue1NZLX8Z0ZlZkW8PlZXMvGDm4g5aoDeJ7qCECG131GWiBzk3lpw9AC2Zo/R82HC8lUOyR96YbwxW3VueuoHQqQ2242rm+V4dbNFL+XBWe71eox5g/d47rLf1thDd/zgnPhGjiIXITFIqD9qvvsuLpGBWQkNCCgu1kX+XKzCaG71v7eu143T28dUmX6dzI7MRgNr9Ipz+Obd0AGU/Dex2p38JyXrK0/aWGRa09Cs5wFJVAaQ/aFuKfDpJYicgqV6jGZhaoNXH6B14LuONoc8mQZZGxW9UyZEb+IXIKKIjKjEAXmjT19Junx
*/