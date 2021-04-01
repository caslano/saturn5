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
b8m+sEwJCfX7a9NkvLfeEk+aen/Qk9HUKL5RXII6XMsz0WjgPFiHAY0408b1WWm5I6PGB1mJZJ667+eBLfpsJ6Z5SlE6MiLWTz8u1WHRxXb+gP0oKPpTs495HMtiRojxlF4mphFGqNjKDQW6WFt0DWES30nKfknyeTsWWPO+ZrS87UeE1zAr+CF7Yim70Obv0CneyGfd5YZ+zqula6OhoftMIxHYG9bqjyQ4S8+fZKwzB0gouoiutfrEfy24Rct8ltVY8joLSaU1oSAvFvMvCT2v+0yt2eNlMI5889qnahuVz8EZGK02QntfaaC6U4xw+RJLjBdFfqCxEwUroM6fwRgfyu0Yb8G2sTyd/RQ7QfA21/vkWORJX91/h1rgSAmLMcHzLfRCx4whCT9HqZdFsBzfcTutAZFafM+1lAbjlv9WpDF0olaoi2+uztWewVOEMBspJEqU310comGyUm5dLLYchDhb+uJZ+ZL8rd9QhMVKIKKoFFqLkAupD6V0fDTBCAgwN1d8dxslmRvQXqW+poJbkQZuRY0QnJmWL6OShjyi5//kj+V725zbdQ==
*/