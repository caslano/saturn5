// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

enum boundary_query { boundary_front, boundary_back, boundary_any };

template <typename Geometry,
          typename WithinStrategy, // Point/Point equals (within) strategy
          typename Tag = typename geometry::tag<Geometry>::type>
class boundary_checker {};

template <typename Geometry, typename WithinStrategy>
class boundary_checker<Geometry, WithinStrategy, linestring_tag>
{
    typedef typename point_type<Geometry>::type point_type;

public:
    typedef WithinStrategy equals_strategy_type;

    boundary_checker(Geometry const& g)
        : has_boundary( boost::size(g) >= 2
                     && !detail::equals::equals_point_point(range::front(g),
                                                            range::back(g),
                                                            equals_strategy_type()) )
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
        , geometry(g)
#endif
    {}

    template <boundary_query BoundaryQuery>
    bool is_endpoint_boundary(point_type const& pt) const
    {
        boost::ignore_unused(pt);
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
        // may give false positives for INT
        BOOST_GEOMETRY_ASSERT( (BoundaryQuery == boundary_front || BoundaryQuery == boundary_any)
                   && detail::equals::equals_point_point(pt, range::front(geometry), WithinStrategy())
                   || (BoundaryQuery == boundary_back || BoundaryQuery == boundary_any)
                   && detail::equals::equals_point_point(pt, range::back(geometry), WithinStrategy()) );
#endif
        return has_boundary;
    }

private:
    bool has_boundary;
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
    Geometry const& geometry;
#endif
};

template <typename Geometry, typename WithinStrategy>
class boundary_checker<Geometry, WithinStrategy, multi_linestring_tag>
{
    typedef typename point_type<Geometry>::type point_type;

public:
    typedef WithinStrategy equals_strategy_type;
    
    boundary_checker(Geometry const& g)
        : is_filled(false), geometry(g)
    {}

    // First call O(NlogN)
    // Each next call O(logN)
    template <boundary_query BoundaryQuery>
    bool is_endpoint_boundary(point_type const& pt) const
    {
        typedef geometry::less<point_type, -1, typename WithinStrategy::cs_tag> less_type;

        typedef typename boost::range_size<Geometry>::type size_type;
        size_type multi_count = boost::size(geometry);

        if ( multi_count < 1 )
            return false;

        if ( ! is_filled )
        {
            //boundary_points.clear();
            boundary_points.reserve(multi_count * 2);

            typedef typename boost::range_iterator<Geometry const>::type multi_iterator;
            for ( multi_iterator it = boost::begin(geometry) ;
                  it != boost::end(geometry) ; ++ it )
            {
                typename boost::range_reference<Geometry const>::type
                    ls = *it;

                // empty or point - no boundary
                if (boost::size(ls) < 2)
                {
                    continue;
                }

                typedef typename boost::range_reference
                    <
                        typename boost::range_value<Geometry const>::type const
                    >::type point_reference;

                point_reference front_pt = range::front(ls);
                point_reference back_pt = range::back(ls);

                // linear ring or point - no boundary
                if (! equals::equals_point_point(front_pt, back_pt, equals_strategy_type()))
                {
                    // do not add points containing NaN coordinates
                    // because they cannot be reasonably compared, e.g. with MSVC
                    // an assertion failure is reported in std::equal_range()
                    if (! geometry::has_nan_coordinate(front_pt))
                    {
                        boundary_points.push_back(front_pt);
                    }
                    if (! geometry::has_nan_coordinate(back_pt))
                    {
                        boundary_points.push_back(back_pt);
                    }
                }
            }

            std::sort(boundary_points.begin(),
                      boundary_points.end(),
                      less_type());

            is_filled = true;
        }

        std::size_t equal_points_count
            = boost::size(
                std::equal_range(boundary_points.begin(),
                                 boundary_points.end(),
                                 pt,
                                 less_type())
            );

        return equal_points_count % 2 != 0;// && equal_points_count > 0; // the number is odd and > 0
    }

private:
    mutable bool is_filled;
    // TODO: store references/pointers instead of points?
    mutable std::vector<point_type> boundary_points;

