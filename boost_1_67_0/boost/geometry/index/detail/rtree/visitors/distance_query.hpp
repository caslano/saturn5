// Boost.Geometry Index
//
// R-tree distance (knn, path, etc. ) query visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DISTANCE_QUERY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DISTANCE_QUERY_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename Value, typename Translator, typename DistanceType, typename OutIt>
class distance_query_result
{
public:
    typedef DistanceType distance_type;

    inline explicit distance_query_result(size_t k, OutIt out_it)
        : m_count(k), m_out_it(out_it)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_count, "Number of neighbors should be greater than 0");

        m_neighbors.reserve(m_count);
    }

    inline void store(Value const& val, distance_type const& curr_comp_dist)
    {
        if ( m_neighbors.size() < m_count )
        {
            m_neighbors.push_back(std::make_pair(curr_comp_dist, val));

            if ( m_neighbors.size() == m_count )
                std::make_heap(m_neighbors.begin(), m_neighbors.end(), neighbors_less);
        }
        else
        {
            if ( curr_comp_dist < m_neighbors.front().first )
            {
                std::pop_heap(m_neighbors.begin(), m_neighbors.end(), neighbors_less);
                m_neighbors.back().first = curr_comp_dist;
                m_neighbors.back().second = val;
                std::push_heap(m_neighbors.begin(), m_neighbors.end(), neighbors_less);
            }
        }
    }

    inline bool has_enough_neighbors() const
    {
        return m_count <= m_neighbors.size();
    }

    inline distance_type greatest_comparable_distance() const
    {
        // greatest distance is in the first neighbor only
        // if there is at least m_count values found
        // this is just for safety reasons since is_comparable_distance_valid() is checked earlier
        // TODO - may be replaced by ASSERT
        return m_neighbors.size() < m_count
            ? (std::numeric_limits<distance_type>::max)()
            : m_neighbors.front().first;
    }

    inline size_t finish()
    {
        typedef typename std::vector< std::pair<distance_type, Value> >::const_iterator neighbors_iterator;
        for ( neighbors_iterator it = m_neighbors.begin() ; it != m_neighbors.end() ; ++it, ++m_out_it )
            *m_out_it = it->second;

        return m_neighbors.size();
    }

private:
    inline static bool neighbors_less(
        std::pair<distance_type, Value> const& p1,
        std::pair<distance_type, Value> const& p2)
    {
        return p1.first < p2.first;
    }

    size_t m_count;
    OutIt m_out_it;

    std::vector< std::pair<distance_type, Value> > m_neighbors;
};

template
<
    typename MembersHolder,
    typename Predicates,
    unsigned DistancePredicateIndex,
    typename OutIter
