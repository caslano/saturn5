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
HgPPUv66HaAN4J/mq9Rq+/YO4aVduJy9LotJkse7WBt48pT0MhRGWcOZF2W/tdhhv7XcYb+1Ooos/QqrLD3TNzjswVa3IFPf5xZzzeZg10de+/6jT1a8se+SjQPXHp5CHQvBtsYxQ4XpWMikju6uwKnUpbCQazeXU9a+hms43wX24ppNHnB/mA6FJMrWpwLzgT0oU98HeDZwBGXrz6NOhSnUqXA1Zexvooz9Q8CxwFeoQ+FN4HjgQepS+AtwIvA94CTgceD5Fpn8Xe46kOtc5zrXuc51rnOd68Lm/5Wf3/y/pHZlZWngb9HyksV15iLAaa0BZKr49uNMmcoLL5gwXaz9T5sJoVGJn4j4sGjVFfHzTPo5hUUTxs2YMX7chOlFk2bOnTb7gpny/Y/rI6zpLpxzwexxUyYp6hW8Mx3f31xvKPbQdjblDW6A/wbSVn/qMdcbxl148cwJRReNmzanaMKceUWlKI+aokVlAbmDyTJ/L61bYfJKGYL1km6V6ou/fniuRzC/LNrBtMsSTNfXt6jLVAehGYW8EVvjXxaSN1grNFdB3qqrhaa0vqYG9+e57g1CU6W640nnqHb63HVJSuvmh/nAyTIPk+fSe/zgmfv5dhvua7hPfwt8B+KNSJ//WbTyW1Tj90eWHcuIabppnQ0XSLhe6zLYI2Ej/Nm1/MZsub7Ucr3Sv6IudJbiGrneg2FIWEo4l/Nos4xOvZxMe4dfk/wgw047leNZRs1c0zqHmYyBbwLN4ahldBn0WMKOPlpZrXIsK6Y9R65f1d68jlap165C18WOanCNR7Kkvkd7Hvby5DrUP+T6qBPKV1D+M6LdpADBG+LAG+f/WUDwgzjyw/Y0OdieYhVXcmhDDv4e5FugvA5lVVpeUnmZv6zl8mJ6nMFgW/JLeApkLmAnHD5UjjCZC3ZZjkxXYS9HIallOQZpUix5lPkrmMcspzyEpFbWx/KU3VYt6KO3c/bxYrk+mWGs/Ek45gzUkzxYZD3xeSkrT1o8AGnzrLR8LtSpHmN9FHYZrkL2U3eAh32OdYqMneuS6WJ1Xb4i4XzVXsVDWislYoxlXTLd8Kh9ptByPVNfL62vrataWhQQaWZ9arqI+kll/fxKrg+B/KfvtOpEj7mMywrrT9m2+rDyah+jq1n+PeHb0i77faZcvBGt/Cv9kI8OvDdov7g19mjHB+9FGfz1tFFZC/8t810d9V7Q2SufEKjwaPXNcX2ZpJ3N+g/m1dupnnk9V9uLrpXwfKH3xup61++Zarm+kO0gmD5HZZI+oh3wfbJG6C5kuwimGyr9fJo8h/m9UFlfbevfpOPaeKFcYzsCXwHrwUqfJ9gstNNC9XGK76co73Etq+eNtbepqYwLa1PaHvQ0yZfPFl7/XJps5NptA78HVGD/JvTVWAS+imr8ZgsoraqvrKt17O9M21OXe08JLwn/TtLtpZ9cv8TxG6mTXK9X4zBeTFe+0/5GCq5VN3mcbOI62xL+vegnrusxL3dYVvv9Y1fuL/pmxTMvOdnQPXnbydFtFTvrS/4gx4w33upa+8yjmztUvbv59bMufL3o5G0Dn6ze5ei2ip1tBo9JMOMvz/V7MvN3LL6n9Bd7ropffd2Zs6l8sew5tH2z99uv7Xl67aQb793w99fOXuZky9lZP/RlUu/Dmp+bO/2dX8etfXXFeXt//uodTrarT94WcnRb1842rQPnITjf4Lxnr2E/D7GRcq6bganARmAn4I20e3oTsDfwNtrlfAg4jNdHm/nQrugPgOOBt3PvZRtwDu2MzqWd0fm0H1oF3AGsBd4HXMH0q2lfcy3wQeANjJdzQopzBuAtfI62wLowedqOwM4Md6Oe7R4=
*/