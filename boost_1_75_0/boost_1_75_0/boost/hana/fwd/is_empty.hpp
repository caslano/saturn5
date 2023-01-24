/*!
@file
Forward declares `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_EMPTY_HPP
#define BOOST_HANA_FWD_IS_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the iterable is empty.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` `xs`, `is_empty` returns whether `xs` contains
    //! no more elements. In other words, it returns whether trying to
    //! extract the tail of `xs` would be an error. In the current version
    //! of the library, `is_empty` must return an `IntegralConstant` holding
    //! a value convertible to `bool`. This is because only compile-time
    //! `Iterable`s are supported right now.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_empty = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct is_empty_impl : is_empty_impl<It, when<true>> { };

    struct is_empty_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr is_empty_t is_empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_EMPTY_HPP

/* is_empty.hpp
pj2mQ6Njul33VHYu7e2sjRc+nV2aXZRNYGxQuFrOoqtb2q1Ho0kTjvms6iN3S3Y3oeUT4GNfyReUpc5fRnNMeOxxzHtLfZtyrF+nvVkgXgpXe81p//BbgJaV+6yzvynhOJjfe1Dt3HpH11r/lBjMfStwMmm5GFDpseih933DAfieI07eJtshhApmiFlVJX+KVRzDiNI1+BTmlMIiJUYevCcwmU/5vZno18mPVX0fOuuNJ+WPCy0DHPzIs/v0rynLrF3YiG5zRFW3xCnXBLm1mV2XU96OH8GTxvYD5HPOUFPvYx2LopjpyXx30atGhznwbZIZsIu2Ywvz1vrG/6mkVs9lPqQS8S7JyXggKBITt7CuY1LOux234TV2W0ymZDByI/I10hw3hLLaiozE5dSe2oqX4mzIMrrQZLmLlh/ukpoFyrTr/SBhA0afhLqIu3W7pBsyGRQbeFosRLH3GP1uZvQtyIYxa3cP3Pmt4ZpTwrnQLN0rBc4FVMMl8m3B1lP8B//4C5oI3HyJ3fMfV07PYK8x3GzstPaHzhHww+p8Om61/e55DKYzblB882R+fiTldGY69LqF3SQc0y1JID9WzktUhaghfsHpErXzgnO3hR4mLCpHPE6RZd+KWD/XMyki4uDIl/L3e2Hk4Iaf6xYeBs1G4g1ohiK9ejhVnJaugdPwpFf953zf1X+oAG167z6p7QVdp8LSEv5hx6oh
*/