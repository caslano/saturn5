/*!
@file
Defines `boost::hana::detail::wrong`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_WRONG_HPP
#define BOOST_HANA_DETAIL_WRONG_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-detail
    //! Equivalent to a type-dependent `std::false_type`.
    //!
    //! This is useful for making a static assertion that would otherwise
    //! always fire up dependent on some template parameters.
    //!
    //!
    //! Example
    //! -------
    //! @include example/detail/wrong.cpp
    template <typename ...>
    struct wrong : std::false_type { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_WRONG_HPP

/* wrong.hpp
3gWK/1dvmhAd610hRKfxC8KLISdQWfQjrzOHIW46qbHIN8u3uKT5LDrGSoYWqc+AvjyCGjDZbNInXZcYMyKSrivEP8l5v3r9XbHBUUw2Dvj6+HTp1P0xOmXcT4XCitoai85rlPM3CsEM6cIXbPI9B/9NUacMJv4DnAEnogkLB7pQxg90oYy+cRPDCehmF7Aoixm+UKx3xIrdEC/25/cNLbYUi235f1Pspf2YDjz9zb5Of+If4uvUjm0zgugItC7IbVN+OE36aDluZuDXsun2tNhVWguI9LFED/qIfvPIAiU7K/QzGH+Vrx0yXVGI2Wzh04EoICfCD1PhAey7DIjiGVsmZks4BSDN4ULm7dKbnsunVXDFJS7puiU0E0h1M2SLCxU/WU4hPplPlpJoBuE0iF45WjoLmXimYXZWlp3RM7Z0nWoF5ud5S0zoe5gnRWYY+sdJ+++NtY4RXnHF+QmI60yDqn1aWFziyV/nWZN1ZC1UHdT6looR5bamatAyMrndkbCBRGCajeBUBCdScEAIGsp9fegRI+Jt5Xa3ruN2N5dlBdeCzNMpVEEdLE4VGI39zkhhMZrc/fxhQNpt9uFoxafhmUDp2jiK6/9NxqVx+YkQzl6IvbdE2IOTbx2/yJO/GhD9eA0gai23BRHRRgXRKCAapVa2g4hoYwzRZkBU9i4ot0W9rWErt9vod/YWuKRXl1OL4pAQEvnXGtBr
*/