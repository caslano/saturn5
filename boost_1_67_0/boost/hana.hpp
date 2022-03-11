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