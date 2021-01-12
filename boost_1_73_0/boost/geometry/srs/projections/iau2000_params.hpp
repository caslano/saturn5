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
RDI432O/Ww4/z2O/Ww1f7rF/Xwg/y2P/vgh+hs/+DT8vWbl9XAefBSf/4bZ8rX3+RfAjHE75Wv++g/DpDr8ZXmv8G+G/TwjulO+tBP4W4d/n1r/Pw58Ob6iK+TlrYvvQD+CXOXwMbsbn++BDDr8LbvLvfvigw5eeL+rfnGTwO1gl/8wPwG+C1wv+qdXi/NQjk3zfv5xPOy8ujV3wBxy+FW5iczn8+w7/MNzG76ik+D7p5PZx
*/