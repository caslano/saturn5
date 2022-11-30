// Boost.Geometry Index
//
// R-tree inserting visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_INSERT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_INSERT_HPP

#ifdef BOOST_GEOMETRY_INDEX_EXPERIMENTAL_ENLARGE_BY_EPSILON
#include <type_traits>
#endif

#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/algorithms/content.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>
#include <boost/geometry/index/detail/rtree/options.hpp>

#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// Default choose_next_node
template
<
    typename MembersHolder,
    typename ChooseNextNodeTag = typename MembersHolder::options_type::choose_next_node_tag
>
class choose_next_node;

template <typename MembersHolder>
class choose_next_node<MembersHolder, choose_by_content_diff_tag>
{
public:
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename rtree::elements_type<internal_node>::type children_type;

    typedef typename index::detail::default_content_result<box_type>::type content_type;

    template <typename Indexable>
    static inline size_t apply(internal_node & n,
                               Indexable const& indexable,
                               parameters_type const& parameters,
                               size_t /*node_relative_level*/)
    {
        children_type & children = rtree::elements(n);

        BOOST_GEOMETRY_INDEX_ASSERT(!children.empty(), "can't choose the next node if children are empty");

        size_t children_count = children.size();

        // choose index with smallest content change or smallest content
        size_t choosen_index = 0;
        content_type smallest_content_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        // caculate areas and areas of all nodes' boxes
        for ( size_t i = 0 ; i < children_count ; ++i )
        {
            typedef typename children_type::value_type child_type;
            child_type const& ch_i = children[i];

            // expanded child node's box
            box_type box_exp(ch_i.first);
            index::detail::expand(box_exp, indexable,
                                  index::detail::get_strategy(parameters));

            // areas difference
            content_type content = index::detail::content(box_exp);
            content_type content_diff = content - index::detail::content(ch_i.first);

            // update the result
            if ( content_diff < smallest_content_diff ||
                ( content_diff == smallest_content_diff && content < smallest_content ) )
            {
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }
};

// ----------------------------------------------------------------------- //

// Not implemented here
template
<
    typename MembersHolder,
    typename RedistributeTag = typename MembersHolder::options_type::redistribute_tag
>
struct redistribute_elements
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this RedistributeTag type.",
        MembersHolder, RedistributeTag);
};

// ----------------------------------------------------------------------- //

// Split algorithm
template
<
    typename MembersHolder,
    typename SplitTag = typename MembersHolder::options_type::split_tag
>
class split
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this SplitTag type.",
        MembersHolder, SplitTag);
};

// Default split algorithm
template <typename MembersHolder>
class split<MembersHolder, split_default_tag>
{
protected:
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;
    typedef typename MembersHolder::size_type size_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename MembersHolder::node_pointer node_pointer;

public:
    typedef index::detail::varray<
        typename rtree::elements_type<internal_node>::type::value_type,
        1
    > nodes_container_type;

    template <typename Node>
    static inline void apply(nodes_container_type & additional_nodes,
                             Node & n,
                             box_type & n_box,
                             parameters_type const& parameters,
                             translator_type const& translator,
                             allocators_type & allocators)
    {
        // TODO - consider creating nodes always with sufficient memory allocated

        // create additional node, use auto destroyer for automatic destruction on exception
        node_pointer n2_ptr = rtree::create_node<allocators_type, Node>::apply(allocators);                  // MAY THROW, STRONG (N: alloc)
        // create reference to the newly created node
        Node & n2 = rtree::get<Node>(*n2_ptr);

        BOOST_TRY
        {
            // NOTE: thread-safety
            // After throwing an exception by redistribute_elements the original node may be not changed or
            // both nodes may be empty. In both cases the tree won't be valid r-tree.
            // The alternative is to create 2 (or more) additional nodes here and store backup info
            // in the original node, then, if exception was thrown, the node would always have more than max
            // elements.
            // The alternative is to use moving semantics in the implementations of redistribute_elements,
            // it will be possible to throw from boost::move() in the case of e.g. static size nodes.

            // redistribute elements
            box_type box2;
            redistribute_elements<MembersHolder>
                ::apply(n, n2, n_box, box2, parameters, translator, allocators);                                   // MAY THROW (V, E: alloc, copy, copy)

            // check numbers of elements
            BOOST_GEOMETRY_INDEX_ASSERT(parameters.get_min_elements() <= rtree::elements(n).size() &&
                rtree::elements(n).size() <= parameters.get_max_elements(),
                "unexpected number of elements");
            BOOST_GEOMETRY_INDEX_ASSERT(parameters.get_min_elements() <= rtree::elements(n2).size() &&
                rtree::elements(n2).size() <= parameters.get_max_elements(),
                "unexpected number of elements");

            // return the list of newly created nodes (this algorithm returns one)
            additional_nodes.push_back(rtree::make_ptr_pair(box2, n2_ptr));                                  // MAY THROW, STRONG (alloc, copy)
        }
        BOOST_CATCH(...)
        {
            // NOTE: This code is here to prevent leaving the rtree in a state
            //  after an exception is thrown in which pushing new element could
            //  result in assert or putting it outside the memory of node elements.
            typename rtree::elements_type<Node>::type & elements = rtree::elements(n);
            size_type const max_size = parameters.get_max_elements();
            if (elements.size() > max_size)
            {
                rtree::destroy_element<MembersHolder>::apply(elements[max_size], allocators);
                elements.pop_back();
            }

            rtree::visitors::destroy<MembersHolder>::apply(n2_ptr, allocators);

            BOOST_RETHROW
        }
        BOOST_CATCH_END
    }
};

