// Boost.Geometry Index
//
// R-tree node children box calculating visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_CHILDREN_BOX_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_CHILDREN_BOX_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
class children_box
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::box_type box_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    inline children_box(box_type & result,
                        parameters_type const& parameters,
                        translator_type const& tr)
        : m_result(result), m_parameters(parameters), m_tr(tr)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_result = rtree::elements_box<box_type>(elements.begin(), elements.end(), m_tr,
                                                 index::detail::get_strategy(m_parameters));
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_result = rtree::values_box<box_type>(elements.begin(), elements.end(), m_tr,
                                               index::detail::get_strategy(m_parameters));
    }

private:
    box_type & m_result;
    parameters_type const& m_parameters;
    translator_type const& m_tr;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_CHILDREN_BOX_HPP

/* children_box.hpp
yuaVvTGuMPTCIgH77zV3BGR7vy40rlsYYLUG9BTs79Jmv67B2+qPPun9/hFP8o4iAAHwF6nokcVxAyRnnlFvu1o3i/KTXiKjb1xVA1drdVeI1BEWFVqmj+rZQJzGv0f1EGOV4xpKscl72CXin2c+dwUe8fR/1yG16owdiPWDivs3hwjqCDTtBVs+wm2gcQvQ7mzcXNJILSsewVXg/pK6IwFzteB2k3hhX7VaYgNJ7DDBWdqR2Dk1LUZsZKm/w064/Ez7DdeR4Mpwd6JrqRkaO+TVoB2TM9hxlcB9xSy2FRwuAvpHLXx9jWx7jWmD1XJ71yDDSGhtLCYb32cXmNvCppsCXCXtb+7U9WcZc6NJ5EMadDOipYw+H1Sak0Ut4rvSIweXalCSTjPa2iP8/Nch8eGGnlgvzYpMYqkps2RGSkUklExmtBzBh46sdh2+8w31d3oivqeDGOxSsXkmd2XorspQ4qSGjo8H0FHYU3PqJB2JE0YgT9CliqWj4vWLxPo+GstP3sive+cmlFg7XEqJzkX7KYtmEKk7PMHXGELY899KjgA0ibMZxRdmc3TIkM3SZHLR5vJbkVZohyvmpM1q2LGRi1xaDXGpt8mKuCnr4isA06ek5XsWHUTZxh4h+q8F+iJngp35+UGoz+ls
*/