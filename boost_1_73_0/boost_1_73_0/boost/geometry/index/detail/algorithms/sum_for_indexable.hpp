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
tal7ZLaErvbmWVpRgPDi/PxP/kjEW1njG75siBIyqhGAUaOou2ohevcWLRpGNVjP+4KIRKY1FQY+Rxi6BRFQaXlBl5wOmVV4i7XjTLw+UJfp5k05nyLtJ9cxo90DIfgTJWtMkdE442xl6GkG2BP7Si7yTybajlhX4yCnujmbccYA341y4z63gpHnqitGwUgmhVMfcNKQBekMzjIKy68W808wCdxrjKMQeZsHNr3BMdNQTNsLU2PSE2wHhfbcSIeFmscUpXP8ZaerleNoLjNrnjIrxq07c97HZ7dw5YrbxKjEeKAsYjeod8q2IDNpVac9wnfudiA7dukIEvVA/LdMsietk8vMWppXf2Hvqty/NrXcpWXK8CfOSt0RfyaaA/aTl/DM3ZNfRm93f9h/PTp8//bV8DjKEhmGlq6bO27/+ADubN/K46gBzWpnAePUfEyYRGdy+1gyYWB8dRzHa8cdV7Br4xrpGurxPIWLs8itmXTGeoIfAg26CxobSHTRjcaOY7ZWc2lLhJVxJk7y7FjuwsudU5yTGtKKfHxIUoSNgPM2naGGz6pwBE2Q6XCenoNksmXyA1garLtPz2BkMocwK4cSNWnCkB45GaTxE0eJ9SnnQ8pCvBbxVcbOnVyDoqsnDRm+JdRGdtCrDO0o
*/