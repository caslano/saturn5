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
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
*/