// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_TRANSFORMATION_HPP
#define BOOST_GEOMETRY_SRS_TRANSFORMATION_HPP


#include <string>

#include <boost/geometry/algorithms/convert.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/grids.hpp>
#include <boost/geometry/srs/projections/impl/pj_transform.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace geometry
{

namespace projections { namespace detail
{

template <typename T1, typename T2>
inline bool same_object(T1 const& , T2 const& )
{
    return false;
}

template <typename T>
inline bool same_object(T const& o1, T const& o2)
{
    return boost::addressof(o1) == boost::addressof(o2);
}

template
<
    typename PtIn,
    typename PtOut,
    bool SameUnits = boost::is_same
                        <
                            typename geometry::detail::cs_angular_units<PtIn>::type,
                            typename geometry::detail::cs_angular_units<PtOut>::type
                        >::value
>
struct transform_geometry_point_coordinates
{
    static inline void apply(PtIn const& in, PtOut & out, bool /*enable_angles*/)
    {
        geometry::set<0>(out, geometry::get<0>(in));
        geometry::set<1>(out, geometry::get<1>(in));
    }
};

template <typename PtIn, typename PtOut>
struct transform_geometry_point_coordinates<PtIn, PtOut, false>
{
    static inline void apply(PtIn const& in, PtOut & out, bool enable_angles)
    {
        if (enable_angles)
        {
            geometry::set_from_radian<0>(out, geometry::get_as_radian<0>(in));
            geometry::set_from_radian<1>(out, geometry::get_as_radian<1>(in));
        }
        else
        {
            geometry::set<0>(out, geometry::get<0>(in));
            geometry::set<1>(out, geometry::get<1>(in));
        }
    }
};

template <typename Geometry, typename CT>
struct transform_geometry_point
{
    typedef typename geometry::point_type<Geometry>::type point_type;

    typedef geometry::model::point
        <   
            typename select_most_precise
                <
                    typename geometry::coordinate_type<point_type>::type,
                    CT
                >::type,
            geometry::dimension<point_type>::type::value,
            typename geometry::coordinate_system<point_type>::type
        > type;

    template <typename PtIn, typename PtOut>
    static inline void apply(PtIn const& in, PtOut & out, bool enable_angles)
    {
        transform_geometry_point_coordinates<PtIn, PtOut>::apply(in, out, enable_angles);
        projections::detail::copy_higher_dimensions<2>(in, out);
    }
};

template <typename Geometry, typename CT>
struct transform_geometry_range_base
{
    struct convert_strategy
    {
        convert_strategy(bool enable_angles)
            : m_enable_angles(enable_angles)
        {}

        template <typename PtIn, typename PtOut>
        void apply(PtIn const& in, PtOut & out)
        {
            transform_geometry_point<Geometry, CT>::apply(in, out, m_enable_angles);
        }

        bool m_enable_angles;
    };

    template <typename In, typename Out>
    static inline void apply(In const& in, Out & out, bool enable_angles)
    {
        // Change the order and/or closure if needed
        // In - arbitrary geometry
        // Out - either Geometry or std::vector
        // So the order and closure of In and Geometry shoudl be compared
        // std::vector's order is assumed to be the same as of Geometry
        geometry::detail::conversion::range_to_range
            <
                In,
                Out,
                geometry::point_order<In>::value != geometry::point_order<Out>::value
            >::apply(in, out, convert_strategy(enable_angles));
    }
};

template
<
    typename Geometry,
    typename CT,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct transform_geometry
{};

template <typename Point, typename CT>
struct transform_geometry<Point, CT, point_tag>
    : transform_geometry_point<Point, CT>
{};

template <typename Segment, typename CT>
struct transform_geometry<Segment, CT, segment_tag>
{
    typedef geometry::model::segment
        <
            typename transform_geometry_point<Segment, CT>::type
        > type;

    template <typename In, typename Out>
    static inline void apply(In const& in, Out & out, bool enable_angles)
    {
        apply<0>(in, out, enable_angles);
        apply<1>(in, out, enable_angles);
    }

private:
    template <std::size_t Index, typename In, typename Out>
    static inline void apply(In const& in, Out & out, bool enable_angles)
    {
        geometry::detail::indexed_point_view<In const, Index> in_pt(in);
        geometry::detail::indexed_point_view<Out, Index> out_pt(out);
        transform_geometry_point<Segment, CT>::apply(in_pt, out_pt, enable_angles);
    }
};

template <typename MultiPoint, typename CT>
struct transform_geometry<MultiPoint, CT, multi_point_tag>
    : transform_geometry_range_base<MultiPoint, CT>
{
    typedef model::multi_point
        <
            typename transform_geometry_point<MultiPoint, CT>::type
        > type;
};

template <typename LineString, typename CT>
struct transform_geometry<LineString, CT, linestring_tag>
    : transform_geometry_range_base<LineString, CT>
{
    typedef model::linestring
        <
            typename transform_geometry_point<LineString, CT>::type
        > type;
};

template <typename Ring, typename CT>
struct transform_geometry<Ring, CT, ring_tag>
    : transform_geometry_range_base<Ring, CT>
{
    typedef model::ring
        <
            typename transform_geometry_point<Ring, CT>::type,
            geometry::point_order<Ring>::value == clockwise,
            geometry::closure<Ring>::value == closed
        > type;
};


template
<
    typename OutGeometry,
    typename CT,
    bool EnableTemporary = ! boost::is_same
                                <
                                    typename select_most_precise
                                        <
                                            typename geometry::coordinate_type<OutGeometry>::type,
                                            CT
                                        >::type,
                                    typename geometry::coordinate_type<OutGeometry>::type
                                >::type::value
>
struct transform_geometry_wrapper
{
    typedef transform_geometry<OutGeometry, CT> transform;
    typedef typename transform::type type;

    template <typename InGeometry>
    transform_geometry_wrapper(InGeometry const& in, OutGeometry & out, bool input_angles)
        : m_out(out)
    {
        transform::apply(in, m_temp, input_angles);
    }

    type & get() { return m_temp; }
    void finish() { geometry::convert(m_temp, m_out); } // this is always copy 1:1 without changing the order or closure

private:
    type m_temp;
    OutGeometry & m_out;
};

template
<
    typename OutGeometry,
    typename CT
>
struct transform_geometry_wrapper<OutGeometry, CT, false>
{
    typedef transform_geometry<OutGeometry, CT> transform;
    typedef OutGeometry type;

    transform_geometry_wrapper(OutGeometry const& in, OutGeometry & out, bool input_angles)
        : m_out(out)
    {
        if (! same_object(in, out))
            transform::apply(in, out, input_angles);
    }

    template <typename InGeometry>
    transform_geometry_wrapper(InGeometry const& in, OutGeometry & out, bool input_angles)
        : m_out(out)
    {
        transform::apply(in, out, input_angles);
    }

    OutGeometry & get() { return m_out; }
    void finish() {}

private:
    OutGeometry & m_out;
};

template <typename CT>
struct transform_range
{
    template
    <
        typename Proj1, typename Par1,
        typename Proj2, typename Par2,
        typename RangeIn, typename RangeOut,
        typename Grids
    >
    static inline bool apply(Proj1 const& proj1, Par1 const& par1,
                             Proj2 const& proj2, Par2 const& par2,
                             RangeIn const& in, RangeOut & out,
                             Grids const& grids1, Grids const& grids2)
    {
        // NOTE: this has to be consistent with pj_transform()
        bool const input_angles = !par1.is_geocent && par1.is_latlong;

        transform_geometry_wrapper<RangeOut, CT> wrapper(in, out, input_angles);

        bool res = true;
        try
        {
            res = pj_transform(proj1, par1, proj2, par2, wrapper.get(), grids1, grids2);
        }
        catch (projection_exception const&)
        {
            res = false;
        }
        catch(...)
        {
            BOOST_RETHROW
        }

        wrapper.finish();

        return res;
    }
};

template <typename Policy>
struct transform_multi
{
    template
    <
        typename Proj1, typename Par1,
        typename Proj2, typename Par2,
        typename MultiIn, typename MultiOut,
        typename Grids
    >
    static inline bool apply(Proj1 const& proj1, Par1 const& par1,
                             Proj2 const& proj2, Par2 const& par2,
                             MultiIn const& in, MultiOut & out,
                             Grids const& grids1, Grids const& grids2)
    {
        if (! same_object(in, out))
            range::resize(out, boost::size(in));

        return apply(proj1, par1, proj2, par2,
                     boost::begin(in), boost::end(in),
                     boost::begin(out),
                     grids1, grids2);
    }

private:
    template
    <
        typename Proj1, typename Par1,
        typename Proj2, typename Par2,
        typename InIt, typename OutIt,
        typename Grids
    >
    static inline bool apply(Proj1 const& proj1, Par1 const& par1,
                             Proj2 const& proj2, Par2 const& par2,
                             InIt in_first, InIt in_last, OutIt out_first,
                             Grids const& grids1, Grids const& grids2)
    {
        bool res = true;
        for ( ; in_first != in_last ; ++in_first, ++out_first )
        {
            if ( ! Policy::apply(proj1, par1, proj2, par2, *in_first, *out_first, grids1, grids2) )
            {
                res = false;
            }
        }
        return res;
    }
};

template
<
    typename Geometry,
    typename CT,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct transform
    : not_implemented<Tag>
{};

template <typename Point, typename CT>
struct transform<Point, CT, point_tag>
{
    template
    <
        typename Proj1, typename Par1,
        typename Proj2, typename Par2,
        typename PointIn, typename PointOut,
        typename Grids
    >
    static inline bool apply(Proj1 const& proj1, Par1 const& par1,
                             Proj2 const& proj2, Par2 const& par2,
                             PointIn const& in, PointOut & out,
                             Grids const& grids1, Grids const& grids2)
    {
        // NOTE: this has to be consistent with pj_transform()
        bool const input_angles = !par1.is_geocent && par1.is_latlong;

        transform_geometry_wrapper<PointOut, CT> wrapper(in, out, input_angles);

        typedef typename transform_geometry_wrapper<PointOut, CT>::type point_type;
        point_type * ptr = boost::addressof(wrapper.get());

        std::pair<point_type *, point_type *> range = std::make_pair(ptr, ptr + 1);

        bool res = true;
        try
        {
            res = pj_transform(proj1, par1, proj2, par2, range, grids1, grids2);
        }
        catch (projection_exception const&)
        {
            res = false;
        }
        catch(...)
        {
            BOOST_RETHROW
        }

        wrapper.finish();

        return res;
    }
};

template <typename MultiPoint, typename CT>
struct transform<MultiPoint, CT, multi_point_tag>
    : transform_range<CT>
{};

template <typename Segment, typename CT>
struct transform<Segment, CT, segment_tag>
{
    template
    <
        typename Proj1, typename Par1,
        typename Proj2, typename Par2,
        typename SegmentIn, typename SegmentOut,
        typename Grids
    >
    static inline bool apply(Proj1 const& proj1, Par1 const& par1,
                             Proj2 const& proj2, Par2 const& par2,
                             SegmentIn const& in, SegmentOut & out,
                             Grids const& grids1, Grids const& grids2)
    {
        // NOTE: this has to be consistent with pj_transform()
        bool const input_angles = !par1.is_geocent && par1.is_latlong;

        transform_geometry_wrapper<SegmentOut, CT> wrapper(in, out, input_angles);

        typedef typename geometry::point_type
            <
                typename transform_geometry_wrapper<SegmentOut, CT>::type
            >::type point_type;

        point_type points[2];

        geometry::detail::assign_point_from_index<0>(wrapper.get(), points[0]);
        geometry::detail::assign_point_from_index<1>(wrapper.get(), points[1]);

        std::pair<point_type*, point_type*> range = std::make_pair(points, points + 2);

        bool res = true;
        try
        {
            res = pj_transform(proj1, par1, proj2, par2, range, grids1, grids2);
        }
        catch (projection_exception const&)
        {
            res = false;
        }
        catch(...)
        {
            BOOST_RETHROW
        }

        geometry::detail::assign_point_to_index<0>(points[0], wrapper.get());
        geometry::detail::assign_point_to_index<1>(points[1], wrapper.get());

        wrapper.finish();

        return res;
    }
};

template <typename Linestring, typename CT>
struct transform<Linestring, CT, linestring_tag>
    : transform_range<CT>
{};

template <typename MultiLinestring, typename CT>
struct transform<MultiLinestring, CT, multi_linestring_tag>
    : transform_multi<transform_range<CT> >
{};

template <typename Ring, typename CT>
struct transform<Ring, CT, ring_tag>
    : transform_range<CT>
{};

template <typename Polygon, typename CT>
struct transform<Polygon, CT, polygon_tag>
{
    template
    <
        typename Proj1, typename Par1,
        typename Proj2, typename Par2,
        typename PolygonIn, typename PolygonOut,
        typename Grids
    >
    static inline bool apply(Proj1 const& proj1, Par1 const& par1,
                             Proj2 const& proj2, Par2 const& par2,
                             PolygonIn const& in, PolygonOut & out,
                             Grids const& grids1, Grids const& grids2)
    {
        bool r1 = transform_range
                    <
                        CT
                    >::apply(proj1, par1, proj2, par2,
                             geometry::exterior_ring(in),
                             geometry::exterior_ring(out),
                             grids1, grids2);
        bool r2 = transform_multi
                    <
                        transform_range<CT>
                     >::apply(proj1, par1, proj2, par2,
                              geometry::interior_rings(in),
                              geometry::interior_rings(out),
                              grids1, grids2);
        return r1 && r2;
    }
};

template <typename MultiPolygon, typename CT>
struct transform<MultiPolygon, CT, multi_polygon_tag>
    : transform_multi
        <
            transform
                <
                    typename boost::range_value<MultiPolygon>::type,
                    CT,
                    polygon_tag
                >
        >
{};


}} // namespace projections::detail
    
namespace srs
{


/*!
    \brief Representation of projection
    \details Either dynamic or static projection representation
    \ingroup projection
    \tparam Proj1 default_dynamic or static projection parameters
    \tparam Proj2 default_dynamic or static projection parameters
    \tparam CT calculation type used internally
*/
template
<
    typename Proj1 = srs::dynamic,
    typename Proj2 = srs::dynamic,
    typename CT = double
>
class transformation
{
    typedef typename projections::detail::promote_to_double<CT>::type calc_t;

public:
    // Both static and default constructed
    transformation()
    {}

    // First dynamic, second static and default constructed
    template <typename Parameters1>
    explicit transformation(Parameters1 const& parameters1,
                            typename boost::enable_if_c
                                <
                                    boost::is_same<Proj1, srs::dynamic>::value
                                 && projections::dynamic_parameters<Parameters1>::is_specialized
                                >::type * = 0)
        : m_proj1(parameters1)
    {}

    // First static, second static and default constructed
    explicit transformation(Proj1 const& parameters1)
        : m_proj1(parameters1)
    {}

    // Both dynamic
    template <typename Parameters1, typename Parameters2>
    transformation(Parameters1 const& parameters1,
                   Parameters2 const& parameters2,
                   typename boost::enable_if_c
                        <
                            boost::is_same<Proj1, srs::dynamic>::value
                         && boost::is_same<Proj2, srs::dynamic>::value
                         && projections::dynamic_parameters<Parameters1>::is_specialized
                         && projections::dynamic_parameters<Parameters2>::is_specialized
                        > * = 0)
        : m_proj1(parameters1)
        , m_proj2(parameters2)
    {}

    // First dynamic, second static
    template <typename Parameters1>
    transformation(Parameters1 const& parameters1,
                   Proj2 const& parameters2,
                   typename boost::enable_if_c
                        <
                            boost::is_same<Proj1, srs::dynamic>::value
                         && projections::dynamic_parameters<Parameters1>::is_specialized
                        > * = 0)
        : m_proj1(parameters1)
        , m_proj2(parameters2)
    {}

    // First static, second dynamic
    template <typename Parameters2>
    transformation(Proj1 const& parameters1,
                   Parameters2 const& parameters2,
                   typename boost::enable_if_c
                        <
                            boost::is_same<Proj2, srs::dynamic>::value
                         && projections::dynamic_parameters<Parameters2>::is_specialized
                        > * = 0)
        : m_proj1(parameters1)
        , m_proj2(parameters2)
    {}

    // Both static
    transformation(Proj1 const& parameters1,
                   Proj2 const& parameters2)
        : m_proj1(parameters1)
        , m_proj2(parameters2)
    {}

    template <typename GeometryIn, typename GeometryOut>
    bool forward(GeometryIn const& in, GeometryOut & out) const
    {
        return forward(in, out, transformation_grids<detail::empty_grids_storage>());
    }

    template <typename GeometryIn, typename GeometryOut>
    bool inverse(GeometryIn const& in, GeometryOut & out) const
    {
        return inverse(in, out, transformation_grids<detail::empty_grids_storage>());
    }

    template <typename GeometryIn, typename GeometryOut, typename GridsStorage>
    bool forward(GeometryIn const& in, GeometryOut & out,
                 transformation_grids<GridsStorage> const& grids) const
    {
        BOOST_MPL_ASSERT_MSG((projections::detail::same_tags<GeometryIn, GeometryOut>::value),
                             NOT_SUPPORTED_COMBINATION_OF_GEOMETRIES,
                             (GeometryIn, GeometryOut));

        return projections::detail::transform
                <
                    GeometryOut,
                    calc_t
                >::apply(m_proj1.proj(), m_proj1.proj().params(),
                         m_proj2.proj(), m_proj2.proj().params(),
                         in, out,
                         grids.src_grids,
                         grids.dst_grids);
    }

    template <typename GeometryIn, typename GeometryOut, typename GridsStorage>
    bool inverse(GeometryIn const& in, GeometryOut & out,
                 transformation_grids<GridsStorage> const& grids) const
    {
        BOOST_MPL_ASSERT_MSG((projections::detail::same_tags<GeometryIn, GeometryOut>::value),
                             NOT_SUPPORTED_COMBINATION_OF_GEOMETRIES,
                             (GeometryIn, GeometryOut));

        return projections::detail::transform
                <
                    GeometryOut,
                    calc_t
                >::apply(m_proj2.proj(), m_proj2.proj().params(),
                         m_proj1.proj(), m_proj1.proj().params(),
                         in, out,
                         grids.dst_grids,
                         grids.src_grids);
    }

    template <typename GridsStorage>
    inline transformation_grids<GridsStorage> initialize_grids(GridsStorage & grids_storage) const
    {
        transformation_grids<GridsStorage> result(grids_storage);

        using namespace projections::detail;
        pj_gridlist_from_nadgrids(m_proj1.proj().params(),
                                  result.src_grids);
        pj_gridlist_from_nadgrids(m_proj2.proj().params(),
                                  result.dst_grids);

        return result;
    }

private:
    projections::proj_wrapper<Proj1, CT> m_proj1;
    projections::proj_wrapper<Proj2, CT> m_proj2;
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_TRANSFORMATION_HPP

/* transformation.hpp
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
*/