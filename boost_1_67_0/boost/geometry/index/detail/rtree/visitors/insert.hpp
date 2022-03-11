// Boost.Geometry Index
//
// R-tree inserting visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_INSERT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_INSERT_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/util/condition.hpp>

#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/algorithms/content.hpp>

#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>

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
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_REDISTRIBUTE_TAG_TYPE,
        (redistribute_elements));
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
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_SPLIT_TAG_TYPE,
        (split));
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
    : MembersHolder::visitor
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
                boost::is_same<Element, value_type>::value
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
                boost::is_same<Node, leaf>::value
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