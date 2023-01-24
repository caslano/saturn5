/*!
@file
Defines `boost::hana::Functor`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FUNCTOR_HPP
#define BOOST_HANA_CONCEPT_FUNCTOR_HPP

#include <boost/hana/fwd/concept/functor.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename F>
    struct Functor
        : hana::integral_constant<bool,
            !is_default<transform_impl<typename tag_of<F>::type>>::value ||
            !is_default<adjust_if_impl<typename tag_of<F>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FUNCTOR_HPP

/* functor.hpp
MWDrtiG7ic/eN1PRjjtm3nGz17qiJtx32CNdZMLdkxAT+/3A3Xrs9/0goncJfPMprvtxY1DqkMWwNHJ6ZaWkYwBXXDAPVD1ptCcwHw1vJ7sE2hERLESDrCMRhrjqSAamjXtVHd2qI9Vjy8IDzWGMl/ayX2J1EtDK0sGtKsVhZxqKmD6xWHOAWdHFR3v0NCHc1tLa6Lb3uQvDSaGbNKdw2omDqMLjq/t4hBq1qYx8L+lkDQrRmTQA6TVXTSuGS7Ojn0gqXkZTzDR7ICeYwSaYcTMd+xrkONCHgxeT9cXCktEhM2iTcbPiEwH4AhI/zru4K80LU9SFZhsrHYGxN9i1KCviytUhyMNyAVCd4/grQl3pZzhryQs6rzYDkNq34GtzHD4ImG6jic6zKmCvAYthK4bB5Ta4eJw2GP7z4AJSj+aycSm7iCdO9czBrwb8+mYPfuUA0Uo2+ygU2OwYQJ9BtgAPyzoqLWJX0ImWGEbuYje7mVfUl4hesUacca9UD4STtt9CSw1xHRQINicobi39LCwdZ02YvBHn0Z4Yb+zWRm8C+4cFFwBsHoZocEMDtmFmDCUE9PCj/GcJVHgJ8BhEAQNBDXCCzlgcG0ZpLeuEd+yHAId14DajqYQlSp1pMGjno1CFS8QdPf3/mNA3BQZ7p97AyTj6m86umVrRicsjI6niKgy93xpxZk5gl1N9rR7bBKjv7xAnFejpLGYu
*/