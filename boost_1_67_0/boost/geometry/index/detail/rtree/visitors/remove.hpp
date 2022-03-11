// Boost.Geometry Index
//
// R-tree removing visitor implementation
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_REMOVE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_REMOVE_HPP

#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

#include <boost/geometry/algorithms/detail/covered_by/interface.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

// Default remove algorithm
template <typename MembersHolder>
class remove
    : public MembersHolder::visitor
{
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

    typedef typename rtree::elements_type<internal_node>::type::size_type internal_size_type;

    //typedef typename Allocators::internal_node_pointer internal_node_pointer;
    typedef internal_node * internal_node_pointer;

public:
    inline remove(node_pointer & root,
                  size_type & leafs_level,
                  value_type const& value,
                  parameters_type const& parameters,
                  translator_type const& translator,
                  allocators_type & allocators)
        : m_value(value)
        , m_parameters(parameters)
        , m_translator(translator)
        , m_allocators(allocators)
        , m_root_node(root)
        , m_leafs_level(leafs_level)
        , m_is_value_removed(false)
        , m_parent(0)
        , m_current_child_index(0)
        , m_current_level(0)
        , m_is_underflow(false)
    {
        // TODO
        // assert - check if Value/Box is correct
    }

    inline void operator()(internal_node & n)
    {
        typedef typename rtree::elements_type<internal_node>::type children_type;
        children_type & children = rtree::elements(n);

        // traverse children which boxes intersects value's box
        internal_size_type child_node_index = 0;
        for ( ; child_node_index < children.size() ; ++child_node_index )
        {
            if ( index::detail::covered_by_bounds(m_translator(m_value),
                                                  children[child_node_index].first,
                                                  index::detail::get_strategy(m_parameters)) )
            {
                // next traversing step
                traverse_apply_visitor(n, child_node_index);                                                            // MAY THROW

                if ( m_is_value_removed )
                    break;
            }
        }

        // value was found and removed
        if ( m_is_value_removed )
        {
            typedef typename rtree::elements_type<internal_node>::type elements_type;
            typedef typename elements_type::iterator element_iterator;
            elements_type & elements = rtree::elements(n);

            // underflow occured - child node should be removed
            if ( m_is_underflow )
            {
                element_iterator underfl_el_it = elements.begin() + child_node_index;
                size_type relative_level = m_leafs_level - m_current_level;

                // move node to the container - store node's relative level as well and return new underflow state
                // NOTE: if the min elements number is 1, then after an underflow
                //       here the child elements count is 0, so it's not required to store this node,
                //       it could just be destroyed
                m_is_underflow = store_underflowed_node(elements, underfl_el_it, relative_level);                       // MAY THROW (E: alloc, copy)
            }

            // n is not root - adjust aabb
            if ( 0 != m_parent )
            {
                // underflow state should be ok here
                // note that there may be less than min_elems elements in root
                // so this condition should be checked only here
                BOOST_GEOMETRY_INDEX_ASSERT((elements.size() < m_parameters.get_min_elements()) == m_is_underflow, "unexpected state");

                rtree::elements(*m_parent)[m_current_child_index].first
                    = rtree::elements_box<box_type>(elements.begin(), elements.end(), m_translator,
                                                    index::detail::get_strategy(m_parameters));
            }
            // n is root node
            else
            {
                BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_root_node), "node must be the root");

                // reinsert elements from removed nodes (underflows)
                reinsert_removed_nodes_elements();                                                                  // MAY THROW (V, E: alloc, copy, N: alloc)

                // shorten the tree
                // NOTE: if the min elements number is 1, then after underflow
                //       here the number of elements may be equal to 0
                //       this can occur only for the last removed element
                if ( rtree::elements(n).size() <= 1 )
                {
                    node_pointer root_to_destroy = m_root_node;
                    if ( rtree::elements(n).size() == 0 )
                        m_root_node = 0;
                    else
                        m_root_node = rtree::elements(n)[0].second;
                    --m_leafs_level;

                    rtree::destroy_node<allocators_type, internal_node>::apply(m_allocators, root_to_destroy);
                }
            }
        }
    }

    inline void operator()(leaf & n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type & elements = rtree::elements(n);
        
        // find value and remove it
        for ( typename elements_type::iterator it = elements.begin() ; it != elements.end() ; ++it )
        {
            if ( m_translator.equals(*it, m_value, index::detail::get_strategy(m_parameters)) )
            {
                rtree::move_from_back(elements, it);                                                           // MAY THROW (V: copy)
                elements.pop_back();
                m_is_value_removed = true;
                break;
            }
        }

        // if value was removed
        if ( m_is_value_removed )
        {
            BOOST_GEOMETRY_INDEX_ASSERT(0 < m_parameters.get_min_elements(), "min number of elements is too small");

            // calc underflow
            m_is_underflow = elements.size() < m_parameters.get_min_elements();

            // n is not root - adjust aabb
            if ( 0 != m_parent )
            {
                rtree::elements(*m_parent)[m_current_child_index].first
                    = rtree::values_box<box_type>(elements.begin(), elements.end(), m_translator,
                                                  index::detail::get_strategy(m_parameters));
            }
        }
    }

    bool is_value_removed() const
    {
        return m_is_value_removed;
    }

