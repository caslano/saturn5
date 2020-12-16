// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::densify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP

/* densify.hpp
464h6kkKZO3VfwY0WyNehNrZJxFI6nh/v+t6R39/e32bHmh7uXv2eCT/IEdPHQc6GoWeWx7CqCRxO+utoDCcnfuxcqTwxi5mzjfN61jR6SGy0tLa5492zVP1hC8veadV5JKw2SV3DIazoy+qF4a3ct01GGHklqOGUzZ5ai/VIXOiVdfq0wgmjGiLbOqxyTjR2LHUY+kp6rCWDN36xM9iv5aAcnTRsHafpKSkq5LODOTeOMURz6vzZ9FNn9G/kkpo13m0QtfZMUfYEdHNjrCWCRt92OHsSSLhcyVX7wjrSwqb4QhbsJ63HqKnlslRzzlldsSMpIh+V8RXOWJXFfF4R0R/UsRMV8Rfc8RfnSER36dfc4LNRPyvP2yQcn7adUnSrF1JY6U+l6jmsCKlgLaPL+0R/YEZ2Zpf5aB7O7nB1p1+2hS53jpCSn/Et0+D8DkGnypTipAtV8MxhKJ7PxT9zCSXz5wy/hD4EmMhb1MSKRJZ8jchD79a7PF8MnHNQxpHrbZc7RiAcCc6rU306uMlmpGxj5Xk87jy8Sb53K18fEk+DconI8lngfLxJ/mcqXwyk3xOuubQcvuHNR6DCfHgVa5DmbLN+xJNX2+y0Ay6LZVmMGCy81S3tKzhVoK8agi9dbJgjBFQ/YUWbJXVRXZjdC69Dr3JhDU4ZW1Y7rrtvKXzcqsSCArKtmIhj+Dqip8BJS23Sg6r6i11zmXZl3AY6ltERYfuQqHVJXXBlLfCFsutsEGXj6V93KKxuwvizOn6pqS773pLc2UC0U6UtFhEG11AV6SePn6+PILEV70d8l9Xqv7E75/hpVttt5h7AWxGKj2gj+HzZhEqLLK9YZzz+uy1U8xlfCcaqRK9bh1Yxi+WWT3FvNO3y7mn+xY1NdGRJHfqPsX2pVu2d3xaeXB589euQPkcKqJ3mVtEOpU6L8ER3w3mGpw/09tDI2QR0J1XSos0PSj2090y565bmV1S6GqSOEuSDdHIqiVMp4nTKHKig5y1coHyVqUuJBjfHl6pVsG5V1vgBzS0+iiqDmfFAurJe+Q7SccKc2Vt0i5OScvjoifKfy1GDJ6mRXuHnMtHuThNK4d0O1dp59QMbpFAzKoe79zvEYbwtmW8kwqT5LlNJI9Ab63L19yzf4N5/T+s43mwXJC3WVQwjV1iePRnmvXgri/KrgKuYDrPLgeoonhC41mh8fdrmEad5aJxh6JxAg4VxTpLDtZRq1Lyook33CxZ0PZ5b8rI+27E/UfVzgMIIt+wwi1QV+R0c3MKiktaHpD5wu6rDZ9DGsiHEzzKwd0yipxNQgiLEMs4+JojNENFMLVA65Yo16xt7VChHCKxs3XMcMqY4cSYEROzD3dVYRpitTjCnfSe4IWsOZWQhbB0AemaMnM+s04aici/mVpSPy1qmVSZ7CWXF+LGckOr0tCqaJ9WXfu0qjACmXVZpdFBV1XGo5GjlAtfoGXJSrmbUlhI88KXkSWvpOXn8jr7XiXj/pAJrnEfPdmCg6eDXSCTlGUnJdK/IdMQ1FiJ5mIcysmBm4fWgtb4CYaHf7tpXx/P2Cp7Oa3ZVJDIRD+7sisq/+4rLaWE5wfjk8W0b6agroosljVzV/fJeUliLD3lNvCQK1f+QcbasEtKay0PRsDmLbJk1udgMqQ9mijDDFPkfIkyLFouUQrcUXB+qyZLTmv5sWtuLv8PJlz+bzwKEjx2jxQRxjpPzSTaeJVKabzCzLcauS+IfnOsPefiOoCrcagiBxytI/3DDwmFKQ4KYaZwdiKFcCIF7inUDkVJy6NCJl5rKfHD7mN5wvm5zeo6vn5kjmn0xa/o+V7P0818r8rb3nxvTThpvgd+9cZT3PM=
*/