// ----------------------------------------------------------------------- //

namespace visitors { namespace detail {

template <typename InternalNode, typename InternalNodePtr, typename SizeType>
struct insert_traverse_data
{
    typedef typename rtree::elements_type<InternalNode>::type elements_type;
    typedef typename elements_type::value_type element_type;
    typedef typename elements_type::size_type elements_size_type;
    typedef SizeType size_type;

    insert_traverse_data()
        : parent(0), current_child_index(0), current_level(0)
    {}

    void move_to_next_level(InternalNodePtr new_parent,
                            elements_size_type new_child_index)
    {
        parent = new_parent;
        current_child_index = new_child_index;
        ++current_level;
    }

    bool current_is_root() const
    {
        return 0 == parent;
    }

    elements_type & parent_elements() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(parent, "null pointer");
        return rtree::elements(*parent);
    }

    element_type & current_element() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(parent, "null pointer");
        return rtree::elements(*parent)[current_child_index];
    }

    InternalNodePtr parent;
    elements_size_type current_child_index;
    size_type current_level;
};

// Default insert visitor
template <typename Element, typename MembersHolder>
class insert
    : public MembersHolder::visitor
{
protected:
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef rtree::subtree_destroyer<MembersHolder> subtree_destroyer;
    typedef typename allocators_type::node_pointer node_pointer;
    typedef typename allocators_type::size_type size_type;

    //typedef typename allocators_type::internal_node_pointer internal_node_pointer;
    typedef internal_node * internal_node_pointer;

    inline insert(node_pointer & root,
                  size_type & leafs_level,
                  Element const& element,
                  parameters_type const& parameters,
                  translator_type const& translator,
                  allocators_type & allocators,
                  size_type relative_level = 0
    )
        : m_element(element)
        , m_parameters(parameters)
        , m_translator(translator)
        , m_relative_level(relative_level)
        , m_level(leafs_level - relative_level)
        , m_root_node(root)
        , m_leafs_level(leafs_level)
        , m_traverse_data()
        , m_allocators(allocators)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_relative_level <= leafs_level, "unexpected level value");
        BOOST_GEOMETRY_INDEX_ASSERT(m_level <= m_leafs_level, "unexpected level value");
        BOOST_GEOMETRY_INDEX_ASSERT(0 != m_root_node, "there is no root node");
        // TODO
        // assert - check if Box is correct

        // When a value is inserted, during the tree traversal bounds of nodes
        // on a path from the root to a leaf must be expanded. So prepare
        // a bounding object at the beginning to not do it later for each node.
        // NOTE: This is actually only needed because conditionally the bounding
        //       object may be expanded below. Otherwise the indexable could be
        //       directly used instead
        index::detail::bounds(rtree::element_indexable(m_element, m_translator),
                              m_element_bounds,
                              index::detail::get_strategy(m_parameters));

#ifdef BOOST_GEOMETRY_INDEX_EXPERIMENTAL_ENLARGE_BY_EPSILON
        // Enlarge it in case if it's not bounding geometry type.
        // It's because Points and Segments are compared WRT machine epsilon
        // This ensures that leafs bounds correspond to the stored elements
        if (BOOST_GEOMETRY_CONDITION((
                std::is_same<Element, value_type>::value
             && ! index::detail::is_bounding_geometry
                    <
                        typename indexable_type<translator_type>::type
                    >::value )) )
        {
            geometry::detail::expand_by_epsilon(m_element_bounds);
        }
