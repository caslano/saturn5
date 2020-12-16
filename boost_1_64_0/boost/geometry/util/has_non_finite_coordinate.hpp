// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct is_not_finite
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return ! boost::math::isfinite(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_non_finite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::is_not_finite,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

/* has_non_finite_coordinate.hpp
VHxzjQQV42MFvVDmwFDfVjmg/UGd9I1ggNpA80DvEt88oA/SN+wLQi8Bukx9hxRuAJ0Duk1839E3xULQv0BfFPWCr0Wg5bX6bBy/v0bMLFOD+WysI7+NUO/dtnuP+m9cjnrx3sV3Sc33bo+9/H5lMBgMBoPBYDBOFERC/pcmWVtmlpT+62n/Pxb5f3e85rNnD4kiHTzZytqSPdss17rvRzn1JIcqoV6tNuPkfrE14slvsrqzdMMry4+mNfQvTWpc+1J/aV96amhxVf8zD3/79eJ3jiS8t3xt+LJzQ8n+4eoijse+1FOjcaTxrW53uYL0831Bxbj3B60EDVjnfi+th09r3i/ce/zydlBZu6ZOvE59eC1r3x+T3jtY/EQxy90MBoPBYDAYDAaj0fL/wwWggWIAjkUH0L3dUR+AVNIBNCP/w6akA4gxUV79AB0AJdUnPUDwXkr2+QBEV9MDVPddf43qvoD6tjvKo21wB/+6qVbJgceiI+Wd26bbZf0JIev/b9n+xydJ2/8R45Re28rOKZn70qWPTNtzOHz9hdALdNNobGnMi2gthUQNID2AmAMDNa//Jo0HjVNRNT3CePIV8IB2Jx+ALWSzz95Xw2YfEf1BOLZ6Pz1BWDkWpqMty1C2o7T4jfUFDAaDwWAwGAzGfx2RWP8/J9dqJ/N/xOX+Qe3+v7n/qkgmXf6bkt+2o0RXIH6rIrhfeRr2U651aTt2YXtmRWTs38cjv4YjuxZVsLzKYDAYDAaDwWAwGOEgEvZ/e4HTYuR4ZIR9Y8UATEMMwCCywV9ENvhoamNzlNOTIGtWenMAoBUWGO8t/pxahE1+jJXWBNSC4z9nh39J2uHnL5x2S/ORH7yy9FDVwLz9qU3D10WQXZ36GH0TxK7eRqVA0tqCijGJA/WuX5Cyv/Ht6hn7TRHRTUzcz7oJBoPBYDAYDAaDceIhEvJ/Hk6y2HVDl3mh658DUMj3ye00n499DMn3ZxL/yShXQo7dEtXcT753eCyKkZwcyPeWPLnkvPKxPwbZXpzzg5SNPQWmT88z0sfMb/nD0J+6FPXyyrpUH/GhVZN148mHvB3lmUvQVG7fKsiGXQ+wfMhgMBgMBoPBYDAYjMZFJPL/ITB+gmVcrt1//f+oesj+Hf1i+6N9sf0AxfYPSMK9SfYXVn2PYXUbeS6Ljw9NO2abfgJKfCch99uuu2LEiq1P3DP5jspN+zO3bvDK/VQX8VBd7m9FNu7TKOY8huR+AzL/Apb7GQwGg8FgMBgMBoPxD+EkFGcDy/92PdOal2NYcnLhUg9p3O7IteTKZew9QiNQL31Aa8QC9G8N3+ubRwy7aagFHuJ1r90vjr+MZHBBDluG91LxA/3ij/oXTA8SP7C2I/zZ96g1BAIa5nI7nEamt3115hBM0lrEivyB2VahN7DcoC4bZuS6rVl6tVyCCabgfKwLxofHZnX62Kg7l6GXj/xa+BhOfMwkPgbSfOmnqTUVt+zxi6eQMRQOa47jTt1SywTQjmHteq8upp8p/HUCrpO6mxaTu278sWrVJNOknab53Zt+h7Xp5DoKX9zdLKvZc7N33zLnzftfeXNNOtohzz+jZMqKjjNv/GSN5d4BzX5yXhc6jiJ4/EPoOI1nJP+zipJ2bi/qMD2j45O9U1J+qQwV7xE6rmORXE/CPsDx8+8/5rScuDJt8KaH477RtM1y/9LDFbaCzk2d/VKXXLB7/a9VodeNcEp+RiRPLbVPPrDirplXt9mc9Ndh7JfnFw+ZdOmey/pcf/DtzklFsacsDhUHEn7cS6j4E5Mcx56Xmxctf2LIxrM+eL7F5Pj2PTTto06y/0c75v+2svTZkpK1LdcWT0fcxrk=
*/