// Boost.Geometry Index
//
// n-dimensional content (hypervolume) - 2d area, 3d volume, ...
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Indexable>
struct default_content_result
{
    typedef typename select_most_precise<
        typename coordinate_type<Indexable>::type,
        long double
    >::type type;
};

namespace dispatch {

template <typename Box,
          std::size_t CurrentDimension = dimension<Box>::value>
struct content_box
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return content_box<Box, CurrentDimension - 1>::apply(b) *
            ( get<max_corner, CurrentDimension - 1>(b) - get<min_corner, CurrentDimension - 1>(b) );
    }
};

template <typename Box>
struct content_box<Box, 1>
{
    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return get<max_corner, 0>(b) - get<min_corner, 0>(b);
    }
};

template <typename Indexable, typename Tag>
struct content
{
    BOOST_MPL_ASSERT_MSG(false, NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_AND_TAG, (Indexable, Tag));
};

template <typename Indexable>
struct content<Indexable, point_tag>
{
    static typename detail::default_content_result<Indexable>::type apply(Indexable const&)
    {
        return 0;
    }
};

template <typename Indexable>
struct content<Indexable, box_tag>
{
    static typename default_content_result<Indexable>::type apply(Indexable const& b)
    {
        return dispatch::content_box<Indexable>::apply(b);
    }
};

} // namespace dispatch

template <typename Indexable>
typename default_content_result<Indexable>::type content(Indexable const& b)
{
    return dispatch::content
            <
                Indexable,
                typename tag<Indexable>::type
            >::apply(b);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP

/* content.hpp
Krdr3uYzQ/2gvLAUvyvtRdUnGeOq1vt/XsLbenRFMbUoraS4fti2eR7mM3stIeu9GLiSb4pyO2R/O61Wn2c/K6J2m7OxwH4kHYPj9qz647T8keb0TVqKrj4rd5X4494lvjVwbM9OfTmgabJYWdDjpr+Zfv9SK8jON9l+qHEv9068Av/ceE7z2lTE3MX5kZ4por4k+yIP/S9/raYs7SqSXjEPjO809WLgGsbvfCAPj44npXmlQpFUjfwUD7Ofpbakasd/X5StPuUB2sXkjpe9keVnWrrKQxLnzZcZNXS9OOSfcqV/B8uJeFWy5+N5GObfSZrj4mbxZ545zDpLA3eNO7t+vryAvrknT+bykTvl8iybR8v29x1ZgBGqVs2eKzvJhoHalac/Txrhcc6t5GkSNOIuY40K1wo/Kfs4ULbsYXFZLFxK6hGeUblDzbSGfftN5Rnh9WXv/5Me/E+T/4Iw/x8XFC+y79oK40z6upL2msrYFl3XQV9eEiTSZbB73DMf8W/QTLxSpvZfYrRS2yMktbvfU49aJKr6ubdtmdM2bcuPRZlvs4xbt+aTIBCfreMhD+R92cIauMXga8v00fv33knpKXfU5Fi89b3f2Be7l1sGHWKV5q0IA3/m7Y8dyx0/fhbAoSNMz8tl2iZmnq0+psfuyvuuV9LfOoM76WdQ57+YX0YfKe4U9kck2F6/TdZJAr4dM/pekLhoe5PD
*/