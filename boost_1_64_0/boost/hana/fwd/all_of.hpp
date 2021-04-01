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
Tkm5fEehGrXHpnI0zdos9lUVDlqVXVGZkbFJw+A5V5OaNj0XEcjhlKN7yxLv8qJvbXglb5fqE2d2ZeBdtVsWqcWE3KW13ZB3JJublmgk/ZKGpj4xX+c5OSkiob6LltrCk4Ek0NqgrNJQHB4x1gVG8U6bApiy7eCvI4BB2xnQLTjdg5BrtBkUBmB1p2XhENFeNZ2hkPZ+08F5kGkLqVBOGm9594c91UgvY+dcqPjWq3A2/M3hSPOVk/HWnyWxQzIRBYcykEBSL2sZ+Qly2ReE6Ng8Bn4LV5QDYpv6GhGt4wf680/iPE2XUlx1wKax57m++Ebx+DWWtMiNk0shayWOB9aqM9NTfmAmAW+G76Yfwnnerl/DPm9V45TBzZ8aF01STCI74DA3oDBzNjqQfF/Ybpot/VRtri9d7a4Af+PRM/NtdtH1iG5X99tTDtV+qaM4DnF1rBE78T4n0OjjaflBO/FiUUxT4I59fMWLh8QStRuYMP79VJjCId2o21zxxtjs+Eo2U44Xe9/venQfaytfvH16Lse3bDBlg1LvE2SLZW67McaYRnAnznYA1A==
*/