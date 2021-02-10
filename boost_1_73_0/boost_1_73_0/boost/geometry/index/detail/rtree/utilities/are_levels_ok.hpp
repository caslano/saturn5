// Boost.Geometry Index
//
// R-tree levels validating visitor implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_LEVELS_OK_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_LEVELS_OK_HPP

#include <boost/geometry/index/detail/rtree/node/node.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
class are_levels_ok
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    inline are_levels_ok()
        : result(true), m_leafs_level((std::numeric_limits<size_t>::max)()), m_current_level(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if (elements.empty())
        {
            result = false;
            return;
        }

        size_t current_level_backup = m_current_level;
        ++m_current_level;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() ; ++it)
        {
            rtree::apply_visitor(*this, *it->second);

            if ( result == false )
                return;
        }

        m_current_level = current_level_backup;
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // empty leaf in non-root node
        if (0 < m_current_level && elements.empty())
        {
            result = false;
            return;
        }

        if ( m_leafs_level == (std::numeric_limits<size_t>::max)() )
        {
            m_leafs_level = m_current_level;
        }
        else if ( m_leafs_level != m_current_level )
        {
            result = false;
        }
    }

    bool result;

private:
    size_t m_leafs_level;
    size_t m_current_level;
};

} // namespace visitors

template <typename Rtree> inline
bool are_levels_ok(Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_levels_ok<
        typename RTV::members_holder
    > v;
    
    rtv.apply_visitor(v);

    return v.result;
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_LEVELS_OK_HPP

/* are_levels_ok.hpp
yE1zg6NV5zlNge9VLjccbfRYwibYL+Q07HS8yoW2zp9wqL9W4gau8CQQdBT4OCmsUmZzS379Bn4F69szaNM0ZEeD6XAcwUFIVqIMWrGhz9RK7iNU2qAa1jvY0LYR5MuoPQj+3cAh8KnYt0dlFbiWdHS9FDJGel/R3+AdfMSMr4X5gV7rasgj2PPQl4Q0pX4o51yoQl+vJNTKijmiQGocjafEnI1Jztn4oaCmh/+HrH7v2+BRrnoLMc8aac8q8oI29YxIT/qMniCvMgP74Yu6sNSkKjmZ4nw86twvPEk3NM1e04MnEcnAD+q9nDQZryaP9vceMF2zCKz4i+symLVdZXlnF4AbgzONR9/WcYUfY1fpAq7xX4RS41cxxg92EaPLnfbc/KfzH1BLAwQKAAAACAAtZ0pS6DAy/EYCAAALBQAAGgAJAGN1cmwtbWFzdGVyL2xpYi9ub25ibG9jay5oVVQFAAG2SCRgrVRdT9swFH3vrziCF0BZw3gaG0LrShkVqEVtEaqEZLnxDfHm2pHtQJH48btOyxASqC84SuzY93z43ji7urSKSlwMemeDiejfTK7EaDz6dTXuX4qLzi6vaUsfLecHn9c6OMDWJtpbcOO+RVx794eK+H60EM9YX4y6436bSI5XyLPYx3bI
*/