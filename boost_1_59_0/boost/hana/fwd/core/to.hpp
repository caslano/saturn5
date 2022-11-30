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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr to_t<To> to{};
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CORE_TO_HPP

/* to.hpp
zENh0bBpSz01Jg89lS+VZunC/S0Ada/3NENvcL8To4DVQjZpWAshc9HtPuvu6UEqIanqgSPiinGAsatL1KcFV+Tg7wfH4dRomjUkAL651XVPE5a5ivJsvRBBqlzUIA51GLK8VTpUTKC5vajg1dQ1OeAR56IHasGPirzAMY0Ey1n5/CxRrEgaJQtLW2NyomkplUEuq2fmUqeBWao1qmvUvG2719cH1nN68l/wzNWeCtjhLZ1nK1Yw1ehOh4ulAiykgapAq0fAOXMi05gxeK3FBwptxYvvE2UrB0GeQJTjwYcOuGb+3ajbFopkIXQfaFlXz+IDxUJwYw8od7wDS5rBSjBXeVclVi1Wzar/jMfuuWiAaUpRCCPG21kjSnAYdRdV/nMnttTmJcRL23Wstqy21djxKVKAi/BzznxCKco3YaIpvvzpkbTI8wUBvNC/kAhC9eqCReoms2LaMKmfhozA8xHgHwlL0dINAsh8sQ7wDD3cts9aZvW0jrLSsvIy87Bz+sN6zPovDadD9WlJbISikUMUdDuJgd4I09262cFLkAHIWke8ZROtQC3OMNHGcbtEB8DKwToCfJk/mE6HVhurwhNIkbtE20XqoG1ts2G5YUvvI766xrrZunTLudP2EnfNcx3s3p21d/XT/GFVVEZ6D2Q6UhY6ikIUFFnSrHQ6y080bLq3hckKjYDXqr9OkyZvKyIGbj6NE/iuhCsKeVJZsKa63rrnyh1h9t+6ipXnBKs8LoAVjlV2+MkTfBCiWsrDFQXpT6xV4g/ZxOFffj+BLa0VmmOS0Za1Fhlq7/GnhJ7D8EQd2cavdZfN51yiyBgjbAoeBe+ir3kQ0gKrm9VtMaKnO+AW75ZAEIbROC1mvAFhfwbe8n8XQkKQqnZG7/EruBWCRZazsRQeJAvNMEQOdNFE62LSMdhc++7EXn+vUQvvNuKjxZziTfVe4nHEAzej6a9a9YNbpQ9iiVROB/CILPDSR3LFtOaC+cSCGaO3iQBPu1wNtLbJUszJY4YKpeyKyW7DfMwcqUbykTs4eP1s7zaNVO4gs5BN7Fpw2h0Pv+MBuWQ6Vy5T1q0buIxOrNEs0ExVjVfMVoJV5MTzH/ER72rERnRR7jBAWtwo7VTt85yakZAPXKiu/hF94gmrHXL0gblwXT6aQ9AKI3pVo6+qr0HoIKzbKgpy5QhARprnd0/DrRavGiNVIgMFt2xhdCJ6lS+A51eTHuUEoa4LBM3x7pN4QlzyqkZTEAwfugF3brj4zt3QC4uK5dPN2jyWHc+vxNJ6goz+LF3vIOy/KQ/NahJ9DTrcJxyhixasYzvzg54UFnbG4rJb+Cw9mPXNLxWixfi4P5YWfomNXqKt07XqhgLwe3bhEuFDxaz3Qh46AY3hwjeJCcWO4M/xiuY9+eXxZDg+YsNoqIKstw7vmg3OW9b6ucD8WWcHNUPrttDmK87/isdjf7887QVpkhMw27Bcn+3Pz5bkx0KBgS7Kp4kH+Ih+/ofuvuZr1AsXn9qKV8enZyvpREI0TiUHcnl1lU3/d73B7s1yIY8S6wD4g/4jTYe6WazCmJ4wzkK5zdR+8+oCJwB7AduG89OF+slt8043ls+hyfXRVdq1yu7eIcIec3e2qdfGd/Hb8yMXJ4XTymH1QO+U/6Luz9AMyfhLSsfd5dFz7FUuxxR/n5UJh5HDGvTpkTkqsEc6GNq4fjFw8M8fs/iUBYW5KNZHzJDQfCNLR/bLXWbi3L8x8Fa44KcL4HBpybeg2n5CbcDZNY+Y+tbViLfY9zgzHFp2+Ir+H/KYL5hT4A5mDmaDeT5oV/o9w1O7OoFoI5pXt8AddRplZ/S79Ne3s/XpoyrYkflroyoekP8ekWkrQlCQDKvsaCsBrutbY3E4XBAZea7r4WKuuEzEl8BELs+pOdHxVPjOEuEKFx3j0t5xYQUaz2bvAN8ci9nYj+2pk76sIDjT0uKQeBOCCaMN/4yqYvP5aDlwR81yqbhUfa+SjfqUqrxGUbH/87iEpHECvi32AaZdrs8ctSks5gxMOYcphrtZLTSsMPTF84Uh6LdJQe5gEYH0Hk0R3IFqH93h7bl49VXBGM/sCEznanbQYy06OaAdHQYRxS0kuWPQmncqiVg5imgfXYxBw6YrRRsJ0EkjtbXrOnbD4rH2H6ASPXi+oxot9yuiGe3lvzeDArqwLpEbNxH/03/5J4bPHmQsUwpUWraTlTf/PhK4FAeNvcZuyWVJTABBIS72Q4C35OmIe3Q6hus2ks1sipQrwZ9RzFHDmvoFNIYMe2vMgLjS/NjoEApbjmNkTrG5uHSddwIsphQn0o5VPqZvER4A2zLbpF9zOibbW3LTIIOXQnqXncvn7LXQMPcg7yAIKdRlhxoBYFQX58YwFHvTc4hApQ+UZHrL4FZSm9JfVhWQZcWPfcanlC1723X96FBS9AMye1slWl+WrPz5JgpM9R2IDIcsFGDXaW4ck5UkyYu9ib/gigIcIiFmc3wMTR/fDtIO8mK4gLPYT25AF2HIUdKR0u59+8wVkzw0WaevfKjcUZyhKgGgFLPUZHNwopyMuyoLl3zoQz8RS1Z3n63JBeHX4pwVRiKcok0rW05hYWYBdczpEOKJ5AldVuhrpBaldgeIewCjQOEF0sqJYM4tS35i3Kzv1VAKEiwZCJkRWYQsdFYa+9v6OAqZazYzNwUPhMwrEpcctseyqvLk+lGbwLy1ay581i07wl1E9UJI9QSteA9ZgqwR0f2VqFKD1BCXvHvBnfBsuK587k1jWasWtOwm+x1PZhAVPIj3WpNWeVae3h2udY+XqwPmoJcERoAkgEzpsdp1/3irXE/sdm9GPnHtiEsMXn86OVBRpjZwn0RjYoyipHlGTIUS727RrRGASQJ3UuwewarqbbaB0zMD5pIqkgPb9fhmIqWp4qZcep79ndHTeEhiqpyPx/3zeGj1RjEmWqtfIpqci1WwmM0tX8Fj5F91PEWeYtl6WDJkwyWOrKyAnnBjbBBSiyYOS85Zl5ybrlX34oePmQ8N7SJMazTXAT5rvH6+MneszosWCu1Whk4bLNXHyi5EFo3s7OzgGdyZnhmCmfCZP9VcRZjVaPql1daZu3hLHclbjhdJOZrpPK0ddtlYWZrZnvS+Fx6SFjOGSWRb+AAzO5w7Ip48Nwb3C289TDXFn1GHRxqqu9zHn2jJj724Cai5k7mBVuksRqaWwRKYfHc7e5m32VqP2lXaBdoJWveHhohrnAS+SLiLfTvDK0SGmEGH14B4DAexry1hGL7EC4ee90hv6Z9YXsmRqHi3X2/zVpQEvtFj5d9BhuxWakM3uAE3FAdsC9W6KnLcIlwcP9yivcD3e2hG15A/nt/eKSmKxUZggz1VyMA968YUAkxeu4zTxriO3HSWYzpgCBjB8EYgmTZOa9MWGlKsOAoxVPjiR+Dxgzz+kd2ReCIGvW1tjOLU2jwEqYudgBti7xCtkR9pGaRz2ojpI7O0w2ZfviMXqABsqaIa500R7rS54CmQTX88kS0QZo9SJpEAxeiRYh7IUnVcLmXYqUZMOD5K2Bwg1Oo0ukUb9wEyNDdRvcbSJM/TFvgECrX1aOtQ2aGGAuAFFKiGHp5p+PXo7DahY7X2fJnDXVgHWuUEXl1IB1qZ7j8fMBhHV11LdkN2sQRyd21XiGpoa7Rr4LQwZDl6ARngP8lfvZPojVjzMIIWmV61b4MYAqMI2l0LRFsvgFZIaia1m7V2nLfOLDY7pCrmvRGkei03gH7yGJwbR3d4jD+3pu5cY8tAwZYOnxfAevqUD9cPxx1h7KIdoh1pCJ9t7ce5kVK7mMQIRmTHQpPo0jynKssxeR5ZrCn1BPkA2nQcv5Shtfgcv1DPlifQKhBW4XqUu9xAfA3ehl5P0ZOS/RecCanJvWHwq+MgMVM1/roE04eRaVEuofqQM5es8ImXFy2GtSzkdRFtTgIYYxaywrwKuSH7vl3qnTV1nRQCQ+ayz3wI+uoH0UuoSdoWUaBLfWjgw5uAP4CLCPBzzOLqH0U0HUc+sBvsxQ6M2jhuPofxvaye7O0jnLVPOEaXhp9IzLLSedZC1nrU0t64b49s12yrOwDCf5N6+d08QisujC0EU2Ej9Tgt8jtwxO8XXUB8HHgDrljHbzi0Tgc93fGMCG/9a+sOZJjXFSedyI/E2mi/34TtUI+IHOJZahmXJrDjIpwZnFaad2KDa4VvdbvzqU9cFcKG5hgdAjDntBn3KsJWzEtUKtar0SzW7PxQcHV8kX4BfaG6tpjnnEeNbyeX+ixxA2uSoJcREtDo5gTK2WBpzbTh69wKdR2L7My3FnhRYykKiOyWWEy9eB6TueJFqpTuMc/YAK+h/oK6siizKgu9hce+f8MxvD2DePQKjrvomfAO/NCxmjKKhKu3yIBPH5lnf+a5UOZ/4xPkcZ6Badto6yQfIaO3jrMqpgK9Jnx5RWAHJFHq3yK5ji/z5l0z+kA/dwgEbztpz02VK4DSzGvwyxDCERUIgkEATQxBW/lievm4jiUQ+QPwYrt1U5BiOlbqKtgNrF0ZwiyMq3MLek0nMhnMzyzD3Cu3FvlHN67VgqzM3zevwO9hO8wLPfqUiA9/nWKBpOpLBgCKWAguFQQgPppcZQwFB609POCwG9wJTDR/LNiPUM41unLJcMnhepToZIzWAohF2FRkq4BOGE7Ytx8wJTLDs96P7N5lb47onsJbuVaB4S6LewMS7Kn6VCwqidV+16hMwioRYJ5oHkn5Bt9dv7EDjqeJDDzM340145BU3Cnx8fya58+Qxn60mheRu3Eh5IbQCNyObz76Q7JNxjXMEKgB1R8QTEx90CBMTtn+vhBZ2djKciz1uhtwe8Z/bB1JoFxio2dpBtzZlDP5iCthmmMyWXDmTwoC1o4+NIcRvSg/BLhpCsbHpu92mR5D2WQ5t2rn9TMHQrzwvbdp46hBAtRvrWneizgSEkQqlWfXfQd+oRT1mRzIINywnuz4PLwI5vOLIn1Chwj8d4rAHmAPJW4hYiVi+WLFYt2jprh87o8eUYoqQog8z9lBX6zAGpC4aDwec1gJc1gm0mt2y8Y3h9M5CgNeaFcvL4cePcftYR4no0ORTua9P6O4C+aaPP4nnTkeyAe1j5sjep+AxEYgOn2LC4stcD23Oe8cCUEw232Kp+qDJx4enhPckWEVZ1jcgWfzj89USnHqMTHlOfWKEtZqjgv5IsHhsSEnzrOZOa08N57W/kMClwQWvANZGPkKV8lRCxc5iLtrJ08x8G68zx5QUH0Ry9u7b0uWJStaaLtvrakhFgaCRzTajRpAP4ZvSBYQtxqHzdJHZNqFwV+hLdx7xYs+quHCeaL0K5atK4B0jaEWY5/EC829eeyRuqOhyXH9iGdMPVp0pnRytfweJSqHx5uhavMvNrXktVq1Bh2i66o65Ycqf1FHUr2L+KVz2BIROx2i4o+R4cce3oekjp5aW0F7BI6emle0NUzw8oadglXpDJuFD4Ad1qneA+j7/cMSWgcRd7tXPcH6Tbz9Xixuop1qT8w23m0LHj87t8swnz8E+jYGNvy3adxTc9r+RNttI96Q23Z8zzsD7TmZBXXKptS90D738L/AP1pAfCjiUmDD3eB5HX9QvzC82N+3H3XOvcDstHqz3btv93ry3eM+mShZPJRuu6W4HUCKS23/vEqL1fJE7nYE5PR7Aa6YRs968nYEcdJHlAPzanq56J331Y6VrLOWYOKpPu5pKu5q5VoYiDPwynak5J1NPiG8v77RT6huUHW58+7x2vNy8B6Nga+PMV5IlbAfSa6FfLoj3J49vqHzeIYY3xQNZPK9Wdy387544b7NcSSfhKn3/jG9Ytp7YMt44mC+aE1j2RnIt24LH52blpYAqSpQHonM4cCW20n81v7OBZWGSkPaRcWH8MIvT2qS7En5REmCd2ItYz09yBsVQPrk6MnvCe6Z7tl5P3td+/jzYfzO85J7jXegew7kVejdWJLyRickNIMEsKOwQ5l1Zltic3ONBLQDu0One1eMbPigeZlSdtd5k9sD3OP7Nn2vedo6YgsVsAholHN9V3wOc6nf/8U21OiT2wDQ24i2i8u0OI8tuDQ7N4sowAwn4FQP/pp9iyTf5Bh2xP0VVTLr0asG6g36AdjL3dsh3xPluXZDTfXl8NguWPy89+786n38YqZW/heOKP8QDu994mYF0M3aCUA7anBmTmLstc2ryDfJncJJmqWkKG3d0h/zG+rL+ZPm8+oTGDTJ26HdYwDt1fKtNxKgDGoeMIMdLh+1csjJ+54yZVOs8Q/LmvYmOt4r11tnvkkoBlfFseLnSDGSQ9QwPyB90UBL/ggoxu3tR++98cy8E6dq38PPv94V3zFfoJ4nsR++ssMqoyy7ZDM0fbB26wcsxx09MByaZuUxKDXEOo4+5j5ZECAVkKpSc8IYDXEqjzMN4GemEMwJ8PV7HNNBY0TNwXiCN3E87I+mbMJpvzR+m93Nvid/eX/XN0xADEBTIEqgcyDeYvKUO/WmQJA7Wv8y1DlM/iPfEyIlTcL9P15Ydmx5dHpA/a/AqCa6aQFzy1ZBNflS789wtwK7+30oQ1g4ZvYHAPKmf4egNlHN8E5xT8E0ryCyEn6QBhSit/V2HvnNXMOWLVLo6Ogp6rhuF/vo6rcdgWdBVf6wFgrL5RG2ErMsOTCmZ34gbx3CVI5bjtYzFw8wcKhUB0rrLxQ9ozYMd/WN+luMa4XD0oxNnbFYJQGMYOZgPhxJpkj+k2gZLGfqGo0MRYmAQLlqUQ+ARRUoeFyKUxP/JFGQaCjygyNuQQT0vOatopg13nES9VubshjGUK0Ymaf595KC3e1XpHgPcYW/FjLiMJJJ9SZPmApd3xBBO+f1OZdUVeCgG52HIbAuMCLQIkBLCM/MdgoDKcw6WLY8GugF/2gzZ4J4vQh/uB6Q9uyLTiz2ODQxLz9i000NABIeQIh8H28/9uf90NDbaHmFZr4C4Yj9mpydHnInHjcpMjIdqiy3w15UX04XAtwC9lzwpYdIG5VEAP/UVyCK2V7Kwzoz8JpJFJ0xPOfKIyKmxv3IritgJfg0OAucA+++dw4p/zq/VJBJaHIgJeQsxBvhWXvVbPXh1nyP8/OsfyPQOTA6gCZgK1Au2Krw9JGw/qojMy+NJk40MBYkl5/ZA2F+NkUAmyt3UhkEGc5jFlKWz/kV+Udpv7xLkaW0Q9bb8by/vNQLPstzwk18bwSKFsaGm+VhKZNa8NsSgA4MeRPj08/ODXQH/DtmeX8NOfSETy68gb8/NjC3HrMnbf32bQmKLvRIST5P8SZnvd/Dy8HCkmXcHRr3WWBt2XEC17oWhUrLkPk6+54dJZj4dltRQNzrWoTxBbfStc0K2CrnaWWpQtaXV4U8pLSpneP13FEXTn+jAVgx5ONllT5riY+gMd3r1n8AK6gLt+E5WfZbNmPhjM3wa6xKu9JhLyQtSC1o1WDmjXA4Thiyi3yeWawPCiH4NSQo6BBR8tCHOPLZYN0ojJkYF0m8t7GB4ZlheFGnS63SRlxbHKujSOqfxw6CA4r3pV5qHJYDlRHh0l48SNAmhLwexHMUdzwb2WF3YBPaXfRdH/vM9px5vpTQSpBG/IZXTX6jsuFf
*/