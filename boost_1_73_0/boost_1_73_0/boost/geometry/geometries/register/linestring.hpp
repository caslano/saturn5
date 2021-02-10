// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING, linestring} The
    linestring may contain template parameters, which must be specified then.
\param Linestring \param_macro_type{linestring}

\qbk{
[heading Example]
[register_linestring]
[register_linestring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<Linestring> { typedef linestring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED, templated linestring}
    \details_macro_templated{linestring, point}
\param Linestring \param_macro_type{linestring (without template parameters)}

\qbk{
[heading Example]
[register_linestring_templated]
[register_linestring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename P> struct tag< Linestring<P> > { typedef linestring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP

/* linestring.hpp
Ms9LANpp9KLKL2b5LHr4qZ5WT/E/a+wnLmIEm/r5tvn8u2iscnyV1bM0nzef01BPnxAmmKZVnfwhcQ3wKlSKVs4yRkE5Ai3eIACwCL5m87yoowOgF9fZdTmP5gnPJtnZ4oLg8SmAfvL6/fHB6OTo9U/D09GPuyc/jk53Xx0MRyf7/3toJpEmMMx1lhSLa0CvW8l+MZ4DFOXFRQI44XwOiOCP/wa9wYX/4/Z2UqdXiEbgriZ/+G7zDJpcwynlRZb8c/I5+fdn/5y8gBfQEGaYJWe3dVZtJYC88+kULuunbH4rM0v4FKXDf/6XzX95lvyU8MoGiEHm2Tl2QTv0h58ImxZlncBBF/l5Pk6LemuD9uwcEND5stVu/BM0wCku2xFY3MY/AcDn5xthn6+PDg+Hr0/3jw75m2aPbS1w01x3tvHb9wen+9DucO9gmDz7/OzZs7P0bDvzrX44OtoLWvU+95O/wK718JdHjxL4Z/PldXqRj5MXL5qd9jc2qjqt4S2+ejsuATrwOAH2CG57gHIXwD+8JkjC+5Q8oX8GG8tZEfsd4pnkCWK0/k5zuHQyGRXZ53qE6KJcuCEReGsCtvJm1WjxiHeZacds26ZK/cXzvPuA0xLuyxPpZnRd+aE+lTlQ2Hk5BtQ3miFEFBcj
*/