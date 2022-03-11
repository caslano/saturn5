// Boost.Geometry Index
//
// R-tree R*-tree split algorithm implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_REDISTRIBUTE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_REDISTRIBUTE_ELEMENTS_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/index/detail/algorithms/intersection_content.hpp>
#include <boost/geometry/index/detail/algorithms/margin.hpp>
#include <boost/geometry/index/detail/algorithms/nth_element.hpp>
#include <boost/geometry/index/detail/algorithms/union_content.hpp>

#include <boost/geometry/index/detail/bounded_view.hpp>

#include <boost/geometry/index/detail/rtree/node/node.hpp>
#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

namespace rstar {

template <typename Element, typename Parameters, typename Translator, typename Tag, size_t Corner, size_t AxisIndex>
class element_axis_corner_less
{
    typedef typename rtree::element_indexable_type<Element, Translator>::type indexable_type;
    typedef typename geometry::point_type<indexable_type>::type point_type;
    typedef geometry::model::box<point_type> bounds_type;
    typedef typename index::detail::strategy_type<Parameters>::type strategy_type;
    typedef index::detail::bounded_view
        <
            indexable_type, bounds_type, strategy_type
        > bounded_view_type;

public:
    element_axis_corner_less(Translator const& tr, strategy_type const& strategy)
        : m_tr(tr), m_strategy(strategy)
    {}

    bool operator()(Element const& e1, Element const& e2) const
    {
        bounded_view_type bounded_ind1(rtree::element_indexable(e1, m_tr), m_strategy);
        bounded_view_type bounded_ind2(rtree::element_indexable(e2, m_tr), m_strategy);

        return geometry::get<Corner, AxisIndex>(bounded_ind1)
            < geometry::get<Corner, AxisIndex>(bounded_ind2);
    }

private:
    Translator const& m_tr;
    strategy_type const& m_strategy;
};

template <typename Element, typename Parameters, typename Translator, size_t Corner, size_t AxisIndex>
class element_axis_corner_less<Element, Parameters, Translator, box_tag, Corner, AxisIndex>
{
    typedef typename index::detail::strategy_type<Parameters>::type strategy_type;

public:
    element_axis_corner_less(Translator const& tr, strategy_type const&)
        : m_tr(tr)
    {}

    bool operator()(Element const& e1, Element const& e2) const
    {
        return geometry::get<Corner, AxisIndex>(rtree::element_indexable(e1, m_tr))
            < geometry::get<Corner, AxisIndex>(rtree::element_indexable(e2, m_tr));
    }

private:
    Translator const& m_tr;
};

template <typename Element, typename Parameters, typename Translator, size_t Corner, size_t AxisIndex>
class element_axis_corner_less<Element, Parameters, Translator, point_tag, Corner, AxisIndex>
{
    typedef typename index::detail::strategy_type<Parameters>::type strategy_type;

public:
    element_axis_corner_less(Translator const& tr, strategy_type const& )
        : m_tr(tr)
    {}

    bool operator()(Element const& e1, Element const& e2) const
    {
        return geometry::get<AxisIndex>(rtree::element_indexable(e1, m_tr))
            < geometry::get<AxisIndex>(rtree::element_indexable(e2, m_tr));
    }

private:
    Translator const& m_tr;
};

template <typename Box, size_t Corner, size_t AxisIndex>
struct choose_split_axis_and_index_for_corner
{
    typedef typename index::detail::default_margin_result<Box>::type margin_type;
    typedef typename index::detail::default_content_result<Box>::type content_type;

    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_index,
                             margin_type & sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        typedef typename Elements::value_type element_type;
        typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
        typedef typename tag<indexable_type>::type indexable_tag;

        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == parameters.get_max_elements() + 1, "wrong number of elements");

        typename index::detail::strategy_type<Parameters>::type const&
            strategy = index::detail::get_strategy(parameters);

        // copy elements
        Elements elements_copy(elements);                                                                       // MAY THROW, STRONG (alloc, copy)
        
        size_t const index_first = parameters.get_min_elements();
        size_t const index_last = parameters.get_max_elements() - parameters.get_min_elements() + 2;

