// Boost.Geometry Index
//
// R-tree distance (knn, path, etc. ) query visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DISTANCE_QUERY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DISTANCE_QUERY_HPP

#include <queue>

#include <boost/geometry/index/detail/distance_predicates.hpp>
#include <boost/geometry/index/detail/predicates.hpp>
#include <boost/geometry/index/detail/priority_dequeue.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/translator.hpp>
#include <boost/geometry/index/parameters.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {


struct pair_first_less
{
    template <typename First, typename Second>
    inline bool operator()(std::pair<First, Second> const& p1,
                           std::pair<First, Second> const& p2) const
    {
        return p1.first < p2.first;
    }
};

struct pair_first_greater
{
    template <typename First, typename Second>
    inline bool operator()(std::pair<First, Second> const& p1,
                           std::pair<First, Second> const& p2) const
    {
        return p1.first > p2.first;
    }
};

template <typename T, typename Comp>
struct priority_dequeue : index::detail::priority_dequeue<T, std::vector<T>, Comp>
{
    priority_dequeue() = default;
    //void reserve(typename std::vector<T>::size_type n)
    //{
    //    this->c.reserve(n);
    //}
    //void clear()
    //{
    //    this->c.clear();
    //}
};

template <typename T, typename Comp>
struct priority_queue : std::priority_queue<T, std::vector<T>, Comp>
{
    priority_queue() = default;
    //void reserve(typename std::vector<T>::size_type n)
    //{
    //    this->c.reserve(n);
    //}
    void clear()
    {
        this->c.clear();
    }
};

struct branch_data_comp
{
    template <typename BranchData>
    bool operator()(BranchData const& b1, BranchData const& b2) const
    {
        return b1.distance > b2.distance || (b1.distance == b2.distance && b1.reverse_level > b2.reverse_level);
    }
};

template <typename DistanceType, typename Value>
class distance_query_result
{
    using neighbor_data = std::pair<DistanceType, const Value *>;
    using neighbors_type = std::vector<neighbor_data>;
    using size_type = typename neighbors_type::size_type;

public:
    inline distance_query_result(size_type k)
        : m_count(k)
    {
        m_neighbors.reserve(m_count);
    }

    // NOTE: Do not call if max_count() == 0
    inline void store(DistanceType const& distance, const Value * value_ptr)
    {
        if (m_neighbors.size() < m_count)
        {
            m_neighbors.push_back(std::make_pair(distance, value_ptr));

            if (m_neighbors.size() == m_count)
            {
                std::make_heap(m_neighbors.begin(), m_neighbors.end(), pair_first_less());
            }
        }
        else if (distance < m_neighbors.front().first)
        {
            std::pop_heap(m_neighbors.begin(), m_neighbors.end(), pair_first_less());
            m_neighbors.back().first = distance;
            m_neighbors.back().second = value_ptr;
            std::push_heap(m_neighbors.begin(), m_neighbors.end(), pair_first_less());
        }
    }

    // NOTE: Do not call if max_count() == 0
    inline bool ignore_branch(DistanceType const& distance) const
    {
        return m_neighbors.size() == m_count
            && m_neighbors.front().first <= distance;
    }

    template <typename OutIt>
    inline size_type finish(OutIt out_it) const
    {
        for (auto const& p : m_neighbors)
        {
            *out_it = *(p.second);
            ++out_it;
        }

        return m_neighbors.size();
    }

    size_type max_count() const
    {
        return m_count;
    }

private:
    size_type m_count;
    neighbors_type m_neighbors;
};

