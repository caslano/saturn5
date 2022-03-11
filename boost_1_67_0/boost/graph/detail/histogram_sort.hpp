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