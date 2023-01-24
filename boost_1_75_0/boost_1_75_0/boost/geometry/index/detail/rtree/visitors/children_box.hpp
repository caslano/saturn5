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
ex57VXtjiZT97dUTa2oEtt+nkD8Ki7N5OWpfY2gkB8yHI3u9sp22Nol7L1yubUiNv1J2ZpX7oekCx0/e66KdiMdEvcHir0MtRP3hBhcbNKaMV5y7znsGCKPOu/h9X1BrkMUoaNsYcBree7IkHI8IeAIQuihAmF1KS4S35mU7iG8Yjp8SOG6Yr1z6NkaBXCdGPwFynV07Cs0cWRHr1uc2QG0X17oWLRuyKgfLcuKYpqZQFJtM7cwB7ab2YpH15bFJozTMW9YE5wUhI4ysSSeWe+IFb90FDs5NOVS2xerHBwbup6W7oe3tp57c7UuZNNZK03aZdRtCgkdue0onCfXxZpDPneyZSvlHiRRU+7VwdrcNo1yjAYdMvV4moV+Ubu2HqBBRcKBHvn3fRBDZIuVf2KFCbEfozrbh9JfX+0KnAptZi2GMzsyD8hERaLyv3gKduJ1zRCwyylYxaFn0bSlcNeLUw1aTZLjq4XrwsEGGEMUIHXoPS/HPP8Lk7PgmWMQ1qStmJ1XzVJDTFBA58HX7tC8GZSnSBoOcmVMDxbLptUbYsVHHwcyKJOJSicXvqt9RqivfMqkLArnNVrWMYOn7pzhgs1MygKwkQo4YuC/7CYjQ+1neP10pK2u2YCheL4RSov/ECamowjJ8bT5xWCUc+WtoVIOWOcdPx10+Lu9Fnh8Eheyvgbhd2FuBDGSEup8+W/MDglyspuvI0or7
*/