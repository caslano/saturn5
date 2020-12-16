/*!
@file
Defines `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIRST_HPP
#define BOOST_HANA_FIRST_HPP

#include <boost/hana/fwd/first.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) first_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using First = BOOST_HANA_DISPATCH_IF(first_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::first(pair) requires 'pair' to be a Product");
    #endif

        return First::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct first_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIRST_HPP

/* first.hpp
hPtS+Yh+6+XLdfxDfzrmN3E4Xf2Z5+qp6jvcj3Yxfzkwan8IPn/N9cvxXl91uUb+wov6V/iUVfgej02n17NekgeT4fibeF5fOS/beusn8PYqn79Fv6FRvKxDzJqsD/MpXVRMJ3aANxv4TH2rGnXblj5Jmkhv0DNVr+ubXkQnwrn0+6PqGL7YRzxZvTXcS6c0x2/Hht9vRed0VGf22cw+WZ2p/xR5U/KyPHPdzCPkQQS/fgkHhqizo1xnqfOLvT5e3i2FC++oozS4Nwk//uk+E/hOOJhdFAuOu+io1z3/lcExZZDxDVb/Jwafry2H3x/y3dbd1tH/K8fqn6yVH1/L1zZ8AR0Y6wfH+tBhVxnXXvxymPzT/8i8y30f4pOm89n8b9VA47ydf9B/6zZR31Afdtkz7pPO3/wMJ5p83vpgzgTz0g6eyqvp18P7++H32erzGPrqWPX3I162rpkWtW62Es7Nkfdf63e0pctv8ByP6oub3+mec1q/sN9J5z/P5+y0r2AGXXA7nq/ic4vUU7gv4C1+N0d+3cuX/cJPvAxPrPP3e9MRb2Q9Red0hw8hny5TP3RjXhM+aZTXP9ApK1znbzr0JutVT5sfOjLL/vJFT8HDP8VdfZXSJ8UN+kwPyIvLrU9G+ZhUOHgCHfUM3TWIr6+jj/iNGUudv8e+DHXV3n7oaFf905M8H52xZQyfEO4f38QHRuHYHrhnvnpeTN8/ZT1plH41/dD0RfB+JzxWOZIur5MX5fJMXpYvSXRe8H5he/n2mXlaqd97kfkdRf94PXudvPtPIt3NByfg4R5wmG7NGgdHyujtsfhskfNvwTcPyE/5nvouvpkNP1pYBxiOV8PvDVlNlw6Fazutq+P5Lafof+1TN/Jv6kB94n3yzfU60Y2N8DLmOYrTrTfh+znD4MV+62138sUHh31S939NHU4Qlwfoi73yfjJcfY/+f58OVE+Td+DHC+jKw8z7RrpFvtTQwbGH1Yf+93L36cYvpjUPjtFwn1UhHNW36hnTx+jBbx6rTxl+X9Bq4zhXv+BGz7/bfCXg8Y7B+4vkRUmidQz1Xfu1vLwd/6bSKSnm6WT9w6PFsYO+SYO6iBvPx/iogU+ntyv2qyM+ogaO1eOlhScaN7xYiC+WR+GD+Oe9Re9chieG882nqe8FzeQdvUxHFVygH/8pfhvvelWR4LiAX+iHD6yPbemsfzFXPX7LD9pPWrhFnPm52KxEfK5OpvCjSep2j3Uo+j3pK3k72no6Xl0lP0rohqRW8HgxfzUFz3XVB4OnCw8VR88z4l26YpH5ikXhL10zV34/R1eJW8rJ5qe/+f8gwsfh+0R6dCZevo+eXM8/luHLjvLAOkKX7fpu8qfmErhjX1r9B/TgXH+3VQfwsgRe9bwxqk8t/xtdz33nDObLkujUbfwB/dTNemDD8cb/H3/PgGf9YnQNXKY3U3JiwfFafr0fHDoa3oXfH/ui+Bhv5ZHwJYNfbeY6zfDcJnrS+Er/pf4Ojvied3WawK+2Vr9H81VX8gu/y5dT5N/D+Gmj/Wl4Mu0e/kcezvqRbz2an3mCbos472m419E8XKL/Pxi+tKJvD4Mj1i/aJhhHjM5OoTdmwtcU/uxvuJlnXe2Aupmtbn8Th4tc7xjn1cuXlfjjLP2wwXTSq/zG8eJwQD6+Kj9T5a3vvZl8tb7CAHVwEz1gPbVgqDpb0UxdNqND8Py9zu8TCY5jzCu9UHhycEz92/jqnF9EH9D5U36mc/rTsfrx5Re5fw/Hv/iI7fzOXPlxBz23Ai+/ZD30GrxOdxSk0leF7mM++02Qp/pTqaPMr3WG9ofhs/uMt4N+RTnc1NeP9qVrF8Atzxmr148=
*/