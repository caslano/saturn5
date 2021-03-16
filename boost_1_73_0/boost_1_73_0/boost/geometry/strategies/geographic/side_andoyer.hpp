// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP


#include <boost/geometry/strategies/geographic/side.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation
 */
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class andoyer
    : public side::geographic<strategy::andoyer, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::andoyer, Spheroid, CalculationType> base_t;

public:
    andoyer()
    {}

    explicit andoyer(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP

/* side_andoyer.hpp
Mb5ForMj0cx7G+z/RdGnl8GhrLZDf0u+byftdm3dr19Jf6AyLvhGo34VQXIsPTbWNzzE4dnG92+p7YB9rL2j7X9Zuxr4pqosf9NCLS1KQwH5Ugp+tMiHLaUVZhg0TUITSZNMkgIV9E2apjXSpmmSUgoOFhBnuiiuM34MMogOoAi666g/xXVcC+goyoyOrq6zOruAH6Mrrq4f6Aoje865993cl6RFGPL7te/lvHfvPfd8/M85972853TXAnTkm80=
*/