        // sort elements
        element_axis_corner_less
            <
                element_type, Parameters, Translator, indexable_tag, Corner, AxisIndex
            > elements_less(translator, strategy);
        std::sort(elements_copy.begin(), elements_copy.end(), elements_less);                                   // MAY THROW, BASIC (copy)
//        {
//            typename Elements::iterator f = elements_copy.begin() + index_first;
//            typename Elements::iterator l = elements_copy.begin() + index_last;
//            // NOTE: for stdlibc++ shipped with gcc 4.8.2 std::nth_element is replaced with std::sort anyway
//            index::detail::nth_element(elements_copy.begin(), f, elements_copy.end(), elements_less);                // MAY THROW, BASIC (copy)
//            index::detail::nth_element(f, l, elements_copy.end(), elements_less);                                    // MAY THROW, BASIC (copy)
//            std::sort(f, l, elements_less);                                                                   // MAY THROW, BASIC (copy)
//        }

        // init outputs
        choosen_index = index_first;
        sum_of_margins = 0;
        smallest_overlap = (std::numeric_limits<content_type>::max)();
        smallest_content = (std::numeric_limits<content_type>::max)();

        // calculate sum of margins for all distributions
        for ( size_t i = index_first ; i < index_last ; ++i )
        {
            // TODO - awulkiew: may be optimized - box of group 1 may be initialized with
            // box of min_elems number of elements and expanded for each iteration by another element

            Box box1 = rtree::elements_box<Box>(elements_copy.begin(), elements_copy.begin() + i,
                                                translator, strategy);
            Box box2 = rtree::elements_box<Box>(elements_copy.begin() + i, elements_copy.end(),
                                                translator, strategy);
            
            sum_of_margins += index::detail::comparable_margin(box1) + index::detail::comparable_margin(box2);

            content_type ovl = index::detail::intersection_content(box1, box2, strategy);
            content_type con = index::detail::content(box1) + index::detail::content(box2);

            // TODO - shouldn't here be < instead of <= ?
            if ( ovl < smallest_overlap || (ovl == smallest_overlap && con <= smallest_content) )
            {
                choosen_index = i;
                smallest_overlap = ovl;
                smallest_content = con;
            }
        }

        ::boost::ignore_unused(parameters);
    }
};

//template <typename Box, size_t AxisIndex, typename ElementIndexableTag>
//struct choose_split_axis_and_index_for_axis
//{
//    BOOST_MPL_ASSERT_MSG(false, NOT_IMPLEMENTED_FOR_THIS_TAG, (ElementIndexableTag));
//};

template <typename Box, size_t AxisIndex, typename ElementIndexableTag>
struct choose_split_axis_and_index_for_axis
{
    typedef typename index::detail::default_margin_result<Box>::type margin_type;
    typedef typename index::detail::default_content_result<Box>::type content_type;

    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_corner,
                             size_t & choosen_index,
                             margin_type & sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        size_t index1 = 0;
        margin_type som1 = 0;
        content_type ovl1 = (std::numeric_limits<content_type>::max)();
        content_type con1 = (std::numeric_limits<content_type>::max)();

        choose_split_axis_and_index_for_corner<Box, min_corner, AxisIndex>
            ::apply(elements, index1,
                    som1, ovl1, con1,
                    parameters, translator);                                                                // MAY THROW, STRONG

        size_t index2 = 0;
        margin_type som2 = 0;
        content_type ovl2 = (std::numeric_limits<content_type>::max)();
        content_type con2 = (std::numeric_limits<content_type>::max)();

        choose_split_axis_and_index_for_corner<Box, max_corner, AxisIndex>
            ::apply(elements, index2,
                    som2, ovl2, con2,
                    parameters, translator);                                                                // MAY THROW, STRONG

        sum_of_margins = som1 + som2;

        if ( ovl1 < ovl2 || (ovl1 == ovl2 && con1 <= con2) )
        {
            choosen_corner = min_corner;
            choosen_index = index1;
            smallest_overlap = ovl1;
            smallest_content = con1;
        }
        else
        {
            choosen_corner = max_corner;
            choosen_index = index2;
            smallest_overlap = ovl2;
            smallest_content = con2;
        }
    }
};

