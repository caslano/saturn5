// Boost.Geometry Index
//
// R-tree count visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COUNT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COUNT_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename Indexable, typename Value>
struct count_helper
{
    template <typename Translator>
    static inline typename Translator::result_type indexable(Indexable const& i, Translator const&)
    {
        return i;
    }
    template <typename Translator, typename Strategy>
    static inline bool equals(Indexable const& i, Value const& v, Translator const& tr, Strategy const& s)
    {
        return index::detail::equals<Indexable>::apply(i, tr(v), s);
    }
};

template <typename Value>
struct count_helper<Value, Value>
{
    template <typename Translator>
    static inline typename Translator::result_type indexable(Value const& v, Translator const& tr)
    {
        return tr(v);
    }
    template <typename Translator, typename Strategy>
    static inline bool equals(Value const& v1, Value const& v2, Translator const& tr, Strategy const& s)
    {
        return tr.equals(v1, v2, s);
    }
};

template <typename ValueOrIndexable, typename MembersHolder>
struct count
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef count_helper<ValueOrIndexable, value_type> count_help;

    inline count(ValueOrIndexable const& vori, parameters_type const& parameters, translator_type const& t)
        : value_or_indexable(vori), m_parameters(parameters), tr(t), found_count(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            if ( index::detail::covered_by_bounds(count_help::indexable(value_or_indexable, tr),
                                                  it->first,
                                                  index::detail::get_strategy(m_parameters)) )
            {
                rtree::apply_visitor(*this, *it->second);
            }
        }
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // get all values meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            // if value meets predicates
            if ( count_help::equals(value_or_indexable, *it, tr,
                                    index::detail::get_strategy(m_parameters)) )
            {
                ++found_count;
            }
        }
    }

    ValueOrIndexable const& value_or_indexable;
    parameters_type const& m_parameters;
    translator_type const& tr;
    typename MembersHolder::size_type found_count;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COUNT_HPP

/* count.hpp
MmmX2XzdbNxOnPVHCNfuMLpV5oq5YDhSB31d84ddbiv5HZJRunZXDqQJvkMVOLFgqabchN3uot3ZC0MH6pys6y1Xs5OlFXxfwJI38lZTCGr93RiGu8kkN5a7dOPt6XpMlCoFYq7Qdk02aHa3qhNezUfVzWdVjjoj4w2XH9NaW4s6eDqEIJa6AY1zuo5/NMy/OtC/LtQfCvZvCPcHA55CPiCkzr+75HGTb+lg2vmYfNKWaS5a9UH1pskZ2Zwyg97W0e2wexCNGQlldP3QemLjQb162kBGMAJnYQsgE/tjf1MLxlH+PHyn+Q5ehafxSOlx17Z56m/u02eK6a+EVbs1xA/uSCBOwm7RXj+cRVRPSGU2Pt1/MKxwXhDE5Ee6KAj3XrDqZ8/gSS8wPuLkXwifE9vG4GjxZwEU7Pc708ORJhzatDdoDlS+IQ9Ql7oQBTbkdICVtLwQF/rCz3lUcE+CE9bbSZQuuww3d5jM6H7TtYgtL5cjODdiIsUORa4a8XTBlIjINqm4Pf6A54fg6lyNfhhPQW74+oLQFHUuCFTXdEmIcFPoWg1OpEuZ5tw2xTKjU9PC2UbYYJlkEO3ynSjmCmkKla7pHC9P5d0WCmxm1p7tIndf97egRHBL0QEUO13aYXrwyt2SuQHfLuyg
*/