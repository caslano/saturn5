/*!
@file
Forward declares `boost::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FILL_HPP
#define BOOST_HANA_FWD_FILL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure with a fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor, the signature is
    //! \f$
    //!     \mathtt{fill} : F(T) \times U \to F(U)
    //! \f$
    //!
    //! @param xs
    //! The structure to fill with a `value`.
    //!
    //! @param value
    //! A value by which every element `x` of the structure is replaced,
    //! unconditionally.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fill.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fill = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct fill_impl : fill_impl<Xs, when<true>> { };

    struct fill_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr fill_t fill{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FILL_HPP

/* fill.hpp
sNWfBp8w+9hgWagVCWvclGNhLMd6yrEyU0blZ6rCzQC28p8WRlCPUPvrsCa/ogz2wv66ha1evIxXCI00dmWhI+jL1DVU/bJ0GdUva1fvCfHl6HoLX4+a1AZ2/R4usHuASS6ClW9xJ/BcsuGCFpHVHBTaaqmmJoba94Xh3/VDpFh3dBx0zKdC+huNJl+K8KhZy7SVo4wPDN845lGL6lnVtZoKTtHi3HBywSzeXlrUTkVDbcDMjn7KL+26uJ/ySylCLO8MROHeejjUN9Z+Wxj+6LGcr3GPWfHaOGYrdeyjqZQCSas42fPHkfO0JYGcjQ3Gqq0WLUIVxeAIv0AEJDWdnPReEWI5OeQWEWLWMuJgDrn+ONXyudbpB0N9tfbbLjRxLdeJWlbgFeoy+kfSv5RQl8mfxu3tdtDLKnuOdafZf00+d5M4sgwpxFoiRfnS59FkxbRl/Inn6wQ7za48IrxsR7PpeM0TiiXOduV2W8RHWRgvKm6sXmaGTBL+VO2i/d2jyGElB5Vutz/Cpasyxnnrjt4YOIcMX221EtjjyrACpequJVEascBWBwU8ls5o2ZNU4/hIJIjHKHcBQioYuFBwBYpUHgU2dNjucPUR0oKmHbYPtzjRStG8GRj3rhwkV9vjM7q7H6Nv+viZ5mlyd3+XPfHxtehEVF10U2xZ/0AY0On6DWYPNQRREA71/i0HVw19jMAU7iCY5GyqVinb3Wk6xkbERfLS4WwZrOvLJ0RNkJxz2WV1i5HBfRek6KpHOMLo+JghzznWSMAIRNrucfTBxGX4wn1O6H0LfwVAymVKe3faPO6mqo1jivbz7CraHQfs8jqJmIFfVwbMpm7u+Sps8t0FW3x4pt1tcnwGz6/xXHePyfE4/HbheRjP9/Hsx/MyHkNKijFF/Ewp5pQUC/hMV9yDMKTrwXMpvr14DJaBf2zyjz7MjZvvBHT62b0mRyee31M+eH+eysd7OZ7n8CxAnG74leJ9HO578L4Xj2HYB/+Mw0zJXubYpyUlNc06LIU+h6QPHTbMNix9WEb63v///m1/WOCCgdFov6QDKxyOpgy7N6P90TMdwvlKAkeA72NBSD5UYiAB3sBIoq9IF2pIkfQQ/ilL1ws0CHgyWSiWU0sqDU0jpHF6rDcpVrWIRRaYvigulU+Ghl2ick2JHo02N6UJGyGRFCJT0H1sOyCBW5qg5eJW5v9UI8m1+/eD2NY0DtVCdSbqBeWgGcprIe1+YhHIb68ftRuIwGbmxX2OVKrnV6OM/pammysUTpPPKqkzLB8uD90IzJ6BkH2DJT2a+vEQ+qRfm99A+O8P4+UblgEmrSnajaHZ4tzANNU/0iYBlJioB4TJ4HM9PoXmp2K42HR5O123wZMJ4gHjyxzfPnMXxvYPoEdYw8Blm9IBsHIvpraPRUK6WQS1aOyZT56OByyP5tJw7LRXbg/DF7Re0qeM2mSs5EnhyJLwDh0xBRY22se//I2eJyo+l4qsC7oXIjClGoEoMMIFFRgpz0r0nhV+Ly4/F4aFflOjpGboGRIS8soCJyXB/5sf0RM5wnRD592W/ULVclEPFWbPi1B5qwsQ/bkm6Kc6bL+6Yw4c+1b8jVpHs7jJfthe3+GiT+Epv0uVLYJFKyPvgocI5gNTHA2MOL/CiRP2qnziQwGdWQZs3fBjmgT+yBzeoguIKWWz5x3AatjiJPoh9WaTw+4dRWsk3nfUBnis+AXqqGy5kffOUdRT8i7qM2pq2xCm/tAw2fOeBBEoTCtkJ9mKt4/BgOKH9uwhznYv0oy9igsoeLbRvnT7e/Y/tx+2L6Cx3HuzcTqnGsrtf0mLv4krIncgegdF71DGHLZfZdlxH7KhpIg=
*/