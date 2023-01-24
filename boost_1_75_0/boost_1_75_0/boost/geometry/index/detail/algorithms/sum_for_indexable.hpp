// Boost.Geometry Index
//
// Sum values calculated for indexable's dimensions, used e.g. in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct sum_for_indexable_dimension
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (sum_for_indexable_dimension));
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t N>
struct sum_for_indexable
{
    typedef typename sum_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, N - 1
    >::result_type result_type;

    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i) +
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i);
    }
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag>
struct sum_for_indexable<Geometry, Indexable, IndexableTag, AlgoTag, 1>
{
    typedef typename sum_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, 0
    >::result_type result_type;

    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

/* sum_for_indexable.hpp
cd6j087HF44zB8S7x1HHM6d38y3Wbd9ZKvhOPnQyUhlNcvIxxVx0DpCtWrNbvy9gq5Bo9TA5/00XMHid2boNgdedGvdNeNqmcvKa38OnLVfuVRyTnJwLbGmVrU5sSXrygOrmXaMkmy07psfKDElO8o5qMuxHgabi6Z0jpwGxg40i9fKBnO2diKuIhacMplZn4iftw7KO4fdkwC7VmZ8BK5JnRa9Psv0PUNIJOn5FhhB1LJEvs1Vmiy02CIC+lTVG5GQs08YBbnpHtgkA4/jyVNIm403ot0CNOwJ85wlsRR4BjvfYo9r+c1nkW8Z6Ul8f+kjJMxhMetTo4/aV9DXj4ogvD5q90trcZceRhxqLFJsWggEa+QUP3p37Z7fxPkCsw6O0zsxzuEvb/dsNB42E2X70qZ2t9nt6uzrzYBUjo2p/ZoPBkvthQixllULeUMymCn9hAfzTZRyzBMPGkiM7VmQtUe6rGvzh6uYDcY6aTm295prKZZv0Ns6SSzHYFo/GMjZjvXPZWfhuD4LsWn49w/P9TTF9j/+50cKk1GWOhBdnAL4//C+RyJEPxXk+O9Xx/OMzxvRXsPayPR0JEzJ+Pd+8IpEOnRPHYz5XrsG+2DiARA4qj4fAXAmZ2RsgmaF4zW2OiJUiUvMUofF7/h6WNUMwR73zU9LeYZgr1tUxpOPdDwgdQ9m7vdCxQATBZdGnP1zKXt8JcC5zvPS8
*/