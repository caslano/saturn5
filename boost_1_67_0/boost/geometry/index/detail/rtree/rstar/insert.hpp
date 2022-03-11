// Boost.Geometry Index
//
// R-tree R*-tree insert algorithm implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_INSERT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_INSERT_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

namespace rstar {

// Utility to distinguish between default and non-default index strategy
template <typename Point1, typename Point2, typename Strategy>
struct comparable_distance_point_point
{
    typedef typename Strategy::comparable_distance_point_point_strategy_type strategy_type;
    typedef typename geometry::comparable_distance_result
        <
            Point1, Point2, strategy_type
        >::type result_type;

    static inline strategy_type get_strategy(Strategy const& strategy)
    {
        return strategy.get_comparable_distance_point_point_strategy();
    }
};

template <typename Point1, typename Point2>
struct comparable_distance_point_point<Point1, Point2, default_strategy>
{
    typedef default_strategy strategy_type;
    typedef typename geometry::default_comparable_distance_result
        <
            Point1, Point2
        >::type result_type;

    static inline strategy_type get_strategy(default_strategy const& )
    {
        return strategy_type();
    }
};

template <typename MembersHolder>
class remove_elements_to_reinsert
{
public:
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    //typedef typename Allocators::internal_node_pointer internal_node_pointer;
    typedef internal_node * internal_node_pointer;

    template <typename ResultElements, typename Node>
    static inline void apply(ResultElements & result_elements,
                             Node & n,
                             internal_node_pointer parent,
                             size_t current_child_index,
                             parameters_type const& parameters,
                             translator_type const& translator,
                             allocators_type & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        typedef typename geometry::point_type<box_type>::type point_type;
        typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;
        // TODO: awulkiew - change second point_type to the point type of the Indexable?
        typedef rstar::comparable_distance_point_point
            <
                point_type, point_type, strategy_type
            > comparable_distance_pp;
        typedef typename comparable_distance_pp::result_type comparable_distance_type;

        elements_type & elements = rtree::elements(n);

        const size_t elements_count = parameters.get_max_elements() + 1;
        const size_t reinserted_elements_count = (::std::min)(parameters.get_reinserted_elements(), elements_count - parameters.get_min_elements());

        BOOST_GEOMETRY_INDEX_ASSERT(parent, "node shouldn't be the root node");
        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == elements_count, "unexpected elements number");
        BOOST_GEOMETRY_INDEX_ASSERT(0 < reinserted_elements_count, "wrong value of elements to reinsert");

        // calculate current node's center
        point_type node_center;
        geometry::centroid(rtree::elements(*parent)[current_child_index].first, node_center);

        // fill the container of centers' distances of children from current node's center
        typedef typename index::detail::rtree::container_from_elements_type<
            elements_type,
            std::pair<comparable_distance_type, element_type>
        >::type sorted_elements_type;

        sorted_elements_type sorted_elements;
        // If constructor is used instead of resize() MS implementation leaks here
        sorted_elements.reserve(elements_count);                                                         // MAY THROW, STRONG (V, E: alloc, copy)
        
        typename comparable_distance_pp::strategy_type
            cdist_strategy = comparable_distance_pp::get_strategy(index::detail::get_strategy(parameters));

        for ( typename elements_type::const_iterator it = elements.begin() ;
              it != elements.end() ; ++it )
        {
            point_type element_center;
            geometry::centroid( rtree::element_indexable(*it, translator), element_center);
            sorted_elements.push_back(std::make_pair(
                geometry::comparable_distance(node_center, element_center, cdist_strategy),
                *it));                                                                                  // MAY THROW (V, E: copy)
        }

        // sort elements by distances from center
        std::partial_sort(
            sorted_elements.begin(),
            sorted_elements.begin() + reinserted_elements_count,
            sorted_elements.end(),
            distances_dsc<comparable_distance_type, element_type>);                                                // MAY THROW, BASIC (V, E: copy)

        // copy elements which will be reinserted
        result_elements.clear();
        result_elements.reserve(reinserted_elements_count);                                             // MAY THROW, STRONG (V, E: alloc, copy)
        for ( typename sorted_elements_type::const_iterator it = sorted_elements.begin() ;
              it != sorted_elements.begin() + reinserted_elements_count ; ++it )
        {
            result_elements.push_back(it->second);                                                      // MAY THROW (V, E: copy)
        }

