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
XbAO1fsz8XLUXT4m6yRmjbTV9BSlI0gW7xGsFB+RE1Nni2MDN6IiVuDBiUSQVWEEqO0TyD/SzYdNqsI/DCcWmDDpCvJ75u+nWTnbBZWMbc3EFOCkZEW7RrfVt8chVzadlBDj008yU9nWbDRTNngCGkfsSdRSgycT0gLAtbaOQQ8QStJGO0zQEAV1vNhOGpro7CfpP9lC7ZduwjR9pNDDvhD0XAo67u/lUVCOurkRYKjl+nAac01FLuiq/x75IqmsbKr6PBLhQFcjjgVWidS8XQRSY/9O2MFXwAMnx1o2jvP5M6sEBYTI8x7GSxslDtAkMR7aoVIdaYqdvXFxs+dpmj3Gtq7F4nwh4IuNir15lDy+kjbavL6aVSvOjDwnUfpXGORqIP4ZB6IfpI8TrfEpX5GYGONTNrkkAJ7qKD+Im8fzwHUR+13Bgqh/FhgZAWhzJWZ5BmLmp10fPJQ8Y7ynGP767wquHU6x1zXRHQXzor0CbZYJf5qDC2zLawTAwB0+RwT3g3Q0cKNVevZ/JImmN1AxKly99CCuDFm5cr+4dpO1Bw+1CdzOinNYMWjtaK2ona5SK5jqwcqQlXY+Gc3IkKzNIEBZu1btvjay2iyafEAtZU2sEy6iKAj5FHGePMKlH7qV6b8Avz39v8Bvjj8bv/38J+M315+yLIGW2rZgV3cGN9jrq+SDub5cPiTUvywfrPVPyYfE+kfxUGB7fQP4oKN7mMgFVVxi5CvLOBAcFG0gXOHUeRxIDIg77FUxKBeEUz1iouqvQSnLyGpCO/oGTnYp7Sgj3Sx7fR+k0Uf5mrK4Ua4/DbHI3D+QsiyR721YYhKfrEYLl18kWng+MrKQ7noheRVaMTTk5q10hRObGlogG5pYICCr/o1DLFZrqK10SpRtsrCxzZojE89GYqTz+W/C7yT/GPxO8f8MvzcHrkfhzuVsKYp3hm9MqL8aieedNyVwMkTWzQhsHluIWJElwQhMrO+vB5qNwKT6k/VAiwxclsxBsCAUfdoCuxzBxtG2O97mcXwxiM4FliyfxUTQV3XQdwZ3mf29xG8X9swZPJzgT4b3hsYIfAjgt6OnWHQZxmlsb8nOh4AIlqZoPc93EZ/gmw0IFigkFnw9Ngm+16IJ+nhhNu59/WC0vh/CAFaZ+BaIBvQUv+lGM5KU4Y1QmOOvTQJJpI1tiXjAuN4UaCMsVkY64iUgDh3lbJTNtUK0EC0Q7RPNEY1EAw0Xwmzcsx1k42rNzRr37Wto3CKE4T5MdFjfHVgilVmRlyXnGiWz67g34zFhXxImIAWQwp7FFmBuZQGvs4BVh1sWkNDKAgIsYCEKkKDKGUFk7KQ8YUGKieQpyyRu2PC0OcuI0Im1Et1AS2LoRHU+o5rZohqUIKZZJW+mvntTMWiwhI0msCBDwE6Q3H6IydqJZOTsp5ATMw4XW5G+nOqAVcEr3rriLTEA8pPoEu+p2MMyhTlJQDfXKLFptcAjeTuxKWA/4GYgl2C7A1EyHHfi74DbYtp0gcXUe6jF9AK+tfgO8VhM6/B9ALB/4TCL6R58/V6LaSP+v0P4RfjviO9v8J2ANDMRNxD/e/H+B/z/EV9Th2N/zB0S4oMsTY+JScltrB2S+Ng2pV2HDqkdUjq0T1n7/8//xOd4zwO2sasm2s6snd7GNjZp+w1QBDyqPjIPbRlOTc1+zOGDuqkXuG33KnWaW6tuuNMmV/Z0i+AHXHW94Mregz/1GVwn0jrVQMt0JOgrE5wrE7zABKFkwVq3LeD1qUxpK30Yz7BE/n107nS6UX+Br0lk58GYExjmtERwqbPsLFna15OksvP3KzRGfIV/jSfoME3v5wmeZ2K7zpEJqyeJaq8=
*/