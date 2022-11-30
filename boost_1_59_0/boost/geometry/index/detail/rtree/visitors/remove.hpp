// Boost.Geometry Index
//
// R-tree removing visitor implementation
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_REMOVE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_REMOVE_HPP

#include <boost/geometry/algorithms/detail/covered_by/interface.hpp>

#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>
#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

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