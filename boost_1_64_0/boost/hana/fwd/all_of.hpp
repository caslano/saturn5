/*!
@file
Forward declares `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_OF_HPP
#define BOOST_HANA_FWD_ALL_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure satisfy the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a false-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/all_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_of_impl : all_of_impl<S, when<true>> { };

    struct all_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr all_of_t all_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_OF_HPP

/* all_of.hpp
RGdwRKD9BIyoM6b/JwY2Oz4wK1HpZ0SfW4IRLYiNaDJnMbL2VAzpZQ6J/gb85tDG9B2aOcGcHFFXeCW4E6zJuY2NrAgjw1CXcVIxoUsCYkJTQrmvPbOQ8vPg9cnyswD8sJTycylFJ2XoZSHQlnJzKdXylQ375PoXsL4hP62Qi7oMfSuQ6TurW4BiM44Lx9XBTqM/C5UyfXlJ0tOrVzgckVEwPUluXqwXQDRiN1gNwXk+BGf+Ebn+11x+T2S0ZbRuNcsN3ye7FdmUPwLL7IZ9/vXhUkt4jfC6KabwTZ3O9HCgEwyXGUpT5n3gnC+Fij5Q5lucxlCRgZ7D+Va3O1QkqaUQ0/Qcha+1Ed/nFeP0NJRPL3oTFtrpRR0wxE4vek9po8ku2GJjb+yDkuqroA1EgKm6Sh5ehLViwB+bECMF4Lo/reU4CiNY0zbKZfKmHYi6Ka5j64XrChSvcJGlXawxh2tssdp0oabJNpixgBNU+fAmgEBFVuNDnjz84g4BkHg8RDyIxJKeGFTEMCDxmnoQ78ckHlT0J7jQgVNNsM0Svs6yRTGCaM40kg0lhUrRB855EvdUWquLuAEtVook5zzupK7wwk4XrXJhlLvUry0CHZc6skFHkhMYA/WQn7Mx3ajMl6YvfBPkn76wA9rh9IXvKa3E/E5iDsLFKWjsgf/dN8QpyLIKW5yCHlKQ8jJOP4gFQcLdLlCPJFwKEqYvIgmX9kPC3TESerpJuI2ICByGVxB/V0x0jNBR+H8VHU0vYcVF+vrvs/v7UUcsJTGyk+vP1Otn9f5Rb7uBdbN6EI7wB6r/M3d/9cFQkrthj79YWWuBuJnrUc5zNj9EIxGsT7l0N5dzQ27Y6Z+Qv2NDeqM16/BzUXPtTq3emvaQWGB3tRTkt9W8vKJaaamKNLFl1UdMppsCDv7xe4KvpodnmNCBtaXLDASmhkuNs4fUnKFcYsHbxODf0x9KB6ycZwXI3++vl85uYn/VsDtURXAO6L+XA5nYmpLeyyvIygIU5Cv25tZ7gn9LR+c5z9Ctbt4twLccM/9+v3Nnw1twEOHsLBe2HPk9tY+Gw4G0qkqYcSLBVdYOZZgnfLMx/9matOBGiyFwHc0qt1Ml/Q5/vYmJ9pRp6yzqHdOwUFU4CiGzT/PeFy/0zRM6sG+ougEhIih2NnMNROgxUXYow3JaChqaN450haUpPoNL3d40nAYbBxf5dZbQBbADnJZtG7LSkb052xa8wLAxUymFPEmrrTFqhkB6SSitoXlTByCKEa34Jy2oJkno/z7Ei5APKtzOw5zBrOBx44b0pq/RInQVtqg0ZSZolaE6yjD0DjDSzSB7tnItjoRLDEVCnB9NX5fe9BIbOJVia3B/Z0ZLsN0SKrYqkYuwgW1c41sjyFSuSjiVc9SURc2BWU3zSMEgf7Hc5X1Up+LMKlbLRO/S7Jn+wdBbr2OGVC1m7NJIeYVL/fyDww30f1i1PfsBEo92e+EYzRyNWtoA3kBItwiwmLjQBPWGS4A/rP3svtjSViyZUQM9mEIzedKoDk1WWjFnl/6TqLtrFzCSGnYGzM7mSLlbmd5weGNAuRR7tsU/KPhaetSHbaG2Jg8TPKi04fCm9+RthXnaVmPAtdXkT/+dkdRcuFXCo4mPc7Za8Gjm4/StNjxKfDxjqx2Pg/g4bmsBHtP4aHPUytv2Htk3bh/7MTn3iYUSLjZyw8LhLcejbDBsnrgQGGW7tRssHvXMbcMNVs3cpTwF6uzZb18ISmEX22Corqz6xOzWZCF/PftZTXN7sNFwVphjcDGWyXlYzaW/kRKjPfi4pWHnjWOVhdwurahrLWOlyRrWCKe2w6M6zxEMoLRWV6H2CaE=
*/