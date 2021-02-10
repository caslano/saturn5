// Boost.Geometry Index
//
// Get smallest value calculated for indexable's dimensions, used in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct smallest_for_indexable_dimension
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (smallest_for_indexable_dimension));
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t N>
struct smallest_for_indexable
{
    typedef typename smallest_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, N - 1
    >::result_type result_type;

    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        result_type r1 = smallest_for_indexable<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        result_type r2 = smallest_for_indexable_dimension<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        return r1 < r2 ? r1 : r2;
    }
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag>
struct smallest_for_indexable<Geometry, Indexable, IndexableTag, AlgoTag, 1>
{
    typedef typename smallest_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, 0
    >::result_type result_type;

    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        return
            smallest_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i, data);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP

/* smallest_for_indexable.hpp
NLSjca4ioB5nMTE+RLxHenW8nIeXnl0BgYQXYqDw8iu5Oop/QdAFAjjulZMPcco4oc2XZGBMsh1Fh0t2oGDzo/dBoiie/Px8xCo7figb0mtuVV9tl9gMP1DnO+2nh+3Y5Y5qEnl/O2r9/Quf2M5bPmF5k7Rh9Gwze8a2TsKxPq2CuPLRORG3TDEDFaWF4dozjCU4hv86rzjdsxvQyKO4AYXaOqO93hCRxtB5k7zIOnZKUmPW97KJXysSydoVIeqdMrhDplV/gv38NKqysbdoyLOFeUjz9GIGxYnNbs1yeXMBgTyuPz3WzoVzrj+Ri68/OmGXAeL6RmG1DwA7rw1SZGYLmOrSuKwmyU9YF1FvzjzAzT5+lRk7X5NrnmEY4IISrdSLuXqKuhJly9w+c5oYTrfp9bkGtqKfEKPg8vqtLjAiFDTQrmVw720s5myjaFLBMm4rGkc86KrmqIDIPo3O8vo6ra7Wad3upB97oS9xw/ccs3GF+0o/fd0dc/ueaMxBn1wL+N4lsW8tMg6YZefGsdVu/i3hCyKuxTvgLwMZU+vLOSX3IPIeMPYYPllaho51kRx1kZB3qtMooTu5eCVURoEUJliyzlee8+10RrXuqFFNcj1it/xAWg3lVG3b6cMaRCWh3/5claKY4ghW
*/