// Boost.Geometry Index
//
// R-tree visitor collecting basic statistics
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP

#include <algorithm>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
struct statistics
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline statistics()
        : level(0)
        , levels(1) // count root
        , nodes(0)
        , leaves(0)
        , values(0)
        , values_min(0)
        , values_max(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);
        
        ++nodes; // count node

        size_t const level_backup = level;
        ++level;

        levels += level++ > levels ? 1 : 0; // count level (root already counted)
                
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }
        
        level = level_backup;
    }

    inline void operator()(leaf const& n)
    {   
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        ++leaves; // count leaves
        
        std::size_t const v = elements.size();
        // count values spread per node and total
        values_min = (std::min)(values_min == 0 ? v : values_min, v);
        values_max = (std::max)(values_max, v);
        values += v;
    }
    
    std::size_t level;
    std::size_t levels;
    std::size_t nodes;
    std::size_t leaves;
    std::size_t values;
    std::size_t values_min;
    std::size_t values_max;
};

} // namespace visitors

template <typename Rtree> inline
boost::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, std::size_t>
statistics(Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::statistics<
        typename RTV::members_holder
    > stats_v;

    rtv.apply_visitor(stats_v);
    
    return boost::make_tuple(stats_v.levels, stats_v.nodes, stats_v.leaves, stats_v.values, stats_v.values_min, stats_v.values_max);
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP

/* statistics.hpp
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
*/