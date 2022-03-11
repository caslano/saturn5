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