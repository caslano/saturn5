// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
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
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/projections/impl/pj_fwd.hpp>
#include <boost/geometry/srs/projections/impl/pj_inv.hpp>

#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry { namespace projections
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Prj, typename CSTag, typename SP, typename CT, typename P>
struct static_projection_type
{
    BOOST_MPL_ASSERT_MSG((false),
        NOT_IMPLEMENTED_FOR_THIS_PROJECTION_OR_CSTAG,
        (Prj, CSTag));
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
        BOOST_MPL_ASSERT_MSG((false),
            PROJECTION_IS_NOT_INVERTABLE,
            (Prj));
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