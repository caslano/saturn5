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
ydp7Uz2djTQ1VTZhy7NlI+7r7uqxz88x8k2p7SqXzDuPFHKdQ6H8qDJ5Yzq9tSV6TIdXO5nrx+HwOsFF0YRsrstEmR5tWU9Tpj21JdUePTPPyDtTvT3Nmda29igvj9FyGfdjY1lKyo8z8nSqN9PT2Lk+Fcnnl8lTrameOD+Pl4ze2shPMHJ670xzY3dj74ay/DlxCi7zZ0E5V+kpe/6kKbh8/mTJu9vok1q6+5ra25qd8j3F
*/