    Geometry const& geometry;
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP

/* boundary_checker.hpp
OGroaM2Y8Ko0SLFBlxM2531uf4UfV1/hdQ6oKvnd/q0ILErOo7mL8Cq79n54NSI+C2pol9sPX1LebMH0Swsdg/4QvK2Rlzpsx7IyO+ew0g533tbZO5F8tUvc8SHvdj5tBQxIhFd5e9tR4rviAkxbpq1yl9e5ejsC2mz2qNtPf+vwak+ktDcyUsGR+9KdMYoi/aJfx97Dmhbgm7IXp+TfqtRCuzTLIwgKdc9T1FtfdomgvhEun7xUEimFXPjHGOT1XVlKAsrLZ8bS0+TrlVJZdp0oSBjs0MuQGY3BQSU9dAr/9cFdc0iIiX2YTCafn5vwyZrIKMz0/NR78XxIMh2nwNGKjr5MUiuS3CP5ld7fO23qlZHy2QbXUO9/gZKhQemxah9qQhyUbQL6o8cy43z85HXyuPJTW1SOZxzjhHz7+S2iAsR4GfL/laao+CZlhyX8hyybe9YiSStTy4o9LoV/tCu92g+9fgz9LoynXfApKnCXf95mUht9UoWQyD8dpy2RIjw1AAvihlXX2X9DISpGW43xZWi0UBp5UTDHo3neWd8IadKpp+T8WJShUnh3VttDyVpgQr1TC4SKd0eLDstcGe363a4kZfyVpqwfR/kBZe3vwAVQm/ZPIlGJhyqs4h3iMWFxIglqC4jr9c6gtlPZ0cSaIt7vmHUtBU9pb+ZSOLDi2BE4mypEFDO1G49HsP3u84SkhPu205QZp17C9uauc8UWdJhhcrM9rG2e6Bhkd9/SyS5HxqvfeZG8l1eyGrOvkdNjDFUi5llOsxORV93fpG0GFl5uF81CqKDH1oLi0c8Seb1Fyq5AOO/lyUtE3imMkgxGKKm1L8SY1uhHLsYvqNUr39SdkiI8WkGkYhWQpB8z7oVQPD7Vh/LfV8sKhkQFYyz5WiGUBTsG9YcHpeq8rEn0XnQmD/yBFdpWlvD0hSwBTZ+98+aU6jns1aFIq62oTzbOHI2FSH4B+fiLP4r/9brJ/wpEj83YmWSznneHjVL6D69b7udfvcop7ud9S/7EuMPPUU/C//5cSjo8KSUd/gggEpo//66lNntxpD+t0DNZ2mzCYyOrAlpSTVWT8/9rcr2h/a83M1dKvioi9sn/V/BlyZh/rNjnSfxpfxhGWyQuGeuwNSf/apaXuUHAj0Zoc/rPEl6AbkDbG8d/87dY/BLEN8ZvCuXFFJW9TFIuk+Rlflag7Qpyy9qdp33v076mPZgTqHhK/Gq4Uk7fu7g3zBH49Tbwy6l7UEpdGUeF0ggFoCUDQa3rt1qSrUBDp5/6D7pAPQwIaK0KYMipbwWuLLFFgR/EC0hb3zeh2BqtQFnfAOqG/ChIsRWpBTmrJq0zTxD3yUuwaagDy+YJYqx+72iHDRmizx9G+FIH2/IDwogCE8kUq+fSxRvI2d8YF5I+96PLfdpydI/XVIau0l9FpwalIu0yIi7aAOr3IheFv59+uSFa3y5fG2ujLMSmVwFZlnzHQuj+XMVKZQ9JX3qJtFqIImHUcFUSwjLc/lq9OyZ1vgZ5hgtdwezLPZMzKGV8uXlfG9QgIEGx9M766eXgyuhY8I6E/StIBXkCOTM8kz5iG7q/zKi69Ki41ps6QXUAewYL596iDkKlRB6qptQLH/cwn7SlFDpbmtKmzDySCoFASrvQXZY8Az/oQIamL5WMHad8CPx5pKt76T/7ftCrzup7lqq149RJkSRp5qy12iSyMr8JZPcbj2D3LVXGzbxgYAr+KcyZ5WvtfoMOSbuC8kZ9hfnTsygJlJ994288k0dmfhAbr3wt+BvKJn1/OWH7ie5q112fDngjapOI6i+igt1d+kWI44iWne/Jz0GGk141IF8gpNxgTwMQKv9yaRI=
*/