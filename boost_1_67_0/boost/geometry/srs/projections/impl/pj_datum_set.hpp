// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_DATUM_SET_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_DATUM_SET_HPP


#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/pj_datums.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/spar.hpp>


namespace boost { namespace geometry { namespace projections {

namespace detail {


/* SEC_TO_RAD = Pi/180/3600 */
template <typename T>
inline T sec_to_rad() { return 4.84813681109535993589914102357e-6; }

/************************************************************************/
/*                        pj_datum_find_datum()                         */
/************************************************************************/

template <typename T>
inline const pj_datums_type<T>* pj_datum_find_datum(srs::detail::proj4_parameters const& params)
{
    std::string name = pj_get_param_s(params, "datum");
    if(! name.empty())
    {
        /* find the datum definition */
        const pj_datums_type<T>* pj_datums = pj_get_datums<T>().first;
        const int n = pj_get_datums<T>().second;
        int index = -1;
        for (int i = 0; i < n && index == -1; i++)
        {
            if(pj_datums[i].id == name)
            {
                index = i;
            }
        }

        if (index != -1)
        {
            return pj_datums + index;
        }
        else
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknown_ellp_param) );
        }
    }

    return NULL;
}

template <typename T>
inline const pj_datums_type<T>* pj_datum_find_datum(srs::dpar::parameters<T> const& params)
{
    typename srs::dpar::parameters<T>::const_iterator
        it = pj_param_find(params, srs::dpar::datum);
    
    if (it != params.end())
    {
        const pj_datums_type<T>* pj_datums = pj_get_datums<T>().first;
        const int n = pj_get_datums<T>().second;
        int i = it->template get_value<int>();
        if (i >= 0 && i < n)
        {
            return pj_datums + i;
        }
        else
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknown_ellp_param) );
        }
    }

    return NULL;
}

template
<
    typename Params,
    typename Param = typename geometry::tuples::find_if
        <
            Params,
            srs::spar::detail::is_param_tr<srs::spar::detail::datum_traits>::pred
        >::type,
    bool IsFound = geometry::tuples::is_found<Param>::value
>
struct pj_datum_find_datum_static
{
    template <typename T>
    static const pj_datums_type<T>* apply(Params const& )
    {
        const pj_datums_type<T>* pj_datums = pj_get_datums<T>().first;
        const int n = pj_get_datums<T>().second;
        const int i = srs::spar::detail::datum_traits<Param>::id;
        if (i >= 0 && i < n)
        {
            return pj_datums + i;
        }
        else
        {
            // TODO: Implemnt as MPL_ASSERT instead
            BOOST_THROW_EXCEPTION( projection_exception(error_unknown_ellp_param) );
        }
    }
};
template <typename Params, typename Param>
struct pj_datum_find_datum_static<Params, Param, false>
{
    template <typename T>
    static const pj_datums_type<T>* apply(Params const& )
    {
        return NULL;
    }
};

template <typename T, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline const pj_datums_type<T>* pj_datum_find_datum(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params)
{
    return pj_datum_find_datum_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>
        >::template apply<T>(params);
}

/************************************************************************/
/*                        pj_datum_find_nadgrids()                      */
/************************************************************************/

inline bool pj_datum_find_nadgrids(srs::detail::proj4_parameters const& params,
                                   srs::detail::nadgrids & out)
{
    std::string snadgrids = pj_get_param_s(params, "nadgrids");
    if (! snadgrids.empty())
    {
        for (std::string::size_type i = 0 ; i < snadgrids.size() ; )
        {
            std::string::size_type end = snadgrids.find(',', i);
            std::string name = snadgrids.substr(i, end - i);
                
            i = end;
            if (end != std::string::npos)
                ++i;

            if (! name.empty())
                out.push_back(name);
        }
    }

    return ! out.empty();
}

template <typename T>
inline bool pj_datum_find_nadgrids(srs::dpar::parameters<T> const& params,
                                   srs::detail::nadgrids & out)
{
    typename srs::dpar::parameters<T>::const_iterator
        it = pj_param_find(params, srs::dpar::nadgrids);
    if (it != params.end())
    {
        out = it->template get_value<srs::detail::nadgrids>();
    }
    
    return ! out.empty();
}

template
<
    typename Params,
    int I = geometry::tuples::find_index_if
        <
            Params,
            srs::spar::detail::is_param<srs::spar::nadgrids>::pred
        >::value,
    int N = boost::tuples::length<Params>::value
>
struct pj_datum_find_nadgrids_static
{
    static void apply(Params const& params, srs::detail::nadgrids & out)
    {
        out = boost::tuples::get<I>(params);
    }
};
template <typename Params, int N>
struct pj_datum_find_nadgrids_static<Params, N, N>
{
    static void apply(Params const& , srs::detail::nadgrids & )
    {}
};

template <BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_datum_find_nadgrids(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params,
                                   srs::detail::nadgrids & out)
{
    pj_datum_find_nadgrids_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>
        >::apply(params, out);

    return ! out.empty();
}

/************************************************************************/
/*                        pj_datum_find_towgs84()                       */
/************************************************************************/

