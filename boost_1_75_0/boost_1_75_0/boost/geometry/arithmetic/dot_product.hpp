// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename P1, typename P2, std::size_t Dimension, std::size_t DimensionCount>
struct dot_product_maker
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<Dimension>(p1) * get<Dimension>(p2)
            + dot_product_maker<P1, P2, Dimension+1, DimensionCount>::apply(p1, p2);
    }
};

template <typename P1, typename P2, std::size_t DimensionCount>
struct dot_product_maker<P1, P2, DimensionCount, DimensionCount>
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<DimensionCount>(p1) * get<DimensionCount>(p2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Computes the dot product (or scalar product) of 2 vectors (points).
    \ingroup arithmetic
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
    \return the dot product
    
    \qbk{[heading Examples]}
    \qbk{[dot_product] [dot_product_output]}

 */
template <typename Point1, typename Point2>
inline typename select_coordinate_type<Point1, Point2>::type dot_product(
        Point1 const& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    return detail::dot_product_maker
        <
            Point1, Point2,
            0, dimension<Point1>::type::value - 1
        >::apply(p1, p2);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP

/* dot_product.hpp
/tsaIqF7DVaaVpHy3RBv/A86RfeSF3121xPnvuv3CTunj2QnG9wfnGZUK8xv9nPYqXTuUTfPm7YdZ7M9QzLs/s1JSUviFVb0cawUHHcO7Vwf8v8r3y4Fq8QtWBt/P4Zzw6/ALhTNBfP6HV9TJdHZJ6sXSNrU/YuwqwyLqtvCpJSEdIdICEg3DEN8iEgjAkoMiIQi3TGMtOSoIA0DIoLS0h1D14B0DjjA0F0Dw3C513t/31/ned613xXnPPvsvdbZZ+8xY4A34gm7b9BOh1qt/WfQvd85NSnRBCr2sBbt+yyxH1UlnwhuJkLo+sWxYjEPUEjBz4+N+yiClXnUvgmsk2p+6L3wPgPd/659P/zC1N+M/prtSVgM1TMlQvxf2tSrn9StuyZs4/ch5gOy+BDHN7wSp/RHdx9SSNv9tH2Nh5Phib9vSsRgdJTFu09ms+lnd3n2jWM2rlkKUy+gzQjag2kTx/D3EgQljQmCqEXEOPj242Axrx8ghjWeS38OuDv2degqbcj24vXD1/IqFgTrd/l+XHSxvCYVC3KgMbM2E1kjTHYArvff/3avbVOXhIQZyJaifarrkxI297Wxr33hxxPUqRpu5DgrSnl4lXs9aHgwKejs2apYUebZqs7ZzmNJGoigAPV59IwBStnKPEcj4Ug5xiA1dG28bRgdFLGm9FsQdg/Gk/2iH0/Eq/qfJaKUc8FBHZcHujb2shPt
*/