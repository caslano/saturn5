/*!
@file
Forward declares `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_COMPARABLE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Comparable Comparable
    //! The `Comparable` concept defines equality and inequality.
    //!
    //! Intuitively, `Comparable` objects must define a binary predicate named
    //! `equal` that returns whether both objects represent the same abstract
    //! value. In other words, `equal` must check for deep equality. Since
    //! "representing the same abstract value" is difficult to express
    //! formally, the exact meaning of equality is partially left to
    //! interpretation by the programmer with the following guidelines:\n
    //! 1. Equality should be compatible with copy construction; copy
    //!    constructing a value yields an `equal` value.
    //! 2. Equality should be independent of representation; an object
    //!    representing a fraction as `4/8` should be `equal` to an object
    //!    representing a fraction as `2/4`, because they both represent
    //!    the mathematical object `1/2`.
    //!
    //! Moreover, `equal` must exhibit properties that make it intuitive to
    //! use for determining the equivalence of objects, which is formalized
    //! by the laws for `Comparable`.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! 1. `equal`\n
    //! When `equal` is defined, `not_equal` is implemented by default as its
    //! complement. For all objects `x`, `y` of a `Comparable` tag,
    //! @code
    //!     not_equal(x, y) == not_(equal(x, y))
    //! @endcode
    //!
    //!
    //! Laws
    //! ----
    //! `equal` must define an [equivalence relation][1], and `not_equal` must
    //! be its complement. In other words, for all objects `a`, `b`, `c` with
    //! a `Comparable` tag, the following must hold:
    //! @code
    //!     equal(a, a)                                         // Reflexivity
    //!     if equal(a, b) then equal(b, a)                     // Symmetry
    //!     if equal(a, b) && equal(b, c) then equal(a, c)      // Transitivity
    //!     not_equal(a, b) is equivalent to not_(equal(a, b))
    //! @endcode
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`, `hana::map`, `hana::optional`, `hana::pair`,
    //! `hana::range`, `hana::set`, `hana::string`, `hana::tuple`,
    //!  `hana::type`
    //!
    //!
    //! Free model for `EqualityComparable` data types
    //! ----------------------------------------------
    //! Two data types `T` and `U` that model the cross-type EqualityComparable
    //! concept presented in [N3351][2] automatically model the `Comparable`
    //! concept by setting
    //! @code
    //!     equal(x, y) = (x == y)
    //! @endcode
    //! Note that this also makes EqualityComparable types in the
    //! [usual sense][3] models of `Comparable` in the same way.
    //!
    //!
    //! Equality-preserving functions
    //! -----------------------------
    //! Let `A` and `B` be two `Comparable` tags. A function @f$f : A \to B@f$
    //! is said to be equality-preserving if it preserves the structure of the
    //! `Comparable` concept, which can be rigorously stated as follows. For
    //! all objects `x`, `y` of tag `A`,
    //! @code
    //!     if  equal(x, y)  then  equal(f(x), f(y))
    //! @endcode
    //! Equivalently, we simply require that `f` is a function in the usual
    //! mathematical sense. Another property is [injectivity][4], which can be
    //! viewed as being a "lossless" mapping. This property can be stated as
    //! @code
    //!     if  equal(f(x), f(y))  then  equal(x, y)
    //! @endcode
    //! This is equivalent to saying that `f` maps distinct elements to
    //! distinct elements, hence the "lossless" analogy. In other words, `f`
    //! will not collapse distinct elements from its domain into a single
    //! element in its image, thus losing information.
    //!
    //! These functions are very important, especially equality-preserving
    //! ones, because they allow us to reason simply about programs. Also
    //! note that the property of being equality-preserving is taken for
    //! granted in mathematics because it is part of the definition of a
    //! function. We feel it is important to make the distinction here
    //! because programming has evolved differently and as a result
    //! programmers are used to work with functions that do not preserve
    //! equality.
    //!
    //!
    //! Cross-type version of the methods
    //! ---------------------------------
    //! The `equal` and `not_equal` methods are "overloaded" to handle
    //! distinct tags with certain properties. Specifically, they are
    //! defined for _distinct_ tags `A` and `B` such that
    //! 1. `A` and `B` share a common tag `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Comparable` when taken individually
    //! 3. @f$ \mathtt{to<C>} : A \to C @f$ and @f$\mathtt{to<C>} : B \to C@f$
    //!    are both equality-preserving and injective (i.e. they are embeddings),
    //!    as determined by the `is_embedding` metafunction.
    //!
    //! The method definitions for tags satisfying the above properties are
    //! @code
    //!     equal(x, y)     = equal(to<C>(x), to<C>(y))
    //!     not_equal(x, y) = not_equal(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Important note: special behavior of `equal`
    //! -------------------------------------------
    //! In the context of programming with heterogeneous values, it is useful
    //! to have unrelated objects compare `false` instead of triggering an
    //! error. For this reason, `equal` adopts a special behavior for
    //! unrelated objects of tags `T` and `U` that do not satisfy the above
    //! requirements for the cross-type overloads. Specifically, when `T` and
    //! `U` are unrelated (i.e. `T` can't be converted to `U` and vice-versa),
    //! comparing objects with those tags yields a compile-time false value.
    //! This has the effect that unrelated objects like `float` and
    //! `std::string` will compare false, while comparing related objects that
    //! can not be safely embedded into the same super structure (like
    //! `long long` and `float` because of the precision loss) will trigger a
    //! compile-time assertion. Also note that for any tag `T` for which the
    //! minimal complete definition of `Comparable` is not provided, a
    //! compile-time assertion will also be triggered because `T` and `T`
    //! trivially share the common tag `T`, which is the expected behavior.
    //! This design choice aims to provide more flexibility for comparing
    //! objects, while still rejecting usage patterns that are most likely
    //! programming errors.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Equivalence_relation#Definition
    //! [2]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3351.pdf
    //! [3]: http://en.cppreference.com/w/cpp/named_req/EqualityComparable
    //! [4]: http://en.wikipedia.org/wiki/Injective_function
    template <typename T>
    struct Comparable;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
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
*/