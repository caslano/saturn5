// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TOPOLOGY_CHECK_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TOPOLOGY_CHECK_HPP


#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// TODO: change the name for e.g. something with the word "exterior"

template <typename Geometry,
          typename EqPPStrategy,
          typename Tag = typename geometry::tag<Geometry>::type>
struct topology_check
    : not_implemented<Tag>
{};

//template <typename Point>
//struct topology_check<Point, point_tag>
//{
//    static const char interior = '0';
//    static const char boundary = 'F';
//
//    static const bool has_interior = true;
//    static const bool has_boundary = false;
//
//    topology_check(Point const&) {}
//    template <typename IgnoreBoundaryPoint>
//    topology_check(Point const&, IgnoreBoundaryPoint const&) {}
//};

template <typename Linestring, typename EqPPStrategy>
struct topology_check<Linestring, EqPPStrategy, linestring_tag>
{
    static const char interior = '1';
    static const char boundary = '0';

    topology_check(Linestring const& ls)
        : m_ls(ls)
        , m_is_initialized(false)
    {}

    bool has_interior() const
    {
        init();
        return m_has_interior;
    }

    bool has_boundary() const
    {
        init();
        return m_has_boundary;
    }

    /*template <typename Point>
    bool check_boundary_point(Point const& point) const
    {
        init();
        return m_has_boundary
            && ( equals::equals_point_point(point, range::front(m_ls))
              || equals::equals_point_point(point, range::back(m_ls)) );
    }*/

    template <typename Visitor>
    void for_each_boundary_point(Visitor & visitor) const
    {
        init();
        if (m_has_boundary)
        {
            if (visitor.apply(range::front(m_ls)))
                visitor.apply(range::back(m_ls));
        }
    }

private:
    void init() const
    {
        if (m_is_initialized)
            return;

        std::size_t count = boost::size(m_ls);
        m_has_interior = count > 0;
        // NOTE: Linestring with all points equal is treated as 1d linear ring
        m_has_boundary = count > 1
            && ! detail::equals::equals_point_point(range::front(m_ls),
                                                    range::back(m_ls),
                                                    EqPPStrategy());

        m_is_initialized = true;
    }

    Linestring const& m_ls;
    mutable bool m_is_initialized;

    mutable bool m_has_interior;
    mutable bool m_has_boundary;
};

template <typename MultiLinestring, typename EqPPStrategy>
struct topology_check<MultiLinestring, EqPPStrategy, multi_linestring_tag>
{
    static const char interior = '1';
    static const char boundary = '0';

    topology_check(MultiLinestring const& mls)
        : m_mls(mls)
        , m_is_initialized(false)
    {}

    bool has_interior() const
    {
        init();
        return m_has_interior;
    }

    bool has_boundary() const
    {
        init();
        return m_has_boundary;
    }

    template <typename Point>
    bool check_boundary_point(Point const& point) const
    {
        init();

        if (! m_has_boundary)
            return false;

        std::size_t count = count_equal(m_endpoints.begin(), m_endpoints.end(), point);

        return count % 2 != 0; // odd count -> boundary
    }

    template <typename Visitor>
    void for_each_boundary_point(Visitor & visitor) const
    {
        init();
        if (m_has_boundary)
        {
            for_each_boundary_point(m_endpoints.begin(), m_endpoints.end(), visitor);
        }
    }

private:
    typedef geometry::less<void, -1, typename EqPPStrategy::cs_tag> less_type;

