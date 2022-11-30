// Boost.Geometry Index
//
// R-tree visitor collecting basic statistics
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP

#include <algorithm>
#include <tuple>

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
std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, std::size_t>
statistics(Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::statistics<
        typename RTV::members_holder
    > stats_v;

    rtv.apply_visitor(stats_v);
    
    return std::make_tuple(stats_v.levels, stats_v.nodes, stats_v.leaves, stats_v.values, stats_v.values_min, stats_v.values_max);
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP

/* statistics.hpp
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
*/