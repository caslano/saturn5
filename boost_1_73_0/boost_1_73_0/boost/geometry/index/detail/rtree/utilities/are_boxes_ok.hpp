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
W5JsjBTP45Za+gNhE+C/9rELvgVAwrhDwoSQ9svpDetL9l2aPsmeMi/RpjvZFOpbXxHxft7Smvp/ZG59+fpn0Z6icvj5F39P8/J0nRapGMJgEMo45Onjw7UfF5vnbthtatMw52u/37Trm6+z7Vrm62yfNEqM/xuif1br7wLHcn0JiZp+uJJ+hmx06I9WuFf+BVBLAwQKAAAACAAtZ0pS1dTVoS0EAABACgAAGgAJAGN1cmwtbWFzdGVyL2xpYi9ub25ibG9jay5jVVQFAAG2SCRgrVZbb9s2FH73rzhIgFQKVCvt09pm3VzXToy5VhA5DQIEIGSJsrjSpEFSuWzZfvvOoazYzvVhVZCQks73ne/cqMT7P+/qwD68ejH/y/DC1SNOjP6T5+5pa8buoPlB1CWurzmJYQ25YyG8DrmDwEPYyssh7Rl7zdElaaM/MSEvGW3xCcII2dfLWyPmlYOgH8K7Dx9+gbfw/uD9QQRfMyW4hNRxNeNmHsFh4Z/8XmU3N13LP0fAHWSyu6KaVsKC1aW7zgwH3EuRc2V5AZmFgtvciBneCAWu4lAKyaGfnFyMJkcRXFcir4jkVtdgK13LAqrsioPhORdXDccyMw50iXAkL4R1SFg7oVUXfXNw3CwscZD7TFoN2VUmZDZD
*/