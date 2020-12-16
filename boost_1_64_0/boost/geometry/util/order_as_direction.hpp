// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP
#define BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/views/reversible_view.hpp>

namespace boost { namespace geometry
{


template<order_selector Order>
struct order_as_direction
{};


template<>
struct order_as_direction<clockwise>
{
    static const iterate_direction value = iterate_forward;
};


template<>
struct order_as_direction<counterclockwise>
{
    static const iterate_direction value = iterate_reverse;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

/* order_as_direction.hpp
sJs+VsM53zuKPlaFnFc9iPOqh/Ibc1X0tTqCvlXH0bfqRH5T7nLgjsCr6WN2DXAX5zwu9cxI0L59qed+1LOE5fINXucAYZbbwPx2nUV70r75wAz6qFXQR206sIh67w2sc8QIWtrd5YyVG1t377cyXdap27z+ftanidfgl4Iftw7fYg2+WGRBD4m3OxS/fSub1+Sj+D9+Tb53D1fCdfk88JPF4r0J9SRak1+40oovtBI4AeXXFmco84v0JN/iAvaw1uKDwHqkuUgLkVYhZfbEGjtSTU89565J099BHZAy+P4/aeK+RRMLR43MkY31oBy8s3ey7s2krnhnf8Qb/85eWFA0yTD9atOt9VPmPiMd63JyNd7ffvScaD8f7sEHT3k+TJn8IZS/mrmvsOWXcHHWX2x9ITzFcnOMdGUOIWjL3W8W9qJUlQSq/CUhtNgv/6VY9mi7zZTdEJPtjyY1e4p1GEQdgvQnKHXoUIiZi4nYzN5efb2MMk+yZe4bDR4QwIusN7h/tbwNp1iu3delvGUd65BbiFmh2po9OD8yUaZHUirbbvOblF3nkD3eWxNFbIDx1iRIattsn9dT+N5/ky13n1p/eFaxP2w6UVSXQ3ptdTuML1v+m5R/rS2/IMITOhTew++V9heb81kpbr9t92K+6y9ulj+BE2ntItcea4vt2A0xubGplf0KA5FoPqYp2svmhZxbeNiWvac/2nxZ2y1iX9ZSLd++pjRSfkVC+amVaffzGDqgvOKUac2OFWBy7MBUt9WWO49y33TInWzu3s03r+MHpliubeOBnTl/FJPb/tftKyjzXodMO3yE6dJW4EupXPtcytzQMOmOlnJ5LSlI+blkt7mBsi9KKju1cu1zuDv31zfacicEIrK32DJ0YaAs7A3PGo+AJZSvSZMmTZr++7S29/8hRoZyv+mKVHVogntNiurQpEmTJk2aNGnSpEmTJk2aNLUPdUDqy3f3A8bvu39RScHkiSPycifIC/yfmHPO4pxzDXN/bs85R6Lh8sqwzC+3i7wm5l5my6vyV8HrNuXyBlBeCdfbf3DIqwrN8IOVcpl2GxdS5vsOmeU1s9pNXh7X1lc55VXVtJu8uZS3xiGvPcaM7TMxlOvonV2UB0/pqM+MlGvFSPb5MWpDszzYHRBth36116Ruox7pzXqM90Rq/OWBikC5h/sPDL02o0mTJk2aNGnSpEmTpvWjtb7/J1q/N3ftJ3ifSWE9mjRp0qRJkyZNmjRp0qRJk6bUktP/X+L2S8w3359czxwQt/Z/ir2eaQdHt/Zrplyevfbf29Xsa1AtC9VGauVl2XtiuQ4/1CEP4tpF1oOU5bZlHYHNztH2addArr/vYsvylqVclt1nsymrb2zNG3EJESAxmuI+s+V1cDF3TF4U+4dH56V6jNjyopQ3JiZPBmUAw6R95C2jvJFOeSIuxe2z97JO5V784mZ5/krGk/Og6lTb1d7L+i7lVsbkhv3TAhGRGvdh0NTKHxQXA2AvW74Z5xDi8W3XVLfZ7ttGypzQQmZq5dk2Hkc3kzJbXrJvUae4vbZfzkLKn5pIPuLThhHh0l89IxAOVVdh73RKdcixbcC9+NUxHfx1/vLaqGKAFN/Psmx/IMoe1Cw7HK4OpVSWPZ7d3IcfjclCxR7rE7mpHs/2teMSyjxSken8xHD79Glv7r8/oFluqLoiMK02HBtW+Mb1jJTKZp+aQehMbJYt7dQ+XZo0adKk6W+hxO//ydfsByRas09RHZo0adKkSZMmTZo0adKkSZOm9qEOSD357j7EXRionu4Pu4es+zz3Xmk79zDKZ/qMCWOnhmr81ZFQbbjcb/0bCQ4rqw0EfcNG5IzIya0=
*/