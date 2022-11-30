// Boost.Geometry Index
//
// R-tree boxes validating visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_BOXES_OK_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_BOXES_OK_HPP

#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/index/detail/rtree/node/node.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
class are_boxes_ok
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    are_boxes_ok(parameters_type const& parameters, translator_type const& tr, bool exact_match)
        : result(false), m_parameters(parameters), m_tr(tr), m_is_root(true), m_exact_match(exact_match)
    {}

    void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if (elements.empty())
        {
            result = false;
            return;
        }

        box_type box_bckup = m_box;
        bool is_root_bckup = m_is_root;

        m_is_root = false;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() ; ++it)
        {
            m_box = it->first;

            rtree::apply_visitor(*this, *it->second);

            if ( result == false )
                return;
        }

        m_box = box_bckup;
        m_is_root = is_root_bckup;

        box_type box_exp = rtree::elements_box<box_type>(elements.begin(), elements.end(), m_tr,
                                                         index::detail::get_strategy(m_parameters));
        
        if ( m_exact_match )
            result = m_is_root || geometry::equals(box_exp, m_box);
        else
            result = m_is_root || geometry::covered_by(box_exp, m_box);
    }

    void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // non-root node
        if (!m_is_root)
        {
            if ( elements.empty() )
            {
                result = false;
                return;
            }
        
            box_type box_exp = rtree::values_box<box_type>(elements.begin(), elements.end(), m_tr,
                                                           index::detail::get_strategy(m_parameters));

            if ( m_exact_match )
                result = geometry::equals(box_exp, m_box);
            else
                result = geometry::covered_by(box_exp, m_box);
        }
        else
            result = true;
    }

    bool result;

private:
    parameters_type const& m_parameters;
    translator_type const& m_tr;
    box_type m_box;
    bool m_is_root;
    bool m_exact_match;
};

} // namespace visitors

template <typename Rtree> inline
bool are_boxes_ok(Rtree const& tree, bool exact_match = true)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_boxes_ok<
        typename RTV::members_holder
    > v(tree.parameters(), rtv.translator(), exact_match);
    
    rtv.apply_visitor(v);

    return v.result;
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_BOXES_OK_HPP

/* are_boxes_ok.hpp
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
*/