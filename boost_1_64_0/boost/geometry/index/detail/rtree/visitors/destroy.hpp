// Boost.Geometry Index
//
// R-tree destroying visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DELETE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DELETE_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
class destroy
    : public MembersHolder::visitor
{
public:
    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename MembersHolder::allocators_type allocators_type;
    typedef typename MembersHolder::node_pointer node_pointer;

    inline destroy(node_pointer node, allocators_type & allocators)
        : m_current_node(node)
        , m_allocators(allocators)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_current_node), "invalid pointers");

        node_pointer node_to_destroy = m_current_node;

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        for (typename elements_type::iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            m_current_node = it->second;
            rtree::apply_visitor(*this, *m_current_node);
            it->second = 0;
        }

        rtree::destroy_node<allocators_type, internal_node>::apply(m_allocators, node_to_destroy);
    }

    inline void operator()(leaf & l)
    {
        boost::ignore_unused(l);
        BOOST_GEOMETRY_INDEX_ASSERT(&l == &rtree::get<leaf>(*m_current_node), "invalid pointers");

        rtree::destroy_node<allocators_type, leaf>::apply(m_allocators, m_current_node);
    }

    static inline void apply(node_pointer node, allocators_type & allocators)
    {
        destroy v(node, allocators);
        rtree::apply_visitor(v, *node);
    }

private:
    node_pointer m_current_node;
    allocators_type & m_allocators;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DELETE_HPP

/* destroy.hpp
NQjW/eaCx6ATfgtjYD3zXoMtYBxsCWvBzvAQ/ruKLu9RmXck7XeY96h1cOeBibABTIINYQpsBT2wLUyGZ8B6UK0Hh+eKu0zYAI61dN1e7ZTr3himvbqwrnWdi2BzeDFsASfD9nACPANmwf4wGw6EOfB8mAeHwXw4TfxVwElwnuiLRT8CDxoy/wOmynvdRnIPmH9FuGsKi2ErOFXakRI4Cc6G18PfwZvg5dJuzpF2Yy58DM6DO+ACuAsuhB/Da6DDfD8GW8FrYUd4HcyCN8DZ8FZ4FVwGH4Kr4TPwTvg+vAt+BO+G38G1MM58HwZT4L26v5D5C3BOmPy/X/qb9VKPH4KN4cOSD0/CNFgJO8M/wR5wAzwbboQj4Z/hBPgXyafHpTyekPJ4UuKzzjdvAP5N4uOBqyQ+T0v/8Iz0D9ukXd8OO8IXYBf4IuwHX5J6sUPqxd/gCPh36QdegXnwNXgjfB3+Ae6G6+Ebcv+9DZ+Ee+Ez8B2df/ItHV4UJv/6S/82EKbAwbADHAK7w3OlHciUejxU4nme1N/zJb6Zko/D4GjRx8BBcJyly/hBvq3DDmHGD+tlHPcgTIMPw9aWrsdZS8V/CpLqOP7Z/c9X44yR/PFOYwGizxo5eb5Ijc8Xeb5fzc8Y2dvvv/uckajhuPmV54zsm/vzZ42UX/XvO29kzXjnf/TMEWP+rzt35Fi/E3/2yKPkyQ7kMyRxAuf/I6OQCmQFsgnZhXyPpE50GgOQbKQCWYM8gexDjiEpWU4jAylEFiNrka3IXiQq22k0QTKQbGQRUonsQY4iiTlOoz1yHlKCrEKeQA4gsbnY5Z48G+Xk38m/k38n/07+nfw7+Xfy7+Tfyb+Tf/+ff7/x+X8F0/J+/fl/5hl/rwec8Tcqwhl/c5kA5ajmGX+W28hn/M3D/ted8SdryV2y34XDT6+5jzDhy5p860h3zvnLt62jsnRZRyXum4nO7gL/MKq530+CdWaRcu/XO6H79s4krJA9IlspM/sekc2UmX2PyBRlZt8j0qPM7Pt5J/jN9DWi/Wb6GobfTF/j28+0mb7GUWVm3wv8sDKz7z99UJnZ93Tcr816KX2v1nsofbfWuyv9Na13k/LW+zlSRvb1c7ti5BsB5d5O2BubjMP+8s5jc5PJvrOhqK2spQu7B9llyk8XV6JD70Uh4fQKqCezCqfkFcp6LZ99D30O0UylH3DGO1gjGrB/xQwOp8rPN/S5/79T7iY4HzRy9Tk/bT5X66MCzjeapu+P2H+adi6jkdRPt9LPwSTOqEuOJPOvGXYxcYhXdinkUrw+p6meMkvGZW2rTuvr1VVp66VqNTHkzyvrWBOU/Z3O8awge83IVPF6SbnL0+dZ/V6l42bnnaRjnpOwlbkv7Al6PeYS5a6pK+DsJp2216tU2vQ+S3uU/lpIvvj3TZB1ubJvTF2VtrPJiRjcYKavn6D89PeoONO88V1J1j1vUfH53OGkRS4k7l615wJ22u/EkPXkF+Bvp4rb25au3WaTHzpuOXl6CbZ/X+fdyt3rXGVn8HVUPSlStbmgoiRLLT9U650zoWn3uLabMpMfcs6ctF1yFgr/6LI+rOLYnW//UQF1qUjX2S+V/SjRffFgL0l9rshUveZ5nsqnYue9Uk/H6HhfjMlFqrwy8bMHeRN5S/Yqfhuashd5B7nC7kabXylmI5F3kUeR9yy/eo3zmvDtbX+siXPvpKWqbXBY+/mquKl1oF187Y9RZdjWQO8LWgN9ULcv6t7W+1FQJpjpMtFr/R8XcykPW3ukJhrIXJW6yBhkGpm+lA89gedLTZuhQs3KLZ7OflHh94f5g/IzRNoiXxge2b/ll++3erbEdXwty+E=
*/