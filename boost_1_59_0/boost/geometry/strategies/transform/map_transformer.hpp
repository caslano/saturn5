// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_MAP_TRANSFORMER_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_MAP_TRANSFORMER_HPP


#include <cstddef>

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>

namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

namespace strategy { namespace transform
{

/*!
\brief Transformation strategy to map from one to another Cartesian coordinate system
\ingroup strategies
\tparam Mirror if true map is mirrored upside-down (in most cases pixels
    are from top to bottom, while map is from bottom to top)
 */
template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2,
    bool Mirror = false,
    bool SameScale = true
>
class map_transformer
    : public matrix_transformer<CalculationType, Dimension1, Dimension2>
{
    typedef boost::qvm::mat<CalculationType, Dimension1 + 1, Dimension2 + 1> M;
    typedef boost::qvm::mat<CalculationType, 3, 3> matrix33;

public :
    template <typename B, typename D>
    explicit inline map_transformer(B const& box, D const& width, D const& height)
    {
        set_transformation(
                get<min_corner, 0>(box), get<min_corner, 1>(box),
                get<max_corner, 0>(box), get<max_corner, 1>(box),
                width, height);
    }

    template <typename W, typename D>
    explicit inline map_transformer(W const& wx1, W const& wy1, W const& wx2, W const& wy2,
                        D const& width, D const& height)
    {
        set_transformation(wx1, wy1, wx2, wy2, width, height);
    }


private :
    template <typename W, typename P, typename S>
    inline void set_transformation_point(W const& wx, W const& wy,
        P const& px, P const& py,
        S const& scalex, S const& scaley)
    {

        // Translate to a coordinate system centered on world coordinates (-wx, -wy)
        matrix33 t1;
        qvm::A<0,0>(t1) = 1;   qvm::A<0,1>(t1) = 0;   qvm::A<0,2>(t1) = -wx;
        qvm::A<1,0>(t1) = 0;   qvm::A<1,1>(t1) = 1;   qvm::A<1,2>(t1) = -wy;
        qvm::A<2,0>(t1) = 0;   qvm::A<2,1>(t1) = 0;   qvm::A<2,2>(t1) = 1;

        // Scale the map
        matrix33 s;
        qvm::A<0,0>(s) = scalex;   qvm::A<0,1>(s) = 0;      qvm::A<0,2>(s) = 0;
        qvm::A<1,0>(s) = 0;        qvm::A<1,1>(s) = scaley; qvm::A<1,2>(s) = 0;
        qvm::A<2,0>(s) = 0;        qvm::A<2,1>(s) = 0;      qvm::A<2,2>(s) = 1;

        // Translate to a coordinate system centered on the specified pixels (+px, +py)
        matrix33 t2;
        qvm::A<0,0>(t2) = 1;   qvm::A<0,1>(t2) = 0;   qvm::A<0,2>(t2) = px;
        qvm::A<1,0>(t2) = 0;   qvm::A<1,1>(t2) = 1;   qvm::A<1,2>(t2) = py;
        qvm::A<2,0>(t2) = 0;   qvm::A<2,1>(t2) = 0;   qvm::A<2,2>(t2) = 1;

        // Calculate combination matrix in two steps
        this->m_matrix = s * t1;
        this->m_matrix = t2 * this->m_matrix;
    }


    template <typename W, typename D>
    void set_transformation(W const& wx1, W const& wy1, W const& wx2, W const& wy2,
                    D const& width, D const& height)
    {
        D px1 = 0;
        D py1 = 0;
        D px2 = width;
        D py2 = height;

        // Get the same type, but at least a double
        typedef typename select_most_precise<D, double>::type type;


        // Calculate appropriate scale, take min because whole box must fit
        // Scale is in PIXELS/MAPUNITS (meters)
        W wdx = wx2 - wx1;
        W wdy = wy2 - wy1;
        type sx = (px2 - px1) / boost::numeric_cast<type>(wdx);
        type sy = (py2 - py1) / boost::numeric_cast<type>(wdy);

        if (SameScale)
        {
            type scale = (std::min)(sx, sy);
            sx = scale;
            sy = scale;
        }

        // Calculate centerpoints
        W wtx = wx1 + wx2;
        W wty = wy1 + wy2;
        W two = 2;
        W wmx = wtx / two;
        W wmy = wty / two;
        type pmx = (px1 + px2) / 2.0;
        type pmy = (py1 + py2) / 2.0;

        set_transformation_point(wmx, wmy, pmx, pmy, sx, sy);

        if (Mirror)
        {
            // Mirror in y-direction
            matrix33 m;
            qvm::A<0,0>(m) = 1;   qvm::A<0,1>(m) = 0;   qvm::A<0,2>(m) = 0;
            qvm::A<1,0>(m) = 0;   qvm::A<1,1>(m) = -1;  qvm::A<1,2>(m) = 0;
            qvm::A<2,0>(m) = 0;   qvm::A<2,1>(m) = 0;   qvm::A<2,2>(m) = 1;

            // Translate in y-direction such that it fits again
            matrix33 y;
            qvm::A<0,0>(y) = 1;   qvm::A<0,1>(y) = 0;   qvm::A<0,2>(y) = 0;
            qvm::A<1,0>(y) = 0;   qvm::A<1,1>(y) = 1;   qvm::A<1,2>(y) = height;
            qvm::A<2,0>(y) = 0;   qvm::A<2,1>(y) = 0;   qvm::A<2,2>(y) = 1;

            // Calculate combination matrix in two steps
            this->m_matrix = m * this->m_matrix;
            this->m_matrix = y * this->m_matrix;
        }
    }
};


}} // namespace strategy::transform

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_MAP_TRANSFORMER_HPP

/* map_transformer.hpp
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
*/