>
class distance_query
    : public MembersHolder::visitor_const
{
public:
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef index::detail::predicates_element<DistancePredicateIndex, Predicates> nearest_predicate_access;
    typedef typename nearest_predicate_access::type nearest_predicate_type;
    typedef typename indexable_type<translator_type>::type indexable_type;

    typedef index::detail::calculate_distance<nearest_predicate_type, indexable_type, strategy_type, value_tag> calculate_value_distance;
    typedef index::detail::calculate_distance<nearest_predicate_type, box_type, strategy_type, bounds_tag> calculate_node_distance;
    typedef typename calculate_value_distance::result_type value_distance_type;
    typedef typename calculate_node_distance::result_type node_distance_type;

    static const unsigned predicates_len = index::detail::predicates_length<Predicates>::value;

    inline distance_query(parameters_type const& parameters, translator_type const& translator, Predicates const& pred, OutIter out_it)
        : m_parameters(parameters), m_translator(translator)
        , m_pred(pred)
        , m_result(nearest_predicate_access::get(m_pred).count, out_it)
        , m_strategy(index::detail::get_strategy(parameters))
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;

        // array of active nodes
        typedef typename index::detail::rtree::container_from_elements_type<
            elements_type,
            std::pair<node_distance_type, typename allocators_type::node_pointer>
        >::type active_branch_list_type;

        active_branch_list_type active_branch_list;
        active_branch_list.reserve(m_parameters.get_max_elements());
        
        elements_type const& elements = rtree::elements(n);

        // fill array of nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if current node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check
                    <
                        index::detail::bounds_tag, 0, predicates_len
                    >(m_pred, 0, it->first, m_strategy) )
            {
                // calculate node's distance(s) for distance predicate
                node_distance_type node_distance;
                // if distance isn't ok - move to the next node
                if ( !calculate_node_distance::apply(predicate(), it->first,
                                                     m_strategy, node_distance) )
                {
                    continue;
                }

                // if current node is further than found neighbors - don't analyze it
                if ( m_result.has_enough_neighbors() &&
                     is_node_prunable(m_result.greatest_comparable_distance(), node_distance) )
                {
                    continue;
                }

                // add current node's data into the list
                active_branch_list.push_back( std::make_pair(node_distance, it->second) );
            }
        }

        // if there aren't any nodes in ABL - return
        if ( active_branch_list.empty() )
            return;
        
        // sort array
        std::sort(active_branch_list.begin(), active_branch_list.end(), abl_less);

        // recursively visit nodes
        for ( typename active_branch_list_type::const_iterator it = active_branch_list.begin();
              it != active_branch_list.end() ; ++it )
        {
            // if current node is further than furthest neighbor, the rest of nodes also will be further
            if ( m_result.has_enough_neighbors() &&
                 is_node_prunable(m_result.greatest_comparable_distance(), it->first) )
                break;

            rtree::apply_visitor(*this, *(it->second));
        }

        // ALTERNATIVE VERSION - use heap instead of sorted container
        // It seems to be faster for greater MaxElements and slower otherwise
        // CONSIDER: using one global container/heap for active branches
        //           instead of a sorted container per level
        //           This would also change the way how branches are traversed!
        //           The same may be applied to the iterative version which btw suffers
        //           from the copying of the whole containers on resize of the ABLs container

        //// make a heap
        //std::make_heap(active_branch_list.begin(), active_branch_list.end(), abl_greater);

        //// recursively visit nodes
        //while ( !active_branch_list.empty() )
        //{
        //    //if current node is further than furthest neighbor, the rest of nodes also will be further
        //    if ( m_result.has_enough_neighbors()
        //      && is_node_prunable(m_result.greatest_comparable_distance(), active_branch_list.front().first) )
        //    {
        //        break;
        //    }

        //    rtree::apply_visitor(*this, *(active_branch_list.front().second));

        //    std::pop_heap(active_branch_list.begin(), active_branch_list.end(), abl_greater);
        //    active_branch_list.pop_back();
        //}
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);
        
        // search leaf for closest value meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if value meets predicates
            if ( index::detail::predicates_check
                    <
                        index::detail::value_tag, 0, predicates_len
                    >(m_pred, *it, m_translator(*it), m_strategy) )
            {
                // calculate values distance for distance predicate
                value_distance_type value_distance;
                // if distance is ok
                if ( calculate_value_distance::apply(predicate(), m_translator(*it),
                                                     m_strategy, value_distance) )
                {
                    // store value
                    m_result.store(*it, value_distance);
                }
            }
        }
    }

    inline size_t finish()
    {
        return m_result.finish();
    }

private:
    static inline bool abl_less(
        std::pair<node_distance_type, typename allocators_type::node_pointer> const& p1,
        std::pair<node_distance_type, typename allocators_type::node_pointer> const& p2)
    {
        return p1.first < p2.first;
    }

    //static inline bool abl_greater(
    //    std::pair<node_distance_type, typename allocators_type::node_pointer> const& p1,
    //    std::pair<node_distance_type, typename allocators_type::node_pointer> const& p2)
    //{
    //    return p1.first > p2.first;
    //}

    template <typename Distance>
    static inline bool is_node_prunable(Distance const& greatest_dist, node_distance_type const& d)
    {
        return greatest_dist <= d;
    }

    nearest_predicate_type const& predicate() const
    {
        return nearest_predicate_access::get(m_pred);
    }

    parameters_type const& m_parameters;
    translator_type const& m_translator;

    Predicates m_pred;
    distance_query_result<value_type, translator_type, value_distance_type, OutIter> m_result;

    strategy_type m_strategy;
};

template <
    typename MembersHolder,
    typename Predicates,
    unsigned DistancePredicateIndex
