// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/azimuth.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template
<
    typename CalculationType = void
>
class cartesian
{};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<cartesian_tag, CalculationType>
{
    typedef strategy::azimuth::cartesian<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

/* azimuth.hpp
za0fbSSg3waFiVUtELSVQrN9iS3ShwmxfQxrQpTSNi3r1XPAEuGbscvYX15U1MPWxWbcyUx7nZHck+xLijZ2H1Vmw0U0II7v/hUmOcMFGiZkHmPNsfBSKSbm9PurkQJhZB/XQKTFECakRb7n4CHIPDpM5Q635yxJFEm0j1hSmwaQtXBwVCnnA8/FbosNTTn85wGeZPpzkkdR/ieCFLy6wzzQIK+ILIlnkY4aJQ+2a2nsBnFXGTbIaFZrlN+onyu1Ggy5gILvIkfjBQuaUa5qP2SisAsa4o5vt2WN2yuNYknoyhXutmuom5jiDp09LtZhM6XKCB45Kuq2PA99xoLSktus8XsndKwKfdNoBmJI1VlYVe6U+SWVI7pnH8vh5E8tONHHaG2X/wOdHNKgqApIrb3/qDm1H1BLAwQKAAAACAAtZ0pSIhX0cygEAAC/CgAAGAAJAGN1cmwtbWFzdGVyL2xpYi9zdHJkdXAuY1VUBQABtkgkYM1VXW/bNhR996+4TYHazlS77dPaZMWCZluDFUmQjxUBAgi0dBVxk0SBpOy4y/77ziWl2O265SUFpiAWRZ77fe7lfPfxnhHt0oNPGv5TPHgHiVNrfufMfx2dpncU/yB1jfdDRua0EblLp/SwyB1NgkjaW9mXdZo+
*/