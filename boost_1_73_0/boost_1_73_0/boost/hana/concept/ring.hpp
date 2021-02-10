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
lO29pRW/v4OU7wGjh36OfmxIqQTtTnM0sM3v2di/ufFWmlRy2eu+aQ9HDm6onTN2fJTIC53+RXvQ649gnLX39VxG9weA489wr5sslrW/vW+weLGss9NTdpBT6Y8tbbjvFauCfW3rBriUO79x/KkzvncCd+HV+K6FXzkTod/Qxe8m6H/CWvsnSFxfT2QZqtOGrfsU2dLkdlXDBw32/cvvCecorTkxQy4kS/7KgC3WavxNvSYf71KBeiONrV12WGcvxXiwJvQz94JafmnqN14Fk+V9DcbQYBwkzu9wUAGO4wB/Gfgngefq7Kie9+aH3DfPc96A+JT/5jCvuWYr581g2ATR9E035/XZcChf7++QAhkpK1O4JOMefHdjshwL5RW3kamP79w50K4fsDs/mKDCu3fLbRVKROz2qHVr1+Id9CzEwzzw37Y/vM8Dvz3E+lqPx/DIOTw8shaXL4v7POat5vSXB8qglUcFg1YeFQzbzcsU/GcXzvDc3je+KYYcirTh2VWqzeYbUFDOAI0O2aktFY0SSR96IxfXby4Ae0C41haS18UgDt92+v8N4n8KxFH7rbU4PC9ur/XhstN961xROWuHqPXD0hGQaX3Sm6vmcNQe5Nfk7+0oUTIaL+RcNIcX9pYsBUubbCHhlzVH
*/