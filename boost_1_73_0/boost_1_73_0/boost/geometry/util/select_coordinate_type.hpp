// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function selecting the most precise coordinate type
        of two geometries
    \ingroup utility
 */
template <typename T1, typename T2 = void, typename T3 = void>
struct select_coordinate_type
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type,
            typename coordinate_type<T3>::type
        >::type type;
};

template <typename T1, typename T2>
struct select_coordinate_type<T1, T2, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type
        >::type type;
};

template <typename T1>
struct select_coordinate_type<T1, void, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type
        >::type type;
};

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP

/* select_coordinate_type.hpp
RbJAXwNzUdhgkDEtoy4EsSyZ0h2/JZMiJCXwbYKXDMgNEhXFk5IM7FL3+iPpOQXysZY2hickG+3rKi1LBpGdgl1+AohmnGQjDT92UbBSaFkKkedd936upjlcDFSpwgLLO0UWLW2kkGDWySd4LmSmFuFiDf/C4pcI7t5HgRo6vtOz4z9HJ51hJxq86Vx03a+d4+PuYBANAIBOu96Npq72XtJc9vYOwzGW2ZpRLFvcfPXiebnYJ1sH5Ijmt3VcT6X+Mr4CaNmo5uadxqNRMremQps0KZuh1alF79wUrtJGlZPJJtU2eG2oHiOxTWujsiEiYy/hXBvk5GdvXBjEJ2acX3tQGGJjqQP86SK/TN4//bAPBwMXAdsdbtzsWbUZ24sSqUUvqX6znbb8BhTuOMEW6BUwvFpZP8n1hKW6TadjoNzHyki1CrmYgD4yoF08wkTXjsZlvtCr0R+dl0aEbwZH+K9fhTEz3HcvS8s0nqb/EvEIbMuJaBeIMiuIDQIaKra84L5h29H2Gdgq3AWgIIWqQjNhWMitIl4KNhS5Zq/xQcCopjCJCG+Yfik2kMG4M91FOaEVwyQl7YseAjYYSFUo9/hSqLX3Eun8I+hxDL8civQ1xsrw93xJNt1cyCdCbdIs4uGgJM0OldsszbAV
*/