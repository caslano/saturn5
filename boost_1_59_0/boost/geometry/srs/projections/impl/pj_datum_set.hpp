// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
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
            // TODO: Implemnt as BOOST_GEOMETRY_STATIC_ASSERT instead
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

template <typename T, typename ...Ps>
inline const pj_datums_type<T>* pj_datum_find_datum(srs::spar::parameters<Ps...> const& params)
{
    return pj_datum_find_datum_static
        <
            srs::spar::parameters<Ps...>
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
    int N = geometry::tuples::size<Params>::value
>
struct pj_datum_find_nadgrids_static
{
    static void apply(Params const& params, srs::detail::nadgrids & out)
    {
        out = geometry::tuples::get<I>(params);
    }
};
template <typename Params, int N>
struct pj_datum_find_nadgrids_static<Params, N, N>
{
    static void apply(Params const& , srs::detail::nadgrids & )
    {}
};

template <typename ...Ps>
inline bool pj_datum_find_nadgrids(srs::spar::parameters<Ps...> const& params,
                                   srs::detail::nadgrids & out)
{
    pj_datum_find_nadgrids_static
        <
            srs::spar::parameters<Ps...>
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
    int N = geometry::tuples::size<Params>::value
>
struct pj_datum_find_towgs84_static
{
    template <typename T>
    static void apply(Params const& params, srs::detail::towgs84<T> & out)
    {
        typename geometry::tuples::element<I, Params>::type const&
            towgs84 = geometry::tuples::get<I>(params);

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

template <typename T, typename ...Ps>
inline bool pj_datum_find_towgs84(srs::spar::parameters<Ps...> const& params,
                                  srs::detail::towgs84<T> & out)
{
    pj_datum_find_towgs84_static
        <
            srs::spar::parameters<Ps...>
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