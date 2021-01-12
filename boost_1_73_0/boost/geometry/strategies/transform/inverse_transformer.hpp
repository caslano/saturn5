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
NR65TiBas89Avg9sm0NJP/LbQSY4lz7WT5Zf6Nwz5i4oLy1285sFEDdpWDAMikSLNk2Mn2l3kfOy7M8UxygrLaMJ3DpayP5ctJP92fdlzymotFJU5lJvpZgkbGJ/t5VxXM3LzT2FuWRLiqWNrGssoSWyJD0yuj7mb6rdCRnPrAc9jqqVji2rrTDPftN59Lw7tuZ33Vh5Je7yyspCd6k8smx/vFqpl58kboxQIfiv0YpDD9Qp
*/