>
class distance_query_incremental
    : public MembersHolder::visitor_const
{
public:
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef index::detail::predicates_element<DistancePredicateIndex, Predicates> nearest_predicate_access;
    typedef typename nearest_predicate_access::type nearest_predicate_type;
    typedef typename indexable_type<translator_type>::type indexable_type;
    
    typedef index::detail::calculate_distance<nearest_predicate_type, indexable_type, strategy_type, value_tag> calculate_value_distance;
    typedef index::detail::calculate_distance<nearest_predicate_type, box_type, strategy_type, bounds_tag> calculate_node_distance;
    typedef typename calculate_value_distance::result_type value_distance_type;
    typedef typename calculate_node_distance::result_type node_distance_type;

    typedef typename allocators_type::size_type size_type;
    typedef typename allocators_type::const_reference const_reference;
    typedef typename allocators_type::node_pointer node_pointer;

    static const unsigned predicates_len = index::detail::predicates_length<Predicates>::value;

    typedef typename rtree::elements_type<internal_node>::type internal_elements;
    typedef typename internal_elements::const_iterator internal_iterator;
    typedef typename rtree::elements_type<leaf>::type leaf_elements;

    typedef std::pair<node_distance_type, node_pointer> branch_data;
    typedef typename index::detail::rtree::container_from_elements_type<
        internal_elements, branch_data
    >::type active_branch_list_type;
    struct internal_stack_element
    {
        internal_stack_element() : current_branch(0) {}
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        // Required in c++03 for containers using Boost.Move
        internal_stack_element & operator=(internal_stack_element const& o)
        {
            branches = o.branches;
            current_branch = o.current_branch;
            return *this;
        }
#endif
        active_branch_list_type branches;
        typename active_branch_list_type::size_type current_branch;
    };
    typedef std::vector<internal_stack_element> internal_stack_type;

    inline distance_query_incremental()
        : m_translator(NULL)
//        , m_pred()
        , current_neighbor((std::numeric_limits<size_type>::max)())
//        , next_closest_node_distance((std::numeric_limits<node_distance_type>::max)())
//        , m_strategy_type()
    {}

    inline distance_query_incremental(parameters_type const& params, translator_type const& translator, Predicates const& pred)
        : m_translator(::boost::addressof(translator))
        , m_pred(pred)
        , current_neighbor((std::numeric_limits<size_type>::max)())
        , next_closest_node_distance((std::numeric_limits<node_distance_type>::max)())
        , m_strategy(index::detail::get_strategy(params))
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < max_count(), "k must be greather than 0");
    }

    const_reference dereference() const
    {
        return *(neighbors[current_neighbor].second);
    }

    void initialize(node_pointer root)
    {
        rtree::apply_visitor(*this, *root);
        increment();
    }

    void increment()
    {
        for (;;)
        {
            size_type new_neighbor = current_neighbor == (std::numeric_limits<size_type>::max)() ? 0 : current_neighbor + 1;

            if ( internal_stack.empty() )
            {
                if ( new_neighbor < neighbors.size() )
                    current_neighbor = new_neighbor;
                else
                {
                    current_neighbor = (std::numeric_limits<size_type>::max)();
                    // clear() is used to disable the condition above
                    neighbors.clear();
                }

                return;
            }
            else
            {
                active_branch_list_type & branches = internal_stack.back().branches;
                typename active_branch_list_type::size_type & current_branch = internal_stack.back().current_branch;

                if ( branches.size() <= current_branch )
                {
                    internal_stack.pop_back();
                    continue;
                }

                // if there are no nodes which can have closer values, set new value
                if ( new_neighbor < neighbors.size() &&
                     // here must be < because otherwise neighbours may be sorted in different order
                     // if there is another value with equal distance
                     neighbors[new_neighbor].first < next_closest_node_distance )
                {
                    current_neighbor = new_neighbor;
                    return;
                }

                // if node is further than the furthest neighbour, following nodes also will be further
                BOOST_GEOMETRY_INDEX_ASSERT(neighbors.size() <= max_count(), "unexpected neighbours count");
                if ( max_count() <= neighbors.size() &&
                     is_node_prunable(neighbors.back().first, branches[current_branch].first) )
                {
                    // stop traversing current level
                    internal_stack.pop_back();
                    continue;
                }
                else
                {
                    // new level - must increment current_branch before traversing of another level (mem reallocation)
                    ++current_branch;
                    rtree::apply_visitor(*this, *(branches[current_branch - 1].second));

                    next_closest_node_distance = calc_closest_node_distance(internal_stack.begin(), internal_stack.end());
                }
            }
        }
    }

    bool is_end() const
    {
        return (std::numeric_limits<size_type>::max)() == current_neighbor;
    }

    friend bool operator==(distance_query_incremental const& l, distance_query_incremental const& r)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(l.current_neighbor != r.current_neighbor ||
                                    (std::numeric_limits<size_type>::max)() == l.current_neighbor ||
                                    (std::numeric_limits<size_type>::max)() == r.current_neighbor ||
                                    l.neighbors[l.current_neighbor].second == r.neighbors[r.current_neighbor].second,
                                    "not corresponding iterators");
        return l.current_neighbor == r.current_neighbor;
    }

    // Put node's elements into the list of active branches if those elements meets predicates
    // and distance predicates(currently not used)
    // and aren't further than found neighbours (if there is enough neighbours)
    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // add new element
        internal_stack.resize(internal_stack.size()+1);

        // fill active branch list array of nodes meeting predicates
        for ( typename elements_type::const_iterator it = elements.begin() ; it != elements.end() ; ++it )
        {
            // if current node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check
                    <
                        index::detail::bounds_tag, 0, predicates_len
                    >(m_pred, 0, it->first, m_strategy) )
            {
                // calculate node's distance(s) for distance predicate
                node_distance_type node_distance;
                // if distance isn't ok - move to the next node
                if ( !calculate_node_distance::apply(predicate(), it->first,
                                                     m_strategy, node_distance) )
                {
                    continue;
                }

                // if current node is further than found neighbors - don't analyze it
                if ( max_count() <= neighbors.size() &&
                     is_node_prunable(neighbors.back().first, node_distance) )
                {
                    continue;
                }

                // add current node's data into the list
                internal_stack.back().branches.push_back( std::make_pair(node_distance, it->second) );
            }
        }

        if ( internal_stack.back().branches.empty() )
            internal_stack.pop_back();
        else
            // sort array
            std::sort(internal_stack.back().branches.begin(), internal_stack.back().branches.end(), abl_less);
    }

    // Put values into the list of neighbours if those values meets predicates
    // and distance predicates(currently not used)
    // and aren't further than already found neighbours (if there is enough neighbours)
    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // store distance to the furthest neighbour
        bool not_enough_neighbors = neighbors.size() < max_count();
        value_distance_type greatest_distance = !not_enough_neighbors ? neighbors.back().first : (std::numeric_limits<value_distance_type>::max)();
        
        // search leaf for closest value meeting predicates
        for ( typename elements_type::const_iterator it = elements.begin() ; it != elements.end() ; ++it)
        {
            // if value meets predicates
            if ( index::detail::predicates_check
                    <
                        index::detail::value_tag, 0, predicates_len
                    >(m_pred, *it, (*m_translator)(*it), m_strategy) )
            {
                // calculate values distance for distance predicate
                value_distance_type value_distance;
                // if distance is ok
                if ( calculate_value_distance::apply(predicate(), (*m_translator)(*it),
                                                     m_strategy, value_distance) )
                {
                    // if there is not enough values or current value is closer than furthest neighbour
                    if ( not_enough_neighbors || value_distance < greatest_distance )
                    {
                        neighbors.push_back(std::make_pair(value_distance, boost::addressof(*it)));
                    }
                }
            }
        }

        // sort array
        std::sort(neighbors.begin(), neighbors.end(), neighbors_less);
        // remove furthest values
        if ( max_count() < neighbors.size() )
            neighbors.resize(max_count());
    }

