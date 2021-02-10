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
YXAuY1VUBQABtkgkYO08a3PaSLbf+RUdppIBjG3syczcCol3MVYSahxwAU42m0mphNSAEiGxaoHjXee/7zn9UktI2DjOnbm3hlRsUHefV593Nz5sPNyrQhqk8GXz/za84DefdRFHn6ibpDNs+4aIfzDzd/hdBOyQpNNu7DopnnZDanyaLaE9x/e2XQTwd8SLPw5x9u82voUnMBVnd6PldezP5gmpdevkuHV0RPbh1/FRk5w5oU8DMkpoOKHxrEmee/zJ3+fOly8HjJ40CU2IExwUwmk1yevoyok90p2vYO382v17tKRh4DnLgyienUgCxnOfERZNE5hLCbwPfJeGjHrEYcSjzI39CXzwQ5LMKZn6ASXdwcX7Xv9Vk1zNfXeOQK6jFWHzaBV4ZO6sKYmpS/21gLF04oREU1gOwD2fJQBwlfhReAC4KUlovGAIA9E7AYuIs3b8wJkAIich8yRZsmeHh+4qDoDnQy9y2aGrmD2YJwvOPwJ4D0QsnGsSLROSRGTFaJPgzCZZRJ4/xd8gRni4XE0Cn82bKTWAKvQOo5gwGgQIC9b5lAmyKRlJ8TRxGlkCxX6Cv1gUMkR1NY8WmYkgR4QyXcUhIAI5wCQvAjE3ySr0aMwnc84VCilTLuCDsq1J6fVIFAIxpNoZ
*/