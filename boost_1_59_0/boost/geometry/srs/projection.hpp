// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTION_HPP
#define BOOST_GEOMETRY_SRS_PROJECTION_HPP


#include <string>
#include <type_traits>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/factory.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/pj_init.hpp>
#include <boost/geometry/srs/projections/invalid_point.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/spar.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename G1, typename G2>
struct same_tags
    : std::is_same
        <
            typename geometry::tag<G1>::type,
            typename geometry::tag<G2>::type
        >
{};

template <typename CT>
struct promote_to_double
{
    typedef std::conditional_t
        <
            std::is_integral<CT>::value || std::is_same<CT, float>::value,
            double, CT
        > type;
};

// Copy coordinates of dimensions >= MinDim
template <std::size_t MinDim, typename Point1, typename Point2>
inline void copy_higher_dimensions(Point1 const& point1, Point2 & point2)
{
    static const std::size_t dim1 = geometry::dimension<Point1>::value;
    static const std::size_t dim2 = geometry::dimension<Point2>::value;
    static const std::size_t lesser_dim = dim1 < dim2 ? dim1 : dim2;
    BOOST_GEOMETRY_STATIC_ASSERT((lesser_dim >= MinDim),
        "The dimension of Point1 or Point2 is too small.",
        Point1, Point2);

    geometry::detail::conversion::point_to_point
        <
            Point1, Point2, MinDim, lesser_dim
        > ::apply(point1, point2);

    // TODO: fill point2 with zeros if dim1 < dim2 ?
    // currently no need because equal dimensions are checked
}


struct forward_point_projection_policy
{
    template <typename LL, typename XY, typename Proj>
    static inline bool apply(LL const& ll, XY & xy, Proj const& proj)
    {
        return proj.forward(ll, xy);
    }
};

struct inverse_point_projection_policy
{
    template <typename XY, typename LL, typename Proj>
    static inline bool apply(XY const& xy, LL & ll, Proj const& proj)
    {
        return proj.inverse(xy, ll);
    }
};

template <typename PointPolicy>
struct project_point
{
    template <typename P1, typename P2, typename Proj>
    static inline bool apply(P1 const& p1, P2 & p2, Proj const& proj)
    {
        // (Geographic -> Cartesian) will be projected, rest will be copied.
        // So first copy third or higher dimensions
        projections::detail::copy_higher_dimensions<2>(p1, p2);

        if (! PointPolicy::apply(p1, p2, proj))
        {
            // For consistency with transformation
            set_invalid_point(p2);
            return false;
        }

        return true;
    }
};

template <typename PointPolicy>
struct project_range
{
    template <typename Proj>
    struct convert_policy
    {
        explicit convert_policy(Proj const& proj)
            : m_proj(proj)
            , m_result(true)
        {}

        template <typename Point1, typename Point2>
        inline void apply(Point1 const& point1, Point2 & point2)
        {
            if (! project_point<PointPolicy>::apply(point1, point2, m_proj) )
                m_result = false;
        }

        bool result() const
        {
            return m_result;
        }

    private:
        Proj const& m_proj;
        bool m_result;
    };

    template <typename R1, typename R2, typename Proj>
    static inline bool apply(R1 const& r1, R2 & r2, Proj const& proj)
    {
        return geometry::detail::conversion::range_to_range
            <
                R1, R2,
                geometry::point_order<R1>::value != geometry::point_order<R2>::value
            >::apply(r1, r2, convert_policy<Proj>(proj)).result();
    }
};

template <typename Policy>
struct project_multi
{
    template <typename G1, typename G2, typename Proj>
    static inline bool apply(G1 const& g1, G2 & g2, Proj const& proj)
    {
        range::resize(g2, boost::size(g1));
        return apply(boost::begin(g1), boost::end(g1),
                     boost::begin(g2),
                     proj);
    }

private:
    template <typename It1, typename It2, typename Proj>
    static inline bool apply(It1 g1_first, It1 g1_last, It2 g2_first, Proj const& proj)
    {
        bool result = true;
        for ( ; g1_first != g1_last ; ++g1_first, ++g2_first )
        {
            if (! Policy::apply(*g1_first, *g2_first, proj))
            {
                result = false;
            }
        }
        return result;
    }
};

