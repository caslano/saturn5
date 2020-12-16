/*!
@file
Forward declares `boost::hana::take_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_WHILE_HPP
#define BOOST_HANA_FWD_TAKE_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Take elements from a sequence while the `predicate` is satisfied.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `take_while` returns a new sequence containing the
    //! longest prefix of `xs` in which all the elements satisfy the given
    //! predicate.
    //!
    //!
    //! @param xs
    //! The sequence to take elements from.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! sequence, and returning a `Logical` representing whether `x` should be
    //! included in the resulting sequence. In the current version of the
    //! library, `predicate` has to return a `Constant Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_while = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_while_impl : take_while_impl<S, when<true>> { };

    struct take_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr take_while_t take_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_WHILE_HPP

/* take_while.hpp
bHViwRLjJa6g3AvVMbveghWYzPD8eh1nx2Z4SJZylPKJTNAJ+z9bjXuqbP8ney3b/7kMxdz1kFHMasrKgaoPB8V5vJLDsP8dOn35UpfmzTsVfZ+XSiNo1zduB21onlRJW1B8p0M1w7cwmeMYbJLy+JCX8uvEpSr/HFk/YSP/U4Kg1CJr5+IHZe3MfebItRMU5jVUHw9vSa6PM1R9XIz62LbykPVxVoesjxdu1+k5W9ctukPRcwaTExQvLpe18d7Tem3UPD6oNiY8/tFqQ9mvz47ic1j78BJPPMUh8Q7G41NsOxgf/0oADLmoWZy4n0QeAbECTRtqPIHvJ90N9xHeh8Jm6kI6JwNjNFEzaUXySv6DNLp6niFTP/jvDDHrz+pK/oWT4uulGtNXQg8ZocIc6kIjVOg+AzWBUedI1DEySgPoAzluUyK12Uitd4VKjYWT6Bana9934+MOnWYEnclBH1NBsbQV20xNo5mtaTqOyuqkZTBoFGhsKFtFDopoN89UXKlfMtIs5jTDKz60aDapPCDyqaTauRwJjlyhdpmdfGa5iuxLTqJ/SuifXM1Er7RKA9jpUYSQuhOh7Ylm4nSefdBIh/reccW23A52RaWr+EM9v/LU7bNwllMNJQCy/Saafo6xVOSF++TQeFMi48uQ8eQHFeMhlwQabcYzDNcM4Ru2wdBEFatOPN2ZkJfXcD6cx7Aj5PHeclW4vow6PrOnhrON727KpOz4apG46odSkLA5dEGiLSvu0ledj2m9ksYrb1HoECD5fD3G5+te/XzdSufrAZ6o6b58gf5Gw638yojNApteQ8Fhk0qxOgrFrFYlizoD3fYMcdxyo4NRWM+gsDUy7CUc9uUHjLAkoszBmhr+BgeIX+UWX18K8Js66BHnAgShYtsmeNfr1TOGN7PZR98fPHVs9TM61JvUv+eAxgJFI2ouSfEk0e4jF1O7Z8H9udA3Eu0e0pAQ4u+7X8U3JsHDn7+Smm4Tr39CQ1Jq4RgVnq3GcCOS/J1KUmfn+fk1aO21zHbD+htnLINf3ncx8DTy6AUpl1QFZuNQi40wjX3FFA9+Nxt+M/u+SG1n4aC/SgzUvhONlvxC6HbD/1KmyiGpmh8nTaFU7ssWtkXziRyF0/yTuyGIKf8sOW1GPs9z4slasUvNiS7SNqSFlOZF3jJrq3CzPSMxA4daZaNMv+9osyDG43EIa+g/tHyVGjwFWgljIMe5kwBc+ZfJZgnfqmSVCLdqrO9T+99rZIUDBT6gYF2I05IDPYdA4dP1Pl3724QuBOUTHdpdZmVdiuIHKD5NMV8KfyE5/mLEpxH01o/5CFOmczyn41Uj0U07YqP9MoJiSquuq/BJtE9iPBz3EzUPug+aB/9+j5oHMRoOdR4rr+nTtA9q57TM9kBoHupPdGg+40NCd95j1Gpd6AOFD4gfdSROBj2hA0bEYhUxrCJORc8wgTxjunnlTnk4OFse6BH+vcRcoOJ/4Z7+j7Z+yvnFFQ6ryeUKpPbSn4zJodGL43ZrS4eVz9qffkBNwa8e+aBd/XrfxT4rGV63muCB+he23K3Buura3Lg4ZVnCpl9G+OJQ9joe9lcG4yOafzLawffYx4BW+NP4ngVac0BraBrgYGg6+ZrFP1gm7e37GtqFA1rEfY/o12lIOTHcKL2L+0ZHx8NUr0Vc+3s1BZWGmyTyMk584x+5IsLXs2dQTAKzG57NQLUoZc6XHglJq4uPmAX6dNWQqdEm3QbFx35DVe9/6LMkmEDG3EbXgLT8Pw5YpOo7dCGH6fo0fdmpI/+L4K8bPgUD8GMjkRAn8u6yRLeLnyMLQdNA6KdGwBkccC0CcnoX/I73zbKj/lKFqhM=
*/