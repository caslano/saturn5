// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP
#define BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace centroid
{

struct not_applicable_strategy
{
};


namespace services
{

/*!
    \brief Traits class binding a centroid calculation strategy to a coordinate system
    \ingroup centroid
    \tparam CsTag tag of coordinate system, for specialization
    \tparam GeometryTag tag of geometry, for specialization
    \tparam Dimension dimension of geometry, for specialization
    \tparam Point point-type
    \tparam Geometry
*/
template
<
    typename CsTag,
    typename GeometryTag,
    std::size_t Dimension,
    typename Point,
    typename Geometry
>
struct default_strategy
{
    typedef not_applicable_strategy type;
};


} // namespace services


}} // namespace strategy::centroid


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP

/* centroid.hpp
13deNlpnQjEI7O79KdhdjWWZBSaPbb+RzWmdNtt9Y1Oe/qmbslDQ2XtSKOy+qY1xsCRbRGKsMql/7f5c+B/84Mb/RjB50f6p3XnXJvmjFcyGlZPKsQYpI0zmLiaiovlgwKNoNBexX1FuxpbXmx3cp96M5RecsQVFWgdfWKQleszcKLoJwuG3X9olA4uNwQCWK+tdcAMwJvzD3vcY3hNbWTqsMTBB8DG4qFTT4eYbTFeJvT2QpEZN6kk+IjGT5bv+q76mPuqen8AKAi7oNs/RUO/23qIR3+i/x68v2qe1xulpV34U1vzXGBNt9k9MvP/yZGfnifyG/oOqAyG3QRj1XzImdX2HTw1JdAWM4ZJZUk2kzMY6zuXgiWqFKGFiP+6AWfhkWFe3xJyJP/mQjHVZmL5iDd8Xl9jRTeTbX/cOKPBamgvxWToiO1YnH3WssE6aS9jdQPre8PYetXFfpaaP2IKWeuCoqhTKjz2sePEgr3ZRPgZgR7md/FiyuVIjEC5A6G2gIK47B4dPbSKmRsQy8LJemYs+oHMdRe7Mg7Z6Sl+vlHHt36KE8N7VfgcPq/VbUoinpCeywgyT+gdKw/GIHvTbOzggNokowTgMKLhD2Qb4KyLfZgFVLmECTi0iek5ZBB00yl2rtO4FIFzx
*/