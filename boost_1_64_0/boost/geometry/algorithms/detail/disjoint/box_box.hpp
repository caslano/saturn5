// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect if boxes are disjoint
    \note Is used from other algorithms, declared separately
        to avoid circular references
 */
template <typename Box1, typename Box2, typename Strategy>
inline bool disjoint_box_box(Box1 const& box1, Box2 const& box2, Strategy const&)
{
    return Strategy::apply(box1, box2);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box1, typename Box2, std::size_t DimensionCount>
struct disjoint<Box1, Box2, DimensionCount, box_tag, box_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const&)
    {
        return Strategy::apply(box1, box2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP

/* box_box.hpp
LRtl7Ab/II17HM1dMouJ/hTsmdV3E/ZDnluhT1kHqDo0mToMmXRtFe7kqwrnY7zeT7XDlVVG+fw9ZNA54lLgifZ55kZ1X+mTfBz973I+25U/ZxGnXXtirybZhKTVnmjRgd73FUe9h6HTgH6A0n01aDf99ovYE9NYPL39ovlBj+Mbw/rYqfNQmbs5Txn6HvUsWoXHWre1dve402k7GuqlL1ocLcvrEDuIwq2p81wM1OLorx0SP7W4zt4ucmabgD8iKi/K9A7FDWzpHfKiZe3tRKwAslocZ65f4+64Uev9FOlG0Xb3dA+d63saC0UsiuxqGc6rpMWfOc/nJp7pDP9f4O+fOYl9KHwhneCDMuQcLR3JregiqA7Wq3hNZqMuldwh/GMY5svs7tFU/fgFZeH3DjAXwV1AqUnZSa7gVQTvSOQuyGcmvQBWQ7Ahuh0//KbE6N4dep5A6XNVegXjMV4HsKczjYHVMp07esPzjJy6L45oI+ANBOcTEea7Fe6LC72pgrP8ewfHM3u3u1cjFLyN9CE74tV955uVXurUfLnfGx/M04mayUJenZtlWF8hT0A9Nz/fwd0dQu48ZDW1ZVaNseMex5gGhrb283Gf7b5j1hBZz9g1d+dmc9Kiqalzszo6x5w0oOWQDC5+93901o/n2HnSjZYaZTn4Um+S4QTDPn+adxaULlsO1Qm0YKClz6bmYkPjtKDk01IuqwZQLt8X7N1Y3Ke8Dz5+96HvSfgVFH24+/NFkD7/wQCH2+9i1pNSUGhtB7icaML8kvceXqTqvvRxsgecP8E+E4nKF9vB2cPkxFgaV5kJ3NWPDg/ujWdH6Y6jyXhe4UhHFDzLj4xTgN1ttGrNZuP7+e4WxESfq+eqM2iHyPabQV/iNrtEzfV2FOcj7qxPGd5fdWdYzFvhtOEpvCcc6Wq1Dz3y/Mgs7JJlulSN858I34GHOcgY7XSl5VE8i3cpApjbXeYtxvnjl7o1adeQW+t0uTsQ7BnLwR5aZag58lAIwufEUO7L/W8vuFSD+h9iNq8It5ubncf4dsNYGuPTVgtE++GNfxcfmtzWhTNwxb6Sm4zjDuDkAuKN73E78U3nVaH15qkxtikaq0ayyUk6UXcqjaUUz2jbT5Ybq/PvLJyGhqTS7zrQNv9ZyfgaksfKeLmS8enTyNgwAxkbjIzeLGV8nZJR3i4KtZ8p3slkYKXeoJthXrbpN6L/nVfKB9PtZkPdbkvo5mQiy9cc7DeMpyMSX32F8tVXotydU5dLvitFHtL30Lwxk/jVodSpSKTMt6gyr0KZl4bGhxzuuNZjbAb3ienzfiOjOFTsYG9yvCaNnn36NxNuoTfp9KGQDvdWwi3xJl0QbyfO+12t2v3Ux63u9E4a6qvtdMEs7fTtEX3pHUreZVP3pVWN0/elVY2mLy2apYzvipDx3UrG06bp76uml7FuFck4G5nWLz5Upvfqdp5GptoZyFTLsVgzHzVjSVTMzR83dtSvMd8tDLLFDj8Hh/W4p+68AMzdo7MLd7by/PF9VN+SRaNvEQ39E7jn379XVfl+btMZjIl8Z4E7A8Y2j79rq4p/Vyj4+opH5L67D7hyOxKTuIf1gy49mKA3nuTelg/xmG3O9X6YYS7e6J9d34353/Xad/+X9N/kVUS+l0+zy0QweWGW2yTVQkh/DVpfOu9wfDQ2QlFDlzVIIKfzIzdiDhT8/Qp1Nvtjat8Q4z6KfUM3FfcXcR7xwZ+gv5+u8n+yRP6bkT+IxZyEvU2G1u3FuwW0Fqf3KJ3Ce5SowI8TnP//FMtE8E9jr9KtQRwKZREvJzf9EIAt824rVY4n5UBHro6O7vMbNZ3oJQonda6GrF+ArF8=
*/