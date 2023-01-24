// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP
#define BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace wkt
{

struct prefix_null
{
    static inline const char* apply() { return ""; }
};

struct prefix_point
{
    static inline const char* apply() { return "POINT"; }
};

struct prefix_polygon
{
    static inline const char* apply() { return "POLYGON"; }
};

struct prefix_linestring
{
    static inline const char* apply() { return "LINESTRING"; }
};

struct prefix_multipoint
{
    static inline const char* apply() { return "MULTIPOINT"; }
};

struct prefix_multilinestring
{
    static inline const char* apply() { return "MULTILINESTRING"; }
};

struct prefix_multipolygon
{
    static inline const char* apply() { return "MULTIPOLYGON"; }
};

}} // namespace wkt::impl
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP

/* prefix.hpp
O1u/EkpKLgq+J9xVvqwRjZkWRRAOxTbOH5t83NDpaXL99skpiNfpK4H49mUZg9KZqP9euusnXa02ABmCNdiBqJ/XanREAHcP8mqEkFqRTMZvcWX9iLGwe1mT4TLbXeMbXPLCwmUyCeioU1X9Y0SCCIfqnWagHin8bDuSLviazwzTJgrT0Iz37cYts1IpSBHeozgY/j0GlmKjw+JNOIg7Y1oK9R1Ni+ssKC394J0hmEN2LNCQT2IUinkJeMxTXTJiLpjd/FYZpBlqH9VQWlVnBO5yIeCxt/GIG0jbTqzFgLEp50xW4DapRk+panfmjKAf79yKXSNw+1xkD6T2f/9pdsg7V/tS08xUp8uvFUErrI9zwRVB67q4urTrAXXMN5ibgLUvzx9YsqbJSZQOIEo00rgG0oUr+M76Vkx2dOYj22t9TT30hC0S9Q3RTOncAjLq9TYNMY2+9wRcD1z06KadeW3ESvdYdF8baZxXGq12YFFkG+WDwlrIiu331GsLdF7gKg6oTmoboAAv7NJWY5VCh2mE1ovvWzXOP+sAvqGGAVTNXElk7J2wtaW/+nS7eGp3gRHh3zLQ18A+W2Hnyqjq5yrFk+xotZOz1kQyVfA8lp78F3VhGpqOxFYC0EC2Do/X0nU4krGGxyuKEbYWFnSNiX+yUmgt3ubrdLCwPByNE9wssEea7Ecf98p5Ot5GAievKqc+mLgofrO0r2XV
*/