// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
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
537Q2dnsdz+j7llZ9Zya9YCbOTV0VmvkeGj4AwPySzo1juWEHIhoXzH8keWbTAbkm/zQzVGR+Txaz5lI9bym94DX4QibZCyK9+MsbO54/9HI3PF+YYOrg/MjrJcF5EdcAxzLj6B98DGyk9uGOHKp7NvfJ/NXWD+Ss6CW6QPAX6ffnWcpEdV0PD67HMWYrwefE5538MXRpihiURvf6MG78yEKVfC3evAJ2wFa7wuPC5818gaApX79WNC3GfkOwJHs7QZOy30O+K6PBucHbQXeLz9oK/CdUW/892PCpixujtpSIC2lcUjB4/bH/cuQfJ9qNmL08oTEo9vJqvhKn/wMeNwoY+SE5e16ysBxn20D/uYQ8fVbonPH178h2jhayae7v4qdm7kDDxBtHRA/p2/91YXPEWmvmztHZH1d+ByRrb5lWQwBZcw8Im733joRQpDrx4dgQ/BZHtOs8/2eE619H2XEEz9vxCO/oNZcX2TxyG+zeOSX2N74y8Z+8yvNuIy98VcVv68Z9f7QeM/sG6rcjXqP6TmT8I79dezbZwPqXOJbPO69oLzxSOzNTN+bmL7fMfT9bjMuQ9/vKT1O0blO8Dvs8PwixZ9NMH9XzrSf0W4/UvX+mO2RAt/hpuiiB0b7jJ8GyU/vA8N78wWTFYG5/D/TOepzyoWjfh/GJp7L+4sQeqfSE4hxEU8OIz6/CqW3+6a+KR6Bud6/UfxeAX/WOQzgUyoCr3MiLPYdv5tdPxaayuefu8+ksDvW/ZLKoC6Yo2JxSfNrFy81033mFhemRZR8ZI5MviRCpOKcrRGbrtOANYY4ZxvX55WL9Fk1fYcQ9LO/Xdik3wGnc5yUjW0+xRQ+ATu0su8b/tbdg+GtXvW9l9/xmFrANxk3+ve3ZDGjSeiZ2v0PRv/6o9G//qT6163kH4HvbaZzW3BsOuUUNlDqjQFX9f5F8qv+vprPGaU4S/gb6PT3X56o2gIwQZN18FYgVnZpfYaqcfUCx97QBI7ex2yUuHHac9L3fACntzIl/O/gFZNwR8/pG9W7mbexdsK3UQvI2mevZrJn6BHwvdBSsVzpqQxC7WW1eM9hIngejJlnH9iPtMh2q1Plr/DGNART8sl6FnutbxE2cf9anqyafYsspvNo6EwRi58NlbVVm3gWZ+bKdxtamO+G0k/6YIOaI1Gn64OLlS6NSheaj8lvgQdO0NwUkzTLFE1TS+A3ThH9L9OZFz1Blnvx93uRe6Njjq+PCXvJfccjhXsAvk3NxXdg+jZZ/E+h6hoMGB9PXKqyyOiwWPxDLDOxw+IxkCzlQJjfQr2rHF8wCPEcM6cwlbZOX6zapJnJ2FbDu//8HA+CuWP8ipaA94lCfNu36tloDd9Nrjp2+HwD/Lnq7P4cV3950MHW5NBJwszvFNVruH6NgX87OVKJz9MXhBh+acTda1QrRGWaGA/9dSJd/0rIGovIrADMeCrhx7E0rjUiQrYMrvPPItjzTsWzpTL7XkcEj0q2VaBtjyBzBqcSkxgqNWwyUvTAVgN2LOI9c7sjYO+WemkE6XKDLhtPlYvu1p7qx3648lXoEiK4Oj8xBp9sZT55IhLuPevLPfMwbMRyaxr1uZnO/ae+oZ/1+IVXpvDnbz25LigzDp22qXH9PN5fQn4TTfSNA8Y782tavPPqndX4tLaF5lW/OSFRQsx7rIzPzek6DbD5vbcLjTn8LqqudTQW+sVvhwYH+90a9APpc0EL2wMY37vVMba7q3ruEahTvAtvc+7rEm90ul97x5uxssrZcP2urOK30z/u3NXfv72rezc+AYGvcg9095ASszD6HVlDn/vg2dTnvkqfDpp3GlrW6e/R6PtI5X5tFN8=
*/