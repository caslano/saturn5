// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP

#include <stddef.h>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Redudant later.
struct no_rescale_policy
{
    static bool const enabled = false;

    // We don't rescale but return the reference of the input
    template <std::size_t Dimension, typename Value>
    inline Value const& apply(Value const& value) const
    {
        return value;
    }
};

} // namespace detail
#endif


// Implement meta-functions for this policy
template <typename Point>
struct robust_point_type<Point, detail::no_rescale_policy>
{
    // The point itself
    typedef Point type;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP

/* no_rescale_policy.hpp
v7NeTOSRQjq+t0yR4kM2kqE+TBTcLLJ7ktx5hSe/VqfNZd7YR4+CxvUYc9STF6brihD0tO/a3o+pFCI9HPqE3NCYusSpzT68vs7Ae5lLW7049LXwlJdioEXrlZ8n+pLn24oXQ33Zoz28vz4n3ProvLtevva+LPTyBD9Y6RvNxROiLqRrxWDhoCXWuBOkA3nyzRYnIjEDHK3DMTjcRqM+nOE1KLJz4hJKdwEtE203jjV7nWmzzis+vNw6JNrULl7M9MLyPO8tT7mYyWItXwmElVXmzHY3Hv8v4DS27TZq8jGauz5cMavWX8addnHp1GQxI8C2nj5kzoV0qdGbHxe2y4DW4S02HcTx3jzTw2ts+qxKf0ddXpsuBYOwk3bEbSE4GUEpWCIZEI8VQD732GrjjvVwHg+XJZCaNHfsesltlNIhmmQrMdqolqnXcspncFqoaYYcfJshU+xoe4hbpXk5GKiNll36nLFe8HaI6aeMuheqqUykmDF92KUfkleU2DfKpYsCYKAljDLucjFR4KwVOofYYdPJMmDovwmHB++WOZ8jhozOFcNJsU8CvU37BaNvEEZGBTRj+ul+OvYMTD/VT8degOkrHvo4p8cd6D46vCZ4jie3OvR2uyUidYh2INuBk8fi9P7GDKJxiEhw8mxVj51+XIJ09T7aOLJhXeVaD33/qITcneSRg0H2uj5312UY2tSH4fXSSd9ptZsyB6SnNWuLjcEsUcHljp1U5xJLGnvRwXLAasaS3uNgcQlHu5mepDlqlw8LRq/RbrX3RWXkPn2FBycgulwHnT6FLQj/jo9CE5s9Kd43Muow6mJR7tnZTlN4jUf5MnZvHBbe6RpLc8fBNlFGwfLE9FyC5uCQHzMNDO0vY/ggOzkG1YQg/PAa8GPmubK/DNbYvOzBjN3THr+XPBg0i1Xfi36MVd9dW72Y2PoOrQFv1veCvwxWXUKXZ0tHhmQ+hX6MGvuMGd1hYZQtSQpi3jM4GI5xyHyS1pxWL1uozb7GHNzRj1HrCtuSvJi2DmI+Pa5luh8HZQZuT2LmQsS3ugs45Wfeo3YZ7Rc8EnzuudePm17GNlUclcMXo62xK55yRJY9evejTTr5IKyZ/zUenNhZibESnXu2qU09ZVVr5DSdy/nyncNBLo60o/yh8+IGtM7/tMPTfcnElCEviMfy+f11PBgoZeNaJ/OV70RsX6oYYP40o8I4YrTllVhckGng76atqcDlsLHR+HgQzStPnZXOUdD5zvh4oSpi9xg1IufbjccCxvbkFU++KhS/GMbyYE/gdRm68Xjdj4u6TqfisbxX3OHFmHVapP6Jxdp1Smz34ITLljkwgScZ7uvPZk94OiSoz7d4MfNjUWcKlzXCXo7DKm1/adGwCXjaSOukGM+ECwfgzD3WUQ+O9VfGzcTg1GEIzbPkRhtXzUZSk/TUnS49kr40/q30bgT2BLdZH849c+SyX91gYe0XBgxb8hU/Di3GsmZlpxcz1zJ1Gm/ZbBvRpT4MtyadB8VgMDKxi+Fyj8TjiNcFZy4E0dRWOyb2K7nWj1M7J8Zd9OPUksy4YatsKkIxZcu4EWe94UjGImvG7fXyI22Ax78XxxtAarsdXpy1Zu7y8pL5CWZsR43H8fmTNz+2XXXddmhzP1nz0YvjCpItzIPjfmLcFaPsHIWa2FH5L2/w4Xitu2jy4YjXWI0pPFiCsBu82M6jCcrl6+70YfVcZ9+ZC16eXhkCoA/LssGSId56sXwgG+nOOJxVrw7x3erDk7xgvdGbP8sMWvNj8ye1e4Z8AzbEYa326tBcGTbwExMw/muHBrb5nt5iYaIrL7PNnkLyXmlrPy6C8PpdGLIxwh6rfWc=
*/