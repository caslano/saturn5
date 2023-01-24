// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP


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
class thomas
    : public side::geographic<strategy::thomas, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::thomas, Spheroid, CalculationType> base_t;

public:
    thomas()
    {}

    explicit thomas(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP

/* side_thomas.hpp
auc+1aeO3nu63hbpuiKbK1p04N80Z0v9VeiB60j2wn6AGyOF2T3WkkndlkuJTp3e93An4GOX3OtrRVOfg3zGdDBKP3Qw947v+4ytoB5M3U8Mp0fr7RBXxMn3xXfLEaeEdZIutmv+iHad1pU4Nvl4H5UpDaYzfavnn00IZtwlm7RP3wveJ++6sceh6QuZgVbHE9x38OpfVePtJzwSX4p0YC/Jr8ZJxhqLmqY7nfxHCzvLJbtmj7U3e/E2tu6fi1+eHT0O3MxATdVqQq3BSpZ5ZmtKCdTSntySh28PygrPQ6F1N8EGZQuO/AgiPuGKCL92D7tPeW39imPcHrIG/f5C2FkFxaFkYRi5hAsECO4eJGgS3CEECG7B3d1dhsGCBHd3d4fAIENwgru7TXAdGBhmrWq3aqW2TvVLv52Hrq6v+u/z5WxKHUEwVqUMSecUnj7UxQemMplgvHT9kftMAUh/ye1Bz37+g2eziH4IgNdTOJPdcBr4XVm23n6paK720UYZpDUuezMDAd8KzVvW9eCNaNAl4BL6+Jt0CpylDk7Z8BfPcfusfKJF7+rCed2ydT56R2ihJHZn4KE35aooyPndt1IVwPDd2iMrSApNRXaW/9zsZIW4LdvHaOLcNDvTOthtQ4GlPZJrbWCx8Ym08FvTtZcdESjb0SzWgWNtJJ2/BuzPsgZebMCuyeNt9l+JAcQ37p2yuIkGhBAyaarq
*/