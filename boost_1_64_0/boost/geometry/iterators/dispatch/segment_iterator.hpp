// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for segments_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_begin
    : not_implemented<Geometry>
{};



// dispatch for segments_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
Y/VLIO1SvXNslrIglVaoyFjtbz/nWkoHzBojp2h9y+5p3ORZDSt4unnIwJvPwr6wiF5wFd7zskuP4HoIvhaHf+gzj9CjtHIFtOwOw5OuDJ6Qj68sprQXA2eQSDftFiTBNxEkk+UN6XmJzkP97HrwrsvtjCm7aRfF7seTTSeqnUY1XQkm4LNXv3nQon2yJ/rEdBemPwZPoh/AMd1ZyiZV7Cl4y3IIwty5EKfWW9x+bkZ9JCKNewFAtpq9yRB4uu+PKxtiL2VxhZEgZcWQzCSwy6dHU0SJwW1zTJRyjLh1/ceFff7KJWLnIPyFiZL779OUThy8qSR8hjX+McWVxCZAjRFAAU5E5ToByNtLH4VbcvKoA7xUJI95oUvthFwVfItRSqDqraVikg49e3zp2FW59uQ20RxwpuhfQ7lvCpKJ6NRFI73iBu92CH69M7J3vYbQMq/ll8kmvK9AFk1RIDQJYx9M9P3zJdTspCWQOQia6Z/asMKqa0u0fFwYzq8qXh28iodV6X4TERjMlMxA7wigDl/MydikwQVET/6kst9sd6Gm/FE2VeGSmevT3w==
*/