template <typename Box, size_t AxisIndex>
struct choose_split_axis_and_index_for_axis<Box, AxisIndex, point_tag>
{
    typedef typename index::detail::default_margin_result<Box>::type margin_type;
    typedef typename index::detail::default_content_result<Box>::type content_type;

    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_corner,
                             size_t & choosen_index,
                             margin_type & sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        choose_split_axis_and_index_for_corner<Box, min_corner, AxisIndex>
            ::apply(elements, choosen_index,
                    sum_of_margins, smallest_overlap, smallest_content,
                    parameters, translator);                                                                // MAY THROW, STRONG

        choosen_corner = min_corner;
    }
};

template <typename Box, size_t Dimension>
struct choose_split_axis_and_index
{
    BOOST_STATIC_ASSERT(0 < Dimension);

    typedef typename index::detail::default_margin_result<Box>::type margin_type;
    typedef typename index::detail::default_content_result<Box>::type content_type;

    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_axis,
                             size_t & choosen_corner,
                             size_t & choosen_index,
                             margin_type & smallest_sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        typedef typename rtree::element_indexable_type<typename Elements::value_type, Translator>::type element_indexable_type;

        choose_split_axis_and_index<Box, Dimension - 1>
            ::apply(elements, choosen_axis, choosen_corner, choosen_index,
                    smallest_sum_of_margins, smallest_overlap, smallest_content,
                    parameters, translator);                                                                // MAY THROW, STRONG

        margin_type sum_of_margins = 0;

        size_t corner = min_corner;
        size_t index = 0;

        content_type overlap_val = (std::numeric_limits<content_type>::max)();
        content_type content_val = (std::numeric_limits<content_type>::max)();

        choose_split_axis_and_index_for_axis<
            Box,
            Dimension - 1,
            typename tag<element_indexable_type>::type
        >::apply(elements, corner, index, sum_of_margins, overlap_val, content_val, parameters, translator); // MAY THROW, STRONG

        if ( sum_of_margins < smallest_sum_of_margins )
        {
            choosen_axis = Dimension - 1;
            choosen_corner = corner;
            choosen_index = index;
            smallest_sum_of_margins = sum_of_margins;
            smallest_overlap = overlap_val;
            smallest_content = content_val;
        }
    }
};

template <typename Box>
struct choose_split_axis_and_index<Box, 1>
{
    typedef typename index::detail::default_margin_result<Box>::type margin_type;
    typedef typename index::detail::default_content_result<Box>::type content_type;

    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_axis,
                             size_t & choosen_corner,
                             size_t & choosen_index,
                             margin_type & smallest_sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        typedef typename rtree::element_indexable_type<typename Elements::value_type, Translator>::type element_indexable_type;

        choosen_axis = 0;

        choose_split_axis_and_index_for_axis<
            Box,
            0,
            typename tag<element_indexable_type>::type
        >::apply(elements, choosen_corner, choosen_index, smallest_sum_of_margins, smallest_overlap, smallest_content, parameters, translator); // MAY THROW
    }
};

template <size_t Corner, size_t Dimension, size_t I = 0>
struct nth_element
{
    BOOST_STATIC_ASSERT(0 < Dimension);
    BOOST_STATIC_ASSERT(I < Dimension);

    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements & elements, Parameters const& parameters,
                             const size_t axis, const size_t index, Translator const& tr)
    {
        //BOOST_GEOMETRY_INDEX_ASSERT(axis < Dimension, "unexpected axis value");

        if ( axis != I )
        {
            nth_element<Corner, Dimension, I + 1>::apply(elements, parameters, axis, index, tr);                     // MAY THROW, BASIC (copy)
        }
        else
        {
            typedef typename Elements::value_type element_type;
            typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
            typedef typename tag<indexable_type>::type indexable_tag;

            typename index::detail::strategy_type<Parameters>::type
                strategy = index::detail::get_strategy(parameters);

            element_axis_corner_less
                <
                    element_type, Parameters, Translator, indexable_tag, Corner, I
                > less(tr, strategy);
            index::detail::nth_element(elements.begin(), elements.begin() + index, elements.end(), less);            // MAY THROW, BASIC (copy)
        }
    }
};

