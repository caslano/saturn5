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