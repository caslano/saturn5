// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_ELLIPTIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_ELLIPTIC_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/formulas/geographic.hpp>

#include <boost/geometry/strategies/spherical/intersection.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

template <typename Spheroid>
struct great_elliptic_segments_calc_policy
    : spherical_segments_calc_policy
{
    explicit great_elliptic_segments_calc_policy(Spheroid const& spheroid = Spheroid())
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename Point3d>
    Point from_cart3d(Point3d const& point_3d) const
    {
        return formula::cart3d_to_geo<Point>(point_3d, m_spheroid);
    }

    template <typename Point3d, typename Point>
    Point3d to_cart3d(Point const& point) const
    {
        return formula::geo_to_cart3d<Point3d>(point, m_spheroid);
    }

    // relate_xxx_calc_policy must live londer than plane because it contains
    // Spheroid object and plane keeps the reference to that object.
    template <typename Point3d>
    struct plane
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        // not normalized
        plane(Point3d const& p1, Point3d const& p2)
            : normal(cross_product(p1, p2))
        {}

        int side_value(Point3d const& pt) const
        {
            return formula::sph_side_value(normal, pt);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2) const
        {
            Point3d v1 = p1;
            detail::vec_normalize(v1);
            Point3d v2 = p2;
            detail::vec_normalize(v2);

            return dot_product(v1, v2);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2, bool & is_forward) const
        {
            coord_t const c0 = 0;

            Point3d v1 = p1;
            detail::vec_normalize(v1);
            Point3d v2 = p2;
            detail::vec_normalize(v2);

            is_forward = dot_product(normal, cross_product(v1, v2)) >= c0;
            return dot_product(v1, v2);
        }

        Point3d normal;
    };

    template <typename Point3d>
    plane<Point3d> get_plane(Point3d const& p1, Point3d const& p2) const
    {
        return plane<Point3d>(p1, p2);
    }

    template <typename Point3d>
    bool intersection_points(plane<Point3d> const& plane1,
                             plane<Point3d> const& plane2,
                             Point3d & ip1, Point3d & ip2) const
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        Point3d id = cross_product(plane1.normal, plane2.normal);
        // NOTE: the length should be greater than 0 at this point
        // NOTE: no need to normalize in this case

        ip1 = formula::projected_to_surface(id, m_spheroid);

        ip2 = ip1;
        multiply_value(ip2, coord_t(-1));

        return true;
    }

private:
    Spheroid m_spheroid;
};

template <typename Spheroid>
struct experimental_elliptic_segments_calc_policy
{
    explicit experimental_elliptic_segments_calc_policy(Spheroid const& spheroid = Spheroid())
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename Point3d>
    Point from_cart3d(Point3d const& point_3d) const
    {
        return formula::cart3d_to_geo<Point>(point_3d, m_spheroid);
    }

    template <typename Point3d, typename Point>
    Point3d to_cart3d(Point const& point) const
    {
        return formula::geo_to_cart3d<Point3d>(point, m_spheroid);
    }

    // relate_xxx_calc_policy must live londer than plane because it contains
    // Spheroid object and plane keeps the reference to that object.
    template <typename Point3d>
    struct plane
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        // not normalized
        plane(Point3d const& p1, Point3d const& p2, Spheroid const& spheroid)
            : m_spheroid(spheroid)
        {
            formula::experimental_elliptic_plane(p1, p2, origin, normal, m_spheroid);
        }

        int side_value(Point3d const& pt) const
        {
            return formula::elliptic_side_value(origin, normal, pt);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2) const
        {
            Point3d const v1 = normalized_vec(p1);
            Point3d const v2 = normalized_vec(p2);
            return dot_product(v1, v2);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2, bool & is_forward) const
        {
            coord_t const c0 = 0;

            Point3d const v1 = normalized_vec(p1);
            Point3d const v2 = normalized_vec(p2);
            
            is_forward = dot_product(normal, cross_product(v1, v2)) >= c0;
            return dot_product(v1, v2);
        }

