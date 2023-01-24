// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

namespace boost { namespace geometry
{

// Meta-function to typedef a robust point type for a policy
template <typename Point, typename Policy>
struct robust_point_type
{
    // By default, the point itself is the robust type
    typedef Point type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

/* robust_point_type.hpp
0nulx3er7Vb49JbiykGRYglju58PHN7YqUxkTKVj43BZ/dm4gJ5MiYx/PNa4bigV/JwS+PMC9YJwPiUguAel5DUnllcX80o2l3h82gcmgDZVctTtcpxAf+DvOXx/xcI5I3r6/qCG/snCJvV16DzXjTM5nqx0paSECZjcvvILjnoVtcQyRZ+TtuE2lcIi7GQ3YoMfLS003M/nNXKNInVZUfJKUB2+uQwoFXyWRmXICoLFm44cQ7Pkg8DOS0Zdt0A//08j0P4YeDT6FZ3Wt1r8ogo2ei3R2iRDgl7rBKHan3nZhiy9/ME+IleUBD1dmErSjmy9EsHySOpIWehNH9TwVtDJkLiRGpHckHTQz9BJ0JpwNiRnpGbEa/Vut6XB5sEf39IHRffI99iPiNoQigr02gcDyqf125pxLlTd8LBMF4m90T3Sdywl1tkZhYvOhNoo6W/wQAy6gVfeH2vglw3TwnkeEJ9v3jo0CWinV3nC+KfnZBQLeolKxn+5WDLpnN0xFCRCbwbdLRKgowbrWsZLoDxY+j7dJIr1inRsV6C+QPZZbj25VpIjzusUoGod6uBhPOXNZmGSmcJeRyAn0aNkePtrPpITJVFM6IPjxjLupex7JdEPxTPtiGUFAkSLPvuJJ7XX/n4tm5TXpZ8GChMTyMoVF31fpPI0sTHLva2zzdvbfBRwZZ0SoZ2sjFGzbsUyOb2eUrwvjSiFdS3a
*/