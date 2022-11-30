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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
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
*/