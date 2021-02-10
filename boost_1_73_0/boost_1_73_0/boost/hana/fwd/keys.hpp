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
RHD11YlYKVpupMLinDDl/Koqe44MN9nL2S1Azb9eoDUMLqMccxyt67Y3X2yq5kLp1ufhmqsW8VOQSinUq8nlV6abem4OZeEyR98xbNFw9RW8/tf9e3x+NRq5EvKJO/sOw55OvkN1NWErS+ESFefabzPxrqy6lVTX0I2MOhaXrWSczGfTMwaVTLIbO2yRcj/ttZ7mNsLiDlkVruDeU2Pr6QA32t6gEfOSZDHl7bRy0xeE4BNcUgqI0s5cdEBu+TiibActQ/F9cXp8JPY6T1rMLYyziB+EF+JkcQlvmDhu4YUzAF1xbrVEAnifZvnz9Dw5ytDID/pjTpgWJU8mJX6Q4SCtfUMT8amtwjXsD4SVGeym3tmoBLBYxNpKVHzMaQjaPLSRS8RcL3zcsAco4tJHY1tnfrzNbW1zrkVUS6fOcZtQsm0snGQEEUZTbXhinPBOHjGLtBaAPFJ20dw8k7XrzrKbmCz+GMyYBGDlPZTvw/Ayngfp1XRpi0zcYqV12tbUV1B+sFezF2ifa3QJG1Rei3R6+GpQRsgcjS2e5J4RdzTe8Uym0mVGo0671c3zSGQ7jLMsVSbD6jEj9cjWjmIxxi9XDGwhClp8UbXvEx/cTHRs0yxnmEz1NGk/rmHFyxmlSaPkva7lPL/pTI3j
*/