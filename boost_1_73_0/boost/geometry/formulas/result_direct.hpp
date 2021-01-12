// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_direct
{
    result_direct()
        : lon2(0)
        , lat2(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T lon2;
    T lat2;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP

/* result_direct.hpp
n/+E1fG68BbHNNghYomXzYtiWa7DepAcr6AX/1lcTncT1iHkeA1dVo3HdrgF62TZ+PVAjOVmsQd/m18/CBvncycC8wSbQNIFp6a6Yjp42HcRSVfwoQOOsedgIcR+KTxa3KuSza8phd1acaITxgXMlVjgrFnidwSwQ6Qsa7/42GE73OPnVGEP1i/HOnjch/MmSbdlzl7cK4l6oGbpJF35/g0/Y7rf+FpD2GWzc8bitxdxjdBK
*/