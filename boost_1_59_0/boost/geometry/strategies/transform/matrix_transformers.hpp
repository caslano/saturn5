// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_MATRIX_TRANSFORMERS_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_MATRIX_TRANSFORMERS_HPP


#include <cstddef>

#include <boost/qvm/mat.hpp>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/mat_access.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/mat_operations.hpp>
#include <boost/qvm/vec_mat_operations.hpp>
#include <boost/qvm/map_mat_mat.hpp>
#include <boost/qvm/map_mat_vec.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace transform
{

namespace detail { namespace matrix_transformer
{

template
<
    typename Point,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = geometry::dimension<Point>::value
>
struct set_point_from_vec
{
    template <typename Vector>
    static inline void apply(Point & p, Vector const& v)
    {
        typedef typename geometry::coordinate_type<Point>::type coord_t;
        set<Dimension>(p, boost::numeric_cast<coord_t>(qvm::A<Dimension>(v)));
        set_point_from_vec<Point, Dimension + 1, DimensionCount>::apply(p, v);
    }
};

template
<
    typename Point,
    std::size_t DimensionCount
>
struct set_point_from_vec<Point, DimensionCount, DimensionCount>
{
    template <typename Vector>
    static inline void apply(Point &, Vector const&) {}
};

template
<
    typename Point,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = geometry::dimension<Point>::value
>
struct set_vec_from_point
{
    template <typename Vector>
    static inline void apply(Point const& p, Vector & v)
    {
        qvm::A<Dimension>(v) = get<Dimension>(p);
        set_vec_from_point<Point, Dimension + 1, DimensionCount>::apply(p, v);
    }
};

template
<
    typename Point,
    std::size_t DimensionCount
>
struct set_vec_from_point<Point, DimensionCount, DimensionCount>
{
    template <typename Vector>
    static inline void apply(Point const&, Vector &) {}
};

template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class matrix_transformer
{
protected :
    typedef CalculationType ct;
    typedef boost::qvm::mat<ct, Dimension2 + 1, Dimension1 + 1> matrix_type;
    matrix_type m_matrix;
public :
    matrix_type const& matrix() const { return m_matrix; }
    template <typename P1, typename P2>
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension_greater_equal<P1,Dimension1>();
        assert_dimension_greater_equal<P2,Dimension2>();
        qvm::vec<ct,Dimension1 + 1> p1temp;
        qvm::A<Dimension1>(p1temp) = 1;
        qvm::vec<ct,Dimension2 + 1> p2temp;
        set_vec_from_point<P1, 0, Dimension1>::apply(p1, p1temp);
        p2temp = m_matrix * p1temp;
        set_point_from_vec<P2, 0, Dimension2>::apply(p2, p2temp);
        return true;
    }

};

}} // namespace detail::matrix_transform

/*!
\brief Affine transformation strategy in Cartesian system.
\details The strategy serves as a generic definition of an affine transformation
         matrix and procedure for applying it to a given point.
\see http://en.wikipedia.org/wiki/Affine_transformation
     and http://www.devmaster.net/wiki/Transformation_matrices
\ingroup strategies
\tparam Dimension1 number of dimensions to transform from
\tparam Dimension2 number of dimensions to transform to
 */
template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class matrix_transformer : public detail::matrix_transformer::matrix_transformer<CalculationType, Dimension1, Dimension2>
{
public:
    template<typename Matrix>
    inline matrix_transformer(Matrix const& matrix)
    {
        qvm::assign(this->m_matrix, matrix);
    }
    inline matrix_transformer() {}
};


template <typename CalculationType>
class matrix_transformer<CalculationType, 2, 2> : public detail::matrix_transformer::matrix_transformer<CalculationType, 2, 2>
{
    typedef CalculationType ct;
public :
    template<typename Matrix>
    inline matrix_transformer(Matrix const& matrix)
    {
        qvm::assign(this->m_matrix, matrix);
    }

    inline matrix_transformer() {}

