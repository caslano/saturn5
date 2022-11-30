// Boost.Geometry Index
//
// R-tree initial packing
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2020 Caian Benedicto, Campinas, Brazil.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_PACK_CREATE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_PACK_CREATE_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>
#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/algorithms/nth_element.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>
#include <boost/geometry/index/parameters.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree {

namespace pack_utils {

template <std::size_t Dimension>
struct biggest_edge
{
    BOOST_STATIC_ASSERT(0 < Dimension);
    template <typename Box>
    static inline void apply(Box const& box, typename coordinate_type<Box>::type & length, std::size_t & dim_index)
    {
        biggest_edge<Dimension-1>::apply(box, length, dim_index);
        typename coordinate_type<Box>::type curr
            = geometry::get<max_corner, Dimension-1>(box) - geometry::get<min_corner, Dimension-1>(box);
        if ( length < curr )
        {
            dim_index = Dimension - 1;
            length = curr;
        }
    }
};

template <>
struct biggest_edge<1>
{
    template <typename Box>
    static inline void apply(Box const& box, typename coordinate_type<Box>::type & length, std::size_t & dim_index)
    {
        dim_index = 0;
        length = geometry::get<max_corner, 0>(box) - geometry::get<min_corner, 0>(box);
    }
};

template <std::size_t I>
struct point_entries_comparer
{
    template <typename PointEntry>
    bool operator()(PointEntry const& e1, PointEntry const& e2) const
    {
        return geometry::get<I>(e1.first) < geometry::get<I>(e2.first);
    }
};

template <std::size_t I, std::size_t Dimension>
struct nth_element_and_half_boxes
{
    template <typename EIt, typename Box>
    static inline void apply(EIt first, EIt median, EIt last, Box const& box, Box & left, Box & right, std::size_t dim_index)
    {
        if ( I == dim_index )
        {
            index::detail::nth_element(first, median, last, point_entries_comparer<I>());

            geometry::convert(box, left);
            geometry::convert(box, right);
            typename coordinate_type<Box>::type edge_len
                = geometry::get<max_corner, I>(box) - geometry::get<min_corner, I>(box);
            typename coordinate_type<Box>::type median
                = geometry::get<min_corner, I>(box) + edge_len / 2;
            geometry::set<max_corner, I>(left, median);
            geometry::set<min_corner, I>(right, median);
        }
        else
            nth_element_and_half_boxes<I+1, Dimension>::apply(first, median, last, box, left, right, dim_index);
    }
};

template <std::size_t Dimension>
struct nth_element_and_half_boxes<Dimension, Dimension>
{
    template <typename EIt, typename Box>
    static inline void apply(EIt , EIt , EIt , Box const& , Box & , Box & , std::size_t ) {}
};

} // namespace pack_utils

// STR leafs number are calculated as rcount/max
// and the number of splitting planes for each dimension as (count/max)^(1/dimension)
// <-> for dimension==2 -> sqrt(count/max)
//
// The main flaw of this algorithm is that the resulting tree will have bad structure for:
// 1. non-uniformly distributed elements
//      Statistic check could be performed, e.g. based on variance of lengths of elements edges for each dimension
// 2. elements distributed mainly along one axis
//      Calculate bounding box of all elements and then number of dividing planes for a dimension
//      from the length of BB edge for this dimension (more or less assuming that elements are uniformly-distributed squares)
//
// Another thing is that the last node may have less elements than Max or even Min.
// The number of splitting planes must be chosen more carefully than count/max
//
// This algorithm is something between STR and TGS
// it is more similar to the top-down recursive kd-tree creation algorithm
// using object median split and split axis of greatest BB edge
// BB is only used as a hint (assuming objects are distributed uniformly)
//
// Implemented algorithm guarantees that the number of elements in nodes will be between Min and Max
// and that nodes are packed as tightly as possible
// e.g. for 177 values Max = 5 and Min = 2 it will construct the following tree:
// ROOT                 177
// L1          125               52
// L2  25  25  25  25  25   25  17    10
// L3  5x5 5x5 5x5 5x5 5x5  5x5 3x5+2 2x5

template <typename MembersHolder>
class pack
{
    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename MembersHolder::node_pointer node_pointer;
    typedef typename MembersHolder::size_type size_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::box_type box_type;
    typedef typename geometry::point_type<box_type>::type point_type;
    typedef typename geometry::coordinate_type<point_type>::type coordinate_type;
    typedef typename detail::default_content_result<box_type>::type content_type;
    typedef typename detail::strategy_type<parameters_type>::type strategy_type;
    static const std::size_t dimension = geometry::dimension<point_type>::value;

