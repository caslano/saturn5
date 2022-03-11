// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTION_HPP
#define BOOST_GEOMETRY_SRS_PROJECTION_HPP


#include <string>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>

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

#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename G1, typename G2>
struct same_tags
{
    static const bool value = boost::is_same
        <
            typename geometry::tag<G1>::type,
            typename geometry::tag<G2>::type
        >::value;
};

template <typename CT>
struct promote_to_double
{
    typedef typename boost::mpl::if_c
        <
            boost::is_integral<CT>::value || boost::is_same<CT, float>::value,
            double, CT
        >::type type;
};

// Copy coordinates of dimensions >= MinDim
template <std::size_t MinDim, typename Point1, typename Point2>
inline void copy_higher_dimensions(Point1 const& point1, Point2 & point2)
{
    static const std::size_t dim1 = geometry::dimension<Point1>::value;
    static const std::size_t dim2 = geometry::dimension<Point2>::value;
    static const std::size_t lesser_dim = dim1 < dim2 ? dim1 : dim2;
    BOOST_MPL_ASSERT_MSG((lesser_dim >= MinDim),
                         THE_DIMENSION_OF_POINTS_IS_TOO_SMALL,
                         (Point1, Point2));

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
    BOOST_MPL_ASSERT_MSG((false),
                         UNKNOWN_PROJECTION_DEFINITION,
                         (Proj));
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
    template <typename Params>
    proj_wrapper(Params const& params,
                 typename boost::enable_if_c
                    <
                        dynamic_parameters<Params>::is_specialized
                    >::type * = 0)
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

template <BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename CT>
class proj_wrapper<srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>, CT>
    : public static_proj_wrapper_base<srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>, CT>
{
    typedef srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>
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
        BOOST_MPL_ASSERT_MSG((projections::detail::same_tags<LL, XY>::value),
                             NOT_SUPPORTED_COMBINATION_OF_GEOMETRIES,
                             (LL, XY));

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
        BOOST_MPL_ASSERT_MSG((projections::detail::same_tags<XY, LL>::value),
                             NOT_SUPPORTED_COMBINATION_OF_GEOMETRIES,
                             (XY, LL));

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
    template <typename DynamicParameters>
    projection(DynamicParameters const& dynamic_parameters,
               typename boost::enable_if_c
                <
                    projections::dynamic_parameters<DynamicParameters>::is_specialized
                >::type * = 0)
        : base_t(dynamic_parameters)
    {}
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_PROJECTION_HPP

/* projection.hpp
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
*/