    void init() const
    {
        if (m_is_initialized)
            return;

        m_endpoints.reserve(boost::size(m_mls) * 2);

        m_has_interior = false;

        typedef typename boost::range_iterator<MultiLinestring const>::type ls_iterator;
        for ( ls_iterator it = boost::begin(m_mls) ; it != boost::end(m_mls) ; ++it )
        {
            typename boost::range_reference<MultiLinestring const>::type
                ls = *it;

            std::size_t count = boost::size(ls);

            if (count > 0)
            {
                m_has_interior = true;
            }

            if (count > 1)
            {
                typedef typename boost::range_reference
                    <
                        typename boost::range_value<MultiLinestring const>::type const
                    >::type point_reference;
                
                point_reference front_pt = range::front(ls);
                point_reference back_pt = range::back(ls);

                // don't store boundaries of linear rings, this doesn't change anything
                if (! equals::equals_point_point(front_pt, back_pt, EqPPStrategy()))
                {
                    // do not add points containing NaN coordinates
                    // because they cannot be reasonably compared, e.g. with MSVC
                    // an assertion failure is reported in std::equal_range()
                    // NOTE: currently ignoring_counter calling std::equal_range()
                    //   is not used anywhere in the code, still it's safer this way
                    if (! geometry::has_nan_coordinate(front_pt))
                    {
                        m_endpoints.push_back(front_pt);
                    }
                    if (! geometry::has_nan_coordinate(back_pt))
                    {
                        m_endpoints.push_back(back_pt);
                    }
                }
            }
        }

        m_has_boundary = false;

        if (! m_endpoints.empty() )
        {
            std::sort(m_endpoints.begin(), m_endpoints.end(), less_type());
            m_has_boundary = find_odd_count(m_endpoints.begin(), m_endpoints.end());
        }

        m_is_initialized = true;
    }

    template <typename It, typename Point>
    static inline std::size_t count_equal(It first, It last, Point const& point)
    {
        std::pair<It, It> rng = std::equal_range(first, last, point, less_type());
        return (std::size_t)std::distance(rng.first, rng.second);
    }

    template <typename It>
    static inline bool find_odd_count(It first, It last)
    {
        interrupting_visitor visitor;
        for_each_boundary_point(first, last, visitor);
        return visitor.found;
    }

    struct interrupting_visitor
    {
        bool found;
        interrupting_visitor() : found(false) {}
        template <typename Point>
        bool apply(Point const&)
        {
            found = true;
            return false;
        }
    };

    template <typename It, typename Visitor>
    static void for_each_boundary_point(It first, It last, Visitor& visitor)
    {
        if ( first == last )
            return;

        std::size_t count = 1;
        It prev = first;
        ++first;
        for ( ; first != last ; ++first, ++prev )
        {
            // the end of the equal points subrange
            if ( ! equals::equals_point_point(*first, *prev, EqPPStrategy()) )
            {
                // odd count -> boundary
                if ( count % 2 != 0 )
                {
                    if (! visitor.apply(*prev))
                    {
                        return;
                    }
                }

                count = 1;
            }
            else
            {
                ++count;
            }
        }

        // odd count -> boundary
        if ( count % 2 != 0 )
        {
            visitor.apply(*prev);
        }
    }

private:
    MultiLinestring const& m_mls;
    mutable bool m_is_initialized;

    mutable bool m_has_interior;
    mutable bool m_has_boundary;

    typedef typename geometry::point_type<MultiLinestring>::type point_type;
    mutable std::vector<point_type> m_endpoints;
};

struct topology_check_areal
{
    static const char interior = '2';
    static const char boundary = '1';

    static bool has_interior() { return true; }
    static bool has_boundary() { return true; }
};

template <typename Ring, typename EqPPStrategy>
struct topology_check<Ring, EqPPStrategy, ring_tag>
    : topology_check_areal
{
    topology_check(Ring const&) {}
};

template <typename Polygon, typename EqPPStrategy>
struct topology_check<Polygon, EqPPStrategy, polygon_tag>
    : topology_check_areal
{
    topology_check(Polygon const&) {}
};

