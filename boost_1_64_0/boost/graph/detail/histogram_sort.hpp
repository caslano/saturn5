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
djpvaPrzq9uypfNzQYmTs0FMi2ineJ70/MxAiQcQz7xe5a1Qfj85xqfxUeO0qvs3dpMWslyd3VKv0qNfvAz97hgDhRhDoOhxVx35Dqn6Aj3WDEsYMnZIiOHIs82ozR6PZ8nnSPNI9jKL+LGM0zX+WF1miEy3ZLqlTL8p6ygu+VNYwBx3o7leJqdMt2A6Vqa3yDp2BtuXkaoh5/Fl1DIWx9j+kpffu5KX0nXeMJe8iUzn45zfF7ewL7eStpG2k3aosTYi1Hva070odZD9mWHMoob6XFjvQ8kbi+wn4uZ4Sm2xuMT0vpC8XZDnS5znq2KJyPOSGDnl3Njx+pfOYsjD3l96SayOy3n9c+6R1z8pOUlGSXKMvUOsd4+e5ni6HAOOvJF6bJeWMp3dmnH8oQFJzyaYyyzaSx7emTKOti7jJa5nZZV9zD4x1+kyLnyszl9Ht/2IlelQqz4OzbHoJU+SXiZCt2lpKNOFnJbRQ5wYjvH1oyTPFOfjhnLcxyWSMTTVmPPUWpjHjkt+rl1m9l7R4/fXkLxlrY7lI1yWX8S0avtCJEG3izlFHqYtjuXquCy3iuncLNcrnywng6/EJzHSuNN7oqHLMhuY1mMfme97qTdrK/l+s7iO7dOUeXdkXj7d1qWtvNZZDfex+c32Li5jges6uydl2cc5ZkvoNlOtpfxA64dEfzNszvWmgx3jWwfhJ7JsMxm3NZCUm1SEMYeeQke7nCf32fMUcKrv5PhOTtJtkoJwgJQT7LZMez4Dcsn9Z+bYmzdJjjF8CpGCSOEh6ePznCe+GA8R2xXKZy1pD2kvaR9pP+ndYFLO3x+vx16XVnmfWZeWO8N4Ofo96jKGj34fSnykzq/fXxKf4GHcuOk6rt8nLmO+6ePfZfw5p+Oc+Co9hk8CR0mQHGccl0w7H5d6vB+3ser4/NLXBTqqgcb7+PO6i+r+Q9k3I9WvHrky4HpdQL++1w7I8aSuEziWXa1f73X7pY2ex2sBOr9uU6Y+ex1t/N5mPr39ZTNseszlRyQ2nul6sj8WSRk1/IPlO1G1B4unHKe2aVfesefJpb+DMubla8Ap7+5D0hbPqKjer2/Lc1jj60tv+H50TlnQEmY5aN1tjLdF0J/6TmOqT07GEZlEX2vFZZvaUtaHsk02f5fPAH3NYY3Mr+h/y+bjsX1jAVnvh7Y71mn0y57N9fnLZ9kCl2sVRWWZd/hs2WJxvSaST31OXpTX7BmqPCpxLWWdZbBtsWx3LPNCZfnDfjn0/hmQxCbpzzT1Xtf7mO9EfSwslX1sk8+QUKZXyHS4tQexheTaxa/RppZW9GnrK+ubT57PZD/87GeWm5KQkCpvHFnnyAzr1G9BI59aR5Cs4xdeqyzGAMqfZfSQ5cbq7xb1HBzvUfWdt1HWe8Gnq+1FxoYppb4L+aSSfTsufVlZZ9cByRUYh25AgmxzBMuekGUf8ZfXTe1fDmmZH8b8MzI/m7+53axffmaY13S6y3YPtZYyeP0lZq6bcuRzYb6UU8c/k3ajkuc0bpM8xZ3y6M8R/Xuh3kH1HmWZveTYJcsUdto+/Vkl+2642neReRzfKbQMHGC+P16T8rKr7xmLcU2mL/H9zi9TNd7cXdbBHD/n9qpq0/U4/K9JnvJO26E/6/T1u7ckz2P+12xW9ZvGcYyQlb8KqffoXsl33+rLseVn9aUf3gD6Xi2ixybsKdv4maWI0ZU+7edQr14x4/eWvD7mc+xziPzkKKSe41qZfp1f1uWMJK6iTuFYm03iucjvxm9l/V/7ubS9VWP08d6Q+dX8v7VlNXLr9Wb4zNafoY/LtuaUstOY/kKW/cHPvlxx/d7TP13lNZuATu169WtfTco=
*/