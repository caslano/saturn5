// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP

#include <algorithm>

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename MultiPoint>
struct is_simple_multipoint
{
    template <typename Strategy>
    static inline bool apply(MultiPoint const& multipoint, Strategy const&)
    {
        typedef typename Strategy::cs_tag cs_tag;
        typedef geometry::less
            <
                typename point_type<MultiPoint>::type,
                -1,
                cs_tag
            > less_type;

        if (boost::empty(multipoint))
        {
            return true;
        }

        MultiPoint mp(multipoint);
        std::sort(boost::begin(mp), boost::end(mp), less_type());

        simplicity_failure_policy policy;
        return !detail::is_valid::has_duplicates
            <
                MultiPoint, closed, cs_tag
            >::apply(mp, policy);
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A MultiPoint is simple if no two Points in the MultiPoint are equal
// (have identical coordinate values in X and Y)
//
// Reference: OGC 06-103r4 (6.1.5)
template <typename MultiPoint>
struct is_simple<MultiPoint, multi_point_tag>
    : detail::is_simple::is_simple_multipoint<MultiPoint>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP

/* multipoint.hpp
faenEU5t2L8lwmc0EovXazwf1KCw8SKSrOy2kWLdYSuaqjuJ67rz+B51xxybCOvG4aFuZNmmiRPsnd5FYXRrYbp9xEZE+TROpVEX0vkbu1tw4ABiG0UHx48wjt+pcHAHZGQbpzPOxiHy+FLCles7OY8vI468vtPLP4Mx0i99mnzcl3uc0+2K4rriTeVn6J2q2TilMnF8Hs5kDpWe3sjzabyCcJIPWjrLD12gjptzUBD0dyDNxjF9CChi7uOsiEMNiVtWJZD7yohvPlnF2Tn0+Qo4rw44SVRGlSPLqHPUMr425OyxjK+P+LKMOofLyO3wbOIE+1rf6MNsXOEHjBBmpzE7eG2IwpPZbP4cx2Gb5zugGIvinceYbc4oo8hPfhILTOhCnaWmJ9JEnnfhA4aOxuEdfu0HcelaksmcT4P7O34XX+NR9fAe/Jjj5fk368FJ/Ufqmn3c95NvgCJmvQdujx+KOI2pYJ97Btf2M10ccWCpAr+EcV4VtmvmlwJ7wiHwKR6FcWaL5yfou2+x6Nu/92Lt/PxlVNfucj3YANdz2vrSBoEqQhyJFQs7Kh76a4iVKwEaYCZ3DuF2QW9FQYUYhXaEYVAZAn2dbl1Ob0plvxFfDMPRkYfvQm450OJ1TF7nypNS9twUKxgx4LMctF5vVK3u56Q6MHP+2nr6HFkHvP+c6mDL6OAGOplU3cVvIMyPMO9DLG4pP9oZtnmLdR+Wz+eVEnPr2faSO2/0deTxRNjjD4y+WpxX2rWjNllF8z51V5UuhIhs8gBVH980ut9RosgUM/Wjv2XzcO9ejywP+n0wB6nt4ibIOmn94PCGoc2bN8g792V4bnWpbm/BcHn/jsQzbxZ9T2KZN4u+H2CUqLtX8DfAzjZ9gWkTdlxwlw17tgi7F2FXI6xLhP3T8haJsIcs7+ki7NEriPcCEbYIYTc/DnvHRNhiy5sjwpYg7OqMjGWWt12EHW/DnmvCWuzTZrAgeSpGzuOlmnaHxGJtDmYL5KQLmRs2bz5hyxBd8YUEZD+1DRz3srTF+M0Q6IdE5rDkV9tN/bro41Y4nJI2U04u7ooQi87c/AhpA6RBhgj/wn70zczm5Tbw/aY8JJw0xl5SLNCen1Os3n/odOzOeyAOPmkmKf/tPRVcfGtWb8utHRzODWwaHd6mnqV/scKTZ+nHYlw9Sz8e86J16YmYE82P7gg46/tH1ofnx18S4eHZz8kI5+w2lxHuG6hGeDwXXFvB6+e0lyGc25iOcEqj1e+KawfmkcK4D1sX9edaO0Dc8H1Ni/MBAPOIOtE6m3Oa4xwd+WN7t9lObb6t8pr8qN/Rjep3o3Opzcua4Q25YC8k2BFGZ1Uc/jJRP8MDWzefMLA2mMt/eYxTBbZ4Tt2WBxsetPKMqOU52OUZs8nZ8rxiRRaDjy/3S0dxUd728mr+aPdMqHl9pctPvjGTzeubXV4qhaRaGieYv7WMZ9YNXm3T1Mr32ixGd6PymIrTjOq68VTCeCUKcyfow/04bkUWRypt3HWd6m8mVUa9Hvk8Y+o36w1OZv8oxgKrt4wO8L7mxU5PCofmsmj1XHLfOhsXHZDknjsbtx7uS3h7xKV5GZqvE/sBm/Aq9Pni/YA6j2Y/RHrvjnnmRYVI7vk6z8nlOwwtL183c4o9pqaCsfwFCu7U7M9daxxSL5+ZVjmkVpeXi5hDk/WUG5+Xiz3OurZyeC2wR3IoARf/kiC+LArL+JjOgQjm7BfLICOV56BX8D680W1DdsGT6/siwsMqUtYoPqHyeE/5J61vugjcBda/vNyGLRdhX0DYdY/BXoy9OexKG3b4Xhx2tQ3bT4R9xYZ9R6T3dRv2B5NeOz6s+WU8xag=
*/