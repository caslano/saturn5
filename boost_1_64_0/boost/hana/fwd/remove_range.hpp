/*!
@file
Forward declares `boost::hana::remove_range` and `boost::hana::remove_range_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_RANGE_HPP
#define BOOST_HANA_FWD_REMOVE_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove the elements inside a given range of indices from a sequence.
    //! @ingroup group-Sequence
    //!
    //! `remove_range` returns a new sequence identical to the original,
    //! except that elements at indices in the provided range are removed.
    //! Specifically, `remove_range([x0, ..., xn], from, to)` is a new
    //! sequence equivalent to `[x0, ..., x_from-1, x_to, ..., xn]`.
    //!
    //!
    //! @note
    //! The behavior is undefined if the range contains any index out of the
    //! bounds of the sequence.
    //!
    //!
    //! @param xs
    //! A sequence from which elements are removed.
    //!
    //! @param [from, to)
    //! An half-open interval of `IntegralConstant`s representing the indices
    //! of the elements to be removed from the sequence. The `IntegralConstant`s
    //! in the half-open interval must be non-negative and in the bounds of
    //! the sequence. The half-open interval must also be valid, meaning that
    //! `from <= to`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_range.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_range = [](auto&& xs, auto const& from, auto const& to) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct remove_range_impl : remove_range_impl<S, when<true>> { };

    struct remove_range_t {
        template <typename Xs, typename From, typename To>
        constexpr auto operator()(Xs&& xs, From const& from, To const& to) const;
    };

    constexpr remove_range_t remove_range{};
#endif

    //! Equivalent to `remove_range`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_range_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t from, std::size_t to>
    constexpr auto remove_range_c = [](auto&& xs) {
        return hana::remove_range(forwarded(xs), hana::size_c<from>, hana::size_c<to>);
    };
#else
    template <std::size_t from, std::size_t to>
    struct remove_range_c_t;

    template <std::size_t from, std::size_t to>
    constexpr remove_range_c_t<from, to> remove_range_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_RANGE_HPP

/* remove_range.hpp
Besh8Q+FTeyskRZDMRm0TRpR6+mbjlJZhrIa1f9ps159SiqvpRb14vayqRjfTE7M8WauZUa73TfudGuTkNfgjBzgJdihPfiXXr7VDBiHuctRC4esBZEJbfasuDzvfaGmWZYWNHp+MWf6xxEjk5tbKvr05Zq3l8hguhmNyzlwMkHxGOREfLdDDHl6JhKT2bIaJ88MJf9LbiHvCEjfg5eTyRrt13Golg1Jw/5m5UvbX0lMQ5hO8UAfXOJhiMO0B1Vyumq3eL/OnK1MI0oBgV2gU5QsVCh70aFUPi4tEM5P9eEPvBtCzElzdMh+iZgfZyQiZmcuIUt7Oob02rclzbj2MDebV8uvLirkX+O8Ti3sn3RMDOemJ4ZvOJgov3rC2oq8qT+EVoZMxuENpepaUw5Xoovfvi8qVLPAQzvrQrhDZVaVOnqeZPNslqMKi/1J5rGMPPeadQM2s87It7vUl1yLzC1ZQIdIfZdHDPIwMkydmr6FJGEeqoFUMxwENlSeOuyXyJMFTdB5HylUbJ8+JPPPURPLp/lAzriWII7/VTEpfbXnTVwMK85cj6H38aTMbCRPnXQ2mQ7P/MH6EcnzCiLJoXlWuhNH6uSZ+BwK0OVIa9jSr2aiKXKR9g8Fyi2eS47dJcxkI7TvG+WUcTlJejk/QXxNgIqyVT3CuvFp1ak4J7DZTbYuTrPNXmrHswsO9/pXOwfg0a/aORCPvtXOQXhkVTtz8OhT7RyMR+9q5xA8elU7h+LhqHbm4jG42jkMj5xq5/Dg1rxQRQ5xz6SA4YJTZY94fUoG3VNMXs7xGADirNNfViT1XLaDZAyEeE3EGMk5vNNx43DWI26XYBAZqv9aNkBn+NP1H3GBpJIVdAsPsOtHZdIE5+irR40I+HF2UP0Ot41Qb6A2WWEZaW9hWK4/FJv5c4hmalNUCpf43CwXy7SqLcg61chaxlkLWmalsolYhUYEn01yexDMTUIQtgqLUw0jkqQ+Ju0VoooldGEaifHIEtstmDs45ZwOSRB3up2lfeTznu5FhLbRNeC6Zmt1x+rx5kiBuNsibYr2f0af6/6L2U1syJkT3DIi2UkI7KRm+68I+dkkcE45XYTa5qnBrVRxX4puGNF26+IoH1rk3PxlFJKoZbMjw06aJuVgyA3MINZ+ywd8RCFNyfbWlhizd6S4nz9lNKTRQICKoIe4f/6SJAemV6hnuPxEnbCGLznB+auTqiebA0nm/kx05pydgufX/HNXKg/YXgHSrNOPztrPjD64PjJz1Eh/Z+0+FYMtqzM0j67ROoL1FqIaIVNLqjFNezRGNe4A9qqFuFDbFEcxFqLLd3OpmdpfVbxHXPJ+/GSsBx3BRM8NT7VUp+JlWLXTjMd51c4kPAqqncnR5QXR5fnTYV85Nlnby1Cc5sd23yulgzfb+ioMP2MPZOEr8S7ufIeaRuexaxGkLgmtRmVtNZ1hiKWqJxHbL/OWpvmubrwU7z6NG1gRjOT5IHYZxcIKe42TryeTLKLBaQe3TK3NvrtuL05sYdbGYZIxAxBj7+DMwutAvFrl66C75TPnbtt9zzg6eLKQrYPTQfSRYuwcY5cxQyjGyjFWGTMUuZEJAG7IpZ4NNgyve9+aLkreQp2XNN7F1ljhq2UZ17vSK76DoeQqQ9Ygxz3vrZpFOST7yk4+7vLUrKKr+qJZ7d+xDVtH26jppJefV4fJ6UiurzFHcrRbDPzwigIFlfZyo8KW/jVzrcAiwkvMowzMtcO75G5vpO6w13epRCHNtwgoFGYuN9MjdstkhVv+pWfEp/qRl87gMyduPnqckYQO6KWLwBBuI54HAxDmug+s6QfDZUk1ySWf+ftqneMo9Q1oS50=
*/