template <size_t Corner, size_t Dimension>
struct nth_element<Corner, Dimension, Dimension>
{
    template <typename Elements, typename Parameters, typename Translator>
    static inline void apply(Elements & /*elements*/, Parameters const& /*parameters*/,
                             const size_t /*axis*/, const size_t /*index*/, Translator const& /*tr*/)
    {}
};

} // namespace rstar

template <typename MembersHolder>
struct redistribute_elements<MembersHolder, rstar_tag>
{
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    static const size_t dimension = geometry::dimension<box_type>::value;

    typedef typename index::detail::default_margin_result<box_type>::type margin_type;
    typedef typename index::detail::default_content_result<box_type>::type content_type;

    template <typename Node>
    static inline void apply(
        Node & n,
        Node & second_node,
        box_type & box1,
        box_type & box2,
        parameters_type const& parameters,
        translator_type const& translator,
        allocators_type & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        
        elements_type & elements1 = rtree::elements(n);
        elements_type & elements2 = rtree::elements(second_node);

        // copy original elements - use in-memory storage (std::allocator)
        // TODO: move if noexcept
        typedef typename rtree::container_from_elements_type<elements_type, element_type>::type
            container_type;
        container_type elements_copy(elements1.begin(), elements1.end());                               // MAY THROW, STRONG
        container_type elements_backup(elements1.begin(), elements1.end());                             // MAY THROW, STRONG

        size_t split_axis = 0;
        size_t split_corner = 0;
        size_t split_index = parameters.get_min_elements();
        margin_type smallest_sum_of_margins = (std::numeric_limits<margin_type>::max)();
        content_type smallest_overlap = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        // NOTE: this function internally copies passed elements
        //       why not pass mutable elements and use the same container for all axes/corners
        //       and again, the same below calling partial_sort/nth_element
        //       It would be even possible to not re-sort/find nth_element if the axis/corner
        //       was found for the last sorting - last combination of axis/corner
        rstar::choose_split_axis_and_index<box_type, dimension>
            ::apply(elements_copy,
                    split_axis, split_corner, split_index,
                    smallest_sum_of_margins, smallest_overlap, smallest_content,
                    parameters, translator);                                                            // MAY THROW, STRONG

        // TODO: awulkiew - get rid of following static_casts?
        BOOST_GEOMETRY_INDEX_ASSERT(split_axis < dimension, "unexpected value");
        BOOST_GEOMETRY_INDEX_ASSERT(split_corner == static_cast<size_t>(min_corner) || split_corner == static_cast<size_t>(max_corner), "unexpected value");
        BOOST_GEOMETRY_INDEX_ASSERT(parameters.get_min_elements() <= split_index && split_index <= parameters.get_max_elements() - parameters.get_min_elements() + 1, "unexpected value");

        // TODO: consider using nth_element
        if ( split_corner == static_cast<size_t>(min_corner) )
        {
            rstar::nth_element<min_corner, dimension>
                ::apply(elements_copy, parameters, split_axis, split_index, translator);                // MAY THROW, BASIC (copy)
        }
        else
        {
            rstar::nth_element<max_corner, dimension>
                ::apply(elements_copy, parameters, split_axis, split_index, translator);                // MAY THROW, BASIC (copy)
        }

        BOOST_TRY
        {
            typename index::detail::strategy_type<parameters_type>::type const&
                strategy = index::detail::get_strategy(parameters);

            // copy elements to nodes
            elements1.assign(elements_copy.begin(), elements_copy.begin() + split_index);               // MAY THROW, BASIC
            elements2.assign(elements_copy.begin() + split_index, elements_copy.end());                 // MAY THROW, BASIC

            // calculate boxes
            box1 = rtree::elements_box<box_type>(elements1.begin(), elements1.end(),
                                                 translator, strategy);
            box2 = rtree::elements_box<box_type>(elements2.begin(), elements2.end(),
                                                 translator, strategy);
        }
        BOOST_CATCH(...)
        {
            //elements_copy.clear();
            elements1.clear();
            elements2.clear();

            rtree::destroy_elements<MembersHolder>::apply(elements_backup, allocators);
            //elements_backup.clear();

            BOOST_RETHROW                                                                                 // RETHROW, BASIC
        }
        BOOST_CATCH_END
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_REDISTRIBUTE_ELEMENTS_HPP

/* redistribute_elements.hpp
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
*/