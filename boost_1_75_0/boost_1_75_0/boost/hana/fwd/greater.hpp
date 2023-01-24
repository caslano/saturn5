/*!
@file
Forward declares `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_HPP
#define BOOST_HANA_FWD_GREATER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_impl : greater_impl<T, U, when<true>> { };

    struct greater_t : detail::nested_than<greater_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_t greater{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_HPP

/* greater.hpp
H8nn526aQ1xXiu3pfO0q5GvE9j8D6pBvEOk5BZAVCYqwIl5PXxPvjXyUeE2n3WmRjy7i+Ohbr/HIJ4v1NYDpyKcX8fHrSH+QX1DE8dcC8pFfDmC/+wGsQn692J9OyN6I/BYR/xlAEfIVYj19EbcS+eMivj+pbKigOCXisxINyNeL7c+SPu3AgrWDX58HhCMfuYPjp48FRCFvFevPAWKRTxKv6wGTkc8Ur+mIYhfy+Tv4+BcBy5FfK17fRfqE/CYRP4WaW5DfJV5TgFaO/BERH50/dhz5GrH+KskMeWEnr6ejbUOQD9vJ8VOA2hv5KLGePlKjRT5arCcHOVTgf+3FVCYE5bPMXu5P3OuEZn/kVyUB7RPHJQn/lb/E2P9af4VNpkgEKIdxn3evI2bCsBhXZtyCmc4c2lhGxyQlREcLgfXTZmbPnebMzc3ORQX+AutmpKROS8nMzJ4ZnedKvaGfsxFnyzrWLzc3ZeG0LOf8aZnOrFmudLFZi3Y34rmRBtfCHOe0jKy0bLHu//799/kLT5MJdwO0gFhAVYZMqABsA7wBeA6QD8gBTM3gT5mfyJYJuYDJgAcAVkAUoA+gE+BKlkw4BTgEKAK8Cnga8AQgBzAdkASIB+gBdwO6A+rnyoTTgB8ALwLP24BtgAoClBUBNgLWAB4HZAGmAhIAakA4oA3gQqZMqAEcB+wH7AS8B3gRsBLgovwsmVAIcAGm
*/