        Point3d origin;
        Point3d normal;

    private:
        Point3d normalized_vec(Point3d const& p) const
        {
            Point3d v = p;
            subtract_point(v, origin);
            detail::vec_normalize(v);
            return v;
        }

        Spheroid const& m_spheroid;
    };

    template <typename Point3d>
    plane<Point3d> get_plane(Point3d const& p1, Point3d const& p2) const
    {
        return plane<Point3d>(p1, p2, m_spheroid);
    }

    template <typename Point3d>
    bool intersection_points(plane<Point3d> const& plane1,
                             plane<Point3d> const& plane2,
                             Point3d & ip1, Point3d & ip2) const
    {
        return formula::planes_spheroid_intersection(plane1.origin, plane1.normal,
                                                     plane2.origin, plane2.normal,
                                                     ip1, ip2, m_spheroid);
    }

private:
    Spheroid m_spheroid;
};


template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct great_elliptic_segments
    : ecef_segments
        <
            great_elliptic_segments_calc_policy<Spheroid>,
            CalculationType
        >
{};

template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct experimental_elliptic_segments
    : ecef_segments
        <
            experimental_elliptic_segments_calc_policy<Spheroid>,
            CalculationType
        >
{};


}} // namespace strategy::intersection

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_ELLIPTIC_HPP

