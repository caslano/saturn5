// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_STATIC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_STATIC_HPP

#if defined(_MSC_VER)
// For CRTP, *this is acceptable in constructor -> turn warning off
#pragma warning( disable : 4355 )
#endif // defined(_MSC_VER)


#include <string>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/projections/impl/pj_fwd.hpp>
#include <boost/geometry/srs/projections/impl/pj_inv.hpp>


namespace boost { namespace geometry { namespace projections
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Prj, typename CSTag, typename SP, typename CT, typename P>
struct static_projection_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this projection or coordinate system.",
        Prj, CSTag, SP, CT, P);
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(PROJ, P_SPHXXX) \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_sphere_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_f<P_SPHXXX<CT, P>, P> type; \
}; \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_spheroid_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_f<P_SPHXXX<CT, P>, P> type; \
}; \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(PROJ, P_SPHXXX) \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_sphere_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHXXX<CT, P>, P> type; \
}; \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_spheroid_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHXXX<CT, P>, P> type; \
}; \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(PROJ, P_SPHERE, P_SPHEROID) \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_sphere_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHERE<CT, P>, P> type; \
}; \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_spheroid_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHEROID<CT, P>, P> type; \
}; \

template <typename P>
struct static_wrapper_b
{
    inline explicit static_wrapper_b(P const& par)
        : m_par(par)
    {}

    std::string name() const { return m_par.id.name; }

    P const& params() const { return m_par; }

    P& mutable_params() { return m_par; }

protected:
    P m_par;
};

// Forward
template <typename Prj, typename P>
struct static_wrapper_f
    : public static_wrapper_b<P>
    , public Prj
{
public:
    template <typename Params>
    inline static_wrapper_f(Params const& params, P const& par)
        : static_wrapper_b<P>(par)
        , Prj(params, this->m_par) // prj can modify parameters
    {}

    template <typename LL, typename XY>
    inline bool forward(LL const& lp, XY& xy) const
    {
        try
        {
            pj_fwd(*this, this->m_par, lp, xy);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    template <typename XY, typename LL>
    inline bool inverse(XY const&, LL&) const
    {
        BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
            "This projection is not invertable.",
            Prj);
        return false;
    }
};

// Forward/inverse
template <typename Prj, typename P>
struct static_wrapper_fi
    : public static_wrapper_f<Prj, P>
{
public:
    template <typename Params>
    inline static_wrapper_fi(Params const& params, P const& par)
        : static_wrapper_f<Prj, P>(params, par)
    {}

    template <typename XY, typename LL>
    inline bool inverse(XY const& xy, LL& lp) const
    {
        try
        {
            pj_inv(*this, this->m_par, xy, lp);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections


#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_STATIC_HPP

/* base_static.hpp
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
*/