#endif
    }

    template <typename Visitor>
    inline void traverse(Visitor & visitor, internal_node & n)
    {
        // choose next node
        size_t choosen_node_index = rtree::choose_next_node<MembersHolder>
            ::apply(n, rtree::element_indexable(m_element, m_translator),
                    m_parameters,
                    m_leafs_level - m_traverse_data.current_level);

        // expand the node to contain value
        index::detail::expand(
            rtree::elements(n)[choosen_node_index].first,
            m_element_bounds,
            index::detail::get_strategy(m_parameters));

        // next traversing step
        traverse_apply_visitor(visitor, n, choosen_node_index);                                                 // MAY THROW (V, E: alloc, copy, N:alloc)
    }

    // TODO: awulkiew - change post_traverse name to handle_overflow or overflow_treatment?

    template <typename Node>
    inline void post_traverse(Node &n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_traverse_data.current_is_root() ||
                                    &n == &rtree::get<Node>(*m_traverse_data.current_element().second),
                                    "if node isn't the root current_child_index should be valid");

        // handle overflow
        if ( m_parameters.get_max_elements() < rtree::elements(n).size() )
        {
            // NOTE: If the exception is thrown current node may contain more than MAX elements or be empty.
            // Furthermore it may be empty root - internal node.
            split(n);                                                                                           // MAY THROW (V, E: alloc, copy, N:alloc)
        }
    }

    template <typename Visitor>
    inline void traverse_apply_visitor(Visitor & visitor, internal_node &n, size_t choosen_node_index)
    {
        // save previous traverse inputs and set new ones
        insert_traverse_data<internal_node, internal_node_pointer, size_type>
            backup_traverse_data = m_traverse_data;

        // calculate new traverse inputs
        m_traverse_data.move_to_next_level(&n, choosen_node_index);

        // next traversing step
        rtree::apply_visitor(visitor, *rtree::elements(n)[choosen_node_index].second);                          // MAY THROW (V, E: alloc, copy, N:alloc)

        // restore previous traverse inputs
        m_traverse_data = backup_traverse_data;
    }

    // TODO: consider - split result returned as OutIter is faster than reference to the container. Why?

    template <typename Node>
    inline void split(Node & n) const
    {
        typedef rtree::split<MembersHolder> split_algo;

        typename split_algo::nodes_container_type additional_nodes;
        box_type n_box;

        split_algo::apply(additional_nodes, n, n_box, m_parameters, m_translator, m_allocators);                // MAY THROW (V, E: alloc, copy, N:alloc)

        BOOST_GEOMETRY_INDEX_ASSERT(additional_nodes.size() == 1, "unexpected number of additional nodes");

        // TODO add all additional nodes
        // For kmeans algorithm:
        // elements number may be greater than node max elements count
        // split and reinsert must take node with some elements count
        // and container of additional elements (std::pair<Box, node*>s or Values)
        // and translator + allocators
        // where node_elements_count + additional_elements > node_max_elements_count
        // What with elements other than std::pair<Box, node*> ?
        // Implement template <node_tag> struct node_element_type or something like that

        // for exception safety
        subtree_destroyer additional_node_ptr(additional_nodes[0].second, m_allocators);

#ifdef BOOST_GEOMETRY_INDEX_EXPERIMENTAL_ENLARGE_BY_EPSILON
        // Enlarge bounds of a leaf node.
        // It's because Points and Segments are compared WRT machine epsilon
        // This ensures that leafs' bounds correspond to the stored elements.
        if (BOOST_GEOMETRY_CONDITION((
                std::is_same<Node, leaf>::value
             && ! index::detail::is_bounding_geometry
                    <
                        typename indexable_type<translator_type>::type
                    >::value )))
        {
            geometry::detail::expand_by_epsilon(n_box);
            geometry::detail::expand_by_epsilon(additional_nodes[0].first);
        }
#endif

        // node is not the root - just add the new node
        if ( !m_traverse_data.current_is_root() )
        {
            // update old node's box
            m_traverse_data.current_element().first = n_box;
            // add new node to parent's children
            m_traverse_data.parent_elements().push_back(additional_nodes[0]);                                     // MAY THROW, STRONG (V, E: alloc, copy)
        }
        // node is the root - add level
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<Node>(*m_root_node), "node should be the root");

            // create new root and add nodes
            subtree_destroyer new_root(rtree::create_node<allocators_type, internal_node>::apply(m_allocators), m_allocators); // MAY THROW, STRONG (N:alloc)

            BOOST_TRY
            {
                rtree::elements(rtree::get<internal_node>(*new_root)).push_back(rtree::make_ptr_pair(n_box, m_root_node));  // MAY THROW, STRONG (E:alloc, copy)
                rtree::elements(rtree::get<internal_node>(*new_root)).push_back(additional_nodes[0]);                 // MAY THROW, STRONG (E:alloc, copy)
            }
            BOOST_CATCH(...)
            {
                // clear new root to not delete in the ~subtree_destroyer() potentially stored old root node
                rtree::elements(rtree::get<internal_node>(*new_root)).clear();
                BOOST_RETHROW                                                                                           // RETHROW
            }
            BOOST_CATCH_END

            m_root_node = new_root.get();
            ++m_leafs_level;

            new_root.release();
        }

        additional_node_ptr.release();
    }

    // TODO: awulkiew - implement dispatchable split::apply to enable additional nodes creation

    Element const& m_element;
    box_type m_element_bounds;
    parameters_type const& m_parameters;
    translator_type const& m_translator;
    size_type const m_relative_level;
    size_type const m_level;

    node_pointer & m_root_node;
    size_type & m_leafs_level;

    // traversing input parameters
    insert_traverse_data<internal_node, internal_node_pointer, size_type> m_traverse_data;

    allocators_type & m_allocators;
};

} // namespace detail

