// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


#include <boost/range/adaptor/uniqued.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::uniqued_range<Geometry> >
#else
struct tag<boost::range_detail::unique_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


/* uniqued.hpp
Pr0SGEbleksRqBRivPt62sT74ck8XTK36aWkJ2BsAH7IL4jnbnFMibyLJaL2/0k+1tbOxXD3TGmdWU7AU4tuLHJ2cHjnB6j0qT9+H925tG6NOHhzNx4XasY4Xipo5eMmLOS5NUbIXFtmGZ7c0kvo6Q6h/gKfMGG5hvz3lokN4cSgi+KxlG1eMukDkZSR5e7j055stIu7aI9oJvoeAdJHiqzJO4QKEhPmaNsjD58sla3jvB+tzhW6xTW+Twn1p7OKQWaBDiviq2tUPsnewj4x+ggo7iCkaTSJ/GhOWNlvew7EifTRi3hKTkQLDAfm/603NtNc0vFpIj6VP4gcdX/UnP+7/AkwK1TK1F/fpy0aKN0LLEhDBbfY31FbsvZJhtN0gD09NDqZ1b6g/0CqKt/c+FMzcG23bVw9ZwA17qY5VNsFYvmNZCAE6jVpd8eKPk3EiqVAQla0996yxlZl/DFqJyMc0yEa4i9y5+GdaK3dcKT1qU63z3wASfY6FtLpeL3++nSJ7TAJy+5xqgrqHpJnaLZ1JlNIvi71pYJKNnvz+pPvhnb2tb5WGCtCfpbVfgQpQLWSmHN/ILLmv65Gh/10fqz27ut6chv15pWH4PrmFpy4R8zzy5TwGTnXDKC1QJ42XhhIu0P6ypNv6Jdznp2cPVal72xJGeN9yZM7D2OjT1Jrcnu/a95OqX9a3N3xBTN2In+0VyQiKUZBHtWd
*/