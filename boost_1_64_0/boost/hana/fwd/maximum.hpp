/*!
@file
Forward declares `boost::hana::maximum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MAXIMUM_HPP
#define BOOST_HANA_FWD_MAXIMUM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the greatest element of a non-empty structure with respect to
    //! a `predicate`, by default `less`.
    //! @ingroup group-Foldable
    //!
    //! Given a non-empty structure and an optional binary predicate
    //! (`less` by default), `maximum` returns the greatest element of
    //! the structure, i.e. an element which is greater than or equal to
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
    //! Given a Foldable `F`, a Logical `Bool` and a predicate
    //! \f$ \mathtt{pred} : T \times T \to Bool \f$, `maximum` has the
    //! following signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{maximum} : F(T) \times (T \times T \to Bool) \to T
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! Orderable. The signature is then
    //! \f[
    //!     \mathtt{maximum} : F(T) \to T
    //! \f]
    //!
    //! @param xs
    //! The structure to find the greatest element of.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)`, where `x` and `y` are elements
    //! of the structure. `predicate` should be a strict weak ordering on the
    //! elements of the structure and its return value should be a Logical,
    //! or a compile-time Logical if the structure is heterogeneous.
    //!
    //! ### Example
    //! @include example/maximum.cpp
    //!
    //!
    //! Syntactic sugar (`maximum.by`)
    //! ------------------------------
    //! `maximum` can be called in a third way, which provides a nice syntax
    //! especially when working with the `ordering` combinator:
    //! @code
    //!     maximum.by(predicate, xs) == maximum(xs, predicate)
    //!     maximum.by(predicate) == maximum(-, predicate)
    //! @endcode
    //!
    //! where `maximum(-, predicate)` denotes the partial application of
    //! `maximum` to `predicate`.
    //!
    //! ### Example
    //! @include example/maximum_by.cpp
    //!
    //!
    //! Tag dispatching
    //! ---------------
    //! Both the non-predicated version and the predicated versions of
    //! `maximum` are tag-dispatched methods, and hence they can be
    //! customized independently. One reason for this is that some
    //! structures are able to provide a much more efficient implementation
    //! of `maximum` when the `less` predicate is used. Here is how the
    //! different versions of `maximum` are dispatched:
    //! @code
    //!     maximum(xs) -> maximum_impl<tag of xs>::apply(xs)
    //!     maximum(xs, pred) -> maximum_pred_impl<tag of xs>::apply(xs, pred)
    //! @endcode
    //!
    //! Also note that `maximum.by` is not tag-dispatched on its own, since it
    //! is just syntactic sugar for calling the corresponding `maximum`.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto maximum = [](auto&& xs[, auto&& predicate]) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct maximum_impl : maximum_impl<T, when<true>> { };

    template <typename T, typename = void>
    struct maximum_pred_impl : maximum_pred_impl<T, when<true>> { };

    struct maximum_t : detail::nested_by<maximum_t> {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr decltype(auto) operator()(Xs&& xs, Predicate&& pred) const;
    };

    constexpr maximum_t maximum{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MAXIMUM_HPP

/* maximum.hpp
ENwO+UAieJdmBaoYMMib3zwK1GsXSUF/QiV4LRTp3ierzN87SsYt5DhrNM5KcZBe3qx67RSKCqPlsVC0kerEkdAyEorqcs+rSaS7LeiHSV3IRIcfRNBFLDCNZaHoSAsCNaFoorW2wTmKNifDSSjapjZ/6TuTE6xPlR+xPr3xbt995HvKUe9ZR70XHfWex/ufR7rbc8ulSVNEk2YiNpvkSJskqHQ19Vo+k5r5lGGwZTAZdJyMInE8M1M/OFGSEeqroJaKK/TQqgGQGTbW85uhZ04sLGyXvcC6e3mNCy7Kebtyh88rDqA9hmsNpNYTLtcSIllxIM4rsucaLpy7pbpNS6X2VcnOO5SMpb6wrjvMlzAKncoIaBO7lBGucBw0GiAA453v6q5AnIfVs8B5w3ZJItnOYn0C2h+awX++gJbzQVriS3jNwIZ3Qwydr/Y3X2epXR8DXjpF/mRCt/k5SoxX0uM3kw/r9YlvhLr6m3ECvxGaDombqEScx/PShBByYL0mcV9of3+zx46Cza8mtpnBZCgeOx3kG1WNdlIdaxMb1ddxR0RtpQwjXJShBT1KbONUmKtgKUcF4oKWJhJpQrgnLntat9TZg42RBeIqkhAVpGH3CCdiO7YGYV664+2BzWrrwMaODQPX2MhuNkxlMxCHMRCHMRCHMRCHERBVAhduYpC+lviuVPbhQe42MFt+JQemlOcGxrnnT5kKTdaEEkjyhEzyFWDSl/On+T95uDv+5BP+eFhQM5n4xQof4c5lhESMP5lPGPjzKOHPTMYf2y0G/vyQ8YcwW+yd0R1/auuOwZ98AG0Bo0tRFH+ee/gY/OGEpVpCJPMG4nGsURnFn2iqy7VUag6oHyGGEi8PsdSRfJ18pB0EVR2JAyGnOhL3T13Q6lEKk4BGh5QZOhrtD8R7giOTNTSqc9KlVDVeopEzHZMezize6vtSOmFQfO1r2rQeRxiUThi0lX4ycf8UT3J6F1oxvZE+Fanxk4Wm6PmQNA3pzGPsEvOS+Qclj0aAln24U2bPQCYzFjq84ScTEziKvy5ZeyaVhb08l4KKOFzDsSRZSpYsJU3hAM7+wo3fiHEC5c4PWtYS1qeHArhQW1epId6TT2gby/Cw6qtxrB60N3Gq1lXLkAJXfAPx6SFKuBcJ1U4k7diq7r6ACu3YUvP+K/i1AWn/ykgbX7FMIm2e1xPZwhhb1LFtYMspYeywJLRex9t4tmvw06PxlidEv1/ICeHHnGS8LfkJ4+20KN4ewIz7X/SHscrD+m8PdcfvYsLviVgfCbPBDx+9Pnr+aOD3z8hq1WLG7/SbDfy+x0z4TSu1OAuhUfz+Rc0x+F0M4D7ER/ueKH6/8dAx+M0Jq7SESDYxYPWKpO9E8TuaapyWSnVjfawEesfR+ljA62MBr48FvD4W8PpYAEUFaMgkqYVQckgGkndE18rOgBVrZYqG5D+zA8k/VGFSje/Zvci6aumIUjdJRO+7Ft+Z/J3Vdy2tfIn0naLEJa6l038dl7P7NuE7g78z6RvJm7C6JjaZ1+FTjBxw9vhyYhPqyVLXy/WUtoiJm9PzkZu+M/Hd2HezuSVxszlE3dqLBxSqNmB1xb3SX7aZzC+Z19Cimrib69yL72T+Tum71zzanriX1nCQEHVz4l4VWelVbU7cyNnXUPY2lLo+fR0t3qgOGVFhkRMVvazQj4oM5pdR495jakSmQ2oj15ZGtbm4tmxlNJQBkSI7scPxSygg/PJVk3m1eaN5K+ptN29KPERkaktiJ2+MPEm1r8akTwC120Y/KfgxT0CLPUlUAuKgNtmgtqEgKmS92pL4MWV/VW0jlTImV4mtyEgEFT9p8idD/mQSgfMnE5U=
*/