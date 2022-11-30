// Boost.Geometry Index
//
// R-tree linear split algorithm implementation
//
// Copyright (c) 2008 Federico J. Fernandez.
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_LINEAR_REDISTRIBUTE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_LINEAR_REDISTRIBUTE_ELEMENTS_HPP

#include <type_traits>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/algorithms/content.hpp>
#include <boost/geometry/index/detail/bounded_view.hpp>

#include <boost/geometry/index/detail/rtree/node/node.hpp>
#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

namespace linear {

template <typename R, typename T>
inline R difference_dispatch(T const& from, T const& to, std::false_type /*is_unsigned*/)
{
    return to - from;
}

template <typename R, typename T>
inline R difference_dispatch(T const& from, T const& to, std::true_type /*is_unsigned*/)
{
    return from <= to ? R(to - from) : -R(from - to);
}

template <typename R, typename T>
inline R difference(T const& from, T const& to)
{
    BOOST_GEOMETRY_STATIC_ASSERT((! std::is_unsigned<R>::value),
        "Result can not be an unsigned type.",
        R);

    return difference_dispatch<R>(from, to, std::is_unsigned<T>());
}

// TODO: awulkiew
// In general, all aerial Indexables in the tree with box-like nodes will be analyzed as boxes
// because they must fit into larger box. Therefore the algorithm could be the same for Bounds type.
// E.g. if Bounds type is sphere, Indexables probably should be analyzed as spheres.
// 1. View could be provided to 'see' all Indexables as Bounds type.
//    Not ok in the case of big types like Ring, however it's possible that Rings won't be supported,
//    only simple types. Even then if we consider storing Box inside the Sphere we must calculate
//    the bounding sphere 2x for each box because there are 2 loops. For each calculation this means
//    4-2d or 8-3d expansions or -, / and sqrt().
// 2. Additional container could be used and reused if the Indexable type is other than the Bounds type.

// IMPORTANT!
// Still probably the best way would be providing specialized algorithms for each Indexable-Bounds pair!
// Probably on pick_seeds algorithm level - For Bounds=Sphere seeds would be choosen differently

// TODO: awulkiew
// there are loops inside find_greatest_normalized_separation::apply()
// iteration is done for each DimensionIndex.
// Separations and seeds for all DimensionIndex(es) could be calculated at once, stored, then the greatest would be choosen.

// The following struct/method was adapted for the preliminary version of the R-tree. Then it was called:
// void find_normalized_separations(std::vector<Box> const& boxes, T& separation, unsigned int& first, unsigned int& second) const

template <typename Elements, typename Parameters, typename Translator, typename Tag, size_t DimensionIndex>
struct find_greatest_normalized_separation
{
    typedef typename Elements::value_type element_type;
    typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
    typedef typename coordinate_type<indexable_type>::type coordinate_type;

    typedef std::conditional_t
        <
            std::is_integral<coordinate_type>::value,
            double,
            coordinate_type
        > separation_type;

    typedef typename geometry::point_type<indexable_type>::type point_type;
    typedef geometry::model::box<point_type> bounds_type;
    typedef index::detail::bounded_view
        <
            indexable_type, bounds_type,
            typename index::detail::strategy_type<Parameters>::type
        > bounded_view_type;

    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& translator,
                             separation_type & separation,
                             size_t & seed1,
                             size_t & seed2)
    {
        const size_t elements_count = parameters.get_max_elements() + 1;
        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == elements_count, "unexpected number of elements");
        BOOST_GEOMETRY_INDEX_ASSERT(2 <= elements_count, "unexpected number of elements");

        typename index::detail::strategy_type<Parameters>::type const&
            strategy = index::detail::get_strategy(parameters);

        // find the lowest low, highest high
        bounded_view_type bounded_indexable_0(rtree::element_indexable(elements[0], translator),
                                              strategy);
        coordinate_type lowest_low = geometry::get<min_corner, DimensionIndex>(bounded_indexable_0);
        coordinate_type highest_high = geometry::get<max_corner, DimensionIndex>(bounded_indexable_0);

        // and the lowest high
        coordinate_type lowest_high = highest_high;
        size_t lowest_high_index = 0;
        for ( size_t i = 1 ; i < elements_count ; ++i )
        {
            bounded_view_type bounded_indexable(rtree::element_indexable(elements[i], translator),
                                                strategy);
            coordinate_type min_coord = geometry::get<min_corner, DimensionIndex>(bounded_indexable);
            coordinate_type max_coord = geometry::get<max_corner, DimensionIndex>(bounded_indexable);

            if ( max_coord < lowest_high )
            {
                lowest_high = max_coord;
                lowest_high_index = i;
            }

            if ( min_coord < lowest_low )
                lowest_low = min_coord;

            if ( highest_high < max_coord )
                highest_high = max_coord;
        }

