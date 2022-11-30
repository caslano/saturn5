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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_LOGICAL_HPP

/* logical.hpp
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
*/