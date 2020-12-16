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
fBEJvahDZXHIB7nBKxYW4zQW79whsXwFlPVxylywhQ7AOB+OsNCOc+ud/Q0ytVdfuIq6CNF+NZoqsMM03tdA5WlaAYV9QMknOhFQylFVwk/BbBrhTZkYVZ0iMnmLmo90PlQ7sxFNZSms7sji1wBe38cr6fn9EU9WJcXTRGEFpFQ9V4+hep+rbnJOEdkN/xifpHhhfo1kuSAj8SFP0C3xIX/FdwDvCMH3lJI/LOiQLBzVTG43DfHCrdIY94sAPz/r4UxiBvOPC2TwVwf6GnhcnoO/nPTlS+wpx3sGvbsSe3x9n8H92joP9wGa3wG8TBTaOK4IydEtaMsFHUwnikOwAaymZOzGMURQPI+eRE34FrmzGDVkjUaE5BR39VR0HUsVSDTSaMuhCgNQkeeSMpzJ0AinhiDBENppNlBRh6FHwNy+Z2WIxl4nR5teF7fJXn9bTr18Qo+1H3u0TftrlfZe3ablQHIdtIHyq4Jw5gvUtRX1QuqjdZQMkSVAdmE+MsytH+Ogq7HUE3X+DY3jNnBrsOEp9wZ2Ml2OS8GXN92azqFesgfo2dhY8rQn4adL/xUY5Rlbd+8uKXd5Vu+j0TaqLZa9gKVxvA4Piat+KgndtoId6NvJonCNuqBeshoJhU7IBm4MpDWabEGlIowg4EGG30iTAkc0u1mN8hOdKiiO/aleN+T694GxU0dGRU9EyosG+WaG+Tny9pyzIShuWdVqrTF2pVB+71rOY+yxYeIXz8lQ80lNJqhJM2g0Zze76N3EG9kpwliv9sJue2KCVAAP1BdenSb7LDfjS9rxDHltyJOYIRNo5HsGlKVRTiScNaFkz4Je+Miry0SjX0J6ZUPI6np+c3pdV3gWpTFyLDpNozWc9R2tAXsMDVjSu08Ol7LHv+zryEMAsTx+YUqVhm58OtH/ijp/fuIpmgGV9f4Eleogk/bQJPMkLlVjxwSSTdV0G/bktj2ddwt6a6KtjYJNXfch6Zltkzoo6ZwWST8g49jTraSjddLXb0bSGS2Sbqak57YYFqN+IjtjOujaQh0DmxDUOEFRdH/qRrc05X5h24LOvZmnE0B4m2Z9y1O4qN75k4KX64hUyHvyn6GXKjHuqtE8lNI/pIH6rK4QhrHMzpq+0A2QsHilztLNid+pIyte2Y42Ltkz/10TkKiIMdT2iQYnQS55Y/4mIkwlO+PdjHWpZmuagiYPixUKIlZw6tlJCCzYRovf09w9wOgrXjXjwGvrkM/q8E5LxZwNTOBAT4uYngahK5Evtl1i3UnsCECJ0lGO2gsQwwsb/q8Mi6a1lufIj9CRKKGQVyLzKdNdjHqWPFVb4hkAboIycVY4p7pnb7LwnrCYu9a6HnAn8hItLDfdRbqJSnbOf9YEboTvWFBQSTknS8q5iPogGqLr0GHR+WELiWe/YSRymGUd8hwNXc/aUodS2J0FeLPBUWRHI5GwOCqF+5GMOym0FM/FYF79rpx7AaJ7Q6AqifnXiNYPUk/O4fpkNBa7vZ7VrDyS5nnc7SDteJ4DW83PtooBu98B3HGfAWhZydb40Sg0wO2GtYp+IiKJDBX+S4wkSlewBTCuoiW8zMx6aR/ojx/tZCJ1RARXWF2x9Fvq0+ZDGRzHz41E8DFP9F1jNehUggmEqVI0esZTA1LVLhmrGjDR5ODWqfsQdQd6vYqn55TBGViE0XtIUq7mbtRqCJkdFj+/x0Lhm72AgQ5gU1hNU8h6PFbt1rPl+Jvk4lP4f2Py///7d//bnM/7nzukfltRJMr7HD7EYzsl3lDdYmati8TZdyGRaP4sqS5VEQORxRZm8xvCIXHL45oEl7IdtYHpqe3Fr+XMOOxnZEaCLRM1V+NlAiQ=
*/