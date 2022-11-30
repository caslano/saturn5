// Copyright 2009 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_DETAIL_HISTOGRAM_SORT_HPP
#define BOOST_GRAPH_DETAIL_HISTOGRAM_SORT_HPP

#include <boost/assert.hpp>

namespace boost
{
namespace graph
{
    namespace detail
    {

        template < typename InputIterator >
        size_t reserve_count_for_single_pass_helper(
            InputIterator, InputIterator, std::input_iterator_tag)
        {
            // Do nothing: we have no idea how much storage to reserve.
            return 0;
        }

        template < typename InputIterator >
        size_t reserve_count_for_single_pass_helper(InputIterator first,
            InputIterator last, std::random_access_iterator_tag)
        {
            using std::distance;
            typename std::iterator_traits< InputIterator >::difference_type n
                = distance(first, last);
            return (size_t)n;
        }

        template < typename InputIterator >
        size_t reserve_count_for_single_pass(
            InputIterator first, InputIterator last)
        {
            typedef typename std::iterator_traits<
                InputIterator >::iterator_category category;
            return reserve_count_for_single_pass_helper(
                first, last, category());
        }

        template < typename KeyIterator, typename RowstartIterator,
            typename VerticesSize, typename KeyFilter, typename KeyTransform >
        void count_starts(KeyIterator begin, KeyIterator end,
            RowstartIterator starts, // Must support numverts + 1 elements
            VerticesSize numkeys, KeyFilter key_filter,
            KeyTransform key_transform)
        {

            typedef
                typename std::iterator_traits< RowstartIterator >::value_type
                    EdgeIndex;

            // Put the degree of each vertex v into m_rowstart[v + 1]
            for (KeyIterator i = begin; i != end; ++i)
            {
                if (key_filter(*i))
                {
                    BOOST_ASSERT(key_transform(*i) < numkeys);
                    ++starts[key_transform(*i) + 1];
                }
            }

            // Compute the partial sum of the degrees to get the actual values
            // of m_rowstart
            EdgeIndex start_of_this_row = 0;
            starts[0] = start_of_this_row;
            for (VerticesSize i = 1; i < numkeys + 1; ++i)
            {
                start_of_this_row += starts[i];
                starts[i] = start_of_this_row;
            }
        }

        template < typename KeyIterator, typename RowstartIterator,
            typename NumKeys, typename Value1InputIter,
            typename Value1OutputIter, typename KeyFilter,
            typename KeyTransform >
        void histogram_sort(KeyIterator key_begin, KeyIterator key_end,
            RowstartIterator rowstart, // Must support numkeys + 1 elements and
                                       // be precomputed
            NumKeys numkeys, Value1InputIter values1_begin,
            Value1OutputIter values1_out, KeyFilter key_filter,
            KeyTransform key_transform)
        {

            typedef
                typename std::iterator_traits< RowstartIterator >::value_type
                    EdgeIndex;

            // Histogram sort the edges by their source vertices, putting the
            // targets into m_column.  The index current_insert_positions[v]
            // contains the next location to insert out edges for vertex v.
            std::vector< EdgeIndex > current_insert_positions(
                rowstart, rowstart + numkeys);
            Value1InputIter v1i = values1_begin;
            for (KeyIterator i = key_begin; i != key_end; ++i, ++v1i)
            {
                if (key_filter(*i))
                {
                    NumKeys source = key_transform(*i);
                    BOOST_ASSERT(source < numkeys);
                    EdgeIndex insert_pos = current_insert_positions[source];
                    ++current_insert_positions[source];
                    values1_out[insert_pos] = *v1i;
                }
            }
        }

        template < typename KeyIterator, typename RowstartIterator,
            typename NumKeys, typename Value1InputIter,
            typename Value1OutputIter, typename Value2InputIter,
            typename Value2OutputIter, typename KeyFilter,
            typename KeyTransform >
        void histogram_sort(KeyIterator key_begin, KeyIterator key_end,
            RowstartIterator rowstart, // Must support numkeys + 1 elements and
                                       // be precomputed
            NumKeys numkeys, Value1InputIter values1_begin,
            Value1OutputIter values1_out, Value2InputIter values2_begin,
            Value2OutputIter values2_out, KeyFilter key_filter,
            KeyTransform key_transform)
        {

            typedef
                typename std::iterator_traits< RowstartIterator >::value_type
                    EdgeIndex;

            // Histogram sort the edges by their source vertices, putting the
            // targets into m_column.  The index current_insert_positions[v]
            // contains the next location to insert out edges for vertex v.
            std::vector< EdgeIndex > current_insert_positions(
                rowstart, rowstart + numkeys);
            Value1InputIter v1i = values1_begin;
            Value2InputIter v2i = values2_begin;
            for (KeyIterator i = key_begin; i != key_end; ++i, ++v1i, ++v2i)
            {
                if (key_filter(*i))
                {
                    NumKeys source = key_transform(*i);
                    BOOST_ASSERT(source < numkeys);
                    EdgeIndex insert_pos = current_insert_positions[source];
                    ++current_insert_positions[source];
                    values1_out[insert_pos] = *v1i;
                    values2_out[insert_pos] = *v2i;
                }
            }
        }

