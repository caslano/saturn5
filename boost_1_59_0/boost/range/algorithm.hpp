///////////////////////////////////////////////////////////////////////////////
/// \file algorithm.hpp
///   Includes the range-based versions of the algorithms in the
///   C++ standard header file <algorithm>
//
/////////////////////////////////////////////////////////////////////////////

// Copyright 2009 Neil Groves.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Acknowledgements:
// This code uses combinations of ideas, techniques and code snippets
// from: Thorsten Ottosen, Eric Niebler, Jeremy Siek,
// and Vladimir Prus'
//
// The original mutating algorithms that served as the first version
// were originally written by Vladimir Prus'
// <ghost@cs.msu.su> code from Boost Wiki

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_RANGE_ALGORITHM_HPP_INCLUDED_01012009
#define BOOST_RANGE_ALGORITHM_HPP_INCLUDED_01012009

#include <boost/range/concepts.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/detail/range_return.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>

// Non-mutating algorithms
#include <boost/range/algorithm/adjacent_find.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/find_end.hpp>
#include <boost/range/algorithm/find_first_of.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/lexicographical_compare.hpp>
#include <boost/range/algorithm/mismatch.hpp>
#include <boost/range/algorithm/search.hpp>
#include <boost/range/algorithm/search_n.hpp>

// Mutating algorithms
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/copy_backward.hpp>
#include <boost/range/algorithm/fill.hpp>
#include <boost/range/algorithm/fill_n.hpp>
#include <boost/range/algorithm/generate.hpp>
#include <boost/range/algorithm/inplace_merge.hpp>
#include <boost/range/algorithm/merge.hpp>
#include <boost/range/algorithm/nth_element.hpp>
#include <boost/range/algorithm/partial_sort.hpp>
#include <boost/range/algorithm/partial_sort_copy.hpp>
#include <boost/range/algorithm/partition.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/algorithm/remove.hpp>
#include <boost/range/algorithm/remove_copy.hpp>
#include <boost/range/algorithm/remove_copy_if.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/range/algorithm/replace.hpp>
#include <boost/range/algorithm/replace_copy.hpp>
#include <boost/range/algorithm/replace_copy_if.hpp>
#include <boost/range/algorithm/replace_if.hpp>
#include <boost/range/algorithm/reverse.hpp>
#include <boost/range/algorithm/reverse_copy.hpp>
#include <boost/range/algorithm/rotate.hpp>
#include <boost/range/algorithm/rotate_copy.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/stable_partition.hpp>
#include <boost/range/algorithm/stable_sort.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm/unique_copy.hpp>

// Binary search
#include <boost/range/algorithm/binary_search.hpp>
#include <boost/range/algorithm/equal_range.hpp>
#include <boost/range/algorithm/lower_bound.hpp>
#include <boost/range/algorithm/upper_bound.hpp>

// Set operations of sorted ranges
#include <boost/range/algorithm/set_algorithm.hpp>

// Heap operations
#include <boost/range/algorithm/heap_algorithm.hpp>

// Minimum and Maximum
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/min_element.hpp>

// Permutations
#include <boost/range/algorithm/permutation.hpp>

#endif // include guard


/* algorithm.hpp
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
*/