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
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
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