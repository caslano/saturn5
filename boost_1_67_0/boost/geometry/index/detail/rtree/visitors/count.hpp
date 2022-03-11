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