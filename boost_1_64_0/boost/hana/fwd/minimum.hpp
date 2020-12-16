/*!
@file
Forward declares `boost::hana::minimum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINIMUM_HPP
#define BOOST_HANA_FWD_MINIMUM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the least element of a non-empty structure with respect to
    //! a `predicate`, by default `less`.
    //! @ingroup group-Foldable
    //!
    //! Given a non-empty structure and an optional binary predicate
    //! (`less` by default), `minimum` returns the least element of
    //! the structure, i.e. an element which is less than or equal to
    //! every other element in the structure, according to the predicate.
    //!
    //! If the structure contains heterogeneous objects, then the predicate
    //! must return a compile-time `Logical`. If no predicate is provided,
    //! the elements in the structure must be Orderable, or compile-time
    //! Orderable if the structure is heterogeneous.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Foldable` `F`, a Logical `Bool` and a predicate
    //! \f$ \mathtt{pred} : T \times T \to Bool \f$, `minimum` has the
    //! following signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{minimum} : F(T) \times (T \times T \to Bool) \to T
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! Orderable. The signature is then
    //! \f[
    //!     \mathtt{minimum} : F(T) \to T
    //! \f]
    //!
    //! @param xs
    //! The structure to find the least element of.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)`, where `x` and `y` are elements
    //! of the structure. `predicate` should be a strict weak ordering on the
    //! elements of the structure and its return value should be a Logical,
    //! or a compile-time Logical if the structure is heterogeneous.
    //!
    //! ### Example
    //! @include example/minimum.cpp
    //!
    //!
    //! Syntactic sugar (`minimum.by`)
    //! ------------------------------
    //! `minimum` can be called in a third way, which provides a nice syntax
    //! especially when working with the `ordering` combinator:
    //! @code
    //!     minimum.by(predicate, xs) == minimum(xs, predicate)
    //!     minimum.by(predicate) == minimum(-, predicate)
    //! @endcode
    //!
    //! where `minimum(-, predicate)` denotes the partial application of
    //! `minimum` to `predicate`.
    //!
    //! ### Example
    //! @include example/minimum_by.cpp
    //!
    //!
    //! Tag dispatching
    //! ---------------
    //! Both the non-predicated version and the predicated versions of
    //! `minimum` are tag-dispatched methods, and hence they can be
    //! customized independently. One reason for this is that some
    //! structures are able to provide a much more efficient implementation
    //! of `minimum` when the `less` predicate is used. Here is how the
    //! different versions of `minimum` are dispatched:
    //! @code
    //!     minimum(xs) -> minimum_impl<tag of xs>::apply(xs)
    //!     minimum(xs, pred) -> minimum_pred_impl<tag of xs>::apply(xs, pred)
    //! @endcode
    //!
    //! Also note that `minimum.by` is not tag-dispatched on its own, since it
    //! is just syntactic sugar for calling the corresponding `minimum`.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minimum = [](auto&& xs[, auto&& predicate]) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct minimum_impl : minimum_impl<T, when<true>> { };

    template <typename T, typename = void>
    struct minimum_pred_impl : minimum_pred_impl<T, when<true>> { };

    struct minimum_t : detail::nested_by<minimum_t> {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr decltype(auto) operator()(Xs&& xs, Predicate&& pred) const;
    };

    constexpr minimum_t minimum{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINIMUM_HPP

/* minimum.hpp
X9Xz71axCL/sh1lnMOhmqrRu0f87BqonMN8ikZLcUj5QbEwc4iLlPUQi4k9MMYj4W0TEcb68fRkTAH2/EiXkXnGHlLuHz/PAnNVMo7ZfaDnzJxs5l7H5CdA9XKK5Th+CBcTFXHmjsV/xT1/WHd98hG+logMLhNpJz14R5sXCWQtl+TxCwBzaWSAr42ArKxOWirWTdIqVjBAXGvKcHlL107DVoDS83WkZg9IRwivDVzvW9CdXYWo4HWiWEu3T3CQPZw4pCW3WPMD4xIo7jnL5ySuJT7yhU2+Y/oNrTj/P6Y9MlVdOX4YSUT6Kix+jG+UZ5BPj9IKqEpH9AYP4O5Cr6hXwRIwDU6Stf/5BC07FTYzxJ81bLrr20mCByTGyeVF2ZtUF9xSZFu2fWNlj0f65VUlEemtXx4Kupi7Qe5EEy1kUjsAlRqAZgSinyqHGs+XheM3ycPlJWPk7ej82dKGkr8TgEmccw37ERAMQJlBYMRdrdTArb9WmMd90duxa9a3p06eHuuLUnfBzYt7ZsSvUFas2mHeGRH+02yxWDVn6bnbHhwqQdUOX2jAc4eYGRTMeIJLuQpFFwTFmhKRyySXCgjBC2WQinoSyqdLSgpMEEUl4Zr77seslZ2CBxCKVuINz2ZbUXvHSdfosSJzeMjImM0a/8N/ewT7UTffq8fHNI2MuDVYBUZfreaqG4cS9CaZqc9BtRzBELEDMmh/neMVCib9KPK8Qv6GialssMH4jJhoVNhElxRU/IiUwWYPjjNXmisfQKXMT2XGS6/yia+GsrQDfVV056FTlUOLK9f3A0ZlX6pmfOjbzgaoNKvrO3eMdYWA0QxDWQysg/DnndnnJw0KNClRyFOEPS469onI+F0gewmMqzygnhxuTiNUPzOWUpeKm6d28OP6nbgIkf3nvPLkekGGXUtE6Sh+PpEBf7kzFhCBkoz3v4g4RvwT9q0AyR0GVL5Ytoi1dqHssIGw6L9BPh+XNgOXLGHwaF8CTsvtw533IFHtlXDPmz0yTOt8CwjC3CPzQs0nSMYm6RrWs2iQcT62GwVFqyvlqK58LhdotcFR9jzINhdf3vmcR/xaYaJHfaa1uQjnVz5U3x8WUqWjIF2ftJHxuu1Pev3BCvAltE2amZ6A195gXY+35Jp5yL63qSbw5NXFEqXrptOV9nT7IxxxPWfp5IpslOHsW1JAvvf4L2onlJqVl+e6418TcFauxJJnbSOAHGFph7UUNEbSzoa2fKAb4aKGiR7YVgwhSmY/wigod5ydp/rOtYMe9xJobBt1CnT3g1WGhRW0JnwGS9953OYPuA5/pi/vDjl1R6uLeGLSsBv509nSMXF+7yzR3qOMFc3DG72OGB28R8KsWzKiAw6WqVMZsv1DH6fT9GmwHmg1qf7n7Q/dGZK8O+UWPO/QJYIF98YVEX2lVhMoEhaI/6A11HvahHXXn0VZcJMpFxL1axqLHX3g0T/1Pyrdv41sPxF2gS28wJwToBWkGWBdDWb0WT4v2X1rVmyWVeZSARBi0eQWTfU0eJoN7H/OXcj68evR8YLVcmhTndpsUmCDMDQVzL1PmSWHNbsKOJCljrjpXOCcQDUdV9HqWzk46G0ne+8Gk48yLZ4+eFyNoXjRiXnjF2jpjXvyA1iu26ke3r5ln1OTRtYet6i71bUjM3ZH0t8yQIWJqwEU/rJa7X8LUkGd7RaHQB5Yxtk4YUN5OaFO7y6qiMNWs5NYPo2K5SFwEXsn3hdE5L3STxfY5htkZJan2TkwSs/Jtu9qim48hYPAEOZNEyuKTOdoE0ePR/X+3mZnaa3bDqnJM1YBASiCvYhVRQGfFpwhq6UERLCJLHy31fyi48Vh+TTc=
*/