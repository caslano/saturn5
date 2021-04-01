// Boost.Geometry Index
//
// Rtree utilities view
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_VIEW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_VIEW_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace utilities {

template <typename Rtree>
class view
{
public:
    typedef typename Rtree::members_holder members_holder;

    typedef typename Rtree::size_type size_type;

    typedef typename Rtree::translator_type translator_type;
    typedef typename Rtree::value_type value_type;
    typedef typename Rtree::options_type options_type;
    typedef typename Rtree::box_type box_type;
    typedef typename Rtree::allocators_type allocators_type;    

    view(Rtree const& rt) : m_rtree(rt) {}

    template <typename Visitor>
    void apply_visitor(Visitor & vis) const
    {
        m_rtree.apply_visitor(vis);
    }

    // This will most certainly be removed in the future
    translator_type translator() const
    {
        return m_rtree.translator();
    }

    // This will probably be removed in the future
    size_type depth() const
    {
        return m_rtree.depth();
    }

private:
    view(view const&);
    view & operator=(view const&);

    Rtree const& m_rtree;
};

}}} // namespace detail::rtree::utilities

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_VIEW_HPP

/* view.hpp
kKIdWRN2pudEkggg3sjWtPHuItVKB7I2Yl0aw/y5ZQ8O7lzSZnimnSVLu3DTnzmRS11eYj24mDMXfQEH1ei3Mr51TJKDA33DBuJBoduaqcDDS446tUK4+iDR/HpK8FmVYjvRH1cYWtHg0+qDUAdj846btF0zVVxE6GojxOKuFjb0X3mJ6sJ2f1bM3e9jNz1hugDjWgFH1NN9QCO0zgnTPaz5+5uSY5fUC7uXB+kXJUZ6z46UZ1V4qCMnGW3tNFNVgFcWTsK7w9QuN+ndITWnxiU6CFbsfcjKDJZGZoHEotL9MOQkj7+df4FUMPSG1qDxdwYOc22jSuB8uugKHUThizC72wbFzRVuhFVWvzIhPPRwkDygC7BiPxxpFswDDl3DbIDoJkgjdORIMwU+jF9edZmO4fM4GIw4tW2R6gTmwDolCrZzQKEDWoN69Yiwy7RknF5OsUpFQMDr3fM1S233QO2wFuz92occiTO8hP9sZMhoXL/PxQyK7N7LRwfehicpMHA84UrPz+us0F5aNrH3HhA2oMGPUnVcojVq64ZNsu2Z4aDmcuRuhJ2/Bw==
*/