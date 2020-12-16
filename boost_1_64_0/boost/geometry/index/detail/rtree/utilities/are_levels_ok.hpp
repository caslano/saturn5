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
/5UwKQ8Jf57S3xMXcE1r/yS9H99a5X47zI1+qboO2dOU7TSzK4pYzGbaJdwKDf+Nyj+vyMsiIWWiycgfzWgf8Xys4lkeNj8sjGO+uMqL8o21CBJPFWyh/bzMZi/KZ+2ssYyusKikQunsxUfC63M5JHwS1Onk2vFmL8DohbJNovxPcLSB7g+K0TX7goMqbQPY783FO/yepIHjHEkYxHG+1o1ihtpN9AX/QGrjn59bXkE+5xUs8p3fY00bQx8ZEL+Bcl3P8PVXcjzWSZ4Dy7awtLzCSLboVFvzVVBeXlRaYkQt/oXinwT1eVUFmOW/m3P0OF+t8QzrSvm7bcvYjIt5Fqqv2xeBbxTPCRQQ3ZNrcfQMFoS4Y5SdNPH31GcugurHZkd3RCk81cyjV62pU+fX7WqaOv+/VdwVxPuyGTdhr4/uQNgYl6wvEf/x9cW+pWvZvOhO0d3pG+lnQ4+1H6j4qTvltq27kOPweypsq1q7Q5K/ivqS/zDXsiTSGFWvnismfLDDX6faTycKnfqR6ERMtOjsqtWp+lzrzFI6btE5IDquqqeknLWfmhx3sbk/20sx9eN0X3QJx/zPc7CB1MfyKymuBhGuWE4W2SNknXyqymiGqhOjcHOQLBX+HlUnjaVO2ov/AcSsk+VVRn3Ui24Q3VlVTOh6+Uadg7KXekm9QK0FDVkX/1L67YPqYle0L2/d65S3O1Q8HpW3Q6RvcLQvb1OteRP/7dE6byl1zdsfJW/xkrfDyj0Pd+i2dneI/G2I8V1Lf1f5i2506vxNUPFMVPnbTdpbxfjyF2HNn/ivj9HX04dm/qJOm78sdY5+Drfkb51y71T5m3WKPE5Veknq/P79xW5fGpdtMa/5+rVryjY4T7m+XvVhwwLGz70cYwzT9x0tOLYVlio96ziFnxqHNio/6xjlxq9Kh6sdk9oY59DHg8YjFS5J+8tYJOc6oY9bxiHl59F+1jFE9qsXP+nHzbyqcYKxg+OMHZK2aq0bMG5IGgq1v3XMaCHlSdrxs4wXyu+QbZ6t92cDGwffny03njkG6/sT2/uzosDnDqXf2u9+pHRBhf8zhvjrPu8M7r+KrPdf0lZU/Ja8bJKnrwJZVzcFuZywOYP12klfAc4vmJ/nXSTjUJJ5XWq7RuRHwkzmnFwbyt+Lglwfkid0ZG8feV5R7nG42aEYCbj/1/t6LVR6Iyjreo6uiOwbIvG59Rp1J/cmleqUeg8Gna7T2UGSPeVl32CVN90uF6hjOj/6Hpa0clzSallXLukIKO8D6l/Cy4kN51WU96Hg8i5Vq2KlvBe7VXkXkCgpb1+YeL8yKy3X97MB/kkB/agnwP+8gPv/ybX+p32n4HtGX6zanJFGuW51+ZAu0UvU5Sv3aNKPnKefBazlNTNBvk+bYH6ITLgaElRe5acpLwkzzL68Avy9NuUl/mrcOUjq1sVLn94pukN0e+MJNtIcd8T/ZLzPTnmEaae8njnsRNvdy0mZN1Dn6BFyfIlU/m3VeX7pevHqegmoA/mYuRIx9EqRRcTpCa4DMlPCdo9m/n7l9vUBte83SlSYaY7Oet8CXzxtbJ/9x2n/lvodxzzlLmJ+oVPvi3RLLOmsw54RvmuctMn1LPYurNeyyn83yX+N5D8RaSjS2zhm2u/nhV+BSnsvjjkd2Zm4JW8+ncQ627MgDtIgcfCOIG6o9R3BVzJn3X5dZeh1v/brXUOtBz7zdbb261FDr3O2Xxcden2p/bro0Otd7dejhlpnG3o9arRaF31oT9cJb163f8HTK+7//qmaI7NCr4u2X68bel20/frb0Ot17ddph16HbL+OOtT67TNfp22/LvrM1z+HWnf9ZqRxvNG+mFU=
*/