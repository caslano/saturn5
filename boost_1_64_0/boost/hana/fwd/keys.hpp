/*!
@file
Forward declares `boost::hana::keys`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_KEYS_HPP
#define BOOST_HANA_FWD_KEYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct keys_impl : keys_impl<T, when<true>> { };
    //! @endcond

    struct keys_t {
        template <typename Map>
        constexpr auto operator()(Map&& map) const;
    };

    constexpr keys_t keys{};

    //! Returns a `Sequence` containing the name of the members of
    //! the data structure.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` object, `keys` returns a `Sequence` containing the
    //! name of all the members of the `Struct`, in the same order as they
    //! appear in the `accessors` sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/struct/keys.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto keys = [](auto&& object) {
        return implementation_defined;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_KEYS_HPP

/* keys.hpp
RkELMwW1I55S8KUuJ3EAv8o9J1sI/36KQEAW1i5605oIPyJWmQtYahXgqcniAnJVAalTahz87cwU+CUko4MhIXKJkSlmMsCpT9HAWZbko7gqZ75l7UBPU0m94n3uQqhjDdVIrhQucxLlBCPUjs4fo1uM2vzcXEdRt1IefutFVb2aGo0jNFgRBtdkcXKZcHHVUhV8wGMBzlYUqbS3ZQy8b/mQ65MrcH8Gh535usqXJnJJRNmnv7nTIshfU/Hzgmj62Qzmpk9T4EJINyEZENtY2lSHnZbcudWaVAkjEjr5OEJ8wRDQWr7VfQMRnNIoAOcvc8y+mMWMy6cQNbXFHCIvsvbgWONfCIMCNVF9vdTvBA+HEPKAy8Ixj2LGhWmLJe99SdHnVmvZgDGhZGxGj2itNt77N+KVwJ3XGi/QQNXilUTZIXUc47X305Q/Z/PJ6MT/f3+fH51/V/JdcYEm3uCLjvzTNffUt91T96Tng856d5iEgWxP4CVifJnWMCJs+ttyi5BNjF0MC6ux39HHLi7BDTx1b8z1V2j1XvaH4IY8GOcZXN8pAayuS1RoQXJ5cMegPgcDP8ZeBnUld1FEWR8B1aXqonK4N+X8dDRPtC5Lwz7swX3mWh5SHit+NB3XHq19vWquIYdWLMph+Y88Pv82KCMfptVNGgFXQZhwLPXQqJr+M3AgzKJRp8R6+i/K5yPq4KpKs3hNVs0lf7fY8uczwc5LVtN2onpmJ9jZmuqYYme/iriINtZwy4HYuzwc+2g7RJ03X3SMcR8OPFHU5iqPM/KHXdwNqtmoUJLqn8f3U/i7o2PheSkiz+nYT6+ESL6N48Nag0f0x8hpy3DEf6I/TONWruF6JOEQ7ltjO0aQ5iYUH5UlIlriw34XkPaHPCf6/+Jeyqe6motWxkctBtgrim+KazdBUj34gtibGkUiaOcPbSTfNDwfxMbbWMoXjeC8raPILuTiV9VB7KmxtR1lpGGhQh3NiZ5+RW08GN4l2Dev3STHZDW+GR30GDGNUHGu3dQxZmIvxvxBW9z1YO2DAsUJqoRv8Wsqw2mxdR3lSLoOScts2LW7OG3Ruk2vj6nvRUmFfpgHum8sIxUNWoUWNd5DdR17FxEZ1C9n8XaV1eTYqo4J6Ca56U2SipPW6Y+cVzusrgaK1Zs6Nkm9f6q/cvxAWccnaSyXG3NabJwt+rDSR40WLVbj9qtl3LtYrBTr0KQs1PNY1caVqKkkP2VjJmqUZUWs+HEoux6vfZQIfedcVJvJUHnO/hqlI/pB+Ff9gmpShn1p+UAunYxreharejPNyS3Rs1lrrw6Drk4bRDSaH2aIGSQvs/GW0JKTfBCWWc8ZpOqIt6ap8rHdwhkbLr8E5RuedKKnKXofdpnsZ26YIVbRZYxpvDi/J298VhWZ/Ogig8iBCtwtvwa5evVTDgMlQPVuuOnAETSUR13gQRdMjVBDC+S5oN6GM6/oSf7uRcdzH+xXmTuepyip3Oo2RwbPXKfwzF6lwKheZwYF5dW7lPyq5Yh9dLD8yD2gN61OoppKLTlJtb/GTjwWnwMfphQqVV9IRmSxtY88jsI4PDzA8jPYvRmxCIHlQ8Jy1zDaqq14RjXYSVYPi1ACHysOKVuS7b0m6v16RObtVSOmxd7OWnBukPnyLeZkqVC83DmdJkmARoIgiHQiR/LSvhhG8AtbwswINjlJ0stx/6gkvatJpzsnKO9FjWhLgZJwOvZohF9H8VtRyfp/bNKo+NnozmLuzl8PZd7sS2F53yauOugQbx0f4VOkP2YgGy2zrT+AYP6vA1RIwEkAT0hpCeB0Kd8mo4eIj2MLQcA59zT+heTYFy1ONEQ5yaufsTYtpVQ=
*/