/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <boost/hana/fwd/concept/ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP

/* ring.hpp
h6OtcLSBbZFLsw3u776qoAEx2P7sJtg+B+LfsCMdOVAVzYua9aV7A6yPLlsfw4xmuE4T3LV9fVQT89JXNY131TReV8ldjnafo/3X1fS+r5oSioOZvqvpiD45prmt3zlg2ioqMlXUoQnNntlesefT/qpmnKuacWG7HCS0tY6WvmbSVAxXEZPrbb2+ilmmOOLyVwwn3sOVLKYc1mfFLK6f3zZQ5rk6WDPSbdDK2QffMA99VU6Zq5wyXRFrHe12R/s=
*/