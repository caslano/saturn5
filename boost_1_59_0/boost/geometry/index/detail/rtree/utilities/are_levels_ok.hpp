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
+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
*/