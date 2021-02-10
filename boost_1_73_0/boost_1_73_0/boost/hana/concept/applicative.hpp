/*!
@file
Defines `boost::hana::Applicative`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_APPLICATIVE_HPP
#define BOOST_HANA_CONCEPT_APPLICATIVE_HPP

#include <boost/hana/fwd/concept/applicative.hpp>

#include <boost/hana/ap.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A>
    struct Applicative
        : hana::integral_constant<bool,
            !is_default<ap_impl<typename tag_of<A>::type>>::value &&
            !is_default<lift_impl<typename tag_of<A>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
NlWwookdFW0voFQ7byMp62R1EFCMIuA0NrcCQ6bDRwUoBTCdMbLw+F4nqMRcTzadGXvEBfVLrfcSnwDLJ72oc0rfhLLYyl0o3IOv2G4lUegUq2OlwwuWkQu8h63Dc9orLSIN1YPShTHkaGLNjJUovyosI13a8Sid9a9rYfBGvh2pAyPP9loHbbJxu4CDaBuPddms240zUGK33K2zDQnSJN+5+tTSElXPu/bst2maJTWhaF3b2fHLF9DAK2uFj3bzHaybRIJVbvJuzbnJe/Zub+cv39aLeSm77sDLDJbxblEi4elw3CDlZTT2I5RLfoSPpnjQXRzoFjRm+0I2sdmUm1ycyIvbnI3gENFj3kU04x8P2q/Pf47Whr3u9M7bBgXF1kDXMmqVfM/xFPiJIHFzNe0u8B76okQelqlIEVxsCMCCdRwkfTioooDU6LsGPeXhCiiOK3YxRpAtU5AmgMkZlHuTjDoDyunEJS31VG5mNYAefDJJ77m0ZkcdrhZkXHNRa3Rxna9rw9Hu1xlUxmTjY82fetncjyuTXcyPxJJxfPJzRa7RUAh4azSNJ0C+rLbI/bE46BLpd9h6cxwxDqIEPR3F/U73fte+xSG2z+B8gzkWh7NsanrcGfHtTGBVwjGNjbf7US4WSwjsjEmZ
*/