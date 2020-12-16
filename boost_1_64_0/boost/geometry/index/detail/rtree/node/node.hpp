// Boost.Geometry Index
//
// R-tree nodes
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_HPP

#include <boost/container/vector.hpp>
#include <boost/geometry/index/detail/varray.hpp>

#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/pairs.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/node/scoped_deallocator.hpp>

//#include <boost/geometry/index/detail/rtree/node/weak_visitor.hpp>
//#include <boost/geometry/index/detail/rtree/node/weak_dynamic.hpp>
//#include <boost/geometry/index/detail/rtree/node/weak_static.hpp>

#include <boost/geometry/index/detail/rtree/node/variant_visitor.hpp>
#include <boost/geometry/index/detail/rtree/node/variant_dynamic.hpp>
#include <boost/geometry/index/detail/rtree/node/variant_static.hpp>

#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/is_bounding_geometry.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// elements box

template <typename Box, typename FwdIter, typename Translator, typename Strategy>
inline Box elements_box(FwdIter first, FwdIter last, Translator const& tr,
                        Strategy const& strategy)
{
    Box result;
    
    // Only here to suppress 'uninitialized local variable used' warning
    // until the suggestion below is not implemented
    geometry::assign_inverse(result);

    //BOOST_GEOMETRY_INDEX_ASSERT(first != last, "non-empty range required");
    // NOTE: this is not elegant temporary solution,
    //       reference to box could be passed as parameter and bool returned
    if ( first == last )
        return result;

    detail::bounds(element_indexable(*first, tr), result, strategy);
    ++first;

    for ( ; first != last ; ++first )
        detail::expand(result, element_indexable(*first, tr), strategy);

    return result;
}

// Enlarge bounds of a leaf node WRT epsilon if needed.
// It's because Points and Segments are compared WRT machine epsilon.
// This ensures that leafs bounds correspond to the stored elements.
// NOTE: this is done only if the Indexable is not a Box
//       in the future don't do it also for NSphere
template <typename Box, typename FwdIter, typename Translator, typename Strategy>
inline Box values_box(FwdIter first, FwdIter last, Translator const& tr,
                      Strategy const& strategy)
{
    typedef typename std::iterator_traits<FwdIter>::value_type element_type;
    BOOST_MPL_ASSERT_MSG((is_leaf_element<element_type>::value),
                         SHOULD_BE_CALLED_ONLY_FOR_LEAF_ELEMENTS,
                         (element_type));

    Box result = elements_box<Box>(first, last, tr, strategy);

#ifdef BOOST_GEOMETRY_INDEX_EXPERIMENTAL_ENLARGE_BY_EPSILON
    if (BOOST_GEOMETRY_CONDITION((
        ! is_bounding_geometry
            <
                typename indexable_type<Translator>::type
            >::value)))
    {
        geometry::detail::expand_by_epsilon(result);
    }
#endif

    return result;
}

// destroys subtree if the element is internal node's element
template <typename MembersHolder>
struct destroy_element
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline static void apply(typename internal_node::elements_type::value_type & element,
                             allocators_type & allocators)
    {
         detail::rtree::visitors::destroy<MembersHolder>::apply(element.second, allocators);

         element.second = 0;
    }

    inline static void apply(typename leaf::elements_type::value_type &,
                             allocators_type &)
    {}
};

// destroys stored subtrees if internal node's elements are passed
template <typename MembersHolder>
struct destroy_elements
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    template <typename Range>
    inline static void apply(Range & elements, allocators_type & allocators)
    {
        apply(boost::begin(elements), boost::end(elements), allocators);
    }

    template <typename It>
    inline static void apply(It first, It last, allocators_type & allocators)
    {
        typedef boost::mpl::bool_<
            boost::is_same<
                value_type, typename std::iterator_traits<It>::value_type
            >::value
        > is_range_of_values;

        apply_dispatch(first, last, allocators, is_range_of_values());
    }

private:
    template <typename It>
    inline static void apply_dispatch(It first, It last, allocators_type & allocators,
                                      boost::mpl::bool_<false> const& /*is_range_of_values*/)
    {
        for ( ; first != last ; ++first )
        {
            detail::rtree::visitors::destroy<MembersHolder>::apply(first->second, allocators);

            first->second = 0;
        }
    }

    template <typename It>
    inline static void apply_dispatch(It /*first*/, It /*last*/, allocators_type & /*allocators*/,
                                      boost::mpl::bool_<true> const& /*is_range_of_values*/)
    {}
};

// clears node, deletes all subtrees stored in node
/*
template <typename MembersHolder>
struct clear_node
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline static void apply(node & node, allocators_type & allocators)
    {
        rtree::visitors::is_leaf<MembersHolder> ilv;
        rtree::apply_visitor(ilv, node);
        if ( ilv.result )
        {
            apply(rtree::get<leaf>(node), allocators);
        }
        else
        {
            apply(rtree::get<internal_node>(node), allocators);
        }
    }

    inline static void apply(internal_node & internal_node, allocators_type & allocators)
    {
        destroy_elements<MembersHolder>::apply(rtree::elements(internal_node), allocators);
        rtree::elements(internal_node).clear();
    }

    inline static void apply(leaf & leaf, allocators_type &)
    {
        rtree::elements(leaf).clear();
    }
};
*/

