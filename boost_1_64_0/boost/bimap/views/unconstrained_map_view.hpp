// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_map_view.hpp
/// \brief Unconstrained view of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a side of a bimap.

template< class Tag, class BimapType>
class unconstrained_map_view
{
    public:
    template< class T >
    unconstrained_map_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
    typedef void reference;
    typedef void const_reference;
    typedef void info_type;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP


/* unconstrained_map_view.hpp
8GNfKlXbTobE6U323BrhrLf4C9XFuoi6mKp1sVb8/ooUH6X10aTRuXel6dP8cu5L6zXt0zLbS3gVNQ6dGD/IdePFz7HYfeLnK2uz9p0x6sdy+OmWqX60zueL/QmeGY8w9T5b3G4nXtVWFjtUtk2iv2/GnnNELMk/JCkuAQ0av02KY+hrvptlT0yM7nmpflbh51rbT5PiJH/T6D0vg21qOTJLMYsxv8P8SjlP2lnD2lSxS5sq128FnWO2ao8x2wIzvqOeqFudkZV6EDbu3yb/tE9MF2UT+1vQ1u5tqLqkpuaMufMkbI+2pH7zTXlWi/0uRv5+R1uyQ9L+3fjpadpfldjvpfR80ma4X6ofUhBqM+qvm6nbs8S+lv2a4pz119THJ+V8kdVK60kGtgvE7SLrMFwdddjU+XPk/J/Yk661Zx2eLzLxpl2eLfaV1sVWS886vLR1eB2+UuxLrNGhOqxxO594HS56rYqbk+aUYB3uJ3X4KKqwR/0V+fKUYP0d61p/dSxm6m+XTOqusOH1tjCq3jq/cQ2UdbrWb8oSNy3LiPcXxrfUPXh1b8zHYLz9XkQbj/pI9a+nLqq//mI/xs5jsa/weYwzVL4H9kA9XCL21b6IcYYZH1wg5+/2aX1U/7lR93E7cWPaBvRhpWNPt/Ar9mork9HccdTXdNWncr24n00YfakJA8lL5HH5u7gfhWQHx/fLpWWnzD/VjBV+K9e/UOsuVxM/ab5kdiZsRnEtRuZykVnpSzVhVJXUzigvonZKOHNJx29E5i++sP2IdY7wXSCNvqi2oO39Ojl/ZSh8zuuHvybt60WmwPcEqW/iy/NI40gZqz4hsgt8Xu2otfiJN2PNbLG/qvdpkwek5W25D2ynMBanBdtQ3eVJcfHgFlqR930AP8ztg+2obg0NKaod9ceepO3oKgxtR9rTnEzKBV6K+ZWSe4K5LzREB1m1S/ta4DLWqosYaznHSw+n6764OtdZjGlmf6PdLtS2Kk4tq6k1sx3P+Y76yTF918tiL7WO13v226nybXeps5xeFJmWobUesWd5rrE8L+fPIFSdixo/bTznRx/J+eOs4cyPgntRV5P/5QSY+QvNk0gbbqTNjIO9x6hrMsx+n1yTuozZw4WrsyLz/PSyeRUz6+vL1E83s861XOzXus5dJhr5LmZecJXY/+S6XlBo5DuZdrxM7HdHz1+1fC6T8wvEXmH85+h57ubtpd05+0LjtzHnuFakbPScRst1p4Q9zGv+YuYuszMOfP4SOS8pdJmXTKtnvryzjer+Jd6y5yRM5qCuvSlzs3oqY/TU4H2lRss6KNvJlN3NYv+dz1HWLEvofcvI9zTz49vFfrHPa6210PjpE12+2kevlPMX+LR8Vb6LmXNTnmWEatp3k2zOY3MbQ20Xv0/QlvuYeUN2ju2WENmWzb31Xr2+Pe65h3Id2Jpv/UXv3Szpsnt6jHtSVX468idmSn9dF9lX91KZHm0CfYK/7hn042WlopH0+MQj42P9qYmHxMf4sxJPiY9PSog361XDtF/Pp8wq4VCxu+8nMocLfippKPSlSrlpGk+pmGs5+qypkm8byJkeWt9DeWOnpZh05BHPUtmb/9wLNS2sk4V0mHbDrTFuCzU+s+AV2ufNMm4NW1O2dfCl5Th08GF/sH3AXoWDc15P3dV7TU3kvJ76qWM+j7Xo8nra0OZ2lvzewuQ4+s01OaYNzayYU1JZT3+psvmmv3xX7H+0PNqQyncybWiz2O/2fKb1dzl/s9gLjf+eru2pwpzvYurGa2K/y7XuZMD35fwqK7ruhPrFT0XmEqsD5d/Is37utU88PFjuZR1MuXuM66PKWOet0f1meT3r4/c=
*/