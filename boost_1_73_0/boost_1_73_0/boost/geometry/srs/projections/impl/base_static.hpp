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
0u7oeZKF4qzX6fSuO71mQ2fLP6Pjwejw0+FEbAmMN4zonCEp7U35qyXz4qGhLHHQ7O34uOoOTFyA5shs4dl4kX+PwJ21Qn8LOA/Z5BS6940ISKszNZJBiCSWp+FBomWK4dC9hpzZub9GEdLkj4wn5tyCQzNA/c/CvnBjiItpL/hfNn4amK32IKcxoEQiPKrtRbDyyXV0HiwjSpRC8BlCEpllFlpiS+sdCcWa+dMuAA3vEV9xSLlN1GUfqBW+4Y/dXgBTbfcQvEsIF6AcOlM31Hlh6+Q6Il6Rk/rYmdt3aP4CypHdjRiFxkcXW/9GdKBbm4ZCTxyrAUf7G9YDvSsSzx50DmLx1t8ev6Xj/Nvjd5pBsKuFTZJRbuFeQCs+/S3HKO77bl3fknm/Xdf326K+acz1MB/g5Bx5ORDtkLVdMyTbjK3yi6Q4cYIAqXokGvSUEsBJdzPnIQrA/64/4X6qbrywo1tQiZmDeWKHcB7gJpyyXEW2MVvFKMsrEUCb8jO5H6IcyX1fXupIvpbLZRBdKyCzWPKUTUc3+tSvwmVActAjPlD/xfiCT7IxWTYPlBPQ0GhFsF4ow9BpQD7nXAGSGSFCZpqYJY90Bnm3j+3J7XMl6Fd7GAohoJKJYJ/+fhu422Vpju1UuqcOloCF
*/