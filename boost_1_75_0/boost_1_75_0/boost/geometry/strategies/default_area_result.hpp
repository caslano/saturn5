// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP


#include <boost/geometry/strategies/area_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of area function, using the default strategy
\ingroup area
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */

template <typename Geometry>
struct default_area_result
    : area_result<Geometry>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP

/* default_area_result.hpp
eQhrB3PKQh2wG7Vnrti2pWaZvbXoWu9k+XopuJqvamepJs3mEbkoIjyvTkW8LIZd4/urQaFRkm+kZWO6eoS+9UiirSApdodnjtZ05xBSO6Dld+r68WmMwzxQbFII0ebn2ELlgzrZXdValbvs6pFe9yvALnzNk3rqodLKzrdT/cFeXMwKz0GAvk8JTlInu0NRc2R24Ava7PRZOkv3B8gRbVL1h+fkAz2b5o7c8cBn1KmeOy8JaG11bFmORvWs2Zp0h16BT2ErS1VO3q1MxvGBkRY8Uj2c/j4vRb4dlMQX5cBJC17tV5URMD4VtpuW0CjD5+meOhWR/MlBxUoHZ9QUydaIisPG60XdxSiMYfMei2zobtDXaWCr8UjGrbHuLW0QWj5vBA0JXtyAousfXro/86kZDJQIFV5nOfKNL958PaZhce2UcuFZhFNZvu0gyTHZ/8Vu6CoHmQuQziUlHaR2R3EOmHpwgSHFuWk14hM30S9Mm3cebRZgpJvrg33x5p0OioGxZmexaHA4duAc/emPpke6L8kmtyZEftxUo4I7dFCQY6QJA+nowyXFZz0dP2gmEW9vrmvUOPBeZi0WJ/i0g3g04Jv33hSr5Hh+3oVauKRdCNFOW1d5l50O65ezyQAX7z2xNuv4ZcxtcugKZulpjuPLkVe86YL0d4nbGEbxZGCPeL9Dk7jJYu/mJIFwESnTgnf7b/fZ7f/wqvyV
*/