/* intersection_elliptic.hpp
2o7UQx9pxGv+V9T/b/auyrBF1aWUnP1G/NGpGzL11eEeHUxmZgrSptu9yhdZFki4QGz+XJcbPsNkX+Gfp335C5XrMN/wAejyRTb2QMXyZepIsR4YUUNDC2V61HIVg5Gk4EKIg0cdUWNHEFJfxgbQO9u6geYwsXQIUnknHPYaWGEPObqwbTHr1T2Zq6HygUQqrNvrfgJP+SKhqEQMJv5RQmB0QrOimW6kG0+UdS1K+ZLE5vf1FxKYzADrOBmL1mjgHgETV0TXhlDxevh2CEmECHTxn4eDpma8nRlbzO5fAeDIA2SvzzR2+wtqcwGzvdw7LWxR2eYQDzhsXH/kMZXtIX8iavyUnxLHyr+qhW2jOdKY9e+QpO+lZAtpVAsWz9Xp2Uv9AtRoWULI4zZMegg0SMZMkaUsdf6okBe3z2NqwlHSVya0H8psxm8oOaL16kQsbCKBo4MWMiyBsbP5euDgLQ3s24JoZ0PCdlZcml5zv+DhwvdDyl0EYIJm5Rx+UIhDGCqMQa2zJurfJCl4r7Ec8OEMQyWyE4c4V2Tk5iPCXsqSWrtmXLAzuLyk+dhSGqLDVFUPepANvlchUG/YFNkJW6D6mpSumSVLMDN96uxsPInq1tIElZ6F/k8Ejs4MjlYQHXNi7P4HkUFuuCofbQ3JgMQKQkTDdp4htfLBXvkuW23x5LLDTSMaH8ovdebhR8d/qcSHbUSjGNiDfAfGliSMlBrIfFrgpwQ5Le1yaEWRoZFy/ZgJ5XQVTB0JS30fBKxm1UCC5JSLsS+WUqBsfiWRHDbzdUM0MkLXzNbbGVlwv7EmOzBmhD3BwtbrIhk16hYfR0Rb7W8WI7qDAQmCcvNE41mrz1WMGREUjq2TAR1aDca63QAOYIGV1iuBoRVhPaWlWY2qFWHK+mkaNXdYDPsIW4GTYYzomddPWZN2YHxV1eiVY5myl4KdqmdvFb0ZIj4DtRsKXIM9l/PCK6AVYSxKtvInLGzHotyKmon2oC855jkHfvxkVwQqatLcFIg6hYRjMeJblaGlkjmRffmelSc3TWDGalS4uBmWa8SWPFqvYD+WfBjsKoqGLolhWocNxiTg0KWVb5W6KAByr5QDUuTnaSp5YrUKKx2EICe7fQb3bMJSPJLlwPYNzhc08EtfCol15iO2yi27HbLWkwFxziEailWZO5lxVfP8aW5i6UA+MZM6l/IqPrtRMkVt0LXMh9AvYHWKG5IXLCYPz5gSNxPn7QeIGUEKtoV7yzpEdUZAeTJ3a0tW1hFs76LYolUi4ub1FWHIOwK0BOjHFaYMPuqCZaRviYO1Bd39mtPTNCBMQlCUEp9Z1Ll3D0anJPOKW7oeMVmLKrPtoYkAACz/05sS+SS2Y9ijQudOuyN2Am1GbjQZztBZS4LJP6f3C3z+sq7AJoqFhBuOXMZrvnuuJZnLoD2ST+FjnPhGbLB5d1iY+fMsnOpMhzKJFNgkSsq5gktj2i+CtUtoDINjHhMidmmgjUom6LhLsrLUpJFMIxVhkmLWIoARUT6JjRYryztbFfGulR/0je5fL9INi9+jSN/uuwENlhXIggcpB44G7kY2hlmRrA1JLP3I9d0+Z/qHYbWM9KKxqPmTOB0klRYm+zCJ5JfUVRYRYwykSa9d7G0AW6KM7/gZoJmFMpWgcIpYEz1VO/BhWCMiFNJQ9++9zTMS6Jdv0/jidkSeYEGY8aki6wJBq0Bn/PnmP+mfSYCOiEG0ZQ3G37tVOt+NoNMPlEDNwCCtrNT2AYQuLrczRsiNjwPVF3xuP4aLppaCSxIJpXCQ2xYAnMag1MituGwjC8vP11Q0IvMrR12Ym4XHyceukGhUzl0RrK45L+m6QRnPLwA4AtcX6Tj2K3lGM/OGZV6Cv2ngDLthROYtqRStQGMhNxRcDQQUqyBGZCdnEz0ANiGCgEquxlHP0MEkVmtukBV29E4Lh1/JbKIB6t3fsJwmmZcTTSxnodG0yzvzydJfykc9TV/KgYfR1ynsMBvsonAtKzf9a65okX/Wd6HyMXTXn6KEpd2NnXSfLU/9chAbbkyXG85cga5dwLVwBcRKRCGSiVSrOgzcRjhPiXPesD8EwkwLOs+VG1bqNJ9isyWmJj8AFZ8CXUnpI5ex3RaRJhFrQTSDHnJV4B0qaoGpohz2S786Q6KPWI07WF5N0AypWNmMoEP1sCKEtA0ltOxJxOw+QapPjL9kswM5HyLaHy170EW5EsPmvwYW/lgp+uGf1IDdJLuKbFlKkqJGvEY4i1YjnqVU1015UUBYFqJkFXbMXt0ukYXPZHOdoykIvIkq3tVAPISoi8dCYH5raMpD87biwX8FMs0lDlnEzA5mvUjTdFwgg1lhvkD3JIZJMyRDCTpY8dd1IWRJp0k41oqxAICRvskR8ZSGsYeefrc4p67nW+ebO/x0ic5WruqYxifkcLtdM61Frun65EtPCDwhVXv3VllQwD+19bRpplCL+ZnH/4Z1SMQ3o8t6hU/npcn2VVfHJZq8BFOjhcpQWbOd0745rpVMxFmnRQlNk/HMyB9FYzWPYl3Y9E9TZ2E1zyjUdBZF8jDboUpCW93jgDd1bFwRNRSJJF9QOiFaL8GcDtIlQmtP2ySkZ+ehKTgGb5Yzm7xlRzV5T/oZzxJhcpOBjU7fjK8MGoBgFn7z4jr8sbgTb9KRKtZol5PQkN7RC4LJDfp9hz3j0S3EAkUhfuVN6T4iK4fZ+JQGHMwLUDM1f8epnfnlQzFCGKjKguTIx5lo03qyY+XZgfVYnifzfjDmX4nWQ/YX6T+otgOHKjOOgWwpX38vaQc6WlTAsk4//fOfHlqMnXiPl8NSk/B0MOY4rizv7rzct0dMHRrOBBJ6pXPAC4eDwTXvHZN8DATvRDD67L+uSlYVxb1yaaOSgXC5FTNppscQbvcCfAdnPQ/SV56g/p6It/bQ1uMkx5AIwrfmWD8vgWNCrqCy9c8eUwPjU/kq2NGm2NpNb2r1zB7ntn9lTEYJUJSiIvgq7n8JkD45TF+7ZUHrIuWMZDAThlfEElmH3rHh6mA140y2isCf1o7IqbOlTEiO/H4jkLa1b3HyKNEhvCDFX90YLHip7dBy7mOlnieWcWkKKOg6nNMQ5qy2U7kgd2TdDSlV0Gb0qUgXHg5q/Xh9QC5m75V94VKVUuN5ztB+6MnzGFGRVDqgLt6L8MTs1SPy6Eop7OoutA+BUzsXVSdOXl6WndxwLLiUxbjJOH7ftlNVpV5k7+07SHMvo2ntTBzz08javVvSOGLMrMbGkSwMVue39y/uBeGlvNdFxr6yxP2Y1lcFK44lwt6ydoU/69I5fxwLcW+44Wx6dMZ/935lHKs1ZsXIOrBbAyc7a/F0BZSFtnmFWjaoKrCbEj9/2PD45EzStk2ZF+TIHDxck1S8+0maMgrrU6UypH5mig/OZoyH9p4+3GqlNMWRmrbELQ0tL+0WVjt9aVBim1Z9C2JenDoMalSwtmn12njzswitKKJsN/l486Nmacm6ykXZylq6CihzPrcWe/vsi62t1LTEBnXWOQ0kXq9SzYaOsip0itYBUX6WJ+1pYMXTmPXFS4klQNgxgSWNmHUGL6BvR5MhyoMU4jI67KkRUtMSTgiUcxWh9qELCYdBoH8Hm5/ThciXCDVJkRkz4cRDiu4YrSiMN1mlDTR5CL2z9WxHbcBHCx7pz/iEO50IIBduwlPzMcWy+waZgWsF4RZgG85E5qWY1xJaCC31Nb2q1/xJob+GFKqcOyERQY8BUQv80QaGzW8dYdeCeXixEKEsCGvS2s9DERHAXPRIe8FuCzAHFHvE/6C57EKV/0MzgiEgChesh6RF7DWSVZgX2vwV3BwlwmEuLunI3gCXPvWe3QSy5k82kJVsHuCIuZhSGk9duG/RhmK4NOhgKA9qvq6fv6l2w5KCCer5xg4Ny2CNtRUuT7n3njzXHbVjxJRTG0Dpx8tgCs/VR21UCtmUqpmbJnNPGeAdZYKHAY64Jxp1kcbyF0d/KcSMacwuzvpcopSy33iKXKBzAbYI8QO8kHVhXAYdx7Qdto0bXQdInMaPFz8j6N0+RN4lhK9Xf3KCMWwRGrchZQNq4SAkFr26ZU59pVwjK5fOGnKxpD9VqjPHfHHP8mWoGv0oXGIs1aEOuGNCn6FgHsGeZyBLWW7ozFyIUw9lDOHcK9l5JkAh/GaGM9CMomBc6pN6kUZQyOF3UoMmkPxfQsQlmdvQkjnDVaCPo1TorHnc1CZBSM3TYwnDREEdZ0afE6p6RsVVaP3cqV4Vi5LxKkyeOBxp/ICjePiPUlAGDETWCbViyOvALNCk+ZxQCzREJEXlLiX3HER0SpgFKDcbDIHWG6BWGKx3wSz00asMnxghmx9bDhiFGu2TniWS1NHThTQBM9Ul5UnMzQEDj03oq6GlRC4Zy7ub64Llw+Y51ibOWqQaqrBbGklhGKwBt6aaBsMAFpLtKAt1GU+T2TzhPkAXWfp766gNG8u6pe1gNxlYI63k93hW1oeYgG9M222EjsNeGDpA4kHnBalcK4lbY49xWo5eGE/lhZTDYOg8Rgu4JxxM1WcgY+mpGTPNdNwC4iPjYXNMZojX/81sGqM2qJ6wCHODYRq3WqwuqiFE0a8NqCmy9J4ERbbvKAp9jY9CWdGz+ZwULvxfiTCUb+mqQXnizIa6c7f/JMJ9s77eVlpleHrsI6ZQTrHH/aQU9ecGL7MzfTCzjZZhzHcumLxRXlrN4LdP2+WYa4ftCGjEBzrt6M2TMHSQhq74Te+53IUJPrUXCRIXCkYN0KXOZ7I3gTwNGojgns5x7cJKorM7lAdXz42ZGdFUg2nmB88XR9WEqIg4OpoLt6FwoFGLKu21wXCgWxvNXOZFzpucfOFYmTgRFhCMyoBxksHAHrPcMbt6S3kypJ68Z9thF7Y6lvuy9smI5DJck7Sly4vg5GvusYggPpit9ALfOBXNa24//jEZpGnLNHd2Vz1WJuzInccRioTj7jsjF5KEvzZ+gimgEoKl/8iYt1kbLWPLtWqHxtlHuXgsD+bcky9hPkU8/X12ObFXRtk95GV0vD1uIG+YLLhqCOxsCEzJK8vLA2tLTmtPivgMMCoqKSnXoygrS5NsS0Jry0xW0FBXN1exoElf/6jfEvNt3DbF0frw8sm9fX3+Pu064XY0mUlnnGR85FLVAtikx6y3z5LQJ6XVpDqXltlkT+aHLk2UVtNKEaQuvSWPHqnt/yvjKx9RWhoh2CWdWQIjXa0P3BW5/mG5mPTeAHBBv0mfa8axwAOkcq97NGcqutiv5MhNvCIBvloFAKjvuc3gsdkW4yKIpm+cmdkQ74PJcd9QKL0e/msttmd82tatIbb/hFrKHSeSRuvruAF63gXFCXYxPh6++HfsCInPnJEHzL1LB4CWEwwQPD9pK/q6EzTfb1G2PGoneD5r5FXPCYvEASNp5gxI6qSJLXB+lC5ZcZQnqidkPQtKPaqmD0Dm8ZP+Aznl/OIbxrjD41U/WmYRx/rAKHWyDHxjwFwCx3ejsJXNe3wccNnOgyM3HtUjU3GFT+TnDK70MhAtuMDjADI+xrKf4BErVt596t60YziV/X3+79bwsXkp3hEk/sx12dXVVWiaiWpGb587iTRoW11HtjbLghOD7GpnVt55Iw1rnBk6f9ulSEXu8UZUzBcBhXcx1/FF6XmUo+E5SCvh2kGsVGejUxZn405gqaMbx9ah9IUvZmxredTzmqhxxuhsE9PqIZ107L5DAuijYw7o5bwHrIl3L+jjEZUsrV2PiDOJhwiGV/5Q4nmqR8MXPY57CB7bahe6d4TLqwG82vFzPP+bLQP23cfAXO2bd+2iks/E8arWj1gxrR/rY3/MhAldqakmKVCupygG/B4KvYju2UKAaOZLAfOVGf3SGgbP0QNNqg91+tWMMX7qY5nRNZZdw9L3SqjwuWjuchPzUWdMy9aUK+Ey1JPxB3b71YCxLc1jG9bgMRUFfNvnbhHDQm/5OGrHRyNLMJIOOG7Jm+YVS+AN+pQHrA4Ho1+yTf4CagdwTl58OUwVHf4a9pjInQxeZJEiXGTfT56tNEGOkwiwdv65mC8q5XfY50BnddpXE3Ll5AhGf5AeS6ELEGN2d/9lVVwWpqXAOpnVgYMnGafh9qH5Jx2LDtUoA+zi4E/TSzABRfpvfk5PHUnUsW08ewoOc2DeTxXTTLb7mEfoEVYn2kxVo8ua1nPzc/A5/JVsQ3XMneD0np0Q0vQ69tp6C3NWhN49lL0JT50P/nptJzy60ihcurRx5Fiw0odoj8VkF0Vhg+aRDUWoaE5D85QX/SyoUPD6+0BYmYxLCnsLt0WYdu8BBs2u7UwxamKuwztzKq/COhSNkHReg/iT0s6ACCcQt2HLRr38Dv/xHhrJqNtVfgNdCWIy7QhWkYP8VKYTrRbm4FdtOLuII82Il4Sx2ZU6J0qxoVIO+l05diTy5PhUo+06VMtptPX4Ckkjgcr9eZvNC1XLDg9YysjoXFpVGK7tLeTuaGTa7UP+xz0VT2BH/ULndg9dWp7zxa20NFxmx8wEkLbCr82ExCa+fMSeEMYiO9Z84E4ebRH9uyOGtrfecnYxdmfjgkeqRAYLUS0wIpP4zlJUc9zJRlvwSrl6DQlHbQ08YtSk0YPZgz5FJEO6VvZ5qFQdvWNZfDN7nEVP8vgFzIXKuxyn7demi9eHSpoaJ3OHS0wbs00pzXFUJjhAQzpXgoP/RMu6VInRr5hx7dVu+ZcqhOW1D0QmZuzFvELtqGdD869lU1MLr+V+4I/5UuLtx27eOe9Hr4UlgOPMpU7sTXby6+Hm07R+dfO0/vXTRH1hBqCDmmzurH4862nbIhZ9IqizoWO5/STmtZTXk3Qdfuq4OE6pphyvY7oX6asmBe+E8XXWTLfQYmAHXbalu75LAY3lIiz3GsnlZPeXEC7KKQ3PFCj8NT1P7MIVZ5h5DNYQEykMQkaszaNPKkLFIVPaeFi/YdkV3Zsx7n3MY1l9+yHDxmhiluRWIPbk30FzGUeibFshVcz5W4xq01tJb/b0TQ6bAlYlxtLCPio4u2flZ6i5BdVlRr6imhx4jrML9P4D04ZDGIzZGgFED44bYMYiS6c0hZbai0BmqCRj4JhcOQzic/VR2j6QEocOvwisWX/qrr5zCI/Be4RiBfPs9cbgWWedzUFkGVqFj8CE3Ny7jyJDQG5PYfGOsXLCUtQpVqz1zXIi3uVekznFhPlyf4WWpScXASdSHKLJDU51fFE0msmFrCuyaGQgwGyseEQlSQzhcXSvL+Bplwc+mrnB3QNn0iMIwi/l2C39eJWUMC697F5iifIxxJdzpu59QV/k4pQ9OLNwBRALctFjbsOMxz8S+/4UDz1xY+fcYo4+ETyOCoDKQN/4goXxY7ggkAyvjjihAHpNRabZpIoZcGQfPNPuRMTskFe7rjtDv7x09KQzHLQCET52OiM/KQKUIpP7LY7kFsA8CVI0lvJ0Rk0KPiF8MSKX5NCLZowQwZBZMRnp3XZtNGBp3XZj4ChDV8Jm8WfXDdjCAsp1aKGl2nARIZUJJgoW0N+CS1m2gIJMG1EbA2Nw8IwrEp5kSMZ1w8UozksfrcPHdBdQjQJKuAf5CpbHUBGhs8wdUQh7rXD7
*/