        // find the highest low
        size_t highest_low_index = lowest_high_index == 0 ? 1 : 0;
        bounded_view_type bounded_indexable_hl(rtree::element_indexable(elements[highest_low_index], translator),
                                               strategy);
        coordinate_type highest_low = geometry::get<min_corner, DimensionIndex>(bounded_indexable_hl);
        for ( size_t i = highest_low_index ; i < elements_count ; ++i )
        {
            bounded_view_type bounded_indexable(rtree::element_indexable(elements[i], translator),
                                                strategy);
            coordinate_type min_coord = geometry::get<min_corner, DimensionIndex>(bounded_indexable);
            if ( highest_low < min_coord &&
                 i != lowest_high_index )
            {
                highest_low = min_coord;
                highest_low_index = i;
            }
        }

        coordinate_type const width = highest_high - lowest_low;
        
        // highest_low - lowest_high
        separation = difference<separation_type>(lowest_high, highest_low);
        // BOOST_GEOMETRY_INDEX_ASSERT(0 <= width);
        if ( std::numeric_limits<coordinate_type>::epsilon() < width )
            separation /= width;

        seed1 = highest_low_index;
        seed2 = lowest_high_index;

        ::boost::ignore_unused(parameters);
    }
};

// Version for points doesn't calculate normalized separation since it would always be equal to 1
// It returns two seeds most distant to each other, separation is equal to distance
template <typename Elements, typename Parameters, typename Translator, size_t DimensionIndex>
struct find_greatest_normalized_separation<Elements, Parameters, Translator, point_tag, DimensionIndex>
{
    typedef typename Elements::value_type element_type;
    typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
    typedef typename coordinate_type<indexable_type>::type coordinate_type;

    typedef coordinate_type separation_type;

    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& translator,
                             separation_type & separation,
                             size_t & seed1,
                             size_t & seed2)
    {
        const size_t elements_count = parameters.get_max_elements() + 1;
        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == elements_count, "unexpected number of elements");
        BOOST_GEOMETRY_INDEX_ASSERT(2 <= elements_count, "unexpected number of elements");

        // find the lowest low, highest high
        coordinate_type lowest = geometry::get<DimensionIndex>(rtree::element_indexable(elements[0], translator));
        coordinate_type highest = geometry::get<DimensionIndex>(rtree::element_indexable(elements[0], translator));
        size_t lowest_index = 0;
        size_t highest_index = 0;
        for ( size_t i = 1 ; i < elements_count ; ++i )
        {
            coordinate_type coord = geometry::get<DimensionIndex>(rtree::element_indexable(elements[i], translator));

            if ( coord < lowest )
            {
                lowest = coord;
                lowest_index = i;
            }

            if ( highest < coord )
            {
                highest = coord;
                highest_index = i;
            }
        }

        separation = highest - lowest;
        seed1 = lowest_index;
        seed2 = highest_index;

        if ( lowest_index == highest_index )
            seed2 = (lowest_index + 1) % elements_count; // % is just in case since if this is true lowest_index is 0

        ::boost::ignore_unused(parameters);
    }
};

template <typename Elements, typename Parameters, typename Translator, size_t Dimension>
struct pick_seeds_impl
{
    BOOST_STATIC_ASSERT(0 < Dimension);

    typedef typename Elements::value_type element_type;
    typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;

    typedef find_greatest_normalized_separation<
        Elements, Parameters, Translator,
        typename tag<indexable_type>::type, Dimension - 1
    > find_norm_sep;

    typedef typename find_norm_sep::separation_type separation_type;

    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& tr,
                             separation_type & separation,
                             size_t & seed1,
                             size_t & seed2)
    {
        pick_seeds_impl<Elements, Parameters, Translator, Dimension - 1>::apply(elements, parameters, tr, separation, seed1, seed2);

        separation_type current_separation;
        size_t s1, s2;
        find_norm_sep::apply(elements, parameters, tr, current_separation, s1, s2);

        // in the old implementation different operator was used: <= (y axis prefered)
        if ( separation < current_separation )
        {
            separation = current_separation;
            seed1 = s1;
            seed2 = s2;
        }
    }
};

template <typename Elements, typename Parameters, typename Translator>
struct pick_seeds_impl<Elements, Parameters, Translator, 1>
{
    typedef typename Elements::value_type element_type;
    typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
    typedef typename coordinate_type<indexable_type>::type coordinate_type;

    typedef find_greatest_normalized_separation<
        Elements, Parameters, Translator,
        typename tag<indexable_type>::type, 0
    > find_norm_sep;

    typedef typename find_norm_sep::separation_type separation_type;

    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& tr,
                             separation_type & separation,
                             size_t & seed1,
                             size_t & seed2)
    {
        find_norm_sep::apply(elements, parameters, tr, separation, seed1, seed2);
    }
};

// from void linear_pick_seeds(node_pointer const& n, unsigned int &seed1, unsigned int &seed2) const

template <typename Elements, typename Parameters, typename Translator>
inline void pick_seeds(Elements const& elements,
                       Parameters const& parameters,
                       Translator const& tr,
                       size_t & seed1,
                       size_t & seed2)
{
    typedef typename Elements::value_type element_type;
    typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;

    typedef pick_seeds_impl
        <
            Elements, Parameters, Translator,
            geometry::dimension<indexable_type>::value
        > impl;
    typedef typename impl::separation_type separation_type;

    separation_type separation = 0;
    impl::apply(elements, parameters, tr, separation, seed1, seed2);
}

} // namespace linear

