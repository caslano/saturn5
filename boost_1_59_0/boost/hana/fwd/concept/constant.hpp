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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_CONSTANT_HPP

/* constant.hpp
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
*/