        BOOST_TRY
        {
            // copy remaining elements to the current node
            elements.clear();
            elements.reserve(elements_count - reinserted_elements_count);                                // SHOULDN'T THROW (new_size <= old size)
            for ( typename sorted_elements_type::const_iterator it = sorted_elements.begin() + reinserted_elements_count;
                  it != sorted_elements.end() ; ++it )
            {
                elements.push_back(it->second);                                                         // MAY THROW (V, E: copy)
            }
        }
        BOOST_CATCH(...)
        {
            elements.clear();

            for ( typename sorted_elements_type::iterator it = sorted_elements.begin() ;
                  it != sorted_elements.end() ; ++it )
            {
                destroy_element<MembersHolder>::apply(it->second, allocators);
            }

            BOOST_RETHROW                                                                                 // RETHROW
        }
        BOOST_CATCH_END

        ::boost::ignore_unused(parameters);
    }

private:
    template <typename Distance, typename El>
    static inline bool distances_asc(
        std::pair<Distance, El> const& d1,
        std::pair<Distance, El> const& d2)
    {
        return d1.first < d2.first;
    }
    
    template <typename Distance, typename El>
    static inline bool distances_dsc(
        std::pair<Distance, El> const& d1,
        std::pair<Distance, El> const& d2)
    {
        return d1.first > d2.first;
    }
};

template
<
    size_t InsertIndex,
    typename Element,
    typename MembersHolder,
    bool IsValue = boost::is_same<Element, typename MembersHolder::value_type>::value
>
struct level_insert_elements_type
{
    typedef typename rtree::elements_type<
        typename rtree::internal_node<
            typename MembersHolder::value_type,
            typename MembersHolder::parameters_type,
            typename MembersHolder::box_type,
            typename MembersHolder::allocators_type,
            typename MembersHolder::node_tag
        >::type
    >::type type;
};

template <typename Value, typename MembersHolder>
struct level_insert_elements_type<0, Value, MembersHolder, true>
{
    typedef typename rtree::elements_type<
        typename rtree::leaf<
            typename MembersHolder::value_type,
            typename MembersHolder::parameters_type,
            typename MembersHolder::box_type,
            typename MembersHolder::allocators_type,
            typename MembersHolder::node_tag
        >::type
    >::type type;
};

