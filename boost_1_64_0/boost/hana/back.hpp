/*!
@file
Defines `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BACK_HPP
#define BOOST_HANA_BACK_HPP

#include <boost/hana/fwd/back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) back_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using Back = BOOST_HANA_DISPATCH_IF(back_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::back(xs) requires 'xs' to be an Iterable");
    #endif

        return Back::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct back_impl<It, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(len > 0, "hana::back(xs) requires 'xs' to be non-empty");
            return hana::at_c<len - 1>(static_cast<Xs&&>(xs));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_BACK_HPP

/* back.hpp
HM3Igo7ib4mFRF/DJZ93mIxNGqEFSGAMIXaeX8XTw3tFzy0f8hwHYVQR2UFIffU1fY2JA/p/+Os3cq1v2qQz5XQbVI4+cQUwNfFfymS/IUzjDZJnu0OD7RiP0GzsZbennpniDU9PX0RHxhV787eZ7AB9OnRvstcH+3TdIIc7QjHMH67HCaeSeQBFVsozT5h9E14dOF/jt9zzdRWi8o4QhZqGYQFFBdNOMyYazCtGABMy5wB5A/rOYIcNdzKgNNzDGiYkJ0MRJ/HvR4q8z72YXhuWFjnkMDVuZ3tk9lAo+iuHMNxzR3uIonyWTfPx1hvwDA1aR/Gt3vHj9UH+S3ZLkshYZWYoEd9IZc2sgWQmLEKZm2K+nKsf2Z4AXfLF/3LhqavsJeVfQoK0jjcPMSs8hWkZCdurJKbwGEdAKTOhKU0ux8C54L9xeMRxkYeqqR2uSpYbasMxnxHsz3DyO/czv7hft20wF9gzWek8akoNg1P5B2E0QD4BOkcScSC0B1Dm8CPhlSCJAS5XcYf16rxR7MWhowRXkpjvglSXYj4smJOwLBRyPp8cL01mEA==
*/