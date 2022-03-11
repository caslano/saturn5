/*!
@file
Forward declares `boost::hana::to` and related utilities.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_TO_HPP
#define BOOST_HANA_FWD_CORE_TO_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Converts an object from one data type to another.
    //!
    //! `to` is a natural extension of the `static_cast` language construct to
    //! data types. Given a destination data type `To` and an object `x`, `to`
    //! creates a new object of data type `To` from `x`. Note, however, that
    //! `to` is not required to actually create a new object, and may return a
    //! reference to the original object (for example when trying to convert
    //! an object to its own data type).
    //!
    //! As a natural extension to `static_cast`, `to` provides a default
    //! behavior. For the purpose of what follows, let `To` be the destination
    //! data type and `From` be the data type of `x`, i.e. the source data type.
    //! Then, `to` has the following default behavior:
    //! 1. If the `To` and `From` data types are the same, then the object
    //!    is forwarded as-is.
    //! 2. Otherwise, if `From` is convertible to `To` using `static_cast`,
    //!    `x` is converted to `From` using `static_cast`.
    //! 3. Otherwise, calling `to<From>(x)` triggers a static assertion.
    //!
    //! However, `to` is a tag-dispatched function, which means that `to_impl`
    //! may be specialized in the `boost::hana` namespace to customize its
    //! behavior for arbitrary data types. Also note that `to` is tag-dispatched
    //! using both the `To` and the `From` data types, which means that `to_impl`
    //! is called as `to_impl<To, From>::%apply(x)`. Also note that some
    //! concepts provide conversions to or from their models. For example,
    //! any `Foldable` may be converted into a `Sequence`. This is achieved
    //! by specializing `to_impl<To, From>` whenever `To` is a `Sequence` and
    //! `From` is a `Foldable`. When such conversions are provided, they are
    //! documented in the source concept, in this case `Foldable`.
    //!
    //!
    //! Hana-convertibility
    //! -------------------
    //! When an object `x` of data type `From` can be converted to a data type
    //! `To` using `to`, we say that `x` is Hana-convertible to the data type
    //! `To`. We also say that there is a Hana-conversion from `From` to `To`.
    //! This bit of terminology is useful to avoid mistaking the various kinds
    //! of conversions C++ offers.
    //!
    //!
    //! Embeddings
    //! ----------
    //! As you might have seen by now, Hana uses algebraic and category-
    //! theoretical structures all around the place to help specify concepts
    //! in a rigorous way. These structures always have operations associated
    //! to them, which is why they are useful. The notion of embedding captures
    //! the idea of injecting a smaller structure into a larger one while
    //! preserving the operations of the structure. In other words, an
    //! embedding is an injective mapping that is also structure-preserving.
    //! Exactly what it means for a structure's operations to be preserved is
    //! left to explain by the documentation of each structure. For example,
    //! when we talk of a Monoid-embedding from a Monoid `A` to a Monoid `B`,
    //! we simply mean an injective transformation that preserves the identity
    //! and the associative operation, as documented in `Monoid`.
    //!
    //! But what does this have to do with the `to` function? Quite simply,
    //! the `to` function is a mapping between two data types, which will
    //! sometimes be some kind of structure, and it is sometimes useful to
    //! know whether such a mapping is well-behaved, i.e. lossless and
    //! structure preserving. The criterion for this conversion to be well-
    //! behaved is exactly that of being an embedding. To specify that a
    //! conversion is an embedding, simply use the `embedding` type as a
    //! base class of the corresponding `to_impl` specialization. Obviously,
    //! you should make sure the conversion is really an embedding, unless
    //! you want to shoot yourself in the foot.
    //!
    //!
    //! @tparam To
    //! The data type to which `x` should be converted.
    //!
    //! @param x
    //! The object to convert to the given data type.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/convert/to.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename To>
    constexpr auto to = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename To, typename From, typename = void>
    struct to_impl;

    template <typename To>
    struct to_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    template <typename To>
    constexpr to_t<To> to{};
#endif

    //! @ingroup group-core
    //! Returns whether there is a Hana-conversion from a data type to another.
    //!
    //! Specifically, `is_convertible<From, To>` is whether calling `to<To>`
    //! with an object of data type `From` would _not_ trigger a static
    //! assertion.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/convert/is_convertible.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename From, typename To>
    struct is_convertible { see documentation };
#else
    template <typename From, typename To, typename = void>
    struct is_convertible;
#endif

    //! @ingroup group-core
    //! Marks a conversion between data types as being an embedding.
    //!
    //! To mark a conversion between two data types `To` and `From` as
    //! an embedding, simply use `embedding<true>` (or simply `embedding<>`)
    //! as a base class of the corresponding `to_impl` specialization.
    //! If a `to_impl` specialization does not inherit `embedding<true>`
    //! or `embedding<>`, then it is not considered an embedding by the
    //! `is_embedded` metafunction.
    //!
    //! > #### Tip
    //! > The boolean template parameter is useful for marking a conversion
    //! > as an embedding only when some condition is satisfied.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/convert/embedding.cpp
    template <bool = true>
    struct embedding { };

    //! @ingroup group-core
    //! Returns whether a data type can be embedded into another data type.
    //!
    //! Given two data types `To` and `From`, `is_embedded<From, To>` returns
    //! whether `From` is convertible to `To`, and whether that conversion is
    //! also an embedding, as signaled by the `embedding` type.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/convert/is_embedded.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename From, typename To>
    struct is_embedded { see documentation };
#else
    template <typename From, typename To, typename = void>
    struct is_embedded;
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_TO_HPP

/* to.hpp
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
*/