template <size_t InsertIndex, typename Element, typename MembersHolder>
struct level_insert_base
    : public detail::insert<Element, MembersHolder>
{
    typedef detail::insert<Element, MembersHolder> base;
    typedef typename base::node node;
    typedef typename base::internal_node internal_node;
    typedef typename base::leaf leaf;

    typedef typename level_insert_elements_type<InsertIndex, Element, MembersHolder>::type elements_type;
    typedef typename index::detail::rtree::container_from_elements_type<
        elements_type,
        typename elements_type::value_type
    >::type result_elements_type;

    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename allocators_type::node_pointer node_pointer;
    typedef typename allocators_type::size_type size_type;

    inline level_insert_base(node_pointer & root,
                             size_type & leafs_level,
                             Element const& element,
                             parameters_type const& parameters,
                             translator_type const& translator,
                             allocators_type & allocators,
                             size_type relative_level)
        : base(root, leafs_level, element, parameters, translator, allocators, relative_level)
        , result_relative_level(0)
    {}

    template <typename Node>
    inline void handle_possible_reinsert_or_split_of_root(Node &n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(result_elements.empty(), "reinsert should be handled only once for level");

        result_relative_level = base::m_leafs_level - base::m_traverse_data.current_level;

        // overflow
        if ( base::m_parameters.get_max_elements() < rtree::elements(n).size() )
        {
            // node isn't root node
            if ( !base::m_traverse_data.current_is_root() )
            {
                // NOTE: exception-safety
                // After an exception result_elements may contain garbage, don't use it
                rstar::remove_elements_to_reinsert<MembersHolder>::apply(
                    result_elements, n,
                    base::m_traverse_data.parent, base::m_traverse_data.current_child_index,
                    base::m_parameters, base::m_translator, base::m_allocators);                            // MAY THROW, BASIC (V, E: alloc, copy)
            }
            // node is root node
            else
            {
                BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<Node>(*base::m_root_node), "node should be the root node");
                base::split(n);                                                                             // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
    }

    template <typename Node>
    inline void handle_possible_split(Node &n) const
    {
        // overflow
        if ( base::m_parameters.get_max_elements() < rtree::elements(n).size() )
        {
            base::split(n);                                                                                 // MAY THROW (V, E: alloc, copy, N: alloc)
        }
    }

    template <typename Node>
    inline void recalculate_aabb_if_necessary(Node const& n) const
    {
        if ( !result_elements.empty() && !base::m_traverse_data.current_is_root() )
        {
            // calulate node's new box
            recalculate_aabb(n);
        }
    }

    template <typename Node>
    inline void recalculate_aabb(Node const& n) const
    {
        base::m_traverse_data.current_element().first =
            elements_box<box_type>(rtree::elements(n).begin(), rtree::elements(n).end(),
                                   base::m_translator,
                                   index::detail::get_strategy(base::m_parameters));
    }

    inline void recalculate_aabb(leaf const& n) const
    {
        base::m_traverse_data.current_element().first =
            values_box<box_type>(rtree::elements(n).begin(), rtree::elements(n).end(),
                                 base::m_translator,
                                 index::detail::get_strategy(base::m_parameters));
    }

    size_type result_relative_level;
    result_elements_type result_elements;
};

template
<
    size_t InsertIndex,
    typename Element,
    typename MembersHolder,
    bool IsValue = boost::is_same<Element, typename MembersHolder::value_type>::value
>
struct level_insert
    : public level_insert_base<InsertIndex, Element, MembersHolder>
{
    typedef level_insert_base<InsertIndex, Element, MembersHolder> base;
    typedef typename base::node node;
    typedef typename base::internal_node internal_node;
    typedef typename base::leaf leaf;

    typedef typename base::parameters_type parameters_type;
    typedef typename base::translator_type translator_type;
    typedef typename base::allocators_type allocators_type;

    typedef typename base::node_pointer node_pointer;
    typedef typename base::size_type size_type;

    inline level_insert(node_pointer & root,
                        size_type & leafs_level,
                        Element const& element,
                        parameters_type const& parameters,
                        translator_type const& translator,
                        allocators_type & allocators,
                        size_type relative_level)
        : base(root, leafs_level, element, parameters, translator, allocators, relative_level)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level, "unexpected level");

        if ( base::m_traverse_data.current_level < base::m_level )
        {
            // next traversing step
            base::traverse(*this, n);                                                                       // MAY THROW (E: alloc, copy, N: alloc)

            // further insert
            if ( 0 < InsertIndex )
            {
                BOOST_GEOMETRY_INDEX_ASSERT(0 < base::m_level, "illegal level value, level shouldn't be the root level for 0 < InsertIndex");

                if ( base::m_traverse_data.current_level == base::m_level - 1 )
                {
                    base::handle_possible_reinsert_or_split_of_root(n);                                     // MAY THROW (E: alloc, copy, N: alloc)
                }
            }
        }
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level, "unexpected level");

            BOOST_TRY
            {
                // push new child node
                rtree::elements(n).push_back(base::m_element);                                              // MAY THROW, STRONG (E: alloc, copy)
            }
            BOOST_CATCH(...)
            {
                // NOTE: exception-safety
                // if the insert fails above, the element won't be stored in the tree, so delete it

                rtree::visitors::destroy<MembersHolder>::apply(base::m_element.second, base::m_allocators);

                BOOST_RETHROW                                                                                 // RETHROW
            }
            BOOST_CATCH_END

            // first insert
            if ( 0 == InsertIndex )
            {
                base::handle_possible_reinsert_or_split_of_root(n);                                         // MAY THROW (E: alloc, copy, N: alloc)
            }
            // not the first insert
            else
            {
                base::handle_possible_split(n);                                                             // MAY THROW (E: alloc, N: alloc)
            }
        }

        base::recalculate_aabb_if_necessary(n);
    }

    inline void operator()(leaf &)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "this visitor can't be used for a leaf");
    }
};

