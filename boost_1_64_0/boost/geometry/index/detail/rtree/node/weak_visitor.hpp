// Boost.Geometry Index
//
// R-tree nodes weak visitor and nodes base type
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_VISITOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_VISITOR_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// empty visitor
template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag, bool IsVisitableConst>
struct weak_visitor {};

// node

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_node {};

// nodes variants forward declarations

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_internal_node;

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_leaf;

// nodes conversion

template <typename Derived, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline Derived & get(weak_node<Value, Parameters, Box, Allocators, Tag> & n)
{
    return static_cast<Derived&>(n);
}

// apply visitor

template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          weak_node<Value, Parameters, Box, Allocators, Tag> & n,
                          bool is_internal_node)
{
    BOOST_GEOMETRY_INDEX_ASSERT(&n, "null ptr");
    if ( is_internal_node )
    {
        typedef weak_internal_node<Value, Parameters, Box, Allocators, Tag> internal_node;
        v(get<internal_node>(n));
    }
    else
    {
        typedef weak_leaf<Value, Parameters, Box, Allocators, Tag> leaf;
        v(get<leaf>(n));
    }
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_DYNAMIC_VISITOR_HPP

/* weak_visitor.hpp
e6spZ82snlyTasplVVMut5pyFdWQy8SsVblaLu3nLdqLzbdhTfhOyHW4VcPNcGn/79jzUvg+bA8/hJlwL+ys9q5qz4IfweHwY3i2uo+Bn8Jc+BmcDD+AU9R+GKZ7dW9d3U+afMiYmwjtv1aUswHsDLvALrAX7A4HwB5wFOwFx8De8ALYB14I+8KLYT+YA/vDSXAQXAvPgHfBofAhOAI+AUfCp+Fo+BwcA1+G58NX4KXwA5gLD8Lx8Cc4Adrz/ImwASyCp8FiOBBOh0PhlXAUnAFvhjPhGjgL3gGvhvfAa+AmWAGPwbnwRzgP+ux5KawJF8Gz4W/guXAxHKv2i9SeC2+EE+ESWAp/Cx+HS+Ez8Ca4DS6HL8Gb4ZtwJXwP3gI/hKvhQXgr/A7+DtoNbw2MhbfBWvD3MAMOgt3hnbAXvAv2hevgmeo+XN1HwnXavvcG9wmF72o7rQ93azv9XPvjgzAdHoIt4bcwE34Hs+AxeAb8Hg6H/4Cjoc/WA/TDchiAV8IYOAvWgNfAODgfxsMbYE24BNaCy2EyXAVT4G2wLrwTpsF7YH14H8yAD2q6z8JGWs5Ys5ch175eB434/YOWc62ORw/AWLWfBjfA4epeCh+Es+FGeD18GN4M/wQfg4/DnfBJ+CbcBr/T8PZ9/yuwJfwL7Ah3wR7wVdgHvg4vhm/ADWp/Du6GL6k7Y6G4r4W74X3Qdn8Zvg0/hu/Bz+H7EF1YH8BacK+Oi+hS95fTe39kk+Bi1Ue+3i9PhD5YCGvAIpgIy//F3pkHRlWcAXw3m5BAAuSAJdwBuQkQIBwiR4CA4V4kQFA0CUkggZCsSaBBQQKColKkFTUqtVSxoqKgooKgYsWK1gMtVVSqaEFQqUarFhW1vzfv28m+3bcQ0Lb/EP347bz5Zt5cb+YdM/PBhnAujIPzoFuON4PFsCWcD1vL8TawRJ5nS2FnOd4FeuEAcX8J1+q92lTeVPqM+lgh72+/c5rx/wh7wp9gX+ggf8OAE2bCcDgHNoRqPzZ4PWwM18BY+AcYDzfCpvAR6IZPwuZSn63gCdgW/gDbqPo03ZGwHYyB7WEC7ACTYGc4EnaBGbArHAe7QQ/sDqfAZJgDe8DLYQosh73hMtgHXgP7wt/AVHgn7Ac3wUHwTTgEHoZpMIIyS4fxMAP2guMh4vDAYpgJr4NZ8D54MdwCL4GPwxbwT/AyKM9JsgcVZWLzPuEhuQXdCiPhwzBG3IlwmzwnPSbPSZtcvv2FOFbPjK/Mofo59feOy2w3R+BAeFT6iY/havgJvBV+Ch+FDp5DdgOnPPe44CEYBWtgPdiYk8XDeJgAE2ET2AIeN84H/wm7ws9kXPkcjoY1UK3FgnPhl7AE/gsugl/BX8Ov4W/hN/Bl+B3cD93G8xZsD4/CLvA47Aq/hN3g17A7/DdMht/BC2BSGPULqUvl9sDhsAJOhzfCzfBm+CC8FT4Ed8Et8BAcCj+CGfB7OAYa/cNYGAHHwxZwEmwHL4Id4BTYB2bCQXAqHAynw8nwYpgFL4WXwMvgHJgN58McWApnwRWwAF4PC+GvYRG8Dc6Fv4fz4B/gfLgDeuEzsBzugRVwP1wAP4CV8Ci8An4Hl0BnOI0MRsFlsBFcDpvDlbAtvA62g9fDrnAN7AnXwUHwZjgY3gFHwvVwEtwAS+A9sAIOgTfA38E7YQf4EGwF/wZbw6OwDYyL4HqAKfBhOAw+AtPh43A8fALOgI/CXLgD5sEn4TXwOfg43AOfgq/CN6FxnbwNj8KP4RscT6jHeAGT4POwPfwznA9fgmXwL/B38GW4Udz3QSP8Ayq8eb3udsh+JPAmp3m9NlXXNX/qejb7+0dhsnEc9oaPweE=
*/