private:

    typedef std::vector< std::pair<size_type, node_pointer> > underflow_nodes;

    void traverse_apply_visitor(internal_node &n, internal_size_type choosen_node_index)
    {
        // save previous traverse inputs and set new ones
        internal_node_pointer parent_bckup = m_parent;
        internal_size_type current_child_index_bckup = m_current_child_index;
        size_type current_level_bckup = m_current_level;

        m_parent = &n;
        m_current_child_index = choosen_node_index;
        ++m_current_level;

        // next traversing step
        rtree::apply_visitor(*this, *rtree::elements(n)[choosen_node_index].second);                    // MAY THROW (V, E: alloc, copy, N: alloc)

        // restore previous traverse inputs
        m_parent = parent_bckup;
        m_current_child_index = current_child_index_bckup;
        m_current_level = current_level_bckup;
    }

    bool store_underflowed_node(
            typename rtree::elements_type<internal_node>::type & elements,
            typename rtree::elements_type<internal_node>::type::iterator underfl_el_it,
            size_type relative_level)
    {
        // move node to the container - store node's relative level as well
        m_underflowed_nodes.push_back(std::make_pair(relative_level, underfl_el_it->second));           // MAY THROW (E: alloc, copy)

        BOOST_TRY
        {
            // NOTE: those are elements of the internal node which means that copy/move shouldn't throw
            // Though it's safer in case if the pointer type could throw in copy ctor.
            // In the future this try-catch block could be removed.
            rtree::move_from_back(elements, underfl_el_it);                                             // MAY THROW (E: copy)
            elements.pop_back();
        }
        BOOST_CATCH(...)
        {
            m_underflowed_nodes.pop_back();
            BOOST_RETHROW                                                                                 // RETHROW
        }
        BOOST_CATCH_END

        // calc underflow
        return elements.size() < m_parameters.get_min_elements();
    }

    static inline bool is_leaf(node const& n)
    {
        visitors::is_leaf<MembersHolder> ilv;
        rtree::apply_visitor(ilv, n);
        return ilv.result;
    }

    void reinsert_removed_nodes_elements()
    {
        typename underflow_nodes::reverse_iterator it = m_underflowed_nodes.rbegin();

        BOOST_TRY
        {
            // reinsert elements from removed nodes
            // begin with levels closer to the root
            for ( ; it != m_underflowed_nodes.rend() ; ++it )
            {
                // it->first is an index of a level of a node, not children
                // counted from the leafs level
                bool const node_is_leaf = it->first == 1;
                BOOST_GEOMETRY_INDEX_ASSERT(node_is_leaf == is_leaf(*it->second), "unexpected condition");
                if ( node_is_leaf )
                {
                    reinsert_node_elements(rtree::get<leaf>(*it->second), it->first);                        // MAY THROW (V, E: alloc, copy, N: alloc)

                    rtree::destroy_node<allocators_type, leaf>::apply(m_allocators, it->second);
                }
                else
                {
                    reinsert_node_elements(rtree::get<internal_node>(*it->second), it->first);               // MAY THROW (V, E: alloc, copy, N: alloc)

                    rtree::destroy_node<allocators_type, internal_node>::apply(m_allocators, it->second);
                }
            }

            //m_underflowed_nodes.clear();
        }
        BOOST_CATCH(...)
        {
            // destroy current and remaining nodes
            for ( ; it != m_underflowed_nodes.rend() ; ++it )
            {
                rtree::visitors::destroy<MembersHolder>::apply(it->second, m_allocators);
            }

            //m_underflowed_nodes.clear();

            BOOST_RETHROW                                                                                      // RETHROW
        }
        BOOST_CATCH_END
    }

    template <typename Node>
    void reinsert_node_elements(Node &n, size_type node_relative_level)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        typename elements_type::iterator it = elements.begin();
        BOOST_TRY
        {
            for ( ; it != elements.end() ; ++it )
            {
                visitors::insert<typename elements_type::value_type, MembersHolder>
                    insert_v(m_root_node, m_leafs_level, *it,
                             m_parameters, m_translator, m_allocators,
                             node_relative_level - 1);

                rtree::apply_visitor(insert_v, *m_root_node);                                               // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
        BOOST_CATCH(...)
        {
            ++it;
            rtree::destroy_elements<MembersHolder>::apply(it, elements.end(), m_allocators);
            elements.clear();
            BOOST_RETHROW                                                                                     // RETHROW
        }
        BOOST_CATCH_END
    }

    value_type const& m_value;
    parameters_type const& m_parameters;
    translator_type const& m_translator;
    allocators_type & m_allocators;

    node_pointer & m_root_node;
    size_type & m_leafs_level;

    bool m_is_value_removed;
    underflow_nodes m_underflowed_nodes;

    // traversing input parameters
    internal_node_pointer m_parent;
    internal_size_type m_current_child_index;
    size_type m_current_level;

    // traversing output parameters
    bool m_is_underflow;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_REMOVE_HPP

/* remove.hpp
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
*/