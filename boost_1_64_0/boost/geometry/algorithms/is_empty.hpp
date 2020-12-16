// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_empty
{

struct always_not_empty
{
    template <typename Geometry>
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

struct range_is_empty
{
    template <typename Range>
    static inline bool apply(Range const& range)
    {
        return boost::empty(range);
    }
};

class polygon_is_empty
{
    template <typename InteriorRings>
    static inline bool check_interior_rings(InteriorRings const& interior_rings)
    {
        return check_iterator_range
            <
                range_is_empty, true // allow empty range
            >::apply(boost::begin(interior_rings), boost::end(interior_rings));
    }

public:
    template <typename Polygon>
    static inline bool apply(Polygon const& polygon)
    {
        return boost::empty(exterior_ring(polygon))
            && check_interior_rings(interior_rings(polygon));
    }
};

template <typename Policy = range_is_empty>
struct multi_is_empty
{
    template <typename MultiGeometry>
    static inline bool apply(MultiGeometry const& multigeometry)
    {
        return check_iterator_range
            <
                Policy, true // allow empty range
            >::apply(boost::begin(multigeometry), boost::end(multigeometry));
    }
    
};

}} // namespace detail::is_empty
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag =  typename tag<Geometry>::type>
struct is_empty : not_implemented<Tag>
{};

template <typename Geometry>
struct is_empty<Geometry, point_tag>
    : detail::is_empty::always_not_empty
{};

template <typename Geometry>
struct is_empty<Geometry, box_tag>
    : detail::is_empty::always_not_empty
{};

template <typename Geometry>
struct is_empty<Geometry, segment_tag>
    : detail::is_empty::always_not_empty
{};

template <typename Geometry>
struct is_empty<Geometry, linestring_tag>
    : detail::is_empty::range_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, ring_tag>
    : detail::is_empty::range_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, polygon_tag>
    : detail::is_empty::polygon_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, multi_point_tag>
    : detail::is_empty::range_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, multi_linestring_tag>
    : detail::is_empty::multi_is_empty<>
{};

template <typename Geometry>
struct is_empty<Geometry, multi_polygon_tag>
    : detail::is_empty::multi_is_empty<detail::is_empty::polygon_is_empty>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct is_empty
{
    static inline bool apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::is_empty<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct is_empty<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor : boost::static_visitor<bool>
    {
        template <typename Geometry>
        inline bool operator()(Geometry const& geometry) const
        {
            return is_empty<Geometry>::apply(geometry);
        }
    };

    static bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{is the empty set}
\ingroup is_empty
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is the empty set}

\qbk{[include reference/algorithms/is_empty.qbk]}
*/
template <typename Geometry>
inline bool is_empty(Geometry const& geometry)
{
    return resolve_variant::is_empty<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP

/* is_empty.hpp
3H3GzHOBfSv65RcyP36aheKTzY8vZjO4cdy+xSjY71Pt8/9x12xeMp+7ZouQeT3NlibDfCubRcBWOCT9SmAZivNxMMuR+eeUZgWRb2cyn9dmeworCSsLq4h+qQo7U1iNzP+mi9ml1J937zfrNIHdKMq8gwyvj9pgf9oe09eKvR9Fo++dPSPsRWFvCHufDK/xPiPD6+JvRZm/iLjQguPjZkCj7w1GyQ7fYaFDA5sX7C+KWwSN8i2NRvVcmWzSZxqizIwoMyesIGxnYXuKtpdEPcuizIpoe1WUeaYosybsUmFXC7tRtP0OUc+2KPNR0fZnyPAZ5BdFvjdEvveFfSbsW2G/iH4JLQTG6w+My4yCcb/MK8pcBIzrsrSIW1nUJSXqkhFl5kSZBWE7C9tTWEm0vSzqWRFlVkXbzxRl1kRdLhVxV4u63Cjqcocosy3q8qiIe0bU5UVRlzdEme+Lunwm4r4VdflF1CW0sFh/ZH7dYe8o2qTvWpaPmhcsNPXqq3obzBYh83qaLS1sZTKvp1mKzK8fzDKizJwosyDK3FmUuSeZ95lZicyP12ZlMt/3mFVEviqZ3480O5PM73ub1UQ9LxVlXi3sRmF3CGsLe5TMn0U1e0bYi2T+u0Zmb4h+eV/YZ8K+FfYLmV+vmIUWGW8zuHG/7HZYFGyqqY/Y19eY3a+bF2zqqfc+2u8TmS1C5vPMbGmzKJj/hptZmuLwvmKWzNtglh9rlTW2B5tm6hWOsbr452q7gYXNfM6bFcl8bZodTOZr2uwoNMp3grBTyfz4aXaOiKsLu4LMfx/MrEHm42fWFO1rCeuQ+TMLZl3RvikirifGoS9sQOZrxWxIht8tG4FNa/8x6TvSZPjdsvCik2zyd6SFxcjwM9o4GV6nJsgmfUdzbL49jkiCTTf1VVP7uJulybztZllheTI/TphtT4Z12U2UWSTzvjY7WOQ7SuQ7Qdipoi7niLrURdwVIq4h6tIU1hJt74i4rqjnFFHPnsjXF2UORF2GZP59BLORKHOCzNeKWXix8fkiZL6OzGLC4sISwpYn88+gzZJk/n1tszTZe73ibYFlyfxZB7M8mT/rZ7a9qOduZP6ZsFmRzI/XZgeD8RgdReb7T7MTyPx5drNTyfw5TrNzyHwfaVYn82fdza4Q/dIwi4L572qatUW+R8l8j2L2DJV5c/aNU/4xewayD3HTT538/7NPswGZrz+zIZmPn9mIzMfIbEKUGV58svn4mUXAOF9MWFxYQtjywpLC0sKywvJkvicy257Mz41mu4kyi8IOFn19lLATyHxPZHYqGI/7OSKuDsZz4gphDTLfa5g1yf7fS+1RbIHNMPWRh3n7zDpkns+sK+KmiLieiOuT+fozG4i4ocg3EnETIi6cGB8XAeO4mFkU7LZ7D+8FtjTF+Rw0W5nMz5tmKTJ/DsIsQ+bHOrMcmX/GZ1agetrftnIrirocTObX2mZHmcXALsq9nA/sHIrzc45ZXfTLFVTPAwuzPRTYHaJf2qLMR4U9M9aa07wINuPUzf9/49PsDTLfL5m9T+bjYPYZmc8zs2+F/ULWW+L5TmChJf63mcz8GGk2AxqVGUWj9s0rbBFhS4t8K5P5OjJLkfme1iwjysyJuhSE7Ux2xnKr1QLbk8z3KGYlMn/O0axM5nsUswqZ7yPNqmS+ps3OBJuZ+qUGFqFxvxSN4q5Go3reiEZ9fQeZrz+zNpk/E2X2qIh7RsS9KOLeIPNnbc3eR6P+/AyNxvZbEfeLiAstacdBsAv2nGcGX0dmGOef6ZstQubPOpgtTebHT7OV0WgOpsh8r2GWQaP1lwPj+VIA4zmxsyhzT1FmCY3WZllYBYznblXU80w=
*/