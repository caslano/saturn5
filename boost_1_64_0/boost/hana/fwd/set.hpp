/*!
@file
Forward declares `boost::hana::set`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SET_HPP
#define BOOST_HANA_FWD_SET_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! Basic unordered container requiring unique, `Comparable` and
    //! `Hashable` keys.
    //!
    //! A set is an unordered container that can hold heterogeneous keys.
    //! A set requires (and ensures) that no duplicates are present when
    //! inserting new keys.
    //!
    //! @note
    //! The actual representation of a `hana::set` is implementation-defined.
    //! In particular, one should not take for granted the order of the
    //! template parameters and the presence of any additional constructors
    //! or assignment operators than what is documented. The canonical way of
    //! creating a `hana::set` is through `hana::make_set`. More details
    //! [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two sets are equal iff they contain the same elements, regardless of
    //! the order.
    //! @include example/set/comparable.cpp
    //!
    //! 2. Foldable\n
    //! Folding a set is equivalent to folding the sequence of its values.
    //! However, note that the values are not required to be in any specific
    //! order, so using the folds provided here with an operation that is not
    //! both commutative and associative will yield non-deterministic behavior.
    //! @include example/set/foldable.cpp
    //!
    //! 3. Searchable\n
    //! The elements in a set act as both its keys and its values. Since the
    //! elements of a set are unique, searching for an element will return
    //! either the only element which is equal to the searched value, or
    //! `nothing`. Also note that `operator[]` can be used instead of the
    //! `at_key` function.
    //! @include example/set/searchable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! Any `Foldable` structure can be converted into a `hana::set` with
    //! `to<set_tag>`. The elements of the structure must all be compile-time
    //! `Comparable`. If the structure contains duplicate elements, only
    //! the first occurence will appear in the resulting set. More
    //! specifically, conversion from a `Foldable` is equivalent to
    //! @code
    //!     to<set_tag>(xs) == fold_left(xs, make_set(), insert)
    //! @endcode
    //!
    //! __Example__
    //! @include example/set/to.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename implementation_defined>
    struct set {
        //! Default-construct a set. This constructor only exists when all the
        //! elements of the set are default-constructible.
        constexpr set() = default;

        //! Copy-construct a set from another set. This constructor only
        //! exists when all the elements of the set are copy-constructible.
        constexpr set(set const& other) = default;

        //! Move-construct a set from another set. This constructor only
        //! exists when all the elements of the set are move-constructible.
        constexpr set(set&& other) = default;

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::at_key`
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key);
    };
#else
    template <typename ...Xs>
    struct set;
#endif

    //! Tag representing the `hana::set` container.
    //! @relates hana::set
    struct set_tag { };

    //! Function object for creating a `hana::set`.
    //! @relates hana::set
    //!
    //! Given zero or more values `xs...`, `make<set_tag>` returns a `set`
    //! containing those values. The values must all be compile-time
    //! `Comparable`, and no duplicate values may be provided. To create
    //! a `set` from a sequence with possible duplicates, use `to<set_tag>`
    //! instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<set_tag> = [](auto&& ...xs) {
        return set<implementation_defined>{forwarded(xs)...};
    };
#endif

    //! Equivalent to `make<set_tag>`; provided for convenience.
    //! @relates hana::set
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/make.cpp
    constexpr auto make_set = make<set_tag>;

    //! Insert an element in a `hana::set`.
    //! @relates hana::set
    //!
    //! If the set already contains an element that compares equal, then
    //! nothing is done and the set is returned as is.
    //!
    //!
    //! @param set
    //! The set in which to insert a value.
    //!
    //! @param element
    //! The value to insert. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& set, auto&& element) {
        return tag-dispatched;
    };
#endif

    //! Remove an element from a `hana::set`.
    //! @relates hana::set
    //!
    //! Returns a new set containing all the elements of the original,
    //! except the one comparing `equal` to the given element. If the set
    //! does not contain such an element, a new set equal to the original
    //! set is returned.
    //!
    //!
    //! @param set
    //! The set in which to remove a value.
    //!
    //! @param element
    //! The value to remove. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/erase_key.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto erase_key = [](auto&& set, auto&& element) {
        return tag-dispatched;
    };
#endif

    //! Returns the union of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `union_(xs, ys)` is a new set containing
    //! all the elements of `xs` and all the elements of `ys`, without
    //! duplicates. For any object `x`, the following holds: `x` is in
    //! `hana::union_(xs, ys)` if and only if `x` is in `xs` or `x` is in `ys`.
    //!
    //!
    //! @param xs, ys
    //! Two sets to compute the union of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/union.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto union_ = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif

    //! Returns the intersection of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `intersection(xs, ys)` is a new set
    //! containing exactly those elements that are present both in `xs` and
    //! in `ys`.
    //! In other words, the following holds for any object `x`:
    //! @code
    //!     x ^in^ intersection(xs, ys) if and only if x ^in^ xs && x ^in^ ys
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two sets to intersect.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/intersection.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto intersection = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif
    //! Equivalent to `to<set_tag>`; provided for convenience.
    //! @relates hana::set
    constexpr auto to_set = to<set_tag>;

    //! Returns the set-theoretic difference of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `difference(xs, ys)` is a new set
    //! containing all the elements of `xs` that are _not_ contained in `ys`.
    //! For any object `x`, the following holds:
    //! @code
    //!     x ^in^ difference(xs, ys) if and only if x ^in^ xs && !(x ^in^ ys)
    //! @endcode
    //!
    //!
    //! This operation is not commutative, i.e. `difference(xs, ys)` is not
    //! necessarily the same as `difference(ys, xs)`. Indeed, consider the
    //! case where `xs` is empty and `ys` isn't. Then, `difference(xs, ys)`
    //! is empty but `difference(ys, xs)` is equal to `ys`. For the symmetric
    //! version of this operation, see `symmetric_difference`.
    //!
    //!
    //! @param xs
    //! A set param to remove values from.
    //!
    //! @param ys
    //! The set whose values are removed from `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
};
#endif

    //! Returns the symmetric set-theoretic difference of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `symmetric_difference(xs, ys)` is a new
    //! set containing all the elements of `xs` that are not contained in `ys`,
    //! and all the elements of `ys` that are not contained in `xs`. The
    //! symmetric difference of two sets satisfies the following:
    //! @code
    //!     symmetric_difference(xs, ys) == union_(difference(xs, ys), difference(ys, xs))
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two sets to compute the symmetric difference of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/symmetric_difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
constexpr auto symmetric_difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif


BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SET_HPP

/* set.hpp
ks2zyIGm2kEN4x7Rmtu4zqK+Ub+3fnNjqwmtM2ZP40HTihcVdeOYvYT7f1GrbTtk2mTaN2b7ioMVY3ZSS2QHbPkTmpf+tLJCHCxm9LqB3utvlejN8AeB3oFXcUS2htuUkYTV3xUzVp9krGZVMVJLbrkASF2bzvxfhWZfhTbHupHEMmdcMPLCRZfQ0BKFF4kkSkMOGKycj2XTlGPSFzlHgXwP0nHubEPe6V75ox05QoCTXPDk69c0TTNQF3PWlstdGSihh1vrc7Rb67PPdGt9DJIv5Kzu4vVsLu/GgCwIr87o3zvfXz9N34+Rew77MRSWVCX3Y0iWmFdBSJfcjVEI5+ElKUQ+JEa/zcPCzmy56CpRyXStCXm5zm1/BjSF04xUPWddvrzPPpd3Z2yVMrnc5H32CeWwfp99xomz3I1x+psO0oSsl3KM7jdiq6pWBZJpOoE+m+7yEp/90Pmrq4qSeHFY1fVLltpWmvWj+ZPfsZRJXoyfznsxeKcPzIQYIGyfAKRnFJlM6y4yKdREJoUdIhNCfl3CudoAboCO5IcgEtRFS49cfTtGxq3d9mOcYi+G2qxsoK0aJAlM7ss4eU8GAtUNir6gR0nyhim/6HsJr/MY3wAezs04jyuAEc5zrjs0ciHTJdEroUQSm6LdoxFDJN1HSPK+Vjv1UhVpeMfGjt7s2MgFsJS9t8ddG17GNFeXzTSpLn685IjBg3jnRjZddADVEu3ZgOGmJLhC87PUSfHm0Xdw5J94Fzs4clFQCQ1bVZW6hXqRQcOkUcPkKfcEMR2uEcesrr/B/RnuGbj1cH+A+zXcT+BeOI67QuGa4Z6GexLud3CPwD18/H9fXvF+/6H1LYmFbjF7fnuiJ0nCWg/Nt5NmkOk8qU5J7Ka86ec7bRJ+yYyJT/YnjssN6QAuWMEyvKkMSV3MtfG/sEHcNYjX75ga3a7qfuEbQtHHsTPhtpaVumBlDrp1gX3lvY7vPOZ20U2LqpE+duHjGptwjOZtI6/egM5xFJ0BGre0cLHMJNQ6iTZrUK+iknbkI00bpUkgzTQ9zZCwISjeyOX1a8xHsI4O3ywjPxVeEE4RbQVciaA44UNlxZSPa0vd2bJKQfEywtXJjkAiu0wMnc7V4SW8THAeeZyT5V1PTwO/Qwwa8Tz3ko7KZaDwjVcRPoCMceE7ZF0KUJsUkSXrEqpHIg4Hgjzi4euoYi9exqArjeB9ITzSMN7gs/uDQPTSDEZ0/5ESUda6xuWW8KLW72GoWuwWi/tL3NrrEtXf49YJil1gqIOqEM1F+ARYP7w8NUSt2nJ7IkH4qqCtv4GwK5Et+lzPYgU/SW3FbXnk8ZB+tVwKsxib51meJel3+dST6Tdd0q8X9Pvbj56Cfr1J+v3NgA76ddb9FJkSSqkbUGzlDUmac9Y2yH2kGUzSU5IkPQ0kbepE0uNGMqaH5CVJujogHgIfHfMBKdV5QK2P8WWH7+qAUIfoMplinQofnELrGvPHTqLF0KN6w4fDrY5QU9J3V/gOkEffSVzfgPjEPMpg3Uc1Ur+glNyZno/cRPx7EHTsYDo2eAl/6LCXhf4Mv07KnwasH72BYW35sbxK0YO9oX4NpepUdykQuekyRmTlcEmyNpCsLbQXyVsfby62uOi7yW7Q70KPeLwfyhGE0sM1g0MvdiCJi3pzIhfVmh/gVqoQx3ykdj4qvjuPez4aKUDEHAwTo5ItxitJcs4WlZeQJ70SRDQy9LqeMyUXWWMIy7cPpi3pomIeF4LuR72v6nwTPQHoUuX+LUC5chljCljaPJyx9Mg47qWAMj2USNY/JXw71T+PQSPpnl/1ORLZATG2hJMzkGcj7uP5ZOUS2Twl7po=
*/