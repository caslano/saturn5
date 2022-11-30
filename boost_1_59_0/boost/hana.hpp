/*!
@file
Includes all the library components except the adapters for external
libraries.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_HPP
#define BOOST_HANA_HPP

//! @defgroup group-concepts Concepts
//! Concepts provided by the library.

//! @defgroup group-datatypes Data types
//! General purpose data types provided by the library.

//! @defgroup group-functional Functional
//! General purpose function objects.

//! @defgroup group-core Core
//! Core utilities of the library.

//! @defgroup group-experimental Experimental features
//! Experimental features that may or may not make it into the library.
//! These features should not expected to be stable.

//! @defgroup group-ext External adapters
//! Adapters for external libraries.

//! @defgroup group-config Configuration options
//! Configurable options to tweak the global behavior of the library.

//! @defgroup group-assertions Assertions
//! Macros to perform different kinds of assertions.

//! @defgroup group-details Details
//! Implementation details. Do not rely on anything here, even if it is
//! documented.

// Include config.hpp first, so that warning messages about compiler support
// appear as soon as possible.
#include <boost/hana/config.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost {
    //! Namespace containing everything in the library.
    namespace hana {
        //! Namespace containing C++14 user-defined literals provided by Hana.
        namespace literals {}
    }
}
#endif

#include <boost/hana/accessors.hpp>
#include <boost/hana/adapt_adt.hpp>
#include <boost/hana/adapt_struct.hpp>
#include <boost/hana/adjust.hpp>
#include <boost/hana/adjust_if.hpp>
#include <boost/hana/all.hpp>
#include <boost/hana/all_of.hpp>
#include <boost/hana/and.hpp>
#include <boost/hana/any.hpp>
#include <boost/hana/any_of.hpp>
#include <boost/hana/ap.hpp>
#include <boost/hana/append.hpp>
#include <boost/hana/assert.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/at_key.hpp>
#include <boost/hana/back.hpp>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/cartesian_product.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/comparing.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core.hpp>
#include <boost/hana/count.hpp>
#include <boost/hana/count_if.hpp>
#include <boost/hana/cycle.hpp>
#include <boost/hana/define_struct.hpp>
#include <boost/hana/difference.hpp>
#include <boost/hana/div.hpp>
#include <boost/hana/drop_back.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/drop_front_exactly.hpp>
#include <boost/hana/drop_while.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/erase_key.hpp>
#include <boost/hana/eval.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/extract.hpp>
#include <boost/hana/fill.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/find.hpp>
#include <boost/hana/find_if.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/fold.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/functional.hpp>
#include <boost/hana/fuse.hpp>
#include <boost/hana/greater.hpp>
#include <boost/hana/greater_equal.hpp>
#include <boost/hana/group.hpp>
#include <boost/hana/index_if.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/insert.hpp>
#include <boost/hana/insert_range.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/intersection.hpp>
#include <boost/hana/intersperse.hpp>
#include <boost/hana/is_disjoint.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/is_subset.hpp>
#include <boost/hana/keys.hpp>
#include <boost/hana/lazy.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/less.hpp>
#include <boost/hana/less_equal.hpp>
#include <boost/hana/lexicographical_compare.hpp>
#include <boost/hana/lift.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/max.hpp>
#include <boost/hana/maximum.hpp>
#include <boost/hana/members.hpp>
#include <boost/hana/min.hpp>
#include <boost/hana/minimum.hpp>
#include <boost/hana/minus.hpp>
#include <boost/hana/mod.hpp>
#include <boost/hana/monadic_compose.hpp>
#include <boost/hana/monadic_fold_left.hpp>
#include <boost/hana/monadic_fold_right.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/negate.hpp>
#include <boost/hana/none.hpp>
#include <boost/hana/none_of.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/not_equal.hpp>
#include <boost/hana/one.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/ordering.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/partition.hpp>
#include <boost/hana/permutations.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/power.hpp>
#include <boost/hana/prefix.hpp>
#include <boost/hana/prepend.hpp>
#include <boost/hana/product.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/remove.hpp>
#include <boost/hana/remove_at.hpp>
#include <boost/hana/remove_if.hpp>
#include <boost/hana/remove_range.hpp>
#include <boost/hana/repeat.hpp>
#include <boost/hana/replace.hpp>
#include <boost/hana/replace_if.hpp>
#include <boost/hana/replicate.hpp>
#include <boost/hana/reverse.hpp>
#include <boost/hana/reverse_fold.hpp>
#include <boost/hana/scan_left.hpp>
#include <boost/hana/scan_right.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/size.hpp>
#include <boost/hana/slice.hpp>
#include <boost/hana/sort.hpp>
#include <boost/hana/span.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/suffix.hpp>
#include <boost/hana/sum.hpp>
#include <boost/hana/symmetric_difference.hpp>
#include <boost/hana/take_back.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/take_while.hpp>
#include <boost/hana/tap.hpp>
#include <boost/hana/then.hpp>
#include <boost/hana/traits.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unfold_left.hpp>
#include <boost/hana/unfold_right.hpp>
#include <boost/hana/union.hpp>
#include <boost/hana/unique.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/value.hpp>
#include <boost/hana/version.hpp>
#include <boost/hana/while.hpp>
#include <boost/hana/zero.hpp>
#include <boost/hana/zip.hpp>
#include <boost/hana/zip_shortest.hpp>
#include <boost/hana/zip_shortest_with.hpp>
#include <boost/hana/zip_with.hpp>

#endif // !BOOST_HANA_HPP

/* hana.hpp
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
*/