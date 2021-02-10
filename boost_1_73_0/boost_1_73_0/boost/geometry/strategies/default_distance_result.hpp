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

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_distance_result
    : distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

/* default_distance_result.hpp
VK6ItrshVzqLjQWHZcm2iKfQbbaNkDTpiRgGFe1Yeb45ox27eijM8gWQ8shW8tpqckR5IFBmKM0R1HSQbACHyJ9cNDkNCd5bmu1+MzCaNgNH/QTGyRHMpVMugpvx7Hx6PYOb/tVVfzK7hekv0J/csrEv48mQSq/ImQVcVRYdObegllWpMGt8fr8rbrWOlU7LOkM44uoJh76uesURL+TcTUKrGI6T/tnFSFxeTX+7fW4mAyaELvJDW0bzKI2yCDuBMRKT6UycXY8vZmI82cE43TKi/JUcsUDvTPpHexWto68deNM6xtIhNTDO3TmWVG1StcxOcmuWJwylU5TXOmUlux4MDcmFC+nkEln2wTYz2h2gioHybGleEtORCLwqSe0lzNeeiHJpaIq1MK/znISlviI8KF7H4LYHE0MyZglqAyXV7oVI6JvMri/HQzi7oHBYSHOkk6iMJUzcUmQ8bCj4Z4OCnLdJTXXarKB0a+hm0suotacnbaoYQhceeJBn+8GFtNClcPYiHEdJhrYhH4R2dedjaxvNy9I10aRGa2r4HAl0+eGV8XR5tBfLPhmg6PiuaBPxNvlPKoDSLFxolNTD4Em8HaisWa1D53Cos0YlFaYqV2loHzQRuoXSsuSW62kQDDq092h7oYQs42Ap
*/