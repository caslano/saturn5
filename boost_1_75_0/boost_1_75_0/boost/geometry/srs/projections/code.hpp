// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_CODE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CODE_HPP


#include <algorithm>

#include <boost/geometry/srs/projections/dpar.hpp>


namespace boost { namespace geometry { namespace projections
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

    struct code_element
    {
        int code;
        srs::dpar::parameters<> parameters;
    };

    struct code_element_less
    {
        inline bool operator()(code_element const& l, code_element const& r) const
        {
            return l.code < r.code;
        }
    };

    template<typename RandIt>
    inline RandIt binary_find_code_element(RandIt first, RandIt last, int code)
    {
        code_element_less comp;
        code_element value;
        value.code = code;
        first = std::lower_bound(first, last, value, comp);
        return first != last && !comp(value, *first) ? first : last;
    }

}
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections

#endif

/* code.hpp
U0TCrA0dIVe31VcS0gsyYlaBeWdXnj3OPTCr2xdTKSoH8MeDBNXnVGxps3lMqh8E/C537YRyKK+obs508z9khqd7LQajvYiPsS+lvqbEE4YMNSRjslOFObJjxSc8fhqS3RMSwEogSJH4ycyVSVIWTiGH7xW+IFtHyP6GPb+ms2NqfiHzlVXCUGa4yPT3cvAkHFqKSB8mmeqru/ClL+77LKb8bfIlmEwudvuxRH3LitJ+7XJ9RkfA1Lp7VOQroZK14IBMH6bWkIIXz7b58N6XV5OvbJkoaEQIM96DpIIAXAFx6ntSI1x0qaKG6awTNgSq0Ot5k/H4ztQYCY49zn2q3Z3MTHYiR20zJvtmhHdUlhO2gh3euFGJig2FYejJlnbvzUKSUcz5hsHbg35uZcM7BuFXhNQGinNpWfmnEWwryglq6eLiy/k1ZxWU1GHvsJifRO2ZXfneMmcsvYuHds8tl99u4EnIpA37W7om8NcWVw7QOC6/OTcv+00UdxKT8p8TlNQe8HjXWpzhZKnS/S7YwXzw/X4r4b5GbbeXQ4pWbt5UPHuqQs3yGbzUO21Q967j9bwrXmuFn8r91SesEnThXLaIEBYg9TJ4uihoSBoyWyui/RUL3X3eAJ3nzGsF7k+Wst9IC0ZHWmObZ2eWPmCm3cemiFX2jrgJTe1z3fa8/L6bt2ZnaSoXNw4GGOnvAaZNxgtr57OO5sdNzau5
*/