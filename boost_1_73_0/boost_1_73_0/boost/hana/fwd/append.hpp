/*!
@file
Forward declares `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_APPEND_HPP
#define BOOST_HANA_FWD_APPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Append an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given an element `x` and a monadic structure `xs`, `append` returns a
    //! new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the right) with `xs`.
    //! In other words,
    //! @code
    //!     append(xs, x) == concat(xs, lift<Xs>(x))
    //! @endcode
    //! where `Xs` is the tag of `xs`. For sequences, this has the intuitive
    //! behavior of simply appending an element to the end of the sequence,
    //! hence the name.
    //!
    //! > #### Rationale for not calling this `push_back`
    //! > See the rationale for using `prepend` instead of `push_front`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{append} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the left of the element.
    //!
    //! @param x
    //! An element to combine to the right of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/append.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto append = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct append_impl : append_impl<M, when<true>> { };

    struct append_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr append_t append{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_APPEND_HPP

/* append.hpp
4ssjTGu4eDoTTO9U+wTbhYUvrXl3DE+j07O3g9E4Oh8M347fOSmcNeBtLwJmHnsn3g2mjh5gI2Brrk/1m1enpVto1kSrxh/ZMECNbC01AVKVUuRCZVHre4HrxGw0e1uJ7YnHWgo3InlsBTp8VqU2QnU+rOs7+kLmpqPPlSs8N3F581zoKfhv5edst6fnlpPgklTeNNf1+dUnoszRvpjSjTf4DhRhr/wyU9N6b56SoliLU5PwWZtIQzuiauvVz5poVlnyt5Pi7/R/FQNxlYWvqOrEUB4cusbWFtfZvQSNphExTZ80QcsUMJgdQNeDsM0ycrxCXZHfMGIdFbbbN9rTdJftPvx7ajIaKeqQaVQ93/CwwT7Q9FgdUzJhDJ9Anetcdwpv7FHv/ciLBCiIU8cGI2itzkgoHZPZ6QWn0hhTRfFRHYA0ph1rTpZ0oPbv6tUrrvNg+l1rVk8iyvZhgbN8foYrjHu6U18obRYLr27PWWWcU5PNGNH7vnnkHGkyStwfE1Az2bVUOR83tZAcGIF3UlWZgU1dpAnYaBYYhQoMeb6QLgPBYorXDYFDtz8I/ScO2U1v1gjLblPGeMroS/W1hIIhbR3bkBLzZ6b/zJnXXkqVew0M/G++BArn+bKmSIDKYmI9tvmyzZoxE4vO
*/