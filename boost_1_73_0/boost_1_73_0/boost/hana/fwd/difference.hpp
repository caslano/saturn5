/*!
@file
Forward declares `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIFFERENCE_HPP
#define BOOST_HANA_FWD_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct difference_impl : difference_impl<S, when<true>> { };
    //! @endcond

    struct difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr difference_t difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIFFERENCE_HPP

/* difference.hpp
VekPCOQIvAG5RFYD6QjZ2dH6vDg6ggPRy8QZrEmCagqFFDVgQoRIEjT1NyFpzwJOcV6+LSG0xyT5KxMp57Q7zpr1Tnqd9ribCqEQNd3Jmn1dPHsmnupXmgT1TB7zo9uiCIyKhIeFdy5d7zM8dVD2xD9gSByjM/4ALlRye8Sf2dOdAV3m8ujJ1yME4CZg9Tu4/OArXgvFR/ThyHqNIpy+xg9HqcW2pqS8jTbbFn/uJ3dob+Qhe1LkVYi95gEslReBB4w+AyIvamoV0SNwQAvsHTjcxPEu6+IGPFh3MiEPGCG9V57Lj80fmy1WyJH8n5UPzEeLvnNMqzPqdoawMB3QZ6/bnbdq8Xmlm6I3JTWN8PgRMjQaR0ChgWCCFNsbH1wbZTdBHV2xpyZOQMdwk33it0sJWoftKTpBekpXMAvQY3GtTr30Iw88viBxIugJ5ttVBDY76EnlaAwwajs7ZKXkjlIm8jaJXDT36QugLI23W+TaHF2ID3UDzdEwr72DumYCUHFP9PLbq6MWsIbLsQ2vG9hW+BP0+gPQQasg9q8AMHgWbgQtqFvjydqwi0Bwy9HfG+I69CdiGzi5/gR5m+EyOGAyOUcGt4exSPsboHbggCd+PHjnjHp/6/6OHWoItU7iAZ/8ae0pII8S+5QY
*/