    inline matrix_transformer(
                ct const& m_0_0, ct const& m_0_1, ct const& m_0_2,
                ct const& m_1_0, ct const& m_1_1, ct const& m_1_2,
                ct const& m_2_0, ct const& m_2_1, ct const& m_2_2)
    {
        qvm::A<0,0>(this->m_matrix) = m_0_0;   qvm::A<0,1>(this->m_matrix) = m_0_1;   qvm::A<0,2>(this->m_matrix) = m_0_2;
        qvm::A<1,0>(this->m_matrix) = m_1_0;   qvm::A<1,1>(this->m_matrix) = m_1_1;   qvm::A<1,2>(this->m_matrix) = m_1_2;
        qvm::A<2,0>(this->m_matrix) = m_2_0;   qvm::A<2,1>(this->m_matrix) = m_2_1;   qvm::A<2,2>(this->m_matrix) = m_2_2;
    }

    template <typename P1, typename P2>
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension_greater_equal<P1, 2>();
        assert_dimension_greater_equal<P2, 2>();

        ct const& c1 = get<0>(p1);
        ct const& c2 = get<1>(p1);

        typedef typename geometry::coordinate_type<P2>::type ct2;
        set<0>(p2, boost::numeric_cast<ct2>(c1 * qvm::A<0,0>(this->m_matrix) + c2 * qvm::A<0,1>(this->m_matrix) + qvm::A<0,2>(this->m_matrix)));
        set<1>(p2, boost::numeric_cast<ct2>(c1 * qvm::A<1,0>(this->m_matrix) + c2 * qvm::A<1,1>(this->m_matrix) + qvm::A<1,2>(this->m_matrix)));

        return true;
    }
};


// It IS possible to go from 3 to 2 coordinates
template <typename CalculationType>
class matrix_transformer<CalculationType, 3, 2> : public detail::matrix_transformer::matrix_transformer<CalculationType, 3, 2>
{
    typedef CalculationType ct;
public :
    template<typename Matrix>
    inline matrix_transformer(Matrix const& matrix)
    {
        qvm::assign(this->m_matrix, matrix);
    }

    inline matrix_transformer() {}

    inline matrix_transformer(
                ct const& m_0_0, ct const& m_0_1, ct const& m_0_2,
                ct const& m_1_0, ct const& m_1_1, ct const& m_1_2,
                ct const& m_2_0, ct const& m_2_1, ct const& m_2_2)
    {
        qvm::A<0,0>(this->m_matrix) = m_0_0;   qvm::A<0,1>(this->m_matrix) = m_0_1;   qvm::A<0,2>(this->m_matrix) = 0;   qvm::A<0,3>(this->m_matrix) = m_0_2;
        qvm::A<1,0>(this->m_matrix) = m_1_0;   qvm::A<1,1>(this->m_matrix) = m_1_1;   qvm::A<1,2>(this->m_matrix) = 0;   qvm::A<1,3>(this->m_matrix) = m_1_2;
        qvm::A<2,0>(this->m_matrix) = m_2_0;   qvm::A<2,1>(this->m_matrix) = m_2_1;   qvm::A<2,2>(this->m_matrix) = 0;   qvm::A<2,3>(this->m_matrix) = m_2_2;
    }

    template <typename P1, typename P2>
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension_greater_equal<P1, 3>();
        assert_dimension_greater_equal<P2, 2>();

        ct const& c1 = get<0>(p1);
        ct const& c2 = get<1>(p1);
        ct const& c3 = get<2>(p1);

        typedef typename geometry::coordinate_type<P2>::type ct2;

        set<0>(p2, boost::numeric_cast<ct2>(
            c1 * qvm::A<0,0>(this->m_matrix) + c2 * qvm::A<0,1>(this->m_matrix) + c3 * qvm::A<0,2>(this->m_matrix) + qvm::A<0,3>(this->m_matrix)));
        set<1>(p2, boost::numeric_cast<ct2>(
            c1 * qvm::A<1,0>(this->m_matrix) + c2 * qvm::A<1,1>(this->m_matrix) + c3 * qvm::A<1,2>(this->m_matrix) + qvm::A<1,3>(this->m_matrix)));

        return true;
    }

};


template <typename CalculationType>
class matrix_transformer<CalculationType, 3, 3> : public detail::matrix_transformer::matrix_transformer<CalculationType, 3, 3>
{
    typedef CalculationType ct;
public :
    template<typename Matrix>
    inline matrix_transformer(Matrix const& matrix)
    {
        qvm::assign(this->m_matrix, matrix);
    }