template <typename MembersHolder, typename Predicates>
class distance_query
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef index::detail::predicates_element
        <
            index::detail::predicates_find_distance<Predicates>::value, Predicates
        > nearest_predicate_access;
    typedef typename nearest_predicate_access::type nearest_predicate_type;
    typedef typename indexable_type<translator_type>::type indexable_type;

    typedef index::detail::calculate_distance<nearest_predicate_type, indexable_type, strategy_type, value_tag> calculate_value_distance;
    typedef index::detail::calculate_distance<nearest_predicate_type, box_type, strategy_type, bounds_tag> calculate_node_distance;
    typedef typename calculate_value_distance::result_type value_distance_type;
    typedef typename calculate_node_distance::result_type node_distance_type;

    typedef typename MembersHolder::size_type size_type;
    typedef typename MembersHolder::node_pointer node_pointer;

    using neighbor_data = std::pair<value_distance_type, const value_type *>;
    using neighbors_type = std::vector<neighbor_data>;

    struct branch_data
    {
        branch_data(node_distance_type d, size_type rl, node_pointer p)
            : distance(d), reverse_level(rl), ptr(p)
        {}

        node_distance_type distance;
        size_type reverse_level;
        node_pointer ptr;
    };
    using branches_type = priority_queue<branch_data, branch_data_comp>;

public:
    distance_query(MembersHolder const& members, Predicates const& pred)
        : m_tr(members.translator())
        , m_strategy(index::detail::get_strategy(members.parameters()))
        , m_pred(pred)
    {
        m_neighbors.reserve((std::min)(members.values_count, size_type(max_count())));
        //m_branches.reserve(members.parameters().get_min_elements() * members.leafs_level); ?
        // min, max or average?
    }

    template <typename OutIter>
    size_type apply(MembersHolder const& members, OutIter out_it)
    {
        return apply(members.root, members.leafs_level, out_it);
    }

private:
    template <typename OutIter>
    size_type apply(node_pointer ptr, size_type reverse_level, OutIter out_it)
    {
        namespace id = index::detail;

        if (max_count() <= 0)
        {
            return 0;
        }

        for (;;)
        {
            if (reverse_level > 0)
            {
                internal_node& n = rtree::get<internal_node>(*ptr);
                // fill array of nodes meeting predicates
                for (auto const& p : rtree::elements(n))
                {
                    node_distance_type node_distance; // for distance predicate

                    // if current node meets predicates (0 is dummy value)
                    if (id::predicates_check<id::bounds_tag>(m_pred, 0, p.first, m_strategy)
                        // and if distance is ok
                        && calculate_node_distance::apply(predicate(), p.first, m_strategy, node_distance)
                        // and if current node is closer than the furthest neighbor
                        && ! ignore_branch(node_distance))
                    {
                        // add current node's data into the list
                        m_branches.push(branch_data(node_distance, reverse_level - 1, p.second));
                    }
                }
            }
            else
            {
                leaf& n = rtree::get<leaf>(*ptr);
                // search leaf for closest value meeting predicates
                for (auto const& v : rtree::elements(n))
                {
                    value_distance_type value_distance; // for distance predicate

                    // if value meets predicates
                    if (id::predicates_check<id::value_tag>(m_pred, v, m_tr(v), m_strategy)
                        // and if distance is ok
                        && calculate_value_distance::apply(predicate(), m_tr(v), m_strategy, value_distance))
                    {
                        // store value
                        store_value(value_distance, boost::addressof(v));
                    }
                }
            }

            if (m_branches.empty()
                || ignore_branch(m_branches.top().distance))
            {
                break;
            }

            ptr = m_branches.top().ptr;
            reverse_level = m_branches.top().reverse_level;
            m_branches.pop();
        }

        for (auto const& p : m_neighbors)
        {
            *out_it = *(p.second);
            ++out_it;
        }

        return m_neighbors.size();
    }

    bool ignore_branch(node_distance_type const& node_distance) const
    {
        return m_neighbors.size() == max_count()
            && m_neighbors.front().first <= node_distance;
    }

    void store_value(value_distance_type value_distance, const value_type * value_ptr)
    {
        if (m_neighbors.size() < max_count())
        {
            m_neighbors.push_back(std::make_pair(value_distance, value_ptr));

            if (m_neighbors.size() == max_count())
            {
                std::make_heap(m_neighbors.begin(), m_neighbors.end(), pair_first_less());
            }
        }
        else if (value_distance < m_neighbors.front().first)
        {
            std::pop_heap(m_neighbors.begin(), m_neighbors.end(), pair_first_less());
            m_neighbors.back() = std::make_pair(value_distance, value_ptr);
            std::push_heap(m_neighbors.begin(), m_neighbors.end(), pair_first_less());
        }
    }

    std::size_t max_count() const
    {
        return nearest_predicate_access::get(m_pred).count;
    }

    nearest_predicate_type const& predicate() const
    {
        return nearest_predicate_access::get(m_pred);
    }

    translator_type const& m_tr;
    strategy_type m_strategy;

    Predicates const& m_pred;

    branches_type m_branches;
    neighbors_type m_neighbors;
};

