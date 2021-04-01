// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/comparable_distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of comparable_distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_comparable_distance_result
    : comparable_distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP

/* default_comparable_distance_result.hpp
WVsFVScvGv45EPzf6KaReCKM6F9Ly18sef2f12ByT/tJc2RlYtzB8AYM8fVLTgG7nH+iMDv5NTefOqCIHdWJR5YAaIFSZakIeNkKx677cB0canQ/7GSo7DEza2tVQo9rFaFPt3tZC6t3xIcUU8LQLIoXKWob5kQgmrFDAqQMcSe6R+W1U2+gtPIzFaRghkb2EwBrRG1ORGTrhYWpfhWpPVKuiC3+yKYoKW1aBUyYd6urwyMSIH5bBL/YI9w8q4qjLPiIoJOtoXEqE2xvcfLC8vrMz1cRdLTWRUVFfK98kJycxNZYEPrhpfXDwgUSuUvwa9sGXWkXZZv+4Rio1tPbFFZ76zAv1KMBs+e+VVyIG/N4i9mpIKRz+QAG50RjWjLnw+B7vcNpRBgX3zVsuqZfMPhY1H5OijTazm37VG+aeF4X854xrzGPwUahd6xbX2M/XGdWEz08AxAhtoDbxApeT/A2y6sCBJtZ3aZZW/ZqHCPFIYa3piJdpsTpHEMaULflPrL1DVifCsbmfLZC3Q2MCEvyuzwWXeN2bh2D+JKM2IUVQm8SWXbBgptETA==
*/