// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TAGS_HPP
#define BOOST_GEOMETRY_STRATEGIES_TAGS_HPP


namespace boost { namespace geometry
{

namespace strategy
{
    /*!
        \brief Indicate compiler/library user that strategy is not implemented.
        \details Strategies are defined for point types or for point type
        combinations. If there is no implementation for that specific point type, or point type
        combination, the calculation cannot be done. To indicate this, this not_implemented
        class is used as a typedef stub.

    */
    struct not_implemented {};
}


struct strategy_tag_distance_point_point {};
struct strategy_tag_distance_point_segment {};
struct strategy_tag_distance_point_box {};
struct strategy_tag_distance_box_box {};
struct strategy_tag_distance_segment_box {};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TAGS_HPP

/* tags.hpp
Mq3djkmk77it3JrJyPIfx+avtPVy3Bs3v1KrWcmKmd3zN1w3Qv4R0moGt4BMXsbW29qNlFZvoqTfQEm/eZL9xkki626cWLfhpnUsM/YpY2sq088rGRtV1n0q9f1e5p2a1u7StHqHJvvdmdbvzGzgrky2OzKt3o35hTsxrd6Faf0OTNpZcErZ2BodNc5h5lrappqi5qsBkvkdipSvUGR+g8J8o6FnZhU/NV1mrdora9Ve68lsVbNVTBfplcp7jU370sPYXuVpevNr82vza/Nr82vza/Nr82vza/Nr8+t/6rXCPkfbszp/nNEBq7tbvYXVxVbny7/3GjrTlI9ZHu5z8pVsN3ZRMo6giyfi8oP8Cxrx088+8bswfrUMP6XWT2A9P4EsftpvwE/c+tk3xU9RK34KrJ9a8ZHmp9b66UWVgF+/dT+FG/Azx/rZT/1sQjwN1k9v6yeUYzxLrJ/9U8an9hfiEb9gup/l1k9hcnxa91O4AT8t1s9B6mcT4sm/2Pjp48Ynx3gi1s/B663DsLrx/aiPX16HUevnkNR1mOHnl+e9yPo5NHW+Mvz88vjErJ+i1PWc4eeX10/c+hmjfjahX3XWz6kunqz9+uX5arB+xqmfTRifJuunyq2fHMdnhfUz3vnJsV9yifEzLznvxklRK/0KhbLHU2D93JDqJ9K6n7y87PFErZ8btV+bEE/M+rlJ/WxCPHHr55bk+mk9nsINxFNn/dya6ifSmp/W42mwfm53855jPE3Wzx3OT47xtLj105gy70XZ/XTfQDwyy66fVD+1G/KTPZ6w9XMjfgKbEE936+cm9bMJ8RRZP/XJfvm5Gx1PzPq5Oc1PYKPjKbV+btF+bUI8U62fW9XPJsRTZ/3Mx0++zl+O87XA+rnN+clxvhqtn9vxI17u8Sy3fu7w/eQeT4v1s8D1K8f5yr/U+LnT+clxviLWz11+v3KPp9D6Wej7yT2emPWzCD9aJD/H+YpbP3c7PznOV531c4/zk+P4NFg/9zo/OY5Pk/XTxvlJeb/jbcT7nRbfD/kpfoqcn414fxG+zPjZKsVPrfOzEdfhUesnbP14Ofar2Prp4Pzk2K9K66ej85Njv2ZaP52sn1CO/aq3fgqcn9R+bcT7uMXWTxfnJ7VfG/F+p8n62W299RPeyOu6Fuun23rrJ7KR13Xhy42f3dXPv/H+orV4otZPd+cnx3hi1s9erl85XvdOtX56OD85XvfWWz/7qp9NuA5fYv1E1c8mXIe3uH6JPX/leN9G6oyfvbWWl7ufAutnH6oUbcJ9pKj1M8v1K8f7NsXWz6XOT473N0qtnzp/fHKPp9b6ucL3k3s89dbPbB3nTbiv1Wj9XK1+NuH+T7P1s8CNc47HhVxhr8ecnxyPi4j1c5c/zrnHU2T9LPT95B5PqfWzSMd5E/aNWuvnbvWzCftGvfVzT9rxBW/k+b3R+rl3veMrkubnl+Nptn4a0vYxeCPP76utnz+s5yeSzY8fT3Y/4SuNnz/68577+EStn/t8P7mPT8z6ud/3k/v4VFo/f/L95D4+tdbPn906zHF86q2fB5yfHMen0fpZ7PzkOD7LrZ8HnZ8cx6fF+tmf87t//zHH6+fwVcbPAc5PjtfPUevnQPWzCcf7COunUP1swvFea/0c5PzkeD0/x/rpo342Yd9YbP0crH42Yd9Ybv3shJ+IP8atn5fzNzDOLdbPztaPl6Of8Gzj51e+nw1/jtZ9Q/uY9RNJ6Vdtq/G0vg6LrZ9dXL9y9FNp/eya7Ffrfrpv6H2l9XPX0tT7dflZz6f5G7ifsMD3A+MntAl+mqyfO62f/Bz9rLZ+Fi6158Ec/RRcba9b8FO7CX6KrJ+78SM=
*/