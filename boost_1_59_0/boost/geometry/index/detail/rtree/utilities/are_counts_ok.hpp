// Boost.Geometry Index
//
// R-tree nodes elements numbers validating visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_COUNTS_OK_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_COUNTS_OK_HPP

#include <boost/geometry/index/detail/rtree/node/node.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
class are_counts_ok
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::parameters_type parameters_type;
    
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    inline are_counts_ok(parameters_type const& parameters, bool check_min = true)
        : result(true)
        , m_current_level(0)
        , m_parameters(parameters)
        , m_check_min(check_min)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // root internal node shouldn't contain 0 elements
        if ( (elements.empty() && m_check_min)
          || !check_count(elements) )
        {
            result = false;
            return;
        }

        size_t current_level_backup = m_current_level;
        ++m_current_level;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() && result == true ;
              ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }

        m_current_level = current_level_backup;
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // empty leaf in non-root node
        if ( (m_current_level > 0 && elements.empty() && m_check_min)
          || !check_count(elements) )
        {
            result = false;
        }
    }

    bool result;

private:
    template <typename Elements>
    bool check_count(Elements const& elements)
    {
        // root may contain count < min but should never contain count > max
        return elements.size() <= m_parameters.get_max_elements()
            && ( elements.size() >= m_parameters.get_min_elements()
              || m_current_level == 0 || !m_check_min );
    }

    size_t m_current_level;
    parameters_type const& m_parameters;
    bool m_check_min;
};

} // namespace visitors

template <typename Rtree> inline
bool are_counts_ok(Rtree const& tree, bool check_min = true)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_counts_ok<
        typename RTV::members_holder
    > v(tree.parameters(), check_min);
    
    rtv.apply_visitor(v);

    return v.result;
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_COUNTS_OK_HPP

/* are_counts_ok.hpp
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
*/