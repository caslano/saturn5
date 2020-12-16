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
f6X/64P0lXY6vVrvPtxJ93bQ+Sttt+7HVHyDzIijvT1fJw9mf5P2/Bmkj5f6HyFPsvJm0MQY/rbUfk4y/uS9uX6PrTxkTSrOmVwWMBaJ6mi6uy9s/mWi/aTCeSh4zoEeW0Yr//cG568eW7VQ9knMJq6ln3+/VGE+YrTHtDdzpFqT97GGNRczQ6QP0i+wHKr1zoJvwB11OQSNR/1n6A3W79RteaLcZ4aWka63Y/taF7tILjoOOdsso44BZVSeRYM0ndF+4dQuYftbcU8opxqnB5xzjbcu/u8+xulqPkWNn4ED4/u8xLeD3GdpyDICzzxdx7dseql+f2rOo65GXe+VNFP2sxnotZ81Nf6s8GdNLcX9cc6aUm5+zVlTd50eetaU4ar5GUUn6syh8Hs+Rd5LKfyeT5H3uAq/B1XkvY7C7/lU8z2Nwu9ZFWmvppqfsdRZ7XH19bkHVi86PGr2FZsWnt9pfN8RkfeyCr+nV+Q9osLv+RRp767f/gywmu49Fn5PtYh7VqkzpUoCzpTaA9+SM6VSHer8D+Y9WfdsDvJdwO9vA35/Lb+HIl/KQpHBLsIP+H004LfvDJVEpz5Dimv/yjOkkAwJL0adSWU/22RtLSu8dTAa3gd9Z9dkij+vcmk/u4b4ancl1XS3tJruKgPcpQS5Iy+1u50/4y4nwF1VNd0luo7vLh3pJO7aSX5Gwfbi7sx4qzz6wBawLzzF0uWsH0T8d1b+7Wf93JxglccyWAs+AJPgPTAFrocN4Z0wVezTxLwlvB12FPNOYn4EZjhkva2sBTava8arGzT/vq9tHbP5A2wCm9WxzgxLg/1hSzgQNoeDYSpU42E4Gp4KJ8C2cAFsB2+AHeDNoi8T/THYCX4D02F94tALpsDesDHsC5vBs2Aa7A/T4TnwXDgCDocj4SQ4BhbCsXAGHAcvgxfDZTAbVsIcuBHmwu2wLdwHL4FHYBH8CU6CcU7LvA7EXOXjGkPWLco6yErELJ9bfHu4UM4e2AQ2gE1hZ9gMDofNYQVMhStgS/gAbAWfgqfC52Bb+BFsB7mc0QE2gqfDNNgN9oPdoVqzB0fCdKlnc6NkzZ6sXTTjeT2/y2V/jgG4awwHwlR4DhwBh8IseB7MhxfAS+EwOAtmwsvhCPh7OBIugaPhcjgGroLj4V1wAtwGJ8IdMBu+AXPgXpgLv4d50EUcC+CpcDIcAgvhcDgFjoVFsBAWwzI4HVbAUng7LIN3wZlwPZwF/wyvhI/DufBZeBV8Hs6HO+EC+Dq8Gr4PF8KP4CJ4BP4efguvg02pDzfB1vBWeBZcBgfBFXAovA2OgivhfLgGroV3wUr4B7gRrobPwjvg8/AeuBveC9+G98P9cD08AB+Gn8BK+BncAL+AG+GXcBP8Hj4Df4IPwCgXc8ESqEdwKWwInzTLHW6GadB03xZuhafB7bALfAF2gztgX/g3OAjuhFnwFTgJvgqnwl1wOjwM58MqeD08CtfCr+BD8Bu4GX4Lt8If4B5oEL93oQt+DN3wSxgNf4QJMIo6XBvWhnVgCqwLW8AkeBr0wO6wHhwCG8NxsCnMhs3gJbA5LIMt4VzYCi6Ap8CVsDW8E54K18K28AFxvwG2h5tgJ7gbdoP/hOnQ4aY/gI3hWbALPBsOgwPhFHguvBqeB1fA8+FqeAFcA4fBR+Bw+Bc4Aj4NR8LX4IVwLxwHv4DjoZuOPAs2h7nwTFgAh8NJcCIshMVwCpwBL4GXwyK4EM6EG+BlcBOcDZ+Dv4OvwfnwLXg1/AJeA7+Ci2BUDPVM+p1jel0PeS7tZRN1Fp31dxf9jck/wPbwXtgTvgLPhK/CPvABOEDMh4j5ufBhOFzMx4j5hXADnCg=
*/