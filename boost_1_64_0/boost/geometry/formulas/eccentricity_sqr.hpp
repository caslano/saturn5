// Boost.Geometry

// Copyright (c) 2016, 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP
#define BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct eccentricity_sqr
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // 1 - (b / a)^2
        return ResultType(1) - math::sqr(ResultType(get_radius<2>(geometry))
                                       / ResultType(get_radius<0>(geometry)));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType eccentricity_sqr(Geometry const& geometry)
{
    return formula_dispatch::eccentricity_sqr<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

/* eccentricity_sqr.hpp
lMOfYrkXZho8YalV5aE1G7DNaM3rsCBa8yasGZ2Ad51tVXHy1Fy4jLZCaxZhY2hNHzaJHoPfPseqytG2XKs6D4ucn2nwM1gUrfn6c+lHtOb52LNozWLMujwTUi7sVHQM2s+zqlHKkwd/jR2kXvbzyQ/LOo8YWE5MYntJo9lxEe2ADl9sVR8poZzoUKlVvWcDsUGeTnjlRuqg84e5l9G+ug3huWWkQfvh+/mf1ZV9ED88gj2ln7uJcYSFea7mq1gLWnPPh6gXWnMIewqt+VVsAq35MJZFffM247+CMaXzd1nVRzEP5dFcVU48oDVLsQjaVsFYw5rJx19tVR90W1W11nAIC6HjcBw7lRjW7KmxKgda836sFK1qraods6IT8CUPscoY0fyQl75AazZgr6A1Q9iJtOEEPOMqq8pBh+CjddSdNI4txEYDZaZesaBVDTZaVR3jV/MXWBCtmbGVNkKXw3gTfXQBeptVWa7lGWg//DkWpp1tO6zqPuywLie0XEd9uTcCn8A2oyfg0x+xKhv3hq4nfkKUWfc7PICVkmYMvvcG4pY21CzAnkJrRrFJtOYB7ET6QrPmRuqITsD+mxhrpJmAAzup7/nkCX9/M/lTzrxdVvVjLKjLfAtxglVfgL+ZNt7NnIY/BLfvoX91+3+MvsNyyUez6jbmSrTmNsyj84fX3U4/omPwh1gHddG0hykPWvOD2EG05j3Ys2jNb3ycdkBr/gzL0fPGHVb1O8xGnGhedqdVLUBrbsby0WOadzEWdL/A72Ae2kHz0Rb6Dq35G6wDPXa3Vb39HuZS0k/Auz9NLDF2EvBbe6kX2navlW9KlA1dDhs/Q/ugNc+PEDNozWLsTrRmExZFa96MxXU+rdQLW7iSZ8GMdtYvreEbOqzKj7bD5VgZ2gnrsUJ0CH4Gc6Jj8DEsDz0GX8E8aFsneWPl6DxY0kX/oSNwcw9xqOvVa1WX9lM+/HFoGSBW0Zofx6JozW4srvOHhweJK7R/yKo+hmWvyjR4ZYznoTW/jRWhNX+NVaM1z/0sz0LH4IrP0bbkoxnFxtGa38KspLF93qp+ie1B2x+0qquxCHoP7MFiOh943Ne4H+2Al2LD6HL4tq+zrun0MI6dmE99YetDxDD+UfgC9ix6At76DcqD3gcf2s+YQmd9k/7FDqPDcM4BykY+dujHmtE74ae+RWyjn4KeEcYReg+84WHKho7DEx+hbdFL4dXYU+gQXPht5lJ0GbwWUwWkhz/CstBLD9Ln2H70YbjoO7Qtejn0Y3vRIXgXdid6L9yP7UMn4M+xB9AvwrWPEp9oD2zBOtAdcBjrR8fhcY8RH+hT4Z+wOl2GBGMHs+sywOzvUkf0ArgOq0Zvhn1YNtr6Pdofs6Fz4XWPU19dHjj/EGMcbYdB7BA6AkexCfQ4XPJ95jF0PrwNm7+ae/9sVd/D7OgnXs+//8SKaLffwhNO4N8AoU+Cl2CHdHtCP5ZPPrPH7DF7zB6zx+wxe8we/03HPXfPM9gr/LLwe8JnhC8LbfeYXCDME14hDAh3CduEDwi/JxwXZnza5GnCpcJC4Sb4nzwS8vxh4aCwQ3iPMCzcJdzxbyr3bXvN55x5r/SL8DTxnyDnSpgn/kJhqbBSGBTGhAeF43v/PfVJHjnyvPnCpf/i52f8i/M/+V+c/xk7zPzPE5YIrxTuEt4p7BJ+WXhQ+IzwZeH86ySehEuFFwvLhDXC7cLbhBFhv/BB4UHhk8KXhK8Ij/+IPFf4PuF5wmJhudAvDAn3CDuE9wsfFT4jnBTarjd5ivAM4XJhkbBGuF24W7hX2C+MC58QPi98VXhyyOQSYb5ws9AnbBbuFQ4Kvyw8IPye8CfC54U=
*/