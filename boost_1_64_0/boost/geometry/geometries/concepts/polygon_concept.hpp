// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/concepts.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/ring_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{

/*!
\brief Checks polygon concept
\ingroup concepts
*/
template <typename PolygonType>
class Polygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::remove_const<PolygonType>::type polygon_type;

    typedef typename traits::ring_const_type<polygon_type>::type ring_const_type;
    typedef typename traits::ring_mutable_type<polygon_type>::type ring_mutable_type;
    typedef typename traits::interior_const_type<polygon_type>::type interior_const_type;
    typedef typename traits::interior_mutable_type<polygon_type>::type interior_mutable_type;

    typedef typename point_type<PolygonType>::type point_type;
    typedef typename ring_type<PolygonType>::type ring_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::Ring<ring_type>) );

    //BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<interior_type>) );

    struct checker
    {
        static inline void apply()
        {
            polygon_type* poly = 0;
            polygon_type const* cpoly = poly;

            ring_mutable_type e = traits::exterior_ring<PolygonType>::get(*poly);
            interior_mutable_type i = traits::interior_rings<PolygonType>::get(*poly);
            ring_const_type ce = traits::exterior_ring<PolygonType>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<PolygonType>::get(*cpoly);

            boost::ignore_unused(poly, cpoly);
            boost::ignore_unused(e, i, ce, ci);
        }
    };

public:

    BOOST_CONCEPT_USAGE(Polygon)
    {
        checker::apply();
    }
#endif
};


/*!
\brief Checks polygon concept (const version)
\ingroup const_concepts
*/
template <typename PolygonType>
class ConstPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename boost::remove_const<PolygonType>::type const_polygon_type;

    typedef typename traits::ring_const_type<const_polygon_type>::type ring_const_type;
    typedef typename traits::interior_const_type<const_polygon_type>::type interior_const_type;

    typedef typename point_type<const_polygon_type>::type point_type;
    typedef typename ring_type<const_polygon_type>::type ring_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstRing<ring_type>) );

    ////BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<interior_type>) );

    struct checker
    {
        static inline void apply()
        {
            const_polygon_type const* cpoly = 0;

            ring_const_type ce = traits::exterior_ring<const_polygon_type>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<const_polygon_type>::get(*cpoly);

            boost::ignore_unused(ce, ci, cpoly);
        }
    };

public:

    BOOST_CONCEPT_USAGE(ConstPolygon)
    {
        checker::apply();
    }
#endif
};

}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP

/* polygon_concept.hpp
cODfnllU+lHrl95r2n/pv3H/pXLtAHh2lu9JyR76Ge/ft4fKOxT5exjmn+vfVyO1+vfTxPFr/bs37o/p3xfx92f6t1kfP9W/rzXNCWu/vR5d1sGLndmX7tH4/MHp/Xb5CJwGP4Sb4VG4Rfci2avm++DH8GXVX1f9I1gLa+FnsLNBmmFX+DWcBb+FeTCe8D6BLvgdbAndIV7zGJgAE2EibAdbwY4wGQ6Cbay9PUKs9dCyDlvSNUm+rbWeRwgHVsK2cAnsApfCbnCk7pWwHH0aPB/OVfMF8Cf67fUF8Ha4Et4PL4K/gZfCI/Ay+CG8HP4ZXgkTzLKA3eDVsCe8BvaDa+FAeB0cCa+H0+ENcCbcAOfBu2Eh3ArL4T2wAu6AP4U74Vr4CNwGH4X3wcfhQ/Ap+BzcA38Dn4OfwufhF/AAPA7fgFEh1AMYDw/BtvB92BN+AG+CH8NH4CfwMfgV/AAeg9/Cv0AXdfQ4bAFDyMc4GAkzYBScDFvCuTAelsDWsBy2hy/CVPgy7ABfhWnwddgZvg+7wU9hJvwa9offwYEwJJT2A5tBU3epTp2R/E6HI9BPhyNhDuwO58AecA08Ba6FGfAG2BduhC/i/w74NNwKn9FvxbOtdbIwQb8VD/OZA7mC+mryShgBr4LN4c9gPLxa6/MspFzDWavhRPqcQbARd054K+wEb4Pd4O1wFLwDngk3w2p4J7wGbtHwM+y1m4Qr4fvv0faI7oXzNIyAz0DZcwLJVn/V6q8ZzEV0nk785cE4mA9TYAHsDItgbzgfjoIL4GxYDMtgiebjdmttoqyTbLiH1GCz/OBQ2B0OgyNgNhwDR8IJcBScB0dDDzwdLoNj4Ao4EdbAKfBimANvhVPhZjgN/gpOh7+GufBxOAs+BWfDZ+BZ0MpXWd8HYgLk62rqj8mrYTRcC3VPIF1HR5hGwz2BrsNdErwRpsNb4HR4u/ZPW+ByeBe8Af4S3gJ3wW3wHvgo3Ab3wnvhQbgdHoH3wW/go/C4+nOb6/xhK/gwbA93wg7wF3A03KXxT7XXiHnfa2Xp2QPxkJ/sCSfrXmB/uBhOg8vgKngBXAMvha/B6+Gb8OfwI3gD/A5ugC7CvBlGw42wN7wN9oWb4TS4BZ4B74JnwidhPnwKeuAeuAA+DdfCX8Lr4TZ4O7wXboH3w8fgo/At+Bh8F14Ja+FqmBpCfw47wWthF2jap8PHYAZ8wt47SdYmabtuuHfSzU5vOd8CU+Av4FC4EQ6HD8OJ8HY4A94L58L74RL4AFym7q6CD0G5P9rreGTtkVy3F39XQflp+YRp+UTAhdAFq2EsvBPGw+0wAT4GE+GzMAm+B1vDozAZ1sJu0GFeC2bAvjATZsIBsCfMggPgMJgCR8K2cAJsDyfDVJgDB8MqeCpcBk+D58N8WAML4GWwEK6GRfBn0AN/BYfBX8MRMDyEfgJGQlO/EI6Gn8Cx8FM4DoaTX+NhFJwE4+BkmAqnwM4wB6bDqbAXzIUj4VnQA8+2y1/Xceg6Eb/y1z30MuHzcCTcD6fAV2AJfBVWwNdh8xAxl/r3JuwM34LEBXvcwYNa/rX67lfbZ4O9W9qH0r5hb72f9IXTYT84C2bCZXAAvBgOgmvgcPg7OBK+DUfDP6n+Z9XDudYs2ByiS3udAifDqXA+zIWL4Qy4Ap4BL4Uz4Vr1vwHOgQ/BIvgunA8/hMU6biyB3eE5ep874tD3eHCD9qvJDvJJ0/24wfgMPg8z4IvwdPgSnAJf1f71t7ASvgb3wdfhAfgmfAO+DQ/BP8D34XFYC9+BX0HiKv3Vn2Bb+L72ox/CbPgxHAs/gTnwU5gLP4Nnwc/hPPgVLIdfw/PgX+C1kOvpnnk=
*/