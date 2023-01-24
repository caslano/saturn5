/*!
@file
Forward declares `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_by_t {
        template <typename Predicate, typename Object>
        constexpr decltype(auto)
        operator()(Predicate&& predicate, Object&& object) const;

        template <typename Predicate>
        constexpr decltype(auto) operator()(Predicate&& predicate) const;
    };

    //! @ingroup group-details
    //! Provides a `.by` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algorithm` whose
    //! signature is `Object x Predicate -> Return`, `nested_by<Algorithm>`
    //! can be used as a base class to `Algorithm`. Doing so will provide a
    //! static constexpr member called `by`, which has the two following
    //! signatures:
    //! @code
    //!     Predicate x Object -> Return
    //!     Predicate -> (Object -> Return)
    //! @endcode
    //!
    //! In other words, `nested_by` is a `curry`ed and `flip`ped version of
    //! `Algorithm`. Note that the function object `Algorithm` must be
    //! default-constructible, since the algorithm will be called as
    //! `Algorithm{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_by { static constexpr nested_by_t<Algorithm> by{}; };

    template <typename Algorithm>
    constexpr nested_by_t<Algorithm> nested_by<Algorithm>::by;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP

/* nested_by_fwd.hpp
dyptqWUKtTFoM8y3nmC4ic8jToUK/Vmo0goXQGlqaArdaFAbA7TULETnQ+4p6m+UlvsORmY4Ix1Yrkp2hS5pzy3Mh10AptITXIx+LLYSszAU0KsF5LG2hmGyDs+Hot8ODMQOQVr6X3pTrfCwvhBKkdFsvZ+SkvtREAarTD+N499O67gdOaKuzXsVaRe3U26y+Ckbh7vJUVZmHRpX6UTSiv67YXSAcbcOj/f5fevhKysivrkTYvlN75G6hPXUs81LlH34q21nOd9JIMfUur0Y4L9Tz3Kgxhlx/BW3dyLH9UPlqXTh6vDKmzBY6V0LLTtOeOlNTKfLM7aIPkxIaDzipx3ctKX/ZSzJ6MNMoM76OhpdjYQJAJrHCnGwMmxN/Iu+Du98KIOr69FRDhqlluN36JVyGq0dam40n9EdjnArTYP7JoRSitB6L8XuJCMXBUV/vKkxqYtyC2tvl9R2E1oTHNZ38WwSod0ui/YS1gU531O0ZNoNoZfuxjIX+u8G1Rh45Y5vIyfW3qSRWkwOhR9Fzo5QgYO9KTQVLxswcSvrvWjFp8TaBi19RY6KydXfQBfiBDzbOVy2SrGuCoLIx0QTih9kHCow2+hyL6WxP55ydAdLmm9rBYHZoQrMbf93AnPV/MsLTN9BRc6NRsNrKdYOKgQ7hwnB175BCL57eSH4Xk1cCL57RSGYvuliIbiNShIqBGV+sTXg0kpB1pJD
*/