// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_EPSG_HPP
#define BOOST_GEOMETRY_SRS_EPSG_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/epsg.hpp>
#include <boost/geometry/srs/projections/epsg_params.hpp>
#include <boost/geometry/srs/projections/epsg_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::epsg>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::epsg const& params)
    {
        return projections::detail::epsg_to_parameters(params.code);
    }
};

template <int Code, typename CT>
class proj_wrapper<srs::static_epsg<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::epsg_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::epsg_traits<Code> epsg_traits;

    typedef proj_wrapper
        <
            typename epsg_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(epsg_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_epsg<Code> const&)
        : base_t(epsg_traits::parameters())
    {}
};

} // namespace projections


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_EPSG_HPP

/* epsg.hpp
9fdXIibevc9ov/lAMURdhumK6rU79Kum6hNlU8K1l/35pIYrERY1+x/vooQjm/w6wpn3PMpAlNuLeXRUF293XkEkoSST7xncs/WkJp5kqGgFRL0fIJa+Rq8AXzR5JhIarPsdnBUWiUZl0HXJRkjnCX0bx++fRlFvsna5BnapHVEoColT5iyXlHJsUGKjTBQzWjLv5r34IdtczpsJEPgXdGPKCYXKFQ8Kyu7bcyi02OCrJhIpUxcIUYiNbfagFQA8DsA4yIBZiObuCiPf6fQsi/hjPxGPOLw1Y+hGXigQfAEXCMIdCIWRtITCWiQvpPWMlxN9Js3qgB2o5JZHwwNTJH+Rr9XXD+nG9SB9TlyYPr+xM8xEebIJvu4jeKI4vWN8ZdmlCOTdZenrwiQ77sYWDuwOoeyL37ke9AjvZ+hWJZN89ttjHns2EHkG7BP/2uZiLXitvhUaq4fPlR6l+l9SGgxN3DEWR4v1Ov6FA7/+Emv4pEqgSFLUv3nnGlevV6uP8o/bAF6QYVB68WH2oa6znIADqazKowJXPOmB8lsx9nR23amOaqAUxlrEZBX2T6p+XyT7ZIeGprgtf78etsNbMG7YEfUKRYBcc6TqHn5K0X7pUZOhAxdudHbEum7iiaE4xWW5+5Ii1xH2KXvA+wUIysLmKwyR2EXQLvdM47bMngD4j0P9qOyKuGy4dEm9ki3glsBU6FWoHWMOHumY
*/