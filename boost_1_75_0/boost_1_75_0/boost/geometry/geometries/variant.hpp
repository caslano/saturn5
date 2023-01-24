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
huF4Ymigvk8VAt2O9eUC/29vcfKAdjUVvtW/m6rSAh5OWZYRep9iCvHxg7uWM4zfPhmNBsPxqGlinw/wZf6HFo3o4mW3iIOnFfJ8f00wnr7AWmZgmPazmb4PtXB8YyRi4z7TznFNoyHgzrE+l+v71TjH3dnJbVvgsYaU5/vVrRzfvUoQTPENQr8cOyULcpRkz/C/aY2jrHLa5j8wX0jePN8jL6My10udLmm5PuPNnEZPA497u3N8Rx/g+IahgYFwgvOfSkc5e8IcLxUeyTrC+tYU3+yvctr6wbCQZn9DnnGnoRWQvg9OdJZx3yvrY1uGB4RqVL773nfJcQvczklo5ysVLUHGGN4chuKXvNnGSG7n0HCMdXbuF0j8FONHp6UxFGuIBGDsgoZ73AuMfz2uVmBjIBEADWtf2Ubh15oGYeQMhTFnIIbhY9+Y5y9/DH1wXWej1YdBOz0ZttM3/q8Z2sTcrxAzAAf7wswuAQ1rgbmG/2OrY2FGiGyDfkIMEuUr9/95P9ch8fAqNrjYzB2IRkP2+DhPfEX+5jRWt+DpJB7uoYBenIt++cgyRt+UoH4pn8vxfe8Cx5vhweDQVo7fxyDT98wXBD60CWXB3c1Fxuy6lsG+yHAwpJbFxH40YYv1P6Pafx2MCbSxdMwt7/+2xI/lSd35+N0qPyYY0LBHIsP48I/bAzE+HwN3JgUypi5aPRyJoAWBG5+Cenuz
*/