        template < typename KeyIterator, typename RowstartIterator,
            typename NumKeys, typename Value1Iter, typename KeyTransform >
        void histogram_sort_inplace(KeyIterator key_begin,
            RowstartIterator rowstart, // Must support numkeys + 1 elements and
                                       // be precomputed
            NumKeys numkeys, Value1Iter values1, KeyTransform key_transform)
        {

            typedef
                typename std::iterator_traits< RowstartIterator >::value_type
                    EdgeIndex;

            // 1. Copy m_rowstart (except last element) to get insert positions
            std::vector< EdgeIndex > insert_positions(
                rowstart, rowstart + numkeys);
            // 2. Swap the sources and targets into place
            for (size_t i = 0; i < rowstart[numkeys]; ++i)
            {
                BOOST_ASSERT(key_transform(key_begin[i]) < numkeys);
                // While edge i is not in the right bucket:
                while (!(i >= rowstart[key_transform(key_begin[i])]
                    && i < insert_positions[key_transform(key_begin[i])]))
                {
                    // Add a slot in the right bucket
                    size_t target_pos
                        = insert_positions[key_transform(key_begin[i])]++;
                    BOOST_ASSERT(
                        target_pos < rowstart[key_transform(key_begin[i]) + 1]);
                    if (target_pos == i)
                        continue;
                    // Swap this edge into place
                    using std::swap;
                    swap(key_begin[i], key_begin[target_pos]);
                    swap(values1[i], values1[target_pos]);
                }
            }
        }

        template < typename KeyIterator, typename RowstartIterator,
            typename NumKeys, typename Value1Iter, typename Value2Iter,
            typename KeyTransform >
        void histogram_sort_inplace(KeyIterator key_begin,
            RowstartIterator rowstart, // Must support numkeys + 1 elements and
                                       // be precomputed
            NumKeys numkeys, Value1Iter values1, Value2Iter values2,
            KeyTransform key_transform)
        {

            typedef
                typename std::iterator_traits< RowstartIterator >::value_type
                    EdgeIndex;

            // 1. Copy m_rowstart (except last element) to get insert positions
            std::vector< EdgeIndex > insert_positions(
                rowstart, rowstart + numkeys);
            // 2. Swap the sources and targets into place
            for (size_t i = 0; i < rowstart[numkeys]; ++i)
            {
                BOOST_ASSERT(key_transform(key_begin[i]) < numkeys);
                // While edge i is not in the right bucket:
                while (!(i >= rowstart[key_transform(key_begin[i])]
                    && i < insert_positions[key_transform(key_begin[i])]))
                {
                    // Add a slot in the right bucket
                    size_t target_pos
                        = insert_positions[key_transform(key_begin[i])]++;
                    BOOST_ASSERT(
                        target_pos < rowstart[key_transform(key_begin[i]) + 1]);
                    if (target_pos == i)
                        continue;
                    // Swap this edge into place
                    using std::swap;
                    swap(key_begin[i], key_begin[target_pos]);
                    swap(values1[i], values1[target_pos]);
                    swap(values2[i], values2[target_pos]);
                }
            }
        }

        template < typename InputIterator, typename VerticesSize >
        void split_into_separate_coords(InputIterator begin, InputIterator end,
            std::vector< VerticesSize >& firsts,
            std::vector< VerticesSize >& seconds)
        {
            firsts.clear();
            seconds.clear();
            size_t reserve_size
                = detail::reserve_count_for_single_pass(begin, end);
            firsts.reserve(reserve_size);
            seconds.reserve(reserve_size);
            for (; begin != end; ++begin)
            {
                std::pair< VerticesSize, VerticesSize > edge = *begin;
                firsts.push_back(edge.first);
                seconds.push_back(edge.second);
            }
        }

        template < typename InputIterator, typename VerticesSize,
            typename SourceFilter >
        void split_into_separate_coords_filtered(InputIterator begin,
            InputIterator end, std::vector< VerticesSize >& firsts,
            std::vector< VerticesSize >& seconds, const SourceFilter& filter)
        {
            firsts.clear();
            seconds.clear();
            for (; begin != end; ++begin)
            {
                std::pair< VerticesSize, VerticesSize > edge = *begin;
                if (filter(edge.first))
                {
                    firsts.push_back(edge.first);
                    seconds.push_back(edge.second);
                }
            }
        }

        template < typename InputIterator, typename PropInputIterator,
            typename VerticesSize, typename PropType, typename SourceFilter >
        void split_into_separate_coords_filtered(InputIterator begin,
            InputIterator end, PropInputIterator props,
            std::vector< VerticesSize >& firsts,
            std::vector< VerticesSize >& seconds,
            std::vector< PropType >& props_out, const SourceFilter& filter)
        {
            firsts.clear();
            seconds.clear();
            props_out.clear();
            for (; begin != end; ++begin)
            {
                std::pair< VerticesSize, VerticesSize > edge = *begin;
                if (filter(edge.first))
                {
                    firsts.push_back(edge.first);
                    seconds.push_back(edge.second);
                    props_out.push_back(*props);
                }
                ++props;
            }
        }

        // The versions of operator()() here can't return by reference because
        // the actual type passed in may not match Pair, in which case the
        // reference parameter is bound to a temporary that could end up
        // dangling after the operator returns.

        template < typename Pair > struct project1st
        {
            typedef typename Pair::first_type result_type;
            result_type operator()(const Pair& p) const { return p.first; }
        };

        template < typename Pair > struct project2nd
        {
            typedef typename Pair::second_type result_type;
            result_type operator()(const Pair& p) const { return p.second; }
        };

    }
}
}

#endif // BOOST_GRAPH_DETAIL_HISTOGRAM_SORT_HPP

/* histogram_sort.hpp
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
*/