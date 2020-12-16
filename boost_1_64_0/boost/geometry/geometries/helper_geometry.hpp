// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace helper_geometries
{

template
<
    typename Point,
    typename NewCoordinateType,
    typename NewUnits,
    typename CS_Tag = typename cs_tag<Point>::type
>
struct helper_point
{
    typedef model::point
        <
            NewCoordinateType,
            dimension<Point>::value,
            typename cs_tag_to_coordinate_system<NewUnits, CS_Tag>::type
        > type;
};


}} // detail::helper_geometries


namespace detail_dispatch
{


template
<
    typename Geometry,
    typename NewCoordinateType,
    typename NewUnits,
    typename Tag = typename tag<Geometry>::type>
struct helper_geometry : not_implemented<Geometry>
{};


template <typename Point, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Point, NewCoordinateType, NewUnits, point_tag>
{
    typedef typename detail::helper_geometries::helper_point
        <
            Point, NewCoordinateType, NewUnits
        >::type type;
};


template <typename Box, typename NewCoordinateType, typename NewUnits>
struct helper_geometry<Box, NewCoordinateType, NewUnits, box_tag>
{
    typedef model::box
        <
            typename helper_geometry
                <
                    typename point_type<Box>::type, NewCoordinateType, NewUnits
                >::type
        > type;
};


} // detail_dispatch


// Meta-function that provides a new helper geometry of the same kind as
// the input geometry and the same coordinate system type,
// but with a possibly different coordinate type and coordinate system units
template
<
    typename Geometry,
    typename NewCoordinateType = typename coordinate_type<Geometry>::type,
    typename NewUnits = typename detail::cs_angular_units<Geometry>::type
>
struct helper_geometry
{
    typedef typename detail_dispatch::helper_geometry
        <
            Geometry, NewCoordinateType, NewUnits
        >::type type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_HELPER_GEOMETRY_HPP

/* helper_geometry.hpp
WKQ4G0FYp5413tRcwK2TNorcyIoUvvvlXVUr/RzySJrkkbOHpWijbWCEL8TehOVw8bCYJlRGSz1hKXbPr99yzNVSmZq1n3w3nMO5PIninz6iPyQ3c+VgSl37N/fatha5hiu3ErmyK7cUuYIrtxC5rCs3FznOlZsViysnXOFt/aZNtofvs3TukufFKqRf/+Jxdda2XvXfF6pjpE/stEnh73Pcttw23ydk/m/Tv/hZR1o/aJ0hbrr1Q47bzoSPTSzYYlv4mo5NPM8zgzAXDCgWZhPkKWNMJtO7c8TfGmZHfyX3nOSVIu+2UrRe+KWC6PfOXaiZNHe+Y7nIu6inot2xLJ9nLKuPmtGxUnd8jGzrfqf/S953VpndFwOl7gn/DtC20SlzZUVPCrqi3PmE8qLmt9eCkC9W3Kd99NiZieUSE2MrRuijHyLDLL3P7qPTEyosNJ30eKqy2KQS7bDj9jHxb01izh/xW+i4htf73bNzgO3fNM93z7OiNhmd8aE1KOr38ltsPyX6z2fVRkIDj7dK9dcDYl8HWjJ/8TiJeD7pI6L/PD2PwdGbQ4wmiH+cuHrpvzg/PNP+xnfn7shD0tf3zs+SR2ScsPi5m3O22hZ20HMc2/D8ivmCgSXzNQEvkUc1XKo/1V47QTw226pxGZea0MhEZLD0OFwiZrPpwwYjxtlSeV9f48fJS2c9vzJ0f2Wx+PDW+ce22ZpP8ZTX81n7VyWPeMM+YzznsI1xvloi1WOqv7q77vJfyM43yzxb73jMa3l29I90xwkyLzXyLeTnxd7vlun5Y7U8FzPTx2MmYC3XbxfHjPfbxTFXyT0b7QORP/S4M4plqFe63yw/yftHvfPMaofPOd9K3XPN4mDo++oP0bvVNZ9bzPyckHn+prA0Ls9ZQyN127ui91PLc9dI2B1wH8v7D5xxZ/memnSOZ5lGGnefJ7KkT7HvZ4l/aQ/Hu/1Gjd8S3yUSD8W+S5y4KZbndtie2shTVXmR+TEolOc0s40QG/LHRMpzqt8Zo6LdEnmeVc9KiDg/U85yzNQRMxVNXIi80GpiRYfyg8a3M09eS/RcJf1WzYtqT61Sv1GnyPvmKjMiJ3KM1P3HKXMLdmg/Nich3+7HBk0/NitC31D8cYVZMyB2DML3FbEXNdfeihH7h7nyriVv0S9qjn6/1CMlvrnPPhfYo/S5QO/YqY7ThPIQcalnUmr6f/yQbWGRz+5HbPbZa8QPhdKfgBdMoc88hYv8nMkZWSxe2n0Np8TsUt9R60bNH459dUpbK67vdSwL+WeRr/Ml+maWuOPBWQPxnei50TeZuF/Go/lB7apqVQutQ2ZM3D76N2/qJFmYL/bouXSmLxY1RMZerZ5WgjtWmOaaDzfqrGeeNNgehylvtVM1YkzULF8769GwPS7vi7o/bI/L26IW493j4pqvbL0v6rrHRdVPYv4z996CAaLWwNfEaivrHo6Tj9cW2fuDEgNVE+IS8ln10DvBrKaLC559rWC22DXY/Z6u4/hX86rH/VL37TYTPT2dvoQ3LGfdz1h+cGg/Y1+Nm+Dgknc5zJA0SlJ9xItXTePkd0n7Zb4hVnWfnAH3IHVGka43HGwO3dOzLXaS5kW6PnAMEZRk741x3mXy7kHHTCAuNIakdq4p0jV89c3xJO4RcNLfyObdGB5nDV9n7z0H+v5aniI1zwZWtMXEJbQtuUcnQ9M16iFd+1lYlFCHtZ/x50VOT6e+uXGw3a+8wIpx6huNK/9Z133eIuaqhK37XO9R6xMhLXqUkhbLxdxv5M6HJM7XEeYdu5y7J143iRFn1EeitoZnm6i/J4khdaK+28pjr/0sfN2JF8c+rLbuF3OPYF9iolE=
*/