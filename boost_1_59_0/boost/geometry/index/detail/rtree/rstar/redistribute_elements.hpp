// Boost.Geometry Index
//
// R-tree R*-tree split algorithm implementation
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_REDISTRIBUTE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_REDISTRIBUTE_ELEMENTS_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/static_assert.hpp>

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
//    BOOST_GEOMETRY_STATIC_ASSERT_FALSE("Not implemented for this Tag type.", ElementIndexableTag);
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
oFZSPCsNpblE+WAI9DaRkbXXzHG+wib24Yo8svpL6271mfKHE7b/o+SdgjNxnnDhYGMnu7G5sW3btm0bG9u2bdvWGzt5Y9vO9/t/d+funJueqqd6erq6arr7qemanLw6JB50YAVOx5lm+cVVvioFknV+7j71bKUjuNazHr7e6l0uFfWXax3mOtXzsPxcDGa6rjEETd7FyIQJaXX0FmzTPB4CE5t0R4VsV6Plez4Qm2MY8wQv+a0csb3sc0dx799Qtiieoe6e01gAO4uYx0NxZV2eLwCo6MxV6Z2sxB+zkYHRdt+dWa3ca5gQmOl0r5Y3NOs3auGyHSWsuXV+NynDBazEMYiNdtA+qIh0T40guO3ZjUL8SbtvG00f5NTwp46cIkDMDS15xkEc1AhaNiKYcwAB+IuftNve/XnxSWycOXgAn9edCRPgj7DfyGXgPg0cH+UC7ZrZ5KeAWeRU/FRcS3pzB9TMxXZDvy+F3X5pnyL52Q92RANpxTUKb/B2wV994XL5ldRmF9YrTWc0NkUKZT+PFB2aBrxdmG4z3ImscD4mWUf7eKQ0/pWQ+UpHw4yNuY70XW7R+TMMfD1zsiz6iTYEReReIzlx46E85HTNe/RNHnrTaHC/OYUlVsG7E9VlVqp9cWcnfZV7qYHX4gOTeCDbHyTrIT03zxnNofJc+QjjvnYge1eV34CL6/qlaG3W+ETyil6kZ1niBwB3OxfZP9bfNH81Pb3KmIxVxKVC5/u5Fv8lvxxmWVgfVtPp33ipFO1GHKZjNqnyliqi6Dp779xwVEqkLp32amAfdce32rv/IH2Q31lRdpNYS1LKXAWQjm1Z8efM85gVRedqEGwgI3LEZJMFrbqlJxyyatBnFes3xOR6Qo1W6PxHLY5G0UbWiZ4u1nDyeNsxPFt+vCzkoQhL6kTIxpq0tHDvTl72SKPBWCN7649cQjUEK5lRPK0XYFQP6jneSCbRMkdV8yTvS+qP0z+yZcR0htFLVe9zWqODM4domBvflsJdrbDjuOSf7Yo+hI3+xMJFIkylu7IMYpbto8UKiwniba/DORUzlsh3aMRIjocO824iNiZN9vwwo6RotQzKQVFXQ2L5vuHuzF6WMytWQIS8QH8R5GWs1+/kGAt2+BTfnA1PAvKOtEWWl/wyiGOOC+qNfONj5OUPLNZXh5yPE8KYmjDNAvFEUut1tLurQg1H+Z3d1pY0Lic6BdNbVKIdJatyGnR497ZrCy2HWlI6O6Y268rE8o8SG8FTEP9x58MP+BbmtolInCOV3R3xZgGo6i4vhM0TpUedPbi0W63cezN2jTCJao255vdXkdUIt0TDmI805d6qQAAALP/Tukg5x113jTt0SHlvje8jDXKjxx2ntx7Tb38NkTxWkcTrMV/Zc8jsBxWwcAt6XpjQyFFOev040bePzAFNrJx3ei0s2LU/f3msZr9Z73w+FSZ4ls70rZhbPHFfcGZPWiEaQvJi0c8VpeQJaWt/sBzP8tHHMzY+Fi6mpG7nTi+TNrCeBMlMBf1tjbbVqsjcp5nBKGxpWMQeSnmaYF4qd15iDuly+GY5rXGpajzsAoOrZS65k4O5GZ17k/NM9TkM8j0pKlcTaxv/wjjprLJTTUPcHGn5afWwNm9C24l1XtG0hBTcahuVYyPODOY0uDpRv+2apubewHXPaXNO+TxKovMbaaX6WWGk+MxQO4Bumnct5DApfR2BhtKmylgE6GVbriuHMIMDFHWrdtEIVEbhfKDLCPcBkIObGUI7sYlDkIy30Q2NPQvls+5bV5JcJ3XdXZbrOavV5htenzh6Qpx9UC0T7LXlb1mobYPS9vzmaF8LnxfGc0LwxdNvE8yHeTPlqYddHpH13Uf2a/jlXSxKredRGVkaLQh8lxPLk7kuzGsdDFllqxKucj0ehxWACEKASTc72cbX2yYA+P3z9Ew/MBbrZh2LdrS9XIR3eZO08qHqTaMYmETmAXhzV1jY00Y20d6JW8Zw71JtKXMcTgfQVZNcD9QDXMTet5xOvIDrFk8xnYbT5w6aB8xESBcbdkKhP6UXIQB+el6J7G0H4a2mzSixS96tzhglSdrOHcgjc+sFqo7MM3mJoLIJ7UBfbn+pb/xVF9vhZ6/1rEDfrKK0N0etHuidZcSrnsdzGOsL0uMOiCs/IoXdMx6NNojvsTjGI4TWJ0uer4x8l6DZbdSdHCf/5V+T46kfKtvknNW69AS3XkY4ZwIeNIe6XssroJttt2xTHbuteQRF8somQ/s441x0clvWP6woGL83Om45P44dCbyBB2QCxC2qeG3DtMl6+NXnZYB5FjF0Tn//rX38ll3jZKwWfDPHfc7dS2QmuSPnFJzRFzZ1cWrMkUH8WKN8owSn1D3uf2rU3rTadmRe3CgiqLUdfPuZD/Ox+ATTpxUNIpraJ2GTXizQ1zcGXXCFQ5ADlYs71HirxA/w++9nVTLgT9C2+28EVi4IVoy+flJ+i6qsbxvCfGll8rLDpG+Y7JuzPvtvj/Ge8fcynWZiYezZIyZrPiU3N1SnevmWjnAycmZzbWiNNk3kcnUI+0dDUpp1MsK39AQPqstovYb1W4ryldJH3kpPb8NH5Eu80YrEBWT8KQlUvkbjjMNPav58yDqUpvwzR4OxzOteO8RHsm+zy78Shz/eTOh61BQaVQcseV+gGana4K8yuC0qynAKAAueng8+oU1ve3gEruH6sQ+KF9WLf/dCWych36wPr5xmSNvu/ssHbPsN+Y/Gq0J+tnoRToXjfxRYL5icyHPbOLoAD6m5bY/dJSe0vPZnntJFbSoArdtul8woAwK03j2/+xzp9Y2Srdy6/24h9fagd4CVFr7Ricwqvjb7wcuO/FJeq23p5n+M7MDdOS8JS762lVATAES7Nb/gfrwnWwn6q5JVk3zUq1oQJ71O2aw1grVQ7GPizE/zqwenhC8H7rEUc52bu9E2DPs40Womll1f2y60yvrTxcREiMOpNf30lAKYt8Ub2TEteukr418bCZ+p+jCvuEbd6v3ugVIcmUeUM1FxfL3Ak3Fo1k13p/f0J1JRBI/0i1NVUT6jOaLM2ov3FuaVs/Edb2dottOkvKE4fkxV8044BnwTk94vdbriuoZBw6vbI23/lvfcgqyC/1ytcl7iYMQed1JXzPXwRn8z38apaBMDZf6R5Z8zDtSHCta21xCn6OB4dmx7WqU0xyfcCOcaPRJI1k4xN0RYS1ZsIXcVz7phHumfere4VKQLfYmtdE28uJymyddqr5npHvY1Avu9aGfKJ9Ut9/DRcgzxqLo/gdlNwfYdX0vUfvbHVhTUpi7enjFzAjnTXyL2Anmb/bIruFREIyXYEdxJ4vQxVWJpfs6HC1kRaE0YGmYerj3F1wE79D7KvgKn66hQOd2786f0XeW+2etp4ASzgmll6CistOeg/MbcbnWvZYRZ1SNeP/SyhXR4XTT/e35b0oXSQJvAkC9xv/2rBBaer8T2+4yQOJxQVEEe9A+q1q9ECX5oKSFVFIATVeTCcCg0FKwGcrUGsqho/ZRnKzeoqGj/M9Bmo/TMs8wd6P/wNjF9fTk72/2S1cZs7ye/1jcf3BNFg7BRJh5UYuGDjxHhwy0is/axls79yVmiQYm9qh0OxJFU8aRKx4AwTo8yuFk21hvzwdlD/fU3rE06LuP9vccereOdDDMiagQOsBcSFcCQCXZmTcy+gxMxtT+QWaYWcGn0CsucEaM5jRd7QDhzXMPrPwsIJcHovPSQYhRCsR96M4kewx1N0Jn1Y9frk6wX15mV6zyrLxelubkyadArUYo3UzCMZmmEpkCZX9cVqPj93JxsDPhq9BhOXyAA1LbFzWU4oHxUcapnNZHkkzmsFhZ1bMHiAply0zj4vRMt9JkdUXCFkM1+0vir6Ouv/ez+DGAmKhvXuvvQRIMH+P9Z+3Op+Gqn+zpbA1HPXFg0Kup8hDUWwytgeBHPR7oIPEDY5SP/pFmvNp5wr2pz0B3skEd9oXOwk2pPIf6mBes17oIzmgFam1MS6ca9XTcST7buVdPd1sePLIkafDjf1p1+42mi+rdHYNmnHxhjm9yFCrt1o0SLRmLMyzosSb4XwsPUsZyTsMTrXd7f/tHHL0IruzIbYqEOvJmKfzlKIQwl0vEAIACKIsL+FKana5KwZ1iP3Hp/iznUGA7cBZ+FTWvFHHlaoRnARwXKHwNxqCfLnpyvMt9F0Q2c7Ugd8KUZx/gzmWMjT17245Q+j1jNHwDngRb+WoYdxxPgPKiPaSWZruPC1Dk812YeUugLviuVFfCX9q50SCBTmfKmYwZJKEn0cJJk0t+mBv7UTZr6GvYAG1qsAlzRcEZyxMjMeOiUE3lquDd0GG8cSri3WWjvxb+wa2eBver7b9Ej0tm73zBo405/zHmd1t4WCtbzX3SwgsTLgj5kGqyuRmOV0WZH8fzoZWEsxP+Io5O92mjObvBRgEFQ6yeThQf4FA5fVfc7FsHeSo07AH/nWk+ZzrcGGP2CvTfLEsBn47imQ0oUsPe17bgDcx69ZWLK4yyjMMJP77s8AVhH3r4fnUybtSL96KU5EpvpT2wt+37ruCY495mk04P4994SVaa1DDuNOL/miToSVsA2PO0aHAjgZikzoxQ8r1+gtmvlQT9jA3qRx9rordD3bnC14rMjm2RGNOFv3/wG6oYAF8akQhCJeMdJ0Dp8eIZfCaidkZqAiLwBxETkIBdC7ladYuiZV2v3gzPsGz0TFPfFr0h7E8eSifqn1DrqmWxuScMxjYMZtds278LwHptAHZpIfQ3nhND0Cxgf4PlCvClDAr09j8v2qnUiTVd2vg41dH3wHSDB53suzEEMOUqjBTpYdMGsADIuDYrvZ4jnN2EECjuYBKwBFiSu69+5TemGhMQDnFT4nYmImUmJ42fSMndd5NK8ebFcAkyfPrQM264SOFHNg7w3BZRERb/NRDKkUQY709yvS7i7f/XVBIJ+qN9csBfreHQvh/x9OGCJ7GDDFdgTtqx4z+5QW96MStXiZLHW/o0MBD9pnwxv0o6Ikv/YVA+NtU2WIzEARGD7Fbv89uT7VPCDedt1CzYsMYGefyadsPQjLk+tfvHh/NN3N0EmEgLWRf06l0TPjFNFdc5lZ6f+vn0zQ83+lCWb/8havvhiT7aQbvWN/DBrQTMVPlhvf7/KJbaJ0PZhPzQiStpRb3bi+YCjxn9GKIbz/ZNQkBFuUT6zpwjhQa1T2OP7c4aSP0vKKUAEEtqZFfx4yFPX3XYvIamCJbyNOs0kTpTgoSmgBcYtChqzMEgcgAmTQYkqAZ9oGCVkNBn4DyLgD404CoMQCYppO+w2ja0Dh+H3Z0EA4HdrkRQpR3IAvwCBm3z0xnP15YUmNb2r5umOBm6Ng37vYUaWC5YwBBIDgyEIOG8XfIxQoQLT8fKkOxhfiF3f2ihlDfhKeGQemEyiAGBovBK7Xbmcnyy+0DjRgXxYkqO7p4d2Nk1EJp9UqTDR4Tr5VyWnHsacmS5P7A88GRFPhAjRwRMo77FncyXkjQ9hSGKws7RcZAFpfKIfmMvyEah2/ywqT/VtgGl9J88OqsxGQMYuCvznL1YsDzQY1aVuwm6q/GkZiYrJT8xcTGFicYp/cYpgv9MzEisT/yWg3P12+lVmxLRPZQZ92kRVCsFPgBIBRyyaNNC1D7a1DQK5ABJ/8kyCGiGajyUhWu+ewPQXEjXC4p3yYbQQEumDd+Xjrk0sxsaspLVncXP+usGmfurh7GlQuaEJHKYuSrHMx9t8RFPGIcLmisUm8clKK8FntcgUqBUSwCymHDqZO45z7tohi0nyW3/lsXxjt0bdp2JgcDe5DSvGyTm71rigJ/FrO1Wyrgh3Jj41jw/b+4rrd9g0vad7cW57ICO2lhhggrYSx2pHw3PdTl2gttOxF6hrgLn3+f4fHfzy0PPP/rJzvtgLOm5hygh2tVQk00Y9erAKk+sbxHtW1xTutvBaXBB23i1/IR8LIIyZLefkv6qa4GcHliSjKAiMfls5ExsLSRskOzfojyUfqR1mZ6Dqctd6nBSMe4bn2L69BCnkexBTnxmDfNHmw7KVxaKIIcYnxIORYUaliBSBekEwY0QU2EOcZjUlC9UqQEnCcMOf0KhXvdC+uzTw7AHT2EOJ938ZtSQp/3NKm2K4e/uyDCBuiq2UOKSARxcI+gHlmoaHmEbCbEHMmf39i7X4+ahm0U/7ZJqhLlvQB3ScSZ7aiCEf+2hABWomOTz6HHyqhwLRFf9BulLDIJuFs4PoRvjpMsYSGmiO8b3ULsxVpCDoHeLE703UZ0xafmBiOeUzCbcf3cOMDJ41a3u1YpdKu5wMXHOWbjNTOjb4qR3+sr5Zx+C01/Sapvu2EqzZC/sA2MUXr/5p9rkUxm3xe0plqyw2iv1yXihFWDSWTWVdr/ElpPT3U5wuSaVpWyvnFc+KRdfUxxSinl8A6vgyfPmNjvX2fhGE3bhPsSvYV/ufAi3UBZm7rn02tVINoqhK6Fl1OHGldLQxfJZ6Kaod9GJTl3HGaE3hOyLJqnBksiar6NSAg6ytYJkdHKxvE2Ng+l28GvA8OvZCk/yCX1fL1+ez1WcwlLCEo8VBmMIGxjIcjX441u/QteIayObfwjWQoFBIYDFk0Mxsah5su2sOSSC8H11LsviouAoujL3foP+yp+aN6H6In1VopRfaPbqGjS7JFJmrGk8XOa1add6mJ4yNB1xzeiNpY9se6Q27mC1rwyKVo3Gvk98O8Ml0nPWfX5WzNyws5XoU/aI2CkTHbNUz8ypmEbRTpdn5bELwazoaQFnnOOSxXBm53V9F6Bh1mmRqTLwtIyjmW9XXz8bc6HXmkOy50X1w7RY7506xKH6WQDc7pD8MB6K6PuSUmoQ7Q0N1suyvt/QiCG+K9LEd+peaPevYVX1vp2lFueCwMGK4w+ucI3q4ZKm6smCrQXNx6buNGB14AarU7ZW05C9nUhtczeyeBdyzVcW7B55xpWVNjBKaQuYjzlcIYgS1n5UObsWOgWqj3BsxCn21p+Y2l1igp/YixkjyUfbkOn1/xTWc2pgqXCIG0dt4iSqv0QquFxVNrHjLxxM1ke1OMY1YAggaRaq+4I8hvDDN+1Hq6ZtomyaaIiWlCrk0NJDR9qcPOH0t5IqHtRWMJad14KzAyIgz0pMt9vB/weZypkN4OFqFixhlg0D1xyZBKniWXuKUlpZGdhqagF3KSYLBQhTIa6Q70iOklzAtzqxYOt4PAKmRlVN6zmUwbDaFLupUKIFM+fP1nhy95RhzC7XzFJ2edqcVy0x36zyszhtb9YiDDeY3kl1p1RxJfdTysa0vbSEZbXCdyov1XeQ64Zh3WYssQ8USUy61yZKDWLwI5otT0MaRVuqqr3MIgcJwg0jWirg5b+Gn1+d/3X1aTLz0N5pXPixz3tphZ+6NDemlXqBCS8t9MfNCr4jIxxb4D71XlmjgbWYsapa3Onr9JFZcOPNdcG6ceSg8RjZtqSwB17RIVan8Uat4cmvnqL7rdv21i34++7ZjWSsvTXWpOufavvIXxsFLiRuGD2bSRb8T56uuWdlCy+xwZkDmzbnD+TpoHhW1qLQvgaEMlWq9VwVthLydQshB3zja5lQGcXmw
*/