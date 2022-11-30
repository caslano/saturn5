//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_HPP
#define BOOST_COMPUTE_ALGORITHM_HPP

/// \file
///
/// Meta-header to include all Boost.Compute algorithm headers.

#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/algorithm/adjacent_difference.hpp>
#include <boost/compute/algorithm/adjacent_find.hpp>
#include <boost/compute/algorithm/all_of.hpp>
#include <boost/compute/algorithm/any_of.hpp>
#include <boost/compute/algorithm/binary_search.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/algorithm/count.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/algorithm/equal.hpp>
#include <boost/compute/algorithm/equal_range.hpp>
#include <boost/compute/algorithm/exclusive_scan.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/algorithm/find_end.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/algorithm/for_each.hpp>
#include <boost/compute/algorithm/for_each_n.hpp>
#include <boost/compute/algorithm/gather.hpp>
#include <boost/compute/algorithm/generate.hpp>
#include <boost/compute/algorithm/generate_n.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/compute/algorithm/includes.hpp>
#include <boost/compute/algorithm/inner_product.hpp>
#include <boost/compute/algorithm/iota.hpp>
#include <boost/compute/algorithm/is_partitioned.hpp>
#include <boost/compute/algorithm/is_permutation.hpp>
#include <boost/compute/algorithm/is_sorted.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/lexicographical_compare.hpp> 
#include <boost/compute/algorithm/max_element.hpp>
#include <boost/compute/algorithm/merge.hpp>
#include <boost/compute/algorithm/min_element.hpp>
#include <boost/compute/algorithm/minmax_element.hpp>
#include <boost/compute/algorithm/mismatch.hpp>
#include <boost/compute/algorithm/next_permutation.hpp>
#include <boost/compute/algorithm/none_of.hpp>
#include <boost/compute/algorithm/partial_sum.hpp>
#include <boost/compute/algorithm/partition.hpp>
#include <boost/compute/algorithm/partition_copy.hpp>
#include <boost/compute/algorithm/partition_point.hpp>
#include <boost/compute/algorithm/prev_permutation.hpp>
#include <boost/compute/algorithm/random_shuffle.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/algorithm/reduce_by_key.hpp>
#include <boost/compute/algorithm/remove.hpp>
#include <boost/compute/algorithm/remove_if.hpp>
#include <boost/compute/algorithm/replace.hpp>
#include <boost/compute/algorithm/replace_copy.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/algorithm/reverse_copy.hpp>
#include <boost/compute/algorithm/rotate.hpp>
#include <boost/compute/algorithm/rotate_copy.hpp>
#include <boost/compute/algorithm/scatter.hpp>
#include <boost/compute/algorithm/search.hpp>
#include <boost/compute/algorithm/search_n.hpp>
#include <boost/compute/algorithm/set_difference.hpp>
#include <boost/compute/algorithm/set_intersection.hpp>
#include <boost/compute/algorithm/set_symmetric_difference.hpp>
#include <boost/compute/algorithm/set_union.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/algorithm/stable_partition.hpp>
#include <boost/compute/algorithm/stable_sort.hpp>
#include <boost/compute/algorithm/stable_sort_by_key.hpp>
#include <boost/compute/algorithm/swap_ranges.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/algorithm/transform_reduce.hpp>
#include <boost/compute/algorithm/unique.hpp>
#include <boost/compute/algorithm/unique_copy.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>

#endif // BOOST_COMPUTE_ALGORITHM_HPP

/* algorithm.hpp
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
*/