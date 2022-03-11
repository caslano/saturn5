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