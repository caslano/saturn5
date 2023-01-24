/*!
@file
Forward declares `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_HPP
#define BOOST_HANA_FWD_ZIP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip` produces a sequence whose
    //! `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the sequences, which are all assumed to
    //! have the same length. Assuming the sequences to all have the same size
    //! allows the library to perform some optimizations. To zip sequences
    //! that may have different lengths, `zip_shortest` should be used
    //! instead. Also note that it is an error to provide no sequence at all,
    //! i.e. `zip` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_impl : zip_impl<S, when<true>> { };

    struct zip_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_t zip{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_HPP

/* zip.hpp
I+zYnu/7qh0aDHJlxGFgu0xzbCMCc8bgYM+1fNN3dEvFcMA8qmujX/QREAOHlhppvgE0RYamBb5luoFtqJ6l6aBC7LqRZ1Ip3WembpuRBgqrkY4BWVFgmLaum07sO57maFYcOeA8l4bGgDNIhhFbmg3BcgwHoDA39t3Qi2NwDXAUhh4z41BD/VgPmWWCKDZExjPN0MYrGyPwNchVzAzLCCLwtGtbvh+ZGovUwArAcZEdR4I2QyhrB47n2ZrtSo3h+rUm4X/QHOgBWsLSY3H99Enzjq7NCA0w/OdAr+iVVgEwoRmpoL1OWgU0dSJfcxxPhTYAMQKwqWnZEPow8FkQxBiZaXih5psa9Asw6sXga0ggM1zDcEIWgY8hMsHTJ4AHFyBkqDpq5Pq2BZXDXJeY2oG+8R3QzY1809VCECq0Q4Y2NQgY8xxXA8YD04WgRbHpgS0NC2ODqgAPgjOiwIoiXY3swIKqsnSNgRZRZDHIrwlGgarDCBzLYS6o6egeuAwvAQgIquqGOwb/HnrxIeyezd+grMYlSrP78C+unz5Z3xlahXMWWuBNMEBg2JoZxKTeHEgEysa2oTsOlKfqOJbrAwgoHaipSAtC8JjraMwmDWpHrqX60PfgaM/B28gH/okhjMC3NZSzIvTlOuADDQynabjxITaGCbr6dqhFIHocqMCQDhJZFvSapxso5YJRSSQ1HbJqkNnSmBb7nk9U
*/