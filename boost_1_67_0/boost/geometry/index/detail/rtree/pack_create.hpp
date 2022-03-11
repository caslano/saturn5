// Boost.Geometry Index
//
// R-tree initial packing
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_PACK_CREATE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_PACK_CREATE_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/index/detail/algorithms/bounds.hpp>
#include <boost/geometry/index/detail/algorithms/nth_element.hpp>
#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>

#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>

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
        typedef typename std::iterator_traits<InIt>::difference_type diff_type;
            
        diff_type diff = std::distance(first, last);
        if ( diff <= 0 )
            return node_pointer(0);

        typedef std::pair<point_type, InIt> entry_type;
        std::vector<entry_type> entries;

        values_count = static_cast<size_type>(diff);
        entries.reserve(values_count);
        
        expandable_box<box_type, strategy_type> hint_box(detail::get_strategy(parameters));
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
            geometry::centroid(indexable, pt);
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