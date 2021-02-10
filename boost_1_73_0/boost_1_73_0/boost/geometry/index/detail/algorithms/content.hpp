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
Yr0cNiAia7KtBKj//+8aK+ELEAQt4R9zUm04Tg3F1lrWzLg4F7twumvZP+w4amUT9wzNCF0h1PhShEt9TOwxBO4myz1MnMgBCGNL0BMxtw3aegf3IiEecQ/GqzMB8GAbA/e1icUHHFOEF+Wv6DeT0kRyrBbfhs+kEIBhdbRr8jiKkG+72wH+OLQcb0XYrLFRTR+sNg+bvf1j2yR2x1jxdeSf05GPrjsEM3HZerl9Xxykg2TaPxydwiGe/tgwcoY897reQF1+1vdyBLqH4+H9XEx8BIW3ojHBFIcGNneFH6EXqZTXIMmfzHyZEG7kQ7iuBlMFYJ8YkdSXKC6w52YI0gj6vKNMlBQRxE5hHha1+0Zm0buAu3bSBfBuDW0gvwaQCDi/2f0p9ivtnmYrY8A/K5yNgkmtGyuCP6Hb1NdD9O/rRxtTLCfexpnbELEinqg6B3IZGdIEWHLgaVP0UhSwt/O9oUovmLShqhcA32UR5Q6THCToIlvAtMrzhDN6jF3134AyyWfNjGuBeuGZUygcvz8EzPShPQSp6ZtgtA1fOt0ADodxugBXlPQScCNat3GaeVawKD1fFC5RybQsZw5T5GYZ6yXMCr3Q2kW1KhTD1vFCuJsfQnsmj7ulfZeQFgt3yORs2pxy10jLw8if
*/