template
<
    typename Geometry,
    typename PointPolicy,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct project_geometry
{};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, point_tag>
    : project_point<PointPolicy>
{};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, multi_point_tag>
    : project_range<PointPolicy>
{};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, segment_tag>
{
    template <typename G1, typename G2, typename Proj>
    static inline bool apply(G1 const& g1, G2 & g2, Proj const& proj)
    {
        bool r1 = apply<0>(g1, g2, proj);
        bool r2 = apply<1>(g1, g2, proj);
        return r1 && r2;
    }

private:
    template <std::size_t Index, typename G1, typename G2, typename Proj>
    static inline bool apply(G1 const& g1, G2 & g2, Proj const& proj)
    {
        geometry::detail::indexed_point_view<G1 const, Index> pt1(g1);
        geometry::detail::indexed_point_view<G2, Index> pt2(g2);
        return project_point<PointPolicy>::apply(pt1, pt2, proj);
    }
};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, linestring_tag>
    : project_range<PointPolicy>
{};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, multi_linestring_tag>
    : project_multi< project_range<PointPolicy> >
{};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, ring_tag>
    : project_range<PointPolicy>
{};

template <typename Geometry, typename PointPolicy>
struct project_geometry<Geometry, PointPolicy, polygon_tag>
{
    template <typename G1, typename G2, typename Proj>
    static inline bool apply(G1 const& g1, G2 & g2, Proj const& proj)
    {
        bool r1 = project_range
                    <
                        PointPolicy
                    >::apply(geometry::exterior_ring(g1),
                             geometry::exterior_ring(g2),
                             proj);
        bool r2 = project_multi
                    <
                        project_range<PointPolicy>
                    >::apply(geometry::interior_rings(g1),
                             geometry::interior_rings(g2),
                             proj);
        return r1 && r2;
    }
};

template <typename MultiPolygon, typename PointPolicy>
struct project_geometry<MultiPolygon, PointPolicy, multi_polygon_tag>
    : project_multi
        <
            project_geometry
            <
                typename boost::range_value<MultiPolygon>::type,
                PointPolicy,
                polygon_tag
            >
        >
{};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename Params>
struct dynamic_parameters
{
    static const bool is_specialized = false;
};

template <>
struct dynamic_parameters<srs::proj4>
{
    static const bool is_specialized = true;
    static inline srs::detail::proj4_parameters apply(srs::proj4 const& params)
    {
        return srs::detail::proj4_parameters(params.str());
    }
};

template <typename T>
struct dynamic_parameters<srs::dpar::parameters<T> >
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<T> const& apply(srs::dpar::parameters<T> const& params)
    {
        return params;
    }
};


// proj_wrapper class and its specializations wrapps the internal projection
// representation and implements transparent creation of projection object
template <typename Proj, typename CT>
class proj_wrapper
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Unknown projection definition.",
        Proj);
};

template <typename CT>
class proj_wrapper<srs::dynamic, CT>
{
    // Some projections do not work with float -> wrong results
    // select <double> from int/float/double and else selects T
    typedef typename projections::detail::promote_to_double<CT>::type calc_t;

    typedef projections::parameters<calc_t> parameters_type;
    typedef projections::detail::dynamic_wrapper_b<calc_t, parameters_type> vprj_t;

public:
    template
    <
        typename Params,
        std::enable_if_t
            <
                dynamic_parameters<Params>::is_specialized,
                int
            > = 0
    >
    proj_wrapper(Params const& params)
        : m_ptr(create(dynamic_parameters<Params>::apply(params)))
    {}

    vprj_t const& proj() const { return *m_ptr; }
    vprj_t & mutable_proj() { return *m_ptr; }

private:
    template <typename Params>
    static vprj_t* create(Params const& params)
    {
        parameters_type parameters = projections::detail::pj_init<calc_t>(params);

        vprj_t* result = projections::detail::create_new(params, parameters);

        if (result == NULL)
        {
            if (parameters.id.is_unknown())
            {
                BOOST_THROW_EXCEPTION(projection_not_named_exception());
            }
            else
            {
                // TODO: handle non-string projection id
                BOOST_THROW_EXCEPTION(projection_unknown_id_exception());
            }
        }

        return result;
    }

    boost::shared_ptr<vprj_t> m_ptr;
};