    inline matrix_transformer() {}

    inline matrix_transformer(
                ct const& m_0_0, ct const& m_0_1, ct const& m_0_2, ct const& m_0_3,
                ct const& m_1_0, ct const& m_1_1, ct const& m_1_2, ct const& m_1_3,
                ct const& m_2_0, ct const& m_2_1, ct const& m_2_2, ct const& m_2_3,
                ct const& m_3_0, ct const& m_3_1, ct const& m_3_2, ct const& m_3_3
                )
    {
        qvm::A<0,0>(this->m_matrix) = m_0_0; qvm::A<0,1>(this->m_matrix) = m_0_1; qvm::A<0,2>(this->m_matrix) = m_0_2; qvm::A<0,3>(this->m_matrix) = m_0_3;
        qvm::A<1,0>(this->m_matrix) = m_1_0; qvm::A<1,1>(this->m_matrix) = m_1_1; qvm::A<1,2>(this->m_matrix) = m_1_2; qvm::A<1,3>(this->m_matrix) = m_1_3;
        qvm::A<2,0>(this->m_matrix) = m_2_0; qvm::A<2,1>(this->m_matrix) = m_2_1; qvm::A<2,2>(this->m_matrix) = m_2_2; qvm::A<2,3>(this->m_matrix) = m_2_3;
        qvm::A<3,0>(this->m_matrix) = m_3_0; qvm::A<3,1>(this->m_matrix) = m_3_1; qvm::A<3,2>(this->m_matrix) = m_3_2; qvm::A<3,3>(this->m_matrix) = m_3_3;
    }

    template <typename P1, typename P2>
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension_greater_equal<P1, 3>();
        assert_dimension_greater_equal<P2, 3>();

        ct const& c1 = get<0>(p1);
        ct const& c2 = get<1>(p1);
        ct const& c3 = get<2>(p1);

        typedef typename geometry::coordinate_type<P2>::type ct2;

        set<0>(p2, boost::numeric_cast<ct2>(
            c1 * qvm::A<0,0>(this->m_matrix) + c2 * qvm::A<0,1>(this->m_matrix) + c3 * qvm::A<0,2>(this->m_matrix) + qvm::A<0,3>(this->m_matrix)));
        set<1>(p2, boost::numeric_cast<ct2>(
            c1 * qvm::A<1,0>(this->m_matrix) + c2 * qvm::A<1,1>(this->m_matrix) + c3 * qvm::A<1,2>(this->m_matrix) + qvm::A<1,3>(this->m_matrix)));
        set<2>(p2, boost::numeric_cast<ct2>(
            c1 * qvm::A<2,0>(this->m_matrix) + c2 * qvm::A<2,1>(this->m_matrix) + c3 * qvm::A<2,2>(this->m_matrix) + qvm::A<2,3>(this->m_matrix)));

        return true;
    }
};


/*!
\brief Strategy of translate transformation in Cartesian system.
\details Translate moves a geometry a fixed distance in 2 or 3 dimensions.
\see http://en.wikipedia.org/wiki/Translation_%28geometry%29
\ingroup strategies
\tparam Dimension1 number of dimensions to transform from
\tparam Dimension2 number of dimensions to transform to
 */
template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class translate_transformer
{
};


template<typename CalculationType>
class translate_transformer<CalculationType, 2, 2> : public matrix_transformer<CalculationType, 2, 2>
{
public :
    // To have translate transformers compatible for 2/3 dimensions, the
    // constructor takes an optional third argument doing nothing.
    inline translate_transformer(CalculationType const& translate_x,
                CalculationType const& translate_y,
                CalculationType const& = 0)
        : matrix_transformer<CalculationType, 2, 2>(
                1, 0, translate_x,
                0, 1, translate_y,
                0, 0, 1)
    {}
};


template <typename CalculationType>
class translate_transformer<CalculationType, 3, 3> : public matrix_transformer<CalculationType, 3, 3>
{
public :
    inline translate_transformer(CalculationType const& translate_x,
                CalculationType const& translate_y,
                CalculationType const& translate_z)
        : matrix_transformer<CalculationType, 3, 3>(
                1, 0, 0, translate_x,
                0, 1, 0, translate_y,
                0, 0, 1, translate_z,
                0, 0, 0, 1)
    {}

};


