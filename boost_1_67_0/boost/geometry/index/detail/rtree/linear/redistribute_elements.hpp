// Boost.Geometry Index
//
// R-tree linear split algorithm implementation
//
// Copyright (c) 2008 Federico J. Fernandez.
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_LINEAR_REDISTRIBUTE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_LINEAR_REDISTRIBUTE_ELEMENTS_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/type_traits/is_unsigned.hpp>

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
inline R difference_dispatch(T const& from, T const& to, ::boost::mpl::bool_<false> const& /*is_unsigned*/)
{
    return to - from;
}

template <typename R, typename T>
inline R difference_dispatch(T const& from, T const& to, ::boost::mpl::bool_<true> const& /*is_unsigned*/)
{
    return from <= to ? R(to - from) : -R(from - to);
}

template <typename R, typename T>
inline R difference(T const& from, T const& to)
{
    BOOST_MPL_ASSERT_MSG(!boost::is_unsigned<R>::value, RESULT_CANT_BE_UNSIGNED, (R));

    typedef ::boost::mpl::bool_<
        boost::is_unsigned<T>::value
    > is_unsigned;

    return difference_dispatch<R>(from, to, is_unsigned());
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

    typedef typename boost::mpl::if_c<
        boost::is_integral<coordinate_type>::value,
        double,
        coordinate_type
    >::type separation_type;

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