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
XCDuX4m7CmbA6+FYuF6O3wUnwfvhZfBhOA7ugOPh8zAb7oeT4RF4EfwEToHRlHcmbAinwbYwC6bAGXAQvBh65DhjjDpPIYyDpn1YWfcA31f9itU+7Cdh5v3HZzJefg498F/wIvg1vAF+A2+EJ+Ct8Ft4G/we3gl/kPGxRsbDL+BL8Ef4pRrvZN6+WmtgpmOMg/yFiR1Il9mv5cMhsACmwdlwBJwDR8FCeCGcC8fA+XAiLIFeWAoXwDJpZ+XwWlgB18KFcAP8FXwAVsIn4SL4DLwCfgCXwI9E/2u4DIaLvdb68GppT9fAvnAdvADeDNPgLTAH3goL4HXwcngDXAhXw6vhGngtXAt/DX8Db4K3wU3wdrgX3gFfgXfC9+Af4DF4F/w3vBv+ADfCMMr0HhgO/wjrw/tgE3g/TIQPSPvZDEfAB+GlcCucBR+Fc+E2WAYfg5XwcbgCboe3wh3wHvgkfBDuhI/B5+BzcA98BT4PP4F/hp+L/w/wFdjQxbgGW8I3YDv4V9gV7oe94VtwHHwBFsO98Er4IlwCX9LtXeYwwwds2ns3uf9Ohj1hD9gX9oIjYQrMgL1hERwA58Hz4UKYCpfAfvAa2B/eAQfCDaIn90syz5YwQfe/EL14OAS2hMNhOzgMdoVpkr7hEl8l4pH4qiW+GFgs8f1NZZ1ygi3lPixF7r/Ol/uu0fB96IHvwUxxz4AfwDL4IVwI/wFvgkegOn+YzFGV+a2cX71nLpbrl75ClesU2BNOg33hdDgFZsGpcB/MgZfAuXAmvBNeCu+Hl8EtMBu+BnPgYRm3PpLwX8B8aFyHBVDZaYbxsBC2gcUwBZbC86EXDoWXw5GwAo6DC+AkuBBOh4tgDrwCzoVXwnJYxf9XwOXwZrgC3glXwXvhdfAJOe9eeCN8E66F38DfwO/hTTCOMlsH28KbYTu4GI6Er8Bx8DU4Ae6Dc+BKWAqvgZfDW+BiWA2vgbfBP8Lb4QNwPXwW3glfg7+Hr8MN8CC8Cx6FG+EX8B4Y56K/gC3gJpgC74ND4WaYDh+CF8EtMAc+DIvhI/By+ChcCh+HN8An4Fq4Hd4Jd8J74DPwA/gsPAn3wKhw+gnYDv4ZdoMvSfvb6pB5vbCjPP8lOFT61d8xaf+fwmbibgE/g/1gDUyDX8Mx8AScDL+VdvgdvBp+D9fDk/Ax+AN8Fv4IX4E/wbchCVH3IWHwRxgOG5CmCNgW1oOSbubt6vE3KN2DONQYXgA7wyEwGQ6F4+EwOBFOkut1BMyCI2EBTIflcBRcAkfDVfBCuA5mwNvgGLgDjoWvwnFwn8T7Jpwo+cIt7zFkri3cZvMeg0dxypfzwbbwQum/smAfmAFHwLFwgrhz4EXwSuiBq+B0uE7CbYDj4N1wPLwfToEPwkwpT8LI3FXqTtLVCC6WdNWX9ETDATAGDoYN4VCYCCfDRtALG8O1MBbeLMfvhk3ho7AZ3CXh9sM4+DWM1/2yzJuE19v0yy3lua01bAM7y/NbG9gDtoVDYJKUV3uYCc+DebADnCvhroCd4FJxy3OjzDEkLzbPjWXoGSyHkbACNoIL/OzqHZLwJSq81a7eO2Jn9SDsb+jCYfADOBJ+CMfDf8BMeARK+2Gumjzf27SfSzi/C14Ko2A2bAhzYBzMlXF6lpRPHlT3gXA6LIL54r4czoblsBRWwLnwV3AeXCzH5f2HzO2i7dq8/xgWbqYjDQ6HI6AvnFfCjbQJN0jCXQCHwsFQ1Y+e+6LmChHODJMM1f23PDf9E3aCn8EUWAMHwC/hBfDf0AObEu9FcACcBb/neDH8AS6BP8Lfwwj8N8IouAVGwydgI/g8jIP7YBP4D4n3iMT7NewLf4SpkMQ=
*/