template <typename StaticParameters, typename CT>
class static_proj_wrapper_base
{
    typedef typename projections::detail::promote_to_double<CT>::type calc_t;

    typedef projections::parameters<calc_t> parameters_type;

    typedef typename srs::spar::detail::pick_proj_tag
        <
            StaticParameters
        >::type proj_tag;
    
    typedef typename projections::detail::static_projection_type
        <
            proj_tag,
            typename projections::detail::static_srs_tag<StaticParameters>::type,
            StaticParameters,
            calc_t,
            parameters_type
        >::type projection_type;

public:
    projection_type const& proj() const { return m_proj; }
    projection_type & mutable_proj() { return m_proj; }

protected:
    explicit static_proj_wrapper_base(StaticParameters const& s_params)
        : m_proj(s_params,
                 projections::detail::pj_init<calc_t>(s_params))
    {}

private:
    projection_type m_proj;
};

template <typename ...Ps, typename CT>
class proj_wrapper<srs::spar::parameters<Ps...>, CT>
    : public static_proj_wrapper_base<srs::spar::parameters<Ps...>, CT>
{
    typedef srs::spar::parameters<Ps...>
        static_parameters_type;
    typedef static_proj_wrapper_base
        <
            static_parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(static_parameters_type())
    {}

    proj_wrapper(static_parameters_type const& s_params)
        : base_t(s_params)
    {}
};


// projection class implements transparent forward/inverse projection interface
template <typename Proj, typename CT>
class projection
    : private proj_wrapper<Proj, CT>
{
    typedef proj_wrapper<Proj, CT> base_t;

public:
    projection()
    {}

    template <typename Params>
    explicit projection(Params const& params)
        : base_t(params)
    {}

    /// Forward projection, from Latitude-Longitude to Cartesian
    template <typename LL, typename XY>
    inline bool forward(LL const& ll, XY& xy) const
    {
        BOOST_GEOMETRY_STATIC_ASSERT(
            (projections::detail::same_tags<LL, XY>::value),
            "Not supported combination of Geometries.",
            LL, XY);

        concepts::check_concepts_and_equal_dimensions<LL const, XY>();

        return projections::detail::project_geometry
                <
                    LL,
                    projections::detail::forward_point_projection_policy
                >::apply(ll, xy, base_t::proj());
    }

    /// Inverse projection, from Cartesian to Latitude-Longitude
    template <typename XY, typename LL>
    inline bool inverse(XY const& xy, LL& ll) const
    {
        BOOST_GEOMETRY_STATIC_ASSERT(
            (projections::detail::same_tags<XY, LL>::value),
            "Not supported combination of Geometries.",
            XY, LL);

        concepts::check_concepts_and_equal_dimensions<XY const, LL>();

        return projections::detail::project_geometry
                <
                    XY,
                    projections::detail::inverse_point_projection_policy
                >::apply(xy, ll, base_t::proj());
    }
};

} // namespace projections


namespace srs
{

    
/*!
    \brief Representation of projection
    \details Either dynamic or static projection representation
    \ingroup projection
    \tparam Parameters default dynamic tag or static projection parameters
    \tparam CT calculation type used internally
*/
template
<
    typename Parameters = srs::dynamic,
    typename CT = double
>
class projection
    : public projections::projection<Parameters, CT>
{
    typedef projections::projection<Parameters, CT> base_t;

public:
    projection()
    {}

    projection(Parameters const& parameters)
        : base_t(parameters)
    {}

    /*!
    \ingroup projection
    \brief Initializes a projection as a string, using the format with + and =
    \details The projection can be initialized with a string (with the same format as the PROJ4 package) for
      convenient initialization from, for example, the command line
    \par Example
        <tt>srs::proj4("+proj=labrd +ellps=intl +lon_0=46d26'13.95E +lat_0=18d54S +azi=18d54 +k_0=.9995 +x_0=400000 +y_0=800000")</tt>
        for the Madagascar projection.
    */
    template
    <
        typename DynamicParameters,
        std::enable_if_t
            <
                projections::dynamic_parameters<DynamicParameters>::is_specialized,
                int
            > = 0
    >
    projection(DynamicParameters const& dynamic_parameters)
        : base_t(dynamic_parameters)
    {}
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_PROJECTION_HPP

/* projection.hpp
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
*/