/*!
\brief Strategy of scale transformation in Cartesian system.
\details Scale scales a geometry up or down in all its dimensions.
\see http://en.wikipedia.org/wiki/Scaling_%28geometry%29
\ingroup strategies
\tparam Dimension1 number of dimensions to transform from
\tparam Dimension2 number of dimensions to transform to
*/
template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class scale_transformer
{
};

template
<
    typename CalculationType,
    std::size_t Dimension1
>
class scale_transformer<CalculationType, Dimension1, Dimension1> : public matrix_transformer<CalculationType, Dimension1, Dimension1>
{
public:
    inline scale_transformer(CalculationType const& scale)
    {
        boost::qvm::set_identity(this->m_matrix);
        this->m_matrix*=scale;
        qvm::A<Dimension1,Dimension1>(this->m_matrix) = 1;
    }
};

template <typename CalculationType>
class scale_transformer<CalculationType, 2, 2> : public matrix_transformer<CalculationType, 2, 2>
{

public :
    inline scale_transformer(CalculationType const& scale_x,
                CalculationType const& scale_y,
                CalculationType const& = 0)
        : matrix_transformer<CalculationType, 2, 2>(
                scale_x, 0,       0,
                0,       scale_y, 0,
                0,       0,       1)
    {}


    inline scale_transformer(CalculationType const& scale)
        : matrix_transformer<CalculationType, 2, 2>(
                scale, 0,     0,
                0,     scale, 0,
                0,     0,     1)
    {}
};


template <typename CalculationType>
class scale_transformer<CalculationType, 3, 3> : public matrix_transformer<CalculationType, 3, 3>
{
public :
    inline scale_transformer(CalculationType const& scale_x,
                CalculationType const& scale_y,
                CalculationType const& scale_z)
        : matrix_transformer<CalculationType, 3, 3>(
                scale_x, 0,       0,       0,
                0,       scale_y, 0,       0,
                0,       0,       scale_z, 0,
                0,       0,       0,       1)
    {}


    inline scale_transformer(CalculationType const& scale)
        : matrix_transformer<CalculationType, 3, 3>(
                scale, 0,     0,     0,
                0,     scale, 0,     0,
                0,     0,     scale, 0,
                0,     0,     0,     1)
    {}
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename DegreeOrRadian>
struct as_radian
{};


template <>
struct as_radian<radian>
{
    template <typename T>
    static inline T get(T const& value)
    {
        return value;
    }
};

template <>
struct as_radian<degree>
{
    template <typename T>
    static inline T get(T const& value)
    {
        typedef typename promote_floating_point<T>::type promoted_type;
        return value * math::d2r<promoted_type>();
    }

};


template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class rad_rotate_transformer
    : public transform::matrix_transformer<CalculationType, Dimension1, Dimension2>
{
public :
    inline rad_rotate_transformer(CalculationType const& angle)
        : transform::matrix_transformer<CalculationType, Dimension1, Dimension2>(
                 cos(angle), sin(angle), 0,
                -sin(angle), cos(angle), 0,
                 0,          0,          1)
    {}
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Strategy for rotate transformation in Cartesian coordinate system.
\details Rotate rotates a geometry by a specified angle about a fixed point (e.g. origin).
\see http://en.wikipedia.org/wiki/Rotation_%28mathematics%29
\ingroup strategies
\tparam DegreeOrRadian degree/or/radian, type of rotation angle specification
\note A single angle is needed to specify a rotation in 2D.
      Not yet in 3D, the 3D version requires special things to allow
      for rotation around X, Y, Z or arbitrary axis.
\todo The 3D version will not compile.
 */
template
<
    typename DegreeOrRadian,
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class rotate_transformer : public detail::rad_rotate_transformer<CalculationType, Dimension1, Dimension2>
{

public :
    inline rotate_transformer(CalculationType const& angle)
        : detail::rad_rotate_transformer
            <
                CalculationType, Dimension1, Dimension2
            >(detail::as_radian<DegreeOrRadian>::get(angle))
    {}
};


}} // namespace strategy::transform


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_MATRIX_TRANSFORMERS_HPP

/* matrix_transformers.hpp
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
*/