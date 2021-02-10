// Boost.Geometry Index
//
// R-tree deep copying visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COPY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COPY_HPP

#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
class copy
    : public MembersHolder::visitor
{
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef rtree::subtree_destroyer<MembersHolder> subtree_destroyer;
    typedef typename allocators_type::node_pointer node_pointer;

public:
    explicit inline copy(allocators_type & allocators)
        : result(0)
        , m_allocators(allocators)
    {}

    inline void operator()(internal_node & n)
    {
        node_pointer raw_new_node = rtree::create_node<allocators_type, internal_node>::apply(m_allocators);      // MAY THROW, STRONG (N: alloc)
        subtree_destroyer new_node(raw_new_node, m_allocators);

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        elements_type & elements_dst = rtree::elements(rtree::get<internal_node>(*new_node));

        for (typename elements_type::iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);                                                   // MAY THROW (V, E: alloc, copy, N: alloc) 

            // for exception safety
            subtree_destroyer auto_result(result, m_allocators);

            elements_dst.push_back( rtree::make_ptr_pair(it->first, result) );                          // MAY THROW, STRONG (E: alloc, copy)

            auto_result.release();
        }

        result = new_node.get();
        new_node.release();
    }

    inline void operator()(leaf & l)
    {
        node_pointer raw_new_node = rtree::create_node<allocators_type, leaf>::apply(m_allocators);                // MAY THROW, STRONG (N: alloc)
        subtree_destroyer new_node(raw_new_node, m_allocators);

        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type & elements = rtree::elements(l);

        elements_type & elements_dst = rtree::elements(rtree::get<leaf>(*new_node));

        for (typename elements_type::iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            elements_dst.push_back(*it);                                                                // MAY THROW, STRONG (V: alloc, copy)
        }

        result = new_node.get();
        new_node.release();
    }

    node_pointer result;

private:
    allocators_type & m_allocators;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COPY_HPP

/* copy.hpp
b7MPrB9MARTZG+L4IZEz+tklCEW47w1R2BzWD/WGjyGtB1EW69iwOybTAQSCqWvbpV2nhWtByIm1MnPnSVRvCYMwl8S42BOBLoQGCClQRPPexj+rpYtDxw0jlX7hfpK3dDLRTj4ocxmpREVodsIqjmMARyJRYGZV2jOq8ty4Y7VaasCsbAFB7ZTusp07+rSkWU3RU3FbCeqXdSVw5oA6aYWrXgqOd1IDNcVM6lDTEVCioRQe0J5Mz2o+iMkOnPXZoCO4xKXwZhzCb5XLHZFA6CO89zA98yEbHYlhzqr5hOxxqPUB9ghZlVqhJaaYdM05ZS4tl1iqieTKYHLNj5Q54IJBHDNK4Jjr/Mlke7bkk57x4eCSEdWn6PdKFY12nP1I2lxGAhEvfDiHjBMG53nMq4zx6iXym5WgXIRAj0qqNTUrV8SYoxPpoaTLtJ4BGo1zOx/C+rLn8g3UEUGbizZMWJL49beGCs3ZFSsdThEX7N73rnc1yQbnfi2cWW1zankdvKrPlZBr5rkeejW6hKk7noGvgT2N7Cc7BH35Ak+6bEPNOir74U66Dev/Bt1RQJh0x2vp99N0RkKveaOGqawlbNLiMZxPL9+ev20H/+pYYpcX2gwAPhzr+jqn+uTrfLgXWSfrAdiKiG2xpp3p
*/