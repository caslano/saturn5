// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_INVERSE_TRANSFORMER_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_INVERSE_TRANSFORMER_HPP

#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace transform
{

/*!
\brief Transformation strategy to do an inverse transformation in a Cartesian coordinate system
\ingroup strategies
 */
template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class inverse_transformer
    : public matrix_transformer<CalculationType, Dimension1, Dimension2>
{
public :
    template <typename Transformer>
    inline inverse_transformer(Transformer const& input)
    {
        this->m_matrix = boost::qvm::inverse(input.matrix());
    }

};


}} // namespace strategy::transform


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_INVERSE_TRANSFORMER_HPP

/* inverse_transformer.hpp
Bq1iR9HISCWYqT5hwIWPqQAySDPYAj4rZpbVFFWk83hIwXG37LJOa0pun4wuuGCIlGL2MwKCx5UrryhYXkCKY6+IvPRcwKDPbLLC7roik/2lEBzrdVOVR32yVvGAbdn6ItjdeF+L8ZD3T1cdFaZbKuyGOmp4L2/uAas/bpiPA0T7xC4f2n733dFx7yjop3n0ykStI/KtF4Cld8jWsB5gg7oUxEm4cr0Ju/ZiZk4JbpEA1d3NbahpOjfSD2ZzehlF1FiJijlwsquW9w4aB18OMPoF8R1/D70FkDR1FXEqunqrJd4ryibhEnkPsJpkAuP+vIJhfk7cVVhcwUbHccCpVDGTulhT2+DXZ8/w82fPSiyxLFT/FP9Cig6utXD0FdjxE45KeXGwz8MHPC3Phv6zDu7pDSrM7UTikehPapFmTcNlpjo47mVut0uMGFP5Fku0HGKjcYy7UWkHTkcjxrhQbMlhVij55YxBychlh1710xij7T61yRf2QGhWHmGdNAXIsS1UuaQBEEiXIO+lK07nyECSi8N5YJshmUpDKEiCnAm/LucgHvq7NzJnZVQNmgf8iV3lj1Oab4OGjAzL1ByRqmiOe5VCgVVxSjIIy1TisEJnVc3YJX5WPLK6gGpsF28Z2gMdxNxjvo77Zwvg
*/