template <typename Container, typename Iterator>
void move_from_back(Container & container, Iterator it)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!container.empty(), "cannot copy from empty container");
    Iterator back_it = container.end();
    --back_it;
    if ( it != back_it )
    {
        *it = boost::move(*back_it);                                                             // MAY THROW (copy)
    }
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_HPP

/* node.hpp
P6iN2yDeYeq3JOKeamWIG4L8pYvbIWsSvc+1yJvnw9o+7LyWIPqe5KmjJ4Nx/GVMZ/qeFT1IC/3n2/cVpdxTMHkK8FzF66vLz3QvnU3qoERvRmKHmER/F6e/qtOLtZq9g/1VxRcJCUj5Aone+IQz7P7KZf163Imex/xRytBAn+XzJlrsV9KbXhD9OtG62ySyZxPWtoeFdb8WtK08KHIXqj0Yrr70Y9UdWyv7KKcdpoT1UeH9E+0HN9qP3vtM3xrePx2x69IXbY+jk98r6WT3CHI/JyPa3kTRzpOIdn5DtHMmou1xFO1cjZM/ByLaeRuvxEr+t91Q45Q+V21q/LO/U8vNoz8++b2b3M+9iLYXVrS9p6LtVRVt76lo55H8euemuJ9fEu2ckujnkUyRcm38ZFzT1bn3xV+XsNOTdvSex6PtCRb9XJCjep46f3KvvZF2g7N8G7rX47yPvTHF/Jb+qZDfxfzO19+L+Z2jv5tj+unv9Zjx+ns6+eqiv9fw2zlXQ79vhjUwhRHnanT3WRU2e0A/7AljYC94GG7FrNXwX2n4uvARDe9DriGsAdvCWNgZxsE+MB4OhAnwLJgIz4c14TiYDCfAFFiq/nNhPXgjTIcrYX14F0yF98AMuBGeAp+CDeEO2Ajuhk3gO7CpliPX0u934W1ajjg4RsvRQvXQEjZQewvYGmbCNvAc2BYWwHZwBmwPb4EdoaNv/d4WtnLR9w+6V9mPsCG0CNdU7YfhDMwuDf+Qhk+ExRq+L/LpsB9sBvvD1vB0eDrMgoPhcDgGDoKT4GA4FQ6BZfAM1etQeCscbvKv32PCgEv+M1VPnaAXdoZ+2EXDr8Js1fATNXwSXKzhR2r4c2A8zIa14bkwA46CLeFo2AWOgQPheXAYvAiOhJfAs+EFcBQcC8+H4+Al8EKYp/IFjrzJX9Yj0fOXq/kbr/nL1/xN0PwVaP4mav4u0/wVav6mav5KNX+TNH+TNX/Fmr8pME/lC1T+MEwKfj+o30cWYhrz2w8t3dOuEbwPNof3w0FwAxwCX4HZ8CE4Hj4MS+AjcAb8E7wWPgo/U/mv1f4PtQdI63EYD7fAmvAVmA6fgE3gk7AFfAq2Vf+u8GnYD26FZ8BnYSF8Di6C2+Bilb8FvgjXwO3wabgD7oY74TuOnPZD+v0YXOHSD+1Crj58HbaAu2Er+BXsBN+AXeCbsBd8C/aH78ChcA8cCd+F58L34Rj4AbwAfggvhnthLvwYToKfqH73wcs1vdlwP5wL/w5vcNzN+TR7tRxDMYUR59N8jVwqPKzlOKL5/xZ2h0dhb/g9zILH4EC1O3sl6ndPsAFmoyd8r8S39Xyjd6AXvgtrwvdgPbgHngLfh4fhUku/K4Jfan5rw/ka30yP04/Ngm3gbNgFXg17wjlwCKyAZ8O5cCycB/PhfHg5vA6Ww+vhJrgAvgAXwl1wMXwN3gid/ly/s4GrXPrzp5BLhU/DemrPUPsF8Bk4Xu1Xq32h2m907JqOfnMCb3FJ5zFN53FYT+0Zar8AboHj1T5b7QvUvljth2G2pd9gwPM0nRpwsKaDTEUa/AZmwCOwFfwWngqPwh7wOyjtAZr8P+jEe6FL/ndq/l+BzeFf4Gnwr7AP3AX7wdfgUPgqHKH28xy7SefQcdJ5Q9N5U9N5S9N5W9N5R9N5T9N5F45Q+3mOXdPRNfVwpEs6z2t7/jNMhi/ANnAHbAdfgp3gy7C7ug9Q96HqbtrXH6Kn8xdNZ5em86qms1vTeUPTeRN2V/cB6j5U3Q/D9ZauEYcHNZ0UuEbT+ZByN4B7YWv4EWwLP4Hd4JdwINwHR8FPtd39DZbAz+E8+AVcAL+CS+FBeCc8BO+HX8M=
*/