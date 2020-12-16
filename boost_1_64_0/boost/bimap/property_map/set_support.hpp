// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file property_map/set_support.hpp
/// \brief Support for the property map concept.

#ifndef BOOST_BIMAP_PROPERTY_MAP_SET_SUPPORT_HPP
#define BOOST_BIMAP_PROPERTY_MAP_SET_SUPPORT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/property_map/property_map.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/support/data_type_by.hpp>
#include <boost/bimap/support/key_type_by.hpp>

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {

template< class Tag, class Bimap >
struct property_traits< ::boost::bimaps::views::map_view<Tag,Bimap> >
{
    typedef BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::support::data_type_by<Tag,Bimap>::type value_type;
    typedef BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::support:: key_type_by<Tag,Bimap>::type   key_type;

    typedef readable_property_map_tag category;
};


template< class Tag, class Bimap >
const BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::data_type_by<Tag,Bimap>::type &
    get(const ::boost::bimaps::views::map_view<Tag,Bimap> & m,
        const BOOST_DEDUCED_TYPENAME
            ::boost::bimaps::support::key_type_by<Tag,Bimap>::type & key)
{
    return m.at(key);
}

} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_PROPERTY_MAP_SET_SUPPORT_HPP

/* set_support.hpp
lPSpHz3fbTz660V/MXMdjSOlWddqqD9iUIq7dMq6KJ6yJl7JpD2uMLF5cqOUkHqdrvX6cvFX5ozB3xQnUco/S/1PxX86/pOTmyc1T+qI1MrkU0KeZR2f+bqEMZ2+e2Pxb+rTcch0OdY8H6p53qmxhMEeYdzDr8OpuE+ZGJbndQs014/wLKm/DkeqV+qmOGS9jC0jq5fYt9DxTqSxTpL1K9b7r8yMVT4zMXRtw0rVp6lM51PE701uHDUqXfP5XHHzU6c/7paivHBrne4a7hXiZiW2jZ0UZtbOgeOdBMq2iTMXLkKfrvfcIG7zxG0W9sHxthGTZW2XFf4s8x48Vfxc47ucsIJpuU/MEiz3yPTTdRT7JR2X2Gtv8m0Z/ZfLvRoZ95eJ3hcIK1HGF70zouQ+k336/j1inUqJUKcywuuUtJVLO4pQD+5aM6didm0NEQx9vrWuTQuAp5GSx8/0i0LqmtU4R61n6mfaUc9LidSG2PW/UIdQNGpOI9RvM1nHEIiT/0SnsoVLSkPacJwcte3KJT9qYc5jDvWidE5FWXloIMc4BvqejIFe02nnzcsu6DKt94iKQ3/etGvx/+4YqCWfRt65GVDWNejvYQ7U3x1UPs0kR7+b9NsFO1uegOzPlQoBU3SMNFP1HXWMtJuOkZ6qY6c9VB8Mf8sRwp+r4c/X8GthG9V3hIthZ7gEdoF1Gj563c+s3xewh4Zv72dervvgVsB0uBJmqb6L6nW/JG22HU7ofskcDaeDhtNVw8nVfaqdYCfYWcPtquHWo6o03OUabjKqUsPtg7vmMA9mq76d6gthPpwI+8NSOADOgAPhJbAfrFR9NewL61Sv++K1zZB2ivuH7osfpOkp0n2258IqOBZeBUvgbfB8+CgcB1+A4+GbcAL8BF4A23OTibATHAnz4EWwH5wCh8Op8Dx4se6bnQYnwVI4C86Ac+El8FVYCQcT72p4JqyDi+Bi+HVYr+mk/db3GmFqPsehOmk6T9N6NhheDIdo/clB7VV/jdWfi2qp/lrh7g74HOPFe1GH1zc56ePVKd/gnqgJqCrUWtQW1C7U4W/ExrH/G6+T0P+vrpIl+P96/9/fZ0+zzv8v0L7uXajOqJWoOl7WGycE2n1uXmqfIV2VKPKL62Z73yDqtrvM2e408vZ1Db/3babuupo1mc9P8Nax18i3DXer8vYIvCr2s/R7OOg/P+p8v96Xi6yy7vuG+EsMnIuu/YgDqA+z/rl5XvIAPXlgzfPWBtcZqtleSJowkzSFz/0e43rA1iv95q22P9HuvaHf/fkZ7esyK34+ute/f53gkdYDFpmypN7oe9aWy9Nc52ZbqNyf1nAKzIL1uj5wJWync7YFtzRxRt/S5LjWr029JfaujF2xK3bFrtgVu2JX7IpdsSt2nfzrZPT/Zywo84+Wn5D9/02t/f9zdM6+WOcaR+pcd+EEMxfhv/fC+dw9dB6iurzWOodsnLgvcPK8s9I1jDTT7z4nLTCW3ew4zqEPzFfIvbxzDVDnSr/4o59n52wb0HnrzwZ80uOVVb/KCo6D6701XY49Tq1rZdNgCuwE02Ce9lcLYEt4ho4XDoepcKTqU6D2SaUfWh/rh8au2BW7Ylfsil2xK3bFrtgVu2LX/811Evr/i+rKSmfNq5l/Qvr/jaz+/+E4XRumZyB0hrP9a93Hmf7/oroZcvO6+djb8v+q6mq1r6/udW7/QvSvib61m2bLqPN7sPaC6z10zTErR8f79U+zh7Z/VDmAreHL4i/T1f3gGk47PY9Y78UpoHULAvGrMG7yrPGLmvLyMu/8671iX+JYsvvUj2uvL9A1p8v8WiPbyyfxrpB1r71ZnZQm5iY9mIw=
*/