template <typename MultiPolygon, typename EqPPStrategy>
struct topology_check<MultiPolygon, EqPPStrategy, multi_polygon_tag>
    : topology_check_areal
{
    topology_check(MultiPolygon const&) {}
    
    template <typename Point>
    static bool check_boundary_point(Point const& ) { return true; }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TOPOLOGY_CHECK_HPP

/* topology_check.hpp
9wlOTzp4Uuic0iP/0jHBJP0ZNvEyQUFSmFc1YZA/vOEoFLkIZVg4iBWW5rLxG72Gnnqu2oo1NQiOvJtlbT8PZc3+8PoxFKhc+xoq0/UZy2r/zqmKLqxC8sNysydYlHq5qOzBs2Yxg6o6+2MbgBWAxOrTlzDUuAQoVXK9CiHA/wlruBLthQNeIDrBSe+MJhRpViN6qSh7plQTM14WW+0KH+WSk4ayQ7jwFA015o8e0Y1yhDsbvkGivY5Q96IovKGEf6YYlY9hN7K72al/EZ2gVWF/FK53Ve5ZONziN1CJ9JdVMuMMpIg9A5rMqjR/rL7gr1e/hVw2uKDuuDezWSTU5BfJIt6xnUWMP2y/y0JC6FCsNLpMMl+9AAnrWkDwtQ3ox49uFPqiKHO9LFomvv6CHq3ibDnJhcT+Q7K3eLNRiXUYlgJJQPGbxU6eg9RHyIQYuVnGMSrxyS5VPRilcH1y8L+b67CtfHOo/P6Luv883DYvUuQu+QQioZyG4rwYftYFjNetX5Wh3m44BelzxZj0R0KFexsEzcWRgWgpJOsXQ1vpaYXGuZ9Kkot3xZANYSMeKhTPckm5seYhcHmDZzMBZk0rzY4vZJo/soNdk0NSpOJo0g9MlsKEVvVUHgcodU3Nli1Lly37Voraa+1tcLJYvdvmsh+jp/kWlGBpsF/buD82x2JNV+K7EZ3ePvrYXYg+U0ZnepZSwb9ac8Vy/RAr9NJ1tuXaHz3diSVbb9RbIAivqlth1ULNXKVPWWeutFyCl77sVEt0uMFprtJDHrav0j9+2VqlA49+xSrtqaSMbbVSc921lusia13ynk3R2GqlVkDNAxL4BA90k5X6MuPPs6sXeOklp1rJe6OQPr04zwsx98GuZnKjFklRRLEXhPwtgHvXvi92IFBEY6nyMUY+Yr4PEGyhADNSEh4LJBYmXO2MnyC/QLZxJkyAM5Q/4+oMrm7yC//rhH/H9RPz2iO+OzjQxxzH3MiAjVi8NKX7s7fEH1j94Y8y/Xs/6viBVb9fPLD68G5ZbrgfEpfT1u3l2FTgxKtR072KuZ5T9Gw+QnBMiqD5YLl1qZUa7SK3U9gPXOa22i+yXTypYv0IzNph3uFNSDV7VVNpO859Z3BEQH+mhE9Jz0MJRmvMLNDkVHnh3tRPdPoNTu9TbH5RopcFj+eDmhBv3YxQXorPLtWfZvgEFf6iwzxghQarsVPTX8mp1wuTAlG/21ijYO+WRypxXOKIJp4tj8k4XZ1KnsaV7dhswZDcacRBwbZ6RbpUFYLTHi6ZJ3NlFUcxIdD/Oe5g4MX+hZfwXtde46peYl0uF0zTWOprPO3nPfWe8FP1+c39WZbzV5sPNyMZ+cNU27Fq+FYsuedb2+6f/EnuAHNXK7k5UvH6fHPzh6uG70Pr/z/u17E8e6X/LUNyVa15cIuYKJq8TzIcXL6ozfCOgb7s3Vy6/NgtF1ZdkeSPTu3k129qdPLZCK8x0QmdivUNaK7O2JW6XvBVHZdn7EQ4aokXxRknbEguik5y6nWFizc4qaBhohYd3xl3TlVTnT7nHiETx1d1hYsXT1AOUmUedhsqr3XIn5Sdw2f1b13J4nxwunw1T5bfK9Zs1sZs/pUL+s/FcsKUo3DJfCWp/GReRcId24KL+F7giQUVJT7bZT73F55dHxqacLDZ75YHmywP51QbnGKoZdy+t2Lst70EoZ0NBJSloecU/zh2ziSI8OdX0RcsZrqzu4sVggGYTmTp88TbPrVOcbDRlYV7Muthn1rc78WKoXPzO4S4Ex/2e4gxyvUgiiHPx/1GfV/lxiux10XughxdfXX7TyGn6en+fNRgMFvMGOQiOVLImU0TA7M7Q4k=
*/