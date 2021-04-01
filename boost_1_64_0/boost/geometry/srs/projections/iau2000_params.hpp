// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct iau2000
{
    explicit iau2000(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_iau2000
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP

/* iau2000_params.hpp
9NmOtSgCXinuvbH/hw3iGOCP/naIgb1UYoS72+TTNxpBhpfLgwDSsGr69K2aza/lVAoCSRBzdeyU3sRRCkbajkvR16E1zMOa2NSIs5uKRurM5rtqZTj4zxHdG2snOS/3AH2xvlzdG6g66ZnYRMdvh3agnn9C8qsYLWNNZm/kfKVtKQg05ou3qIip+XVOxGYTxR+UTHN335zVgKUga4LzQpEvTMpFcLaLui1gjEygnQMqSlhMKlsopNy6IOpz4zZrFWB4t2q6aXpi3S6Wl+MNBrQG94+MDQudRkOJtoFSIMYK5z78vsRwTA7Ln0kxMNNYlSbyq+oDn6SXgfGUt/zk/zQeHQvGJxUBd1CRkV5jt/sYtYjT6jJMcmhpF4Ck2X+kNgZq2nxiMjSNfge8p1T3hvzu4zMOEyQ+TndHywlpySS+Rsmc4YFef33jk8GrI2LP4QI5BKxbFJH1B3s5DpX2e5NN9nBg71xtSZyK0BXIrILbs6iHxYV7l2GM41F/2RZ3dBz+UZ8lpcbE9h73AeQUVsJX9Cae0C2Xge+ea79SDwGx0z+yONpNP5C4RQ==
*/