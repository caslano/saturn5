// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_VARIANT_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_VARIANT_GEOMETRY_HPP


#include <boost/mpl/front.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry {


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct point_type<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
    : point_type<
        typename boost::mpl::front<
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types
        >::type
    >
{};


} // namespace geometry
} // namespace boost


#endif // BOOST_GEOMETRY_GEOMETRIES_VARIANT_GEOMETRY_HPP

/* variant.hpp
ijvNwlYinCVinuHVQX3VGkt3WgZquFsgsdIqKvQkAlByzPnhLPaq0BrS+Wef50iiljdU6vywVDIPulfonITxlPKYDTRKdOaqs2IsF5YR81uL7OBeeBmg3GJ/FCE/tpbmGmykKYAPB09mB1N76/E+lerX6DbdcTYtvmkuE5FmCd7hwd5LbKUZCoRfIVfFg2s7/6hqliogQXRkbFddWVStOFHvsH80OD55N/zr+9Hp2fnFr5fjydWHj799+p1PPV/M5ovgy024jOLVP4G17Pbu/uGP7u7ei5f7r356/eZ5xzHa7VECJOnfEO/dttgQ2+iZ7oghbNcXcn+EiNlhL5vq/s4OJi10+WCexNkKTxJesKnxotg4NBkNVo/0avAXJiuTNCIH0QmObjGVikn6piaAKZQLYBjiwhhwBkEOKk7rqVzVURGB6Z69o1N1YLUnvQbiVjUvLAvzS7wiVw14NAQGnD70xv3yEMzxNg2r775H3XP+IRdjEjM/ZYG0BpDHayUyqZJ2WAp0qCwERjbUl4Jaz/fxbjL+JIH9IZK4OkbX6vBHPShxPRyifpfKdVFFtvrwGvhRF4vVe11EwoUpfWux/gio6vwS35st28VMoGmEtIYlvobEi/+cxP5/TuKnEomSvHHb6KcbICaQzAUI
*/