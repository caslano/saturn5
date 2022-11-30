// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_DYNAMIC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_DYNAMIC_HPP

#include <string>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry { namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
    \brief projection virtual base class
    \details class containing virtual methods
    \ingroup projection
    \tparam CT calculation type
    \tparam P parameters type
*/
template <typename CT, typename P>
class dynamic_wrapper_b
{
public :
    dynamic_wrapper_b(P const& par)
        : m_par(par)
    {}

    virtual ~dynamic_wrapper_b() {}

    /// Forward projection using lon / lat and x / y separately
    virtual void fwd(P const& par, CT const& lp_lon, CT const& lp_lat, CT& xy_x, CT& xy_y) const = 0;

    /// Inverse projection using x / y and lon / lat
    virtual void inv(P const& par, CT const& xy_x, CT const& xy_y, CT& lp_lon, CT& lp_lat) const = 0;

    /// Forward projection, from Latitude-Longitude to Cartesian
    template <typename LL, typename XY>
    inline bool forward(LL const& lp, XY& xy) const
    {
        try
        {
            pj_fwd(*this, m_par, lp, xy);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    /// Inverse projection, from Cartesian to Latitude-Longitude
    template <typename LL, typename XY>
    inline bool inverse(XY const& xy, LL& lp) const
    {
        try
        {
            pj_inv(*this, m_par, xy, lp);
            return true;
        }
        catch (projection_not_invertible_exception &)
        {
            BOOST_RETHROW
        }
        catch (...)
        {
            return false;
        }
    }

    /// Returns name of projection
    std::string name() const { return m_par.id.name; }

    /// Returns parameters of projection
    P const& params() const { return m_par; }

    /// Returns mutable parameters of projection
    P& mutable_params() { return m_par; }

protected:
    P m_par;
};

// Forward
template <typename Prj, typename CT, typename P>
class dynamic_wrapper_f
    : public dynamic_wrapper_b<CT, P>
    , protected Prj
{
    typedef dynamic_wrapper_b<CT, P> base_t;

public:
    template <typename Params>
    dynamic_wrapper_f(Params const& params, P const& par)
        : base_t(par)
        , Prj(params, this->m_par) // prj can modify parameters
    {}

    template <typename Params, typename P3>
    dynamic_wrapper_f(Params const& params, P const& par, P3 const& p3)
        : base_t(par)
        , Prj(params, this->m_par, p3) // prj can modify parameters
    {}

    virtual void fwd(P const& par, CT const& lp_lon, CT const& lp_lat, CT& xy_x, CT& xy_y) const
    {
        prj().fwd(par, lp_lon, lp_lat, xy_x, xy_y);
    }

    virtual void inv(P const& , CT const& , CT const& , CT& , CT& ) const
    {
        BOOST_THROW_EXCEPTION(projection_not_invertible_exception(this->name()));
    }

protected:
    Prj const& prj() const { return *this; }
};

// Forward/inverse
template <typename Prj, typename CT, typename P>
class dynamic_wrapper_fi : public dynamic_wrapper_f<Prj, CT, P>
{
    typedef dynamic_wrapper_f<Prj, CT, P> base_t;

public:
    template <typename Params>
    dynamic_wrapper_fi(Params const& params, P const& par)
        : base_t(params, par)
    {}

    template <typename Params, typename P3>
    dynamic_wrapper_fi(Params const& params, P const& par, P3 const& p3)
        : base_t(params, par, p3)
    {}
    
    virtual void inv(P const& par, CT const& xy_x, CT const& xy_y, CT& lp_lon, CT& lp_lat) const
    {
        this->prj().inv(par, xy_x, xy_y, lp_lon, lp_lat);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_DYNAMIC_HPP

/* base_dynamic.hpp
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
*/