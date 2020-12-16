// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP


#include <boost/geometry/algorithms/detail/intersection/interface.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Box1, typename Box2, bool Reverse
>
struct intersection
    <
        Box1, Box2,
        box_tag, box_tag,
        Reverse
    > : public detail::intersection::intersection_box_box
            <
                0, geometry::dimension<Box1>::value
            >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP

/* box_box.hpp
s93bfC7AaC+lw/YGWLhXciHAeC+kwy+y+OBw/46BwXg/5N4A532NDn9SgMd7G5+s4LjIJ8rzYDXO81MYU/NMmJ5nxuL9n08Dbh6ax6BRrFR6cQ1nznPZKFP82Ic40mU6HpQpn9UjXWiP+5R/g4N0obcxWG5qXv499/jJOKtTVnV5FtnF7hPmsuZ+OsbRU/Pe2CB8XBcujvDwDrTnxbi5TCC4m/GaUAe5H5bvjY/jAcNEw3ujVzbnzqI8cG6Oy+FFjpd0C7xXOcbivcovDvCwLr40wOK9yq8I8Lh9vojbryl4UqwFjhT4rZ0QH5LnSF8bYyYo6xbiVjmRNrczXTfGdd0YV3RjTNeNcdaNy/1S4JUGyrk+V8HZEjzmhJfPpsdnZ1Hqud/2s21MvxfgaStav6UABemAZv73BG2a+n01z1THjTdbW2zZj5tfx2pby/vZTn85JsHoYpR9OG6JNxPkvYV/XkK4OaQEQvRuy1tP0vACnuXjNNYuI05DppH3DiSbX2zCVfL7fM6vKNvL4jZNx8BSZy3eqfDmJwvVGjr/xhzn8V0RLz4/8u6YQ9cz0AGSZrqVqYrCbCK+98Q8U0SooHTQfXVTHumXvlfivTG3sre53fg4yV2q3ZjnzNY0vrAP7szmVXGzeQbOc4SV2fmq1StTpjuBYsx7f8xraDb9gMoLbZpd7uE7BF1NeWE+rog5aLB8Bom/ayXPftrW6BSPTPODYXzcBuTZtpDDeqtp8ac+2VVLJzzalK0P161sTlhflqocqiu6bcgmME6idJN8NWS+9HQS74H/fv+Iw1K+6KutfPtA1Afwd0bImZHvtn48jaXa8CcCnC5qgq074vTjuujP2cUcukC8MFkNbMS8VF1kzmcCjoyH8/RZ5sg6yHsbGY/e73iIPxfF5y5dvJsYC85cruZ0JR50oOm6eV3Mje7k+JzGwQRZxnO9xsEkWXJuiDl087tcG9Y4bHtdZ+Wc4GdVDm4OoKJIzLAym2sm18n7R+B5O3xe4VHBcx3/gufwOU+n05dSWKNJuXw54sbl8tWIE5fL1yJOXC63RJy4XL6hcbhcdJ2jctFsoJeLztXL5VsRj8slbovUd5hOjf3AEqe4YzkFMX6PWyE7bBn5Tsfa8XtgPjc7UVbmczep36U/tGnv3DIovpO4rv1I4PhWNt/S3iY/jjGf56X8De440T7xn3F4ui1b2OoOxtAG+Nvkl5Dv2HJWYaKBzr+42+S1V/aHl6HfSu7esYZARQzWmX6N8CaMuVBH1s/1h7O8sGV0sG+k/8xC//adhdOH/T0Dr19lOOEd9L85ie5JdiYc20ZZcfjvIjz8Lv9DhPNbOdlp0Bs5Lo4/Rzhd+NPud4+ptLGv73b1u+cvrny29o9u6t25dfA8rjN/cxikgEDgNvJPgZkK04MHr+fEusLdKm7e4xkeGhDztP9k8lA7BG/R6ize3IK8e+hekke3HCVMWbcOkhxUSiJwWveOcFZdzhHuE/FYdVknNx2p8Yq1edzRkNc3P4NpTrz+9tvIN39f6PToZbSu8dg21mpM/PFazR/UtZrP2W9VhGhL/3ht4U8t4t+Q9KGHIk8N24ee18Ye6CRNOpKh+I//prYHTptC8v0idG6dxkN7Hht6vWsZ+ePPb6NvN3oVe9X9C4FOS9I6IVQ7fcFM1ro+qkfzdJKAie0XI4+3Qn4M8F1t5bFemS3PKGsOBx7XzO4Uqmdjt63PS1bT+1PrwHl8W+lnlfshTfNOZa7Ke3vXd6jyDRtV+bpNOn9DT6+T09tGyfwJsSDdWA62rIMXQW7mSUaZtAxRRDIoEclMlC6dp0BG8x+Ehj1iOdht+KFg98rUXu29gKOP0+Y=
*/