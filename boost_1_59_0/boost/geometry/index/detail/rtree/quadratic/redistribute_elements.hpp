// Boost.Geometry Index
//
// R-tree quadratic split algorithm implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUADRATIC_REDISTRIBUTE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUADRATIC_REDISTRIBUTE_ELEMENTS_HPP

#include <algorithm>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>
#include <boost/geometry/index/detail/algorithms/union_content.hpp>

#include <boost/geometry/index/detail/bounded_view.hpp>

#include <boost/geometry/index/detail/rtree/node/node.hpp>
#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

namespace quadratic {

template <typename Box, typename Elements, typename Parameters, typename Translator>
inline void pick_seeds(Elements const& elements,
                       Parameters const& parameters,
                       Translator const& tr,
                       size_t & seed1,
                       size_t & seed2)
{
    typedef typename Elements::value_type element_type;
    typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
    typedef Box box_type;
    typedef typename index::detail::default_content_result<box_type>::type content_type;
    typedef typename index::detail::strategy_type<Parameters>::type strategy_type;
    typedef index::detail::bounded_view
        <
            indexable_type, box_type, strategy_type
        > bounded_indexable_view;

    const size_t elements_count = parameters.get_max_elements() + 1;
    BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == elements_count, "wrong number of elements");
    BOOST_GEOMETRY_INDEX_ASSERT(2 <= elements_count, "unexpected number of elements");

    strategy_type const& strategy = index::detail::get_strategy(parameters);

    content_type greatest_free_content = 0;
    seed1 = 0;
    seed2 = 1;

    for ( size_t i = 0 ; i < elements_count - 1 ; ++i )
    {
        for ( size_t j = i + 1 ; j < elements_count ; ++j )
        {
            indexable_type const& ind1 = rtree::element_indexable(elements[i], tr);
            indexable_type const& ind2 = rtree::element_indexable(elements[j], tr);

            box_type enlarged_box;
            index::detail::bounds(ind1, enlarged_box, strategy);
            index::detail::expand(enlarged_box, ind2, strategy);

            bounded_indexable_view bounded_ind1(ind1, strategy);
            bounded_indexable_view bounded_ind2(ind2, strategy);
            content_type free_content = ( index::detail::content(enlarged_box)
                                            - index::detail::content(bounded_ind1) )
                                                - index::detail::content(bounded_ind2);
                
            if ( greatest_free_content < free_content )
            {
                greatest_free_content = free_content;
                seed1 = i;
                seed2 = j;
            }
        }
    }

    ::boost::ignore_unused(parameters);
}

} // namespace quadratic

template <typename MembersHolder>
struct redistribute_elements<MembersHolder, quadratic_tag>
{
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename index::detail::default_content_result<box_type>::type content_type;