template <size_t InsertIndex, typename Value, typename MembersHolder>
struct level_insert<InsertIndex, Value, MembersHolder, true>
    : public level_insert_base<InsertIndex, typename MembersHolder::value_type, MembersHolder>
{
    typedef level_insert_base<InsertIndex, typename MembersHolder::value_type, MembersHolder> base;
    typedef typename base::node node;
    typedef typename base::internal_node internal_node;
    typedef typename base::leaf leaf;

    typedef typename MembersHolder::value_type value_type;
    typedef typename base::parameters_type parameters_type;
    typedef typename base::translator_type translator_type;
    typedef typename base::allocators_type allocators_type;

    typedef typename base::node_pointer node_pointer;
    typedef typename base::size_type size_type;

    inline level_insert(node_pointer & root,
                        size_type & leafs_level,
                        value_type const& v,
                        parameters_type const& parameters,
                        translator_type const& translator,
                        allocators_type & allocators,
                        size_type relative_level)
        : base(root, leafs_level, v, parameters, translator, allocators, relative_level)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level, "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_level, "unexpected level");

        // next traversing step
        base::traverse(*this, n);                                                                       // MAY THROW (V, E: alloc, copy, N: alloc)

        BOOST_GEOMETRY_INDEX_ASSERT(0 < base::m_level, "illegal level value, level shouldn't be the root level for 0 < InsertIndex");
        
        if ( base::m_traverse_data.current_level == base::m_level - 1 )
        {
            base::handle_possible_reinsert_or_split_of_root(n);                                         // MAY THROW (E: alloc, copy, N: alloc)
        }

        base::recalculate_aabb_if_necessary(n);
    }

    inline void operator()(leaf & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level == base::m_leafs_level,
                                    "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level ||
                                    base::m_level == (std::numeric_limits<size_t>::max)(),
                                    "unexpected level");
        
        rtree::elements(n).push_back(base::m_element);                                                  // MAY THROW, STRONG (V: alloc, copy)

        base::handle_possible_split(n);                                                                 // MAY THROW (V: alloc, copy, N: alloc)
    }
};

template <typename Value, typename MembersHolder>
struct level_insert<0, Value, MembersHolder, true>
    : public level_insert_base<0, typename MembersHolder::value_type, MembersHolder>
{
    typedef level_insert_base<0, typename MembersHolder::value_type, MembersHolder> base;
    typedef typename base::node node;
    typedef typename base::internal_node internal_node;
    typedef typename base::leaf leaf;

    typedef typename MembersHolder::value_type value_type;
    typedef typename base::parameters_type parameters_type;
    typedef typename base::translator_type translator_type;
    typedef typename base::allocators_type allocators_type;

    typedef typename base::node_pointer node_pointer;
    typedef typename base::size_type size_type;

    inline level_insert(node_pointer & root,
                        size_type & leafs_level,
                        value_type const& v,
                        parameters_type const& parameters,
                        translator_type const& translator,
                        allocators_type & allocators,
                        size_type relative_level)
        : base(root, leafs_level, v, parameters, translator, allocators, relative_level)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level,
                                    "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_level,
                                    "unexpected level");

        // next traversing step
        base::traverse(*this, n);                                                                       // MAY THROW (V: alloc, copy, N: alloc)

        base::recalculate_aabb_if_necessary(n);
    }

    inline void operator()(leaf & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level == base::m_leafs_level,
                                    "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level ||
                                    base::m_level == (std::numeric_limits<size_t>::max)(),
                                    "unexpected level");

        rtree::elements(n).push_back(base::m_element);                                                  // MAY THROW, STRONG (V: alloc, copy)

        base::handle_possible_reinsert_or_split_of_root(n);                                             // MAY THROW (V: alloc, copy, N: alloc)
        
        base::recalculate_aabb_if_necessary(n);
    }
};

} // namespace rstar

// R*-tree insert visitor
// After passing the Element to insert visitor the Element is managed by the tree
// I.e. one should not delete the node passed to the insert visitor after exception is thrown
// because this visitor may delete it
template <typename Element, typename MembersHolder>
class insert<Element, MembersHolder, insert_reinsert_tag>
    : public MembersHolder::visitor
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename allocators_type::node_pointer node_pointer;
    typedef typename allocators_type::size_type size_type;

