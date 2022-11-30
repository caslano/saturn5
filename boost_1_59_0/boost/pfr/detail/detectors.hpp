// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_DETECTORS_HPP
#define BOOST_PFR_DETAIL_DETECTORS_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <functional>
#include <type_traits>

namespace boost { namespace pfr { namespace detail {
///////////////////// `value` is true if Detector<Tleft, Tright> does not compile (SFINAE)
    struct can_not_apply{};

    template <template <class, class> class Detector, class Tleft, class Tright>
    struct not_appliable {
        static constexpr bool value = std::is_same<
            Detector<Tleft, Tright>,
            can_not_apply
        >::value;
    };

///////////////////// Detectors for different operators
    template <class S, class T> auto comp_eq_detector_msvc_helper(long) -> decltype(std::declval<S>() == std::declval<T>());
    template <class S, class T> can_not_apply comp_eq_detector_msvc_helper(int);
    template <class T1, class T2> using comp_eq_detector = decltype(comp_eq_detector_msvc_helper<T1,T2>(1L));

    template <class S, class T> auto comp_ne_detector_msvc_helper(long) -> decltype(std::declval<S>() != std::declval<T>());
    template <class S, class T> can_not_apply comp_ne_detector_msvc_helper(int);
    template <class T1, class T2> using comp_ne_detector = decltype(comp_ne_detector_msvc_helper<T1,T2>(1L));

    template <class S, class T> auto comp_lt_detector_msvc_helper(long) -> decltype(std::declval<S>() < std::declval<T>());
    template <class S, class T> can_not_apply comp_lt_detector_msvc_helper(int);
    template <class T1, class T2> using comp_lt_detector = decltype(comp_lt_detector_msvc_helper<T1,T2>(1L));

    template <class S, class T> auto comp_le_detector_msvc_helper(long) -> decltype(std::declval<S>() <= std::declval<T>());
    template <class S, class T> can_not_apply comp_le_detector_msvc_helper(int);
    template <class T1, class T2> using comp_le_detector = decltype(comp_le_detector_msvc_helper<T1,T2>(1L));

    template <class S, class T> auto comp_gt_detector_msvc_helper(long) -> decltype(std::declval<S>() > std::declval<T>());
    template <class S, class T> can_not_apply comp_gt_detector_msvc_helper(int);
    template <class T1, class T2> using comp_gt_detector = decltype(comp_gt_detector_msvc_helper<T1,T2>(1L));

    template <class S, class T> auto comp_ge_detector_msvc_helper(long) -> decltype(std::declval<S>() >= std::declval<T>());
    template <class S, class T> can_not_apply comp_ge_detector_msvc_helper(int);
    template <class T1, class T2> using comp_ge_detector = decltype(comp_ge_detector_msvc_helper<T1,T2>(1L));


    template <class S> auto hash_detector_msvc_helper(long) -> decltype(std::hash<S>{}(std::declval<S>()));
    template <class S> can_not_apply hash_detector_msvc_helper(int);
    template <class T1, class T2> using hash_detector = decltype(hash_detector_msvc_helper<T1,T2>(1L));


    template <class S, class T> auto ostreamable_detector_msvc_helper(long) -> decltype(std::declval<S>() << std::declval<T>());
    template <class S, class T> can_not_apply ostreamable_detector_msvc_helper(int);
    template <class S, class T> using ostreamable_detector = decltype(ostreamable_detector_msvc_helper<S,T>(1L));

    template <class S, class T> auto istreamable_detector_msvc_helper(long) -> decltype(std::declval<S>() >> std::declval<T>());
    template <class S, class T> can_not_apply istreamable_detector_msvc_helper(int);
    template <class S, class T> using istreamable_detector = decltype(istreamable_detector_msvc_helper<S,T>(1L));

}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_DETECTORS_HPP



/* detectors.hpp
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
*/