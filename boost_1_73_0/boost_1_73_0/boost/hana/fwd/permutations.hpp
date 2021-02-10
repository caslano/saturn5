/*!
@file
Forward declares `boost::hana::permutations`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PERMUTATIONS_HPP
#define BOOST_HANA_FWD_PERMUTATIONS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return a sequence of all the permutations of the given sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `permutations(xs)` is a sequence whose elements are
    //! permutations of the original sequence `xs`. The permutations are not
    //! guaranteed to be in any specific order. Also note that the number
    //! of permutations grows very rapidly as the length of the original
    //! sequence increases. The growth rate is `O(length(xs)!)`; with a
    //! sequence `xs` of length only 8, `permutations(xs)` contains over
    //! 40 000 elements!
    //!
    //!
    //! Example
    //! -------
    //! @include example/permutations.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto permutations = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct permutations_impl : permutations_impl<S, when<true>> { };

    struct permutations_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr permutations_t permutations{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PERMUTATIONS_HPP

/* permutations.hpp
luv71qrhCupwjeVUroZTvBFwC7gPV3p0GEil3IgoiAFfu464wddjM4UEeRuWweG5jMdfPTZOHW9xg3e/OxFtjOBxWxz7uRz5seXCWn7uhw4m7EhZeQLQiYv3pQM4bA7WZK0fEJSj4zXkoGrplnjPpt0b13Jwx0w7zBKjhbc0zSzKPgFgcK6lmnQrGJ6KAsN2vggAH8CFnfLogWBodDg4UavKAK8zkgdrjOTBZiqqhlu2ai/q24oHm9qKVf3AdWCCyQFQbsmdM6Z9ztoOD8mrtelR4AwoViVy4NQxxuOD+tx3uIa78DDfXbixt70qxvXl5XBTeUGxMFxnhpfj6hwS89/a/BYbeQBoxpGH6TAsn82jW2Po27drQ5bn1tCfJYLdDLRIMBQvyBqSdTxqnlyr1jFtpGWiqq5r4GQd+iooQV6njmrceG8FgYWUAysgbKokMeTTg3eZSaEQ6XEEVohxFczXkaj6BvbhXq6BHcO9djxYDsKsZwVgkoWpQmUZPOkiuWJnz8pxU74OYxZKo6Wqz7GEPPUt8sP/nAfbT/Cuv4N1mL+DVUxyQePjdn2uq89zX9adbXTBWgfF+uP+eFPns9hU8/jEQvvSoGP8lfWWqKw249I9rrWRv3BdIzlIWxmBsc1dmBAMqq/cYqMp
*/