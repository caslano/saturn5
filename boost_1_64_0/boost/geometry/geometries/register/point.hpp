// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP


#include <cstddef>

#ifndef DOXYGEN_NO_SPECIALIZATIONS

// Starting point, specialize basic traits necessary to register a point
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, Dim, CoordinateType, CoordinateSystem) \
    template<> struct tag<Point> { typedef point_tag type; }; \
    template<> struct dimension<Point> : boost::mpl::int_<Dim> {}; \
    template<> struct coordinate_type<Point> { typedef CoordinateType type; }; \
    template<> struct coordinate_system<Point> { typedef CoordinateSystem type; };

// Specialize access class per dimension
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, Dim, CoordinateType, Get, Set) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) { return p. Get; } \
        static inline void set(Point& p, CoordinateType const& value) { p. Set = value; } \
    };

// Const version
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, Dim, CoordinateType, Get) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) { return p. Get; } \
    };


// Getter/setter version
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, Dim, CoordinateType, Get, Set) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) \
        { return  p. Get (); } \
        static inline void set(Point& p, CoordinateType const& value) \
        { p. Set ( value ); } \
    };

#endif // DOXYGEN_NO_SPECIALIZATIONS


/*!
\brief \brief_macro{2D point type}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D, two-dimensional point type}
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}

\qbk{[include reference/geometries/register/point.qbk]}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D(Point, CoordinateType, CoordinateSystem, Field0, Field1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 0, CoordinateType, Field0, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 1, CoordinateType, Field1, Field1) \
}}}

/*!
\brief \brief_macro{3D point type}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D, three-dimensional point type}
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
\param Field2 \param_macro_member{\macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D(Point, CoordinateType, CoordinateSystem, Field0, Field1, Field2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 0, CoordinateType, Field0, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 1, CoordinateType, Field1, Field1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 2, CoordinateType, Field2, Field2) \
}}}

/*!
\brief \brief_macro{2D point type} \brief_macro_const
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D_CONST, two-dimensional point type}. \details_macro_const
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D_CONST(Point, CoordinateType, CoordinateSystem, Field0, Field1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 0, CoordinateType, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 1, CoordinateType, Field1) \
}}}

/*!
\brief \brief_macro{3D point type} \brief_macro_const
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D_CONST, three-dimensional point type}. \details_macro_const
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
\param Field2 \param_macro_member{\macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D_CONST(Point, CoordinateType, CoordinateSystem, Field0, Field1, Field2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 0, CoordinateType, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 1, CoordinateType, Field1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 2, CoordinateType, Field2) \
}}}

/*!
\brief \brief_macro{2D point type} \brief_macro_getset
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET, two-dimensional point type}. \details_macro_getset
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Get0 \param_macro_getset{get, \macro_x}
\param Get1 \param_macro_getset{get, \macro_y}
\param Set0 \param_macro_getset{set, \macro_x}
\param Set1 \param_macro_getset{set, \macro_y}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(Point, CoordinateType, CoordinateSystem, Get0, Get1, Set0, Set1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 0, CoordinateType, Get0, Set0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 1, CoordinateType, Get1, Set1) \
}}}

/*!
\brief \brief_macro{3D point type} \brief_macro_getset
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET, three-dimensional point type}. \details_macro_getset
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Get0 \param_macro_getset{get, \macro_x}
\param Get1 \param_macro_getset{get, \macro_y}
\param Get2 \param_macro_getset{get, \macro_z}
\param Set0 \param_macro_getset{set, \macro_x}
\param Set1 \param_macro_getset{set, \macro_y}
\param Set2 \param_macro_getset{set, \macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(Point, CoordinateType, CoordinateSystem, Get0, Get1, Get2, Set0, Set1, Set2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 0, CoordinateType, Get0, Set0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 1, CoordinateType, Get1, Set1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 2, CoordinateType, Get2, Set2) \
}}}

#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP

/* point.hpp
i9LMHH0a+mtRUo8WLjaTdKmDar4bVSxuY66Uga//eEr9b0VMlqVgx171asZQc4pv8OfW8dQB/IicoeMp78hYD2NXhoYu8UPNMzFfLn7EzIppQJOQzNAxLdYdrs/zX/OaQeZNxO4w3Wft7J3ZilpB3f0gBfk/XDOw6yPpbepjInJEtOd/WkM4giP772WP793KJihnCkWXrS9k6hzeqlxg/VXri7ptbNaiY2JsebmnbH1J1/oSJuZdPU2t/q4HKF3brHmW1hn1q56pMzMqyTqB+R7Xpe+Tnbl8kvh1qyfY+sAMzOPEfSWVKYUiNwtY56yt5b1FrG32jdWBVulTeu94dtX3Za13uRWpa2DqXvcC6Pqv6V+bx9lm4WY/WqSEbZgn1h3GeCNc2xO++BQ/evutA9hpHLgOEC9uV3nK1s2LNawzJaw/knr18CmMEGeyC4E3kFaWa4yV4/qHlWT2pCZLuMI0Ds7zW6m5CU/ZdWUzNu0m7r+hRXzab5zAaYUTSvcKJMA1Yi/e7DF5UuQnKGeFuj6pcXXWM3TMt1vi2tqsC2yTuGWQjoFudCHEfJN7Be50nyAyq5Ui72HseJtrtSuGcQZ9O6l2ajZ7CAlgbGTjgG/iZZ6odkbl6ZrhBN/U1G6VUvQulrO4z8wrnZfmxcZUFbdqNgyzHerWngY3kGVDn//+z/BepXPRhd/7zUXjQs5FX5H4fOsaxxi4puiRKqK3xFOLdvtxTMZbbVxJlBKZPxOOo6Xh9Cw8o/PROJ2Pqh3XVc58dOH3Zeej9TWsC6/S9FhYrHP1HEkUTyqtMfZrYy8SO8NQTrosfImHeSNjPelI2mY79hagdjj+kUjSsMdk0agmmnGWk1/rsPubnV8xRU3Kzk3T1U4Jdh5OxE7Yoi7EgHNIy39DavIfu7/KPHbxfcHnp/qdVTJpjsAZO8iqp3wOs4/QT7VVku9dxk6Uf3s+vILzU9qQ0vmp6lEHA9t19GZU+l/mrNKmlJuzTsSi/fe8nkW4HcoacuVQ7b+EMuh7tx3i5hGrK/8+iqpH+ZyMWo3SvkH9rRL0npB+xnwuLWons9d/fLyMp8qu+Wq7ghsxz2Y19mLT1qQn2HodkOsS1zF8Pxy4dnCkzFi4GKXmhu8lV3SP0J/3ufY7pQcIp75jCsiDI/N9nq3SdfxrdB2/JCFUHsgOwqB9L24C1u/PijwjLMSagdpvYfYBuRNteYTYX+nfv2qflpRim8dccH9hK/GjxNvA9aDXmSPGVrH1LvIb6+bjiLG33zp2NXHnNu15DZGr+H+rbsra+mQJhzuSXB+KWoR6ExVmnTNjhZ2p8kz/vt08q6bE42KVeUoVncPqPsBI3QfojCvqi18LVeZtrNjvJ/P42TqPHy/hrWuli55Pc1GSrfeRZ527mqvQk1hubN1G++/fJB+6hW0kRi+zYz3eU93V2dPRtcLT3/W9J8mV5M1w9fLOdr3gvchVJSzMlSrunDiuJpbtOP++PvpmDCFHHLDENCff71uNUxLGXYQE2aTR48yV2pbuB5C4z/FNjZDSNYwbJc3OuRqTzoNRS1CJYqbpQYkOkzA4+YUnl+tZC35laI6kCeeJ6rpDU5GzvItptLd42krflVNAvbjGNyfg5jGWkumAqzG51vH6Asx2omReMECnBdrHOuaHUcWOe9/UIMLM3/UZWYV6tnSl6zxpPCMqxdfHH8VtcqEz79goFzOJOzVrVah3rl6HI09MbAp9ajm/5xFGcf+cHGoe2Tnomebm/X+x5E0Xbx/XTk+kt47qO3lEm8h/rMAFO+Nc1pL2ifsmXpFNGR18wTPON4qbBjyr9Izz+0RvvDfTVdeb6nfO+QkJR5bs1vQ761w=
*/