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
1R4WeM9ajfTyy3VPQddp8o4wknBNAJZABsjloQ2OBCGLWlq86jp2xyfs7ZiLikOVCzsdOh5jfgIoGTUVp/ZcdnQAxtgVeusP7yB1WutwWbHTZjW2kdf0qL2V8wFBYXtIVI259TxfUdI1K7ouIZO+M5pwd9iRh/n1yG9jDXZke1BO4QILkUn+Qfn7yRAw/ViZKriJEFHVeqILGMr5EpLiRsIIYkR6+hdWRwgZLHz8IGPpDezB6A+7GLzTHPLMCIcS8ngDtq3uSAzBb9esaZ3/98YNNvysTFUZgwd5fNkKCllY2V+oKb1ioWV0SZtxwjrz/ula8A+tcDEHwAtjcGRGwR882sioC5yRepVQD7ffnizIudtM4OqKNODFNgjPKCI/wWXqHv1OfVLltTuwkV6GNSpDgYb3zTjvgScd5eJI4YlXBCQvByVKpvQPwPEIuVspU7wFjhSd8lcdLTFi/HfshDITNbwgms1o4APpeF2k5gL4EdjG1xcKBG5N/d5ZvMbkYeh6Xs/l2NN8vhotYgoRsZ2hlX3us5qd9tOWgeur34T1uYgR2Xb8QVgeJg==
*/