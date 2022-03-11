/*!
@file
Forward declares `boost::hana::Constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_CONSTANT_HPP
#define BOOST_HANA_FWD_CONCEPT_CONSTANT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Constant Constant
    //! The `Constant` concept represents data that can be manipulated at
    //! compile-time.
    //!
    //! At its core, `Constant` is simply a generalization of the principle
    //! behind `std::integral_constant` to all types that can be constructed
    //! at compile-time, i.e. to all types with a `constexpr` constructor
    //! (also called [Literal types][1]). More specifically, a `Constant` is
    //! an object from which a `constexpr` value may be obtained (through the
    //! `value` method) regardless of the `constexpr`ness of the object itself.
    //!
    //! All `Constant`s must be somewhat equivalent, in the following sense.
    //! Let `C(T)` and `D(U)` denote the tags of `Constant`s holding objects
    //! of type `T` and `U`, respectively. Then, an object with tag `D(U)`
    //! must be convertible to an object with tag `C(T)` whenever `U` is
    //! convertible to `T`, as determined by `is_convertible`. The
    //! interpretation here is that a `Constant` is just a box holding
    //! an object of some type, and it should be possible to swap between
    //! boxes whenever the objects inside the boxes can be swapped.
    //!
    //! Because of this last requirement, one could be tempted to think that
    //! specialized "boxes" like `std::integral_constant` are prevented from
    //! being `Constant`s because they are not able to hold objects of any
    //! type `T` (`std::integral_constant` may only hold integral types).
    //! This is false; the requirement should be interpreted as saying that
    //! whenever `C(T)` is _meaningful_ (e.g. only when `T` is integral for
    //! `std::integral_constant`) _and_ there exists a conversion from `U`
    //! to `T`, then a conversion from `D(U)` to `C(T)` should also exist.
    //! The precise requirements for being a `Constant` are embodied in the
    //! following laws.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `value` and `to`, satisfying the laws below.
    //!
    //!
    //! Laws
    //! ----
    //! Let `c` be an object of with tag `C`, which represents a `Constant`
    //! holding an object with tag `T`. The first law ensures that the value
    //! of the wrapped object is always a constant expression by requiring
    //! the following to be well-formed:
    //! @code
    //!     constexpr auto x = hana::value<decltype(c)>();
    //! @endcode
    //!
    //! This means that the `value` function must return an object that can
    //! be constructed at compile-time. It is important to note how `value`
    //! only receives the type of the object and not the object itself.
    //! This is the core of the `Constant` concept; it means that the only
    //! information required to implement `value` must be stored in the _type_
    //! of its argument, and hence be available statically.
    //!
    //! The second law that must be satisfied ensures that `Constant`s are
    //! basically dumb boxes, which makes it possible to provide models for
    //! many concepts without much work from the user. The law simply asks
    //! for the following expression to be valid:
    //! @code
    //!     to<C>(i)
    //! @endcode
    //! where, `i` is an _arbitrary_ `Constant` holding an internal value
    //! with a tag that can be converted to `T`, as determined by the
    //! `hana::is_convertible` metafunction. In other words, whenever `U` is
    //! convertible to `T`, a `Constant` holding a `U` is convertible to
    //! a `Constant` holding a `T`, if such a `Constant` can be created.
    //!
    //! Finally, the tag `C` must provide a nested `value_type` alias to `T`,
    //! which allows us to query the tag of the inner value held by objects
    //! with tag `C`. In other words, the following must be true for any
    //! object `c` with tag `C`:
    //! @code
    //!     std::is_same<
    //!         C::value_type,
    //!         tag_of<decltype(hana::value(c))>::type
    //!     >::value
    //! @endcode
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! In certain cases, a `Constant` can automatically be made a model of
    //! another concept. In particular, if a `Constant` `C` is holding an
    //! object of tag `T`, and if `T` models a concept `X`, then `C` may
    //! in most cases model `X` by simply performing whatever operation is
    //! required on its underlying value, and then wrapping the result back
    //! in a `C`.
    //!
    //! More specifically, if a `Constant` `C` has an underlying value
    //! (`C::value_type`) which is a model of `Comparable`, `Orderable`,
    //! `Logical`, or `Monoid` up to `EuclideanRing`, then `C` must also
    //! be a model of those concepts. In other words, when `C::value_type`
    //! models one of the listed concepts, `C` itself must also model that
    //! concept. However, note that free models are provided for all of
    //! those concepts, so no additional work must be done.
    //!
    //! While it would be possible in theory to provide models for concepts
    //! like `Foldable` too, only a couple of concepts are useful to have as
    //! `Constant` in practice. Providing free models for the concepts listed
    //! above is useful because it allows various types of integral constants
    //! (`std::integral_constant`, `mpl::integral_c`, etc...) to easily have
    //! models for them just by defining the `Constant` concept.
    //!
    //! @remark
    //! An interesting observation is that `Constant` is actually the
    //! canonical embedding of the subcategory of `constexpr` things
    //! into the Hana category, which contains everything in this library.
    //! Hence, whatever is true in that subcategory is also true here, via
    //! this functor. This is why we can provide models of any concept that
    //! works on `constexpr` things for Constants, by simply passing them
    //! through that embedding.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Provided conversion to the tag of the underlying value
    //! ------------------------------------------------------
    //! Any `Constant` `c` holding an underlying value of tag `T` is
    //! convertible to any tag `U` such that `T` is convertible to `U`.
    //! Specifically, the conversion is equivalent to
    //! @code
    //!     to<U>(c) == to<U>(value<decltype(c)>())
    //! @endcode
    //!
    //! Also, those conversions are marked as an embedding whenever the
    //! conversion of underlying types is an embedding. This is to allow
    //! Constants to inter-operate with `constexpr` objects easily:
    //! @code
    //!     plus(int_c<1>, 1) == 2
    //! @endcode
    //!
    //! Strictly speaking, __this is sometimes a violation__ of what it means
    //! to be an embedding. Indeed, while there exists an embedding from any
    //! Constant to a `constexpr` object (since Constant is just the canonical
    //! inclusion), there is no embedding from a Constant to a runtime
    //! object since we would lose the ability to define the `value` method
    //! (the `constexpr`ness of the object would have been lost). Since there
    //! is no way to distinguish `constexpr` and non-`constexpr` objects based
    //! on their type, Hana has no way to know whether the conversion is to a
    //! `constexpr` object of not. In other words, the `to` method has no way
    //! to differentiate between
    //! @code
    //!     constexpr int i = hana::to<int>(int_c<1>);
    //! @endcode
    //! which is an embedding, and
    //! @code
    //!     int i = hana::to<int>(int_c<1>);
    //! @endcode
    //!
    //! which isn't. To be on the safer side, we could mark the conversion
    //! as not-an-embedding. However, if e.g. the conversion from
    //! `integral_constant_tag<int>` to `int` was not marked as an embedding,
    //! we would have to write `plus(to<int>(int_c<1>), 1)` instead of just
    //! `plus(int_c<1>, 1)`, which is cumbersome. Hence, the conversion is
    //! marked as an embedding, but this also means that code like
    //! @code
    //!     int i = 1;
    //!     plus(int_c<1>, i);
    //! @endcode
    //! will be considered valid, which implicitly loses the fact that
    //! `int_c<1>` is a Constant, and hence does not follow the usual rules
    //! for cross-type operations in Hana.
    //!
    //!
    //! Provided common data type
    //! -------------------------
    //! Because of the requirement that `Constant`s be interchangeable when
    //! their contents are compatible, two `Constant`s `A` and `B` will have
    //! a common data type whenever `A::value_type` and `B::value_type` have
    //! one. Their common data type is an unspecified `Constant` `C` such
    //! that `C::value_type` is exactly `common_t<A::value_type, B::value_type>`.
    //! A specialization of the `common` metafunction is provided for
    //! `Constant`s to reflect this.
    //!
    //! In the same vein, a common data type is also provided from any
    //! constant `A` to a type `T` such that `A::value_type` and `T` share
    //! a common type. The common type between `A` and `T` is obviously the
    //! common type between `A::value_type` and `T`. As explained above in
    //! the section on conversions, this is sometimes a violation of the
    //! definition of a common type, because there must be an embedding
    //! to the common type, which is not always the case. For the same
    //! reasons as explained above, this common type is still provided.
    //!
    //!
    //! [1]: http://en.cppreference.com/w/cpp/named_req/LiteralType
    template <typename C>
    struct Constant;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_CONSTANT_HPP

/* constant.hpp
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
*/