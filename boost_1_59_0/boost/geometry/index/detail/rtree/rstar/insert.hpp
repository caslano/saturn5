// Boost.Geometry Index
//
// R-tree R*-tree insert algorithm implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_INSERT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_INSERT_HPP

#include <type_traits>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/comparable_distance/interface.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>
#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

namespace rstar {

// Utility to distinguish between default and non-default index strategy
template <typename Point1, typename Point2, typename Strategy>
struct comparable_distance
{
    typedef typename geometry::comparable_distance_result
        <
            Point1, Point2, Strategy
        >::type result_type;

    static inline result_type call(Point1 const& p1, Point2 const& p2, Strategy const& s)
    {
        return geometry::comparable_distance(p1, p2, s);
    }
};

template <typename Point1, typename Point2>
struct comparable_distance<Point1, Point2, default_strategy>
{
    typedef typename geometry::default_comparable_distance_result
        <
            Point1, Point2
        >::type result_type;

    static inline result_type call(Point1 const& p1, Point2 const& p2, default_strategy const& )
    {
        return geometry::comparable_distance(p1, p2);
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
        typedef rstar::comparable_distance
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

        auto const& strategy = index::detail::get_strategy(parameters);

        // calculate current node's center
        point_type node_center;
        geometry::centroid(rtree::elements(*parent)[current_child_index].first, node_center,
                           strategy);

        // fill the container of centers' distances of children from current node's center
        typedef typename index::detail::rtree::container_from_elements_type<
            elements_type,
            std::pair<comparable_distance_type, element_type>
        >::type sorted_elements_type;

        sorted_elements_type sorted_elements;
        // If constructor is used instead of resize() MS implementation leaks here
        sorted_elements.reserve(elements_count);                                                         // MAY THROW, STRONG (V, E: alloc, copy)
        
        for ( typename elements_type::const_iterator it = elements.begin() ;
              it != elements.end() ; ++it )
        {
            point_type element_center;
            geometry::centroid(rtree::element_indexable(*it, translator), element_center,
                               strategy);
            sorted_elements.push_back(std::make_pair(
                comparable_distance_pp::call(node_center, element_center, strategy),
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
    bool IsValue = std::is_same<Element, typename MembersHolder::value_type>::value
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
    bool IsValue = std::is_same<Element, typename MembersHolder::value_type>::value
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