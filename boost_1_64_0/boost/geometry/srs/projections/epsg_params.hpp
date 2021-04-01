// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct epsg
{
    explicit epsg(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_epsg
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP

/* epsg_params.hpp
kOMdNu5DCRx1pTN6hczMo9YzebOBm3ZU2TYIiKNlSLMZmiu0XWTBXNERNQv7vZR9IQ90UHyp3NopUux6N7LROtC+7x7Yp2uX21iLuNBu1afYCEraGibWxBBvY2wEhLEy4GNO634EeaD8ONz65KjQ0ccQx3OzNRNr+ro2LyeDgzvyEuK/m+sHHmslemBZsMdnJeeh7Zi11KmEKeQBP0pCuvxSsmacU33JdRH55a/1iiUZoHUsMXXwjsJdzesxzWna1f6H0fyvmIVVnHj/z9xnHm6orSIvkg9wu0+xv29Ci6oTbrh0K7nKraf5I+E4uX2Ua3G9Sj96JEsCeyrGoZcvZlQOcdPyWqYspFnU5ulDHED/7QcPcfQzXXgOUfrz+p7gPGyuASy9MrmQEdNjQcUJ16v+Ly2zd5MaPw6zrSvh690N8n/9b/edPwKZVoijj04oMJLwyyGABHsF9oPPq6kWrt2w2aHkVkgWu6/M1ehtozpd9YoEZj25imVxrjab4w6XgGO7Zfw+TpexDcvxdGCSui9QK0dDcAGyw/ZtRozfaFUnPIANH0FRUyD4Uw==
*/