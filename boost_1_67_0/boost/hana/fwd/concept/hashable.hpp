/*!
@file
Forward declares `boost::hana::Hashable`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_HASHABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_HASHABLE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Hashable Hashable
    //! The `Hashable` concept represents objects that can be normalized to
    //! a type-level hash.
    //!
    //! In day to day programming, hashes are very important as a way to
    //! efficiently lookup objects in maps. While the implementation of
    //! maps is very different, the same idea of using hashes for efficient
    //! lookup applies in metaprogramming. The `Hashable` concept represents
    //! objects that can be summarized (possibly with loss of information) to
    //! a type, in a way suitable for use in hash-based data structures. Of
    //! course, in order for a hash to be well-behaved, it must obey some laws
    //! that are explained below.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `hash`, satisfying the laws below
    //!
    //!
    //! Laws
    //! ----
    //! First, `hana::hash` must return a `hana::type`. Furthermore, for any
    //! two `Hashable` objects `x` and `y`, it must be the case that
    //! @code
    //!     x == y   implies   hash(x) == hash(y)
    //! @endcode
    //!
    //! where `==` denotes `hana::equal`. In other words, any two objects that
    //! compare equal (with `hana::equal`) must also have the same hash.
    //! However, the reverse is not true, and two different objects may have
    //! the same hash. This situation of two different objects having the same
    //! hash is called a _collision_.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`, `hana::type`, `hana::string`
    //!
    //!
    //! Free model for `IntegralConstant`s
    //! ----------------------------------
    //! Any `IntegralConstant` is `Hashable`, by normalizing its value to a
    //! `hana::integral_constant`. The type of the value held in the normalized
    //! `integral_constant` is `unsigned long long` for unsigned integral
    //! types, and `signed long long` for signed integral types.
    template <typename T>
    struct Hashable;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_HASHABLE_HPP

/* hashable.hpp
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
*/