private:
    static inline bool abl_less(std::pair<node_distance_type, node_pointer> const& p1,
                                std::pair<node_distance_type, node_pointer> const& p2)
    {
        return p1.first < p2.first;
    }

    static inline bool neighbors_less(std::pair<value_distance_type, const value_type *> const& p1,
                                      std::pair<value_distance_type, const value_type *> const& p2)
    {
        return p1.first < p2.first;
    }

    node_distance_type
    calc_closest_node_distance(typename internal_stack_type::const_iterator first,
                               typename internal_stack_type::const_iterator last)
    {
        node_distance_type result = (std::numeric_limits<node_distance_type>::max)();
        for ( ; first != last ; ++first )
        {
            if ( first->branches.size() <= first->current_branch )
                continue;

            node_distance_type curr_dist = first->branches[first->current_branch].first;
            if ( curr_dist < result )
                result = curr_dist;
        }
        return result;
    }

    template <typename Distance>
    static inline bool is_node_prunable(Distance const& greatest_dist, node_distance_type const& d)
    {
        return greatest_dist <= d;
    }

    inline unsigned max_count() const
    {
        return nearest_predicate_access::get(m_pred).count;
    }

    nearest_predicate_type const& predicate() const
    {
        return nearest_predicate_access::get(m_pred);
    }

    const translator_type * m_translator;

    Predicates m_pred;
    
    internal_stack_type internal_stack;
    std::vector< std::pair<value_distance_type, const value_type *> > neighbors;
    size_type current_neighbor;
    node_distance_type next_closest_node_distance;

    strategy_type m_strategy;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DISTANCE_QUERY_HPP

/* distance_query.hpp
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
*/