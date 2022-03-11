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