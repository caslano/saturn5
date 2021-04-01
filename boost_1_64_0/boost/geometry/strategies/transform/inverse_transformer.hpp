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
oVTEW53SlA7guF9pHR7X6UIvobjZwR3lKAEmGiyBogStbnINs1uzX3+SF0YMlhbycNUY8a00XJkssKBJBAu569+E88yleKOxv5uZ4W7TdQLdWC9VoyWCExchJTzwP2liWx4JSpbB+OjPb7xRZMp8TtClI6a+1y1QGUdGp3JijrecnI34PBc3Md1VoD36pq0boPPjZymfW18Rh5HAUhg0T5WSkVA4h4/O+RaD+A3MaD0kAIOy0tqE4ijyqMAD1PY19RDtOJzn9HLgq+pAKij8mba5U96ZNoAa/8B4mB+Y874mmNKSuwXo79Eak9P7rFIaG4w2w0ORzkQSdDF2FOmXkUJiF6rHUUUT3xb/rcgi/YSNDIidOWTLzObcP5IEF5CqQPxwTJpaRiSW2Kb688k1JUAHmYwRiJqRazDJkuLVuIX+cCz8iQL+ygcI3dAuf5jlFnUvhOD+itfHRFjIBzWyt04O/ySR8RnCdYrmDheN4LZmuIgUdAY9jHKQr6+EZVP8zY50egQyveckI2gZ8WOI8V8+XoCWkv1Tyk39iCY/I5l5KjqLwEEjhvUfmQ==
*/