template <typename T>
inline bool pj_datum_find_towgs84(srs::detail::proj4_parameters const& params,
                                  srs::detail::towgs84<T> & out)
{
    std::string towgs84 = pj_get_param_s(params, "towgs84");
    if(! towgs84.empty())
    {
        std::vector<std::string> parm;
        boost::split(parm, towgs84, boost::is_any_of(" ,"));

        std::size_t n = (std::min<std::size_t>)(parm.size(), 7);
        std::size_t z = n <= 3 ? 3 : 7;

        /* parse out the pvalues */
        for (std::size_t i = 0 ; i < n; ++i)
        {
            out.push_back(geometry::str_cast<T>(parm[i]));
        }
        for (std::size_t i = out.size() ; i < z; ++i)
        {
            out.push_back(T(0));
        }
    }

    return ! out.empty();
}

template <typename T>
inline bool pj_datum_find_towgs84(srs::dpar::parameters<T> const& params,
                                  srs::detail::towgs84<T> & out)
{
    typename srs::dpar::parameters<T>::const_iterator
        it = pj_param_find(params, srs::dpar::towgs84);
    
    if (it != params.end())
    {
        srs::detail::towgs84<T> const&
            towgs84 = it->template get_value<srs::detail::towgs84<T> >();

        std::size_t n = (std::min<std::size_t>)(towgs84.size(), 7u);
        std::size_t z = n <= 3 ? 3 : 7;

        for (std::size_t i = 0 ; i < n; ++i)
        {
            out.push_back(towgs84[i]);
        }
        for (std::size_t i = out.size() ; i < z; ++i)
        {
            out.push_back(T(0));
        }
    }

    return ! out.empty();
}

template
<
    typename Params,
    int I = geometry::tuples::find_index_if
        <
            Params,
            srs::spar::detail::is_param_t<srs::spar::towgs84>::pred
        >::value,
    int N = boost::tuples::length<Params>::value
>
struct pj_datum_find_towgs84_static
{
    template <typename T>
    static void apply(Params const& params, srs::detail::towgs84<T> & out)
    {
        typename boost::tuples::element<I, Params>::type const&
            towgs84 = boost::tuples::get<I>(params);

        std::size_t n = (std::min<std::size_t>)(towgs84.size(), 7u);
        std::size_t z = n <= 3 ? 3 : 7;

        for (std::size_t i = 0 ; i < n; ++i)
        {
            out.push_back(towgs84[i]);
        }
        for (std::size_t i = out.size() ; i < z; ++i)
        {
            out.push_back(T(0));
        }
    }
};
template <typename Params, int N>
struct pj_datum_find_towgs84_static<Params, N, N>
{
    template <typename T>
    static void apply(Params const& , srs::detail::towgs84<T> & )
    {}
};

template <typename T, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_datum_find_towgs84(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params,
                                  srs::detail::towgs84<T> & out)
{
    pj_datum_find_towgs84_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>
        >::apply(params, out);

    return ! out.empty();
}

/************************************************************************/
/*                        pj_datum_prepare_towgs84()                    */
/************************************************************************/

template <typename T>
inline bool pj_datum_prepare_towgs84(srs::detail::towgs84<T> & towgs84)
{
    if( towgs84.size() == 7
     && (towgs84[3] != 0.0
      || towgs84[4] != 0.0
      || towgs84[5] != 0.0
      || towgs84[6] != 0.0) )
    {
        static const T sec_to_rad = detail::sec_to_rad<T>();

        /* transform from arc seconds to radians */
        towgs84[3] *= sec_to_rad;
        towgs84[4] *= sec_to_rad;
        towgs84[5] *= sec_to_rad;
        /* transform from parts per million to scaling factor */
        towgs84[6] = (towgs84[6]/1000000.0) + 1;
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************************/
/*                            pj_datum_init()                           */
/************************************************************************/

// This function works differently than the original pj_datum_set().
// It doesn't push parameters defined in datum into params list.
// Instead it tries to use nadgrids and towgs84 and only then
// falls back to nadgrid or towgs84 defiend in datum parameter.
template <typename Params, typename T>
inline void pj_datum_init(Params const& params, parameters<T> & projdef)
{
    projdef.datum_type = datum_unknown;

    // Check for nadgrids parameter.
    if(pj_datum_find_nadgrids(params, projdef.nadgrids))
    {
        // NOTE: It's different than in the original proj4.
        // Nadgrids names are stored in projection definition.

        projdef.datum_type = datum_gridshift;
    }
    // Check for towgs84 parameter.
    else if(pj_datum_find_towgs84(params, projdef.datum_params))
    {
        if (pj_datum_prepare_towgs84(projdef.datum_params))
        {
            projdef.datum_type = datum_7param;
        }
        else
        {
            projdef.datum_type = datum_3param;
        }

        /* Note that pj_init() will later switch datum_type to
           PJD_WGS84 if shifts are all zero, and ellipsoid is WGS84 or GRS80 */
    }
    // Check for datum parameter.
    else
    {
        const pj_datums_type<T>* datum = pj_datum_find_datum<T>(params);
        if (datum != NULL)
        {
            if (! datum->nadgrids.empty())
            {
                projdef.nadgrids = datum->nadgrids;
                projdef.datum_type = datum_gridshift;
            }
            else if ( ! datum->towgs84.empty() )
            {
                projdef.datum_params = datum->towgs84;
                if (pj_datum_prepare_towgs84(projdef.datum_params))
                {
                    projdef.datum_type = datum_7param;
                }
                else
                {
                    projdef.datum_type = datum_3param;
                }
            }
        }
    }
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_DATUM_SET_HPP

/* pj_datum_set.hpp
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
*/