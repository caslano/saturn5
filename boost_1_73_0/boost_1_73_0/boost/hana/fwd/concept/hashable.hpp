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
5LeBipDfWCJCfsfSEPLbTkJMhbXTmwrlIULpBzVcNPkgvwOoB9MyhHiwijDaQX4j1m/hxX7KQQe8EsIhYxJANyRkgGQjCKAbJBrk9yppRhj+anUUxcDjj6UXrIc4cqGigqcWCiwgYkEHCqYVMoZOUuETNFrFSSjc5kPRCfIbQSYoQD4qIZsNTSQkm3loxPnJr93dElXO/nTeEXWrqART1kAmGCJYOsEqxRIKppGdUpiLa7c3F6vDhRILbshoasGaCSAXQtcQeiGqwggGE0as4LV/+0kGH/pKaIaKTgDRUDACUo1gqG6QbjAdVvywSKgx9AZQvCPMGFjuIXqJYx86Pnj+oQEEYiB8wGAOouLpZCF+UYuVnEzEZ1AUF2F7EYKNcLB8fEQ1JJqRKFb0cpKjo+4oCdnH7wwjmU6NhOToCM9Hjo6QNwMa6Mh06mIjhlLJ9w2lykDhVGQ67YKJTKdBRIQqGsZDaE0oDZlOUas5d2kICSGjtnOQ+g6HEA4iARNEQRp4wAwkCKUV8Q/p/gsH/5hOV04/guyg1UeSD7wd8NSD9hHLPBRoQoiHjA2Qd5DBImiHhKSHdXgkzdbxcA6nHZGU4+gIxTgITH7CIdkvgG80xnPRjd/PDs97v3XCNj4vsjK9vhNkg6uqcw2O
*/