    typedef typename rtree::container_from_elements_type<
        typename rtree::elements_type<leaf>::type,
        size_type
    >::type values_counts_container;

    typedef typename rtree::elements_type<internal_node>::type internal_elements;
    typedef typename internal_elements::value_type internal_element;

    typedef rtree::subtree_destroyer<MembersHolder> subtree_destroyer;

public:
    // Arbitrary iterators
    template <typename InIt> inline static
    node_pointer apply(InIt first, InIt last,
                       size_type & values_count,
                       size_type & leafs_level,
                       parameters_type const& parameters,
                       translator_type const& translator,
                       allocators_type & allocators)
    {
        return apply(first, last, values_count, leafs_level, parameters, translator,
                     allocators, boost::container::new_allocator<void>());
    }

    template <typename InIt, typename TmpAlloc> inline static
    node_pointer apply(InIt first, InIt last,
                       size_type & values_count,
                       size_type & leafs_level,
                       parameters_type const& parameters,
                       translator_type const& translator,
                       allocators_type & allocators,
                       TmpAlloc const& temp_allocator)
    {
        typedef typename std::iterator_traits<InIt>::difference_type diff_type;
            
        diff_type diff = std::distance(first, last);
        if ( diff <= 0 )
            return node_pointer(0);

        typedef std::pair<point_type, InIt> entry_type;
        typedef typename boost::container::allocator_traits<TmpAlloc>::
            template rebind_alloc<entry_type> temp_entry_allocator_type;

        temp_entry_allocator_type temp_entry_allocator(temp_allocator);
        boost::container::vector<entry_type, temp_entry_allocator_type> entries(temp_entry_allocator);

        values_count = static_cast<size_type>(diff);
        entries.reserve(values_count);

        auto const& strategy = index::detail::get_strategy(parameters);
        
        expandable_box<box_type, strategy_type> hint_box(strategy);
        for ( ; first != last ; ++first )
        {
            // NOTE: support for iterators not returning true references adapted
            // to Geometry concept and default translator returning true reference
            // An alternative would be to dereference the iterator and translate
            // in one expression each time the indexable was needed.
            typename std::iterator_traits<InIt>::reference in_ref = *first;
            typename translator_type::result_type indexable = translator(in_ref);

            // NOTE: added for consistency with insert()
            // CONSIDER: alternative - ignore invalid indexable or throw an exception
            BOOST_GEOMETRY_INDEX_ASSERT(detail::is_valid(indexable), "Indexable is invalid");

            hint_box.expand(indexable);

            point_type pt;
            geometry::centroid(indexable, pt, strategy);
            entries.push_back(std::make_pair(pt, first));
        }

        subtree_elements_counts subtree_counts = calculate_subtree_elements_counts(values_count, parameters, leafs_level);
        internal_element el = per_level(entries.begin(), entries.end(), hint_box.get(), values_count, subtree_counts,
                                        parameters, translator, allocators);

        return el.second;
    }

private:
    template <typename BoxType, typename Strategy>
    class expandable_box
    {
    public:
        explicit expandable_box(Strategy const& strategy)
            : m_strategy(strategy), m_initialized(false)
        {}

        template <typename Indexable>
        explicit expandable_box(Indexable const& indexable, Strategy const& strategy)
            : m_strategy(strategy), m_initialized(true)
        {
            detail::bounds(indexable, m_box, m_strategy);
        }

        template <typename Indexable>
        void expand(Indexable const& indexable)
        {
            if ( !m_initialized )
            {
                // it's guaranteed that the Box will be initialized
                // only for Points, Boxes and Segments but that's ok
                // since only those Geometries can be stored
                detail::bounds(indexable, m_box, m_strategy);
                m_initialized = true;
            }
            else
            {
                detail::expand(m_box, indexable, m_strategy);
            }
        }

        void expand_by_epsilon()
        {
            geometry::detail::expand_by_epsilon(m_box);
        }

        BoxType const& get() const
        {
            BOOST_GEOMETRY_INDEX_ASSERT(m_initialized, "uninitialized envelope accessed");
            return m_box;
        }

    private:
        BoxType m_box;
        Strategy m_strategy;
        bool m_initialized;
    };

    struct subtree_elements_counts
    {
        subtree_elements_counts(size_type ma, size_type mi) : maxc(ma), minc(mi) {}
        size_type maxc;
        size_type minc;
    };