template <typename MembersHolder, typename Predicates>
class distance_query_incremental
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef index::detail::predicates_element
        <
            index::detail::predicates_find_distance<Predicates>::value, Predicates
        > nearest_predicate_access;
    typedef typename nearest_predicate_access::type nearest_predicate_type;
    typedef typename indexable_type<translator_type>::type indexable_type;
    
    typedef index::detail::calculate_distance<nearest_predicate_type, indexable_type, strategy_type, value_tag> calculate_value_distance;
    typedef index::detail::calculate_distance<nearest_predicate_type, box_type, strategy_type, bounds_tag> calculate_node_distance;
    typedef typename calculate_value_distance::result_type value_distance_type;
    typedef typename calculate_node_distance::result_type node_distance_type;

    typedef typename allocators_type::size_type size_type;
    typedef typename allocators_type::const_reference const_reference;
    typedef typename allocators_type::node_pointer node_pointer;

    typedef typename rtree::elements_type<internal_node>::type internal_elements;
    typedef typename internal_elements::const_iterator internal_iterator;
    typedef typename rtree::elements_type<leaf>::type leaf_elements;

    using neighbor_data = std::pair<value_distance_type, const value_type *>;
    using neighbors_type = priority_dequeue<neighbor_data, pair_first_greater>;

    struct branch_data
    {
        branch_data(node_distance_type d, size_type rl, node_pointer p)
            : distance(d), reverse_level(rl), ptr(p)
        {}

        node_distance_type distance;
        size_type reverse_level;
        node_pointer ptr;
    };
    using branches_type = priority_queue<branch_data, branch_data_comp>;

public:
    inline distance_query_incremental()
        : m_tr(nullptr)
//        , m_strategy()
//        , m_pred()
        , m_neighbors_count(0)
        , m_neighbor_ptr(nullptr)
    {}

    inline distance_query_incremental(Predicates const& pred)
        : m_tr(nullptr)
//        , m_strategy()
        , m_pred(pred)
        , m_neighbors_count(0)
        , m_neighbor_ptr(nullptr)        
    {}

    inline distance_query_incremental(MembersHolder const& members, Predicates const& pred)
        : m_tr(::boost::addressof(members.translator()))
        , m_strategy(index::detail::get_strategy(members.parameters()))
        , m_pred(pred)
        , m_neighbors_count(0)
        , m_neighbor_ptr(nullptr)        
    {}

    const_reference dereference() const
    {
        return *m_neighbor_ptr;
    }

    void initialize(MembersHolder const& members)
    {
        if (0 < max_count())
        {
            apply(members.root, members.leafs_level);
            increment();
        }
    }

    void increment()
    {
        for (;;)
        {
            if (m_branches.empty())
            {
                // there exists a next closest neighbor so we can increment
                if (! m_neighbors.empty())
                {
                    m_neighbor_ptr = m_neighbors.top().second;
                    ++m_neighbors_count;
                    m_neighbors.pop_top();
                }
                else
                {
                    // there aren't any neighbors left, end
                    m_neighbor_ptr = nullptr;
                    m_neighbors_count = max_count();
                }

                return;
            }
            else
            {
                branch_data const& closest_branch = m_branches.top();

                // if next neighbor is closer or as close as the closest branch, set next neighbor
                if (! m_neighbors.empty() && m_neighbors.top().first <= closest_branch.distance )
                {
                    m_neighbor_ptr = m_neighbors.top().second;
                    ++m_neighbors_count;
                    m_neighbors.pop_top();
                    return;
                }

                BOOST_GEOMETRY_INDEX_ASSERT(m_neighbors_count + m_neighbors.size() <= max_count(), "unexpected neighbors count");

                // if there is enough neighbors and there is no closer branch
                if (ignore_branch_or_value(closest_branch.distance))
                {
                    m_branches.clear();
                    continue;
                }
                else
                {
                    node_pointer ptr = closest_branch.ptr;
                    size_type reverse_level = closest_branch.reverse_level;
                    m_branches.pop();

                    apply(ptr, reverse_level);
                }
            }
        }
    }

    bool is_end() const
    {
        return m_neighbor_ptr == nullptr;
    }

    friend bool operator==(distance_query_incremental const& l, distance_query_incremental const& r)
    {
        return l.m_neighbors_count == r.m_neighbors_count;
    }

