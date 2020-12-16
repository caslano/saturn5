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
s18FW/Uhi1y6PmvDMx+iJODj33DJ4WBryryBodsskh9I7zs5DxsrcoL1B4Ot1nk4m3HzNXL3rDMf3w6UMDlw0lxSKBHH9rjcovUJkHrlxdrCY9vjYuGx2hpfCHIlfnOrWXpB9wZfYkCBO/n60qXZmnsIl3r3lfo5H/KwRmW2Qx5MABI4nyWyQ/mh3DYK3/luEPDM9baaQkAJVdHH6CqfteF4/urrNPvmHWn2j7en2RfhacHfS3jfhr8vEWcFgRos4hc9OppsSfmv8drT/o+PelnpqNd7NKFPieXn7zM/t+r7h5HAxfBHoBbr8pZXHZOvyVueyCqLkRYo3IerrDytNvAyM7d5yTg5SnVRCvJb/zom1SUWSuuGJ88hGjXd+2i85PRdOHRdDt8qMSX2fFs2cUViTwVCmVDoDaHCiMhS35kVL0aFn6D6VHTT1gU0rHEm6yK2OM+B7MTHZRf2I3WVW0hWPS2aZDVVpraL1Lqk9bRXzZwhWYVlCIsgGAqYNeBZuJrbpuJSYDc0pn3caOtJg0X7lKnnnavfjnA16BqyilkbkkpjtNy7pslyzRwFHCtg2mCrIXshDxp82OXaDcgxyF6tZQIOp/DyWkZckgBtIaCdH4OhV2wNPD1IIhku1JF8EUvxKI4s2tikiwyFiSMwng5NsoYqG5iN/oEQAG30IQsffjRWB3YDgCnNECk0cDHI/3GqwDEO1hkzEmA5L2dYdC9RMVKOZmqVZ2xzy6S8eLb4TlDU2aN0nWIuDjFMlRuEadhNjGA90WIKvqYdgH7lbFZPkIZBaYyRIglh+SZ5ljjht3MKY338tP2f8IvaH9z943h5cJMmD1qj8mDgEjjouoqb0u0hw1b1N0NjmMn+MyDid1GXxn5L7ycdDXbGLPcYDUoBzaNmeDVS86jDzhev6tV/tEAFfA4H7aFg63fe79fOP0LTold0hY+Ut6042CA8OZCJkiXYarb9ogFzO1AVTgCnYq4jNyngdH2hg50uR3w69CVzMvc2plZYxcXenfEeSJvMsxFlYscdZWrNBZISz/C9aonbvn9UbKF1G69toSEvMnrU58q5EGDQh5ZUuB/DHkgJNqYGP20Nj7SIVOGRreKFCw+gG2h+D5zJXNztKhM6ZK96kK3QspW1dGPBOtwQLnL5BsUny5/VZrL2oKaVdAiqMrmNZMehlT7xX923hm5x5/+HpsSHXzbGh29PCLcmhAuS4sN5CfGDk+PDkxLKn5KQflMCPi9E4v0VvJMAb3pC+bMT8hea4sMHE9LPSIi/KyH8i4T0sxLKX55Qn7UJ6a2p8eGdCfV5PaG8PyTgf485PuxLCG9ICJsT8DMkxN+fEF+fgP/AhPS1Cfg6EtJbEvDN5v0fd6w8kkXCOA/7AuIxA1kmcVGEOmqGZo8Mlz01L9MCMEiTUrDe4txpW/w0Xllb1jBZitTZHK4fJhUHxlCqUmIOjTXz91MK5ffRhlAJ/jWHSix1rZAH8hmuaaeY0YM0o3vEIf2PB2hzXzCbhbpn8vSpuIjKf9pu1Ob0S4bFp/wQywMSCoKvWILNFjVnspZRCfKUP4vVPh7oeB6j9GXqxMs1bVHMt1nD9dJeMVBpPFebL8JUXXGZvkYAQ9RaphxNY2oSIkEWJtc7ypiTNGplMWpsrDNFlhX91ueSOMFgglYYBEa9SkZZZqBQi7WeU8qig+qXkgMEJyUGg0wNAw982/WTsoEDjE074L8LO0L/OfccaPodt/oq5mkF/U/EojrxYqu5HvWlBWi2bfEMkvg8fgtc5V/JnU6NFtxyIFifDR1Dr0Gy027tScTxDOkgw39hTZ7qcEqrjKt7657yvhUCaq472KSquydJ2bCG1Yo=
*/