    template <typename EIt> inline static
    internal_element per_level(EIt first, EIt last,
                               box_type const& hint_box,
                               size_type values_count,
                               subtree_elements_counts const& subtree_counts,
                               parameters_type const& parameters,
                               translator_type const& translator,
                               allocators_type & allocators)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < std::distance(first, last) && static_cast<size_type>(std::distance(first, last)) == values_count,
                                    "unexpected parameters");

        if ( subtree_counts.maxc <= 1 )
        {
            // ROOT or LEAF
            BOOST_GEOMETRY_INDEX_ASSERT(values_count <= parameters.get_max_elements(),
                                        "too big number of elements");
            // if !root check m_parameters.get_min_elements() <= count

            // create new leaf node
            node_pointer n = rtree::create_node<allocators_type, leaf>::apply(allocators);                       // MAY THROW (A)
            subtree_destroyer auto_remover(n, allocators);
            leaf & l = rtree::get<leaf>(*n);

            // reserve space for values
            rtree::elements(l).reserve(values_count);                                                       // MAY THROW (A)

            // calculate values box and copy values
            //   initialize the box explicitly to avoid GCC-4.4 uninitialized variable warnings with O2
            expandable_box<box_type, strategy_type> elements_box(translator(*(first->second)),
                                                                 detail::get_strategy(parameters));
            rtree::elements(l).push_back(*(first->second));                                                 // MAY THROW (A?,C)
            for ( ++first ; first != last ; ++first )
            {
                // NOTE: push_back() must be called at the end in order to support move_iterator.
                //       The iterator is dereferenced 2x (no temporary reference) to support
                //       non-true reference types and move_iterator without boost::forward<>.
                elements_box.expand(translator(*(first->second)));
                rtree::elements(l).push_back(*(first->second));                                             // MAY THROW (A?,C)
            }

#ifdef BOOST_GEOMETRY_INDEX_EXPERIMENTAL_ENLARGE_BY_EPSILON
            // Enlarge bounds of a leaf node.
            // It's because Points and Segments are compared WRT machine epsilon
            // This ensures that leafs bounds correspond to the stored elements
            // NOTE: this is done only if the Indexable is a different kind of Geometry
            //   than the bounds (only Box for now). Spatial predicates are checked
            //   the same way for Geometry of the same kind.
            if ( BOOST_GEOMETRY_CONDITION((
                    ! index::detail::is_bounding_geometry
                        <
                            typename indexable_type<translator_type>::type
                        >::value )) )
            {
                elements_box.expand_by_epsilon();
            }
#endif

            auto_remover.release();
            return internal_element(elements_box.get(), n);
        }

        // calculate next max and min subtree counts
        subtree_elements_counts next_subtree_counts = subtree_counts;
        next_subtree_counts.maxc /= parameters.get_max_elements();
        next_subtree_counts.minc /= parameters.get_max_elements();

        // create new internal node
        node_pointer n = rtree::create_node<allocators_type, internal_node>::apply(allocators);                  // MAY THROW (A)
        subtree_destroyer auto_remover(n, allocators);
        internal_node & in = rtree::get<internal_node>(*n);

        // reserve space for values
        size_type nodes_count = calculate_nodes_count(values_count, subtree_counts);
        rtree::elements(in).reserve(nodes_count);                                                           // MAY THROW (A)
        // calculate values box and copy values
        expandable_box<box_type, strategy_type> elements_box(detail::get_strategy(parameters));
        
        per_level_packets(first, last, hint_box, values_count, subtree_counts, next_subtree_counts,
                          rtree::elements(in), elements_box,
                          parameters, translator, allocators);

        auto_remover.release();
        return internal_element(elements_box.get(), n);
    }

    template <typename EIt, typename ExpandableBox> inline static
    void per_level_packets(EIt first, EIt last,
                           box_type const& hint_box,
                           size_type values_count,
                           subtree_elements_counts const& subtree_counts,
                           subtree_elements_counts const& next_subtree_counts,
                           internal_elements & elements,
                           ExpandableBox & elements_box,
                           parameters_type const& parameters,
                           translator_type const& translator,
                           allocators_type & allocators)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < std::distance(first, last) && static_cast<size_type>(std::distance(first, last)) == values_count,
                                    "unexpected parameters");

        BOOST_GEOMETRY_INDEX_ASSERT(subtree_counts.minc <= values_count,
                                    "too small number of elements");

        // only one packet
        if ( values_count <= subtree_counts.maxc )
        {
            // the end, move to the next level
            internal_element el = per_level(first, last, hint_box, values_count, next_subtree_counts,
                                            parameters, translator, allocators);

            // in case if push_back() do throw here
            // and even if this is not probable (previously reserved memory, nonthrowing pairs copy)
            // this case is also tested by exceptions test.
            subtree_destroyer auto_remover(el.second, allocators);
            // this container should have memory allocated, reserve() called outside
            elements.push_back(el);                                                 // MAY THROW (A?,C) - however in normal conditions shouldn't
            auto_remover.release();

            elements_box.expand(el.first);
            return;
        }
        
        size_type median_count = calculate_median_count(values_count, subtree_counts);
        EIt median = first + median_count;

        coordinate_type greatest_length;
        std::size_t greatest_dim_index = 0;
        pack_utils::biggest_edge<dimension>::apply(hint_box, greatest_length, greatest_dim_index);
        box_type left, right;
        pack_utils::nth_element_and_half_boxes<0, dimension>
            ::apply(first, median, last, hint_box, left, right, greatest_dim_index);
        
        per_level_packets(first, median, left,
                          median_count, subtree_counts, next_subtree_counts,
                          elements, elements_box,
                          parameters, translator, allocators);
        per_level_packets(median, last, right,
                          values_count - median_count, subtree_counts, next_subtree_counts,
                          elements, elements_box,
                          parameters, translator, allocators);
    }

    inline static
    subtree_elements_counts calculate_subtree_elements_counts(size_type elements_count, parameters_type const& parameters, size_type & leafs_level)
    {
        boost::ignore_unused(parameters);

        subtree_elements_counts res(1, 1);
        leafs_level = 0;

        size_type smax = parameters.get_max_elements();
        for ( ; smax < elements_count ; smax *= parameters.get_max_elements(), ++leafs_level )
            res.maxc = smax;

        res.minc = parameters.get_min_elements() * (res.maxc / parameters.get_max_elements());

        return res;
    }

    inline static
    size_type calculate_nodes_count(size_type count,
                                    subtree_elements_counts const& subtree_counts)
    {
        size_type n = count / subtree_counts.maxc;
        size_type r = count % subtree_counts.maxc;

        if ( 0 < r && r < subtree_counts.minc )
        {
            size_type count_minus_min = count - subtree_counts.minc;
            n = count_minus_min / subtree_counts.maxc;
            r = count_minus_min % subtree_counts.maxc;
            ++n;
        }

        if ( 0 < r )
            ++n;

        return n;
    }

    inline static
    size_type calculate_median_count(size_type count,
                                     subtree_elements_counts const& subtree_counts)
    {
        // e.g. for max = 5, min = 2, count = 52, subtree_max = 25, subtree_min = 10

        size_type n = count / subtree_counts.maxc; // e.g. 52 / 25 = 2
        size_type r = count % subtree_counts.maxc; // e.g. 52 % 25 = 2
        size_type median_count = (n / 2) * subtree_counts.maxc; // e.g. 2 / 2 * 25 = 25

        if ( 0 != r ) // e.g. 0 != 2
        {
            if ( subtree_counts.minc <= r ) // e.g. 10 <= 2 == false
            {
                //BOOST_GEOMETRY_INDEX_ASSERT(0 < n, "unexpected value");
                median_count = ((n+1)/2) * subtree_counts.maxc; // if calculated ((2+1)/2) * 25 which would be ok, but not in all cases
            }
            else // r < subtree_counts.second  // e.g. 2 < 10 == true
            {
                size_type count_minus_min = count - subtree_counts.minc; // e.g. 52 - 10 = 42
                n = count_minus_min / subtree_counts.maxc; // e.g. 42 / 25 = 1
                r = count_minus_min % subtree_counts.maxc; // e.g. 42 % 25 = 17
                if ( r == 0 )                               // e.g. false
                {
                    // n can't be equal to 0 because then there wouldn't be any element in the other node
                    //BOOST_GEOMETRY_INDEX_ASSERT(0 < n, "unexpected value");
                    median_count = ((n+1)/2) * subtree_counts.maxc;     // if calculated ((1+1)/2) * 25 which would be ok, but not in all cases
                }
                else
                {
                    if ( n == 0 )                                        // e.g. false
                        median_count = r;                                // if calculated -> 17 which is wrong!
                    else
                        median_count = ((n+2)/2) * subtree_counts.maxc; // e.g. ((1+2)/2) * 25 = 25
                }
            }
        }

        return median_count;
    }
};

}}}}} // namespace boost::geometry::index::detail::rtree

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_PACK_CREATE_HPP

/* pack_create.hpp
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
*/