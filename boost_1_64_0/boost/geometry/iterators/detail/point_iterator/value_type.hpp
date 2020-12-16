// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template <typename Geometry>
struct value_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename geometry::point_type<Geometry>::type,
            typename geometry::point_type<Geometry>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

/* value_type.hpp
/wI2wMed89rnUt9YYXc9p3efywvSnHi/EJpxl7Czjm378Bzn/tG631s/DlG6GaF29xh4OhwHB8PxcCg8Cw7XsdIx3y4Tp+MR6U46HglbwVHQ7tOq+/J87jsLex3g2XAgHKv7doT0zQ9+oPu8++nNUHqdpXbbbNgH1ql+nKd0Ox9eDC+Cl8CL4TK4AK6ApfBqWA6/AhcrX9fCe1VPPih3H4EV8DFYCZ+Gl8BX4RL4NqyC78r+W3B1SN/04CLlh2Mj6UX+6I5/j4c9YD94IpwOT4IlsBe8CfaGt8NT4ZPwdPg+HAC74uZAWAiHRO6HQ+F5MBdeoGOV0/p+Rdj5lNPT05xyegbsC4thNpwDJ8P50IlXfUeCXXziNaR47QI7wo7QbWfl6L7rdZ+3nfVPvQ8dVDv2Q7VvUlOccGkFF8LW8ErYFq5xjq37++X+Kh/3p6U47s+AA2Cx2h0z4TQ4C9bBubARzoOfc46Vv/T9BN7gk7/WYK8XXCf3b4Jj4M16/lthCfyW3N1k872+K8C2pp11+Pvb7jmM9dqLrmbfNUz6jf77N+5d6b9+e58bUz9dwz0Ja7iPJFz91nEvujH1f2It90/3cwx2Lfdy4tVvPfd7Hk+8pnvTjalHvK77nscPb233Nbi9CbMLsw+Tvi411AeTj1mAWYPZjtmDOYDpeVNqaCRmPmYlZgNmB2Yfpu1XU0M5mCJMLeYWzE7MXkz611JD2ZgCTDlmNWYL5hnMAUxnOsgHYIowTZj1mO2YPZgD6z9de/7Tv0//Pv379C+Zf8lc/5/Fm0tgZAOAj7X+fw/W/z850+lETw1VhxsqlpbXR1yuddb+L+eaxqCylnH8OKBukfWMaExHukcKZ5QsitwaOswxt+Pl7urU+HlEPXC3OOouI1s1fSgiwNTlmhqWeNZYo64dzbyahqZQdEz/InNvVnT8pznuYtf6v9Mct9F62HZOjF0j5KvmegcdM57dHLf32Oc5PHpXm+t9E7uvddjs/CZzfRzhdH7H1pxfjJ0KTCXmEsySiDmsMW6tOt48QOvr1dXZOdOECe9iJkxixhF/kObcfJO+S1ypPR32xoY1nksctu8bu70Utu69J1q/9x9o/K51xGP3ctDYUN1zkl3b/6A5ruN9rXVsnHjGImcYdytCg/g/YqefjYfoGnA9jZ2pxFynuOdRWJtwrlb41mCWHnrso0mzfmHbJXZek/wZO79iVyuNJVH6vk3pe8NAb5h7E7Zv2BPWugfVTprXea85LiAfE25al3jYILO2fcK0nWOut8INjq39HuTrVM89PIon7B8zOqvpc0wx82JC6YRjK2cd0ow2w9tntJ/GxIvM9tntF7JGbee2micUF9aEc/xzKe5eNxrnN49bO4f1PXN9dJw/zfoamgd4qfLRJUeQf4YNOnT+cedVjGwTm3++gOkdWZNkkI1LHtpZW6GeSbiVS2tKKukEayc/M35Ucene09fG5TZzXMJYgNYe+4ts+Nw8KDo2dqq9/0QbR9vN8YWhc5Q/+vBclISRCfU27n9r7Jxgy7W0wSqnrP0Gx740dxv72TqWfc9+nPWZjmmQaTysMHfCuI0zz8Mcj7THi2LGFGerspmLOV68phN1zmBveNuR2Z5wW2j9MM/YPVvh7t7bxa7/tc4ce8NsYUyYVZvrnWyYfc4ct7VzTy+T35swy4/Y/wtj1gx8pm38unkDeKZtjn8ZPl3H4NYhdu2VVsavnLVlhOxqTTy7ZpZnTvzd5nr3wx5n28o8JxrN1tWY0i42biZGnhe7u88wz2ryQWlV1ULGB7vTZWPiR88r+yfFzZFVXaHr3exewfvM8Rhq91bmnu5OPqkNeeqBV4ydobjazhk=
*/