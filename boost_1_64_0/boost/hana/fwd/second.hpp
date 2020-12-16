/*!
@file
Forward declares `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SECOND_HPP
#define BOOST_HANA_FWD_SECOND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the second element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::second` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the second element, where
    //! the type of reference must match that of the pair passed to `second`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //! Example
    //! -------
    //! @include example/second.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto second = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct second_impl : second_impl<P, when<true>> { };

    struct second_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr second_t second{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SECOND_HPP

/* second.hpp
9Q134+sZbRiZ3tHHmGP6sPO2rmo9ziOUbGXfCUSzx0UYYjMiPs+eT0UlZQlxgxnib8M6Ltqbg0l6K9FC5Jh96fjoULVJIkbjuTRrmWKzHINmWoATDWdWPCmKsNI6peHGBMYbtHI+3tDKaw6fdiCbyfnilcvhpxY1VCHIDtkBWbragrqweqduh/M+0QnZd7Si38N9BO5muKlwBXBj4a6BK0Hx+XC5cNlwo+GGwV0GN+jw/8YYcdrxw8L2b1Xc0B4MHTjzG3RZAPq8zRaks7afpul8HC6XoANlndPxEj9IyvqX7Ehm5Hc+jPMx+Y5Aa5ogvRveUpCKjzu18IvSSHMyrmJp+CLy5At6TtS9uewTNLkw/0fj1LWRhHFZGuVdwGZHM82vq7ucv9ylbnD+csMfwGEsn1lgXqfseOv1hrrRi96xIFTdq+z4I8W89aZ6qC6x/PfEwBG4MWRMdaCTLuv2VTtiA2O3W2CzFKMwAA22mc7UtjhXfTLBNKOum33LeeXNaCi2h+0BESzke+rpuuLLAsI8SbvXuObFgGieyR7mmyqbcA1505n0oYm5ne0FCHEBiIZIU49ubPEHxE6sXejMePu4gN15/7rIMofh5hq36qNz1e2lfr94eDwbL7Reps5Ib/C5/GRy4U/8jtWrpaWifCFFe6BvpfIkZOBe189rT/RO5MP1VxqT9yfUu7Oh3h7/xbVQb9f0ZbOCf56u4mg5y9q1P3O7NPpQ7RNSwZ+UWCZMsVT3xTVNE3MfcbuWgrSaerzvOjJxAQwwDM66olvbEwnAQk78bgE3Bj565lTpB3VOX5tM36v6jZL1Cwj3RK25q21rT9AdxU1kDhIQWTJfqnlkY+JsjFtZC85s8S0WdFUbul3Dneh56Iz9aJaOYyYwYprgFxOYUH6xUNQevKSkbY8fdKXtpQuOLSQWZLNhtrHdA/nnwQHKtpUHDQbgHfLAAZD47UQkQnd2CUXaLRA0btQEjXHzJoRsJEHjFk3QuIcEjfGeUqmtKNRgOBo/7Fj50lG8pbXA+CF+2MJz28oX8bXhiSXAXlor3ebspDVAZJxB3Vg9IH6AtuXhRuat9HbY1IoaD9kuOAAvh9Na+Au1TUWZBkOjYfsR9S1128qX0S42VABmMGn/WvkSpdn+qkzjQoj6HL1ZDfFX3WnbV75iAEzxQ30pvpEILv3R3F8Cmvb4Eau6MS39gdxfuF2kcHhj+6tp6U/l/hxS2efT0huIDFHG5bT04RKtKw+sAEWCZdqK/FF4/JANheHIFCeLoQepeQ/k/hqE/fjOeKsrLe/R3N+68WjI/Q1y3Iok9P4rEhoDJkMiQfj5O5pvy2AaOOObL4/1j91iicTt+vWIkTgvmFa2E+05VzXLWfB9tiMEgIJuwS2uICijeClIegrIZ0r6TPCZkz6alCxJn4Uml6QvhSadpM8Kny3ps52+/mupuzd18pN0X3x7VqfxlYfAMvWbLHp3Bhthk8XDJDrik1JN8DrmE1wR87ytYYYRjyJDvdVX21jTPupfSiPmt+r6dEjmVxwYuqLdtehydaNp34oDzhXtdnXjInvkgC07fVxrCT9HtOY3Nlnqd9ZvaTxgajxkGrO98UXTioPKmJ31m+v3mjZtax2zx7QDWb1YgRzG7KU8XlA33mVSd+H7UduzP2JTAUn+hA1LV0VO2JenqbYY5BfFlliRJSjmwei5QnwE/1mqEhS/gBQgiPdMfyBYJtThHJHrrxAPkHiAlsf+QEWZuGs43+8Avzu0gi2/PjoKHwoX55eK/+oqtsbBfKJJOR76CM0T0V7ME+f6k+11JHD69mK1RVB9G+3k4AZqmGmU8sx6WzG3VDtaKrFsVqDejaY=
*/