private:
    void apply(node_pointer ptr, size_type reverse_level)
    {
        namespace id = index::detail;
        // Put node's elements into the list of active branches if those elements meets predicates
        // and distance predicates(currently not used)
        // and aren't further than found neighbours (if there is enough neighbours)
        if (reverse_level > 0)
        {
            internal_node& n = rtree::get<internal_node>(*ptr);
            // fill active branch list array of nodes meeting predicates
            for (auto const& p : rtree::elements(n))
            {
                node_distance_type node_distance; // for distance predicate

                // if current node meets predicates (0 is dummy value)
                if (id::predicates_check<id::bounds_tag>(m_pred, 0, p.first, m_strategy)
                    // and if distance is ok
                    && calculate_node_distance::apply(predicate(), p.first, m_strategy, node_distance)
                    // and if current node is closer than the furthest neighbor
                    && ! ignore_branch_or_value(node_distance))
                {
                    // add current node into the queue
                    m_branches.push(branch_data(node_distance, reverse_level - 1, p.second));
                }
            }
        }
        // Put values into the list of neighbours if those values meets predicates
        // and distance predicates(currently not used)
        // and aren't further than already found neighbours (if there is enough neighbours)
        else
        {
            leaf& n = rtree::get<leaf>(*ptr);
            // search leaf for closest value meeting predicates
            for (auto const& v : rtree::elements(n))
            {
                value_distance_type value_distance; // for distance predicate

                // if value meets predicates
                if (id::predicates_check<id::value_tag>(m_pred, v, (*m_tr)(v), m_strategy)
                    // and if distance is ok
                    && calculate_value_distance::apply(predicate(), (*m_tr)(v), m_strategy, value_distance)
                    // and if current value is closer than the furthest neighbor
                    && ! ignore_branch_or_value(value_distance))
                {
                    // add current value into the queue
                    m_neighbors.push(std::make_pair(value_distance, boost::addressof(v)));

                    // remove unneeded value
                    if (m_neighbors_count + m_neighbors.size() > max_count())
                    {
                        m_neighbors.pop_bottom();
                    }
                }
            }
        }
    }

    template <typename Distance>
    bool ignore_branch_or_value(Distance const& distance)
    {
        return m_neighbors_count + m_neighbors.size() == max_count()
            && (m_neighbors.empty() || m_neighbors.bottom().first <= distance);
    }

    std::size_t max_count() const
    {
        return nearest_predicate_access::get(m_pred).count;
    }

    nearest_predicate_type const& predicate() const
    {
        return nearest_predicate_access::get(m_pred);
    }

    const translator_type * m_tr;
    strategy_type m_strategy;

    Predicates m_pred;
    
    branches_type m_branches;
    neighbors_type m_neighbors;
    size_type m_neighbors_count;
    const value_type * m_neighbor_ptr;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DISTANCE_QUERY_HPP

/* distance_query.hpp
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
*/