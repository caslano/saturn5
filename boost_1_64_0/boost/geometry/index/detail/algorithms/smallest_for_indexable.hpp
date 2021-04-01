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
jp/4MqyI7XUAb+QWUAhLjzsylzJmuB2EU9EbJvtsxMknTuSSEs6I3sqWda9/BZ/uiqJ3xvnnNGXBbzEpMwiZpd7ky2UK1qnL5fT/WcfkGbaEbUmtTzGU1kvYCecY6CMWwZ2Ow9ber2zBkgTGbEiNHdsrNcljzJUQp53P0LvsSgmsKGa4rD1AJibIRRVde+VCtJFAZ+Pv3JmFEplIN8e82p0c4DGvf3pBA7sXP6V1C+mdNKdD5ANKON9qPRWWlecRvRoUIRdZJ9soNIOS7EzvgWU4F3+bipwtF0lbksUVxe0XF7+qEx4+ez6C0KesrrtEBQxcKLidMwYTCfqDnsR/ukyelEWIwqTdIE7MH5c89Us0JiNRru+I086gOd0OrqZv5ExOaN5mx9HMKXTWhDGmdFIEReixxx07zAa8qCg+ylyTNl3J++0nkzU4zsoPAiGZtvgQzmX5Zr7BsMnNKaHNVwc494fSdUkiBCUdxTZdPY5G7zyFl27SYwjj1NcnxMZgUXy/aOxi5+Om1M3nsdq3PNZtGW7PvZ56Q/OqZyaqQgOo74hOl//JNnSeiA==
*/