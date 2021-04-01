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
d5ZF2tyWsD4UuwvXzwG5gJ7S+VE6U+B9l5e+BYEgAd9n5t3COMzZpzr38QFWXo73UoHpvqmc/ETZ/JmbqlPBRs2K0b/Bklu9hyatMYb1XC4Es1WPQi9gfUc2FTqutlUZAdqxsSDYlhtYKfDx2GUdlpnAR/jQyzt41LkZeRs2tzOs/vnUlBGwhnzN4wHg/7q8/8MsTHOpR7i97EjsVso2YKmlTq7REiEg19c8GuRB5/6+3DJLFzafsqUPobejrpdncsHzDnmCEL6/DmZgaH9r7gOAdTNMhx0gqcvdqeeWOURd2vcpDWGkwriSjDbAURedvTfW/wQKhYFGblr5vMrk28wW4Jpn2LZCMkKaUmLUaWPZ/rriRC+5/pEmH5GdV+4wX8+MBBr0aoRYiXF5FHFs0XJagWSzWDWw9BD7OPHQ5m5CWjUyVHUH90xfkrDdIACwfMnxaKraTzmvyWTsL0GZhiuljBtDJRPCUMXXRN5gntPjvwH6/9HDldVGqGS/w+ZJfB+2Mug648qzGVDtU23fOUvjtzntJiihUezX+d8DljnfxtBV4Hhog9HpNw==
*/