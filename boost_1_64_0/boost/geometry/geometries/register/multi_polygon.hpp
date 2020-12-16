// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POLYGON_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POLYGON_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{multi_polygon}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POLYGON, multi_polygon} The
    multi_polygon may contain template parameters, which must be specified then.
\param MultiPolygon \param_macro_type{multi_polygon}

\qbk{
[heading Example]
[register_multi_polygon]
[register_multi_polygon_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POLYGON(MultiPolygon) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<MultiPolygon> { typedef multi_polygon_tag type; }; \
}}}


/*!
\brief \brief_macro{templated multi_polygon}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POLYGON_TEMPLATED, templated multi_polygon}
    \details_macro_templated{multi_polygon, polygon}
\param MultiPolygon \param_macro_type{multi_polygon (without template parameters)}

\qbk{
[heading Example]
[register_multi_polygon_templated]
[register_multi_polygon_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POLYGON_TEMPLATED(MultiPolygon) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename Polygon> struct tag< MultiPolygon<Polygon> > { typedef multi_polygon_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POLYGON_HPP

/* multi_polygon.hpp
SsTPDHN+aQcJr8eMSy8V+Sddi3HCsMRKYG/XncxO+lkNtc46cctkpJXm9655il2x5WMQZwwYew573Hzpk5kp8TxkdePERcOp4Uo6HxiuVJFbqsybKfEjVs6FuG8cZWkCe/rt/iqicWxkrMvvmweto2rv7AQ9U+Ma6nd0VKw3wVe/16F/BKXtR/TChWIkbhPV/BRKzseIuqb0zD/1d9xEbZuGl2+bzuEuC3OnbZrq3zap+SjMN4n78m2TE8ejEzXsReuxVCkq1BnDPSUPv9Z1Es0n6kGknkU9EX/2+cKDX1vs6Holnmp2BOWLZ9F6Jwy1NQyjJpHO4q6AiCZwCOy0GJJSwmunxTHcNpxk4uotupGDQCJi7Z9xclal2hmGnWL1hwhXionASpgnpiOwDxUp+9yDznMXx+lzr4ixXXrDfM8dh/lav+curslzvTH2zyjxR+0c0OfijzwXCxERMR2A21M2Twsma3ovLorJlSyNDIv1RAc9g0X6eCmjcdZErcP9TR0+ZTV1TXTqsIS3hHBkTy4tE4v/GhsZGe7Bey2vaidvspMXi4sIAOd4lk+bY5OdtMkmbapqflDAtPwVYr5TnxUbsThXMgNj8UPNj6KKfX7EzLKzIlyzwv8cFH1e5BTum03Er5jF+/y/VfC30wQ7P6MXW/nGOv7fZ/iX52FqhzAdi02q5SprbyByIvJd+j7pder3Gzr+c1QJ8puBetq3ijJrfLdW4D2T3c/St0g/mzN71lTnu1L6kZDzOhk3BjnTM8/cRWHa6YCx4eZc34OH0UjUVtIfc7+1p0x/HLCkF3Q97wZxU8/7hzte2wDHn0tCfaev5h3Nu4NlIh/xVHXHWc5estlh6DEbqs74PV3PPmLmOenqqROYZE2aOUG6MOKr+zLuFD/iveutNtYvzKgSzXlJ+blXzGJsO2eqrPON1PORrvV6ZF36jKum6lui7zy3CjUmUf1uJ3anu++y7ik37myvfcT7Ho/s4fC6KjP7iWHlfbTrDtq85/H/S/bMl9CLfY+Kdg9xTXNX4e74DNN3LpCwN/SWnR+lav/cS/x+xP0Aftu7DdJxV4itleIu2fs6b3unWAus393jXGW+yTDvFdaL3b2ep1y3u1Od8bT4u9tdmRt977e+9kszSeJ8l54zNczS919if6wrXfR0D4To7XNvtDyuKPcN2DfrQzmyK8tvr/B6Scc461XSJEg+l1+X0bX82l4dX2m8x3uQSZVb5XlOfnAmDVntvxYzTNw1MPPQaeGeMu8d5lztb/+g+Jtm3uUc0zytTC4PZ79Y6fiHB5G8+X776raIXeJF+9KE0FenYm7DbmzTokqh2uwx4uYmxsRufcdtmfR8yIqV9LTbq5XEKg3/tkufVYkWtk60nGuFfjL6G0Q/jUOB+3LSYrg34FwrDU8h9p7w9at2Lx8TH+utZJtloD8K5euPp8rYgP+dtlLMC1BbxFwGCOGO35fTRqa5fHPjt2jn3ka9g3oX9Z6uZy1LYv0xwfdt4PvI6xN03ctPHUb/ceio4pT/7Lwru528Pjywncwr004Wlmkna6KXac5mD9KuBJqbNkTe7wdZJy4MnKsbPcqz7Hsr+075iO1S6r5vTW0StNvg3RFl22D5LjKfH5yxMKEgl/f8IfaNqtv6Zk70lS1Tbsu0w+Y96TdiHul+jhnCo1a2ts+OP43MXL1KtC1X9hsz28EI3JvUNVLqqBlDdxe5I89C5td+kedaEa4Eq4PFPUtm3u+LEp84XT61IJeh+DTZW+u0W/Hi7g3eb8SatelPo2y9wSHXAB4RNwW0tp0sXQPwj4O+M3aStXTN+V5x10TnRYRZ/Wnu+kXGMsW5jF2n63hnul0=
*/