    template <typename Node>
    static inline void apply(Node & n,
                             Node & second_node,
                             box_type & box1,
                             box_type & box2,
                             parameters_type const& parameters,
                             translator_type const& translator,
                             allocators_type & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        typedef typename rtree::element_indexable_type<element_type, translator_type>::type indexable_type;

        elements_type & elements1 = rtree::elements(n);
        elements_type & elements2 = rtree::elements(second_node);
        
        BOOST_GEOMETRY_INDEX_ASSERT(elements1.size() == parameters.get_max_elements() + 1, "unexpected elements number");

        // copy original elements - use in-memory storage (std::allocator)
        // TODO: move if noexcept
        typedef typename rtree::container_from_elements_type<elements_type, element_type>::type
            container_type;
        container_type elements_copy(elements1.begin(), elements1.end());                                   // MAY THROW, STRONG (alloc, copy)
        container_type elements_backup(elements1.begin(), elements1.end());                                 // MAY THROW, STRONG (alloc, copy)
        
        // calculate initial seeds
        size_t seed1 = 0;
        size_t seed2 = 0;
        quadratic::pick_seeds<box_type>(elements_copy, parameters, translator, seed1, seed2);

        // prepare nodes' elements containers
        elements1.clear();
        BOOST_GEOMETRY_INDEX_ASSERT(elements2.empty(), "second node's elements container should be empty");

        BOOST_TRY
        {
            typename index::detail::strategy_type<parameters_type>::type const&
                strategy = index::detail::get_strategy(parameters);

            // add seeds
            elements1.push_back(elements_copy[seed1]);                                                      // MAY THROW, STRONG (copy)
            elements2.push_back(elements_copy[seed2]);                                                      // MAY THROW, STRONG (alloc, copy)

            // calculate boxes
            detail::bounds(rtree::element_indexable(elements_copy[seed1], translator),
                           box1, strategy);
            detail::bounds(rtree::element_indexable(elements_copy[seed2], translator),
                           box2, strategy);

            // remove seeds
            if (seed1 < seed2)
            {
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed2);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed1);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
            }
            else
            {
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed1);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed2);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
            }

            // initialize areas
            content_type content1 = index::detail::content(box1);
            content_type content2 = index::detail::content(box2);

            size_t remaining = elements_copy.size();

            // redistribute the rest of the elements
            while ( !elements_copy.empty() )
            {
                typename container_type::reverse_iterator el_it = elements_copy.rbegin();
                bool insert_into_group1 = false;

                size_t elements1_count = elements1.size();
                size_t elements2_count = elements2.size();

                // if there is small number of elements left and the number of elements in node is lesser than min_elems
                // just insert them to this node
                if ( elements1_count + remaining <= parameters.get_min_elements() )
                {
                    insert_into_group1 = true;
                }
                else if ( elements2_count + remaining <= parameters.get_min_elements() )
                {
                    insert_into_group1 = false;
                }
                // insert the best element
                else
                {
                    // find element with minimum groups areas increses differences
                    content_type content_increase1 = 0;
                    content_type content_increase2 = 0;
                    el_it = pick_next(elements_copy.rbegin(), elements_copy.rend(),
                                      box1, box2, content1, content2,
                                      translator, strategy,
                                      content_increase1, content_increase2);

                    if ( content_increase1 < content_increase2 ||
                         ( content_increase1 == content_increase2 && ( content1 < content2 ||
                           ( content1 == content2 && elements1_count <= elements2_count ) )
                         ) )
                    {
                        insert_into_group1 = true;
                    }
                    else
                    {
                        insert_into_group1 = false;
                    }
                }

                // move element to the choosen group
                element_type const& elem = *el_it;
                indexable_type const& indexable = rtree::element_indexable(elem, translator);

                if ( insert_into_group1 )
                {
                    elements1.push_back(elem);                                                              // MAY THROW, STRONG (copy)
                    index::detail::expand(box1, indexable, strategy);
                    content1 = index::detail::content(box1);
                }
                else
                {
                    elements2.push_back(elem);                                                              // MAY THROW, STRONG (alloc, copy)
                    index::detail::expand(box2, indexable, strategy);
                    content2 = index::detail::content(box2);
                }

                BOOST_GEOMETRY_INDEX_ASSERT(!elements_copy.empty(), "expected more elements");
                typename container_type::iterator el_it_base = el_it.base();
                rtree::move_from_back(elements_copy, --el_it_base);                                         // MAY THROW, STRONG (copy)
                elements_copy.pop_back();

                BOOST_GEOMETRY_INDEX_ASSERT(0 < remaining, "expected more remaining elements");
                --remaining;
            }
        }
        BOOST_CATCH(...)
        {
            //elements_copy.clear();
            elements1.clear();
            elements2.clear();

            rtree::destroy_elements<MembersHolder>::apply(elements_backup, allocators);
            //elements_backup.clear();

            BOOST_RETHROW                                                                                     // RETHROW, BASIC
        }
        BOOST_CATCH_END
    }

    // TODO: awulkiew - change following function to static member of the pick_next class?

    template <typename It>
    static inline It pick_next(It first, It last,
                               box_type const& box1, box_type const& box2,
                               content_type const& content1, content_type const& content2,
                               translator_type const& translator,
                               typename index::detail::strategy_type<parameters_type>::type const& strategy,
                               content_type & out_content_increase1, content_type & out_content_increase2)
    {
        typedef typename boost::iterator_value<It>::type element_type;
        typedef typename rtree::element_indexable_type<element_type, translator_type>::type indexable_type;

        content_type greatest_content_incrase_diff = 0;
        It out_it = first;
        out_content_increase1 = 0;
        out_content_increase2 = 0;
        
        // find element with greatest difference between increased group's boxes areas
        for ( It el_it = first ; el_it != last ; ++el_it )
        {
            indexable_type const& indexable = rtree::element_indexable(*el_it, translator);

            // calculate enlarged boxes and areas
            box_type enlarged_box1(box1);
            box_type enlarged_box2(box2);
            index::detail::expand(enlarged_box1, indexable, strategy);
            index::detail::expand(enlarged_box2, indexable, strategy);
            content_type enlarged_content1 = index::detail::content(enlarged_box1);
            content_type enlarged_content2 = index::detail::content(enlarged_box2);

            content_type content_incrase1 = (enlarged_content1 - content1);
            content_type content_incrase2 = (enlarged_content2 - content2);

            content_type content_incrase_diff = content_incrase1 < content_incrase2 ?
                content_incrase2 - content_incrase1 : content_incrase1 - content_incrase2;

            if ( greatest_content_incrase_diff < content_incrase_diff )
            {
                greatest_content_incrase_diff = content_incrase_diff;
                out_it = el_it;
                out_content_increase1 = content_incrase1;
                out_content_increase2 = content_incrase2;
            }
        }

        return out_it;
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUADRATIC_REDISTRIBUTE_ELEMENTS_HPP

/* redistribute_elements.hpp
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
*/