public:
    inline insert(node_pointer & root,
                  size_type & leafs_level,
                  Element const& element,
                  parameters_type const& parameters,
                  translator_type const& translator,
                  allocators_type & allocators,
                  size_type relative_level = 0)
        : m_root(root), m_leafs_level(leafs_level), m_element(element)
        , m_parameters(parameters), m_translator(translator)
        , m_relative_level(relative_level), m_allocators(allocators)
    {}

    inline void operator()(internal_node & n)
    {
        boost::ignore_unused(n);
        BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_root), "current node should be the root");

        // Distinguish between situation when reinserts are required and use adequate visitor, otherwise use default one
        if ( m_parameters.get_reinserted_elements() > 0 )
        {
            rstar::level_insert<0, Element, MembersHolder> lins_v(
                m_root, m_leafs_level, m_element, m_parameters, m_translator, m_allocators, m_relative_level);

            rtree::apply_visitor(lins_v, *m_root);                                                              // MAY THROW (V, E: alloc, copy, N: alloc)

            if ( !lins_v.result_elements.empty() )
            {
                recursive_reinsert(lins_v.result_elements, lins_v.result_relative_level);                       // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
        else
        {
            visitors::insert<Element, MembersHolder, insert_default_tag> ins_v(
                m_root, m_leafs_level, m_element, m_parameters, m_translator, m_allocators, m_relative_level);

            rtree::apply_visitor(ins_v, *m_root); 
        }
    }

    inline void operator()(leaf & n)
    {
        boost::ignore_unused(n);
        BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<leaf>(*m_root), "current node should be the root");

        // Distinguish between situation when reinserts are required and use adequate visitor, otherwise use default one
        if ( m_parameters.get_reinserted_elements() > 0 )
        {
            rstar::level_insert<0, Element, MembersHolder> lins_v(
                m_root, m_leafs_level, m_element, m_parameters, m_translator, m_allocators, m_relative_level);

            rtree::apply_visitor(lins_v, *m_root);                                                              // MAY THROW (V, E: alloc, copy, N: alloc)

            // we're in the root, so root should be split and there should be no elements to reinsert
            BOOST_GEOMETRY_INDEX_ASSERT(lins_v.result_elements.empty(), "unexpected state");
        }
        else
        {
            visitors::insert<Element, MembersHolder, insert_default_tag> ins_v(
                m_root, m_leafs_level, m_element, m_parameters, m_translator, m_allocators, m_relative_level);

            rtree::apply_visitor(ins_v, *m_root); 
        }
    }

private:
    template <typename Elements>
    inline void recursive_reinsert(Elements & elements, size_t relative_level)
    {
        typedef typename Elements::value_type element_type;

        // reinsert children starting from the minimum distance
        typename Elements::reverse_iterator it = elements.rbegin();
        for ( ; it != elements.rend() ; ++it)
        {
            rstar::level_insert<1, element_type, MembersHolder> lins_v(
                m_root, m_leafs_level, *it, m_parameters, m_translator, m_allocators, relative_level);

            BOOST_TRY
            {
                rtree::apply_visitor(lins_v, *m_root);                                                          // MAY THROW (V, E: alloc, copy, N: alloc)
            }
            BOOST_CATCH(...)
            {
                ++it;
                for ( ; it != elements.rend() ; ++it)
                    rtree::destroy_element<MembersHolder>::apply(*it, m_allocators);
                BOOST_RETHROW                                                                                     // RETHROW
            }
            BOOST_CATCH_END

            BOOST_GEOMETRY_INDEX_ASSERT(relative_level + 1 == lins_v.result_relative_level, "unexpected level");

            // non-root relative level
            if ( lins_v.result_relative_level < m_leafs_level && !lins_v.result_elements.empty())
            {
                recursive_reinsert(lins_v.result_elements, lins_v.result_relative_level);                   // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
    }

    node_pointer & m_root;
    size_type & m_leafs_level;
    Element const& m_element;

    parameters_type const& m_parameters;
    translator_type const& m_translator;

    size_type m_relative_level;

    allocators_type & m_allocators;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_INSERT_HPP

/* insert.hpp
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
*/