// from void split_node(node_pointer const& n, node_pointer& n1, node_pointer& n2) const

template <typename MembersHolder>
struct redistribute_elements<MembersHolder, linear_tag>
{
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

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
        typedef typename index::detail::default_content_result<box_type>::type content_type;

        typename index::detail::strategy_type<parameters_type>::type const&
            strategy = index::detail::get_strategy(parameters);

        elements_type & elements1 = rtree::elements(n);
        elements_type & elements2 = rtree::elements(second_node);
        const size_t elements1_count = parameters.get_max_elements() + 1;

        BOOST_GEOMETRY_INDEX_ASSERT(elements1.size() == elements1_count, "unexpected number of elements");

        // copy original elements - use in-memory storage (std::allocator)
        // TODO: move if noexcept
        typedef typename rtree::container_from_elements_type<elements_type, element_type>::type
            container_type;
        container_type elements_copy(elements1.begin(), elements1.end());                                   // MAY THROW, STRONG (alloc, copy)

        // calculate initial seeds
        size_t seed1 = 0;
        size_t seed2 = 0;
        linear::pick_seeds(elements_copy, parameters, translator, seed1, seed2);

        // prepare nodes' elements containers
        elements1.clear();
        BOOST_GEOMETRY_INDEX_ASSERT(elements2.empty(), "unexpected container state");

        BOOST_TRY
        {
            // add seeds
            elements1.push_back(elements_copy[seed1]);                                                      // MAY THROW, STRONG (copy)
            elements2.push_back(elements_copy[seed2]);                                                      // MAY THROW, STRONG (alloc, copy)

            // calculate boxes
            detail::bounds(rtree::element_indexable(elements_copy[seed1], translator),
                           box1, strategy);
            detail::bounds(rtree::element_indexable(elements_copy[seed2], translator),
                           box2, strategy);

            // initialize areas
            content_type content1 = index::detail::content(box1);
            content_type content2 = index::detail::content(box2);

            BOOST_GEOMETRY_INDEX_ASSERT(2 <= elements1_count, "unexpected elements number");
            size_t remaining = elements1_count - 2;

            // redistribute the rest of the elements
            for ( size_t i = 0 ; i < elements1_count ; ++i )
            {
                if (i != seed1 && i != seed2)
                {
                    element_type const& elem = elements_copy[i];
                    indexable_type const& indexable = rtree::element_indexable(elem, translator);

                    // if there is small number of elements left and the number of elements in node is lesser than min_elems
                    // just insert them to this node
                    if ( elements1.size() + remaining <= parameters.get_min_elements() )
                    {
                        elements1.push_back(elem);                                                          // MAY THROW, STRONG (copy)
                        index::detail::expand(box1, indexable, strategy);
                        content1 = index::detail::content(box1);
                    }
                    else if ( elements2.size() + remaining <= parameters.get_min_elements() )
                    {
                        elements2.push_back(elem);                                                          // MAY THROW, STRONG (alloc, copy)
                        index::detail::expand(box2, indexable, strategy);
                        content2 = index::detail::content(box2);
                    }
                    // choose better node and insert element
                    else
                    {
                        // calculate enlarged boxes and areas
                        box_type enlarged_box1(box1);
                        box_type enlarged_box2(box2);
                        index::detail::expand(enlarged_box1, indexable, strategy);
                        index::detail::expand(enlarged_box2, indexable, strategy);
                        content_type enlarged_content1 = index::detail::content(enlarged_box1);
                        content_type enlarged_content2 = index::detail::content(enlarged_box2);

                        content_type content_increase1 = enlarged_content1 - content1;
                        content_type content_increase2 = enlarged_content2 - content2;

                        // choose group which box content have to be enlarged least or has smaller content or has fewer elements
                        if ( content_increase1 < content_increase2 ||
                                ( content_increase1 == content_increase2 &&
                                    ( content1 < content2 ||
                                        ( content1 == content2 && elements1.size() <= elements2.size() ) ) ) )
                        {
                            elements1.push_back(elem);                                                      // MAY THROW, STRONG (copy)
                            box1 = enlarged_box1;
                            content1 = enlarged_content1;
                        }
                        else
                        {
                            elements2.push_back(elem);                                                      // MAY THROW, STRONG (alloc, copy)
                            box2 = enlarged_box2;
                            content2 = enlarged_content2;
                        }
                    }
                
                    BOOST_GEOMETRY_INDEX_ASSERT(0 < remaining, "unexpected value");
                    --remaining;
                }
            }
        }
        BOOST_CATCH(...)
        {
            elements1.clear();
            elements2.clear();

            rtree::destroy_elements<MembersHolder>::apply(elements_copy, allocators);
            //elements_copy.clear();

            BOOST_RETHROW                                                                                     // RETHROW, BASIC
        }
        BOOST_CATCH_END
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_LINEAR_REDISTRIBUTE_ELEMENTS_HPP

/* redistribute_elements.hpp
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
*/