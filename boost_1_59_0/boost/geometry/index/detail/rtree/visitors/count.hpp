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
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
*/