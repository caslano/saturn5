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
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
*/