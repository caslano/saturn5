// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_TRANSFORMATION_HPP
#define BOOST_GEOMETRY_SRS_TRANSFORMATION_HPP


#include <string>
#include <type_traits>

#include <boost/throw_exception.hpp>

#include <boost/geometry/algorithms/convert.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/grids.hpp>
#include <boost/geometry/srs/projections/impl/pj_transform.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


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
    bool SameUnits = std::is_same
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
    bool EnableTemporary = ! std::is_same
                                <
                                    typename select_most_precise
                                        <
                                            typename geometry::coordinate_type<OutGeometry>::type,
                                            CT
                                        >::type,
                                    typename geometry::coordinate_type<OutGeometry>::type
                                >::value
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
    template
    <
        typename Parameters1,
        std::enable_if_t
            <
                std::is_same<Proj1, srs::dynamic>::value
             && projections::dynamic_parameters<Parameters1>::is_specialized,
                int
            > = 0
    >
    explicit transformation(Parameters1 const& parameters1)
        : m_proj1(parameters1)
    {}

    // First static, second static and default constructed
    explicit transformation(Proj1 const& parameters1)
        : m_proj1(parameters1)
    {}

    // Both dynamic
    template
    <
        typename Parameters1, typename Parameters2,
        std::enable_if_t
            <
                std::is_same<Proj1, srs::dynamic>::value
             && std::is_same<Proj2, srs::dynamic>::value
             && projections::dynamic_parameters<Parameters1>::is_specialized
             && projections::dynamic_parameters<Parameters2>::is_specialized,
                int
            > = 0
    >
    transformation(Parameters1 const& parameters1,
                   Parameters2 const& parameters2)
        : m_proj1(parameters1)
        , m_proj2(parameters2)
    {}

    // First dynamic, second static
    template
    <
        typename Parameters1,
        std::enable_if_t
            <
                std::is_same<Proj1, srs::dynamic>::value
             && projections::dynamic_parameters<Parameters1>::is_specialized,
                int
            > = 0
    >
    transformation(Parameters1 const& parameters1,
                   Proj2 const& parameters2)
        : m_proj1(parameters1)
        , m_proj2(parameters2)
    {}

    // First static, second dynamic
    template
    <
        typename Parameters2,
        std::enable_if_t
            <
                std::is_same<Proj2, srs::dynamic>::value
             && projections::dynamic_parameters<Parameters2>::is_specialized,
                int
            > = 0
    >
    transformation(Proj1 const& parameters1,
                   Parameters2 const& parameters2)
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
        BOOST_GEOMETRY_STATIC_ASSERT(
            (projections::detail::same_tags<GeometryIn, GeometryOut>::value),
            "Not supported combination of Geometries.",
            GeometryIn, GeometryOut);

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
        BOOST_GEOMETRY_STATIC_ASSERT(
            (projections::detail::same_tags<GeometryIn, GeometryOut>::value),
            "Not supported combination of Geometries.",
            GeometryIn, GeometryOut);

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
wjWkYooY9lQC3QI6kqvdBF8upIpH2J6kER6vkj44mR8r5hNzJ9TFdtWHZkUPzbWrzkIq9CNfi+7D/gN6jpVdR6h+MQbVyqGgWjmI5t/A0fyj83i8kPyPYa+0mKXpnMu8jXs3S8z/wvOXgIn97k/xglw/EobUJ13Po0VOrx93p/BA1qwCLyDUCza7o5Dzt5+1jCEIJsWoSWNfsxl6kQReYOnprykwdD6ywG0XLMDz//E8WcyalLV4PUTGjQjL9gjPFqMUShfM80Oex4wN97DlAbggSF1uYqMlETk3Y05e6cSs03nWS5S1usTWHMQOuVndBdo48qU+MNzsgUjFPX6YkL+J4Q948CGXJw1gIVE04helRMF4YlFmjl55TFFBfQhlHoou3kBRBoA5K7ETL83tsAESgtKOjN/peJmTVPyIGapznSfk/vc2UeMbOHWFwA8iL2PsJJq6Yo0kCvO41NQ5M1Aesy4fzowTkNz14bQEnxY0WtY4sGPSTflnNXWqWzKUmahMRfyA9yDTlbx1zXFQWv55aQoQ6AblgQwKIwRZpE8BGEXqXaNqTWBuMpHaq7wCoIXdsX+RbvdOVK7BICr4hb3zfPJXaOJ0R2Gmod9CJm4q0rM6wlQEGlrnNSZwP0IcAVROvIED9sxTSiW+OaCrOTiJTk1YJF0BxdRGM5xsDFGkZ6OviL3aOWcGKkYFPrE9C97dU9XUTdOXYwgGcQPym91TwhI+INdZwebEtr083p+y0OQ7nSTN9p3OENcjo9d32tqU7Dv9DSnedzpTbH9Kk/LoPRPb/KTtwy57UQxVGNH35GDfh+YjDNAzsf2mEXID/i2eGkOMGahqV0lyeN88aA1twPjqTRLfB+LrTRlsM5R21XCdZNwqh2AvDA0jzLBzeVG82PYvUsqZysN/+liiZCorE9uTosbNzrnxsxMYPzsfjh92O0Y+d4QGHCJbPghfHs73RLblU3nJVFMF9rBJ8v+SOLrhjM2WPGRyOYMUztAV58NmCyeS2EuhdvazimXELJsPjzfDY2AWujoLNplNTUqXa/XPxPrJjvTc0ZNoYnzXb0Rh6E8AXAhtYvabk4UJ2HMNfjvBHmuAJamU3FEs7TPoVKWkRLkNcD0uG6dCHH8j5cM7He2HVtDxlVKwqMAGh/SiRiwaLLkQk2IgKcKiyoL1/fEGvd2nobCvFS70a5TSDLyVyaxqxNFdijxVods+YqGfUWTVsZE1UcLSZb0RwdTwfOvwZgr0M3+vlMA7VjJEcbkiQC9JjEoltCHdiYJWKZu2cVCC/A72rA9yiK+TMwa30cHOMhHZAslIkdygTaYZ+y++LmMe1P9ksMeAwBlwwfNR/nxASXp5luIFfG6aMgW90APZh84IgcxPCfxv/sdB/VFXlYt/gcbU1AIYSeBnkXGwUMB1wlZvAmSp7zVddoh2/FdS5Dri4YmKLjwECljnH5/4FVr9wDYAklauH2NXn8Q7595b4dVGBF1rri5P/Nc1CeTaRPq5ssCEIXYI6X7kGG1Sr1QMRTgN2PxXapQKvZcVLoTcPy0khBTbuojtkyGIbagCgNURWJwojlyOQcg0xrvH5CnShJKBwmA7Lma7VtdQVPaxZ46fUYF0Usa0dt814BYZI8cMzSpu/HMN3/7/S6yJncOQVecCcZxCLaNIXOGbiggGk5oq4K2xNELflBhPGFTowZf5ab+IGCeWcaoM7wfZ5hf4vnyiAn7lIyHHL1WRGi5puh0selRsJikJKoDaZh5C+ciJkNO3V1UjOX2T64Aa5AFFKSRpSwpiPyTJUt5hL24aVm0zSbbyLU1zaJ+UwY4/w3U8PKlcuHeES1NnO53qjY7AZYrdXOigMHQ3wuwERA4V809KSZihRqmwsKJrkoKu167ZREQFqlhFGq1HRBtHt5Iugl6nWcbLhEDVc2U6QF5S2W3QJd8RQ4EBPRynXYd4VRw8zA55jOOC2m2ao1p0Ddew9g8rvP7KFPbXB4HMJamrv9LI3nyQ+hMeYdi7cxnamt5RxZ1VajRXm/wL3HSs4TzMpb3NQYeN7Z+H2EebUjia3+W5keCjf8naxermEU3NVBG627Gc5phSmqYDsfJvJgsb6pX8vR7jXrsSBZWd4hnRafRanKrzG4fVvHpFQvT5h9cnC0P/S8QDj99Yf4THPZTrj3F7gxp/xSb2j1vJSUs05xJQXs9mziBwR2GGE99Gz03IDse3NxeJQsOuEv5yaKEouFVlDI1Ujugc4wkDMiiCUjbqtvqXHEEPvvZNUFR1NJJbbt7tBRvRNRpU6IMK4Rcdaf/1ViSe2sj/KXxmTzhCurU1QCYgq7LJ6GLPiydUNKquNMI6x8hFxoBBLjXJpcZlXS51jZGt177fgt+NchR+NsoLjOP1rd/99KuwPKWoERCTqC6lMEMrt7AR9xUhxSL78pe6+psht6MrVw8v3MB9P/8hpJg+GB7Abk7XhAB2mMQOXzuJjvrOl5si8colJqWz/SAA/o9fihfWeiXBc0mNco+RNagocxiHKC2DM+fLEMbrX5j3FklRE9M7oSvk/qkNqq7ZWygJyt1GJk5WMa932ThV+oc2oyZ6tvd2r+95ZB0Lvue5ac3+7lIJ4VJ3afNKnJsHJ9V9f0b4r3XfV25WNe10qJxalneTXvNu0nQGrIqU1Q3ulbWoqt48UVU9twOadsiljd3rUUJABtOlXjV1F7Yvr6fKHsfKQpEAr70VDv2Z8qACOg0YuQ6VuDmmcQU+eg7q+O1n56Gn7JWKSHN2NCBHW1PTj5HRizATIzQoCyTs+YLm5dDjiS7Wq0gE5qoBiOeAcqdK06KkW/3Lm50s6dww6WQbUCUb1bDPnR1W/cu9TnYSH0jX21HDNmUAlL0F+3cxbeQpvnwB7mz+mW38e7IGFLEvgVKeU9vyeibb0WRBXuBV1zQzF1SNatS30K+XLcBfUpxWX28jvYnjlyUJGuieIN1LD3FA07gmsaUGDVsBnnbg7NhKHR5zbq8swtkd2kPES0ruQa5hkN8DsyzXrJRrGqT783ukabaiDCnZVlroiXcb2Ze/QGdkttI0qUqpzLYVjUoLUQ+NGiptpog5xUbSY+4ky/IppLuLOnbkJLscGamksJuexaOGZGTBN01ht9ioVDYbShuGMFIqND0Tm05jx36qAwRAORsB5fRSJxxOrhDrYs/9XFXJv3k354om5kTqwU5q+FjZyJmIjcgG/D57MNjIcvIlUNoYYVGoa608I9kVAMvVvo5Ydwrkqsvq9LFYeFiRVVrr6zRklTZk2ccM9hFuDFla66jCltiPfi4iobeWR04lU8M7rxtnkkMaXFC3oUeurMNFKG2GPXIz7ZEC9s8n9Q7maJ1oDHWitBp7oTbVKvDUYXDAJFl4i+g8cPxuP5YWHv6Xb/t+2cNY3/MwkcWNJEUoRSlCURjSPiMrGRH0GPbGb0kn16zr4j6GG2hRIz+hixrDtHDl+xsho9fWmiGtRr1ZtGRyC1vd5zVDJrrjkmg09hF/SVSsv+JYlephQJ5wXtshBBTFcF1IuYCR3iwElUSLG4NYG/E5fPcDdSNC634fP0vTjyQLQeunM9dG+IHgyw9zu4zmtpZtfEKf23KXv7XapWtyeQpgH7hCKku4kue+jbR6Y9jERM1KFlxqUyOLah5R3Qa3wcVHNgk2+ee2MHPOcQrTOTo6Cc3kHtYFbIhVohbouhZTPFCbUhI9IJ/icVLI4KNVP05GANsNWB4xPuus6Yhswl8a/KXAnxW+ZSZw3VYLengqQF2HBTOIAToPLf0CuRRM/VbkgM7nl+cnmajogIEvgN5LsS3zekT/Q22kT1PWyHZ8BBvirKcXUVu9ZWZJT9C8IuWMQzCNAlv3gm446E7f+biM/k8WoOAgt2M3ddvTJ9uPynZY/yOyfUC2HwPKFPsM+9Rv7yOnxY9NJ3Q0SakYQG1V8rWfjoGvPX1syyUJAntugWWC8l4kPLSQxI2DAKXFTPpzvWIbwkHcD9wchzU9ru0Jse0FQjQA6HEiy2ZPEdsIgScIKLYR1m9Pk6ZzAQSyDi9G3l66dDFbXqGqgVSNkSgFSBVCV4HQ445VrlTisjoNC0zuKXoArDQlzoApCoDFpmw9NUNZYDYsMFK0QysBVUxUm0YVQw2qYTQG0lWPFcUrIdEzKnq7nGymn8NIDiGHZkUKnheG3Vus+TH9NOiOkSIwGprROaEZzYmQsZWgjI0V/yxcvpY+mXzNqszFQ5LV6f4SB0FaCVZUPJyLmheojcw9hNzzXUSZUemCNJTnCogvU0wSQwNizCRE4wWNJXomlMbxTB99lyRxGRgOyC9Z0w08iEk2qkSQFC6HKpgTlO+NFgdbz3Gw0VXYuhCs+ByveI6DtX8XLyGk76ocFHXToan8Z6KaA2Offq7qwroCPunSNZMK62JLSHbmZY/8epywbhrAbyUDhXW7AF/dC9je5AK7NdKFpXVbSsYLITiA6YD7NRPv1yttdpOUZiM8TbLAFT/jcVFz6JEXiHWwRHidgC8SYwuqYdd/iOEllNgGBE4k9MFL+ILZZ/132au/OrsORN662SLknnqTi3wAEhzF4LaeI+R6VAchBD88Jtlzji1OJaCXrtgHAKylArzj0G70SoJ2e6WLlRGEKC197OaLE9Bh0i3FJGxinc9FOIZBCpmtGSea+fD8BUUzmL3sv8s+/T/OjrkDXEqCUbCVQsCUGqIs4SIS9Nc9sdAOXigJCwFUt/UnCxOFKZjRH5lRwYwTq+RojFxqhUsSchcRpyVfE65IU3XZylQtxZOsw0Yd2ODuPNjeIW7Zs5h9+Gj45tO1VA4VEmtA1dzG4FavDopmFxw3AtkLeNu5cFZLPbJaEsnacR8ruh8w+iZETSyo6+ZSc2tYelqSkKsu0ESM0Zijm7mKYN0tYVSrNIOGkzKOcUTTG+aXjSUNJlII9BK5tEwuLZdLgRaq7o5tvu92b3dpYdSkhJr1Kwm1ocC2mHD8pbTcpcwrmbrcy2tFb7cOZJ87gk/V2tNy9Pj2u1BpvkZlUlKZFKMUlQdMSpEjYFCKIL8nWSmagzLzq6KjjEIgHhWYZ6C60ARxjq+1UJCSoRdIi2vZkMeLmxTGWsK2DiQK43YoehR6oFzwOGvY1oe/VHfGzAfUxW12MOE9gDhzc5Avo74vLyhn6/HzVP3z3w6KAn1wsB/gh7abtA89+ofqZaT32b2AonWwe6Ht5eOY649/nCj4VuUBLD16H0mousaJpzCZJR9J/ErxFGYaGoKqIgojbpAHiPGzT8ULWqiX2UqF2aGF33awhg2J5F8AbmSlMg8uZcCViRcNGK5Bi5ZTrzuv992bh9owS6AyZWEe5NzcB3nGL4De5uwLtTn64AXbHJjQ5vha+34ZrHVuRK2/5LUiekG1poVqPWDg+hZX2i1a5Wn6yfGO5/d4w/g9Sf7J+T0UyKv16RC/54Zwfo/xrQn8HkxigUsu6JPA/oCqcjBR2dwdm9IM6z3jMyPno6wlPgr3ISBPejx/+h/wUdzcnYvOR0mf2OBvhoyCzlrhjBRUzgiz+jfzxsM4KXKRt3tdm85FWUem/OuIEbNuU9BQBUBjDDJQ/pgfZKBge7p2RaU3jIfiDeehlDaj4f3UJjK8fwk6zO4omJyd8kf4qDNRgDZt9C9odsDA2EkPGkZT0CHuymBS/Ta03P/iAd3kXfommbv/4bPhMHN35K08DSlYMXM1jKjrujeRWEKBxEABGpoXfsbZInlY8Bavfw1SyKYatvdqUjjcz+bfM6w6WeX3dHt05SQzQ94JorlJ2SSEGnmJUWK3oDSoBW2xzRhs8xso7gF6TIp1stObEEFy4t0yQFtSjpOXG4c+EPQ4HcShF9se5Sz8mVgszbas0DMNsKtdVJhwNCptW4aslNJsZE4v5MbPFjJ+xnCPZtS15fRbmm4EbeVG0GnOkPEzqTxTlHLkpVQ2BOAqlZeh0qqZAm6iYbLhbiN0c40xkAtdugi7NMXJroscCTJULLkdGlsFmTLLGlipEslc+f2l45gr2rQRyerBihvZt2T9SK/knBFO5CNzpFMP/XYQ0NMDcEu53ClVSmVdVo9vCO7rylrD2/CvF5kYTlauiOgvJmRi94ou8XU6G17XnyOVEsKtmqPkqroIBan0nXPQzCXWZtENk4Fs/OQx5Hp4ietxO3I96sKIe+uMSIPk3U9ObpA8REwQr78Y9m7eVcn4rDFEvBEMES8ahqC0jayNt2sGxS1HiBxxf4m8/wjGiKHiqGKQK475K45UqZ4+ZIocIKYIXvlruPZ9ns4UQTfSrnCcRMOKBtj1/zByHS7oon3AwR6zouBkgCwjZ6irmyFdJu17ZkVV9+fId03AjHn9i5qZeA+qpQ0gavTp3cMqc+WFaV9pWPhNN5LWmbYTgsyLRzjzAv3vekb8pTA906HtbnsfoeuaEOWIXD8g14fj6nI9mds8H0+4+g1Ky0DgWuJPVHD+BAH7m9M0/sRUwNqTFQuAIwpIe4gik3neASxea4h5E5EvYSNPKOKWDtZ8I0fpj/8kEqWHbRGhRK6Ro/Qy5xkU64zDaiYhhy26OcUiLzEY0JKi2UoOLJHRcH2Uzmi4Gn1JJa0PMhrQSWjuKZsnTWxD9f2gbYXY9ktS7iXb7fQqZR8Fskfvm+jFSbJmcwtz29xslB6abNtJ6I7h5FjRDlg56JBLj5aZp1lDZGP888XNpPWu8TVadL4GqcBrfI2WNCk7ZOQxCw08splcoKqBWZqBh9h2BypRqwuG6uBXt/p4X2d19BSHrD0oIDZCuBGl0Ix69bdlG5AwJ4I8TKE+hxTq80IK9cTX2DeOr5HpqmH2ZgJPGok9ZcbkCvWl3qA5bAw7+xhpJgfZeog7lnrDznzORXA4etjUG0VyRUpSZzyRYRcbYTA6w2RR29czTCLvmgkMk6kbL6SQbGoxuE26QvJ5Ukg+P5lCcspXKiR/UIMRKzk7QuMB/SNtUnbEmlzSdEUtbCb8ZLw2bw2rQUt9cjxOjAiMf6tp8zZJrGetps2rSvFKHMbL1DkR3SxhzmScCJzHHJrHWdzTHtyRT7SHOBBxboFtaOf6FbH6RTUJhqEYUIeeEJIH/04auNc48WXJD2D/UyvT1abmkDiKFfgAzj1PcG4idnDMQtEbi9KkchvhXlKJUpVtu3lUKlDurVbuXulUltYp3Vl7DV2cN2cf8RtvpBelqsFQtQKTxpSiWriH7KPyknN+z8htAYP/7mq8njAk2tblIYerOgQ9d/1/xcfYaJzAxyComD1tAh/jvljiYzz4TQ70Tj/yFXwMou9pqg8RdjOO2QD7JOpH0NlboLO4KyC3784Rgd1IcZq5VzFlhHV8xC8c6DbFqz0lJeISVgLOfSlpDLIz1483uQhxDrz/HzkH3iDn4GnfRLaVZlxLwLEaGgla1m4IGdHOmUp6X3M0iAApV0wl+8nK6jDjySavphcWM3Vyg9r/ToPktLIGb82T0lJyBalpfpWHNEjuGQzTIInD4NqcrVFhcToRsiHKFogB7FPNqWFVcSF9D5t7WDfu+AqdDyTQ/hPWxjjVkJiHiCFU0F2aNusrdT8cP1tOuh/v3jms+rqzXaj5set74zU/gqRW389Pkt7487somhLpYXXHnmu+
*/