// Insert visitor forward declaration
template
<
    typename Element,
    typename MembersHolder,
    typename InsertTag = typename MembersHolder::options_type::insert_tag
>
class insert;

// Default insert visitor used for nodes elements
// After passing the Element to insert visitor the Element is managed by the tree
// I.e. one should not delete the node passed to the insert visitor after exception is thrown
// because this visitor may delete it
template <typename Element, typename MembersHolder>
class insert<Element, MembersHolder, insert_default_tag>
    : public detail::insert<Element, MembersHolder>
{
public:
    typedef detail::insert<Element, MembersHolder> base;

    typedef typename base::parameters_type parameters_type;
    typedef typename base::translator_type translator_type;
    typedef typename base::allocators_type allocators_type;

    typedef typename base::node node;
    typedef typename base::internal_node internal_node;
    typedef typename base::leaf leaf;

    typedef typename base::node_pointer node_pointer;
    typedef typename base::size_type size_type;

    inline insert(node_pointer & root,
                  size_type & leafs_level,
                  Element const& element,
                  parameters_type const& parameters,
                  translator_type const& translator,
                  allocators_type & allocators,
                  size_type relative_level = 0
    )
        : base(root, leafs_level, element, parameters, translator, allocators, relative_level)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level, "unexpected level");

        if ( base::m_traverse_data.current_level < base::m_level )
        {
            // next traversing step
            base::traverse(*this, n);                                                                           // MAY THROW (E: alloc, copy, N: alloc)
        }
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level, "unexpected level");

            BOOST_TRY
            {
                // push new child node
                rtree::elements(n).push_back(base::m_element);                                                  // MAY THROW, STRONG (E: alloc, copy)
            }
            BOOST_CATCH(...)
            {
                // if the insert fails above, the element won't be stored in the tree

                rtree::visitors::destroy<MembersHolder>::apply(base::m_element.second, base::m_allocators);

                BOOST_RETHROW                                                                                     // RETHROW
            }
            BOOST_CATCH_END
        }

        base::post_traverse(n);                                                                                 // MAY THROW (E: alloc, copy, N: alloc)
    }

    inline void operator()(leaf &)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "this visitor can't be used for a leaf");
    }
};

// Default insert visitor specialized for Values elements
template <typename MembersHolder>
class insert<typename MembersHolder::value_type, MembersHolder, insert_default_tag>
    : public detail::insert<typename MembersHolder::value_type, MembersHolder>
{
public:
    typedef detail::insert<typename MembersHolder::value_type, MembersHolder> base;

    typedef typename base::value_type value_type;
    typedef typename base::parameters_type parameters_type;
    typedef typename base::translator_type translator_type;
    typedef typename base::allocators_type allocators_type;

    typedef typename base::node node;
    typedef typename base::internal_node internal_node;
    typedef typename base::leaf leaf;

    typedef typename base::node_pointer node_pointer;
    typedef typename base::size_type size_type;

    inline insert(node_pointer & root,
                  size_type & leafs_level,
                  value_type const& value,
                  parameters_type const& parameters,
                  translator_type const& translator,
                  allocators_type & allocators,
                  size_type relative_level = 0
    )
        : base(root, leafs_level, value, parameters, translator, allocators, relative_level)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level, "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_level, "unexpected level");

        // next traversing step
        base::traverse(*this, n);                                                                                   // MAY THROW (V, E: alloc, copy, N: alloc)

        base::post_traverse(n);                                                                                     // MAY THROW (E: alloc, copy, N: alloc)
    }

    inline void operator()(leaf & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level == base::m_leafs_level, "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level ||
                                    base::m_level == (std::numeric_limits<size_t>::max)(), "unexpected level");
        
        rtree::elements(n).push_back(base::m_element);                                                              // MAY THROW, STRONG (V: alloc, copy)

        base::post_traverse(n);                                                                                     // MAY THROW (V: alloc, copy, N: alloc)
    }
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_INSERT_HPP

/* insert.hpp
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
*/