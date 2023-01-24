// Boost.Geometry Index
//
// R-tree leaf node checking visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
struct is_leaf
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    is_leaf()
        : result(false)
    {}

    inline void operator()(internal_node const&)
    {
        // result = false;
    }

    inline void operator()(leaf const&)
    {
        result = true;
    }

    bool result;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP

/* is_leaf.hpp
B3O3lhT3qiYaY6mZ4VZzJsMcC89BTO5duNUGRY7JoLYh8/x3lMRMtE2Y9aqtGb/vOe+d0povSPJ6EhprsBbR9QINDbefjdlyRb6D/5xfJv9E0yBxksHLrdb5ldprqALH2++45lWNuLpWvjQrfXum8bMH84NwNSrHRnf5LEWq67cpHm/fWBYZv9gwvUPbvLDG963J+clPuh4RyRFb00jzMaQIE9LMIf3DByY2MKRUVRePeWnyw0HlNz17F+uqqlmEh20waL+BU4hkcjE4GgzBX8eNwziRS51kfTEuhXHhXhZa+Wa5nsRkQyn25K912qiyjI6DYr+XLdQ/hthCzBIlNGgLBCAY7uUOU87FzFNnBVoLb5v78o/oUmjnk44jj0dnx8m84nUJbntQKXWcXlO4F12/f2z0YZP8kINTnqbWoS5KTANO4lQ2t9siiYxpRMTLTIKeGTqSw7JgP324JPn5uNPuyvm4i22+zLqTmI5cOoC+HkW7sZkOeuhKI5t/RBqMXb3mX+7ezPbA1LQg1hKiptFZoErpo8QyT70zx9kjp6GL9z7xA28BTVal93GPXztwolCMuc5WS6BaJKSXqa4t1tQTtea5W+WsERiMnmbluytYYFeM6F632z5i1UsSsnrX1rVzkTTx1Zl7U7LbI1Jl0sg2ec2wJsL7zNFwwwIzZTbmu/QyPp5quHGA0Cusp91EQJ8GXXlcbVriJ7+o
*/