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
62m4OMIsNAfD5kwnSwswlh5lgcPyIn1uU6X3AxA9llsASmJ9o2Jfdz0u8jhRVLov6tRRg+sZEn/upLkVaw5Pg+Z0R1jklDGQZHe398G/jxqqXN+ys2ldcwovP13ClU3rGy61uPkwhClZNzICHu9MypLW+ralVJqD3sxPt7intJ3rm1OsUlmXqKw1Misy7j/9+eNl+rPGy/Qz2WKMxu+A5en1zplc6BTLS1uvd67kQpc4u9S23rmJSYuW2tY7b12Ft13rHfEiMdroKFG/uEfuEfdvUtyy/1si5zt5psTVaBdf/djo0vNbEk3ayLDRQt4380kkiXhJNHTTcEv49zzg2dYfH8Qn1vpju2Scg/yFKr9LnJbKv75lfi9kGvb1ax6JKPCcpfK6xWHDrbMA+ry5EFh75AXuPPNyBvNyfChdQTZXaJY4gpRRyRK7zbFuLuBlCcTDTm7HelNEuJ/nH02Ev/NP37/xklQiivXox0TAFEuA2+RgOrqL3lkshfiGPOSQyivfGCA7W7jrk03KPvOdKV0lrpTcciFZgPWBdDJXq2Tx+erGyZlWEneLJM0TeI8Q5973YkAHxb3FepQOQ1xAhkPl6SdWeD/ubQ53B8UKK1yKMkLi8S5Mov5B120237h9P/cxlhVJPkZ6/McUCSpfROLub3YpiwNOIop0i50ZdLeWoItYJt9Gp9jvWE/NCbwFMMvIRHov2kfjtmuVqCthCsHclHRrYQFojd+7I+z46f8Iv+yJu+34RaKEm478PY2EPQgnsQx8usD+f3PvqBhcJU92vaIsR8pJ0OIxR7BKSh6lBoS4Aht7Og8+cQQvrmRN7O9YFqS+8gDAIPKg9QTNMi33xGuAj0Ol/NcF1LMjQW2GO4DQoM4k7u9luZ+8cCBfvTZ2vs8cRWdpgDY8RKsVsh1Q6h7cxE7G4L/cifx3BngkSRN3v8+gDz9Jso1HNagI1/zPA2CL9tdtwe9iFcMcBZ4pJr8Zd1lpL9Zpnz1SofIP1jpleb59/H7b6nt56ruVf4Sexhsaz2Qt/EswL+423rQqL37Rn4MOtIS0XidiDhqX9p84AgPnO1X3Ymlt0n/lPEB6mjgJkSE5rYTIjI9KCEc8U04XqhwPpfhhRh+H7oMA7hsWS7OSZDLagehM2WxQcGVF2Uh8Ij0DNRWxkTJPDkSsliV/WEEuVV3fPDQWkAbAp17SMS3C44hF36MKeVYoTiM2TKafY3SS3f9crh6JbPG/MY1MQ25O/+HXy2PplgPBbPGpQ7dcK3rjItXUBM8uN3Ga5gk+M0jUZ3LiwgB0Nla9DIew03WL8eVUo4vEvJvGnBB3N6YF5HpMFLnbpOQFaNwrKzRbOkaOBmOKwxr/GsyzgzUYY5JVznpbOXcMbrfOsf7T/jnSufeVaZmtLfNrQrulpm/sdIlT3HDLIodbRUbQU3qsJEbIjvei4/0xQ3W8zpOu86CTAxGiJpKWVPstWuIXjw/UxsSOiJ2n5lIUB9ux81tB28QHJgGC1q7T7rZ/FoPlo7tCJ5vyGGE4qD1ZyMRD5H5FK5YXDQU63i92dKuReczh+jLhtAZsLrOQLjsQd8L3xOuR1GwYOCI1G/pbs0HD2HGYbhQAIUcW0jGlGLasYxryNBEPFxurWljcpoT65QE00JDY+FbAbgSwWLlqtUMP0Q0EyKhhzYnURc29FFOw7LDYSRYBeycfGStVRtGHu0BmNMsDywN76P9ZA5bRY8KAsuauHm+Wp1uax1vh9XQrIwiwcvz1LgJszetsMSffZoR25g/nN54/+Hj2OWjQhrAbnOLzrKK5CEHAqYmLMVEnEy9Fu0eDjF9EjHEfkP2bX+YrjnbpUBV+z+kUfrU=
*/