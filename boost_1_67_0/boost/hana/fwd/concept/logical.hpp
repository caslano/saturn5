/*!
@file
Forward declares `boost::hana::Logical`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_LOGICAL_HPP
#define BOOST_HANA_FWD_CONCEPT_LOGICAL_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Logical Logical
    //! The `Logical` concept represents types with a truth value.
    //!
    //! Intuitively, a `Logical` is just a `bool`, or something that can act
    //! like one. However, in the context of programming with heterogeneous
    //! objects, it becomes extremely important to distinguish between those
    //! objects whose truth value is known at compile-time, and those whose
    //! truth value is only known at runtime. The reason why this is so
    //! important is because it is possible to branch at compile-time on
    //! a condition whose truth value is known at compile-time, and hence
    //! the return type of the enclosing function can depend on that truth
    //! value. However, if the truth value is only known at runtime, then
    //! the compiler has to compile both branches (because any or both of
    //! them may end up being used), which creates the additional requirement
    //! that both branches must evaluate to the same type.
    //!
    //! More specifically, `Logical` (almost) represents a [boolean algebra][1],
    //! which is a mathematical structure encoding the usual properties that
    //! allow us to reason with `bool`. The exact properties that must be
    //! satisfied by any model of `Logical` are rigorously stated in the laws
    //! below.
    //!
    //!
    //! Truth, falsity and logical equivalence
    //! --------------------------------------
    //! A `Logical` `x` is said to be _true-valued_, or sometimes also just
    //! _true_ as an abuse of notation, if
    //! @code
    //!     if_(x, true, false) == true
    //! @endcode
    //!
    //! Similarly, `x` is _false-valued_, or sometimes just _false_, if
    //! @code
    //!     if_(x, true, false) == false
    //! @endcode
    //!
    //! This provides a standard way of converting any `Logical` to a straight
    //! `bool`. The notion of truth value suggests another definition, which
    //! is that of logical equivalence. We will say that two `Logical`s `x`
    //! and `y` are _logically equivalent_ if they have the same truth value.
    //! To denote that some expressions `p` and `q` of a Logical data type are
    //! logically equivalent, we will sometimes also write
    //! @code
    //!     p   if and only if   q
    //! @endcode
    //! which is very common in mathematics. The intuition behind this notation
    //! is that whenever `p` is true-valued, then `q` should be; but when `p`
    //! is false-valued, then `q` should be too. Hence, `p` should be
    //! true-valued when (and only when) `q` is true-valued.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `eval_if`, `not_` and `while_`
    //!
    //! All the other functions can be defined in those terms:
    //! @code
    //!     if_(cond, x, y) = eval_if(cond, lazy(x), lazy(y))
    //!     and_(x, y) = if_(x, y, x)
    //!     or_(x, y) = if_(x, x, y)
    //!     etc...
    //! @endcode
    //!
    //!
    //! Laws
    //! ----
    //! As outlined above, the `Logical` concept almost represents a boolean
    //! algebra. The rationale for this laxity is to allow things like integers
    //! to act like `Logical`s, which is aligned with C++, even though they do
    //! not form a boolean algebra. Even though we depart from the usual
    //! axiomatization of boolean algebras, we have found through experience
    //! that the definition of a Logical given here is largely compatible with
    //! intuition.
    //!
    //! The following laws must be satisfied for any data type `L` modeling
    //! the `Logical` concept. Let `a`, `b` and `c` be objects of a `Logical`
    //! data type, and let `t` and `f` be arbitrary _true-valued_ and
    //! _false-valued_ `Logical`s of that data type, respectively. Then,
    //! @code
    //!     // associativity
    //!     or_(a, or_(b, c))   == or_(or_(a, b), c)
    //!     and_(a, and_(b, c)) == and_(and_(a, b), c)
    //!
    //!     // equivalence through commutativity
    //!     or_(a, b)   if and only if   or_(b, a)
    //!     and_(a, b)  if and only if   and_(b, a)
    //!
    //!     // absorption
    //!     or_(a, and_(a, b)) == a
    //!     and_(a, or_(a, b)) == a
    //!
    //!     // left identity
    //!     or_(a, f)  == a
    //!     and_(a, t) == a
    //!
    //!     // distributivity
    //!     or_(a, and_(b, c)) == and_(or_(a, b), or_(a, c))
    //!     and_(a, or_(b, c)) == or_(and_(a, b), and_(a, c))
    //!
    //!     // complements
    //!     or_(a, not_(a))  is true-valued
    //!     and_(a, not_(a)) is false-valued
    //! @endcode
    //!
    //! > #### Why is the above not a boolean algebra?
    //! > If you look closely, you will find that we depart from the usual
    //! > boolean algebras because:
    //! > 1. we do not require the elements representing truth and falsity to
    //! >    be unique
    //! > 2. we do not enforce commutativity of the `and_` and `or_` operations
    //! > 3. because we do not enforce commutativity, the identity laws become
    //! >    left-identity laws
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Free model for arithmetic data types
    //! ------------------------------------
    //! A data type `T` is arithmetic if `std::is_arithmetic<T>::%value` is
    //! true. For an arithmetic data type `T`, a model of `Logical` is
    //! provided automatically by using the result of the builtin implicit
    //! conversion to `bool` as a truth value. Specifically, the minimal
    //! complete definition for those data types is
    //! @code
    //!     eval_if(cond, then, else_) = cond ? then(id) : else(id)
    //!     not_(cond) = static_cast<T>(cond ? false : true)
    //!     while_(pred, state, f) = equivalent to a normal while loop
    //! @endcode
    //!
    //! > #### Rationale for not providing a model for all contextually convertible to bool data types
    //! > The `not_` method can not be implemented in a meaningful way for all
    //! > of those types. For example, one can not cast a pointer type `T*`
    //! > to bool and then back again to `T*` in a meaningful way. With an
    //! > arithmetic type `T`, however, it is possible to cast from `T` to
    //! > bool and then to `T` again; the result will be `0` or `1` depending
    //! > on the truth value. If you want to use a pointer type or something
    //! > similar in a conditional, it is suggested to explicitly convert it
    //! > to bool by using `to<bool>`.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Boolean_algebra_(structure)
    template <typename L>
    struct Logical;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_LOGICAL_HPP

/* logical.hpp
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
*/