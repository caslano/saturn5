// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace equals
{

/*!
    \brief Internal utility function to detect of points are disjoint
    \note To avoid circular references
 */
template <typename Point1, typename Point2, typename Strategy>
inline bool equals_point_point(Point1 const& point1, Point2 const& point2,
                               Strategy const& )
{
    return Strategy::apply(point1, point2);
}

}} // namespace detail::equals
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP

/* point_point.hpp
B/QVivNF5lWPe6EsYc4x+bYB25HjkworoK5/sOmTCZ9h6KrG6PPzxgwIZDd7cONKOskmiZTjPW1+wuwAfLfNbme/9LmAaJqnLQdn6PZR+2sqxpPjx243De66LR5kL9nyIsYLsLhLWuuYkexscy11l3s7fYXedtdfg5NDafas8vDk7NbICVtOIYzm90MLhGh57uS85vwTtlhBQWksJz8JF5YX5RTPLD0OA3hypDQrPrm0oHhPqJ2ukZtdm4mfM+UFWCMrhEYxBM38khfWxdAGMiCztUhBqD2q5cJwzI/EHIVaERuQjlIYwHT+J7r9zUy3v24q1+/ugMgTEF6ZSvdsjSriZ0rZvinds31uqmEWsOV9NxovKKvlD6WXUAbW6Jk2KosNB1nMZZHFrk7lcqf9R5noOxCmQHBY+UgqMM9mFU9UkV2cdaSL5REY66r23R9ZkRrGD816BT8tNkiNYlDIl9OwWqhNEdRiuUJZJgeBYYwin1ApF1Nn8YznC8D8kwE8n7cPz/fgj/javg8ir0P4CIJm0oXV18tEf9rOYVQYk8uWEhAYBUV928jeEfwM9IjHhnhHE82TWCvfaVPK1I2wdnfjYjRVzGMezweyewlX8PoaD5G5EO6rMJ2vZF82xBbWUesp9g3vokzxws5Xzq+wnq8sSYFae16ISqVyWOlSW7QsR5tGWOwI9eDdRsRq2aFqDsifw878nRN/oy1M
*/