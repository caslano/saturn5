// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP

#include <cstddef>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/times.hpp>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace num_segments
{


struct range_count
{
    template <typename Range>
    static inline std::size_t apply(Range const& range)
    {
        std::size_t n = boost::size(range);
        if ( n <= 1 )
        {
            return 0;
        }

        return
            geometry::closure<Range>::value == open
            ?
            n
            :
            static_cast<std::size_t>(n - 1);
    }
};

}} // namespace detail::num_segments
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_segments
    : not_implemented<Tag>
{};

template <typename Geometry>
struct num_segments<Geometry, point_tag>
    : detail::counting::other_count<0>
{};

// the number of segments (1-dimensional faces) of the hypercube is
// given by the formula: d * 2^(d-1), where d is the dimension of the
// hypercube; see also:
//            http://en.wikipedia.org/wiki/Hypercube
template <typename Geometry>
struct num_segments<Geometry, box_tag>
    : detail::counting::other_count
        <
            geometry::dimension<Geometry>::value
            * (1 << (geometry::dimension<Geometry>::value - 1))
        >
{};

template <typename Geometry>
struct num_segments<Geometry, segment_tag>
    : detail::counting::other_count<1>
{};

template <typename Geometry>
struct num_segments<Geometry, linestring_tag>
    : detail::num_segments::range_count
{};

template <typename Geometry>
struct num_segments<Geometry, ring_tag>
    : detail::num_segments::range_count
{};

template <typename Geometry>
struct num_segments<Geometry, polygon_tag>
    : detail::counting::polygon_count<detail::num_segments::range_count>
{};

template <typename Geometry>
struct num_segments<Geometry, multi_point_tag>
    : detail::counting::other_count<0>
{};

template <typename Geometry>
struct num_segments<Geometry, multi_linestring_tag>
    : detail::counting::multi_count
        <
            num_segments< typename boost::range_value<Geometry>::type>
        >
{};

template <typename Geometry>
struct num_segments<Geometry, multi_polygon_tag>
    : detail::counting::multi_count
        <
            num_segments< typename boost::range_value<Geometry>::type>
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



namespace resolve_variant
{


template <typename Geometry>
struct num_segments
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::num_segments<Geometry>::apply(geometry);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_segments<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_segments<Geometry>::apply(geometry);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};


} // namespace resolve_variant



/*!
\brief \brief_calc{number of segments}
\ingroup num_segments
\details \details_calc{num_segments, number of segments}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{number of segments}

\qbk{[include reference/algorithms/num_segments.qbk]}
*/
template <typename Geometry>
inline std::size_t num_segments(Geometry const& geometry)
{
    return resolve_variant::num_segments<Geometry>::apply(geometry);
}



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP

/* num_segments.hpp
I3xI30g/yq9n6VL7hzkkv7+P1+fKNJrqIqaeaXaXl7FbzswcCvnGl9l1/TOPargu+BrrvRqiD5HjFtERbdp//3UqKrBymnyd//oQSDlxGnapwY810ET65JwKaZf9C/xLTeh0f459Shlnjm72atK0wBeO0/1Ci46T0j90df3HNndX1sEZv6/bLPKo/zSn85qw65tut+eKZyGd717LaYrxStZFOWdh5gbQ9V/v91wb/DnI5gDStj/Kv1ag/UWp1JPH0/EO5Sd9Ys5C2x7iInOEZK+fbvMD/ZvsD+QcA7GQ8bS79k/HCtkHeGNor5Yx4735+KzGuqdaakg7okF9wL/uR/VRXU3TqNYxkU5RB2V6oRf42iJiQv506f+Qh3r6z6v2xNm7GPqij/i9+vZqmU/wSeuHjKtLnh3Z1G2s8Hfm6kTDJlkf6FwLunJMgI4cf4iGnHN7x+cNmwLrw3rbtidtom3bZD5wBtt2/Cb//VVtTN/7LE9ZHtnYs3Ggt1obNvZvHk7pYbrOxPiWuNH/GFAbc2bHgfYN/Z/OvUQzP/KrbXPueq+d1//316vji/Sn9hF0Doq0wN4qzwERz/+n1voN/as32atnvjalrkvZNvRfbG+t12PLwfPf1mnai9jrsMM31ZZldAUYfMBe19NM5nWIk14rhK2Mi/hV5qrYR66Db6XuQ0dtYzIexAIt2JJ0Qg/aajvTY/nPWnkeK9OonMvK2F9RfMA3XYOHftc4fwPfiF2O+eR8j8YstaFBY1bjleWJmKTGXWuD679ybWD5D21FT813qS31iuEbWmb+0V/2XSPMqxG8NBy6Jrj+66V/aUPKuufrEt1dK1pzTeB90TeukfVNaqpjk6qPWGUMNP103TDmGl0X8dPrB7RtwSfsZHzSlrRP/31KW1XwyuqhKllWsnxwDHzqx8Gv7APhW/bn75vEKvzSdZx1QYzfXRXcumwLsv+31wTXf0OQ/QfT98Ygxz4lyP7tXv/6MatWq3MhXQecatO1B+hITen77dUe7TPr82GvT/9ru8y6As6n/d83Vbw6sDXkvup8ucq/zrTKnq+TUI03vBrymhb8dZv3avmo9YiWjdSj88D7VgWejkDX2Wk6VnnTQeOQaz3Szzk9iKE3eRkD/8q9C/AZ2PV99Zqjem3/jyvp2Cz9kOuYMn5yHift4V/mCTMfNSt/Wd7SJ/yp5S19q/Ohz0nadq8MfL6zeSVfXqtzRR73vsxmrDRdO4DfwOd2ZuU7cGVg15z6WvdOXu3VIGshgaVlRmjP0tN0dXDT8e2rg59Xc3UN7L3XeErzr5Mb5Lz6bEXw8+pXK4LbPnau8Oj1T3ksWUH7Ntpvmo1ndCyT/SeNCzHT/hP+V/Su/ze7H0+uJ6yg/T97/R+afbv+f/Cq3o9j/tJx71U0HcGtuyuvCn77mNAPGtH9oHEY9tBQy1X6DXH2fk4RzLgbKuWaCHzR+V/X+cTGysDnHQmVom31bp3HrI28c2WX+7rk9zwewuersBdh/89y6GDfgX0udmiZracgHnWdxlhTNtpidh/tO5b1zf6FPtrv6KP9ZbCn+ZyzLLD7H96I7V35frLU/FoUzvfkNTBc78b17TN7HewXS/1fM1V04IdPo6rxPaJB78uJzNXjPLBIvZ+Jlp1MN+LC66Xyejv1hRh6528I8af2N/Aj8xo2yAfdbh65Z34Of76OmAK71+ur/XTwtZE+qf/Zkr7FcGBR7+MQMbxIYjiwqHdxHE7qXRxou11iqVsi6428vqv2//CHuNRxoGtbXQg/iM8kX+W4AF89y1M+P6W+PiddItseNAJrI4gPMUk/8nz934tFe+lbOZ2JMmpZTNMl2z9s/acP8ck=
*/